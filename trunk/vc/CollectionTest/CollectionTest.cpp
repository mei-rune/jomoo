// CollectionTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define TEST 1
#include "Hazel.Base/Collections/Test.CPP"



//template< typename Base  >
//class AbstractFactory
//{
//public:
//	virtual ~AbstractFactory() {};
//    virtual Base create( ) = 0;
//    virtual void release( Base ) = 0;
//};
//template< >
//class AbstractFactory< void >
//{
//public:
//	virtual ~AbstractFactory() {};
//};
//
//template< typename Base , typename T1 >
//class AbstractFactory< Base, T1 >
//{
//public:
//	virtual ~AbstractFactory() {};
//    virtual Base create( T1 ) = 0;
//    virtual void release( Base ) = 0;
//};
//
//template< typename Base , typename T1, typename T2 >
//class AbstractFactory< Base, T1 ,T2 >
//{
//public:
//	virtual ~AbstractFactory() {};
//    virtual Base create( T1 ,T2 ) = 0;
//    virtual void release( Base ) = 0;
//};
//
//template< typename Base , typename T1, typename T2, typename T3 >
//class AbstractFactory
//{
//public:
//	virtual ~AbstractFactory() {};
//    virtual Base create( T1 ,T2,T3 ) = 0;
//    virtual void release( Base ) = 0;
//};



int _tmain(int argc, _TCHAR* argv[])
{
	Test();
	return 0;
}

