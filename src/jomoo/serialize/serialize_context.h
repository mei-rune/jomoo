
#ifndef _serialize_context_h_
#define _serialize_context_h_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_serializing.h"
#include "jomoo/exception.hpp"

_serializing_begin

class serialize_context
{
public:
	virtual ~serialize_context(){};

	/**
	 * 序列化深入一级
	 */
	virtual void push( const tstring& className, const tstring& fieldName) = 0;

	/**
	 * 序列化跳出一级
	 */
	virtual void pop( ) = 0;

	/**
	 * 当前级的类名
	 */
	virtual const tstring& currentClass() const = 0;

	/**
	 * 当前级的字段名
	 */
	virtual const tstring& currentField() const = 0;

	/**
	 * 当前深度
	 */
	virtual size_t depth() const = 0;

	/**
	 * 取得level级的字段名
	 */
	virtual const tstring& getClass( int level ) const = 0;

	/**
	 * 取得level级的类名
	 */
	virtual const tstring& getField( int level ) const = 0;


	/**
	 * 取得当前级中字典中键名为key的值
	 * @remarks 注意取不到时会抛出NotFindException异常
	 */
	virtual const tstring& operator[](const tstring& key) const = 0;


};

_serializing_end

#endif // _serialize_context_h_