
# include "PluginFactoryImpl.H"
# include "Hazel.Base/macro/macro_params.hpp"
# include "MapUniqueIterator.h"
# include <map>



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

//////////////////////////////////////////////////////////////////////
template < typename R Hazel_COMMA Hazel_TEMPLATE_PARAMS >
class PluginFactory< R ( Hazel_TEMPLATE_ARGS ) >
{
public:
	typedef typename PluginFactoryImpl<R ( Hazel_TEMPLATE_ARGS )> factory_type;
	typedef typename factory_type::Types Types;
	typedef IPluginManager::factory_type base_factory_type;
	typedef IPluginManager::factory_ptr_type base_factory_ptr_type;
	typedef typename factory_type::Iterator Iterator;
	typedef typename factory_type::ptr_type ptr_type;

	typedef typename Types::Factory AbstractFactory;

	PluginFactory ( IPluginManager& manager , const tstring &category , const tstring& version )
		: manager_( manager )
		, pfactory_( dynamicCast< factory_type >( manager_.findFactory( FactoryKey( typename factory_type::params_value,category ) ) ) )
	{
		if( is_null( pfactory_ ) )
		{
			base_factory_ptr_type ptr( new factory_type( manager_, category ,version ) );
			pfactory_ = dynamicCast< factory_type >( ptr );
			manager_.addFactory( FactoryKey( typename factory_type::params_value,category ) , ptr );
		}
		else
		{
			if( pfactory_->version() != version )
				ThrowException2( PluginInterfaceVersonException, category,version );
		}
	}

	~PluginFactory ()
	{
		manager_.removeFactory( FactoryKey( typename factory_type::params_value,pfactory_->category() ) );
	}

	const tstring &	category (void) const
	{
		return pfactory_->category();
	}

	Iterator begin()const
	{
		return pfactory_->begin();
	}
	
	Iterator end()const
	{
		return pfactory_->end();
	}

	virtual R		create ( Hazel_FUNCTION_PARAMS )const
	{
		if( is_null( pfactory_->default_factory() ) )
			return NULL;
		return  pfactory_->default_factory() ->create ( Hazel_FUNCTION_ARGS );
	}

	virtual R		create (const tstring &name Hazel_COMMA Hazel_FUNCTION_PARAMS )const
	{
		Iterator pos (pfactory_->locate (name));
		if( pos == end () )
			ThrowException3( PluginInfoNoExistError, name , category(),"没有找到" );
		return  (*pos)->create ( Hazel_FUNCTION_ARGS );
	}
	
	virtual void		release ( R r )const
	{
		if( is_null( pfactory_->default_factory() ) )
			return ;
		return  pfactory_->default_factory() ->release ( r );
	}

	virtual void		release (const tstring &name , R r )const
	{
		Iterator pos (pfactory_->locate (name));
		if( pos == end () )
			ThrowException3( PluginInfoNoExistError, name , category(),"没有找到" );
		return  (*pos)->release ( r );
	}

	void	installFactory ( IModuleDef& def , const tstring& name,
		typename AbstractFactory *factory )
	{
		pfactory_->installFactory( def, name , factory );
	}

	void	uninstallFactory ( IModuleDef& def , const tstring& name )
	{
		pfactory_->uninstallFactory( def, name );
	}

	const tstring& toString() const
	{
		return pfactory_->toString();
	}

private:
	IPluginManager& manager_;
	ptr_type pfactory_;
};

_seal_end
