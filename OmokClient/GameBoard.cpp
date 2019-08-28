#include "stdafx.h"
#include "GameBoard.h"
#include "Basis.h"
#include "Stone.h"
#include "Client.h"
#include "Basis.h"

GameBoard::GameBoard()
	: Observer(),msg_(nullptr)
{
}

void GameBoard::onNotify(const Subject * sub, TYPE_EVENT event)
{
	switch (event)
	{
	case T_INIT:
	{

	}	break;
	case T_UPDATE:
	{

	}	break;
	case T_RENDER:
	{

	}	break;
	case T_PUTSTONE:
	{
		SendMsg message;
		message.posX = mousePos_.x;
		message.posY = mousePos_.y;
		net_->Send(message);
	}	break;
	case T_SENDMSG:
	{

	}	break;
	default:
		break;
	}
}

std::vector<Basis*> GameBoard::GetObjects()
{
	std::vector<Basis*> list;
	list.push_back((Basis*)stones_);

	return list;
}

void GameBoard::Init()
{
	stones_ = new Stone;
	net_ = new Client("127.0.0.1",8000);
	auto list_sub = GetObjects();
	for (auto list : list_sub)
	{
		list->Register(this);
		list->Init(this);
	}
}

void GameBoard::Update()
{
	if (!Observer::is_all_initiated)
		return;
	if (msg_->flag != TYPE_FLAG::GAME_PLAY)
		return;
	if (myStone_ == TYPE_COLOR::C_NONE)
		PostMessage(g_hwnd, WM_CHOOSE, 0, 0);

	if (!ChekeMyTurn())
		return;

	SetMousePos();

	auto list_sub = GetObjects();
	for (auto list : list_sub)
		list->Update();
}

void GameBoard::Render(HDC & hdc)
{
	RenderBoard(hdc);

	auto list_sub = GetObjects();
	for (auto list : list_sub)
		list->Render(hdc);

#ifdef _DEBUG
	TCHAR szBuff[64];
	auto pt = mousePos_;
	wsprintf(szBuff, _T("=== ¸¶¿ì½º ÁÂÇ¥ :: X : %d / Y : %d ==="), pt.x, pt.y);
	TextOut(hdc, 10, 620, szBuff, _tcslen(szBuff));
#endif // _DEBUG

	if (!Observer::is_all_rendered)
		std::cout << "render is Undone" << std::endl;

}

void GameBoard::RenderBoard(HDC & hdc)
{
	for (int i = 0; i < 19; ++i)
	{
		MoveToEx(hdc, BoardStartX + i * BasicPxl, BoardStartY, NULL);
		LineTo(hdc, BoardStartX + i * BasicPxl, BoardStartY + BasicPxl * 18);
	}
	for (int i = 0; i < 19; ++i)
	{
		MoveToEx(hdc, BoardStartX, BoardStartY + i * BasicPxl, NULL);
		LineTo(hdc, BoardStartX + BasicPxl * 18, BoardStartY + i * BasicPxl);
	}
	HBRUSH hbrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

	int r1[3] = { 117,297,477 };
	int r2[3] = { 123,303,483 };
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			Ellipse(hdc, r1[j], r1[i], r2[j], r2[i]);
		}
	}

	SelectObject(hdc, oldbrush);
	DeleteObject(hbrush);
}

bool GameBoard::ChekeMyTurn()
{
	if (msg_->flag == TYPE_FLAG::TURN_BLACK || msg_->flag == TYPE_FLAG::TURN_WHITE)
		if (msg_->flag == myStone_)
			return true;

	return false;
}

void GameBoard::SetMyStone(TYPE_COLOR color)
{
	myStone_ = color;
}

bool GameBoard::CheckConnect()
{
	bool result = false;
	if (net_)
		result = true;
	return result;
}

void GameBoard::SetReceivedMsg(RecvMsg* m)
{
	msg_->flag = m->flag;
	msg_->posX = m->posX;
	msg_->posY = m->posY;
	msg_->stone = m->stone;
}



void GameBoard::SetMousePos()
{
	POINT mousePos_;
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		GetCursorPos(&mousePos_);
		ScreenToClient(g_hwnd, &mousePos_);
	}
}
