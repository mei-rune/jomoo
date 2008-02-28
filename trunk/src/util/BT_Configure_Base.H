

/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - ¤╭⌒╮ ╭⌒╮		            BT_Configure_Base.h,v 1.0 2005/03/25 09:50:54
*  ╱◥██◣ ╭╭ ⌒╮
* ︱田︱田田| ╰------
* -------------------------------------------------------------------------------
*/

#ifndef _BT_Configure_Base_H_
#define _BT_Configure_Base_H_


#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include <list>
#include "config.h"
#include "tstring.h"
# include <boost/iterator/iterator_facade.hpp>
#include "boost/shared_ptr.hpp"

_bt_begin


/**
 * @Brief BT_Configure_Base 配置接口
 * 这是BT的配置接口，每一个具体的配置都必须从它继承，每一个需要配置的组件都可以得到一个这样的接口，
 * 它是一个树形的数据结构，每一个叶子对应一个值和一个名字，每树枝对应一个名字
 */
class BT_Configure_Base
{
public:

	typedef std::list< BT_Configure_Base* > ChildList;
	typedef std::list< const BT_Configure_Base* > ConstChildList;

	/**
	 * 内部迭代器的接口
	 */
	class IIterator
	{
	public:
		virtual ~IIterator(){}
		virtual void next() = 0;
		virtual void prev() = 0;
		virtual BT_Configure_Base* data() = 0;

	};

	/**
	 * 内部迭代器的接口
	 */
	class IConstIterator
	{
	public:
		virtual ~IConstIterator(){}
		virtual void next() = 0;
		virtual void prev() = 0;
		virtual const BT_Configure_Base* data() = 0;
	};


	class iterator
		: public boost::iterator_facade<
		iterator
		, IIterator*
		, boost::bidirectional_traversal_tag
		, BT_Configure_Base&
		>
	{
	public:
		iterator()
			: m_node( (IIterator*)0) {}

			explicit iterator( IIterator* p)
				: m_node(p) {}

	private:
		friend class boost::iterator_core_access;

		void increment()
		{
			if( m_node.get() != 0 )
				m_node -> next();

		}

		void decrement()
		{
			if( m_node.get() == 0 )
				m_node -> prev();
		}

		bool equal( iterator const& other) const
		{
			if( m_node.get() != 0 && other.m_node.get() != 0 )
				return ( m_node->data() == other.m_node-> data() );
			if( m_node.get() == 0 && other.m_node.get() == 0 )
				return true;
			return false;
		}

		BT_Configure_Base&  dereference() const
		{
			if( m_node.get() == 0 || m_node->data() == 0 )
				throw std::logic_error( "BT_Configure_Base::iterator > 迭代器无效" );
			return *m_node->data();
		}

	private:

		boost::shared_ptr< IIterator >  m_node;

	};

		class const_iterator
		: public boost::iterator_facade<
		const_iterator
		, IConstIterator*
		, boost::bidirectional_traversal_tag
		, const BT_Configure_Base&
		>
	{
	public:
		const_iterator()
			: m_node( (IConstIterator*)0) {}

			explicit const_iterator( IConstIterator* p)
				: m_node(p) {}

	private:
		friend class boost::iterator_core_access;

		void increment()
		{
			if( m_node.get()!= 0 )
				m_node -> next();

		}

		void decrement()
		{
			if( m_node.get()!= 0 )
				m_node -> prev();
		}

		bool equal( const_iterator const& other) const
		{
			if( m_node.get() != 0 && other.m_node.get() != 0 )
				return ( m_node->data() == other.m_node-> data() );
			if( m_node.get() == 0 && other.m_node.get() == 0 )
				return true;
			return false;
		}

		const BT_Configure_Base&  dereference() const
		{
			if( m_node.get() == 0 || m_node->data() == 0 )
				throw std::logic_error( "迭代器无效" );
			return *m_node->data();
		}

		boost::shared_ptr< IConstIterator >  m_node;
	};

	/**
	 * virtula BT_Configure_Base destructor
	 */
	virtual ~BT_Configure_Base(){}

	/**
	 * 设置节点的名字。
	 * @param[ in ] name 名字的指针
	 * @return 成功返回true, 失败返回false;
	 * @remarks 注意当name 指针为null时，名字会被清空.
	 */
	virtual bool setName( const tchar* name ) = 0;

	/**
	 * 设置节点的值。
	 * @param[ in ] value 名字的指针
	 * @return 成功返回true, 失败返回false;
	 */
	virtual bool setValue( const tchar* value ) = 0;

	/**
	 * 在当前节点下增加一个子节点。
	 * @param[ in ] node 子节点的指针
	 * @return 成功返回true, 失败返回false;
	 * @remarks 注意在添加成功后，新添加的子节点会在本节点删除时，同时
	 * 被析构
	 */
	virtual bool appendChild( BT_Configure_Base* node ) = 0;

	/**
	 * 删除当前节点下的一个指定子节点。
	 * @param[ in ] node 该子节点的指针
	 * @return 成功返回true, 失败返回false;
	 * @remarks 注意在删除成功后，新删除的子节点会同时
	 * 被析构，node 会变成无效的野指针
	 */
	virtual bool deleteChild( BT_Configure_Base* node ) = 0;

