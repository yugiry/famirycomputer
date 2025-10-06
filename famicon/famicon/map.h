#pragma once
#include "objBase.h"

class CMap :public BaseVector
{
public:
	CMap(vector<unique_ptr<BaseVector>>&s);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	int map[MAP_WIDTH * MAP_HEIGHT];

	int img[BLOCK_END];
};