
/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - ¡è¨q¡Ð¨r ¨q¡Ð¨r		            XML_Reflection.h,v 1.0 2005/03/11 11:33:34
 *  ¨u¨¨€¨€¨Ž ¨q¨q ¡Ð¨r
 * ¦òÌï¦òÌïÌï| ¨t------
 * -------------------------------------------------------------------------------
 */

#ifndef _XML_Reflection_H_
#define _XML_Reflection_H_

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */


#include "XML_serializer.h"
#include "Reflection_Impl.h"

_bt_serialize_begin

struct strcmpop
{
	bool operator()( const char* _Left, const char* _Right) const
	{
		return ( strcmp( _Left, _Right ) > 0 );
	}
};

class XML_Reflection : public Reflection_Impl
{
public:
	typedef std::map< const char* , XERCES_CPP_NAMESPACE_QUALIFIER DOMText* ,strcmpop > assoc_container_type;
	XML_Reflection( );
	~XML_Reflection(void);
	const std::list< std::string >& get_MemberName() const;
	const char* get_Member( const char* name ) const;
	bool set_Member( const char* name , const char* value );

	bool createmap( XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* root );
protected:

	mutable std::vector< char > value_str_;
	std::list< std::string > member_;
	assoc_container_type member_node_map_;
	bool edit_;
	bool edited_;
};


#define XML_Reflection_T_ST_1	typename T
#define XML_Reflection_T_ST_2	T

template< XML_Reflection_T_ST_1 >
class XML_Reflection_T : public XML_Reflection
{
public:
	XML_Reflection_T( const T &t );
	XML_Reflection_T( T &t );
	~XML_Reflection_T( );

	void flush( );
private:
	bool init( const T &t );
	void fini();
	XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* createDocument( );

	T* t_;
	BT_Scope_Ptr< XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument > document_;
};




_bt_serialize_end

#include "XML_Reflection_T.cpp"
#endif // _XML_Reflection_H_