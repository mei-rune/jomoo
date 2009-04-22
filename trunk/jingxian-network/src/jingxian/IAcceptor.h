
#ifndef _IAcceptor_H_
#define _IAcceptor_H_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "buffer.h"
# include "Dictionary.h"

_jingxian_begin

class IEndpoint;
class IProtocolFactory;

class IAcceptor
{
public:
	virtual ~IAcceptor(){}

	/**
	 * 取得超时时间
	 */
    virtual  time_t timeout () const = 0;

	/**
	 * 监听的地址
	 */
    virtual const IEndpoint& bindPoint() const = 0;

	/**
	 * 停止监听
	 */
    virtual void stopListening() = 0;

	/**
	 * 启动监听
	 * 
	 * @return 启动监听成功返回true, 失败返回false
	 */
    virtual bool startListening() = 0;

	/**
	 * 取得协议工厂
	 */
    virtual IProtocolFactory& protocolFactory() = 0;

	/**
	 * 取得配置字典
	 */
    virtual IDictionary& misc() = 0;

	/**
	 * 取得配置字典
	 */
	virtual const IDictionary& misc() const = 0;

	/**
	* 取得地址的描述
	*/
	virtual const tstring& toString() const = 0;
};


class IAcceptorFactory
{
public:

	virtual ~IAcceptorFactory(){}

	/**
	 * 创建 IAcceptor 对象
	 */
	virtual IAcceptor* createAcceptor(const tchar* endPoint) = 0;

	/**
	 * 取得地址的描述
	 */
	virtual const tstring& toString() const = 0;
};

inline tostream& operator<<( tostream& target, const IAcceptor& acceptor )
{
	target << acceptor.toString();
	return target;
}

inline tostream& operator<<( tostream& target, const IAcceptorFactory& acceptorFactory )
{
	target << acceptorFactory.toString();
	return target;
}

_jingxian_end

#endif //_IAcceptor_H_ 