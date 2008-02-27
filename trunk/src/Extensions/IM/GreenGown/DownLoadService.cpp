#include "StdAfx.h"
#include "DownLoadService.H"
#include "BOE/tstring.h"
#include "BOE/exception.hpp"
#include "BOE/Directory.H"
#include <errno.h>
#include <io.h>
#include <fstream>

_greengown_begin

DownLoadService::DownLoadService( Instance_IM& instance )
: instance_( instance )
{
}

DownLoadService::~DownLoadService( )
{
	std::map< tstring , FILE* >::iterator it = file_cache_.begin();
	for( ; it != file_cache_.end(); it ++ )
	{
		::fclose( it->second );
	}
	file_cache_.clear();
}

int DownLoadService::readFile( const tstring& url, Data_Block_Ptr data, size_t begin, size_t end )
{
	if( begin == end || url.empty() )
		return ERR_PARAMETER;

	std::map< tstring , FILE* >::iterator it = file_cache_.find( url );
	FILE* handle = 0;
	if( it == file_cache_.end() || handle == 0 )
	{
		int r = openFile( url,handle );
		if( r != 0 )
			return r;
	}
	else
	{
		handle = it->second ;
	}
	if( fseek( handle,begin ,SEEK_SET ) != 0 )
		return ERR_SEEKFILE;

	Data_Buffer_Ptr ptr = instance_.getBufferFactory().createBuffer( );
	if( ptr->space() < ( end - begin ) )
		return ERR_LENGTH;
	while( !feof( handle ) )
	{
		size_t numread = fread( ptr->wd_ptr() , sizeof( char ), end - begin , handle );
		ptr->wd_ptr( numread );
		begin += numread;
		if( end == begin )
			return 0;
		if( ferror( handle ) )
		{
			return ERR_READFILE;
		}
	}

	return 0;
}

tstring DownLoadService::realname( const tstring& url )
{
	if( ( _access( url.c_str(), 0 )) != -1 )
		return url;
	if( EACCES == errno )
		return url;


	return url;
}

int DownLoadService::openFile( const tstring& url ,FILE* &handle )
{
	tstring name = realname( url );
	handle = fopen( name.c_str(), "rb" );
	if( handle == 0 )
	{
		if( errno == ENOENT || EINTR == errno )
			return ERR_OBJECT_NOEXIST;
		return ERR_INTERNAL;
	}
	file_cache_[ url ] = handle;
	return 0;
}

int DownLoadService::readDirectory( const tstring& addr,std::list< URLInfo >& addrs )
{
	struct _finddata_t fileinfo;
	tstring name = realname( RemoveLeaf( addr ) );
	intptr_t handle = _findfirst( name.c_str(), &fileinfo );
	if( handle == -1 )
	{
		if( errno == EINVAL )
			return ERR_OBJECT_NOEXIST;
		return 0;
	}
	do
	{
		if( tendwithstr( fileinfo.name, BT_TEXT(".crc") ) == 0 )
			continue;
		URLInfo info;
		if( tendwithstr( fileinfo.name, BT_TEXT(".redirect") ) == 0 )
		{
			try
			{
				std::fstream f( fileinfo.name );
				if( !f )
					continue;
				f >> info.type;
				if( !f )
					continue;
				f >> info.url;
				if( !f )
					continue;
				f >> info.length;
				f >> info.crc;
			}
			catch( std::exception& e )
			{
				tstring s = BT_TEXT( ",处理" );
				s += fileinfo.name;
				s += BT_TEXT("时，发生错误,");
				s += e.what();
				_findclose( handle );
				ThrowException1( RuntimeException ,  s );
			}
			catch( ... )
			{
				tstring s = BT_TEXT( ",处理" );
				s += fileinfo.name;
				s += BT_TEXT("时，发生未知错误");
				_findclose( handle );
				ThrowException1( RuntimeException ,  s );
			}
		}
		else
		{
			if( _A_SUBDIR == fileinfo.attrib )
				info.type = 1;
			else
				info.type = 2;

			info.url = fileinfo.name;
			info.length = fileinfo.size;

			try
			{
				tstring crcname = fileinfo.name;
				crcname += + ".crc";
				std::fstream f( crcname.c_str() );
				if( !f )
					continue;
				f >> info.crc;
			}
			catch( std::exception& e )
			{
				tstring s = BT_TEXT( ",处理" );
				s += fileinfo.name;
				s += BT_TEXT("时，发生错误,");
				s += e.what();

				_findclose( handle );
				ThrowException1( RuntimeException ,  s );
			}
			catch( ... )
			{
				tstring s = BT_TEXT( ",处理" );
				s += fileinfo.name;
				s += BT_TEXT("时，发生未知错误");
				_findclose( handle );
				ThrowException1( RuntimeException ,  s );
			}
		}
		addrs.push_back( info );
	}
	while( _findnext( handle, &fileinfo ) != 0 );
	_findclose( handle );

}


_greengown_end
