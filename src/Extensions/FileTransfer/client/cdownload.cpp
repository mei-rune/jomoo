// cdownload.cpp: implementation of the cdownload class.
//
//////////////////////////////////////////////////////////////////////
//*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
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
#define SIZE_OF_zmfile 1080//关于此宏的定义，见server1项目。
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//参数是：“可下载文件列表”List控件中当前列表项的索引。
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

//在开始传送之前，向服务器发出“获得可下载文件列表”的命令，以便让客户端知道有哪些文件可下载。 
//经过我的搜索，我发现，原来这个函数是个作废了的东西，根本就没用到呀？！！！
int cdownload::sendrequest(int n)
{
	//获取服务器信息
	sockaddr_in local;
	//建套接字
	SOCKET m_socket;
	int rc=0;
	//初使化服务器地址
	local.sin_family=AF_INET;
	local.sin_port=htons(SERVER_PORT);
	local.sin_addr.S_un.S_addr=inet_addr(g_csIP);
	//socket函数的第三个参数的默认值是0，表示由程序本身根据地址格式和套接字类型，自动选择一个合适的协议。
	m_socket=socket(AF_INET,SOCK_STREAM,0);
	int ret;
	//联接服务器
	ret=connect(m_socket,(LPSOCKADDR)&local,sizeof(local));
	//有错的话
	if(ret<0)
	{
		AfxMessageBox("联接错误");
		closesocket(m_socket);
		return -1;
	}
	//初使化命令
	fileinfo fileinfo1;
	fileinfo1.len=n;
	fileinfo1.seek=50;
	fileinfo1.type=1;
	//发送命令
	int aa=sendn(m_socket,(char*)&fileinfo1,100);
	if(aa<0)
	{	
		closesocket(m_socket);
		return -1;
	}
	//接收服务器传来的信息
	aa=readn(m_socket,(char*)&fileinfo1,100);
	if(aa<0)
	{
		closesocket(m_socket);
		return -1;
	}

	//关闭
	shutdown(m_socket,2);
	closesocket(m_socket);
	return 1;
}

