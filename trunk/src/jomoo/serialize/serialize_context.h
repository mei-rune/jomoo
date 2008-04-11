
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

	class string_guard
	{
	public:
		string_guard( serialize_context& context )
			: _context( 0 )
			, _isSequence( false )
		{
			_isSequence = context.isSequenue();
			context.isString( true );
			_context = &context;
		}

		~string_guard()
		{
			if( 0 != _context )
			{
				_context -> isString( false );
				_context -> isSequenue( _isSequence );
				_context = 0;
			}
		}

	private:
		serialize_context* _context;
		bool _isSequence;
	};

	class dictinary_guard
	{
	public:
		dictinary_guard( serialize_context& context )
			: _context( 0 )
			, _isSequence( false )
		{
			_isSequence = context.isSequenue();
			context.isDictinary( true );
			_context = &context;
		}

		~dictinary_guard()
		{
			if( 0 != _context )
			{
				_context -> isDictinary( false );
				_context -> isSequenue( _isSequence );
				_context = 0;
			}
		}

	private:
		serialize_context* _context;
		bool _isSequence;
	};

	
	class sequenue_guard
	{
	public:
		sequenue_guard( serialize_context& context )
			: _context( 0 )
		{
			_isSequence = context.isSequenue( false );
			_context = &context;
		}

		~sequenue_guard()
		{
			if( 0 != _context )
			{
				_context -> isSequenue( false );
				_context = 0;
			}
		}

	private:
		serialize_context* _context;
	};

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

	/**
	 * 当前正在序列化的字段是一个容器
	 * @param[ in ] v 如果v为true则设置当前是容器,否则不是容器
	 */
	virtual void isSequenue( bool v) = 0;

	/**
	 * 当前正在序列化的字段是一个容器
	 * @return 如果返回true则当前是容器,否则不是容器
	 */
	virtual bool isSequenue( ) const = 0;

	/**
	 * 当前正在序列化的字段是字符串
	 * @param[ in ] v 如果v为true则设置当前是字符串,否则不是字符串
	 * @remarks 字符串也被认为是一个容器
	 */
	virtual void isString( bool v) = 0;

	/**
	 * 当前正在序列化的字段是字符串
	 * @return 如果返回true则当前是字符串,否则不是字符串
	 * @remarks 字符串也被认为是一个容器
	 */
	virtual bool isString( ) const = 0;

	/**
	 * 当前正在序列化的字段是字典
	 * @param[ in ] v 如果v为true则设置当前是字典,否则不是字典
	 * @remarks 字符串也被认为是一个容器
	 */
	virtual void isDictinary( bool v) = 0;

	/**
	 * 当前正在序列化的字段是字典
	 * @return 如果返回true则当前是字典,否则不是字典
	 * @remarks 字符串也被认为是一个容器
	 */
	virtual bool isDictinary( ) const = 0;
};

_serializing_end

#endif // _serialize_context_h_