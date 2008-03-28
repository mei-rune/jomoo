
#include "Options.h"
#include <iostream>

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_util_begin

using namespace std;

Options::Options()
: parseCalled(false)
{
}

void
Options::checkArgs(const string& shortOpt, const string& longOpt, bool needArg, const string& dflt)
{
	if(shortOpt.empty() && longOpt.empty())
	{
		throw APIError("短选项名和长选项名不能同时为空");
	}

	if(!shortOpt.empty())
	{
		if(shortOpt.size() != 1)
		{
			string err = "`";
			err += shortOpt;
			err += "': 短选项名长度不能大于1";
			throw APIError(err);
		}
		if(shortOpt.find_first_of(" \t\n\r\f\v") != string::npos)
		{
			string err = "`";
			err += shortOpt;
			err += "': 短选项名不能是空白符";
			throw APIError(err);
		}
		if(shortOpt[0] == '-')
		{
			string err = "`";
			err += shortOpt;
			err += "': 短选项名不能是 `-'";
			throw APIError(err);
		}
	}

	if(!longOpt.empty())
	{
		if(longOpt.find_first_of(" \t\n\r\f\v") != string::npos)
		{
			string err = "`";
			err += longOpt;
			err += "': 长选项名不能包含空白符";
			throw APIError(err);
		}
		if(longOpt[0] == '-')
		{
			string err = "`";
			err += longOpt;
			err += "': 长选项名不能以`-'开头";
			throw APIError(err);
		}
	}

	if(!needArg && !dflt.empty())
	{
		throw APIError("是否有参数与缺省值发生冲突!");
	}
}

void
Options::addOpt(const string& shortOpt, const string& longOpt, ArgType at, string dflt, RepeatType rt)
{    
	if(parseCalled)
	{
		throw APIError("不能在调用 parse() 后调用 addOpt");
	}

	checkArgs(shortOpt, longOpt, at == NeedArg, dflt);

	addValidOpt(shortOpt, ShortOpt, at, dflt, rt);
	addValidOpt(longOpt, LongOpt, at, dflt, rt);
}
StringSeqPtr Options::parse( const StringSeq& argv)
{
	if(parseCalled)
	{
		throw APIError("一个实例只能调用 parse() 一次");
	}
	parseCalled = true;

	set<string> seenOpts; // To catch repeated non-repeatable options.

	StringSeqPtr result( new StringSeq );

	size_t argc  = argv.size();
	size_t i;
	for(i = 1; i < argv.size(); ++i)
	{
		if(strcmp(argv[i].c_str(), "-") == 0 || strcmp(argv[i].c_str(), "--") == 0)
		{
			++i;
			break; // 单个"-" 和 "--" 表示选项结束.
		}

		string opt;
		ValidOpts::iterator pos;
		bool argDone = false;

		if(strncmp(argv[i].c_str(), "--", 2) == 0)
		{
			//
			// 长选项. 如果它有参数,可能用一个"="分隔或一个单独的参数，如
			// "--name value" 与 "--name=value"是一样的.
			//
			const char *p = argv[i].c_str() + 2;
			while(*p != '=' && *p != '\0')
			{
				++p;
			}

			// 取得选项名opt, 去除了"--"
			if(*p == '=')
			{
				opt.assign(argv[i].c_str() + 2, p - (argv[i].c_str() + 2));
			}
			else
			{
				opt = argv[i].c_str() + 2;
			}

			pos = checkOpt(opt, LongOpt);

			// 保存选项
			if(*p == '=')
			{
				if(pos->second.arg == NoArg)
				{
					string err = "--";
					err += opt;
					err.push_back('=');
					err += p + 1;
					err += "': 选项没有参数";
					throw BadOpt(err);
				}
				setOpt(opt, p + 1, pos->second.repeat);
				argDone = true;
			}

			// 判断是否有重复的选项
			set<string>::iterator seenPos = seenOpts.find(opt);
			if(seenPos != seenOpts.end())
			{
				ValidOpts::const_iterator validPos = _validOpts.find(opt);
				if(validPos != _validOpts.end() && validPos->second.repeat == NoRepeat)
				{
					string err = "`--";
					err += opt + ":' 选项不能重复";
					throw BadOpt(err);
				}
			}
			seenOpts.insert(seenPos, opt);
		}
		else if(*(argv[i].c_str()) == '-')
		{
			//
			// 短选项
			//
			const char *p = argv[i].c_str();

			// 如果该选项没有参数值时，最后一个字符作为选项名。
			char c;
			while((c = *++p) != '\0')
			{
				opt.clear();
				opt.push_back(c);
				pos = checkOpt(opt, ShortOpt);
				if(pos->second.arg == NeedArg && *(p + 1) != '\0')
				{
					// 取得选项参数值
					string optArg;
					while(*++p != '\0')
					{
						optArg.push_back(*p);
					}
					--p;
					setOpt(opt, optArg, pos->second.repeat);
					argDone = true;
				}
			}

			// 判断是否有重复的选项
			set<string>::iterator seenPos = seenOpts.find(opt);
			if(seenPos != seenOpts.end())
			{
				ValidOpts::const_iterator validPos = _validOpts.find(opt);
				if(validPos != _validOpts.end() && validPos->second.repeat == NoRepeat)
				{
					string err = "`-";
					err += opt + ":' 选项不能重复";
					throw BadOpt(err);
				}
			}
			seenOpts.insert(seenPos, opt);
		}
		else
		{
			result->push_back(argv[i]); // 不是预期的选项
			argDone = true;
		}


		// 如果没有找到参数
		if(!argDone)
		{
			if(pos->second.arg == NeedArg) // Need an argument that is separated by whitespace.
			{
				if(i == argc - 1)
				{
					string err = "`-";
					if(opt.size() != 1)
					{
						err += "-";
					}
					err += opt;
					err += "' 选项需要一个参数";
					throw BadOpt(err);
				}
				setOpt(opt, argv[++i], pos->second.repeat);
			}
			else
			{
				setOpt(opt, "1", pos->second.repeat);
			}
		}
	}

	while(i < argc)
	{
		result->push_back(argv[i++]);
	}

	return result;

}

