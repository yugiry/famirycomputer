#pragma once
#include "scaf.h"

CScaf::CScaf(Point p)
{
	pos = p;
	img = LoadGraph("image\\scaf.png");

	ImgWidth = BLOCK_WIDTH;
	ImgHeight = BLOCK_HEIGHT;

	ID = SCAF;
}

int CScaf::Action(vector<unique_ptr<BaseVector>>& base)
{
	pos.y += vec.y;

	if (vec.y == -10.0f)vec.y = 10.0f;
	else if (vec.y == 10.0f)vec.y = 0;

	return 0;
}

void CScaf::Draw()
{
	DrawGraph(pos.x, pos.y, img, true);
}