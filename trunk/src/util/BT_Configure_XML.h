

/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - ¤╭⌒╮ ╭⌒╮		          BT_Configure_XML.h,v 1.0 2005/04/22 13:53:54
 *  ╱◥██◣ ╭╭ ⌒╮
 * ︱田︱田田| ╰------
 * -------------------------------------------------------------------------------
 */

#ifndef _BT_Configure_XML_H_
#define _BT_Configure_XML_H_


#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "BT_Configure_Base.h"
#include "xml/xml.h"
#include <map>
#include <list>

_bt_begin

class BT_Configure_XML_Text : public BT_Configure_Base
{
public:
	/**
	 * BT_Configure_XML_Text constructor
	 */
	BT_Configure_XML_Text( BT_Configure_Base* parent = 0  );
	
	/**
	 * BT_Configure_XML_Text constructor
	 * 从一个字符串中构造出配置
	 * @param[ in ] name 节点的名称
	 * @param[ in ] value 节点的值
	 */
	BT_Configure_XML_Text( const tchar* name, const tchar* value ,BT_Configure_Base* parent = 0 );

	/**
	 * BT_Configure_XML_Text destructor
	 */
	~BT_Configure_XML_Text(void);

	/**
	 * 设置节点的名字。
	 * @param[ in ] name 名字的指针
	 * @return 成功返回true, 失败返回false;
	 * @remarks 注意当name 指针为null时，名字会被清空.
	 */
	bool setName( const tchar* name );

	/**
	 * 设置节点的值。
	 * @param[ in ] value 名字的指针
	 * @return 成功返回true, 失败返回false;
	 */
	bool setValue( const tchar* value );

	/**
	 * 在当前节点下增加一个子节点。
	 * @param[ in ] node 子节点的指针
	 * @return 成功返回true, 失败返回false;
	 * @remarks 注意在添加成功后，新添加的子节点会在本节点删除时，同时
	 * 被析构
	 */
	bool appendChild( BT_Configure_Base* node );

	/**
	 * 删除当前节点下的一个指定子节点。
	 * @param[ in ] node 该子节点的指针
	 * @return 成功返回true, 失败返回false;
	 * @remarks 注意在删除成功后，新删除的子节点会同时
	 * 被析构，node 会变成无效的野指针
	 */
	bool deleteChild( BT_Configure_Base* node );

	/**
	 * 删除当前节点下的一个指定名称的子节点。
	 * @param[ in ] name 该子节点的名称
	 * @return 成功返回true, 失败返回false;
	 * @remarks 注意在删除成功后，新删除的子节点会同时
	 * 被析构。
	 */
	bool deleteChild( const tchar* name );
	
	/**
	 * 取得当前节点的值。
	 * @return 成功返回值, 失败返回0;
	 * @remarks 注意在使用返回值后，不要删除它
	 */
	const tchar* getValue() const;
	
	/**
	 * 取得当前节点的名称。
	 * @return 成功返回当前节点的名称, 失败返回0;
	 * @remarks 注意在使用当前节点的名称后，不要删除它
	 */
	const tchar* getName() const;

	/**
	 * 在当前节点下查找一个指定名称的节点的指针。
	 * @param[ in ] name 要查找的节点的名称
	 * @return 成功返回该子节点的引用, 失败返回0;
	 * @remarks 注意在使用该子节点后，不要删除它
	 */
	BT_Configure_Base* findChild( const tchar* name );

	/**
	 * 在当前节点下查找一个指定名称的节点的指针。
	 * @param[ in ] name 要查找的节点的名称
	 * @return 成功返回该子节点的引用, 失败返回0;
	 * @remarks 注意在使用该子节点后，不要删除它
	 */
	const BT_Configure_Base* findChild( const tchar* name ) const;

	/**
	 * 在当前节点下查找一个指定名称的节点的值。
	 * @param[ in ] name 要查找的节点的名称
	 * @return 成功返回该子节点的值, 失败返回0;
	 */
	const tchar* findValue( const tchar* name ) const;

	/**
	 * 取得当前节点的父节点
	 * @return 成功返回该父节点, 失败返回0;
	 * @remarks 注意在使用该父节点后，不要删除它
	 */
	BT_Configure_Base* getParentNode();

	/**
	 * 取得当前节点的父节点
	 * @return 成功返回该父节点, 失败返回0;
	 * @remarks 注意在使用该父节点后，不要删除它
	 */
	const BT_Configure_Base* getParentNode() const;

	/**
	 * 取得当前节点的根节点
	 * @return 成功返回该根节点, 失败返回0;
	 * @remarks 注意在使用该根节点后，不要删除它
	 */
	BT_Configure_Base* getRootNode();

