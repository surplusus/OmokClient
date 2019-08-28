#pragma once
#include <vector>
#include "Basis.h"
class Subject;
class Stone;
class Basis;
class Client;

class Observer
{
protected:
	bool is_all_initiated = false;
	bool is_all_updated = false;
	bool is_all_rendered= false;
public:
	virtual ~Observer() = default;
	virtual void onNotify(const Subject* sub, TYPE_EVENT event) = 0;
};

class GameBoard : public Observer
{
public:
	GameBoard();
	virtual ~GameBoard() = default;

	virtual void onNotify(const Subject* sub, TYPE_EVENT event);
	std::vector<Basis*> GetObjects();
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC &hdc);
private:
	Stone* stones_;
	Client* net_ = nullptr;
	HDC hdc_;
	POINT mousePos_;
	RecvMsg* msg_;
	TYPE_COLOR myStone_ = TYPE_COLOR::C_NONE;
private:
	void SetMousePos();
	void RenderBoard(HDC &hdc);
	bool ChekeMyTurn();
public:
	POINT GetMousePos() { return mousePos_; }
	void SetMyStone(TYPE_COLOR color);
	const TYPE_COLOR GetMyStone() const { return myStone_; }
	bool CheckConnect();
	Client* AccessClient() { return net_; }
	void SetReceivedMsg(RecvMsg* m);
};

