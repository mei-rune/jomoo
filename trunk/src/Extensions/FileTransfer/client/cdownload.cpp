// cdownload.cpp: implementation of the cdownload class.
//
//////////////////////////////////////////////////////////////////////
//*************************************************************
//���ߣ�����
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//��ҳ��http://h2osky.126.com
/********************************************************/
#include "stdafx.h"
#include "client.h"
#include "cdownload.h"
#include "MainFrm.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define SERVER_PORT 3962
#define SIZE_OF_zmfile 1080//���ڴ˺�Ķ��壬��server1��Ŀ��
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//�����ǣ����������ļ��б�List�ؼ��е�ǰ�б����������
cdownload::cdownload(int thno1)
{
	m_fname="zm.zip";
	m_index=-1;

	doinfo.totle=0;
	doinfo.threadno=thno1;
}

cdownload::~cdownload()
{

}

//�ڿ�ʼ����֮ǰ�����������������ÿ������ļ��б�������Ա��ÿͻ���֪������Щ�ļ������ء� 
//�����ҵ��������ҷ��֣�ԭ����������Ǹ������˵Ķ�����������û�õ�ѽ��������
int cdownload::sendrequest(int n)
{
	//��ȡ��������Ϣ
	sockaddr_in local;
	//���׽���
	SOCKET m_socket;
	int rc=0;
	//��ʹ����������ַ
	local.sin_family=AF_INET;
	local.sin_port=htons(SERVER_PORT);
	local.sin_addr.S_un.S_addr=inet_addr(g_csIP);
	//socket�����ĵ�����������Ĭ��ֵ��0����ʾ�ɳ�������ݵ�ַ��ʽ���׽������ͣ��Զ�ѡ��һ�����ʵ�Э�顣
	m_socket=socket(AF_INET,SOCK_STREAM,0);
	int ret;
	//���ӷ�����
	ret=connect(m_socket,(LPSOCKADDR)&local,sizeof(local));
	//�д�Ļ�
	if(ret<0)
	{
		AfxMessageBox("���Ӵ���");
		closesocket(m_socket);
		return -1;
	}
	//��ʹ������
	fileinfo fileinfo1;
	fileinfo1.len=n;
	fileinfo1.seek=50;
	fileinfo1.type=1;
	//��������
	int aa=sendn(m_socket,(char*)&fileinfo1,100);
	if(aa<0)
	{	
		closesocket(m_socket);
		return -1;
	}
	//���շ�������������Ϣ
	aa=readn(m_socket,(char*)&fileinfo1,100);
	if(aa<0)
	{
		closesocket(m_socket);
		return -1;
	}

	//�ر�
	shutdown(m_socket,2);
	closesocket(m_socket);
	return 1;
}

