
#ifdef __sun
#    define _POSIX_PTHREAD_SEMANTICS
#endif

#include "CtrlCHandler.h"

#ifndef _WIN32
#   include <signal.h>
#else
#   include <windows.h>
#endif

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_jomoo_begin

using namespace std;

static CtrlCHandlerCallback _callback = 0;
static CtrlCHandler* _handler = 0;

void CtrlCHandler::setCallback(CtrlCHandlerCallback callback)
{
    _callback = callback;
}

CtrlCHandlerCallback 
CtrlCHandler::getCallback() const
{
    return _callback;
}

CtrlCHandler* CtrlCHandler::get( )
{
	return _handler;
}

#ifdef _WIN32

static BOOL WINAPI handlerRoutine(DWORD dwCtrlType)
{
    CtrlCHandlerCallback callback = _handler->getCallback();
    if(callback != 0)
    {
	callback(dwCtrlType);
    }
    return TRUE;
}


CtrlCHandler::CtrlCHandler(CtrlCHandlerCallback callback)
{
    if(_handler != 0)
    {
	throw CtrlCHandlerException( "巳经有一个CtrlCHandler实例了" );
    }
    else
    {
	_callback = callback;
	_handler = this;
	SetConsoleCtrlHandler(handlerRoutine, TRUE);
    }
}

CtrlCHandler::~CtrlCHandler()
{
    SetConsoleCtrlHandler(handlerRoutine, FALSE);
    {
	_handler = 0;
    }
}

#else

extern "C" 
{

static void* 
sigwaitThread(void*)
{
    sigset_t ctrlCLikeSignals;
    sigemptyset(&ctrlCLikeSignals);
    sigaddset(&ctrlCLikeSignals, SIGHUP);
    sigaddset(&ctrlCLikeSignals, SIGINT);
    sigaddset(&ctrlCLikeSignals, SIGTERM);

    //
    // Run until I'm cancelled (in sigwait())
    //
    for(;;)
    {
	int signal = 0;
	int rc = sigwait(&ctrlCLikeSignals, &signal);
#if defined(__APPLE__)
	//
	// WORKAROUND: sigwait is not a cancelation point on MacOS X. To cancel this thread, the 
	// destructor cancels the thread and send a signal to the thread to unblock sigwait, then
	// we explicitly test for cancellation.
	//
	pthread_testcancel();
#endif
	//
	// Some sigwait() implementations incorrectly return EINTR
	// when interrupted by an unblocked caught signal
	//
	if(rc == EINTR)
	{
	    continue;
	}
	assert(rc == 0);
	
	rc = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, 0);
	assert(rc == 0);
	
	CtrlCHandlerCallback callback = _handler->getCallback();
	
	if(callback != 0)
	{
	    callback(signal);
	}

	rc = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, 0);
	assert(rc == 0);
    }
    return 0;
}
}

static pthread_t _tid;

CtrlCHandler::CtrlCHandler(CtrlCHandlerCallback callback)
{
    if(_handler != 0)
    {
	throw CtrlCHandlerException(__FILE__, __LINE__);
    }
    else
    {
	_callback = callback;
	_handler = this;
	lock.release();
	
	// We block these CTRL+C like signals in the main thread,
	// and by default all other threads will inherit this signal
	// disposition.
	
	sigset_t ctrlCLikeSignals;
	sigemptyset(&ctrlCLikeSignals);
	sigaddset(&ctrlCLikeSignals, SIGHUP);
	sigaddset(&ctrlCLikeSignals, SIGINT);
	sigaddset(&ctrlCLikeSignals, SIGTERM);
	int rc = pthread_sigmask(SIG_BLOCK, &ctrlCLikeSignals, 0);
	assert(rc == 0);

	// Joinable thread
	rc = pthread_create(&_tid, 0, sigwaitThread, 0);
	assert(rc == 0);
    }
}

CtrlCHandler::~CtrlCHandler()
{
    int rc = pthread_cancel(_tid);
    assert(rc == 0);
#if defined(__APPLE__)
    //
    // WORKAROUND: sigwait isn't a cancellation point on MacOS X, see
    // comment in sigwaitThread
    //
    rc = pthread_kill(_tid, SIGTERM);
    assert(rc == 0);
#endif
    void* status = 0;
    rc = pthread_join(_tid, &status);
    assert(rc == 0);
#if !defined(__APPLE__)
    assert(status == PTHREAD_CANCELED);
#endif
    {
	_handler = 0;
    }
}

#endif

_jomoo_end