#pragma once
#include "pipe.h"
#include "function.h"
#include "turtle.h"

CPipe::CPipe(Point p, int _type)
{
	pos = p;
	img = LoadGraph("image\\pipe.png");

	type = _type;

	if (type == 0 || type == 1)
	{
		CutX = 0;
		CutY = 0;
		ImgWidth = 64;
		ImgHeight = 48;
	}
	if (type == 2 || type == 3)
	{
		CutX = 0;
		CutY = 48;
		ImgWidth = 112;
		ImgHeight = 80;
	}

	if (type == 0)
	{
		hit.x = pos.x + ImgWidth;
		hit.y = pos.y;
	}
	if (type == 1)
	{
		hit.x = pos.x - 10;
		hit.y = pos.y;
	}

	ID = PIPE;

	pri = 3;
}

int CPipe::Action(vector<unique_ptr<BaseVector>>& base)
{
	for (auto i = 0; i < base.size(); i++)
	{
		if (base[i]->ID == TURTLE && (type == 0 || type == 1))
		{
			CTurtle* turtle = (CTurtle*)base[i].get();
			if (!turtle->fall_down)
			{
				if (HitCheck_box(hit.x, hit.y, base[i]->pos.x, base[i]->pos.y, 10, ImgHeight, base[i]->ImgWidth, base[i]->ImgHeight))
				{

					base[i]->vec.y = -1.0f;
				}
			}
		}
	}

	return 0;
}

void CPipe::Draw()
{
	//DrawRectGraph(pos.x, pos.y, CutX, CutY, 100, 100, img, true);

	if (type == 0 || type == 2)
	{
		DrawRectGraph(pos.x, pos.y, CutX, CutY, ImgWidth, ImgHeight, img, true, false);
	}
	if (type == 1 || type == 3)
	{
		DrawRectGraph(pos.x, pos.y, CutX, CutY, ImgWidth, ImgHeight, img, true, true);
	}
}