	/**
	 * 取得当前节点的根节点
	 * @return 成功返回该根节点, 失败返回0;
	 * @remarks 注意在使用该根节点后，不要删除它
	 */
	const BT_Configure_Base* getRootNode() const;

protected:

	/**
	 * 取得当前节点下孩子节点的起始迭代器。
	 * @return 成功返回起始迭代器的指针, 失败返回0;
	 * @remarks 注意在使用本迭代器后，要删除它
	 */
	IIterator* begin_( );

	/**
	 * 取得当前节点下孩子节点的结束迭代器。
	 * @return 成功返回结束迭代器的指针, 失败返回0;
	 * @remarks 注意在使用本迭代器后，要删除它
	 */
	IIterator* end_( );

	/**
	 * 取得当前节点下孩子节点的起始迭代器。
	 * @return 成功返回起始迭代器的指针, 失败返回0;
	 * @remarks 注意在使用本迭代器后，要删除它
	 */
	IConstIterator* begin_( ) const;

	/**
	 * 取得当前节点下孩子节点的结束迭代器。
	 * @return 成功返回结束迭代器的指针, 失败返回0;
	 * @remarks 注意在使用本迭代器后，要删除它
	 */
	IConstIterator* end_( ) const;


private:

	tstring value_;
	tstring name_;

	BT_Configure_Base* parentNode_;
};

class BT_Configure_XML_Node : public BT_Configure_Base
{
public:

	typedef std::multimap< tstring , BT_Configure_Base* , stringcaseless > container_type;

	/**
	 * 内部迭代器的接口
	 */
	class IIterator_XML : public IIterator
	{
	public:
		IIterator_XML( container_type::iterator it , container_type::iterator endit )
			: it_( it )
			, endit_( endit )
		{}

		void next()
		{
			it_ ++;
		}
		void prev()
		{
			it_ --;
		}
		BT_Configure_Base* data()
		{
			if( it_ != endit_ )
				return it_->second;
			return 0;
		}
	private:
		container_type::iterator it_;
		container_type::iterator endit_;
	};

	/**
	 * 内部迭代器的接口
	 */
	class IConstIterator_XML : public IConstIterator
	{
	public:
		IConstIterator_XML( container_type::const_iterator it , container_type::const_iterator endit )
			: it_( it )
			, endit_( endit )
		{}

		void next()
		{
			it_ ++;
		}
		void prev()
		{
			it_ --;
		}
		const BT_Configure_Base* data()
		{
			if( it_ != endit_ )
				return it_->second;
			return 0;
		}
	private:
		container_type::const_iterator it_;
		container_type::const_iterator endit_;
	};

	/**
	 * BT_Configure_XML_Node constructor
	 */
	BT_Configure_XML_Node( BT_Configure_Base* parent = 0 );

	/**
	 * BT_Configure_XML_Node constructor
	 * 从一个文件中构造出配置
	 * @param[ in ] file_name 文件名( 文档名可以是一个任意url; )
	 */
	BT_Configure_XML_Node( const tchar* file_name ,BT_Configure_Base* parent = 0 );
	
	/**
	 * BT_Configure_XML_Node constructor
	 * 从一个字符串中构造出配置
	 * @param[ in ] buf 字符缓冲的指针
	 * @param[ in ] len 字符缓冲的大小
	 */
	BT_Configure_XML_Node( const tchar* buf, size_t len , BT_Configure_Base* parent = 0 );

	/**
	 * BT_Configure_XML_Node constructor
	 * 从一个Dom中构造出配置
	 * @param[ in ] node_ 字符缓冲的指针
	 */
	BT_Configure_XML_Node( _bt_xml DOM_Node_Ptr node_ , BT_Configure_Base* parent = 0 );

	/**
	 * BT_Configure_XML_Node destructor
	 */
	~BT_Configure_XML_Node(void);

	/**
	 * 从一个文件中构造出配置
	 * @param[ in ] file_name 文件名( 文档名可以是一个任意url; )
	 * @return 成功返回true, 失败返回false;
	 */
	bool open( const tchar* file_name );

	/**
	 * 从一个字符串中构造出配置
	 * @param[ in ] buf 字符缓冲的指针
	 * @param[ in ] len 字符缓冲的大小
	 * @return 成功返回true, 失败返回false;
	 */
	bool open( const tchar* buf, size_t len );

	/**
	 * 从一个xml 树中导出一个配置
	 */
	void init( _bt_xml DOM_Node_Ptr node );

	/**
	 * 设置节点的名字。
	 * @param[ in ] name 名字的指针
	 * @return 成功返回true, 失败返回false;
	 * @remarks 注意当name 指针为null时，名字会被清空.
	 */
	bool setName( const tchar* name );

