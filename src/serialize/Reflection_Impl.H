
/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - ¤╭⌒╮ ╭⌒╮		            Reflection_Impl.h,v 1.0 2005/03/11 11:33:34
 *  ╱◥██◣ ╭╭ ⌒╮
 * ︱田︱田田| ╰------
 * -------------------------------------------------------------------------------
 */

#ifndef _Reflection_Impl_H_
#define _Reflection_Impl_H_

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "serialize_def.h"

_bt_serialize_begin

/**
 * @brief 反射接口
 * 本类提供了一个可以通字符串来访问类的成员变量的接口
 * 例如有下面一个类 \n
 * struct T { \n 
 * int a; \n
 * int b; \n
 * std::list< int > ls;
 * };\n
 * 你可以通过"T.a"来访问a，通过"T.b"来访问b;
 * 注意本接口不支持链表等容器类,这意味着你不能用"T.ls[0]"来访问ls中第一个值。
 */
class Reflection_Impl
{
public:
	/**
	 * Reflection_Impl deconstruct
	 */
	virtual ~Reflection_Impl() {}

	/**
	 * 取得所有成员变量名列表
	 * @return 成员变量名列表
	 */ 
	virtual const std::list< std::string >& get_MemberName() const = 0;

	/**
	 * 取得一个成员的值(字符串)
	 * @param[ in ] name 成员变量的名称。
	 * @return 成功则取得一个成员的值(字符串)的指针，失败则返回0;
	 */
	virtual const char* get_Member( const char* name ) const = 0;

	/**
	 * 设置一个成员的值(字符串)
	 * @param[ in ] name 成员变量的名称。
	 * @param[ in ] 成员变量的值(字符串)的指针
	 * @return 成功返回true,失败返回false;
	 */
	virtual bool set_Member( const char* name , const char* value ) = 0;
};

_bt_serialize_end

#endif // _XML_Reflection_H_