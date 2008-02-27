#ifndef SEAL_COMPONENTCONTEXT_H
# define SEAL_COMPONENTCONTEXT_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_MicroKernel.h"
# include "Hazel.Base/counter_ptr.hpp"
# include "Hazel.Base/string.hpp"
# include "Hazel.Base/exception.hpp"
# include "Hazel.Base/collections/enumerator.h"
# include "IComponentModel.h"

_micro_kernel_begin

class IKernel;

class IComponentContext
{
public:

	typedef IComponent::key_type key_type;
	
	typedef IComponentContext* ComponentContextPtr;
	typedef const IComponentContext* ComponentContextConstPtr;

	class IContextContainer
	{
	public:
		
		class NoExistError : public Exception
		{
		public:

			NoExistError( const   char* const         srcFile
				, size_t        srcLine 
				, const tstring& n )
				: _hazel Exception( srcFile, srcLine ,NoFindError )
				, name_( n )
			{
			}

			const tstring& name() const
			{
				return name_;
			}

			virtual Exception* clone()
			{
				return new NoExistError( *this );
			}

			virtual void rethrow()
			{
				Raise( *this );
			}

			virtual void print(std::ostream& Target ) const
			{
				Target << BT_TEXT( "IComponentContext::NoExistError[" )
					<< what()
					<< BT_TEXT( "]" )
					<< std::endl;
				dumpFile( Target );
				Target << BT_TEXT( "\t[ name =" )
					<< name()
					<< BT_TEXT( " ]" );
			}
		private:
			tstring name_;
		};



		class ExistError : public Exception
		{
		public:

			ExistError( const   char* const         srcFile
				, size_t        srcLine
				, const tstring& n )
				: _hazel Exception( srcFile, srcLine ,_ExistError )
				, name_( n )
			{
			}

			const tstring& name() const
			{
				return name_;
			}

			virtual Exception* clone()
			{
				return new ExistError( *this );
			}

			virtual void rethrow()
			{
				Raise( *this );
			}

			virtual void print(std::ostream& Target ) const
			{
				Target << BT_TEXT( "IComponentContext::ExistError[" )
					<< what()
					<< BT_TEXT( "]" )
					<< std::endl;
				dumpFile( Target );
				Target << BT_TEXT( "\t[ name =" )
					<< name()
					<< BT_TEXT( " ]" );
			}
		private:
			tstring name_;
		};



		class walker_type
		{
		public:
			typedef IComponentContext value_type;

			virtual ~walker_type(){}
			virtual void on_walk( value_type& ) = 0;
			virtual void on_walk( const value_type& ) = 0;
		};

		typedef _hazel enumerator< walker_type > enumerator;
		typedef _hazel const_enumerator< walker_type > const_enumerator;

		virtual ~IContextContainer(){}

		/**
		 * 初始化
		 */
		virtual void Initialize( IKernel& kernel ) = 0;

		/**
			* 增加一个子节点
		 */
		virtual void add( ComponentContextPtr child ) = 0;

		/**
		 * 删除一个子节点
		 */
		virtual bool remove( const tstring& name ) = 0;

		/**
		 * 查找一个子节点
		 */
		virtual ComponentContextPtr find( const tstring& name ) = 0;
		virtual ComponentContextConstPtr find( const tstring& name ) const = 0;

		/**
		 * 子节点的个数
		 */
		virtual size_t size( ) const = 0;

		/**
		 * 遍历所有的组件模型
		 */
		virtual void walk( walker_type& walker ) = 0;
		virtual void walk( walker_type& walker ) const = 0;

		virtual const tstring& toString() const = 0;
	};


	class walker_type
	{
	public:
		typedef IComponent value_type;

		virtual ~walker_type(){}
		virtual void on_walk( value_type& ) = 0;
		virtual void on_walk( const value_type& ) = 0;
	};

	
	typedef enumerator< walker_type > enumerator;
	typedef const_enumerator< walker_type > const_enumerator;
	
	class NoExistError : public _hazel Exception
	{
	public:

		NoExistError( const   char* const         srcFile
			, size_t        srcLine
			, const key_type& key )
			: _hazel Exception( srcFile, srcLine ,NoFindError )
			, guid_( key.guid() )
			, position_( key.position() )
		{
		}

		NoExistError( const   char* const         srcFile
			, size_t        srcLine
			, const key_type::guid_type& _guid
			, size_t _position )
			: _hazel Exception( srcFile, srcLine ,NoFindError )
			, guid_( _guid )
			, position_( _position )
		{
		}

		const key_type::guid_type& guid() const
		{
			return guid_;
		}

		size_t position() const
		{
			return position_;
		}

		virtual Exception* clone()
		{
			return new NoExistError( *this );
		}

		virtual void rethrow()
		{
			Raise( *this );
		}

		virtual void print(std::ostream& Target ) const
		{
			Target << BT_TEXT( "IComponentContext::NoExistError[" )
				<< what()
				<< BT_TEXT( "]" )
				<< std::endl;
			dumpFile( Target );
			Target << BT_TEXT( "\t[ guid =" )
				<< guid()
				<< BT_TEXT( ",position =" )
				<< position()
				<< BT_TEXT( " ]" );
		}
	private:
		key_type::guid_type guid_;
		size_t position_;
	};


	virtual ~IComponentContext (void){};

	/**
	 * 节点的名字
	 */
	virtual const tstring& name() const = 0;
	
	/**
	 * 取得子节点的容器
	 */
	virtual IContextContainer& childs() = 0;
	virtual const IContextContainer& childs() const = 0;

	/**
	 * 取得父节点
	 */
	virtual IComponentContext* parent() = 0;
	virtual const IComponentContext* parent() const= 0;

	/**
	 * 取得组件的引用
	 * @param[ in ] key 组件的id号
	 * @remarks 注意，如果找不到时因扔出异常
	 */
	virtual IComponent&	component ( const key_type& key ) = 0;
	virtual const IComponent&	component ( const key_type& key ) const = 0;
	virtual IComponent&	component ( const tstring& key_string ) = 0;
	virtual const IComponent&	component ( const tstring& key_string ) const = 0;

	/**
	 * 是否有组件
	 * @param[ in ] key 组件的id号
	 * @return 找到组件返回true,否则返回false
	 */
	virtual bool		has_component ( const key_type& key ) const = 0;
	virtual bool		has_component ( const tstring& key_string ) const = 0;

    /**
	 * 容器中组件的个数
	 * @return 组件的个数
	 */
	virtual size_t			size (void) const = 0;

	/**
	 * 遍历所有的组件模型
	 */
	virtual void walk( walker_type& walker ) = 0;
	virtual void walk( walker_type& walker ) const = 0;

	virtual const tstring&	toString() const = 0;
};

typedef IComponentContext::ComponentContextPtr ComponentContextPtr;
typedef const IComponentContext::ComponentContextConstPtr ComponentContextConstPtr;

class IComponentContextFactory
{
public:
	virtual ~IComponentContextFactory(){}
    virtual ComponentContextPtr create( const tstring& type_string  ) = 0;
	virtual void release( ComponentContextPtr ) = 0; 
};

_micro_kernel_end

#endif // SEAL_COMPONENTCONTEXT_H
