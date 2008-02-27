// cdownload.h: interface for the cdownload class.
//
//////////////////////////////////////////////////////////////////////
//#include "MainFrm.h"
//*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
/********************************************************/
#if !defined(AFX_CDOWNLOAD_H__9D039885_5200_4E69_A6DF_13A277F53A04__INCLUDED_)
#define AFX_CDOWNLOAD_H__9D039885_5200_4E69_A6DF_13A277F53A04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
int readn(SOCKET fd,char *bp,int len);
//extern int totle;
//extern long filelen;
extern char name1[10][255];
//extern int size;
//extern int black;
//extern struct downinfo;
int sendn(SOCKET fd,char *bp,int len);

struct fileinfo
{
	//文件信息
	int fileno;//占四个字节
	int type;
	long len;//占四个字节
	int seek;
	char name[100];//占100个字节。
};//经过测试后发现，此结构体的大小是116字节：4*4+100=116 。

struct downinfo
{
	//下载信息
	int totle;//要被下载的文件中，已经下载下来了的字节数。
    int black;
	int filelen;//文件长度。
	int threadno;//“可下载文件列表”List控件中当前列表项的索引。可用作filedono数组的下标，还可用作zmfile数组，down数组的下标。其实，这三个数组的下标值都是对应的，可互用。
	CString name;
};

extern	CString g_csIP;
DWORD WINAPI timethread(LPVOID lpparam);

//作者说，这是一个很重要的类。每一个下载的文件，都对应于一个此类的数据(存放在down数组中)
class cdownload  
{
public:
	void		createthread();//开线程
	DWORD		finish1();//完成线程
	int			SendListCmd();//发命令1
	downinfo	doinfo;//文件信息（与服务器中的那个结构体的定义一样）
	int			startask(int n);//开始传文件n

	//这个成员变量是用来作为下载文件的线程的编号，有效编号是从0开始的，所以，
	//在类的构造函数中，此变量被初始化为-1。之所以要从0开始编号，是因为这个变量将作为两个
	//数组(good和filerange)的下标用。
	long		m_index;//每一个下载线程，都对应于此变量的一个取值(0,1,2,3)。
	//用来表示：文件的各个段(每个段都用一个线程单独下载)，是否已经被成功地下载下来了。
	BOOL		good[BLOCK];
	//每一个下载线程，都对应于此数组中的两个元素：一个用作seek，另一个用做文件段的长度。
	int			filerange[100];

	CString		m_fname;//文件名
	CString		fnametwo;
	UINT		threadfunc(long index);//下载进程

//在开始传送之前，向服务器发出获取“可下载文件列表”的命令，以便让客户端知道有服务器上哪些文件可下载。 
	int			sendrequest(int n);

				cdownload(int thno1);
	virtual ~	cdownload();

};

#endif // !defined(AFX_CDOWNLOAD_H__9D039885_5200_4E69_A6DF_13A277F53A04__INCLUDED_)
