
#include "Options.h"
#include <iostream>

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_jomoo_begin

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
		throw APIError("��ѡ�����ͳ�ѡ��������ͬʱΪ��");
	}

	if(!shortOpt.empty())
	{
		if(shortOpt.size() != 1)
		{
			tstring err = _T("`");
			err += shortOpt;
			err += _T("': ��ѡ�������Ȳ��ܴ���1");
			throw APIError(err);
		}
		if(shortOpt.find_first_of(_T(" \t\n\r\f\v")) != string::npos)
		{
			tstring err = _T("`");
			err += shortOpt;
			err += _T("': ��ѡ���������ǿհ׷�");
			throw APIError(err);
		}
		if(shortOpt[0] == _T('-'))
		{
			tstring err = _T("`");
			err += shortOpt;
			err += _T("': ��ѡ���������� `-'");
			throw APIError(err);
		}
	}

	if(!longOpt.empty())
	{
		if(longOpt.find_first_of(" \t\n\r\f\v") != string::npos)
		{
			tstring err = _T("`");
			err += longOpt;
			err += _T("': ��ѡ�������ܰ����հ׷�");
			throw APIError(err);
		}
		if(longOpt[0] == _T('-'))
		{
			tstring err = _T("`");
			err += longOpt;
			err += _T("': ��ѡ����������`-'��ͷ");
			throw APIError(err);
		}
	}

	if(!needArg && !dflt.empty())
	{
		throw APIError("�Ƿ��в�����ȱʡֵ������ͻ!");
	}
}

void
Options::addOpt(const string& shortOpt, const string& longOpt, ArgType at, string dflt, RepeatType rt)
{    
	if(parseCalled)
	{
		throw APIError("�����ڵ��� parse() ����� addOpt");
	}

	checkArgs(shortOpt, longOpt, at == NeedArg, dflt);

	addValidOpt(shortOpt, ShortOpt, at, dflt, rt);
	addValidOpt(longOpt, LongOpt, at, dflt, rt);
}
StringSeqPtr Options::parse( const StringSeq& argv)
{
	if(parseCalled)
	{
		throw APIError("һ��ʵ��ֻ�ܵ��� parse() һ��");
	}
	parseCalled = true;

	set<tstring> seenOpts; // To catch repeated non-repeatable options.

	StringSeqPtr result( new StringSeq );

	size_t argc  = argv.size();
	size_t i;
	for(i = 1; i < argv.size(); ++i)
	{
		if( string_traits<tstring::value_type>::strcmp(argv[i].c_str(), _T("-")) == 0 
			|| string_traits<tstring::value_type>::strcmp(argv[i].c_str(), _T("--")) == 0)
		{
			++i;
			break; // ����"-" �� "--" ��ʾѡ�����.
		}

		tstring opt;
		ValidOpts::iterator pos;
		bool argDone = false;

		if( string_traits<tstring::value_type>::strncmp(argv[i].c_str(), _T("--"), 2) == 0)
		{
			//
			// ��ѡ��. ������в���,������һ��"="�ָ���һ�������Ĳ�������
			// "--name value" �� "--name=value"��һ����.
			//
			const tchar *p = argv[i].c_str() + 2;
			while(*p != _T('=') && *p != _T(_T('\0')))
			{
				++p;
			}

			// ȡ��ѡ����opt, ȥ����"--"
			if(*p == _T('='))
			{
				opt.assign(argv[i].c_str() + 2, p - (argv[i].c_str() + 2));
			}
			else
			{
				opt = argv[i].c_str() + 2;
			}

			pos = checkOpt(opt, LongOpt);

			// ����ѡ��
			if(*p == _T('='))
			{
				if(pos->second.arg == NoArg)
				{
					tstring err = _T("--" );
					err += opt;
					err.push_back('=');
					err += p + 1;
					err += _T("': ѡ��û�в���");
					throw BadOpt(err);
				}
				setOpt(opt, p + 1, pos->second.repeat);
				argDone = true;
			}

			// �ж��Ƿ����ظ���ѡ��
			set<string>::iterator seenPos = seenOpts.find(opt);
			if(seenPos != seenOpts.end())
			{
				ValidOpts::const_iterator validPos = _validOpts.find(opt);
				if(validPos != _validOpts.end() && validPos->second.repeat == NoRepeat)
				{
					tstring err = _T("`--");
					err += opt + _T(":' ѡ����ظ�");
					throw BadOpt(err);
				}
			}
			seenOpts.insert(seenPos, opt);
		}
		else if(*(argv[i].c_str()) == _T(_T('-')))
		{
			//
			// ��ѡ��
			//
			const char *p = argv[i].c_str();

			// �����ѡ��û�в���ֵʱ�����һ���ַ���Ϊѡ������
			char c;
			while((c = *++p) !=_T( _T('\0')) )
			{
				opt.clear();
				opt.push_back(c);
				pos = checkOpt(opt, ShortOpt);
				if(pos->second.arg == NeedArg && *(p + 1) != _T(_T('\0')))
				{
					// ȡ��ѡ�����ֵ
					string optArg;
					while(*++p != _T(_T('\0')))
					{
						optArg.push_back(*p);
					}
					--p;
					setOpt(opt, optArg, pos->second.repeat);
					argDone = true;
				}
			}

			// �ж��Ƿ����ظ���ѡ��
			set<string>::iterator seenPos = seenOpts.find(opt);
			if(seenPos != seenOpts.end())
			{
				ValidOpts::const_iterator validPos = _validOpts.find(opt);
				if(validPos != _validOpts.end() && validPos->second.repeat == NoRepeat)
				{
					tstring err = _T("`-");
					err += opt + _T(":' ѡ����ظ�" );
					throw BadOpt(err);
				}
			}
			seenOpts.insert(seenPos, opt);
		}
		else
		{
			result->push_back(argv[i]); // ����Ԥ�ڵ�ѡ��
			argDone = true;
		}


		// ���û���ҵ�����
		if(!argDone)
		{
			if(pos->second.arg == NeedArg) // Need an argument that is separated by whitespace.
			{
				if(i == argc - 1)
				{
					tstring err = _T("`-");
					if(opt.size() != 1)
					{
						err += _T("-");
					}
					err += opt;
					err += _T("' ѡ����Ҫһ������");
					throw BadOpt(err);
				}
				setOpt(opt, argv[++i], pos->second.repeat);
			}
			else
			{
				setOpt(opt, _T("1"), pos->second.repeat);
			}
		}
	}

	while(i < argc)
	{
		result->push_back(argv[i++]);
	}

	return result;

}

