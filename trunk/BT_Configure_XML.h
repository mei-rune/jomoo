

/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - ��q�Шr �q�Шr		          BT_Configure_XML.h,v 1.0 2005/04/22 13:53:54
 *  �u�������� �q�q �Шr
 * ���������| �t------
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
	 * ��һ���ַ����й��������
	 * @param[ in ] name �ڵ������
	 * @param[ in ] value �ڵ��ֵ
	 */
	BT_Configure_XML_Text( const tchar* name, const tchar* value ,BT_Configure_Base* parent = 0 );

	/**
	 * BT_Configure_XML_Text destructor
	 */
	~BT_Configure_XML_Text(void);

	/**
	 * ���ýڵ�����֡�
	 * @param[ in ] name ���ֵ�ָ��
	 * @return �ɹ�����true, ʧ�ܷ���false;
	 * @remarks ע�⵱name ָ��Ϊnullʱ�����ֻᱻ���.
	 */
	bool setName( const tchar* name );

	/**
	 * ���ýڵ��ֵ��
	 * @param[ in ] value ���ֵ�ָ��
	 * @return �ɹ�����true, ʧ�ܷ���false;
	 */
	bool setValue( const tchar* value );

	/**
	 * �ڵ�ǰ�ڵ�������һ���ӽڵ㡣
	 * @param[ in ] node �ӽڵ��ָ��
	 * @return �ɹ�����true, ʧ�ܷ���false;
	 * @remarks ע������ӳɹ�������ӵ��ӽڵ���ڱ��ڵ�ɾ��ʱ��ͬʱ
	 * ������
	 */
	bool appendChild( BT_Configure_Base* node );

	/**
	 * ɾ����ǰ�ڵ��µ�һ��ָ���ӽڵ㡣
	 * @param[ in ] node ���ӽڵ��ָ��
	 * @return �ɹ�����true, ʧ�ܷ���false;
	 * @remarks ע����ɾ���ɹ�����ɾ�����ӽڵ��ͬʱ
	 * ��������node ������Ч��Ұָ��
	 */
	bool deleteChild( BT_Configure_Base* node );

	/**
	 * ɾ����ǰ�ڵ��µ�һ��ָ�����Ƶ��ӽڵ㡣
	 * @param[ in ] name ���ӽڵ������
	 * @return �ɹ�����true, ʧ�ܷ���false;
	 * @remarks ע����ɾ���ɹ�����ɾ�����ӽڵ��ͬʱ
	 * ��������
	 */
	bool deleteChild( const tchar* name );
	
	/**
	 * ȡ�õ�ǰ�ڵ��ֵ��
	 * @return �ɹ�����ֵ, ʧ�ܷ���0;
	 * @remarks ע����ʹ�÷���ֵ�󣬲�Ҫɾ����
	 */
	const tchar* getValue() const;
	
	/**
	 * ȡ�õ�ǰ�ڵ�����ơ�
	 * @return �ɹ����ص�ǰ�ڵ������, ʧ�ܷ���0;
	 * @remarks ע����ʹ�õ�ǰ�ڵ�����ƺ󣬲�Ҫɾ����
	 */
	const tchar* getName() const;

	/**
	 * �ڵ�ǰ�ڵ��²���һ��ָ�����ƵĽڵ��ָ�롣
	 * @param[ in ] name Ҫ���ҵĽڵ������
	 * @return �ɹ����ظ��ӽڵ������, ʧ�ܷ���0;
	 * @remarks ע����ʹ�ø��ӽڵ�󣬲�Ҫɾ����
	 */
	BT_Configure_Base* findChild( const tchar* name );

	/**
	 * �ڵ�ǰ�ڵ��²���һ��ָ�����ƵĽڵ��ָ�롣
	 * @param[ in ] name Ҫ���ҵĽڵ������
	 * @return �ɹ����ظ��ӽڵ������, ʧ�ܷ���0;
	 * @remarks ע����ʹ�ø��ӽڵ�󣬲�Ҫɾ����
	 */
	const BT_Configure_Base* findChild( const tchar* name ) const;

	/**
	 * �ڵ�ǰ�ڵ��²���һ��ָ�����ƵĽڵ��ֵ��
	 * @param[ in ] name Ҫ���ҵĽڵ������
	 * @return �ɹ����ظ��ӽڵ��ֵ, ʧ�ܷ���0;
	 */
	const tchar* findValue( const tchar* name ) const;

	/**
	 * ȡ�õ�ǰ�ڵ�ĸ��ڵ�
	 * @return �ɹ����ظø��ڵ�, ʧ�ܷ���0;
	 * @remarks ע����ʹ�øø��ڵ�󣬲�Ҫɾ����
	 */
	BT_Configure_Base* getParentNode();

	/**
	 * ȡ�õ�ǰ�ڵ�ĸ��ڵ�
	 * @return �ɹ����ظø��ڵ�, ʧ�ܷ���0;
	 * @remarks ע����ʹ�øø��ڵ�󣬲�Ҫɾ����
	 */
	const BT_Configure_Base* getParentNode() const;

	/**
	 * ȡ�õ�ǰ�ڵ�ĸ��ڵ�
	 * @return �ɹ����ظø��ڵ�, ʧ�ܷ���0;
	 * @remarks ע����ʹ�øø��ڵ�󣬲�Ҫɾ����
	 */
	BT_Configure_Base* getRootNode();

	/**
	 * ȡ�õ�ǰ�ڵ�ĸ��ڵ�
	 * @return �ɹ����ظø��ڵ�, ʧ�ܷ���0;
	 * @remarks ע����ʹ�øø��ڵ�󣬲�Ҫɾ����
	 */
	const BT_Configure_Base* getRootNode() const;

