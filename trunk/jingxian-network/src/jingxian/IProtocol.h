
#ifndef _IProtocol_H_
#define _IProtocol_H_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "exception.hpp"

_jingxian_begin

class ProtocolContext;

class IProtocol
{
public:

	virtual ~IProtocol(){}

    /**
     * ��ָ����ʱ�����û���յ��κ�����
     * 
     * @param[ in ] context �Ự��������
	 */
    void onTimeout(ProtocolContext& context);

    /**
     * ���Ự�����󣬱����á�
     * 
     * @param[ in ] context �Ự��������
	 */
    void onConnection(ProtocolContext& context);

    /**
     * ���Ự�رպ󣬱����á�
     * 
     * @param[ in ] context �Ự��������
	 */
    void onDisconnection(ProtocolContext& context, Exception& reason);

    /**
     * �����µ���Ϣ����ʱ�������á�
     * 
     * @param[ in ] context �Ự��������
     * @param[ in ] buffer �����µ�����Ϣ�Ļ�����
	 */
    void onReceived(ProtocolContext& context, Buffer& buffer);

    /**
     * �����´�������ȡ���ݵĻ�����
     * 
     * @param[ in ] lastBuffer ��һ��������ȡ���ݵĻ�����</param>
     * @param[ in ] buffer �����µ�����Ϣ�Ļ�����
	 */
	Buffer createBuffer(Buffer& lastBuffer);

	/**
	* ȡ�õ�ַ������
	*/
	virtual const tstring& toString() const = 0;
};

inline tostream& operator<<( tostream& target, const IProtocol& protocol )
{
	target << protocol.toString();
	return target;
}

_jingxian_end

#endif // _IProtocol_H_