// Communication


#ifndef __JOMOO_Transport__
#define __JOMOO_Transport__

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "Transport_Result.H"

_networks_begin

class JOMOO_Transport;
class JOMOO_Transport_Handler;

typedef counter_ptr< JOMOO_Transport > JOMOO_Transport_Ptr;

class JOMOO_Read_Result : virtual public JOMOO_Transport_Result
{

public:

	typedef JOMOO_Transport_Handler handler_type;
	typedef JOMOO_Transport transport_type;

	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Read_Result(){}

	/**
	 * 取得实际读到的数据块大小
	 * @return 实际读到的数据块大小
	 */
	virtual size_t bytes_to_transferred() const = 0;

	/**
	 * 取得数据块的缓冲
	 * @return 数据缓冲的指针
	 */
	virtual void* buffer() = 0;

	/**
	 * 取得数据块的缓冲
	 * @return 数据缓冲的指针
	 */
	virtual const void* buffer() const = 0;

	/**
	 * 取得数据缓冲的大小
	 * @return 数据缓冲的大小
	 */
	virtual size_t length() const = 0;

	/**
	 * 本次异步操作的回调句柄
	 */
	virtual JOMOO_Transport_Handler& handle() = 0;

	/**
	 * 本次异步操作的transport句柄
	 */
	virtual JOMOO_Transport& transport() = 0;

};// END CLASS DEFINITION JOMOO_Read_Result


class JOMOO_Read_Array_Result : virtual public JOMOO_Transport_Result
{

public:

	typedef JOMOO_Transport_Handler handler_type;
	typedef JOMOO_Transport transport_type;

	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Read_Array_Result(){}

	/**
	 * 取得实际读到的数据块大小
	 * @return 实际读到的数据块大小
	 */
	virtual size_t bytes_to_transferred() const = 0;

	/**
	 * 取得数据缓冲数据组
	 * @return 成功返回数据缓冲数据组的指针，失败返回0
	 */
	virtual iovec* data() = 0;
	
	/**
	 * 取得数据缓冲数据组大小
	 * @return 数据缓冲数据组大小
	 */
	virtual size_t size() const = 0;

	/**
	 * 本次异步操作的回调句柄
	 */
	virtual JOMOO_Transport_Handler& handle() = 0;

	/**
	 * 本次异步操作的transport句柄
	 */
	virtual JOMOO_Transport& transport() = 0;

};// END CLASS DEFINITION JOMOO_Read_Array_Result



class JOMOO_Write_Result : virtual public JOMOO_Transport_Result
{

public:
		
	typedef JOMOO_Transport_Handler handler_type;
	typedef JOMOO_Transport transport_type;

	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Write_Result(){}

	/**
	 * 取得实际发送的数据大小
	 * @return 实际发送的数据大小
	 */
	virtual size_t bytes_to_transferred() const = 0;

	/**
	 * 取得数据块的缓冲
	 * @return 数据缓冲的指针
	 */
	virtual const void* buffer() const = 0;

	/**
	 * 取得数据缓冲的大小
	 * @return 数据缓冲的大小
	 */
	virtual size_t length() const = 0;

	/**
	 * 本次异步操作的回调句柄
	 */
	virtual JOMOO_Transport_Handler& handle() = 0;

	/**
	 * 本次异步操作的transport句柄
	 */
	virtual JOMOO_Transport& transport() = 0;

};// END CLASS DEFINITION JOMOO_Write_Result


class JOMOO_Write_Array_Result : virtual public JOMOO_Transport_Result
{

public:
		
	typedef JOMOO_Transport_Handler handler_type;
	typedef JOMOO_Transport transport_type;

	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Write_Array_Result(){}

	/**
	 * 取得实际读到的数据块大小
	 * @return 实际读到的数据块大小
	 */
	virtual size_t bytes_to_transferred() const = 0;

	/**
	 * 取得数据缓冲数据组
	 * @return 成功返回数据缓冲数据组的指针，失败返回0
	 */
	virtual const iovec* data() = 0;

	/**
	 * 取得数据缓冲数据组大小
	 * @return 数据缓冲数据组大小
	 */
	virtual size_t size() const= 0;

	/**
	 * 本次异步操作的回调句柄
	 */
	virtual JOMOO_Transport_Handler& handle() = 0;

	/**
	 * 本次异步操作的transport句柄
	 */
	virtual JOMOO_Transport& transport() = 0;

};// END CLASS DEFINITION JOMOO_Transmit_Result



class JOMOO_Transmit_Result : virtual public JOMOO_Transport_Result
{

public:
		
