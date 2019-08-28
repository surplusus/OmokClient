#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "stdafx.h"
#include "Client.h"

Client::Client(const std::string & host, int port) : 
	host_(host), port_(port), socket_(SOCKET(-1)), isRunning_(true)
{
}

void Client::Init(GameBoard * G)
{
	GB = G;
	Subject::Notify(T_INIT);
}

void Client::Connect()
{
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	socket_ = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port_);
	inet_pton(AF_INET, host_.c_str(), &addr.sin_addr.S_un.S_addr);
	//WSAAsyncSelect(socket_, g_hwnd, WM_ASYNC, FD_READ);
	if (connect(socket_, (LPSOCKADDR)&addr, sizeof(addr)) == -1)
		return;
	else
		isRunning_ = true;
}

bool Client::Send(SendMsg msg)
{
	try
	{
		send(socket_, (char*)&msg, sizeof(SendMsg), 0);
	}
	catch (...)
	{
		cout << "send failed" << endl;
		return false;
	}
	
	return true;
}

RecvMsg Client::Receive()
{
	RecvMsg* msg = nullptr;
	char buffer[512];
	int msglen = recv(socket_, buffer, sizeof(RecvMsg), 0);
	memcpy_s(msg, sizeof(RecvMsg), buffer, msglen);

	Subject::Notify(T_SENDMSG);
	return *msg;
}