//下面是真正执行下载文件操作的函数,是本程序中最最核心的东西了！！！
//参数是：cdownload类的m_index成员的值，用来作为filerange和good数组的下标，还用来作为
//辅助文件的文件名后缀的最后一个字符。
UINT cdownload::threadfunc(long index)
{
	//初使化连接
	sockaddr_in local;
	SOCKET m_socket;
	int rc=0;
	local.sin_family=AF_INET;
	local.sin_port=htons(SERVER_PORT);
	local.sin_addr.S_un.S_addr=inet_addr(g_csIP);
	//socket函数的第三个参数的默认值是0，表示由程序本身根据地址格式和套接字类型，自动选择
	//一个合适的协议。
	m_socket=socket(AF_INET,SOCK_STREAM,0);
	int ret;
	//创建一个“读入缓冲区”，大小是20
	char* m_buf=new char[SIZE];
	//remanent中放的是：要下载的这一段文件中，还没有被下载的字节数，也就是剩余的字节数。
	int remanent,len2;
	fileinfo fileinfo1;
	//连接服务器端。
	ret=connect(m_socket,(LPSOCKADDR)&local,sizeof(local));

	//读入此线程的下载信息。
	fileinfo1.seek=filerange[index*2];//在文件中seek的位置。

	fileinfo1.len=filerange[index*2+1];//要下载的这一段文件的长度。
	remanent=fileinfo1.len;

	//发给服务器端的信息中，type=2，表示要求下载文件中的一段。(目前，服务器能识别的type的类型只有0和2这两种)
	fileinfo1.type=2;
	//这个字段，大概是“可下载文件列表”中的索引，可以用作对应的数组的下标。
	fileinfo1.fileno=doinfo.threadno;

	//destination  n.目的地(目标,指定)
	CFile destFile;//用来保存要下载的文件的数据的文件，是“目标文件”。
	FILE* fp=NULL;

	//如果打开m_fname文件失败，说明此文件并不存在，也就是说：这是第一次下载。
	if((fp=fopen(m_fname,"r"))==NULL)
		//指定了CFile::modeCreate标记，表示一定要创建新文件。
		//调试后发现，m_fname中放的就是要下载的文件的真正的文件名。
		//注意：文件必须要以CFile::shareDenyNone的方式打开，只有这样，才能实现多个线程同时
		//打开此文件。
		destFile.Open(m_fname, CFile::modeCreate|CFile::modeWrite|CFile::typeBinary|CFile::shareDenyNone);
	//如果此文件已经存在了，则说明这是另一个“正在下载此文件的”线程在运行，或者是续传。
	else
	{
		//这一句代码必须要加上，否则，在下载完文件之后，并且客户端程序没有退出的情况下，就
		//不能删除或移动或重命名下载的文件，因为fopen函数打开了文件，如果不关闭文件，则文件
		//就会被锁定住。
		fclose(fp);//added by yjk 
		destFile.Open(m_fname,CFile::modeWrite | CFile::typeBinary|CFile::shareDenyNone);
	}

	//文件指针移到指定位置，是从文件的开始位置开始偏移的。
	destFile.Seek(filerange[index*2],CFile::begin);
	//发消息给服务器，告诉它“可以传文件了”。
	sendn(m_socket,(char*)&fileinfo1,100);
	CFile myfile;//这是一个辅助文件，是以“.down+N”为文件名后缀的。
	CString csTemp;
	CString temp;
	temp.Format(".down%d",index);
	//形成了一个辅助下载操作的文件的文件名“XX.down+N”。
	csTemp=m_fname+temp;
	//打开了“XX.down+N”文件
	myfile.Open(csTemp,CFile::modeWrite|CFile::typeBinary|CFile::shareDenyNone);
	
	//当还没下载完这一段文件的时候，就继续循环
	while(remanent>0)
	{
		//SIZE宏的大小是20，是缓冲区的大小；
		//而remanent中放的是：要下载的这一段文件中，还没有被下载的字节数。
		len2=remanent>SIZE?SIZE:remanent;
		//从服务器端读取len2这么多的数据。
		int len1=readn(m_socket,m_buf,len2);
		//如果接收数据的时候发生错误，则
		if(len1==SOCKET_ERROR)
		{
			closesocket(m_socket);
			break;
		}
		//将刚刚成功下载下来的这一段数据，写入到“目标文件”中。
		destFile.Write(m_buf, len1);	

		//更改要下载的这一段文件的长度，减去已经下载下来了的部分。
		filerange[index*2+1]-=len1;
		//前移在文件中seek的位置，也就是把已经下载下来了的那一部分移掉了。
		filerange[index*2]+=len1;
		//移动“文件指针”到辅助文件的开头位置。
		myfile.Seek(0,CFile::begin);
		//将当前的下载情况写入到辅助文件中，以备以后实现断点续传功能。
		myfile.Write(&filerange[index*2],sizeof(int));
		myfile.Write(&filerange[index*2+1],sizeof(int));
		//减去这次循环所读取的数据的长度。
		remanent=remanent-len1;
		//totle字段的含义：要被下载的文件段中，已经下载了的字节数。
		//对，下载完了一段之后，就需要把新下载的这一段的字节数加上去。
		doinfo.totle=doinfo.totle+len1;
	};

	//要下载的文件的片段下载完成了，做收尾工作。
	myfile.Close();//关闭辅助文件。
	destFile.Close();//关闭目标文件。
	delete [] m_buf;//删除用来从服务器端接收数据的缓冲区。
	shutdown(m_socket,2);//关闭连接socket。

	//The shutdown function does not close the socket. Any resources attached to the socket will not be freed until closesocket is invoked.
	closesocket(m_socket);//added by yjk 

	//如果剩余的字节数<=0，则
	if(remanent<=0)
		good[index]=TRUE;//设为true，大概表示：文件的这一段已经被成功下载下来了。
	return 1;
}