protected:

	/**
	 * ȡ�õ�ǰ�ڵ��º��ӽڵ����ʼ��������
	 * @return �ɹ�������ʼ��������ָ��, ʧ�ܷ���0;
	 * @remarks ע����ʹ�ñ���������Ҫɾ����
	 */
	IIterator* begin_( );

	/**
	 * ȡ�õ�ǰ�ڵ��º��ӽڵ�Ľ�����������
	 * @return �ɹ����ؽ�����������ָ��, ʧ�ܷ���0;
	 * @remarks ע����ʹ�ñ���������Ҫɾ����
	 */
	IIterator* end_( );

	/**
	 * ȡ�õ�ǰ�ڵ��º��ӽڵ����ʼ��������
	 * @return �ɹ�������ʼ��������ָ��, ʧ�ܷ���0;
	 * @remarks ע����ʹ�ñ���������Ҫɾ����
	 */
	IConstIterator* begin_( ) const;

	/**
	 * ȡ�õ�ǰ�ڵ��º��ӽڵ�Ľ�����������
	 * @return �ɹ����ؽ�����������ָ��, ʧ�ܷ���0;
	 * @remarks ע����ʹ�ñ���������Ҫɾ����
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
	 * �ڲ��������Ľӿ�
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
	 * �ڲ��������Ľӿ�
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
	 * ��һ���ļ��й��������
	 * @param[ in ] file_name �ļ���( �ĵ���������һ������url; )
	 */
	BT_Configure_XML_Node( const tchar* file_name ,BT_Configure_Base* parent = 0 );
	
	/**
	 * BT_Configure_XML_Node constructor
	 * ��һ���ַ����й��������
	 * @param[ in ] buf �ַ������ָ��
	 * @param[ in ] len �ַ�����Ĵ�С
	 */
	BT_Configure_XML_Node( const tchar* buf, size_t len , BT_Configure_Base* parent = 0 );

	/**
	 * BT_Configure_XML_Node constructor
	 * ��һ��Dom�й��������
	 * @param[ in ] node_ �ַ������ָ��
	 */
	BT_Configure_XML_Node( _bt_xml DOM_Node_Ptr node_ , BT_Configure_Base* parent = 0 );

	/**
	 * BT_Configure_XML_Node destructor
	 */
	~BT_Configure_XML_Node(void);

	/**
	 * ��һ���ļ��й��������
	 * @param[ in ] file_name �ļ���( �ĵ���������һ������url; )
	 * @return �ɹ�����true, ʧ�ܷ���false;
	 */
	bool open( const tchar* file_name );

	/**
	 * ��һ���ַ����й��������
	 * @param[ in ] buf �ַ������ָ��
	 * @param[ in ] len �ַ�����Ĵ�С
	 * @return �ɹ�����true, ʧ�ܷ���false;
	 */
	bool open( const tchar* buf, size_t len );

	/**
	 * ��һ��xml ���е���һ������
	 */
	void init( _bt_xml DOM_Node_Ptr node );

	/**
	 * ���ýڵ�����֡�
	 * @param[ in ] name ���ֵ�ָ��
	 * @return �ɹ�����true, ʧ�ܷ���false;
	 * @remarks ע�⵱name ָ��Ϊnullʱ�����ֻᱻ���.
	 */
	bool setName( const tchar* name );

	/**
	 * ���ýڵ��ֵ��
	 * @param[ in ] value ���ֵ�ָ��
	 * @return �ɹ�����true, ʧ�ܷ���false;
	 */
	bool setValue( const tchar* value );

	/**
	 * �ڵ�ǰ�ڵ�������һ���ӽڵ㡣
	 * @param[ in ] node �ӽڵ��ָ��
	 * @return �ɹ�����true, ʧ�ܷ���false;
	 * @remarks ע������ӳɹ�������ӵ��ӽڵ���ڱ��ڵ�ɾ��ʱ��ͬʱ
	 * ������
	 */
	bool appendChild( BT_Configure_Base* node );

	/**
	 * ɾ����ǰ�ڵ��µ�һ��ָ���ӽڵ㡣
	 * @param[ in ] node ���ӽڵ��ָ��
	 * @return �ɹ�����true, ʧ�ܷ���false;
	 * @remarks ע����ɾ���ɹ�����ɾ�����ӽڵ��ͬʱ
	 * ��������node ������Ч��Ұָ��
	 */
	bool deleteChild( BT_Configure_Base* node );

	/**
	 * ɾ����ǰ�ڵ��µ�һ��ָ�����Ƶ��ӽڵ㡣
	 * @param[ in ] name ���ӽڵ������
	 * @return �ɹ�����true, ʧ�ܷ���false;
	 * @remarks ע����ɾ���ɹ�����ɾ�����ӽڵ��ͬʱ
	 * ��������
	 */
	bool deleteChild( const tchar* name );
	
	/**
	 * ȡ�õ�ǰ�ڵ��ֵ��
	 * @return �ɹ�����ֵ, ʧ�ܷ���0;
	 * @remarks ע����ʹ�÷���ֵ�󣬲�Ҫɾ����
	 */
	const tchar* getValue() const;
	
	/**
	 * ȡ�õ�ǰ�ڵ�����ơ�
	 * @return �ɹ����ص�ǰ�ڵ������, ʧ�ܷ���0;
	 * @remarks ע����ʹ�õ�ǰ�ڵ�����ƺ󣬲�Ҫɾ����
	 */
	const tchar* getName() const;

	/**
	 * �ڵ�ǰ�ڵ��²���һ��ָ�����ƵĽڵ��ָ�롣
	 * @param[ in ] name Ҫ���ҵĽڵ������
	 * @return �ɹ����ظ��ӽڵ������, ʧ�ܷ���0;
	 * @remarks ע����ʹ�ø��ӽڵ�󣬲�Ҫɾ����
	 */
	BT_Configure_Base* findChild( const tchar* name );

	/**
	 * �ڵ�ǰ�ڵ��²���һ��ָ�����ƵĽڵ��ָ�롣
	 * @param[ in ] name Ҫ���ҵĽڵ������
	 * @return �ɹ����ظ��ӽڵ������, ʧ�ܷ���0;
	 * @remarks ע����ʹ�ø��ӽڵ�󣬲�Ҫɾ����
	 */
	const BT_Configure_Base* findChild( const tchar* name ) const;

	/**
	 * �ڵ�ǰ�ڵ��²���һ��ָ�����ƵĽڵ��ֵ��
	 * @param[ in ] name Ҫ���ҵĽڵ������
	 * @return �ɹ����ظ��ӽڵ��ֵ, ʧ�ܷ���0;
	 */
	const tchar* findValue( const tchar* name ) const;

	/**
	 * ȡ�õ�ǰ�ڵ�ĸ��ڵ�
	 * @return �ɹ����ظø��ڵ�, ʧ�ܷ���0;
	 * @remarks ע����ʹ�øø��ڵ�󣬲�Ҫɾ����
	 */
	BT_Configure_Base* getParentNode();

	/**
	 * ȡ�õ�ǰ�ڵ�ĸ��ڵ�
	 * @return �ɹ����ظø��ڵ�, ʧ�ܷ���0;
	 * @remarks ע����ʹ�øø��ڵ�󣬲�Ҫɾ����
	 */
	const BT_Configure_Base* getParentNode() const;

	/**
	 * ȡ�õ�ǰ�ڵ�ĸ��ڵ�
	 * @return �ɹ����ظø��ڵ�, ʧ�ܷ���0;
	 * @remarks ע����ʹ�øø��ڵ�󣬲�Ҫɾ����
	 */
	BT_Configure_Base* getRootNode();

	/**
	 * ȡ�õ�ǰ�ڵ�ĸ��ڵ�
	 * @return �ɹ����ظø��ڵ�, ʧ�ܷ���0;
	 * @remarks ע����ʹ�øø��ڵ�󣬲�Ҫɾ����
	 */
	const BT_Configure_Base* getRootNode() const;

protected:

	/**
	 * ȡ�õ�ǰ�ڵ��º��ӽڵ����ʼ��������
	 * @return �ɹ�������ʼ��������ָ��, ʧ�ܷ���0;
	 * @remarks ע����ʹ�ñ���������Ҫɾ����
	 */
	IIterator* begin_( );

	/**
	 * ȡ�õ�ǰ�ڵ��º��ӽڵ�Ľ�����������
	 * @return �ɹ����ؽ�����������ָ��, ʧ�ܷ���0;
	 * @remarks ע����ʹ�ñ���������Ҫɾ����
	 */
	IIterator* end_( );

	/**
	 * ȡ�õ�ǰ�ڵ��º��ӽڵ����ʼ��������
	 * @return �ɹ�������ʼ��������ָ��, ʧ�ܷ���0;
	 * @remarks ע����ʹ�ñ���������Ҫɾ����
	 */
	IConstIterator* begin_( ) const;

	/**
	 * ȡ�õ�ǰ�ڵ��º��ӽڵ�Ľ�����������
	 * @return �ɹ����ؽ�����������ָ��, ʧ�ܷ���0;
	 * @remarks ע����ʹ�ñ���������Ҫɾ����
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