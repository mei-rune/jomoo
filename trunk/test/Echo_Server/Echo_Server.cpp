// Echo_Server.cpp : ���� DLL Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "../BT_Server_Handler.H"


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}



class Echo : public BOE_Server
{
public:
	Echo( _io Instance_IO& io )
		: instance_( io )
	{
		toString_ = "Echo";
	}

	int open( _util PropertiesPtr config )
	{
		if( isNone( config ) )
			BT_LOG_ERROR_RETURN( getLogger(), toString() << "> ����Ϊ��" , -1 );

		toString_ = config->getProperty( "ServerName" );
		if( toString_.empty() )
			toString_ = "Echo";
		ServerAddr_ = config->getProperty( "ServerAddress" );
		if( ServerAddr_.empty() )
			BT_LOG_ERROR_RETURN( getLogger(), toString() << "> ���ò���ȷ��û�з�������ַ��" , -1);
		BOE_Endpoint_Ptr endpoint = instance_.create( ServerAddr_ );
		if( isNone( endpoint ) )
			BT_LOG_ERROR_RETURN( getLogger(), toString() 
			<< BT_TEXT("> �����˽ڵ�") 
			<< ServerAddr_ 
			<< BT_TEXT("ʧ�ܡ�" ), -1);
		acceptor_ = endpoint->acceptor();
		if( isNone( acceptor_ ) )
			BT_LOG_ERROR_RETURN( getLogger(), toString() 
			<< BT_TEXT("> ����������") 
			<< ServerAddr_ 
			<< BT_TEXT("ʧ�ܡ�" ), -1);
		
        if( ! acceptor_->accept( handler , 0 ) )
			BT_LOG_ERROR_RETURN( getLogger(), toString() 
			<< BT_TEXT("> ��������ʧ�ܡ�" ), -1);
		return 0;
	}
	
	void close( )
	{
		if( isNone( acceptor_ ) )
		{
			BT_LOG_ERROR( getLogger(), toString() 
			<< BT_TEXT("> û����������" ) );
			return ;
		}
		acceptor_->cancel();
	}
	const tstring& toString() const
	{
		return toString_;
	}

	Instance_IO::LoggerPtr getLogger()
	{
		return instance_.getLogger();
	}

private:
	tstring toString_;
	tstring ServerAddr_;
	_io Instance_IO& instance_; 
	Accept_Handler handler;
	BOE_Acceptor_Ptr acceptor_;
	tstring ServerAddr_;
};

DEFINE_SERVER( Echo );