	typedef JOMOO_Transport_Handler handler_type;
	typedef JOMOO_Transport transport_type;

	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Transmit_Result(){}

	/**
	 * 取得实际读到的数据块大小
	 * @return 实际读到的数据块大小
	 */
	virtual size_t bytes_to_transferred() const = 0;

	/**
	 * 取得数据缓冲数据组
	 * @return 成功返回数据缓冲数据组的指针，失败返回0
	 */
	virtual const iopack* data() = 0;

	/**
	 * 取得数据缓冲数据组大小
	 * @return 数据缓冲数据组大小
	 */
	virtual size_t size() const= 0;

	/**
	 * 本次异步操作的回调句柄
	 */
	virtual JOMOO_Transport_Handler& handle() = 0;

	/**
	 * 本次异步操作的transport句柄
	 */
	virtual JOMOO_Transport& transport() = 0;

};// END CLASS DEFINITION JOMOO_Transmit_Result


/**
 * @Brief JOMOO_Transport_Handler channel 异步回调接口，@see JOMOO_Transport
 */
class JOMOO_Transport_Handler
{

public:
	typedef counter_ptr< JOMOO_Transport_Handler > ptr_type;
	typedef JOMOO_Read_Result read_result_type;
	typedef JOMOO_Read_Array_Result read_array_result_type;
	typedef JOMOO_Write_Result write_result_type;
	typedef JOMOO_Write_Array_Result write_array_result_type;
	typedef JOMOO_Transmit_Result transmit_result_type;
	typedef JOMOO_Transport transport_type;


	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Transport_Handler(){}

	/**
	 * channel读操作回调接口
	 * @see JOMOO_Read_Result
	 * @see JOMOO_Transport::read
	 */
	virtual void onRead(read_result_type& result) = 0;

	/**
	 * channel读操作回调接口
	 * @see JOMOO_Read_Array_Result
	 * @see JOMOO_Transport::read
	 */
	virtual void onReadArray(read_array_result_type& result ) = 0;

	/**
	 * channel写操作回调接口
	 * @see JOMOO_Write_Result
	 * @see JOMOO_Transport::write
	 */
	virtual void onWrite(write_result_type& result) = 0;

	/**
	 * channel写操作回调接口
	 * @see JOMOO_Write_Result
	 * @see JOMOO_Transport::write
	 */
	virtual void onWriteArray(write_array_result_type& result) = 0;

	/**
	 * channel写操作回调接口
	 * @see JOMOO_Transmit_Result
	 * @see JOMOO_Transport::transmit
	 */
	virtual void onTransmit(transmit_result_type& result ) = 0;

	/**
	 * 取得实例的描述
	 */
	virtual const tstring& toString() const = 0;

};// END CLASS DEFINITION handler_type

class JOMOO_Transport
{
public:

	typedef counter_ptr< JOMOO_Transport > ptr_type;

	typedef NetWorksLoggerPtr LoggerPtr;
	typedef JOMOO_Transport_Handler handler_type;


	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Transport(){}

	/**
	 * 发送一块数据（注意它是异步的  )
	 * @param[ in ] handle 异步回调接口,当数据发送操作（不管成功，失败，撤消）
	 *				调用成功，都会回调handle的onWrite接口
	 * @param[ in ] buffer 待发送的数据块指针
	 * @param[ in ] length 待发送的数据块大小
	 * @param[ in ] act 本次操作的的key
	 * @return 成功调用异步发送则返回true,否则返回false
	 * @remark 注意如果返回成功，并不代表数据被发送，也不代表数据一定会发送成
	 *		   功，但一定会回调handle的onWrite接口，如果返回失败则一定不
	 *		   会调用handle的onWrite接口
	 * @see JOMOO_Transport_Handler
	 */
	virtual bool write(handler_type& handle,
				   const void* buffer,
				   size_t length,
				   void* act ) = 0;

