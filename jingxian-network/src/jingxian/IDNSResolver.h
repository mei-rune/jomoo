
#ifndef _IDNSResolver_H_
#define _IDNSResolver_H_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files

_jingxian_begin

struct IPHostEntry
{
	//获取或设置与主机关联的 IP 地址列表。 
	std::vector<tstring> AddressList;
	//获取或设置与主机关联的别名列表。 
	std::vector<tstring> Aliases;
	//获取或设置主机的 DNS 名称。 
	tstring HostName 
};

typedef void (*ResolveHost)(const tstring& name, const IPHostEntry& hostEntry, void* context);
typedef void (*ResolveError)(const tstring& name, void* context);

class IDNSResolver
{
public:

	virtual ~IDNSResolver(){}

	/**
	 * 开始异步请求关于指定 DNS 主机名的 IPHostEntry 信息。
	 */
	virtual void ResolveHostByName(const tstring& name, void* context, IReactorCore* port, ResolveHost callback, ResolveError onError, int timeout);
};

_jingxian_end

#endif // _IDNSResolver_H_
