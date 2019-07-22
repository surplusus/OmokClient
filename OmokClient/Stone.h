#pragma once
#include <vector>


class Stone : public Basis
{
public:
	Stone() = default;
	virtual ~Stone() = default;

	virtual void Init(GameBoard* G);
	virtual void Update();
	virtual void Render(HDC hdc);
private:
	enum TYPE_COORD{COORD_WIN, COORD_VEC};
	GameBoard* GB;
	std::vector<STONE> W_stn;
	std::vector<STONE> B_stn;
private:
	bool CheckStonePos(POINT p);
	RECT MakeStoneCollider(STONE stn);
	POINT ShiftStoneCoordinate(POINT p, TYPE_COORD type);
};