	/**
	 * 发送多块数据（注意它是异步的  )
	 * @param[ in ] handle 异步回调接口,当数据发送操作（不管成功，失败，撤消）
	 *				调用成功，都会回调handle的onTransmit接口
	 * @param[ in ] data 待发送的数据块指针
	 * @param[ in ] size 待发送的数据块个数
	 * @param[ in ] act 本次操作的的key
	 * @return 成功调用异步发送则返回true,否则返回false
	 * @remark 注意如果返回成功，并不代表数据被发送，也不代表数据一定会发送成
	 *		   功，但一定会回调handle的onTransmit接口，如果返回失败则一定
	 *		   不会调用handle的onTransmit接口
	 * @see JOMOO_Transport_Handler
	 */
	virtual bool write(handler_type& handle,
					  const iovec* data,
					  size_t size,
				   void* act ) = 0;
#ifndef ___iopack___
	/**
	 * 发送文件（注意它是异步的  )
	 * @param[ in ] handle 异步回调接口,当数据发送操作（不管成功，失败，撤消）
	 *				调用成功，都会回调handle的onTransmit接口
	 * @param[ in ] data 待发送的数据块指针
	 * @param[ in ] size 待发送的数据块个数
	 * @param[ in ] act 本次操作的的key
	 * @return 成功调用异步发送则返回true,否则返回false
	 * @remark 注意如果返回成功，并不代表数据被发送，也不代表数据一定会发送成
	 *		   功，但一定会回调handle的onTransmit接口，如果返回失败则一定
	 *		   不会调用handle的onTransmit接口
	 * @see JOMOO_Transport_Handler
	 */
	virtual bool transmit(handler_type& handle,
					  const iopack* data,
					  size_t size,
				   void* act ) = 0;
#endif

	/**
	 * 读一块数据（注意它是异步的  )
	 * @param[ in ] handle 异步回调接口,当数据发送操作（不管成功，失败，撤消）
	 *				调用成功，都会回调handle的onRead接口
	 * @param[ in ] buffer 读数据的缓冲指针
	 * @param[ in ] length 读数据的缓冲大小
	 * @param[ in ] act 本次操作的的key
	 * @return 成功调用异步读则返回true,否则返回false
	 * @remark 注意如果返回成功，并不代表读到数据，也不代表一定会读到数据，
	 *		   但一定会回调handle的onRead接口，如果返回失败则一定不会
	 *		   调用handle的onRead接口
	 * @see JOMOO_Transport_Handler
	 */
	virtual bool read(handler_type& handle,
				  void* buffer,
				  size_t length,
				   void* act ) = 0;

	/**
	 * 读多块数据（注意它是异步的  )
	 * @param[ in ] handle 异步回调接口,当数据发送操作（不管成功，失败，撤消）
	 *				调用成功，都会回调handle的onReadArray接口
	 * @param[ in ] data 读数据的缓冲数组的指针
	 * @param[ in ] length 读数据的缓冲数组大小
	 * @param[ in ] act 本次操作的的key
	 * @return 成功调用异步读则返回true,否则返回false
	 * @remark 注意如果返回成功，并不代表读到数据，也不代表一定会读到数据，
	 *		   但一定会回调handle的onReadArray接口，如果返回失败则一
	 *		   定不会调用handle的onReadArray接口
	 * @see JOMOO_Transport_Handler
	 */
	virtual bool read(handler_type& handle,
				  iovec* data,
				  size_t size,
				   void* act ) = 0;

	/**
	 * 设置channel待征
	 * @param[ in ] option 待征名
	 * @param[ in ] value 待征值
	 * @return 成功返加0,不成功返回非 0
	 */
	virtual int setFeature(const char* feature,
						bool value) = 0;

	/**
	 * 取得channel待征
	 * @param[ in ] option 待征名
	 * @param[ in ] value 待征值
	 * @return 成功返加0,不成功返回非 0
	 */
	virtual int getFeature(const char* feature,
						bool& value) const = 0;

	/**
	 * 设置channel选项
	 * @param[ in ] option 选项名
	 * @param[ in ] value 选项值的buffer
	 * @param[ in ] size 选项值的buffer的大小
	 * @return 成功返加0,不成功返回非 0
	 */
	virtual int setOption(const char* option,
					   void* value,
					   size_t size) = 0;

	/**
	 * 取得channel选项
	 * @param[ in ] option 选项名
	 * @param[ in ] value 选项值的buffer
	 * @param[ in/out ] size 选项值的buffer的大小
	 * @return 成功返加0,不成功返回非 0
	 */
	virtual int getOption(const char* option,
					   void* value,
					   size_t& size) const = 0;

	///**
	// * 取得本地地址
	// * @return 本地地址
	// */
	//virtual const JOMOO_INET_Addr& getLocalAddr() const = 0;

	///**
	// * 取得远程地址
	// * @return 远程地址
	// */
	//virtual const JOMOO_INET_Addr& getRemoteAddr() const = 0;

	/**
	 * 撤消当前操作
	 * @return 成功返回true,不成功返回false
	 */
	virtual bool cancel() = 0;

	/**
	 * 取得该通道的日志对象
	 */
	virtual LoggerPtr getLogger() = 0;

	/**
	 * 取得实例的描述
	 */
	virtual const tstring& toString() const = 0;

};// END CLASS DEFINITION JOMOO_Transport



_networks_end

#endif // __JOMOO_Transport__