//开始下载用户选中的那个“可下载的文件”。
//参数是：要下载的文件的下标索引。
int cdownload::startask(int n)
{
	//读入文件长度
	doinfo.filelen=zmfile[n].length;
	//读入文件名
	m_fname=zmfile[n].name;

	//给主窗体发消息
	CString aaa;
	aaa="正在读取 "+m_fname+" 信息，马上开始下载。。。\n";
    AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
	aaa.ReleaseBuffer();

	//如果文件长度小于0，则 返回-1
	if(doinfo.filelen<=0)
		return -1;

	//建一个以.down结尾的文件，用来记录文件信息
	CString csTemp;
	csTemp=m_fname+".down";
	//保存以.down结尾的文件之名。
	doinfo.name=csTemp;
	FILE* fp=NULL;
	CFile myfile;

	//Run-Time Library Reference  fopen, _wfopen  Open a file.
	//The character string mode specifies the type of access requested for the file, as follows: 
	//"r"  Opens for reading. If the file does not exist or cannot be found, the fopen call fails. 
	//Return Value  Each of these functions returns a pointer to the open file. A null pointer value indicates an error. 
	//如果以r的方式打开XX.down文件失败，则说明此文件不存在，从而说明这是第一次下载此文件，
	//于是就：初使化对应于各个下载线程的辅助文件。
	if((fp=fopen(csTemp,"r"))==NULL)
	{
		//added by yjk begin
		//看看要下载的文件是否已经存在了，如果是已经存在了，就需要询问一下用户，是否要
		//重新下载，如果用户选择重新下载，将删除原来的文件。
		if((fp=fopen(m_fname,"r"))!=NULL)
		{
			fclose(fp);
			//如果用户不想重新下载，就返回2，终止这次下载操作。
			if(::MessageBox(NULL,"同名的文件已经存在了，如果选择“是”将覆盖原来的文件。你是否还要下载此文件？"," YJK 提醒用户",MB_YESNO|MB_ICONQUESTION)==IDNO)
				return 2;
			//删除原来的文件，这样，就跟以前从没有下载过此文件一样了。
			DeleteFile(m_fname);
		}
		//added by yjk end

		//这里已经把filerange[0]设定为0了，这表示，数组中的元素的值是从0开始的。
		filerange[0]=0;
		//文件分块
		//BLOCK的值为4，那么就是从0至3进行循环了。假设文件的长度为203，那么
		//“doinfo.filelen/BLOCK”就等于50了。
		for(int i=0;i<BLOCK;i++)
		{
			if(i>0)
				//当i==1的时候，filerange[2]=50;
				//当i==2的时候，filerange[4]=100;
				//当i==3的时候，filerange[6]=150;
//				filerange[i*2]=i*(doinfo.filelen/BLOCK+1);//加上1，是为了防止程序在遇到doinfo.filelen/BLOCK==0这种情况的时候，运行出错。
				filerange[i*2]=i*(doinfo.filelen/BLOCK);//added by yjk
			//当i==0的时候，filerange[1]=50;
			//当i==1的时候，filerange[3]=50;
			//当i==2的时候，filerange[5]=50;
			//当i==3的时候，filerange[7]=50;
//			filerange[i*2+1]=doinfo.filelen/BLOCK+1;//
			filerange[i*2+1]=doinfo.filelen/BLOCK;//added by yjk
		}
		//由filerange[4*2-1]=200-filerange[4*2-2]; 可得：filerange[7]=203-150，这等于是给
		//filerange[7]赋了一个新值53(原值也是50)。之所以需要这最后的一句代码，是因为
		//doinfo.filelen可能并不能被BLOCK完全除尽，所以，文件分段的时候，会有一些误差，所以，
		//需要在最后的这一段中，修正这个误差。修正的方法很简单：就是前面的几段都分配完了
		//之后，所剩下的字节数就是这最后一段的长度了。
		//我认为，如果有了这最后的一句，那么，就完全可以不用加1了！当遇到
		//doinfo.filelen/BLOCK==0这种情况的时候，前几个线程段的长度都是0，而最后一段的长度
		//等于文件的实际的长度。
		filerange[BLOCK*2-1]=doinfo.filelen-filerange[BLOCK*2-2];

		//创建那个以.down结尾的辅助文件。
		//CFile::modeCreate   Directs the constructor to create a new file. If the file exists already, it is truncated to 0 length. 
		//CFile::modeWrite   Opens the file for writing only.
		myfile.Open(csTemp,CFile::modeCreate|CFile::modeWrite | CFile::typeBinary);

		//将要下载的文件的“文件长度”写入这个以.down结尾的辅助文件中。
		myfile.Write(&doinfo.filelen,sizeof(int));
		//关闭这个以.down结尾的辅助文件。
		myfile.Close();

		CString temp;
		//BLOCK的值为4，那么就是从0至3进行循环了，共循环4次。
		for(int ii=0;ii<BLOCK;ii++)
		{
			//初使化各进程记录文件信息（以 .down+N 结尾）
			temp.Format(".down%d",ii);
			//注意：四次循环中，csTemp的内容分别为：XX.down0,XX.down1,XX.down2,XX.down3
			csTemp=m_fname+temp;

			//打开了一个以“.down+N”结尾的辅助文件。由于采用的是CFile::modeCreate的
			//方式打开的文件，所以，将创建一个新文件，或者是把已存在的文件的长度设为0。
			myfile.Open(csTemp,CFile::modeCreate|CFile::modeWrite | CFile::typeBinary);

			//将各个线程所需要下载的文件段信息写入到对应的辅助文件中。
			//一次写入两个数组元素，分别是：0,1 ; 2,3 ; 4,5 ; 6,7 ;
			//作者使用的方法是：每两个数组元素一组，第一个元素
			//中的值是：在文件中seek用的；而第二个元素的值表示：这一段文件的长度。因为是
			//多线程下载嘛，所以，一个完整的文件要分成几段，分别下载。
			myfile.Write(&filerange[ii*2],sizeof(int));
			myfile.Write(&filerange[ii*2+1],sizeof(int));
			//关闭了这个以“.down+N”结尾的辅助文件。
			myfile.Close();

/*			CString temp;
			temp.Format("the seek is %d,the len is %d",filerange[ii*2],filerange[ii*2+1]);
			AfxMessageBox(temp);//这一段是调试代码		 */
		}
		//在那个显示“文件下载进度”的List控件中，添加一条信息。
		((CMainFrame*)::AfxGetMainWnd())->m_work.m_ListCtrl->AddItemtwo(n,2,0,0,0,doinfo.threadno);
	}
	//否则，就说明XX.down文件已经存在了，就说明这次操作应该是(断点)续传，具体的做法就是：
	//读上次下载的信息，用来接着下载。
	else
	{
		//The fread function reads up to count items of size bytes from the input stream and stores them in buffer.
		//从fp文件中读取1个数据块(一个int变量的长度)，放到&doinfo.filelen缓冲区中。
		fread(&doinfo.filelen,sizeof(int),1,fp);
		//读完数据，就应该关闭此XX.down文件，作者的代码是正确的。
		fclose(fp);

		//下面的这一段代码好像已经没什么用了，可以去掉了。
		CString temp;
		csTemp=m_fname+".down0";
		//如果XX.down0文件并不存在(下载成功之后，所有的XX.downX文件都会被删除掉)，则
		//说明文件已经被成功地下载完了，返回1。
		if((fp=fopen(csTemp,"r"))==NULL)
			return 1;
		else 
			fclose(fp);


		//此变量用来计算需要下载的总的数据量。
		int bb;
		//初始化为0
		bb=0;
		//从辅助文件中读取各线程的下载信息，读取的信息存放到filerange数组中。
		for(int ii=0;ii<BLOCK;ii++)
		{
			temp.Format(".down%d",ii);
			csTemp=m_fname+temp;
			myfile.Open(csTemp,CFile::modeRead | CFile::typeBinary);
			myfile.Read(&filerange[ii*2],sizeof(int));//seek值
			myfile.Read(&filerange[ii*2+1],sizeof(int));//需要下载的文件段的长度
			myfile.Close();
			//用累加的方法来计算需要下载的总的数据量。
			bb=	bb+filerange[ii*2+1];
			CString temp;
			temp.Format(" aa the seek is %d,the len is %d",filerange[ii*2],filerange[ii*2+1]);
		}
		//如果需要下载的总的数据量为0，则
		if(bb==0)
			return 1;
		//.totle中存放的是：要被下载的文件中，已经下载下来了的字节数。
		doinfo.totle=doinfo.filelen-bb;
		temp.Format("the value is %d,totle is %d,filelen is %d",BLOCK,doinfo.totle,doinfo.filelen);
		temp.Format("the totle is %d,filelen is %d",doinfo.totle,doinfo.filelen);
		((CMainFrame*)::AfxGetMainWnd())->m_work.m_ListCtrl->AddItemtwo(n,2,doinfo.totle,1,0,doinfo.threadno);
	}

	//建立一个新线程，以显示各文件下载线程的"下载进度"等信息。
	DWORD dwthread;
	//线程函数是timethread，传递给线程函数的参数是this指针。
	::CreateThread(NULL,0,timethread,(LPVOID)this,0,&dwthread);

	return 0;
}

