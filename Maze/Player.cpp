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

		// 1. ���� �ٶ󺸴� ������ �������� ���������� �� �� �ִ��� Ȯ��.
		if (Cango(pos + front[int32(newDir)]))
		{
			// ������ �������� 90�� ȸ��
			dir = newDir;

			// ������ �� �� ����
			pos += front[int32(newDir)];
			_path.push_back(pos);
		}
		// 2. ���� �ٶ󺸴� ������ �������� ������ �� �ִ��� Ȯ��.
		else if (Cango(pos + front[int32(dir)]))
		{
			// ������ �Ѻ� ����
			pos += front[int32(dir)];
			_path.push_back(pos);
		}
		else
		{
			// ���� �������� 90�� ȸ��
			dir = Dir((int32(dir) + 1) % int32(Dir::COUNT));
		}
	}

	stack<Pos> s;

	for (int i = 0; i < _path.size() - 1; ++i)
	{
		if (s.empty() == false && s.top() == _path[i + 1])
		{
			// �ǵ��� �����ϴ� ��
			s.pop();
		}
		else
		{
			s.push(_path[i]);
		}
	}

	// ������ ����
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
