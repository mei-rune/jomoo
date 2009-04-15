
#ifndef _protocol_h_
#define _protocol_h_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "ProtocolContext.h"
# include "exception.hpp"

_jomoo_networks_begin

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
};

_jomoo_networks_end

#endif // _protocol_h_