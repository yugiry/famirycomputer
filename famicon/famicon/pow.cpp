#pragma once
#include "pow.h"

CPow::CPow(Point p)
{
	img = LoadGraph("image\\pow.png");

	ImgWidth = 32;
	ImgHeight = 32;

	CutX = CutY = 0;

	pos.x = p.x - ImgWidth / 2;
	pos.y = p.y + 96;

	ID = POW;
}

int CPow::Action(vector<unique_ptr<BaseVector>>& base)
{
	if (plosion_time == 3)
	{
		CutX = 0;
		CutY = 0;
	}
	if (plosion_time == 2)
	{
		CutX = 32;
		CutY = 0;
	}
	if (plosion_time == 1)
	{
		CutX = 64;
		CutY = 0;
	}
	if (plosion_time == 0)
	{
		FLAG = false;
	}

	return 0;
}

void CPow::Draw()
{
	DrawRectGraph(pos.x, pos.y, CutX, CutY, ImgWidth, ImgHeight, img, true);
}