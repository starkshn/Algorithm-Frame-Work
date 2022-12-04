#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	p_board = board;
	
	RightHand();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIdx >= _path.size())
	{
		if (_pathIdx == 45)
			return;
		p_board->GenerateMap();
		Init(p_board);
		return;
	}

	_sumTick += deltaTick;

	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;

		_pos = _path[_pathIdx];
		++_pathIdx;
	}
}

void Player::RightHand()
{
	Pos pos = _pos;
	Dir dir = _dir;

	_path.clear();
	_path.push_back(pos);

	Pos dest = p_board->GetExitPos();


	Pos front[4] =
	{
		Pos {0, -1},
		Pos {-1, 0},
		Pos {0, 1},
		Pos {1, 0}
	};

	while (pos != dest)
	{
		Dir newDir = Dir((int32(dir) + int32(Dir::COUNT) - 1) % int32(Dir::COUNT));

		// 1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인.
		if (Cango(pos + front[int32(newDir)]))
		{
			// 오른쪽 방향으로 90도 회전
			dir = newDir;

			// 앞으로 한 보 전진
			pos += front[int32(newDir)];
			_path.push_back(pos);
		}
		// 2. 현재 바라보는 방향을 기준으로 전진할 수 있는지 확인.
		else if (Cango(pos + front[int32(dir)]))
		{
			// 앞으로 한보 전진
			pos += front[int32(dir)];
			_path.push_back(pos);
		}
		else
		{
			// 왼쪽 방향으로 90도 회전
			dir = Dir((int32(dir) + 1) % int32(Dir::COUNT));
		}
	}

	stack<Pos> s;

	for (int i = 0; i < _path.size() - 1; ++i)
	{
		if (s.empty() == false && s.top() == _path[i + 1])
		{
			// 되돌아 가야하는 길
			s.pop();
		}
		else
		{
			s.push(_path[i]);
		}
	}

	// 목적지 도착
	if (_path.empty() == false)
		s.push(_path.back());

	vector<Pos> path;
	while (!s.empty())
	{
		path.push_back(s.top());
		s.pop();
	}

	std::reverse(path.begin(), path.end());

	_path = path;

}


bool Player::Cango(Pos pos)
{
	TILE_TYPE tileType = p_board->GetTileType(pos);
	return tileType == TILE_TYPE::EMPTY;
}
