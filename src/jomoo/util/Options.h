
#ifndef UTIL_OPTIONS_H
#define UTIL_OPTIONS_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Util.h"
#include <string>
#include <vector>
#include <map>
#include <set>

_jomoo_begin

class Options
{
public:

	struct APIError : public std::runtime_error
    {
        APIError(const ::std::string& r) : std::runtime_error(r) {}
    };

    struct BadOpt : public std::runtime_error
    {
        BadOpt(const ::std::string& r) : std::runtime_error(r) {}
    };

	struct BadFindOpt : public std::runtime_error
    {
        BadFindOpt(const ::std::string& r) : std::runtime_error(r) {}
    };

    enum LengthType { ShortOpt, LongOpt }; // { 短选项,长选项 }
	enum RepeatType { Repeat, NoRepeat };// { 重复，不重复 }
    enum ArgType { NeedArg, NoArg }; // {需要，不需要}

    Options();

	/**
	 * 增加一个选项配置。
	 * @param[ in ] shortOpt 短选项名，只能是一个非空白符和"-"的字符
	 * @param[ in ] longOpt 长选项名，不能含有空白字符，不能以"-"开头
	 * @param[ in ] at 是否有参数值,
	 * @param[ in ] dflt 选项缺省值
	 * @param[ in ] rt 是不是可以重复出现
	 * @remarks 注意，短选项名和长选项名不能同时为空，在needArg为true时，dflt必须为空。
	 */
    void addOpt(const ::std::string& shortOpt, const ::std::string& longOpt= "",
                ArgType at = NoArg, ::std::string dflt = "", RepeatType rt= NoRepeat);

	/**
	 * 分析参数
	 * @return 返回不是以"-"开头的参数数组
	 * @remarks 注意，它只能调用一次，并且跳过第一个参数
	 */
    StringSeqPtr parse(int, char*[]);

	/**
	 * 分析参数
	 * @return 返回不是以"-"开头的参数数组
	 * @remarks 注意，它只能调用一次，并且跳过第一个参数
	 */
    StringSeqPtr parse( const StringSeq& );

	/**
	 * 指定的选项是否在选项数组中
	 * @param[ in ] opt 选项名
	 * @return 在选项数组中出现返回true,否则返回false
	 */
    bool isSet(const ::std::string& opt ) const;

	/**
	 * 取得指定的选项的参数值
	 * @param[ in ] opt 选项名
	 * @return 指定的选项的参数值
	 * @remarks 注意，如果该选项是可重复的或没有找到会发生异常APIError和BadFindOpt
	 */
    const ::std::string& optArg(const ::std::string& opt ) const;

	/**
	 * 取得指定的选项的参数值数组
	 * @param[ in ] opt 选项名
	 * @return 指定的选项的参数值数组
	 * @remarks 注意，如果该选项是不可重复的或没有找到会发生异常APIError和BadFindOpt
	 */
    const ::std::vector< ::std::string>& argVec(const ::std::string&) const;

private:

    struct OptionDetails
    {
	LengthType length;
	ArgType arg;
        RepeatType repeat;
    };
    typedef ::std::map< ::std::string, OptionDetails> ValidOpts; // Valid options and their details.
    typedef ::std::map< ::std::string, ::std::string> Opts; // Value of non-repeating options.
    typedef ::std::map< ::std::string, ::std::vector< ::std::string> > ROpts; // Value of repeating options.

    void addValidOpt(const ::std::string&, LengthType, ArgType, const ::std::string&, RepeatType);

	/**
	 * 检验选项是否合法，失败扔出异常，否则返回它在_validOpts中的位置
	 */
    ValidOpts::iterator checkOpt(const ::std::string&, LengthType);

	/**
	 * 添加或设置选项值
	 * @param[ in ] opt 选项名
	 * @param[ in ] val 选项值
	 * @param[ in ] rt 是否可以重复
	 * @remarks 注意，如果选项名不可重复，将覆盖旧值.
	 */
    void setOpt(const ::std::string& opt, const ::std::string& val, RepeatType rt);


    ValidOpts::const_iterator checkOptIsValid(const ::std::string&) const;
    ValidOpts::const_iterator checkOptHasArg(const ::std::string&) const;

    ValidOpts _validOpts;
    Opts _opts;
    ROpts _ropts;

    bool parseCalled;

    Options(const Options&); // Not allowed.
    void operator=(const Options&); // Not allowed.

	/**
	 * 检验一个选项是否合法
	 * @param[ in ] shortOpt 短选项名，只能是一个非空白符和"-"的字符
	 * @param[ in ] longOpt 长选项名，不能含有空白字符，不能以"-"开头
	 * @param[ in ] needArg 是否有参数值,( true 有， false 没有)
	 * @param[ in ] dflt 选项缺省值
	 * @remarks 注意，短选项名和长选项名不能同时为空，在needArg为true时，dflt必须为空。
	 */
    static void checkArgs(const ::std::string& shortOpt, 
		const ::std::string& longOpt, bool needArg, 
		const ::std::string& dflt);
};

_jomoo_end

#endif
