/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - °Ë®q°–®r ®q°–®r		               Dom_Adapter.h,v 1.0 2005/03/18 11:40:54
 *  ®u®ê®Ä®Ä®é ®q®q °–®r
 * ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
 * -------------------------------------------------------------------------------
 */

#ifndef _Dom_Adapter_H_
#define _Dom_Adapter_H_


#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "xml_adapter.h"


_bt_serialize_begin

class Dom_Adapter: public DomNode_Adapter
{
public:
	Dom_Adapter( XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* node , bool del = false )
		: node_( node )
		, delete_( del )
	{
	}

	~Dom_Adapter()
	{
		if( !delete_ )
			node_.release();
	}

	virtual XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* getDOMDocument()
	{
		return node_.get();
	}

	virtual void setDOMDocument( XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* node )
	{
		if( !delete_ )
			node_.release();
		node_.reset( node );
	}

	XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* release()
	{
		node_.release();
	}

private:

	BT_Scope_Ptr< XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument > node_;
	bool delete_;
};

_bt_serialize_end

#endif // _Dom_Adapter_H_