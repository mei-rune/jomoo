
#ifndef _writer_hpp_
#define _writer_hpp_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_serializing.h"

_serializing_begin

class serialize_writer
{
public:
	virtual ~serialize_writer(){};

	/**
	 * 开始反序列化一个结构
	 * @param[ in ] className 结构名字
	 * @param[ in ] field 字段名
	 */
	virtual bool open(serialize_context& context, const tchar* className, const tchar* field) = 0;

	/**
	 * 序列化一个结构结束
	 * @param[ in ] className 结构名字
	 */
	virtual bool close(serialize_context& context) = 0;

	/**
	 * 序列化一个bool型字段
	 * @param[ in ] t 要序列化的字段
	 * @param[ in ] field_name 字段名字
	 */
	virtual bool write(serialize_context& context,  bool t, const tchar* field_name) = 0;

	/**
	 * 序列化一个int8型字段
	 * @param[ in ] t 要序列化的字段
	 * @param[ in ] field_name 字段名字
	 */
	virtual bool write(serialize_context& context,  int8_t t, const tchar* field_name) = 0;

	/**
	 * 序列化一个int16型字段
	 * @param[ in ] t 要序列化的字段
	 * @param[ in ] field_name 字段名字
	 */
	virtual bool write(serialize_context& context,  int16_t t, const tchar* field_name) = 0;

	/**
	 * 序列化一个int32型字段
	 * @param[ in ] t 要序列化的字段
	 * @param[ in ] field_name 字段名字
	 */
	virtual bool write(serialize_context& context,  int32_t t, const tchar* field_name) = 0;

	/**
	 * 序列化一个int64型字段
	 * @param[ in ] t 要序列化的字段
	 * @param[ in ] field_name 字段名字
	 */
	virtual bool write(serialize_context& context,  int64_t t, const tchar* field_name) = 0;

	/**
	 * 序列化一个bool字段
	 * @param[ out ] blob 要序列化的数据块
	 * @param[ in ] len 要序列化的数据块的长度
	 * @param[ in ] field_name 字段名字
	 */
	virtual bool write(serialize_context& context, const void* blob, size_t len, const tchar* field_name = "blob") = 0;

	/**
	 * 流是否正常
	 */
	virtual bool is_good() const = 0;

	/**
	 * 取得最后一次错误描述
	 */
	virtual const tstring& last_error() const = 0;

	/**
	 * 设置最后一次错误描述
	 */
	virtual void last_error( const tstring& err ) = 0;
};

_serializing_end

#endif // _writer_hpp_