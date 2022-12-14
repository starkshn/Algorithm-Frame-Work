#pragma once
#include "ConsoleHelper.h"

class Player;

enum
{
	BOARD_MAX_SIZE = 100,
};


enum class TILE_TYPE
{
	NONE = 0,
	EMPTY,
	WALL,
};

class Board
{
public:
	Board();
	~Board();

public:
	void			Init(INT32 size, Player* player);
	void			Render();
	void			GenerateMap();

public:
	TILE_TYPE		GetTileType(Pos pos);
	ConsoleColor	GetTileColor(Pos pos);

	Pos				GetEnterPos()			{ return Pos{ 1, 1 }; };
	Pos				GetExitPos()			{ return Pos{ _size - 2, _size - 2 }; };
	INT32			GetSize()				{ return _size; }

private:
	TILE_TYPE		_tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE] = {};
	INT32			_size = 0;
	Player*			p_player;

};

