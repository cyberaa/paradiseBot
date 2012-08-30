#include <winsock2.h>
#include <windows.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#include <winsock.h>
#include <fstream>

using namespace std;

int main (){




	ofstream ofs("new.txt", ofstream::out);     

	if (ofs.good())   { // if opening is successful

		
			ofs << "ThisTextMustbeSend!";

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
	
	char sendString1 [] ="POST /BotServer/index.php/Bot_c/catchFile HTTP/1.1"
                         "\r\nHost: localhost"
	                     "\r\nUser-Agent: Mozilla/5.0 (Windows NT 6.1; rv:14.0) Gecko/20100101 Firefox/14.0.1"
                         "\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8"
						 "\r\nAccept-Language: en-us,en;q=0.5"
						 "\r\nAccept-Encoding: gzip, deflate"
						 "\r\nConnection: keep-alive"
						 "\r\nReferer: localhost/BotServer/index.php/bot_C/showcatchFileForm/"
						 "\r\nContent-Type: multipart/form-data; boundary=---------------------------98942870323811"
						 "\r\nContent-Length: 324"

						 "\r\n\r\n-----------------------------98942870323811"
						 "\r\nContent-Disposition: form-data; name='BotReport'; filename='new.txt'"
						 "\r\nContent-Type: text/plain"

						 "\r\n\r\nThisTextMustbeSend!"
						 "\r\n-----------------------------98942870323811"
						 "\r\nContent-Disposition: form-data; name='submit'"

						 "\r\n\r\nTransmit Report !"
						 "\r\n-----------------------------98942870323811--"
                         "\r\n";




	char sendString2 [] = "POST /BotServer/index.php/Bot_c/RegisterBot HTTP/1.1\r\n"
                          "Host: localhost\r\n"
	                      "User-Agent: Mozilla/5.0 (Windows NT 6.1; rv:14.0) Gecko/20100101 Firefox/14.0.1\r\n"
                          "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
						  "Accept-Language: en-us,en;q=0.5\r\n"
						  "Accept-Encoding: gzip, deflate\r\n"
						  "Connection: keep-alive\r\n"
						  "Referer: localhost/BotServer/index.php/bot_C/showRegisterForm/\r\n"
						  "Content-Type: application/x-www-form-urlencoded\r\n"
						  "Content-Length: 66\r\n\r\n"
						  "ip=192.23.34.12&systemVersion=CnewOs&submit=Register+Bot+please%23";



	

	//printf(sendString );

	send(Socket, sendString1, strlen(sendString1),0);
	//send(Socket, sendString2, strlen(sendString2),0);

	



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