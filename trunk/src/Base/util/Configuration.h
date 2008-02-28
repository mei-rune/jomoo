#ifndef __Configuration_h__
#define __Configuration_h__

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_Util.h"
# include "../Exception.HPP"
# include "Hazel_Export.H"

_util_begin


class ConfigurationException: public _hazel Exception
{
public:

	ConfigurationException( const   char* const         srcFile
		, size_t        srcLine
		, const tstring& key )
		: _hazel Exception( srcFile, srcLine ,BT_TEXT( "取配置属性值失败!" ) )
		, key_( key )
	{
	}

	const tstring& key() const
	{
		return key_;
	}

	virtual Exception* clone()
	{
		return new ConfigurationException( *this );
	}

	virtual void rethrow()
	{
		Raise( *this );
	}

	virtual void print(std::ostream& Target ) const
	{
		Target << BT_TEXT( "ConfigurationException" )
			<< what()
			<< std::endl;
		dumpFile( Target );
		Target << BT_TEXT( "\t[ key=" )
			<< key()
			<< BT_TEXT( " ]" );
	}
private:
	tstring key_;
};

class NodeException: public _hazel Exception
{
public:

	NodeException( const   char* const         srcFile
		, size_t        srcLine
		, const tstring& key )
		: _hazel Exception( srcFile, srcLine ,BT_TEXT( "取配置节点值失败!" ) )
		, key_( key )
	{
	}

	const tstring& key() const
	{
		return key_;
	}

	virtual Exception* clone()
	{
		return new NodeException( *this );
	}

	virtual void rethrow()
	{
		Raise( *this );
	}

	virtual void print(std::ostream& Target ) const
	{
		Target << BT_TEXT( "NodeException" )
			<< what()
			<< std::endl;
		dumpFile( Target );
		Target << BT_TEXT( "\t[ key=" )
			<< key()
			<< BT_TEXT( " ]" );
	}
private:
	tstring key_;
};


class IConfiguration;
class IValue;

class INode
{
public:
	enum Type
	{
		  Node
		, Element
	};

	virtual ~INode(){}
	virtual const tstring& name() const = 0;
	
	virtual Type type() const = 0;
	virtual const IConfiguration& node() const = 0;
	virtual const IValue& value() const = 0;
	
	virtual const INode& parent() const = 0;
	virtual const INode& next() const = 0;

	virtual INode* clone() const = 0;
};


class IValue
{
public:
	virtual ~IValue(){}
	virtual const tstring& name() const = 0;
	virtual const tstring& value() const = 0;
	virtual const tstring& toString() const = 0;
	virtual IValue* clone() const = 0;
};

class IConfiguration
{
public:

	//typedef IEnumerator< const INode* > Enumerator; 
	typedef counter_ptr< IConfiguration > ptr_type;

	virtual ~IConfiguration(){}

	/**
	* 读节点
	* @param[ in ] key 节点名
	* @return 成功返回节点，失败扔出NodeException异常
	*/
	virtual const INode& getNode(const ::std::string& key) const = 0;

	/**
	* 读属性的数量
	* @return 成功返回属性的数量
	*/
	virtual size_t size( ) const = 0;

	virtual const INode* getFirstNode()const = 0;

	/**
	* 生成一个本实例的拷贝
	* @return 成功返回一个本实例的拷贝，失败返回null
	*/
	virtual IConfiguration* clone() const = 0;

	/**
	 */
	virtual const tstring& toString() const = 0;
};

typedef  IConfiguration::ptr_type ConfigurationPtr;

_util_end

Hazel_Export_C _util IConfiguration* ___createConfiguration();
Hazel_Export_C _util IConfiguration* ___createConfiguration_args( int, char*[] );
Hazel_Export_C _util IConfiguration* ___createConfiguration_vec( const _util StringSeq&);
Hazel_Export_C void ___freeConfiguration( _util IConfiguration* );

_util_begin

inline ConfigurationPtr createConfiguration()
{
	return ConfigurationPtr( ___createConfiguration(),___freeConfiguration );
}

inline ConfigurationPtr createConfiguration( const StringSeq& args )
{
	return ConfigurationPtr( ___createConfiguration_vec( args ),___freeConfiguration );
}

inline ConfigurationPtr createConfiguration(int argc , char* argv[] )
{
	return ConfigurationPtr( ___createConfiguration_args( argc, argv ),___freeConfiguration );
}

inline _util StringSeq argsToStringSeq(int argc, char* argv[])
{
	_util StringSeq result;
	for(int i = 0; i < argc; i++)
	{
		result.push_back(argv[i]);
	}
	return result;
}

class ConfigurationSettings
{
public:

