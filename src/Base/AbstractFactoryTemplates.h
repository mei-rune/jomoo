
# include "macro/macro_params.hpp"


#pragma warning (push)
#pragma warning (disable : 4005) // macro redefinition

// E.g. <typename T0, typename T1, typename T2, ...>
#define FACTORY_TEMPLATE_PARAMS    JOMOO_MAKE_PARAMS1( FACTORY_NUM_ARGS, typename T)

// E.g. <T0, T1, T2, ...>
#define FACTORY_TEMPLATE_ARGS      JOMOO_MAKE_PARAMS1( FACTORY_NUM_ARGS, T)

// E.g. (T0 a0, T1 a1, T2 a2, ...)
#define FACTORY_FUNCTION_PARAMS    JOMOO_MAKE_PARAMS2( FACTORY_NUM_ARGS, T, a)

// E.g. <a0, a1, a2, ...>
#define FACTORY_FUNCTION_ARGS      JOMOO_MAKE_PARAMS1( FACTORY_NUM_ARGS, a)


#if FACTORY_NUM_ARGS == 0
    #define FACTORY_COMMA
#else
    #define FACTORY_COMMA    ,
#endif

#pragma warning (pop)


_JOMOO_begin

/**
 * Brief 本类是一个虚工厂接口模板，用于定义一个虚工厂接口
 * <p>
 */
template< typename Base  FACTORY_COMMA FACTORY_TEMPLATE_PARAMS >
class Abstract_Factory
{
public:
	virtual ~Abstract_Factory() {};
    virtual Base create( FACTORY_TEMPLATE_ARGS ) = 0;
};

template< typename Base  FACTORY_COMMA FACTORY_TEMPLATE_PARAMS >
class AbstractFactory
{
public:
	virtual ~AbstractFactory() {};
    virtual Base create( FACTORY_TEMPLATE_ARGS ) = 0;
    virtual void release( Base ) = 0;
};

template< typename Base , typename Drive FACTORY_COMMA FACTORY_TEMPLATE_PARAMS >
class Abstract_Factory_T_1 : public Abstract_Factory< Base  FACTORY_COMMA FACTORY_TEMPLATE_ARGS >
{
public:	
	Base create( FACTORY_FUNCTION_PARAMS )
	{
		return Base( new Drive( FACTORY_FUNCTION_ARGS ) );
	}
};




template< typename Base , typename POOL FACTORY_COMMA FACTORY_TEMPLATE_PARAMS >
class Abstract_Factory_T_POOL : public Abstract_Factory< Base  FACTORY_COMMA FACTORY_TEMPLATE_ARGS >
{
public:	
	Base create( FACTORY_FUNCTION_PARAMS )
	{
		return Base( POOL::get().alloc( FACTORY_FUNCTION_ARGS ) );
	}
};


_JOMOO_end