StringSeqPtr Options::parse(int argc, char* argv[])
{
	if(parseCalled)
	{
		throw APIError("一个实例只能调用 parse() 一次");
	}
	parseCalled = true;

	set<string> seenOpts; // To catch repeated non-repeatable options.

	StringSeqPtr result( new StringSeq );

	int i;
	for(i = 1; i < argc; ++i)
	{
		if(strcmp(argv[i], "-") == 0 || strcmp(argv[i], "--") == 0)
		{
			++i;
			break; // 单个"-" 和 "--" 表示选项结束.
		}

		string opt;
		ValidOpts::iterator pos;
		bool argDone = false;

		if(strncmp(argv[i], "--", 2) == 0)
		{
			//
			// 长选项. 如果它有参数,可能用一个"="分隔或一个单独的参数，如
			// "--name value" 与 "--name=value"是一样的.
			//
			const char *p = argv[i] + 2;
			while(*p != '=' && *p != '\0')
			{
				++p;
			}

			// 取得选项名opt, 去除了"--"
			if(*p == '=')
			{
				opt.assign(argv[i] + 2, p - (argv[i] + 2));
			}
			else
			{
				opt = argv[i] + 2;
			}

			pos = checkOpt(opt, LongOpt);

			// 保存选项
			if(*p == '=')
			{
				if(pos->second.arg == NoArg)
				{
					string err = "--";
					err += opt;
					err.push_back('=');
					err += p + 1;
					err += "': 选项没有参数";
					throw BadOpt(err);
				}
				setOpt(opt, p + 1, pos->second.repeat);
				argDone = true;
			}

			// 判断是否有重复的选项
			set<string>::iterator seenPos = seenOpts.find(opt);
			if(seenPos != seenOpts.end())
			{
				ValidOpts::const_iterator validPos = _validOpts.find(opt);
				if(validPos != _validOpts.end() && validPos->second.repeat == NoRepeat)
				{
					string err = "`--";
					err += opt + ":' 选项不能重复";
					throw BadOpt(err);
				}
			}
			seenOpts.insert(seenPos, opt);
		}
		else if(*argv[i] == '-')
		{
			//
			// 短选项
			//
			const char *p = argv[i];

			// 如果该选项没有参数值时，最后一个字符作为选项名。
			char c;
			while((c = *++p) != '\0')
			{
				opt.clear();
				opt.push_back(c);
				pos = checkOpt(opt, ShortOpt);
				if(pos->second.arg == NeedArg && *(p + 1) != '\0')
				{
					// 取得选项参数值
					string optArg;
					while(*++p != '\0')
					{
						optArg.push_back(*p);
					}
					--p;
					setOpt(opt, optArg, pos->second.repeat);
					argDone = true;
				}
			}

			// 判断是否有重复的选项
			set<string>::iterator seenPos = seenOpts.find(opt);
			if(seenPos != seenOpts.end())
			{
				ValidOpts::const_iterator validPos = _validOpts.find(opt);
				if(validPos != _validOpts.end() && validPos->second.repeat == NoRepeat)
				{
					string err = "`-";
					err += opt + ":' 选项不能重复";
					throw BadOpt(err);
				}
			}
			seenOpts.insert(seenPos, opt);
		}
		else
		{
			result->push_back(argv[i]); // 不是预期的选项
			argDone = true;
		}


		// 如果没有找到参数
		if(!argDone)
		{
			if(pos->second.arg == NeedArg) // Need an argument that is separated by whitespace.
			{
				if(i == argc - 1)
				{
					string err = "`-";
					if(opt.size() != 1)
					{
						err += "-";
					}
					err += opt;
					err += "' 选项需要一个参数";
					throw BadOpt(err);
				}
				setOpt(opt, argv[++i], pos->second.repeat);
			}
			else
			{
				setOpt(opt, "1", pos->second.repeat);
			}
		}
	}

	while(i < argc)
	{
		result->push_back(argv[i++]);
	}

	return result;
}

