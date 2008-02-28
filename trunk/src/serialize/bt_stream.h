#pragma once
    //#define SEEK_CUR    1
    //#define SEEK_END    2
    //#define SEEK_SET    0

#include <string>
using namespace std;

class bt_istream
{
public:
	//���ܣ������ж�ȡָ�����ȣ�Len�������ݵ�pBufferForReadָ�����ڴ����
	//���أ�����ֵ��ʾʵ�ʶ�ȡ���ȣ����ʧ����Ϊ0xFFFFFFFF��-1��
	virtual size_t read( void *pBufferForRead, size_t Len ) = 0;

	//���ܣ������Ķ�ȡָ�����õ�ָ��λ��(��start_pos��ʼoffsetλ��)
	//���أ�����ֵ��ʾ��ǰָ��λ�ã����ʧ����Ϊ0xFFFFFFFFFFFFFFFF��-1��
	virtual size_t seek( size_t offset, int start_pos) = 0;
};

class bt_ostream
{
public:
	//���ܣ���pBufferForWriteָ�����ڴ����ָ�����ȣ�Len��������д������
	//���أ�����ֵ��ʾʵ��д�볤�ȣ����ʧ����Ϊ0xFFFFFFFF��-1��
	virtual size_t write( const void *pBufferForWrite, size_t Len ) = 0;




	//���ܣ�������д��ָ�����õ�ָ��λ��(��start_pos��ʼoffsetλ��)
	//���أ�����ֵ��ʾ��ǰָ��λ�ã����ʧ����Ϊ0xFFFFFFFFFFFFFFFF��-1��
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
