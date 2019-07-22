#pragma once
#include <string>
#include <WinSock2.h>
class Client : public Basis
{
public:
	Client(const std::string& host, int port);
	virtual void Init(GameBoard* G);
	virtual void Update() {}
	virtual void Render(HDC hdc) {}
private:
	GameBoard* GB;
	std::string host_;
	int port_;
	SOCKET socket_;
public:
	int isRunning_;
	void Connect();
	bool Send(SendMsg msg);
	RecvMsg Receive();

	//void Disconnect();
	//void Run(LPARAM lParam);
	bool CheckRunning() { return isRunning_; }
};

