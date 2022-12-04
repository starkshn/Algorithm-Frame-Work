#pragma once

class Board;

class Player
{
	enum
	{
		MOVE_TICK = 100,
	};

public:
	void	Init(Board* board);
	void	Update(uint64 deltaTick);

private:
	// 이곳에 구현할 길찾기 알고리즘 함수 구현하면됨.
	void	RightHand(); // 우수법

public:
	void	SetPos(Pos pos) { _pos = pos; }

public:
	Pos		GetPos() { return _pos; }

public:
	bool	Cango(Pos pos);

private:
	Pos				_pos = {};
	Dir				_dir = Dir::UP;
	Board*			p_board = nullptr;

	vector<Pos>		_path;
	int32			_pathIdx = 0;
	uint64			_sumTick = 0;
};

