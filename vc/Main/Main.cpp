// Main.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "BOE\IO\IO.h"
#include "BOE\StdLogger.H"

//class StdLogger : public BOE_Log_Impl
//{
//public:
//
//	StdLogger()
//	{
//	 l = Trace;
//	}
//
//	void assertLog(bool assertion, const StringStream& message, const char* file=0, int line=-1)
//	{
//		std::cout << message.str() << std::endl;
//		assert( assertion );
//	}
//
//	bool isFatalEnabled() const
//	{
//		return true;
//	}
//
//	void fatal(const StringStream& message, const char* file=0, int line=-1)
//	{
//		std::cout << message.str() << std::endl;
//	}
//
//
//	bool isErrorEnabled() const
//	{
//		return true;
//	}
//
//	void error(const StringStream& message, const char* file=0, int line=-1)
//	{
//		std::cout << message.str() << std::endl;
//	}
//
//
//	bool isInfoEnabled() const
//	{
//		return true;
//	}
//
//	void info(const StringStream& message, const char* file=NULL, int line=-1)
//	{
//		std::cout << message.str() << std::endl;
//	}
//
//	bool isDebugEnabled() const
//	{
//		return true;
//	}
//
//	void debug(const StringStream& message, const char* file=0, int line=-1)
//	{
//		std::cout << message.str() << std::endl;
//	}
//
//	bool isWarnEnabled() const
//	{
//		return true;
//	}
//
//	void warn(const StringStream& message, const char* file=NULL, int line=-1)
//	{
//		std::cout << message.str() << std::endl;
//	}
//
//	bool isTraceEnabled() const
//	{
//		return true;
//	}
//
//	void trace(const StringStream& message, const char* file=NULL, int line=-1)
//	{
//		std::cout << message.str() << std::endl;
//	}
//
//	bool isEnabledFor(const LevelPtr& level) const
//	{
//		return true;
//	}
//
//	void log(const LevelPtr& level, const StringStream& message,
//		const char* file=0, int line=-1)
//	{
//		std::cout << message.str() << std::endl;
//	}
//
//	const LevelPtr& getLevel() const
//	{
//		return l;
//	}
//
//	void pushNDC( const tchar* str )
//	{
//	}
//
//	void popNDC( )
//	{
//	}
//
//	virtual void clearNDC()
//	{
//	}
//private:
//	LevelPtr l;
//};
class Application
{
public:

	Application()
	{
		if( application_ != 0 )
			throw( std::runtime_error( "初始化Application失败,已经有一个实例了" ) );

		application_ = this;
	//	init_BT_Log_Cxx( );
	}

	~Application()
	{
		application_ = 0;
	//	shutdown_BT_Log_Cxx(  );
	}

	int main( int argc, _TCHAR* argv[] )
	{
		communicator_ = initializeCommunicator( );
		if( communicator_.get() ==0 )
			return -1;
		communicator_->setLogger( new _boe StdLogger );
		_util PropertiesPtr config = createProperties( argc , argv );
		try
		{
		if( config->getProperty( "BOE.Config").empty() )
			config->load( "BOE.Conf" );
		}catch( ... )
		{
		}
		if( communicator_->open( config ) != 0 )
			return -1;
		stop_ = false;
		run();
		return 0;
	}

	void shutdown()
	{
		stop_ = true;
	}

	void run( )
	{
		while( !stop_ )
			communicator_->run( 1000 );
	}

	BOE_Communicator_Ptr communicator()
	{
		return communicator_;
	}

	static Application* application_;
private:
	bool stop_;
	_io BOE_Communicator_Ptr communicator_;
};

Application* Application::application_ = 0;

void shutdown(int)
{
	if( Application::application_ == 0)
		return;
	Application::application_->shutdown();
}

int _tmain(int argc, _TCHAR* argv[])
{
	Application app;
	return app.main( argc, argv );
}