//给服务器发送type=0的命令(作者称之为：LIST命令)，以获取服务上可下载的文件信息列表。
int cdownload::SendListCmd()
{
	sockaddr_in local;
	SOCKET socket1;
	int rc=0;
	local.sin_family=AF_INET;
	local.sin_port=htons(SERVER_PORT);
	local.sin_addr.S_un.S_addr=inet_addr(g_csIP);
	//create a stream socket.
	//socket函数的第三个参数的默认值是0，表示由程序本身根据地址格式和套接字类型，自动选择一个合适的协议。
	socket1=socket(AF_INET,SOCK_STREAM,0);
	int ret;
	//The connect function establishes a connection to a specified socket.The connect function is used to create a connection to the specified destination. If socket s, is unbound, unique values are assigned to the local association by the system, and the socket is marked as bound.
	//Return Values  If no error occurs, connect returns zero. Otherwise, it returns SOCKET_ERROR, and a specific error code can be retrieved by calling WSAGetLastError.
	ret=connect(socket1,(LPSOCKADDR)&local,sizeof(local));
	if(ret<0)
	{
		CString aaa;
		aaa="服务器接不上！\n";
		//下面这一句代码将导致CClientView::addmessage消息处理函数被调用。
		AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
		aaa.ReleaseBuffer();
		closesocket(socket1);
		return -1;
	}

	fileinfo fileinfo1;
	fileinfo1.len=100;
	fileinfo1.seek=50;
	fileinfo1.type=0;//设为0，表示：要获取服务上可下载的文件信息列表。
	//需要注意的是：这里只发送了100个字节的数据，而实际上，fileinfo结构的大小是116个字节，这样的话，最后的那个字符数组就会被截去了一部分数据。大概是因为这最后的字符数组在这里没用上吧。
	sendn(socket1,(char*)&fileinfo1,100);
	//读取服务器端的zmfile数组中全部(10个元素)的数据，放到客户端的zmfile数组中。
	readn(socket1,(char*)zmfile,SIZE_OF_zmfile);

	//The shutdown function disables sends or receives on a socket.
	shutdown(socket1,2);
	closesocket(socket1);
 
	//因为作者立的规矩是：zmfile数组中第一个可用的空元素的.name成员赋值为"none"，所以，
	//如果zmfile[0].name的内容是"none"，就表明此数组中根本就没有可下载的文件的信息。
	//如果服务器端没有文件可供下载，则
	if(strcmp(zmfile[0].name,"none")==0)
	{
		CString aaa;
		aaa="服务器没有文件可下载！\n";
		AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
		aaa.ReleaseBuffer();
		return -2;
	}

	//发送CLT_ON消息给主框架窗口，处理此消息的函数是CMainFrame::on 。
	//作用是：将可下载的文件列表在List控件中显示出来。传递的WPARAM参数是字符数组的指针，
	//但是，作者根本就没用到参数，而是使用了全局变量zmfile直接传递数据。
	::SendMessage(::AfxGetApp()->m_pMainWnd->m_hWnd,CLT_ON,(WPARAM)&zmfile,0);
	return 1;
}

