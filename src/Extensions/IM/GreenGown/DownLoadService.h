
#ifndef DownLoadService_H
#define DownLoadService_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_GreenGown.H"
#include "../Instance_IM.H"
#include <list>

_greengown_begin


struct URLInfo
{
	URLInfo()
		: type( 0 )
		, length( -1 )
	{
	}
	int type;		// 类型 (目录或文件) ( 1目录，2文件)
	tstring url;	// url
	size_t length;	// 大小
	tstring crc;	// 校验码
};

class DownLoadService
{
public:
	DownLoadService( Instance_IM& instance );
	~DownLoadService( );
	int readFile( const tstring& url, Data_Block_Ptr data, size_t begin, size_t end );
	int readDirectory( const tstring& addr,std::list< URLInfo >& addrs );

	int openFile( const tstring& url ,FILE* &handle );
	tstring realname( const tstring& url );
private:
	std::map< tstring , FILE* > file_cache_;
	Instance_IM& instance_;
};

_greengown_end

#endif // DownLoadService_H