StringSeqPtr Options::parse(int argc, tchar* argv[])
{
	if(parseCalled)
	{
		throw APIError("һ��ʵ��ֻ�ܵ��� parse() һ��");
	}
	parseCalled = true;

	set<string> seenOpts; // To catch repeated non-repeatable options.

	StringSeqPtr result( new StringSeq );

	int i;
	for(i = 1; i < argc; ++i)
	{
		if(strcmp(argv[i], _T("-")) == 0 || strcmp(argv[i], _T("--")) == 0)
		{
			++i;
			break; // ����"-" �� "--" ��ʾѡ�����.
		}

		string opt;
		ValidOpts::iterator pos;
		bool argDone = false;

		if(strncmp(argv[i], _T("--"), 2) == 0)
		{
			//
			// ��ѡ��. ������в���,������һ��"="�ָ���һ�������Ĳ�������
			// "--name value" �� "--name=value"��һ����.
			//
			const tchar *p = argv[i] + 2;
			while(*p != _T('=') && *p != _T(_T('\0')))
			{
				++p;
			}

			// ȡ��ѡ����opt, ȥ����"--"
			if(*p == _T('='))
			{
				opt.assign(argv[i] + 2, p - (argv[i] + 2));
			}
			else
			{
				opt = argv[i] + 2;
			}

			pos = checkOpt(opt, LongOpt);

			// ����ѡ��
			if(*p == _T('='))
			{
				if(pos->second.arg == NoArg)
				{
					tstring err = _T("--");
					err += opt;
					err.push_back(_T('='));
					err += p + 1;
					err += _T("': ѡ��û�в���");
					throw BadOpt(err);
				}
				setOpt(opt, p + 1, pos->second.repeat);
				argDone = true;
			}

			// �ж��Ƿ����ظ���ѡ��
			set<string>::iterator seenPos = seenOpts.find(opt);
			if(seenPos != seenOpts.end())
			{
				ValidOpts::const_iterator validPos = _validOpts.find(opt);
				if(validPos != _validOpts.end() && validPos->second.repeat == NoRepeat)
				{
					tstring err = _T("`--");
					err += opt + _T(":' ѡ����ظ�");
					throw BadOpt(err);
				}
			}
			seenOpts.insert(seenPos, opt);
		}
		else if(*argv[i] == _T('-'))
		{
			//
			// ��ѡ��
			//
			const char *p = argv[i];

			// �����ѡ��û�в���ֵʱ�����һ���ַ���Ϊѡ������
			char c;
			while((c = *++p) != _T('\0'))
			{
				opt.clear();
				opt.push_back(c);
				pos = checkOpt(opt, ShortOpt);
				if(pos->second.arg == NeedArg && *(p + 1) != _T('\0'))
				{
					// ȡ��ѡ�����ֵ
					string optArg;
					while(*++p != _T('\0'))
					{
						optArg.push_back(*p);
					}
					--p;
					setOpt(opt, optArg, pos->second.repeat);
					argDone = true;
				}
			}

			// �ж��Ƿ����ظ���ѡ��
			set<string>::iterator seenPos = seenOpts.find(opt);
			if(seenPos != seenOpts.end())
			{
				ValidOpts::const_iterator validPos = _validOpts.find(opt);
				if(validPos != _validOpts.end() && validPos->second.repeat == NoRepeat)
				{
					tstring err = _T("`-");
					err += opt + _T(":' ѡ����ظ�" );
					throw BadOpt(err);
				}
			}
			seenOpts.insert(seenPos, opt);
		}
		else
		{
			result->push_back(argv[i]); // ����Ԥ�ڵ�ѡ��
			argDone = true;
		}


		// ���û���ҵ�����
		if(!argDone)
		{
			if(pos->second.arg == NeedArg) // Need an argument that is separated by whitespace.
			{
				if(i == argc - 1)
				{
					tstring err = _T("`-");
					if(opt.size() != 1)
					{
						err += "-";
					}
					err += opt;
					err += _T("' ѡ����Ҫһ������");
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
Options::isSet(const tstring& opt) const
{

	if(!parseCalled)
	{
		throw APIError("�����ڵ��� parse()֮ǰ���ñ�������");
	}

	ValidOpts::const_iterator pos = checkOptIsValid(opt);
	return pos->second.repeat == NoRepeat ? _opts.find(opt) != _opts.end() : _ropts.find(opt) != _ropts.end();
}

const tstring&
Options::optArg(const tstring& opt) const
{

	if(!parseCalled)
	{
		throw APIError("�����ڵ��� parse()֮ǰ���ñ�������");
	}

	ValidOpts::const_iterator pos = checkOptHasArg(opt);

	if(pos->second.repeat == Repeat)
	{
		tstring err = _T("`-");
		if(pos->second.length == LongOpt)
		{
			err.push_back(_T('-'));
		}
		err += opt;
		err += _T("': ��һ�����ظ���ѡ�� -- ��ʹ�� argVec()");
		throw APIError(err);
	}

	map<string, string>::const_iterator p = _opts.find(opt);
	if( p == _opts.end() )
	{
		tstring err = _T("`-");
		if(pos->second.length == LongOpt)
		{
			err.push_back(_T('-'));
		}
		err += opt;
		err += _T("': û���ҵ�");
		throw BadFindOpt( err );
	}
	return p->second;
}

const std::vector<string>&
Options::argVec(const string& opt) const
{

	if(!parseCalled)
	{
		throw APIError("�����ڵ��� parse()֮ǰ���ñ�������");
	}

	ValidOpts::const_iterator pos = checkOptHasArg(opt);

	if(pos->second.repeat == NoRepeat)
	{
		tstring err = _T("`-");
		if(pos->second.length == LongOpt)
		{
			err.push_back(_T('-'));
		}
		err += opt + _T("': ��һ�������ظ���ѡ�� -- ��ʹ�� optArg()");
		throw APIError(err);
	}

	map<string, vector<string> >::const_iterator p = _ropts.find(opt);
	if( p == _ropts.end() )
	{
		tstring err = _T("`-");
		if(pos->second.length == LongOpt)
		{
			err.push_back(_T('-'));
		}
		err += opt;
		err += _T("': û���ҵ�");
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
		tstring err = _T("`");
		err += opt;
		err += _T("': ��ͬ����ѡ����");
		throw APIError(err);
	}

	OptionDetails od;
	od.length = lt;
	od.arg = at;
	od.repeat = rt;

	_validOpts.insert(pos, ValidOpts::value_type(opt, od));

	// ���ȱʡֵ
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
		tstring err = _T("����ѡ��: `-");
		if(lt == LongOpt)
		{
			err.push_back(_T('-'));
		}
		err += opt;
		err.push_back(_T('\''));
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
		tstring err = _T("`");
		err += opt;
		err += _T("': ��Чѡ��");
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
		tstring err = _T("`-");
		if(pos->second.length == LongOpt)
		{
			err.push_back(_T('-'));
		}
		err += opt;
		err += _T("': ѡ��û�в�����");
		throw APIError(err);
	}
	return pos;
}

_jomoo_end