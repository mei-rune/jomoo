

#ifndef THREAD_CLOSURE_H
#define THREAD_CLOSURE_H


#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"


_thread_begin

template<typename F>
class thread_closure_0
{
public:

	thread_closure_0(pool_ptr pool, const F& f, const char* nm = 0)
		: _pool( pool )
		, _function( f )
		, _name( (0 == nm) ? "" : nm )
	{
	}

	static int start_routine( void* c )
	{
            thread_closure_0 *self = static_cast<thread_closure_0*>(c);
            try
			{
                self->_function();
            }
			catch ( ... )
			{
                JOMOO_DELETE( self->_pool , self );
                throw;
            }
                JOMOO_DELETE( self->_pool , self );
            return 0;
     }

	const tstring& name() const
	{
		return _name;
	}
private:
	F _function;
	pool_ptr _pool;
	tstring _name;
};

template<typename F, typename P>
class thread_closure_1
{
public:

	thread_closure_1(pool_ptr pool, const F& f, const P& x, const char* nm = 0)
		: _pool( pool )
		, _function( f )
		, _name( (0 == nm) ? "" : nm )
		, arg1( x )
	{
	}

	static int start_routine( void* c )
	{
            thread_closure_1 *self = static_cast<thread_closure_1*>(c);
            try
			{
                self->_function( arg1 );
            }
			catch ( ... )
			{
                JOMOO_DELETE( self->_pool , self );
                throw;
            }
                JOMOO_DELETE( self->_pool , self );
            return 0;
    }

	const tstring& name() const
	{
		return _name;
	}
private:
	F _function;
	pool_ptr _pool;
	tstring _name;
	P arg1;
};

template<typename F, typename P1, typename P2>
class thread_closure_2
{
public:

	thread_closure_2(pool_ptr pool, const F& f, const P1& x1, const P2& x2, const char* nm = 0)
		: _pool( pool )
		, _function( f )
		, _name( (0 == nm) ? "" : nm )
		, arg1( x1 )
		, arg2( x2 )
	{
	}

	static int start_routine( void* c )
	{
            thread_closure_2 *self = static_cast<thread_closure_2*>(c);
            try
			{
                self->_function( arg1, arg2 );
            }
			catch ( ... )
			{
                JOMOO_DELETE( self->_pool , self );
                throw;
            }
                JOMOO_DELETE( self->_pool , self );
            return 0;
    }

	const tstring& name() const
	{
		return _name;
	}
private:
	F _function;
	pool_ptr _pool;
	tstring _name;
	P1 arg1;
	P2 arg2;
};

template<typename F, typename P1, typename P2, typename P3>
class thread_closure_3
{
public:

	thread_closure_3(pool_ptr pool, const F& f, const P1& x1, const P2& x2, const P3& x3, const char* nm = 0)
		: _pool( pool )
		, _function( f )
		, _name( (0 == nm) ? "" : nm )
		, arg1( x1 )
		, arg2( x2 )
	{
	}

	static int start_routine( void* c )
	{
            thread_closure_3 *self = static_cast<thread_closure_3*>(c);
            try
			{
                self->_function( arg1, arg2, arg3 );
            }
			catch ( ... )
			{
                JOMOO_DELETE( self->_pool , self );
                throw;
            }
                JOMOO_DELETE( self->_pool , self );
            return 0;
    }

	const tstring& name() const
	{
		return _name;
	}
private:
	F _function;
	pool_ptr _pool;
	tstring _name;
	P1 arg1;
	P2 arg2;
	P3 arg3;
};

_thread_end

#endif // THREAD_CLOSURE_H