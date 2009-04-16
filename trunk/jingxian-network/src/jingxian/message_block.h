
#ifndef _mem_block_h_
#define _mem_block_h_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

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
	 * ע�������tallocator���������ڲ����ݿ�ģ����Ƿ���������;
	 */
	data_block( size_t len = 1024 , BT_Memory_Base* alloc_ = 0 );

	/**
	 * @remarks ע�⣬���flagָ���Զ�ɾ������һ��Ҫָ��allocator������
	 * ����ͼ����Ĭ�ϵ�allocator��ɾ��ͬmsg_data.
	 */
	data_block( char* msg_data, size_t len , MessageFlags flag = DONT_DELETE ,BT_Memory_Base* alloc_ = 0 );

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
	* ȡ���ڴ��Ĵ�С
	* @return �ɹ������ڴ���С�����ɹ�����< 0
	*/
	size_t capacity (void) const;

	BT_Memory_Base *allocator( );

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

	BT_Memory_Base* allocator_;
};

class message_block
{
public:
	/**
	 * message_block constructor
	 * @param[ in ] len �����С
	 */
	message_block( size_t len = 1024 , BT_Memory_Base* alloc_ = 0 );

	/**
	 * message_block constructor
	 * �����캯�����ڣ�����һ�����ݰ���
	 * @param[ in ] buf ���ݰ����ָ��
	 * @param[ in ] len ���ݰ���ĳ���
	 * @param[ in ] flag �Ƿ�Ҫɾ��msg_dataָ������ݰ���
	 * @remarks ע�⣬���flagָ���Զ�ɾ������һ��Ҫָ��allocator������
	 * ����ͼ����Ĭ�ϵ�allocator��ɾ��ͬmsg_data.
	 */
	message_block( char* msg_data, size_t len , MessageFlags flag = DONT_DELETE , BT_Memory_Base* alloc_ = 0 );

	/**
	 * message_block constructor
	 * �����캯�����ڣ�����һ��data_block����
	 * @param[ in ] data data_block�����ָ��
	 * @param[ in ] flag �Ƿ�Ҫɾ��data_block��
 	 * @remarks ע�⣬���flagָ���Զ�ɾ������һ��Ҫָ��allocator������
	 * ����ͼ����Ĭ�ϵ�allocator��ɾ��ͬmsg_data.
	 */
	message_block( data_block* data , MessageFlags flag = DONT_DELETE , BT_Memory_Base* allocator_ = 0 );

	/**
	 * message_block destructor
	 */
	~message_block();
	
	/**
	 * �����ڴ���С
	 * @param[ in ] size ���ڴ���С
	 * @return �ɹ��������ݿ飬���ɹ��򷵻�0
	 */
	char* reset( size_t size );

	/**
	 * ȡ��message_block������Я�������ݿ��ַ
	 * @return �ɹ��������ݿ��ַ�����ɹ��򷵻�0
	 */
	const char* rd_ptr() const;
		
	/**
	 * ��message_block������Я�������ݿ����ַ��ǰ�ƶ� size ���ֽ�
	 * @param[ in ] size ��ǰ�ƶ��ֽ���
	 * @return �ɹ��������ݿ����ַ�����ɹ��򷵻�0
	 */
	const char* rd_ptr( size_t size );

	/**
	 * ȡ��message_block������Я�������ݿ��С
	 * @return �ɹ��������ݿ��С�����ɹ��򷵻أ�1
	 */
	size_t length() const;

	/**
	 * ȡ��message_block������Я�������ݿ�д��ַ
	 * @return �ɹ��������ݿ�д��ַ�����ɹ��򷵻�0
	 */
	char* wr_ptr();
	
	/**
	 * ��message_block������Я�������ݿ�д��ַ��ǰ�ƶ� size ���ֽ�
	 * @param[ in ] size ��ǰ�ƶ��ֽ���
	 * @return �ɹ��������ݿ�д��ַ�����ɹ��򷵻�0
	 * @remarks ������ÿ�д���ݿ�Ĵ�С����  space, ��
	 * ������  length;
	 */
	char* wr_ptr( size_t size );

	/**
	 * ��message_block������Я�������ݿ�д��ַ��ǰ�ƶ� size ���ֽ�
	 * @return �ɹ��������ݿ�д��ַ�����ɹ��򷵻�0
	 */
	size_t space( ) const;

	/**
	 * ��ָ����С�����ݿ鿽����message_block����ĩβ
	 * @param[ in ] buf ���ݿ�ָ��
	 * @param[ in ] len ���ݿ��С
	 * @return �ɹ����ؿ������ֽ��������򷵻�< 0;
	 */
	size_t copy( const char* buf, size_t len );

	/**
	 * ���message_block������Я�������ݿ�
	 * @return �ɹ��������ݿ�д��ַ�����ɹ��򷵻�0
	 */
	const char* crunch( );

	/**
	 * ȡ���ڴ��Ĵ�С
	 * @return �ɹ������ڴ���С�����ɹ�����< 0
	 */
	size_t capacity( );

	/**
	 * ȡ�÷�����
	 * @return �ɹ����ط�����ָ�룬���򷵻�0;
	 */
	BT_Memory_Base *allocator( );

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

	BT_Memory_Base* allocator_;
};

_bt_end

#endif // _mem_block_h_