//����������ִ�������ļ������ĺ���,�Ǳ�������������ĵĶ����ˣ�����
//�����ǣ�cdownload���m_index��Ա��ֵ��������Ϊfilerange��good������±꣬��������Ϊ
//�����ļ����ļ�����׺�����һ���ַ���
UINT cdownload::threadfunc(long index)
{
	//��ʹ������
	sockaddr_in local;
	SOCKET m_socket;
	int rc=0;
	local.sin_family=AF_INET;
	local.sin_port=htons(SERVER_PORT);
	local.sin_addr.S_un.S_addr=inet_addr(g_csIP);
	//socket�����ĵ�����������Ĭ��ֵ��0����ʾ�ɳ�������ݵ�ַ��ʽ���׽������ͣ��Զ�ѡ��
	//һ�����ʵ�Э�顣
	m_socket=socket(AF_INET,SOCK_STREAM,0);
	int ret;
	//����һ�������뻺����������С��20
	char* m_buf=new char[SIZE];
	//remanent�зŵ��ǣ�Ҫ���ص���һ���ļ��У���û�б����ص��ֽ�����Ҳ����ʣ����ֽ�����
	int remanent,len2;
	fileinfo fileinfo1;
	//���ӷ������ˡ�
	ret=connect(m_socket,(LPSOCKADDR)&local,sizeof(local));

	//������̵߳�������Ϣ��
	fileinfo1.seek=filerange[index*2];//���ļ���seek��λ�á�

	fileinfo1.len=filerange[index*2+1];//Ҫ���ص���һ���ļ��ĳ��ȡ�
	remanent=fileinfo1.len;

	//�����������˵���Ϣ�У�type=2����ʾҪ�������ļ��е�һ�Ρ�(Ŀǰ����������ʶ���type������ֻ��0��2������)
	fileinfo1.type=2;
	//����ֶΣ�����ǡ��������ļ��б��е�����������������Ӧ��������±ꡣ
	fileinfo1.fileno=doinfo.threadno;

	//destination  n.Ŀ�ĵ�(Ŀ��,ָ��)
	CFile destFile;//��������Ҫ���ص��ļ������ݵ��ļ����ǡ�Ŀ���ļ�����
	FILE* fp=NULL;

	//�����m_fname�ļ�ʧ�ܣ�˵�����ļ��������ڣ�Ҳ����˵�����ǵ�һ�����ء�
	if((fp=fopen(m_fname,"r"))==NULL)
		//ָ����CFile::modeCreate��ǣ���ʾһ��Ҫ�������ļ���
		//���Ժ��֣�m_fname�зŵľ���Ҫ���ص��ļ����������ļ�����
		//ע�⣺�ļ�����Ҫ��CFile::shareDenyNone�ķ�ʽ�򿪣�ֻ������������ʵ�ֶ���߳�ͬʱ
		//�򿪴��ļ���
		destFile.Open(m_fname, CFile::modeCreate|CFile::modeWrite|CFile::typeBinary|CFile::shareDenyNone);
	//������ļ��Ѿ������ˣ���˵��������һ�����������ش��ļ��ġ��߳������У�������������
	else
	{
		//��һ��������Ҫ���ϣ��������������ļ�֮�󣬲��ҿͻ��˳���û���˳�������£���
		//����ɾ�����ƶ������������ص��ļ�����Ϊfopen���������ļ���������ر��ļ������ļ�
		//�ͻᱻ����ס��
		fclose(fp);//added by yjk 
		destFile.Open(m_fname,CFile::modeWrite | CFile::typeBinary|CFile::shareDenyNone);
	}

	//�ļ�ָ���Ƶ�ָ��λ�ã��Ǵ��ļ��Ŀ�ʼλ�ÿ�ʼƫ�Ƶġ�
	destFile.Seek(filerange[index*2],CFile::begin);
	//����Ϣ���������������������Դ��ļ��ˡ���
	sendn(m_socket,(char*)&fileinfo1,100);
	CFile myfile;//����һ�������ļ������ԡ�.down+N��Ϊ�ļ�����׺�ġ�
	CString csTemp;
	CString temp;
	temp.Format(".down%d",index);
	//�γ���һ���������ز������ļ����ļ�����XX.down+N����
	csTemp=m_fname+temp;
	//���ˡ�XX.down+N���ļ�
	myfile.Open(csTemp,CFile::modeWrite|CFile::typeBinary|CFile::shareDenyNone);
	
	//����û��������һ���ļ���ʱ�򣬾ͼ���ѭ��
	while(remanent>0)
	{
		//SIZE��Ĵ�С��20���ǻ������Ĵ�С��
		//��remanent�зŵ��ǣ�Ҫ���ص���һ���ļ��У���û�б����ص��ֽ�����
		len2=remanent>SIZE?SIZE:remanent;
		//�ӷ������˶�ȡlen2��ô������ݡ�
		int len1=readn(m_socket,m_buf,len2);
		//����������ݵ�ʱ����������
		if(len1==SOCKET_ERROR)
		{
			closesocket(m_socket);
			break;
		}
		//���ոճɹ�������������һ�����ݣ�д�뵽��Ŀ���ļ����С�
		destFile.Write(m_buf, len1);	

		//����Ҫ���ص���һ���ļ��ĳ��ȣ���ȥ�Ѿ����������˵Ĳ��֡�
		filerange[index*2+1]-=len1;
		//ǰ�����ļ���seek��λ�ã�Ҳ���ǰ��Ѿ����������˵���һ�����Ƶ��ˡ�
		filerange[index*2]+=len1;
		//�ƶ����ļ�ָ�롱�������ļ��Ŀ�ͷλ�á�
		myfile.Seek(0,CFile::begin);
		//����ǰ���������д�뵽�����ļ��У��Ա��Ժ�ʵ�ֶϵ��������ܡ�
		myfile.Write(&filerange[index*2],sizeof(int));
		myfile.Write(&filerange[index*2+1],sizeof(int));
		//��ȥ���ѭ������ȡ�����ݵĳ��ȡ�
		remanent=remanent-len1;
		//totle�ֶεĺ��壺Ҫ�����ص��ļ����У��Ѿ������˵��ֽ�����
		//�ԣ���������һ��֮�󣬾���Ҫ�������ص���һ�ε��ֽ�������ȥ��
		doinfo.totle=doinfo.totle+len1;
	};

	//Ҫ���ص��ļ���Ƭ����������ˣ�����β������
	myfile.Close();//�رո����ļ���
	destFile.Close();//�ر�Ŀ���ļ���
	delete [] m_buf;//ɾ�������ӷ������˽������ݵĻ�������
	shutdown(m_socket,2);//�ر�����socket��

	//The shutdown function does not close the socket. Any resources attached to the socket will not be freed until closesocket is invoked.
	closesocket(m_socket);//added by yjk 

	//���ʣ����ֽ���<=0����
	if(remanent<=0)
		good[index]=TRUE;//��Ϊtrue����ű�ʾ���ļ�����һ���Ѿ����ɹ����������ˡ�
	return 1;
}

