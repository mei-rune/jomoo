
#include "PropertiesI.h"
#include <fstream>
#include <sstream>

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_util_begin

using namespace std;

std::string emptystring;
const string&
PropertiesI::getProperty(const string& key) const
{
	map<string, string>::const_iterator p = _properties.find(key);
	if(p != _properties.end())
	{
		return p->second;
	}
	else
	{
		return emptystring;
	}
}

const string&
PropertiesI::getPropertyWithDefault(const string& key, const string& value) const
{
	map<string, string>::const_iterator p = _properties.find(key);
	if(p != _properties.end())
	{
		return p->second;
	}
	else
	{
		return value;
	}
}

int
PropertiesI::getPropertyAsInt(const string& key) const
{
	return getPropertyAsIntWithDefault(key, 0);
}

int
PropertiesI::getPropertyAsIntWithDefault(const string& key, int value) const
{
	map<string, string>::const_iterator p = _properties.find(key);
	if(p != _properties.end())
	{
		istringstream v(p->second);
		if(!(v >> value) || !v.eof())
		{
			return 0;
		}
	}

	return value;
}

PropertiesPtr
PropertiesI::getPropertiesForPrefix(const string& prefix, bool deleteprefix ) const 
{
	PropertiesPtr result( new PropertiesI );
	map<string, string>::const_iterator p;
	for(p = _properties.begin(); p != _properties.end(); ++p)
	{
		if(prefix.empty() || p->first.compare(0, prefix.size(), prefix) == 0)
		{
			if( deleteprefix )
			{
				std::string key = p->first.substr( prefix.size() );
				if( key.empty() )
					key = "_";
				result->setProperty( key , p->second );
			}
			else
			{
				result->setProperty( p->first , p->second );
			}
		}
	}

	return result;
}

StringSeqPtr PropertiesI::getPropertiesKeys( ) const
{
	StringSeqPtr result( new StringSeq );
	map<string, string>::const_iterator p;
	for(p = _properties.begin(); p != _properties.end(); ++p)
	{
		result->push_back( p->first );
	}
	return result;
}

void
PropertiesI::setProperty(const string& key, const string& value)
{
	if(key.empty())
	{
		return;
	}

	if(!value.empty())
	{
		_properties[key] = value;
	}
	else
	{
		_properties.erase(key);
	}
}

StringSeqPtr
PropertiesI::getCommandLineOptions() const
{
	StringSeqPtr result( new StringSeq );
	result->reserve(_properties.size());
	map<string, string>::const_iterator p;
	for(p = _properties.begin(); p != _properties.end(); ++p)
	{
		result->push_back("--" + p->first + "=" + p->second);
	}
	return result;
}

StringSeqPtr
PropertiesI::parseCommandLineOptions(const string& prefix, const StringSeq& options)
{
	string pfx = prefix;
	// 保证pfx以"."结尾
	if(!pfx.empty() && pfx[pfx.size() - 1] != '.')
	{
		pfx += '.';
	}
	pfx = "--" + pfx;

	StringSeqPtr result( new StringSeq );
	StringSeq::const_iterator i;
	for(i = options.begin(); i != options.end(); i++)
	{
		if( i->find(pfx) == 0)
		{
			std::string opt = opt.substr(2);
			if(i->find('=') == string::npos)
			{
				opt += "=1";
			}
			parseLine( opt );
		}
		else
		{
			result->push_back(*i);
		}
	}
	return result;
}

StringSeqPtr
PropertiesI::parseBTCommandLineOptions(const StringSeq& options)
{
	return parseCommandLineOptions("BT", options);
}

void
PropertiesI::load(const std::string& file)
{
	ifstream in(file.c_str());
	if(!in)
	{
		throw std::runtime_error( "打开文件["+ file + "]出错" );
	}

	std::string line;
	while( std::getline( in, line ))
	{
		parseLine(line);
		line.clear();
	}
}

