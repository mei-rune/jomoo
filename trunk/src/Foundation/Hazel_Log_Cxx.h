

/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - ��q�Шr �q�Шr		                   BT_Log_Cxx.h,v 1.0 2005/04/22 10:34:54
 *  �u�������� �q�q �Шr
 * ���������| �t------
 * -------------------------------------------------------------------------------
 */

#ifndef _BT_Log_Cxx_H_
#define _BT_Log_Cxx_H_


#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#ifndef NOLOG4CXX

#include <list>
#include "Logger.h"
#include "log4cxx\logger.h"
#include "log4cxx\ndc.h"

_boe_begin


/**
 * @Brief BT_Log ��־�ӿ�
 * ����BT����־�ӿڣ�ÿһ���������־����������̳У�ÿһ����Ҫ����־�Ķ����Եõ�һ�������Ľӣ�
 * �����Ƽ�ֱ��ʹ��������һ��Ԥ����õĺ꣬��ʹ�ú�
 */
class BT_Log_Cxx :
	public BOE_Log_Impl
{
public:

	BT_Log_Cxx( const tchar* name );

	~BT_Log_Cxx(void);
	
	/**
	 * assert ���
	 * @param[ in ] assertion �����Ƿ�Ϊ��
	 * @param[ in ] message ��־����
	 * @param[ in ] file ��־��¼��Դ�ļ���
	 * @param[ in ] line ��־��¼��Դ�ļ��ĵ�ǰ��
	 */
	void assertLog(bool assertion, const StringStream& msg, const char* file, int line );

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
	void fatal(const StringStream& message, const char* file, int line );

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
	void error(const StringStream& message, const char* file, int line );

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
	void info(const StringStream& message, const char* file, int line );

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
	void debug(const StringStream& message, const char* file, int line );

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
	void warn(const StringStream& message, const char* file, int line );

	/**
	 * level������־�Ƿ���Լ���־
	 * @return ����true,������false
	 */
	bool isEnabledFor(const LevelPtr& level) const;

	/**
	 * Trace������־�Ƿ���Լ���־
	 * @return ����true,������false
	 */
	bool isTraceEnabled() const;

	/**
	 * ��¼warn������־
	 * @param[ in ] message ��־����
	 * @param[ in ] file ��־��¼��Դ�ļ���
	 * @param[ in ] line ��־��¼��Դ�ļ��ĵ�ǰ��
	 */
	void trace(const StringStream& message, const char* file, int line );

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

	/**
	 * ���ڶ����NDC,������Ļ����̵߳Ĳ�һ��������ֻ��ʹ�������־�������
	 * ������־�д�ӡNDC
	 * ��һ��NDC
	 * @param[ in ] str �����ַ���
	 */
	void pushNDC( const tchar* str );

	/**
	 * ȡ��һ��NDC
	 */
	void popNDC( );

	/**
	 * ���NDC
	 */
	void clearNDC();

	void createLog_i();

	LevelPtr Log4CxxLeveltoLevelPtr( int level ) const;

	int LevelPtrtoLog4CxxLevel( LevelPtr level ) const;

private:

	mutable LevelPtr level_;
	log4cxx:: LoggerPtr rootLogger_;

	std::list< tstring > m_NDCs_;
};

class BT_Log_NDC_Cxx : public BOE_Log_NDC_Base
{
public:


	void pushNDC( const tchar* str );
	void popNDC( );

};

BOE_Log_NDC_Base* make_BT_NDC_Cxx( );
BOE_Log_Impl* make_BT_Log_Cxx( const tchar* name );

int init_BT_Log_Cxx(  );
void shutdown_BT_Log_Cxx(  );




_boe_end


#endif // #ifndef NOLOG4CXX

#endif // _BT_Log_Cxx_H_
