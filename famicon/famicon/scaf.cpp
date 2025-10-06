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
	return 0;
}

void CScaf::Draw()
{
	DrawGraph(pos.x, pos.y, img, true);
}