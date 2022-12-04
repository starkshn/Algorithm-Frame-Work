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
	// �̰��� ������ ��ã�� �˰��� �Լ� �����ϸ��.
	void	RightHand(); // �����

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

