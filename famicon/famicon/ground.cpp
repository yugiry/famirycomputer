#pragma once
#include "ground.h"

CGround::CGround(Point p)
{
	pos = p;
	img = LoadGraph("image\\ground.png");

	ImgWidth = BLOCK_WIDTH;
	ImgHeight = BLOCK_HEIGHT;

	ID = GROUND;
}

int CGround::Action(vector<unique_ptr<BaseVector>>& base)
{
	return 0;
}

void CGround::Draw()
{
	DrawGraph(pos.x, pos.y, img, true);
}