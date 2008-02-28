

#ifndef TCPSCAN_H
#define TCPSCAN_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "BOE_Export.H"

struct TCPack;

typedef struct TCPack* TCPackPtr;
/**
 * 初始化DLL，在调用所有函数之前先调它。
 * @return 成功返回0
 */
BT_Export_C int init_TCPack( );

/**
 * 结束
 * @remark 在调用它之后不要在调用任何函数了
 */
BT_Export_C void shutdown_TCPack( );

/**
 * 创建一个TCPack，它包含了所有
 * @return 成功返回对象指针，失败返回0
 * @remark 注意，对于一个TCPack不能同时进行的连接总数不能超过255个所有
 * 的TCPack同时进行的连接总数不能超过系统的总数据( 一般不超过1000个)。
 */
BT_Export_C TCPackPtr createTCPack();

/**
 * 释放TCPack
 * @param[ in ] TCPack 对象指针
 */
BT_Export_C void freeTCPack( TCPackPtr ptr );


enum TCPConnectStatus
{
	/// TCP端口打开
	Tcp_success  
	
	/// TCP端口关闭
	,Tcp_error  

	/// TCP端口连接超时
	,Tcp_timeout

	/// 其它错误
	,Tcp_other
};

/**
 * TCP连接结果的回调句柄
 * 第一个参数为一个TCPConnectStatus值，表示连接的结果
 * 第二个参数为该次连接的ip地址
 * 第三个参数为该次连接的端口号
 */
typedef void (*TCPConnectedHandler )( int ,u_long , u_short );

/**
 * 设置TCP连接结果的回调句柄
 * @param[ in ] ptr TCPack对象指针，它是由createTCPack创建的
 * @param[ in ] handler TCP连接结果的回调句柄
 * @return 成功返回0，失败返回非0
 */
BT_Export_C int setTCPConnectedHandler( TCPackPtr ptr ,TCPConnectedHandler handler );

/**
 * 设置TCP连接结果的回调句柄
 * @param[ in ] ptr TCPack对象指针，它是由createTCPack创建的
 * @param[ in ] ipstr 主机
 * @param[ in ] port 主机端口
 * @return 成功返回0，失败返回非0
 */
BT_Export_C int sendTCPConnectPack_str( TCPackPtr ptr , const char* ipstr, u_short port );

/**
 * 设置TCP连接结果的回调句柄
 * @param[ in ] ptr TCPack对象指针，它是由createTCPack创建的
 * @param[ in ] ipstr 主机
 * @param[ in ] port 主机端口
 * @return 成功返回0，失败返回非0
 */
BT_Export_C int sendTCPConnectPack( TCPackPtr ptr , long ip, u_short port );

/**
 * 取得TCPack对象中当前连接池中的连接状态
 * @param[ in ] ptr TCPack对象指针，它是由createTCPack创建的
 * @param[ in ] milli_seconds 超时时间
 * @return 成功返回0，失败返回<0，超时返回1
 * @remark 注意，如果当前连接池中的连接有返回时，会马上返回0，想得到所有的连接
 * 结果就必须继续调用它，直到返回失败或超时。
 */
BT_Export_C int getTCPConnectStatus( TCPackPtr ptr , u_long milli_seconds );


#endif // TCPSCAN_H