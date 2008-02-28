

/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - ��q�Шr �q�Шr		              BT_Log_CPlus.h,v 1.0 2005/04/22 10:34:54
 *  �u�������� �q�q �Шr
 * ���������| �t------
 * -------------------------------------------------------------------------------
 */

#ifndef _BT_Log_CPlus_H_
#define _BT_Log_CPlus_H_


#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#ifndef _NO_LOGCPLUS_

#include "BOE_Log_Base.h"
#include "log4\log4.hpp"

_bt_begin


/**
 * @Brief BT_Log ��־�ӿ�
 * ����BT����־�ӿڣ�ÿһ���������־����������̳У�ÿһ����Ҫ����־�Ķ����Եõ�һ�������Ľӣ�
 * �����Ƽ�ֱ��ʹ��������һ��Ԥ����õĺ꣬��ʹ�ú�
 */
class BT_Log_CPlus :
	public BOE_Log_Impl
{
public:

	BT_Log_CPlus(void);

	~BT_Log_CPlus(void);
	
	/**
	 * assert ���
	 * @param[ in ] assertion �����Ƿ�Ϊ��
	 * @param[ in ] message ��־����
	 * @param[ in ] file ��־��¼��Դ�ļ���
	 * @param[ in ] line ��־��¼��Դ�ļ��ĵ�ǰ��
	 */
	void assertLog(bool assertion, const StringStream& msg, const char* file=0, int line=-1);

	/**
	 * fatal������־�Ƿ���Լ���־
	 * @return ����true,������false
	 */
	bool isFatalEnabled() const;
	
	/**
	 * ��¼fatal������־
	 * @param[ in ] message ��־����
	 * @param[ in ] file ��־��¼��Դ�ļ���
	 * @param[ in ] line ��־��¼��Դ�ļ��ĵ�ǰ��
	 */
	void fatal(const StringStream& message, const char* file=0, int line=-1);

	/**
	 * error������־�Ƿ���Լ���־
	 * @return ����true,������false
	 */
	bool isErrorEnabled() const;

	/**
	 * ��¼error������־
	 * @param[ in ] message ��־����
	 * @param[ in ] file ��־��¼��Դ�ļ���
	 * @param[ in ] line ��־��¼��Դ�ļ��ĵ�ǰ��
	 */
	void error(const StringStream& message, const char* file=0, int line=-1);

	/**
	 * info������־�Ƿ���Լ���־
	 * @return ����true,������false
	 */
	bool isInfoEnabled() const;

	/**
	 * ��¼info������־
	 * @param[ in ] message ��־����
	 * @param[ in ] file ��־��¼��Դ�ļ���
	 * @param[ in ] line ��־��¼��Դ�ļ��ĵ�ǰ��
	 */
	void info(const StringStream& message, const char* file=NULL, int line=-1);

	/**
	 * debug������־�Ƿ���Լ���־
	 * @return ����true,������false
	 */
	bool isDebugEnabled() const;

	/**
	 * ��¼debug������־
	 * @param[ in ] message ��־����
	 * @param[ in ] file ��־��¼��Դ�ļ���
	 * @param[ in ] line ��־��¼��Դ�ļ��ĵ�ǰ��
	 */
	void debug(const StringStream& message, const char* file=0, int line=-1);

	/**
	 * warn������־�Ƿ���Լ���־
	 * @return ����true,������false
	 */
	bool isWarnEnabled() const;

	/**
	 * ��¼warn������־
	 * @param[ in ] message ��־����
	 * @param[ in ] file ��־��¼��Դ�ļ���
	 * @param[ in ] line ��־��¼��Դ�ļ��ĵ�ǰ��
	 */
	void warn(const StringStream& message, const char* file=NULL, int line=-1);

	/**
	 * level������־�Ƿ���Լ���־
	 * @return ����true,������false
	 */
	bool isEnabledFor(const LevelPtr& level) const;

	/**
	 * ��¼level������־
	 * @param[ in ] message ��־����
	 * @param[ in ] file ��־��¼��Դ�ļ���
	 * @param[ in ] line ��־��¼��Դ�ļ��ĵ�ǰ��
	 */
	void log(const LevelPtr& level, const StringStream& message,
		const char* file=0, int line=-1);

	/**
	 * ȡ�õ�ǰ����־�ļ���
	 * @return ��־�ļ���
	 */
	const LevelPtr& getLevel() const;


	LevelPtr Log4CxxLeveltoLevelPtr( int level ) const;

	int LevelPtrtoLog4CxxLevel( LevelPtr level ) const;

private:

	mutable log4cplus::LogLevel level_;
	log4cplus:: Logger rootLogger_;
};

class BT_Log_NDC_CPlus : public BOE_Log_NDC_Base
{
public:

	BT_Log_NDC_CPlus( );


	~BT_Log_NDC_CPlus() ;

	void pushNDC( const tchar* str );
	void popNDC( );

};

BOE_Log_NDC_Base* make_BT_NDC_CPlus( const tchar* name );


int init_BT_Log_CPlus(  );
int shutdown_BT_Log_CPlus( name );
BOE_Log_Impl* make_BT_Log_CPlus( const tchar* name );


_bt_end



#endif // _NO_LOGCPLUS_

#endif // _BT_Log_CPlus_H_