	//class const_iterator ITERATOR_BASE( forward_iterator_tag, ConfigurationSettings , size_t )
	//{	// iterator for nonmutable list
	//public:
	//	typedef std::forward_iterator_tag iterator_category;
	//	typedef tstring value_type;
	//	typedef size_t difference_type;
	//	typedef const ConfigurationSettings& reference;
	//	typedef reference const_reference;
	//	typedef const ConfigurationSettings* _Ctptr;

	//	const_iterator( Enumerator& container )
	//		: container_( Enumerator )
	//	{	// construct with null node pointer
	//	}

	//	const_iterator(size_t _Pnode , const ConfigurationSettings& container )
	//		: p_(_Pnode)
	//		, container_( container )
	//	{	// construct with node pointer _Pnode
	//	}

	//	const_reference operator*() const
	//	{	// return designated value
	//		return ( container_.getPropertyWithIndex(p_));
	//	}

	//	_Ctptr operator->() const
	//	{	// return pointer to class object
	//		return (&**this);
	//	}

	//	const_iterator& operator++()
	//	{	// preincrement
	//		p_ ++;
	//		return (*this);
	//	}

	//	const_iterator operator++(int)
	//	{	// postincrement
	//		const_iterator _Tmp = *this;
	//		++*this;
	//		return (_Tmp);
	//	}

	//	const_iterator& operator--()
	//	{	// predecrement
	//		p_ --;
	//		return (*this);
	//	}

	//	const_iterator operator--(int)
	//	{	// postdecrement
	//		const_iterator _Tmp = *this;
	//		--*this;
	//		return (_Tmp);
	//	}

	//	bool operator==(const const_iterator& _Right) const
	//	{	// test for iterator equality
	//		return (p_ == _Right.p_);
	//	}

	//	bool operator!=(const const_iterator& _Right) const
	//	{	// test for iterator inequality
	//		return (!(*this == _Right));
	//	}


	//protected:
	//	size_t p_;	// pointer to node
	//	const ConfigurationSettings& container_;
	//};



	//typedef const_iterator iterator;

	ConfigurationSettings( int argc, char* args[] )
		: configuration_( ___createConfiguration_args( argc, args ), ___freeConfiguration )
	{
	}

	ConfigurationSettings( const StringSeq& vec )
		: configuration_( ___createConfiguration_vec( vec ), ___freeConfiguration )
	{
	}

	ConfigurationSettings( IConfiguration* configuration = 0 )
		: configuration_( configuration )
	{
	}

	ConfigurationSettings( ConfigurationPtr configuration )
		: configuration_( configuration )
	{
	}

	/**
	* 读属性
	* @param[ in ] key 属性名
	* @return 成功返回属性值，失败扔出ConfigurationException异常
	*/
	const ::std::string& getProperty(const ::std::string& key) const
	{
		return configuration_->getNode( key ).value().value();
	}	

	/**
	* 读属性
	* @param[ in ] key 属性名
	* @param[ in ] value 缺省属性值
	* @return 成功返回属性值，失败返回缺省值
	*/
	const ::std::string& getPropertyWithDefault(const ::std::string& key, const ::std::string& value) const
	{
		try
		{
			return configuration_->getNode( key ).value().value();
		}
		catch( ... )
		{
		}
		return value;
	}

	/**
	* 读属性
	* @param[ in ] key 属性名
	* @return 成功返回属性值，失败扔出ConfigurationException异常
	*/
	template< typename T > 
		T get(const ::std::string& key) const
	{
		return convertStringToInteger< T >( getProperty( key ) );
	}

	/**
	* 读属性
	* @param[ in ] key 属性名
	* @param[ in ] value 缺省属性值
	* @return 成功返回属性值，失败返回缺省值
	*/
	template< typename T > 
		T get(const ::std::string& key, const T& value) const
	{
		try
		{
			return get< T >( key );
		}
		catch( ... )
		{
		}
		return value;
	}
	
	/**
	* 读属性的数量
	* @return 成功返回属性的数量
	*/
	size_t size( ) const
	{
		return configuration_->size();
	}

	///**
	// * 取得迭代器
	// */
	//Enumerator& enumerator() const
	//{
	//	return configuration_->enumerator();
	//}

	/**
	* 读属性集的一个子集
	* @param[ in ] key 子集名
	* @return 成功返回子集，失败返回null
	*/
	//ConfigurationSettings getConfig( const ::std::string& key ) const
	//{

	//	//return ConfigurationSettings( configuration_->getNode( key ).node() );
	//}

	const tstring& toString() const
	{
		return configuration_->toString();
	}
private:

	ConfigurationPtr configuration_;
};

_util_end

#endif // __Configuration_h__
