#pragma once
enum TYPE_EVENT{
	T_INIT,T_UPDATE,T_RENDER,
	T_BLACKPUT, T_WHITEPUT, T_PUTSTONE,
	T_SENDMSG, T_RECEIVEMSG
};
enum TYPE_COLOR{
	C_NONE, C_BLACK, C_WHITE
};
enum TYPE_FLAG
{
	GAME_INIT, GAME_PLAY, GAME_END,
	TURN_BLACK, TURN_WHITE, 
	GAME_WIN, GAME_LOSE
};

typedef struct _tagStone {
	int x = -1;
	int y = -1;
	TYPE_COLOR color = TYPE_COLOR::C_NONE;
	_tagStone(int ix = -1, int iy = -1, TYPE_COLOR icolor = TYPE_COLOR::C_NONE) :
		x(ix), y(iy), color(icolor) {}
}STONE;

typedef struct _tagRMsg
{
	TYPE_FLAG flag = TYPE_FLAG::GAME_END;
	int posX = -1;
	int posY = -1;
	STONE stone;
	_tagRMsg(int x = -1, int y = -1, STONE s = STONE());
} RecvMsg;
typedef struct _tagSMsg
{
	int posX = -1;
	int posY = -1;
} SendMsg;

static const int BoardWidth = 700;
static const int BoardHeight = 700;
static const int BoardStartX = 30;
static const int BoardStartY = 30;
static const int BasicPxl = 30;
static const int CirSize = 13;
#define WM_CHOOSE WM_USER+3
class GameBoard;
class Observer;
class Subject
{
public:
	virtual ~Subject() = default;
private:
	Observer* observer_;	//  원래는 리스트
protected:
	void Notify(TYPE_EVENT event);
public:
	void Register(Observer* ob);
	//void UnRegister(Observer* ob);	원래는 있어야됨
};

class Basis : public Subject
{
public:
	Basis();
	virtual ~Basis() {}

	virtual void Init(GameBoard* G) = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
};

