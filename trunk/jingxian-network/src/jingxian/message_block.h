
#ifndef _message_block_h_
#define _message_block_h_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include <jingxian/exception.hpp>
# include <jingxian/string/string.hpp>


_jingxian_begin

enum MessageFlags
{

	DONT_DELETE = 01,
	USER_FLAGS = 0x1000

};

/**
 *
 */
class data_block
{
public:
	/**
	 * 注意这里的tallocator是用来分内部数据块的，不是分配它本身;
	 */
	data_block( size_t len = 1024 );

	/**
	 * @remarks 注意，如果flag指定自动删除，则一定要指定allocator，否则
	 * 会试图调用默认的allocator来删除同msg_data.
	 */
	data_block( char* msg_data, size_t len , MessageFlags flag = DONT_DELETE );

	~data_block();

	char *base (void);

	const char *base (void) const;

	char *end (void);

	const char *end (void) const;

	size_t size (void) const;

	/**
	 *
	 */
	int size (size_t length);

	char* reset( size_t size );

	/**
	* 取得内存块的大小
	* @return 成功返回内存块大小，不成功返回< 0
	*/
	size_t capacity (void) const;

private:

	data_block( const data_block& ref );

	data_block& operator=( const data_block& ref );

	/// Current size of message block.
	size_t cur_size_;

	/// Total size of buffer.
	size_t max_size_;

	/// Pointer To beginning of message payload.
	char *base_;

	/// Misc flags (e.g., DONT_DELETE and USER_FLAGS).
	MessageFlags flags_;
};

class message_block
{
public:
	/**
	 * message_block constructor
	 * @param[ in ] len 缓存大小
	 */
	message_block( size_t len = 1024 );

	/**
	 * message_block constructor
	 * 本构造函数用于，接收一个数据包，
	 * @param[ in ] buf 数据包块的指针
	 * @param[ in ] len 数据包块的长度
	 * @param[ in ] flag 是否要删除msg_data指向的数据包块
	 * @remarks 注意，如果flag指定自动删除，则一定要指定allocator，否则
	 * 会试图调用默认的allocator来删除同msg_data.
	 */
	message_block( char* msg_data, size_t len , MessageFlags flag = DONT_DELETE  );

	/**
	 * message_block constructor
	 * 本构造函数用于，接收一个data_block包，
	 * @param[ in ] data data_block包块的指针
	 * @param[ in ] flag 是否要删除data_block包
 	 * @remarks 注意，如果flag指定自动删除，则一定要指定allocator，否则
	 * 会试图调用默认的allocator来删除同msg_data.
	 */
	message_block( data_block* data , MessageFlags flag = DONT_DELETE );

	/**
	 * message_block destructor
	 */
	~message_block();
	
	/**
	 * 重设内存块大小
	 * @param[ in ] size 新内存块大小
	 * @return 成功返回数据块，不成功则返回0
	 */
	char* reset( size_t size );

	/**
	 * 取得message_block包的所携带的数据块地址
	 * @return 成功返回数据块地址，不成功则返回0
	 */
	const char* rd_ptr() const;
		
	/**
	 * 将message_block包的所携带的数据块读地址向前移动 size 个字节
	 * @param[ in ] size 向前移动字节数
	 * @return 成功返回数据块读地址，不成功则返回0
	 */
	const char* rd_ptr( size_t size );

	/**
	 * 取得message_block包的所携带的数据块大小
	 * @return 成功返回数据块大小，不成功则返回－1
	 */
	size_t length() const;

	/**
	 * 取得message_block包的所携带的数据块写地址
	 * @return 成功返回数据块写地址，不成功则返回0
	 */
	char* wr_ptr();
	
	/**
	 * 将message_block包的所携带的数据块写地址向前移动 size 个字节
	 * @param[ in ] size 向前移动字节数
	 * @return 成功返回数据块写地址，不成功则返回0
	 * @remarks 如果想获得可写数据块的大小可用  space, 而
	 * 不能用  length;
	 */
	char* wr_ptr( size_t size );

	/**
	 * 将message_block包的所携带的数据块写地址向前移动 size 个字节
	 * @return 成功返回数据块写地址，不成功则返回0
	 */
	size_t space( ) const;

	/**
	 * 将指定大小的数据块拷贝到message_block包的末尾
	 * @param[ in ] buf 数据块指针
	 * @param[ in ] len 数据块大小
	 * @return 成功返回拷贝的字节数，否则返回< 0;
	 */
	size_t copy( const char* buf, size_t len );

	/**
	 * 清空message_block包的所携带的数据块
	 * @return 成功返回数据块写地址，不成功则返回0
	 */
	const char* crunch( );

	/**
	 * 取得内存块的大小
	 * @return 成功返回内存块大小，不成功返回< 0
	 */
	size_t capacity( );

public:

	/**
	 * message_block constructor
	 */
	message_block( const message_block& block );

	/**
	 * operator =
	 */
	message_block& operator=( const message_block& block );

	data_block * data_block_;
	size_t rd_size_;

	MessageFlags flags_;
};

_jingxian_end

#endif // _message_block_h_