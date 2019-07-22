#include "stdafx.h"
#include "Stone.h"


void Stone::Init(GameBoard* G)
{
	W_stn.resize(0);
	B_stn.resize(0);
	GB = G;
	Subject::Notify(T_INIT);
}

void Stone::Update()
{
	POINT mousePos = GB->GetMousePos();

	if (CheckStonePos(mousePos))
	{
		// 돌놓기
		if (GB->GetMyStone() == TYPE_COLOR::C_BLACK)
			B_stn.push_back(STONE(mousePos.x, mousePos.y, C_BLACK));
		else
			W_stn.push_back(STONE(mousePos.x, mousePos.y, C_WHITE));
	}
}

void Stone::Render(HDC hdc)
{
	auto it = W_stn.begin();
	HBRUSH Wbrush = CreateSolidBrush(RGB(235, 235, 235));
	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, Wbrush);
	while (it != W_stn.end())
	{
		POINT p;
		p.x = (*it).x;	p.y = (*it).y;
		p = ShiftStoneCoordinate(p, COORD_VEC);
		Ellipse(hdc, p.x - CirSize, p.y - CirSize,
			p.x + CirSize, p.y + CirSize);
		it++;
	}
	HBRUSH Bbrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, Bbrush);
	it = B_stn.begin();
	while (it != B_stn.end())
	{
		POINT p;
		p.x = (*it).x;	p.y = (*it).y;
		p = ShiftStoneCoordinate(p, COORD_VEC);
		Ellipse(hdc, p.x - CirSize, p.y - CirSize,
			p.x + CirSize, p.y + CirSize);
		it++;
	}
	SelectObject(hdc, oldbrush);
	DeleteObject(Wbrush);
	DeleteObject(Bbrush);
	Subject::Notify(TYPE_EVENT::T_RENDER);
}

bool Stone::CheckStonePos(POINT p)
{
	if (0 < p.x && 0 < p.y && p.x < 580 && p.y < 580)
	{
		// 놓여있는 돌과 마우스 점 충돌확인
		for (auto W : W_stn)
		{
			RECT *re = &MakeStoneCollider(W);
			if (PtInRect(re, p))
				return false;
		}
		for (auto B : B_stn)
		{
			RECT *re = &MakeStoneCollider(B);
			if (PtInRect(re, p))
				return false;
		}
		return true;
	}
	else
		return false;
}

RECT Stone::MakeStoneCollider(STONE stn)
{
	RECT rect;
	POINT p;
	p.x = stn.x;
	p.y = stn.y;
	p = ShiftStoneCoordinate(p,COORD_VEC);
	rect.left = p.x - (BasicPxl / 2);
	rect.top = p.y - (BasicPxl / 2);
	rect.right = p.x + BasicPxl - (BasicPxl / 2);
	rect.bottom = p.y + BasicPxl - (BasicPxl / 2);

	return rect;
}

POINT Stone::ShiftStoneCoordinate(POINT p, TYPE_COORD type)
{
	if (type == COORD_WIN)
	{
		p.x = BoardStartX + p.x * BasicPxl;
		p.y = BoardStartY + p.y * BasicPxl;
	}
	else
	{
		p.x = (p.x - BoardStartX) / BasicPxl;
		p.x = (p.y - BoardStartY) / BasicPxl;
	}
	return p;
}