//��ʼ�����û�ѡ�е��Ǹ��������ص��ļ�����
//�����ǣ�Ҫ���ص��ļ����±�������
int cdownload::startask(int n)
{
	//�����ļ�����
	doinfo.filelen=zmfile[n].length;
	//�����ļ���
	m_fname=zmfile[n].name;

	//�������巢��Ϣ
	CString aaa;
	aaa="���ڶ�ȡ "+m_fname+" ��Ϣ�����Ͽ�ʼ���ء�����\n";
    AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
	aaa.ReleaseBuffer();

	//����ļ�����С��0���� ����-1
	if(doinfo.filelen<=0)
		return -1;

	//��һ����.down��β���ļ���������¼�ļ���Ϣ
	CString csTemp;
	csTemp=m_fname+".down";
	//������.down��β���ļ�֮����
	doinfo.name=csTemp;
	FILE* fp=NULL;
	CFile myfile;

	//Run-Time Library Reference  fopen, _wfopen  Open a file.
	//The character string mode specifies the type of access requested for the file, as follows: 
	//"r"  Opens for reading. If the file does not exist or cannot be found, the fopen call fails. 
	//Return Value  Each of these functions returns a pointer to the open file. A null pointer value indicates an error. 
	//�����r�ķ�ʽ��XX.down�ļ�ʧ�ܣ���˵�����ļ������ڣ��Ӷ�˵�����ǵ�һ�����ش��ļ���
	//���Ǿͣ���ʹ����Ӧ�ڸ��������̵߳ĸ����ļ���
	if((fp=fopen(csTemp,"r"))==NULL)
	{
		//added by yjk begin
		//����Ҫ���ص��ļ��Ƿ��Ѿ������ˣ�������Ѿ������ˣ�����Ҫѯ��һ���û����Ƿ�Ҫ
		//�������أ�����û�ѡ���������أ���ɾ��ԭ�����ļ���
		if((fp=fopen(m_fname,"r"))!=NULL)
		{
			fclose(fp);
			//����û������������أ��ͷ���2����ֹ������ز�����
			if(::MessageBox(NULL,"ͬ�����ļ��Ѿ������ˣ����ѡ���ǡ�������ԭ�����ļ������Ƿ�Ҫ���ش��ļ���"," YJK �����û�",MB_YESNO|MB_ICONQUESTION)==IDNO)
				return 2;
			//ɾ��ԭ�����ļ����������͸���ǰ��û�����ع����ļ�һ���ˡ�
			DeleteFile(m_fname);
		}
		//added by yjk end

		//�����Ѿ���filerange[0]�趨Ϊ0�ˣ����ʾ�������е�Ԫ�ص�ֵ�Ǵ�0��ʼ�ġ�
		filerange[0]=0;
		//�ļ��ֿ�
		//BLOCK��ֵΪ4����ô���Ǵ�0��3����ѭ���ˡ������ļ��ĳ���Ϊ203����ô
		//��doinfo.filelen/BLOCK���͵���50�ˡ�
		for(int i=0;i<BLOCK;i++)
		{
			if(i>0)
				//��i==1��ʱ��filerange[2]=50;
				//��i==2��ʱ��filerange[4]=100;
				//��i==3��ʱ��filerange[6]=150;
//				filerange[i*2]=i*(doinfo.filelen/BLOCK+1);//����1����Ϊ�˷�ֹ����������doinfo.filelen/BLOCK==0���������ʱ�����г���
				filerange[i*2]=i*(doinfo.filelen/BLOCK);//added by yjk
			//��i==0��ʱ��filerange[1]=50;
			//��i==1��ʱ��filerange[3]=50;
			//��i==2��ʱ��filerange[5]=50;
			//��i==3��ʱ��filerange[7]=50;
//			filerange[i*2+1]=doinfo.filelen/BLOCK+1;//
			filerange[i*2+1]=doinfo.filelen/BLOCK;//added by yjk
		}
		//��filerange[4*2-1]=200-filerange[4*2-2]; �ɵã�filerange[7]=203-150��������Ǹ�
		//filerange[7]����һ����ֵ53(ԭֵҲ��50)��֮������Ҫ������һ����룬����Ϊ
		//doinfo.filelen���ܲ����ܱ�BLOCK��ȫ���������ԣ��ļ��ֶε�ʱ�򣬻���һЩ�����ԣ�
		//��Ҫ��������һ���У���������������ķ����ܼ򵥣�����ǰ��ļ��ζ���������
		//֮����ʣ�µ��ֽ������������һ�εĳ����ˡ�
		//����Ϊ���������������һ�䣬��ô������ȫ���Բ��ü�1�ˣ�������
		//doinfo.filelen/BLOCK==0���������ʱ��ǰ�����̶߳εĳ��ȶ���0�������һ�εĳ���
		//�����ļ���ʵ�ʵĳ��ȡ�
		filerange[BLOCK*2-1]=doinfo.filelen-filerange[BLOCK*2-2];

		//�����Ǹ���.down��β�ĸ����ļ���
		//CFile::modeCreate   Directs the constructor to create a new file. If the file exists already, it is truncated to 0 length. 
		//CFile::modeWrite   Opens the file for writing only.
		myfile.Open(csTemp,CFile::modeCreate|CFile::modeWrite | CFile::typeBinary);

		//��Ҫ���ص��ļ��ġ��ļ����ȡ�д�������.down��β�ĸ����ļ��С�
		myfile.Write(&doinfo.filelen,sizeof(int));
		//�ر������.down��β�ĸ����ļ���
		myfile.Close();

		CString temp;
		//BLOCK��ֵΪ4����ô���Ǵ�0��3����ѭ���ˣ���ѭ��4�Ρ�
		for(int ii=0;ii<BLOCK;ii++)
		{
			//��ʹ�������̼�¼�ļ���Ϣ���� .down+N ��β��
			temp.Format(".down%d",ii);
			//ע�⣺�Ĵ�ѭ���У�csTemp�����ݷֱ�Ϊ��XX.down0,XX.down1,XX.down2,XX.down3
			csTemp=m_fname+temp;

			//����һ���ԡ�.down+N����β�ĸ����ļ������ڲ��õ���CFile::modeCreate��
			//��ʽ�򿪵��ļ������ԣ�������һ�����ļ��������ǰ��Ѵ��ڵ��ļ��ĳ�����Ϊ0��
			myfile.Open(csTemp,CFile::modeCreate|CFile::modeWrite | CFile::typeBinary);

			//�������߳�����Ҫ���ص��ļ�����Ϣд�뵽��Ӧ�ĸ����ļ��С�
			//һ��д����������Ԫ�أ��ֱ��ǣ�0,1 ; 2,3 ; 4,5 ; 6,7 ;
			//����ʹ�õķ����ǣ�ÿ��������Ԫ��һ�飬��һ��Ԫ��
			//�е�ֵ�ǣ����ļ���seek�õģ����ڶ���Ԫ�ص�ֵ��ʾ����һ���ļ��ĳ��ȡ���Ϊ��
			//���߳���������ԣ�һ���������ļ�Ҫ�ֳɼ��Σ��ֱ����ء�
			myfile.Write(&filerange[ii*2],sizeof(int));
			myfile.Write(&filerange[ii*2+1],sizeof(int));
			//�ر�������ԡ�.down+N����β�ĸ����ļ���
			myfile.Close();

/*			CString temp;
			temp.Format("the seek is %d,the len is %d",filerange[ii*2],filerange[ii*2+1]);
			AfxMessageBox(temp);//��һ���ǵ��Դ���		 */
		}
		//���Ǹ���ʾ���ļ����ؽ��ȡ���List�ؼ��У����һ����Ϣ��
		((CMainFrame*)::AfxGetMainWnd())->m_work.m_ListCtrl->AddItemtwo(n,2,0,0,0,doinfo.threadno);
	}
	//���򣬾�˵��XX.down�ļ��Ѿ������ˣ���˵����β���Ӧ����(�ϵ�)������������������ǣ�
	//���ϴ����ص���Ϣ�������������ء�
	else
	{
		//The fread function reads up to count items of size bytes from the input stream and stores them in buffer.
		//��fp�ļ��ж�ȡ1�����ݿ�(һ��int�����ĳ���)���ŵ�&doinfo.filelen�������С�
		fread(&doinfo.filelen,sizeof(int),1,fp);
		//�������ݣ���Ӧ�ùرմ�XX.down�ļ������ߵĴ�������ȷ�ġ�
		fclose(fp);

		//�������һ�δ�������Ѿ�ûʲô���ˣ�����ȥ���ˡ�
		CString temp;
		csTemp=m_fname+".down0";
		//���XX.down0�ļ���������(���سɹ�֮�����е�XX.downX�ļ����ᱻɾ����)����
		//˵���ļ��Ѿ����ɹ����������ˣ�����1��
		if((fp=fopen(csTemp,"r"))==NULL)
			return 1;
		else 
			fclose(fp);


		//�˱�������������Ҫ���ص��ܵ���������
		int bb;
		//��ʼ��Ϊ0
		bb=0;
		//�Ӹ����ļ��ж�ȡ���̵߳�������Ϣ����ȡ����Ϣ��ŵ�filerange�����С�
		for(int ii=0;ii<BLOCK;ii++)
		{
			temp.Format(".down%d",ii);
			csTemp=m_fname+temp;
			myfile.Open(csTemp,CFile::modeRead | CFile::typeBinary);
			myfile.Read(&filerange[ii*2],sizeof(int));//seekֵ
			myfile.Read(&filerange[ii*2+1],sizeof(int));//��Ҫ���ص��ļ��εĳ���
			myfile.Close();
			//���ۼӵķ�����������Ҫ���ص��ܵ���������
			bb=	bb+filerange[ii*2+1];
			CString temp;
			temp.Format(" aa the seek is %d,the len is %d",filerange[ii*2],filerange[ii*2+1]);
		}
		//�����Ҫ���ص��ܵ�������Ϊ0����
		if(bb==0)
			return 1;
		//.totle�д�ŵ��ǣ�Ҫ�����ص��ļ��У��Ѿ����������˵��ֽ�����
		doinfo.totle=doinfo.filelen-bb;
		temp.Format("the value is %d,totle is %d,filelen is %d",BLOCK,doinfo.totle,doinfo.filelen);
		temp.Format("the totle is %d,filelen is %d",doinfo.totle,doinfo.filelen);
		((CMainFrame*)::AfxGetMainWnd())->m_work.m_ListCtrl->AddItemtwo(n,2,doinfo.totle,1,0,doinfo.threadno);
	}

	//����һ�����̣߳�����ʾ���ļ������̵߳�"���ؽ���"����Ϣ��
	DWORD dwthread;
	//�̺߳�����timethread�����ݸ��̺߳����Ĳ�����thisָ�롣
	::CreateThread(NULL,0,timethread,(LPVOID)this,0,&dwthread);

	return 0;
}