void PropertiesI::save(const std::string& file) const
{
	ofstream out(file.c_str());
	if(!out)
	{
		throw std::runtime_error( "打开文件["+ file + "]出错" );
	}
	for( std::map<std::string, std::string>::const_iterator it = _properties.begin()
		; it != _properties.end()
		; it ++ )
		out << it->first << "=" << it->second << std::endl;
}

PropertiesPtr
PropertiesI::clone()
{
	return PropertiesPtr( new PropertiesI(this));
}

PropertiesI::PropertiesI(const PropertiesI* p) :
_properties(p->_properties)
{
}

PropertiesI::PropertiesI()
{
	loadConfig();
}

PropertiesI::PropertiesI( const StringSeq& args)
{

	/// 注意，args中的属性将优先于Hazel.Config指定的配置属性值
	StringSeq::const_iterator q = args.begin();
	if(q != args.end())
	{
		// 将第一个字符串当成BT.ProgramName的值
		//
		string name = *q;
		replace(name.begin(), name.end(), '\\', '/');
		setProperty("BT.ProgramName", name);
	}


	/// 先找到"Hazel.Config"
	StringSeq tmp;
	while(q != args.end())
	{
		string s = *q;
		if(s.find("--Hazel.Config") == 0)
		{
			if(s.find('=') == string::npos)
			{
				s += "=1";
			}
			parseLine(s.substr(2));
		}
		else
		{
			tmp.push_back(s);
		}
		++q;
	}

	/// 先找到"Hazel.Config"，载入文件中的配置
	loadConfig();

	// 在分析命令行的配置
	parseBTCommandLineOptions( tmp );
}

void
PropertiesI::parseLine(const string& line)
{
	const string delim = " \t\r\n";
	string s = line;

	// 删除注释
	string::size_type idx = s.find('#');
	if(idx != string::npos)
	{
		s.erase(idx);
	}

	// 删除该行前面的空白符
	idx = s.find_last_not_of(delim);
	if(idx != string::npos && idx + 1 < s.length())
	{
		s.erase(idx + 1);
	}

	// 该行全部是空白符就返回
	string::size_type beg = s.find_first_not_of(delim);
	if(beg == string::npos)
	{
		return;
	}

	// 没有找到"="就返回
	string::size_type end = s.find_first_of(delim + "=", beg);
	if(end == string::npos)
	{
		return;
	}

	string key = s.substr(beg, end - beg);

	// 没有找到"="就返回
	end = s.find('=', end);
	if(end == string::npos)
	{
		return;
	}
	++end;

	// 删除该行紧跟"="后的空白符，注意如果全都是空白符，就不管了
	string value;
	beg = s.find_first_not_of(delim, end);
	if(beg != string::npos)
	{
		end = s.length();
		value = s.substr(beg, end - beg);
	}

	setProperty(key, value);
}

void
PropertiesI::loadConfig()
{
	string value = getProperty("Hazel.Config");

	if(value.empty() || value == "1")
	{
		const char* s = getenv("Hazel_CONFIG");
		if(s && *s != '\0')
		{
			value = s;
		}
	}

	if(!value.empty())
	{
		const string delim = " \t\r\n";
		string::size_type beg = value.find_first_not_of(delim);
		while(beg != string::npos)
		{
			string::size_type end = value.find(",", beg);
			string file;
			if(end == string::npos)
			{
				file = value.substr(beg);
				beg = end;
			}
			else
			{
				file = value.substr(beg, end - beg);
				beg = value.find_first_not_of("," + delim, end);
			}
			load(file);
		}
	}

	setProperty("Hazel.Config", value);
}

_util_end

JOMOO_Export_C _util Properties* ___createProperties()
{
	return new _util PropertiesI();
}

JOMOO_Export_C _util Properties* ___createProperties_args(const StringSeq& args )
{
	return new _util PropertiesI( args );
}

JOMOO_Export_C _util Properties* ___createProperties_vec(int argc, char* argv[])
{
    StringSeq args = argsToStringSeq(argc, argv);
    return ___createProperties_args(args);
}

JOMOO_Export_C void ___freeProperties( _util Properties* ptr )
{
	delete ptr;
}