//完成线程
DWORD cdownload::finish1()
{
	//pos表示：已经下载了的字节数，占文件总长度的百分之几。
	//pos1是一个辅助变量，记录的是pos变量的上一个值。
	int pos,pos1;
	//此变量是用来计算：时间差是否超过了1秒钟。
	int now;
	int totle1;
	//doinfo.totle中存放的是：？？？
	//totle1的值是：要被下载的文件段中，已经下载了的字节数。
	totle1=doinfo.totle;
	char* posbye;
	//既然是用了new，那就是在堆上分配的缓冲区了，这样，此缓冲区就相当于一个全局变量了。
	posbye=new char[100];
	CString posname;
	//此aaa变量是个辅助变量，用来表示：now变量是否需要重新取当前时间值。
	BOOL aaa;
	aaa=1;
	pos1=0;
	//又是死循环
	while(1)
	{
		if(aaa==1)
		{
			//The GetTickCount function retrieves the number of milliseconds that have elapsed since the system was started. It is limited to the resolution of the system timer. To obtain the system timer resolution, use the GetSystemTimeAdjustment function. 
			//now变量取当前时间值。
			now=GetTickCount();
			aaa=0;
		}

		//如果时间差超过了1000毫秒，则
		if(GetTickCount()-now>1000)
		{
			//doinfo是cdownload类的成员变量，很显然了，对此变量的值的修改，是在别的地方，而
			//并不是在本函数中。
			totle1=doinfo.totle-totle1;
			//obviously,现在totle1的值是：一秒钟内下载的字节数。
			posname.Format("%d K/s",totle1/1000);
			//拷贝到posbye数组中的内容是：XXX k/s 。Attention：拷贝的时候，前面空出了20个字节。
			strcpy(&posbye[20],posname.GetBuffer(0));
			//使totle1的值等于：要被下载的文件中，已经下载了的字节数。
			totle1=doinfo.totle;
			//doinfo.filelen/100==文件总长度的1/100。
			//pos应该表示：已经下载了的字节数，占文件总长度的百分之几。
			//当文件的长度小于100字节的时候，执行下面的这一句代码就会出现
			//“integer divide by zero”的错误。
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
				//这一次，是拷贝到posbye数组中的开头位置处了。
				strcpy(posbye,posname.GetBuffer(0));
				//posname串被赋了新值“|”。
				posname="|";
				while(pos>0)
				{
					//下面的这两句代码表明：一个“|”表示两个百分点。
					posname=posname+'|';
					pos-=2;
				}
			}
			else
			{
				posname="zm";//将串设置为"zm"，这个暗号是有用的。
			}

			pos1=pos;
			//这一次拷贝串，是从posbye[40]这个位置开始拷贝的，前面空出了40个字节。
			strcpy(&posbye[40],posname.GetBuffer(0));
			//向主窗口发送CLT_ONSETWO消息，处理此消息的是CMainFrame::OnSetwo函数。
			AfxGetMainWnd()->SendMessage(CLT_ONSETWO,(WPARAM)&doinfo.threadno,(LPARAM)posbye);
			//如果已经下载了的字节数>=文件的长度，就表示文件已经下载完了，于是就可以返回了。
			if(doinfo.totle>=doinfo.filelen)
				return 1;//唯一能跳出死循环的地方！

			//将此变量设为1，表示：now变量需要重新取当前时间值了。
			aaa=1;
		}

		Sleep(100);//既然是用来显示下载进度的函数，就没必要执行的那么频繁，可以睡一会儿。
	}
	return 1;
}

//
void cdownload::createthread()
{
	
}
