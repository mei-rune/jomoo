#pragma once
    //#define SEEK_CUR    1
    //#define SEEK_END    2
    //#define SEEK_SET    0

#include <string>
using namespace std;

class bt_istream
{
public:
	//功能：从流中读取指定长度（Len）的数据到pBufferForRead指定的内存块中
	//返回：返回值表示实际读取长度，如果失败则为0xFFFFFFFF（-1）
	virtual size_t read( void *pBufferForRead, size_t Len ) = 0;

	//功能：将流的读取指针重置到指定位置(从start_pos开始offset位置)
	//返回：返回值表示当前指针位置，如果失败则为0xFFFFFFFFFFFFFFFF（-1）
	virtual size_t seek( size_t offset, int start_pos) = 0;
};

class bt_ostream
{
public:
	//功能：将pBufferForWrite指定的内存块中指定长度（Len）的数据写入流中
	//返回：返回值表示实际写入长度，如果失败则为0xFFFFFFFF（-1）
	virtual size_t write( const void *pBufferForWrite, size_t Len ) = 0;




	//功能：将流的写入指针重置到指定位置(从start_pos开始offset位置)
	//返回：返回值表示当前指针位置，如果失败则为0xFFFFFFFFFFFFFFFF（-1）
	virtual size_t seek( size_t offset, int start_pos) = 0;

};

inline bool read( bt_istream& istm_, char& ch)
{
	return istm_.read( &ch, sizeof(ch) ) == sizeof(ch);
}
inline bool read( bt_istream& istm_, string& line, char& end_char, const string& end_chars = "\n" )
{
	int  len = 0;
	end_char = 0;
	size_t off = 0;
	char ch;
	while( true )
	{
		if ( !read(istm_, ch) )
			break;
		len ++;
		if ( (off=end_chars.find(ch)) != -1 )
		{
			end_char = end_chars[off];
			break;
		}
		if ( ch != '\r' )
			line.append( 1, ch);
	}
	return len > 0;
}