	/**
	 * 删除当前节点下的一个指定名称的子节点。
	 * @param[ in ] name 该子节点的名称
	 * @return 成功返回true, 失败返回false;
	 * @remarks 注意在删除成功后，新删除的子节点会同时
	 * 被析构。
	 */
	virtual bool deleteChild( const tchar* name ) = 0;
	
	/**
	 * 取得当前节点的值。
	 * @return 成功返回值, 失败返回0;
	 * @remarks 注意在使用返回值后，不要删除它
	 */
	virtual const tchar* getValue() const = 0;
	
	/**
	 * 取得当前节点的名称。
	 * @return 成功返回当前节点的名称, 失败返回0;
	 * @remarks 注意在使用当前节点的名称后，不要删除它
	 */
	virtual const tchar* getName() const = 0;

	/**
	 * 在当前节点下查找一个指定名称的节点的指针。
	 * @param[ in ] name 要查找的节点的名称
	 * @return 成功返回该子节点的引用, 失败返回0;
	 * @remarks 注意在使用该子节点后，不要删除它
	 * 节点名称支持"."符分隔递归存取下层一节点，如xxx.xx为取得
	 * 当前节点下名为xxx的节点下的名为xx的节点，。
	 */
	virtual BT_Configure_Base* findChild( const tchar* name ) = 0;

	/**
	 * 在当前节点下查找一个指定名称的节点的指针。
	 * @param[ in ] name 要查找的节点的名称
	 * @return 成功返回该子节点的引用, 失败返回0;
	 * @remarks 注意在使用该子节点后，不要删除它
	 * 节点名称支持"."符分隔递归存取下层一节点，如xxx.xx为取得
	 * 当前节点下名为xxx的节点下的名为xx的节点，。
	 */
	virtual const BT_Configure_Base* findChild( const tchar* name ) const = 0;

	/**
	 * 在当前节点下查找一个指定名称的节点的值。
	 * @param[ in ] name 要查找的节点的名称
	 * @return 成功返回该子节点的值, 失败返回0;
	 * 节点名称支持"."符分隔递归存取下层一节点，如xxx.xx为取得
	 * 当前节点下名为xxx的节点下的名为xx的节点，。
	 */
	virtual const tchar* findValue( const tchar* name ) const = 0;


	/**
	 * 取得当前节点的父节点
	 * @return 成功返回该父节点, 失败返回0;
	 * @remarks 注意在使用该父节点后，不要删除它
	 */
	virtual BT_Configure_Base* getParentNode() = 0;

	/**
	 * 取得当前节点的父节点
	 * @return 成功返回该父节点, 失败返回0;
	 * @remarks 注意在使用该父节点后，不要删除它
	 */
	virtual const BT_Configure_Base* getParentNode() const = 0;

	/**
	 * 取得当前节点的根节点
	 * @return 成功返回该根节点, 失败返回0;
	 * @remarks 注意在使用该根节点后，不要删除它
	 */
	virtual BT_Configure_Base* getRootNode() = 0;

	/**
	 * 取得当前节点的根节点
	 * @return 成功返回该根节点, 失败返回0;
	 * @remarks 注意在使用该根节点后，不要删除它
	 */
	virtual const BT_Configure_Base* getRootNode() const = 0;

	/**
	 * 取得当前节点下孩子节点的起始迭代器。
	 * @return 成功返回起始迭代器的指针, 失败返回0;
	 */
	iterator begin()
	{
		return iterator( begin_() );
	}

	/**
	 * 取得当前节点下孩子节点的起始迭代器。
	 * @return 成功返回起始迭代器的指针, 失败返回0;
	 */
	iterator end()
	{
		return iterator( end_() );
	}

	/**
	 * 取得当前节点下孩子节点的起始迭代器。
	 * @return 成功返回起始迭代器的指针, 失败返回0;
	 */
	const_iterator begin()const 
	{
		return const_iterator( begin_() );
	}

	/**
	 * 取得当前节点下孩子节点的起始迭代器。
	 * @return 成功返回起始迭代器的指针, 失败返回0;
	 */
	const_iterator end()const 
	{
		return const_iterator( end_() );
	}

protected:

	/**
	 * 取得当前节点下孩子节点的起始迭代器。
	 * @return 成功返回起始迭代器的指针, 失败返回0;
	 * @remarks 注意在使用本迭代器后，要删除它
	 */
	virtual IIterator* begin_( ) = 0;

	/**
	 * 取得当前节点下孩子节点的结束迭代器。
	 * @return 成功返回结束迭代器的指针, 失败返回0;
	 * @remarks 注意在使用本迭代器后，要删除它
	 */
	virtual IIterator* end_( ) = 0;

	/**
	 * 取得当前节点下孩子节点的起始迭代器。
	 * @return 成功返回起始迭代器的指针, 失败返回0;
	 * @remarks 注意在使用本迭代器后，要删除它
	 */
	virtual IConstIterator* begin_( ) const = 0;

	/**
	 * 取得当前节点下孩子节点的结束迭代器。
	 * @return 成功返回结束迭代器的指针, 失败返回0;
	 * @remarks 注意在使用本迭代器后，要删除它
	 */
	virtual IConstIterator* end_( ) const = 0;
};

_bt_end;

#endif // _BT_Configure_Base_H_