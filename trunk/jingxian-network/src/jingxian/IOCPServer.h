
#ifndef _IOCPServer_H_
#define _IOCPServer_H_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include <hash_map>
# include "jingxian/string/string.hpp"
# include "jingxian/IReactorCore.h"
# include "jingxian/networks/proactor.h"


_jingxian_begin

class IOCPServer : public IReactorCore
{
public:
	IOCPServer(void);

	virtual ~IOCPServer(void);


    /**
	 * ����һ��������
	 */
    virtual IConnector* connectWith(const tchar* endPoint);
	
    /**
	 * ����һ����������
	 */
    virtual IAcceptor* listenWith(const tchar* endPoint
			, IProtocolFactory* protocolFactory);

	
    /**
     * ��ִ�з������͵��̵߳ȴ�����,�Ժ�ִ��
     *
     * @param[ in ] run ִ�з���
	 */
    virtual void send( IRunnable* runnable );

	/**
	 * ��ʼ����ֱ������Interrupt�ŷ���
	 */
	virtual void runForever();

	/**
	 * ֹͣ����
	 */
	virtual void interrupt();

	/**
	 * ������󶨵����˿�
	 */
	virtual bool bind(HANDLE systemHandler);

	/**
	* ȡ�õ�ַ������
	*/
	virtual const tstring& toString() const;

private:

	proactor _proactor;

	stdext::hash_map<tstring, IConnectorFactory > _connectorFactory;

	stdext::hash_map<tstring, IAcceptorFactory > _acceptorFactory;
};

_jingxian_end

#endif //_IOCPServer_H_