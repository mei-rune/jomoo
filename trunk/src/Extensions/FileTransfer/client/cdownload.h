// cdownload.h: interface for the cdownload class.
//
//////////////////////////////////////////////////////////////////////
//#include "MainFrm.h"
//*************************************************************
//���ߣ�����
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//��ҳ��http://h2osky.126.com
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
	//�ļ���Ϣ
	int fileno;//ռ�ĸ��ֽ�
	int type;
	long len;//ռ�ĸ��ֽ�
	int seek;
	char name[100];//ռ100���ֽڡ�
};//�������Ժ��֣��˽ṹ��Ĵ�С��116�ֽڣ�4*4+100=116 ��

struct downinfo
{
	//������Ϣ
	int totle;//Ҫ�����ص��ļ��У��Ѿ����������˵��ֽ�����
    int black;
	int filelen;//�ļ����ȡ�
	int threadno;//���������ļ��б�List�ؼ��е�ǰ�б����������������filedono������±꣬��������zmfile���飬down������±ꡣ��ʵ��������������±�ֵ���Ƕ�Ӧ�ģ��ɻ��á�
	CString name;
};

extern	CString g_csIP;
DWORD WINAPI timethread(LPVOID lpparam);

//����˵������һ������Ҫ���ࡣÿһ�����ص��ļ�������Ӧ��һ�����������(�����down������)
class cdownload  
{
public:
	void		createthread();//���߳�
	DWORD		finish1();//����߳�
	int			SendListCmd();//������1
	downinfo	doinfo;//�ļ���Ϣ����������е��Ǹ��ṹ��Ķ���һ����
	int			startask(int n);//��ʼ���ļ�n

	//�����Ա������������Ϊ�����ļ����̵߳ı�ţ���Ч����Ǵ�0��ʼ�ģ����ԣ�
	//����Ĺ��캯���У��˱�������ʼ��Ϊ-1��֮����Ҫ��0��ʼ��ţ�����Ϊ�����������Ϊ����
	//����(good��filerange)���±��á�
	long		m_index;//ÿһ�������̣߳�����Ӧ�ڴ˱�����һ��ȡֵ(0,1,2,3)��
	//������ʾ���ļ��ĸ�����(ÿ���ζ���һ���̵߳�������)���Ƿ��Ѿ����ɹ������������ˡ�
	BOOL		good[BLOCK];
	//ÿһ�������̣߳�����Ӧ�ڴ������е�����Ԫ�أ�һ������seek����һ�������ļ��εĳ��ȡ�
	int			filerange[100];

	CString		m_fname;//�ļ���
	CString		fnametwo;
	UINT		threadfunc(long index);//���ؽ���

//�ڿ�ʼ����֮ǰ���������������ȡ���������ļ��б�������Ա��ÿͻ���֪���з���������Щ�ļ������ء� 
	int			sendrequest(int n);

				cdownload(int thno1);
	virtual ~	cdownload();

};

#endif // !defined(AFX_CDOWNLOAD_H__9D039885_5200_4E69_A6DF_13A277F53A04__INCLUDED_)
