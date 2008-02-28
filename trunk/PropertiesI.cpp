
#include <PropertiesI.h>
#include <fstream>
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
				std::string key = p->first->substr( prefix.size() );
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
	// ��֤pfx��"."��β
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
			result->push_back(opt);
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
		SyscallException ex(__FILE__, __LINE__);
		ex.error = getSystemErrno();
		throw ex;
	}

	std::string line;
	while( std::getline( in, line ))
	{
		parseLine(line);
		line.clear();
	}
}

PropertiesPtr
PropertiesI::clone()
{
	return new PropertiesI(this);
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

	/// ע�⣬args�е����Խ�������BT.Configָ������������ֵ
	StringSeq::const_iterator q = args.begin();
	if(q != args.end())
	{
		// ����һ���ַ�������BT.ProgramName��ֵ
		//
		string name = *q;
		replace(name.begin(), name.end(), '\\', '/');
		setProperty("BT.ProgramName", name);
	}


	/// ���ҵ�"BT.Config"
	StringSeq tmp;
	while(q != args.end())
	{
		string s = *q;
		if(s.find("--BT.Config") == 0)
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
	args = tmp;

	/// ���ҵ�"BT.Config"�������ļ��е�����
	loadConfig();

	// �ڷ��������е�����
	args = parseBTCommandLineOptions(args);
}

void
PropertiesI::parseLine(const string& line)
{
	const string delim = " \t\r\n";
	string s = line;

	// ɾ��ע��
	string::size_type idx = s.find('#');
	if(idx != string::npos)
	{
		s.erase(idx);
	}

	// ɾ������ǰ��Ŀհ׷�
	idx = s.find_last_not_of(delim);
	if(idx != string::npos && idx + 1 < s.length())
	{
		s.erase(idx + 1);
	}

	// ����ȫ���ǿհ׷��ͷ���
	string::size_type beg = s.find_first_not_of(delim);
	if(beg == string::npos)
	{
		return;
	}

	// û���ҵ�"="�ͷ���
	string::size_type end = s.find_first_of(delim + "=", beg);
	if(end == string::npos)
	{
		return;
	}

	string key = s.substr(beg, end - beg);

	// û���ҵ�"="�ͷ���
	end = s.find('=', end);
	if(end == string::npos)
	{
		return;
	}
	++end;

	// ɾ�����н���"="��Ŀհ׷���ע�����ȫ���ǿհ׷����Ͳ�����
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
	string value = getProperty("BT.Config");

	if(value.empty() || value == "1")
	{
		const char* s = getenv("BT_CONFIG");
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

	setProperty("BT.Config", value);
}

BTNM_Export_C PropertiesPtr createProperties()
{
	return new PropertiesI();
}

BTNM_Export_C PropertiesPtr createProperties(StringSeq& args )
{
	return new PropertiesI( args );
}

BTNM_Export_C PropertiesPtr createProperties(int& argc, char* argv[])
{
    StringSeq args = argsToStringSeq(argc, argv);
    PropertiesPtr properties = createProperties(args);
    stringSeqToArgs(args, argc, argv);
    return properties;
}