bool
Options::isSet(const string& opt) const
{

	if(!parseCalled)
	{
		throw APIError("不能在调用 parse()之前调用本函数据");
	}

	ValidOpts::const_iterator pos = checkOptIsValid(opt);
	return pos->second.repeat == NoRepeat ? _opts.find(opt) != _opts.end() : _ropts.find(opt) != _ropts.end();
}

const std::string&
Options::optArg(const string& opt) const
{

	if(!parseCalled)
	{
		throw APIError("不能在调用 parse()之前调用本函数据");
	}

	ValidOpts::const_iterator pos = checkOptHasArg(opt);

	if(pos->second.repeat == Repeat)
	{
		string err = "`-";
		if(pos->second.length == LongOpt)
		{
			err.push_back('-');
		}
		err += opt;
		err += "': 是一个可重复的选项 -- 请使用 argVec()";
		throw APIError(err);
	}

	map<string, string>::const_iterator p = _opts.find(opt);
	if( p == _opts.end() )
	{
		string err = "`-";
		if(pos->second.length == LongOpt)
		{
			err.push_back('-');
		}
		err += opt;
		err += "': 没有找到";
		throw BadFindOpt( err );
	}
	return p->second;
}

const std::vector<string>&
Options::argVec(const string& opt) const
{

	if(!parseCalled)
	{
		throw APIError("不能在调用 parse()之前调用本函数据");
	}

	ValidOpts::const_iterator pos = checkOptHasArg(opt);

	if(pos->second.repeat == NoRepeat)
	{
		string err = "`-";
		if(pos->second.length == LongOpt)
		{
			err.push_back('-');
		}
		err += opt + "': 是一个不可重复的选项 -- 请使用 optArg()";
		throw APIError(err);
	}

	map<string, vector<string> >::const_iterator p = _ropts.find(opt);
	if( p == _ropts.end() )
	{
		string err = "`-";
		if(pos->second.length == LongOpt)
		{
			err.push_back('-');
		}
		err += opt;
		err += "': 没有找到";
		throw BadFindOpt( err );
	}
	return p->second;
}

void
Options::addValidOpt(const string& opt, LengthType lt, ArgType at, const string& dflt, RepeatType rt)
{
	if(opt.empty())
	{
		return;
	}

	ValidOpts::iterator pos = _validOpts.find(opt);
	if(pos != _validOpts.end())
	{
		string err = "`";
		err += opt;
		err += "': 有同样的选项名";
		throw APIError(err);
	}

	OptionDetails od;
	od.length = lt;
	od.arg = at;
	od.repeat = rt;

	_validOpts.insert(pos, ValidOpts::value_type(opt, od));

	// 添加缺省值
	if(at == NeedArg && !dflt.empty())
	{
		setOpt(opt, dflt, rt);
	}
}

Options::ValidOpts::iterator
Options::checkOpt(const string& opt, LengthType lt)
{
	ValidOpts::iterator pos = _validOpts.find(opt);
	if(pos == _validOpts.end())
	{
		string err = "错误选项: `-";
		if(lt == LongOpt)
		{
			err.push_back('-');
		}
		err += opt;
		err.push_back('\'');
		throw BadOpt(err);
	}

	return pos;
}

void
Options::setOpt(const string& opt, const string& val, RepeatType rt)
{
	if(rt == Repeat)
	{
		ROpts::iterator pos = _ropts.find(opt);
		if(pos != _ropts.end())
		{
			pos->second.push_back(val);
		}
		else
		{
			vector<string> vec;
			vec.push_back(val);
			_ropts.insert(pos, ROpts::value_type(opt, vec));
		}
	}
	else
	{
		_opts[opt] = val;
	}
}

Options::ValidOpts::const_iterator
Options::checkOptIsValid(const string& opt) const
{
	ValidOpts::const_iterator pos = _validOpts.find(opt);
	if(pos == _validOpts.end())
	{
		string err = "`";
		err += opt;
		err += "': 无效选项";
		throw APIError(err);
	}
	return pos;
}

Options::ValidOpts::const_iterator
Options::checkOptHasArg(const string& opt) const
{
	ValidOpts::const_iterator pos = checkOptIsValid(opt);
	if(pos->second.arg == NoArg)
	{
		string err = "`-";
		if(pos->second.length == LongOpt)
		{
			err.push_back('-');
		}
		err += opt;
		err += "': 选项没有参数据";
		throw APIError(err);
	}
	return pos;
}

_util_end