//������������type=0������(���߳�֮Ϊ��LIST����)���Ի�ȡ�����Ͽ����ص��ļ���Ϣ�б�
int cdownload::SendListCmd()
{
	sockaddr_in local;
	SOCKET socket1;
	int rc=0;
	local.sin_family=AF_INET;
	local.sin_port=htons(SERVER_PORT);
	local.sin_addr.S_un.S_addr=inet_addr(g_csIP);
	//create a stream socket.
	//socket�����ĵ�����������Ĭ��ֵ��0����ʾ�ɳ�������ݵ�ַ��ʽ���׽������ͣ��Զ�ѡ��һ�����ʵ�Э�顣
	socket1=socket(AF_INET,SOCK_STREAM,0);
	int ret;
	//The connect function establishes a connection to a specified socket.The connect function is used to create a connection to the specified destination. If socket s, is unbound, unique values are assigned to the local association by the system, and the socket is marked as bound.
	//Return Values  If no error occurs, connect returns zero. Otherwise, it returns SOCKET_ERROR, and a specific error code can be retrieved by calling WSAGetLastError.
	ret=connect(socket1,(LPSOCKADDR)&local,sizeof(local));
	if(ret<0)
	{
		CString aaa;
		aaa="�������Ӳ��ϣ�\n";
		//������һ����뽫����CClientView::addmessage��Ϣ�����������á�
		AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
		aaa.ReleaseBuffer();
		closesocket(socket1);
		return -1;
	}

	fileinfo fileinfo1;
	fileinfo1.len=100;
	fileinfo1.seek=50;
	fileinfo1.type=0;//��Ϊ0����ʾ��Ҫ��ȡ�����Ͽ����ص��ļ���Ϣ�б�
	//��Ҫע����ǣ�����ֻ������100���ֽڵ����ݣ���ʵ���ϣ�fileinfo�ṹ�Ĵ�С��116���ֽڣ������Ļ��������Ǹ��ַ�����ͻᱻ��ȥ��һ�������ݡ��������Ϊ�������ַ�����������û���ϰɡ�
	sendn(socket1,(char*)&fileinfo1,100);
	//��ȡ�������˵�zmfile������ȫ��(10��Ԫ��)�����ݣ��ŵ��ͻ��˵�zmfile�����С�
	readn(socket1,(char*)zmfile,SIZE_OF_zmfile);

	//The shutdown function disables sends or receives on a socket.
	shutdown(socket1,2);
	closesocket(socket1);
 
	//��Ϊ�������Ĺ���ǣ�zmfile�����е�һ�����õĿ�Ԫ�ص�.name��Ա��ֵΪ"none"�����ԣ�
	//���zmfile[0].name��������"none"���ͱ����������и�����û�п����ص��ļ�����Ϣ��
	//�����������û���ļ��ɹ����أ���
	if(strcmp(zmfile[0].name,"none")==0)
	{
		CString aaa;
		aaa="������û���ļ������أ�\n";
		AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
		aaa.ReleaseBuffer();
		return -2;
	}

	//����CLT_ON��Ϣ������ܴ��ڣ��������Ϣ�ĺ�����CMainFrame::on ��
	//�����ǣ��������ص��ļ��б���List�ؼ�����ʾ���������ݵ�WPARAM�������ַ������ָ�룬
	//���ǣ����߸�����û�õ�����������ʹ����ȫ�ֱ���zmfileֱ�Ӵ������ݡ�
	::SendMessage(::AfxGetApp()->m_pMainWnd->m_hWnd,CLT_ON,(WPARAM)&zmfile,0);
	return 1;
}

