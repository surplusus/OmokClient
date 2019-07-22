#pragma once
class GameBoard;

class MyBitMap
{
public:
	MyBitMap() = default;
	~MyBitMap();
private:
	HDC hMemDC_;
	HDC hdc_;
	HBITMAP hBitmap_;
	HBITMAP hOldbitmap_;
	BITMAP image_;
public:
	MyBitMap* LoadBmp(LPCWSTR pFileName);
	HDC& GetMemDC() { return hMemDC_; }
	const BITMAP GetBitMapImage() { return image_; }
};

class Renderer
{
public:
	Renderer() { Init(); }
	~Renderer() = default;
private:
	GameBoard* GB;
	HDC hdc_;
	MyBitMap* backBuffer_;
	MyBitMap* backGround_;
public:
	void Init(GameBoard* G);
	void Render();
};

