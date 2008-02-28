

#ifndef _Abstract_Factory_H_
#define _Abstract_Factory_H_

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */



/**
 * Brief 本类是一个虚工厂接口模板，用于定义一个虚工厂接口
 * <p>
 */
template< typename Base >
class Abstract_Factory
{
public:
	virtual ~Abstract_Factory() {};
    virtual Base* create_object( ) = 0;
};

template < typename T >
class __ALLO
{
public:
	T* new_( )
	{
		return new T();
	}

	template< typename T1 >
		T* new_( T1 t1 )
	{
		return new T( t1 );
	}

	template< typename T1,typename T2 >
		T* new_( T1 t1 ,T2 t2 )
	{
		return new T( t1 ,t2 );
	}

	template< typename T1,typename T2,typename T3 >
		T* new_( T1 t1 ,T2 t2,T3 t3 )
	{
		return new T( t1 ,t2 ,t3 );
	}
	
	template< typename T1,typename T2,typename T3,typename T4 >
		T* new_( T1 t1 ,T2 t2,T3 t3,T4 t4 )
	{
		return new T( t1 ,t2 ,t3 ,t4 );
	}
};

template< typename Base
		, typename Drive
		, typename ALLO = __ALLO< Drive >
		>
class Abstract_Factory_T : public Abstract_Factory< Base >
{
public:
	Base* create_object( )
	{
		return __allo.new_();
	}
private:
	ALLO __allo;
};

template< typename Base
		, typename Drive
		, typename T1
		, typename ALLO = __ALLO< Drive >
		>
class Abstract_Factory_T_1 : public Abstract_Factory< Base >
{
public:
	Abstract_Factory_T_1( T1 t1 )
		: t1_( t1 )
	{
	}
	
	Base* create_object( )
	{
		return __allo.new_( t1_ );
	}
private:
	T1 t1_;

	ALLO __allo;
};

template< typename Base
		, typename Drive
		, typename T1
		, typename T2
		, typename ALLO = __ALLO< Drive >
		>
class Abstract_Factory_T_2 : public Abstract_Factory< Base >
{
public:
	Abstract_Factory_T_2( T1 t1 ,T2 t2 )
		: t1_( t1 )
		, t2_( t2 )
	{
	}

	Base* create_object( )
	{
		return __allo.new_( t1_ ,t2_ );
	}
private:
	T1 t1_;
	T2 t2_;

	ALLO __allo;
};

template< typename Base
		, typename Drive
		, typename T1
		, typename T2
		, typename T3
		, typename ALLO = __ALLO< Drive >
		>
class Abstract_Factory_T_3 : public Abstract_Factory< Base >
{
public:
	Abstract_Factory_T_3( T1 t1 ,T2 t2,T3 t3 )
		: t1_( t1 )
		, t2_( t2 )
		, t3_( t3 )
	{
	}

	Base* create_object( )
	{
		return __allo.new_( t1_ ,t2_ ,t3_ );
	}
private:
	T1 t1_;
	T2 t2_;
	T3 t3_;

	ALLO __allo;
};


#endif
