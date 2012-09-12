#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <winsock.h>
#include <fstream>
#include <vector>

using namespace std;
#pragma comment(lib,"ws2_32.lib")



int main (){

	ofstream ofs("new.txt", ofstream::out);     

	if (ofs.good())   { // if opening is successful

		
			ofs << "ThisTextMustbeSend plus this one !";

		// close the file

		ofs.close();

	} else

		// otherwise print a message

		cout << "ERROR: can't open file for writing." << endl;


	//Making socket for posting file :

	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
		cout << "WSAStartup failed.\n";
		system("pause");
		return 1;
	}

	SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	struct hostent *host;
	host = gethostbyname("localhost");

	

	SOCKADDR_IN SockAddr;
	SockAddr.sin_port=htons(80);
	SockAddr.sin_family=AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

	//Alarm about connecting to socket :  
	cout << "Connecting...\n";

	if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr)) != 0){
		cout << "Could not connect";
		system("pause");
		return 1;
	}
	cout << "Connected.\n";


	
	/************************************************************************/
	/* int send(
	__in  SOCKET s,
	__in  const char *buf,
	__in  int len,
	__in  int flags
	);
	
	s [in]

	A descriptor identifying a connected socket.
	
	buf [in]
	A pointer to a buffer containing the data to be transmitted.
	
	len [in]
	The length, in bytes, of the data in buffer pointed to by the buf parameter.
	
	flags [in]
	A set of flags that specify the way in which the call is made. 
	This parameter is constructed by using the bitwise OR operator with any of the following values.
	/************************************************************************/

	//printf("We pass here !\n");

	//char sendString [] = "GET /BotServer/ HTTP/1.1\r\nHost: localhost\r\nUser-Agent: Mozilla/5.0 (Windows NT 6.1; rv:14.0) Gecko/20100101 Firefox/14.0.1\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: en-us,en;q=0.5\r\nAccept-Encoding: gzip, deflate\r\nConnection: keep-alive\r\n\r\n";
	
	char sendStringP1 [] = "POST /BotServer/index.php/Bot_c/catchFile HTTP/1.1\r\n"
                            "Host: localhost\r\n"
	                        "User-Agent: Mozilla/5.0 (Windows NT 6.1; rv:14.0) Gecko/20100101 Firefox/14.0.1\r\n"
                            "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
							"Accept-Language: en-us,en;q=0.5\r\n"
							"Accept-Encoding: gzip, deflate\r\n"
							"Connection: keep-alive\r\n"
							"Referer: localhost/BotServer/index.php/bot_C/showcatchFileForm/\r\n"
							"Content-Type: multipart/form-data; boundary=---------------------------41184676334\r\n";
	
	
	//char sendStringP2 [] =  "Content-Length: 314";

	vector <char> sendBuffer;
	char ch ='S';//Alaki!
	ifstream ifs("new.txt",ifstream::in);
	if (ifs.good())
	{
		while (!(ifs.eof()))
		{
			ch = (char) ifs.get( );
			sendBuffer.push_back(ch);
		}

	}else {

		cout << "Cannot read from file !";

	}

	

	int fileSize = (int) sendBuffer.size();//this method print size + 1 because of null at the End . 

	//cout<<endl<<fileSize<<endl;

	char sendStringP2 [25];
    
	sprintf(sendStringP2 , "Content-Length: %d",fileSize/*-1*/+297);//For making suitable size we remove '-1' because /n !
	

	char sendStringP3 [] =	"\r\n\r\n-----------------------------41184676334\r\n"
							"Content-Disposition: form-data; name='BotReport'; filename='test.txt'\r\n"
							"Content-Type: text/plain\r\n\r\n";
     
	
	char sendStringP4 [60] ={0};

	



	for (int i=0 ; i<=sendBuffer.size()-1;i++)
	{
		sendStringP4[i] = sendBuffer[i];
	}



	//cout<<endl<<sizeof(sendStringP4)<<endl;

	//for (int i=0 ; i<=sizeof(sendStringP4);i++)
	//{
	//	cout<<" "<<sendStringP4[i]<<"-";
	//}




	
	char sendStringP5 [] =	"\r\n-----------------------------41184676334"
							"\r\nContent-Disposition: form-data; name='submit'"

							"\r\n\r\nTransmit Report !"
							"\r\n-----------------------------41184676334--\r\n";

	char sendString [1000];
	sprintf(sendString , "%s%s%s%s%s" , sendStringP1,sendStringP2,sendStringP3,sendStringP4,sendStringP5);


	//printf(sendString );



	send(Socket, sendString, strlen(sendString),0);
	

	



	char buffer[10000];

	ZeroMemory(buffer , 10000);

  /*
	int recv(
		_In_   SOCKET s,
		_Out_  char *buf,
		_In_   int len,
		_In_   int flags
		);

  */


	
	int nDataLength ;
	//initializing in while for writing when data is ready :
	while ((nDataLength = recv(Socket,buffer,10000,0)) > 0){

		//printf("nDataLenght is : %u \n" , nDataLength);

		int i = 0;
		while (i<=nDataLength)
		{

			cout << buffer[i];
			i++;
		}


	}


	
	closesocket(Socket);
	WSACleanup();

	system("pause");
	return 0;
}