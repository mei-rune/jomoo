
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

    enum LengthType { ShortOpt, LongOpt }; // { ��ѡ��,��ѡ�� }
	enum RepeatType { Repeat, NoRepeat };// { �ظ������ظ� }
    enum ArgType { NeedArg, NoArg }; // {��Ҫ������Ҫ}

    Options();

	/**
	 * ����һ��ѡ�����á�
	 * @param[ in ] shortOpt ��ѡ������ֻ����һ���ǿհ׷���"-"���ַ�
	 * @param[ in ] longOpt ��ѡ���������ܺ��пհ��ַ���������"-"��ͷ
	 * @param[ in ] at �Ƿ��в���ֵ,
	 * @param[ in ] dflt ѡ��ȱʡֵ
	 * @param[ in ] rt �ǲ��ǿ����ظ�����
	 * @remarks ע�⣬��ѡ�����ͳ�ѡ��������ͬʱΪ�գ���needArgΪtrueʱ��dflt����Ϊ�ա�
	 */
    void addOpt(const ::std::string& shortOpt, const ::std::string& longOpt= "",
                ArgType at = NoArg, ::std::string dflt = "", RepeatType rt= NoRepeat);

	/**
	 * ��������
	 * @return ���ز�����"-"��ͷ�Ĳ�������
	 * @remarks ע�⣬��ֻ�ܵ���һ�Σ�����������һ������
	 */
    StringSeqPtr parse(int, char*[]);

	/**
	 * ��������
	 * @return ���ز�����"-"��ͷ�Ĳ�������
	 * @remarks ע�⣬��ֻ�ܵ���һ�Σ�����������һ������
	 */
    StringSeqPtr parse( const StringSeq& );

	/**
	 * ָ����ѡ���Ƿ���ѡ��������
	 * @param[ in ] opt ѡ����
	 * @return ��ѡ�������г��ַ���true,���򷵻�false
	 */
    bool isSet(const ::std::string& opt ) const;

	/**
	 * ȡ��ָ����ѡ��Ĳ���ֵ
	 * @param[ in ] opt ѡ����
	 * @return ָ����ѡ��Ĳ���ֵ
	 * @remarks ע�⣬�����ѡ���ǿ��ظ��Ļ�û���ҵ��ᷢ���쳣APIError��BadFindOpt
	 */
    const ::std::string& optArg(const ::std::string& opt ) const;

	/**
	 * ȡ��ָ����ѡ��Ĳ���ֵ����
	 * @param[ in ] opt ѡ����
	 * @return ָ����ѡ��Ĳ���ֵ����
	 * @remarks ע�⣬�����ѡ���ǲ����ظ��Ļ�û���ҵ��ᷢ���쳣APIError��BadFindOpt
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
	 * ����ѡ���Ƿ�Ϸ���ʧ���ӳ��쳣�����򷵻�����_validOpts�е�λ��
	 */
    ValidOpts::iterator checkOpt(const ::std::string&, LengthType);

	/**
	 * ��ӻ�����ѡ��ֵ
	 * @param[ in ] opt ѡ����
	 * @param[ in ] val ѡ��ֵ
	 * @param[ in ] rt �Ƿ�����ظ�
	 * @remarks ע�⣬���ѡ���������ظ��������Ǿ�ֵ.
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
	 * ����һ��ѡ���Ƿ�Ϸ�
	 * @param[ in ] shortOpt ��ѡ������ֻ����һ���ǿհ׷���"-"���ַ�
	 * @param[ in ] longOpt ��ѡ���������ܺ��пհ��ַ���������"-"��ͷ
	 * @param[ in ] needArg �Ƿ��в���ֵ,( true �У� false û��)
	 * @param[ in ] dflt ѡ��ȱʡֵ
	 * @remarks ע�⣬��ѡ�����ͳ�ѡ��������ͬʱΪ�գ���needArgΪtrueʱ��dflt����Ϊ�ա�
	 */
    static void checkArgs(const ::std::string& shortOpt, 
		const ::std::string& longOpt, bool needArg, 
		const ::std::string& dflt);
};

_jomoo_end

#endif
