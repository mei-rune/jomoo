
#ifndef _jingxian_tracer_h_
#define _jingxian_tracer_h_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

#include "string.hpp"
#include "buffer.h"

_jingxian_begin

namespace logging
{
    enum TransportWay
    {
        Receive,

        Send,

        Both
    };
}

class tracer 
{
public:
	/**
	 * virtual tracer destructor
	 */
	virtual ~tracer(){};

	/**
	 * 
	 */
    virtual void WriteInboundBuffer(const Buffer& buffer) = 0;
    
	/**
	 *
	 */
	virtual void WriteOutboundBuffer(const Buffer& buffer) = 0;

	/**
	 * debug������־�Ƿ���Լ���־
	 * @return ����true,������false
	 */
	virtual bool isDebugEnabled() const = 0;

	/**
	 * ��¼debug������־
	 * @param[ in ] way ������ķ���
	 * @param[ in ] message ��־����
	 * @param[ in ] file ��־��¼��Դ�ļ���
	 * @param[ in ] line ��־��¼��Դ�ļ��ĵ�ǰ��
	 */
	virtual void debug(logging::TransportWay way, const StringStream& message, const char* file=0, int line=-1);
	
	/**
	 * error������־�Ƿ���Լ���־
	 * @return ����true,������false
	 */
	virtual bool isErrorEnabled() const = 0;

	/**
	 * ��¼error������־
	 * @param[ in ] way ������ķ���
	 * @param[ in ] message ��־����
	 * @param[ in ] file ��־��¼��Դ�ļ���
	 * @param[ in ] line ��־��¼��Դ�ļ��ĵ�ǰ��
	 */
    virtual void error(logging::TransportWay way, const StringStream& message, const char* file=0, int line=-1);
	
	/**
	 * fatal������־�Ƿ���Լ���־
	 * @return ����true,������false
	 */
	virtual bool isFatalEnabled() const = 0;

	/**
	 * ��¼fatal������־
	 * @param[ in ] way ������ķ���
	 * @param[ in ] message ��־����
	 * @param[ in ] file ��־��¼��Դ�ļ���
	 * @param[ in ] line ��־��¼��Դ�ļ��ĵ�ǰ��
	 */
    virtual void fatal(logging::TransportWay way, const StringStream& message, const char* file=0, int line=-1);

	/**
	 * info������־�Ƿ���Լ���־
	 * @return ����true,������false
	 */
	virtual bool isInfoEnabled() const = 0;

	/**
	 * ��¼info������־
	 * @param[ in ] way ������ķ���
	 * @param[ in ] message ��־����
	 * @param[ in ] file ��־��¼��Դ�ļ���
	 * @param[ in ] line ��־��¼��Դ�ļ��ĵ�ǰ��
	 */
    virtual void info(logging::TransportWay way, const StringStream& message, const char* file=0, int line=-1);
	
	/**
	 * warn������־�Ƿ���Լ���־
	 * @return ����true,������false
	 */
	virtual bool isWarnEnabled() const = 0;

	/**
	 * ��¼warn������־
	 * @param[ in ] way ������ķ���
	 * @param[ in ] message ��־����
	 * @param[ in ] file ��־��¼��Դ�ļ���
	 * @param[ in ] line ��־��¼��Դ�ļ��ĵ�ǰ��
	 */
    virtual void warn(logging::TransportWay way, const StringStream& message, const char* file=0, int line=-1);

	
	/**
	 * Trace������־�Ƿ���Լ���־
	 * @return ����true,������false
	 */
	virtual bool isTraceEnabled() const = 0;

	/**
	 * ��¼trace������־
	 * @param[ in ] way ������ķ���
	 * @param[ in ] message ��־����
	 * @param[ in ] file ��־��¼��Դ�ļ���
	 * @param[ in ] line ��־��¼��Դ�ļ��ĵ�ǰ��
	 */
    virtual void trace(logging::TransportWay way, const StringStream& message, const char* file=0, int line=-1);
};

_jingxian_end

#endif // _JOMOO_Log_H_
