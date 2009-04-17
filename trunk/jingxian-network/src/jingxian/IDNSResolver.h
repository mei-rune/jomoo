
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
	//��ȡ������������������ IP ��ַ�б� 
	std::vector<tstring> AddressList;
	//��ȡ�����������������ı����б� 
	std::vector<tstring> Aliases;
	//��ȡ������������ DNS ���ơ� 
	tstring HostName 
};

typedef void (*ResolveHost)(const tstring& name, const IPHostEntry& hostEntry, void* context);
typedef void (*ResolveError)(const tstring& name, void* context);

class IDNSResolver
{
public:

	virtual ~IDNSResolver(){}

	/**
	 * ��ʼ�첽�������ָ�� DNS �������� IPHostEntry ��Ϣ��
	 */
	virtual void ResolveHostByName(const tstring& name, void* context, IReactorCore* port, ResolveHost callback, ResolveError onError, int timeout);
};

_jingxian_end

#endif // _IDNSResolver_H_