//����߳�
DWORD cdownload::finish1()
{
	//pos��ʾ���Ѿ������˵��ֽ�����ռ�ļ��ܳ��ȵİٷ�֮����
	//pos1��һ��������������¼����pos��������һ��ֵ��
	int pos,pos1;
	//�˱������������㣺ʱ����Ƿ񳬹���1���ӡ�
	int now;
	int totle1;
	//doinfo.totle�д�ŵ��ǣ�������
	//totle1��ֵ�ǣ�Ҫ�����ص��ļ����У��Ѿ������˵��ֽ�����
	totle1=doinfo.totle;
	char* posbye;
	//��Ȼ������new���Ǿ����ڶ��Ϸ���Ļ������ˣ��������˻��������൱��һ��ȫ�ֱ����ˡ�
	posbye=new char[100];
	CString posname;
	//��aaa�����Ǹ�����������������ʾ��now�����Ƿ���Ҫ����ȡ��ǰʱ��ֵ��
	BOOL aaa;
	aaa=1;
	pos1=0;
	//������ѭ��
	while(1)
	{
		if(aaa==1)
		{
			//The GetTickCount function retrieves the number of milliseconds that have elapsed since the system was started. It is limited to the resolution of the system timer. To obtain the system timer resolution, use the GetSystemTimeAdjustment function. 
			//now����ȡ��ǰʱ��ֵ��
			now=GetTickCount();
			aaa=0;
		}

		//���ʱ������1000���룬��
		if(GetTickCount()-now>1000)
		{
			//doinfo��cdownload��ĳ�Ա����������Ȼ�ˣ��Դ˱�����ֵ���޸ģ����ڱ�ĵط�����
			//�������ڱ������С�
			totle1=doinfo.totle-totle1;
			//obviously,����totle1��ֵ�ǣ�һ���������ص��ֽ�����
			posname.Format("%d K/s",totle1/1000);
			//������posbye�����е������ǣ�XXX k/s ��Attention��������ʱ��ǰ��ճ���20���ֽڡ�
			strcpy(&posbye[20],posname.GetBuffer(0));
			//ʹtotle1��ֵ���ڣ�Ҫ�����ص��ļ��У��Ѿ������˵��ֽ�����
			totle1=doinfo.totle;
			//doinfo.filelen/100==�ļ��ܳ��ȵ�1/100��
			//posӦ�ñ�ʾ���Ѿ������˵��ֽ�����ռ�ļ��ܳ��ȵİٷ�֮����
			//���ļ��ĳ���С��100�ֽڵ�ʱ��ִ���������һ�����ͻ����
			//��integer divide by zero���Ĵ���
//			pos=doinfo.totle/(doinfo.filelen/100);
			//added by yjk begin
			if(doinfo.filelen>0)
			{
				pos=doinfo.totle*100/doinfo.filelen;
			}
			else
				pos=100;
			//added by yjk end
			if(pos>pos1)
			{
				posname.Format("%d k",doinfo.totle/1000);
				//��һ�Σ��ǿ�����posbye�����еĿ�ͷλ�ô��ˡ�
				strcpy(posbye,posname.GetBuffer(0));
				//posname����������ֵ��|����
				posname="|";
				while(pos>0)
				{
					//�������������������һ����|����ʾ�����ٷֵ㡣
					posname=posname+'|';
					pos-=2;
				}
			}
			else
			{
				posname="zm";//��������Ϊ"zm"��������������õġ�
			}

			pos1=pos;
			//��һ�ο��������Ǵ�posbye[40]���λ�ÿ�ʼ�����ģ�ǰ��ճ���40���ֽڡ�
			strcpy(&posbye[40],posname.GetBuffer(0));
			//�������ڷ���CLT_ONSETWO��Ϣ���������Ϣ����CMainFrame::OnSetwo������
			AfxGetMainWnd()->SendMessage(CLT_ONSETWO,(WPARAM)&doinfo.threadno,(LPARAM)posbye);
			//����Ѿ������˵��ֽ���>=�ļ��ĳ��ȣ��ͱ�ʾ�ļ��Ѿ��������ˣ����ǾͿ��Է����ˡ�
			if(doinfo.totle>=doinfo.filelen)
				return 1;//Ψһ��������ѭ���ĵط���

			//���˱�����Ϊ1����ʾ��now������Ҫ����ȡ��ǰʱ��ֵ�ˡ�
			aaa=1;
		}

		Sleep(100);//��Ȼ��������ʾ���ؽ��ȵĺ�������û��Ҫִ�е���ôƵ��������˯һ�����
	}
	return 1;
}

//
void cdownload::createthread()
{
	
}
