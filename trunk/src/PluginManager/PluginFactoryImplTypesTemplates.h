

# include "Hazel.Base/macro/macro_params.hpp"
# include "PluginInfo.H"
# include "result_traits.h"
//# include "Hazel.Base/AbstractFactory.H"

#pragma warning (push)
#pragma warning (disable : 4005) // macro redefinition

// E.g. <typename T0, typename T1, typename T2, ...>
#define Hazel_TEMPLATE_PARAMS    Hazel_MAKE_PARAMS1( Hazel_NUM_ARGS, typename T)

// E.g. <T0, T1, T2, ...>
#define Hazel_TEMPLATE_ARGS      Hazel_MAKE_PARAMS1( Hazel_NUM_ARGS, T)

// E.g. (T0 a0, T1 a1, T2 a2, ...)
#define Hazel_FUNCTION_PARAMS    Hazel_MAKE_PARAMS2( Hazel_NUM_ARGS, T, a)

// E.g. <a0, a1, a2, ...>
#define Hazel_FUNCTION_ARGS      Hazel_MAKE_PARAMS1( Hazel_NUM_ARGS, a)


#if Hazel_NUM_ARGS == 0
    #define Hazel_COMMA
#else
    #define Hazel_COMMA    ,
#endif

#pragma warning (pop)

_seal_begin


template< typename Base Hazel_COMMA Hazel_TEMPLATE_PARAMS >
class AbstractFactory<Base ( Hazel_TEMPLATE_ARGS ) >
{
public:
	typedef typename result_traits< Base >::pointer_type result_type;
	virtual ~AbstractFactory() {};
    virtual result_type create( Hazel_FUNCTION_PARAMS ) = 0;
	virtual void release( result_type ) = 0;
};

template < typename R Hazel_COMMA Hazel_TEMPLATE_PARAMS >
class PluginFactoryImplTypes<R ( Hazel_TEMPLATE_ARGS )>
{
public:

	enum
	{
		params_value = Hazel_NUM_ARGS
	};

	typedef R Object;
	
	typedef AbstractFactory< R ( Hazel_TEMPLATE_ARGS ) > Factory;

	template < typename T> class AutoFactory : public Factory
	{
	public:
		virtual R create ( Hazel_FUNCTION_PARAMS ){ return R( new T ( Hazel_FUNCTION_ARGS )); }
		virtual void release ( R o){ delete o; }
	};

	class Info : public PluginInfo
	{
	public:
		Info (IModule& module, const ModuleDescriptor &details, const tstring &tag )
			: PluginInfo (module, details, tag),
			m_factory (0)
		{  }

		~Info (void)
		{
			detach ();
		}

		R	create ( Hazel_FUNCTION_PARAMS )
		{
			return factory ()->create ( Hazel_FUNCTION_ARGS );
		}

		void	release( R r )
		{
			return factory ()->release ( r );
		}

		void	attach (Factory *factory)
		{
			if( m_factory )
				ThrowException3( FacetoryRegisterError, category(), name() ,"注册工厂时，发现它已经注册" );
			m_factory = factory;
		}

		virtual void	detach (void)
		{
			if( is_null( m_factory ) )
				ThrowException3( FacetoryRegisterError, category(), name() ,"注销工厂时，发现它没有注册" );

			//delete m_factory;
			m_factory = 0;
		}
	private:
		Factory*	factory (void) const
		{
			if ( is_null( m_factory ) )
				module ().attach ();

			if ( is_null( m_factory ) )
				noFactory ();

			return get_ptr( m_factory );
		}

		Factory*	m_factory;	
	};
};

_seal_end

