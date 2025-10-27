#pragma once
#include "scaf.h"

CScaf::CScaf(Point p)
{
	set_pos = pos = p;
	img = LoadGraph("image\\scaf.png");

	ImgWidth = BLOCK_WIDTH;
	ImgHeight = BLOCK_HEIGHT;

	vec.y = 0;

	ID = SCAF;

	pri = 0;
}

int CScaf::Action(vector<unique_ptr<BaseVector>>& base)
{
	pos.y += vec.y;
	if (pos.y != set_pos.y)
		vec.y += 0.5f;

	//Œ»Ý‚ÌˆÊ’u‚©‚ç
	if (pos.y > set_pos.y)
	{
		vec.y = 0.0f;
		pos.y = set_pos.y;
	}

	return 0;
}

void CScaf::Draw()
{
	DrawGraph(pos.x, pos.y, img, true);
}