	/**
	 * 设置节点的值。
	 * @param[ in ] value 名字的指针
	 * @return 成功返回true, 失败返回false;
	 */
	bool setValue( const tchar* value );

	/**
	 * 在当前节点下增加一个子节点。
	 * @param[ in ] node 子节点的指针
	 * @return 成功返回true, 失败返回false;
	 * @remarks 注意在添加成功后，新添加的子节点会在本节点删除时，同时
	 * 被析构
	 */
	bool appendChild( BT_Configure_Base* node );

	/**
	 * 删除当前节点下的一个指定子节点。
	 * @param[ in ] node 该子节点的指针
	 * @return 成功返回true, 失败返回false;
	 * @remarks 注意在删除成功后，新删除的子节点会同时
	 * 被析构，node 会变成无效的野指针
	 */
	bool deleteChild( BT_Configure_Base* node );

	/**
	 * 删除当前节点下的一个指定名称的子节点。
	 * @param[ in ] name 该子节点的名称
	 * @return 成功返回true, 失败返回false;
	 * @remarks 注意在删除成功后，新删除的子节点会同时
	 * 被析构。
	 */
	bool deleteChild( const tchar* name );
	
	/**
	 * 取得当前节点的值。
	 * @return 成功返回值, 失败返回0;
	 * @remarks 注意在使用返回值后，不要删除它
	 */
	const tchar* getValue() const;
	
	/**
	 * 取得当前节点的名称。
	 * @return 成功返回当前节点的名称, 失败返回0;
	 * @remarks 注意在使用当前节点的名称后，不要删除它
	 */
	const tchar* getName() const;

	/**
	 * 在当前节点下查找一个指定名称的节点的指针。
	 * @param[ in ] name 要查找的节点的名称
	 * @return 成功返回该子节点的引用, 失败返回0;
	 * @remarks 注意在使用该子节点后，不要删除它
	 */
	BT_Configure_Base* findChild( const tchar* name );

	/**
	 * 在当前节点下查找一个指定名称的节点的指针。
	 * @param[ in ] name 要查找的节点的名称
	 * @return 成功返回该子节点的引用, 失败返回0;
	 * @remarks 注意在使用该子节点后，不要删除它
	 */
	const BT_Configure_Base* findChild( const tchar* name ) const;

	/**
	 * 在当前节点下查找一个指定名称的节点的值。
	 * @param[ in ] name 要查找的节点的名称
	 * @return 成功返回该子节点的值, 失败返回0;
	 */
	const tchar* findValue( const tchar* name ) const;

	/**
	 * 取得当前节点的父节点
	 * @return 成功返回该父节点, 失败返回0;
	 * @remarks 注意在使用该父节点后，不要删除它
	 */
	BT_Configure_Base* getParentNode();

	/**
	 * 取得当前节点的父节点
	 * @return 成功返回该父节点, 失败返回0;
	 * @remarks 注意在使用该父节点后，不要删除它
	 */
	const BT_Configure_Base* getParentNode() const;

	/**
	 * 取得当前节点的根节点
	 * @return 成功返回该根节点, 失败返回0;
	 * @remarks 注意在使用该根节点后，不要删除它
	 */
	BT_Configure_Base* getRootNode();

	/**
	 * 取得当前节点的根节点
	 * @return 成功返回该根节点, 失败返回0;
	 * @remarks 注意在使用该根节点后，不要删除它
	 */
	const BT_Configure_Base* getRootNode() const;

protected:

	/**
	 * 取得当前节点下孩子节点的起始迭代器。
	 * @return 成功返回起始迭代器的指针, 失败返回0;
	 * @remarks 注意在使用本迭代器后，要删除它
	 */
	IIterator* begin_( );

	/**
	 * 取得当前节点下孩子节点的结束迭代器。
	 * @return 成功返回结束迭代器的指针, 失败返回0;
	 * @remarks 注意在使用本迭代器后，要删除它
	 */
	IIterator* end_( );

	/**
	 * 取得当前节点下孩子节点的起始迭代器。
	 * @return 成功返回起始迭代器的指针, 失败返回0;
	 * @remarks 注意在使用本迭代器后，要删除它
	 */
	IConstIterator* begin_( ) const;

	/**
	 * 取得当前节点下孩子节点的结束迭代器。
	 * @return 成功返回结束迭代器的指针, 失败返回0;
	 * @remarks 注意在使用本迭代器后，要删除它
	 */
	IConstIterator* end_( ) const;

private:

	_bt_xml XMLDoc xml_;

	container_type node_map_;
	
	tstring name_;

	BT_Configure_Base* parentNode_;
};

_bt_end

#endif // _BT_Configure_XML_H_