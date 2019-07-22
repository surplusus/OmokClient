#include "stdafx.h"
#include "Renderer.h"

MyBitMap::~MyBitMap()
{
	SelectObject(hMemDC_, hOldbitmap_);
	DeleteObject(hBitmap_);
	DeleteDC(hMemDC_);
}

MyBitMap * MyBitMap::LoadBmp(LPCWSTR pFileName)
{
	hdc_ = GetDC(g_hwnd);
	hMemDC_ = CreateCompatibleDC(hdc_);
	hBitmap_ = (HBITMAP)LoadImage(NULL, pFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(hBitmap_, sizeof(BITMAP), &image_);

	if (!hBitmap_)
	{
		MessageBox(g_hwnd, _T("이미지로드 실패"), _T("이미지로드 실패"), MB_OK);
		exit(0);
	}
	hOldbitmap_ = (HBITMAP)SelectObject(hMemDC_, hBitmap_);

	DeleteObject(hBitmap_);
	DeleteObject(hOldbitmap_);
	return this;
}

void Renderer::Init(GameBoard* G)
{
	hdc_ = GetDC(g_hwnd);
	backBuffer_ = new MyBitMap;
	backGround_ = new MyBitMap;
	backBuffer_->LoadBmp((LPCWSTR)_T("background.bmp"));
	backGround_->LoadBmp((LPCWSTR)_T("background.bmp"));
	GB = G;
}

void Renderer::Render()
{
	BitBlt(hdc_, 0, 0, BoardWidth, BoardHeight, backBuffer_->GetMemDC(), 0, 0, SRCCOPY);
	BitBlt(backBuffer_->GetMemDC(), 0, 0, BoardWidth, BoardHeight, backGround_->GetMemDC(), 0, 0, SRCCOPY);

	GB->Render(backBuffer_->GetMemDC());

	BitBlt(hdc_, 0, 0, BoardWidth, BoardHeight, backBuffer_->GetMemDC(), 0, 0, SRCCOPY);
}
