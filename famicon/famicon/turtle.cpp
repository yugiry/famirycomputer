#pragma once
#include "turtle.h"
#include "function.h"

CTurtle::CTurtle(Point p)
{
	img = LoadGraph("image\\turtle.png");

	pos = p;

	ImgWidth = 32;
	ImgHeight = 32;

	CutX = 0;
	CutY = 0;

	vec.x = -speed;

	ID = TURTLE;
}

int CTurtle::Action(vector<unique_ptr<BaseVector>>& base)
{
	vec.y += g;
	anim_time++;
	
	Point latepos{ pos.x + vec.x,pos.y + vec.y };
	for (auto i = base.begin(); i != base.end(); i++)
	{
		if ((*i)->ID == GROUND)
		{
			if (HitCheck_box(latepos.x, latepos.y + ImgHeight - 10, (*i)->pos.x, (*i)->pos.y, ImgWidth, 10, (*i)->ImgWidth, 5))
			{
				vec.y = 0;
				pos.y = (*i)->pos.y - ImgHeight;
				break;
			}
		}
		if ((*i)->ID == SCAF)
		{
			if (HitCheck_box(latepos.x, latepos.y + ImgHeight - 10, (*i)->pos.x, (*i)->pos.y, ImgWidth, 10, (*i)->ImgWidth, 5))
			{
				vec.y = 0;
				pos.y = (*i)->pos.y - ImgHeight;
				break;
			}
		}
	}
	
	//画面端に行ったとき、反対側の画面端から出るようにする
	if (pos.x + vec.x + ImgWidth < 0)
	{
		pos.x = WINDOW_WIDTH;
	}
	if (pos.x + vec.x > WINDOW_WIDTH)
	{
		pos.x = -ImgWidth;
	}

	pos.x += vec.x;
	pos.y += vec.y;

	//アニメーション
	if (anim_time < 2)
	{
		CutX = 0;
		CutY = 0;
	}
	else if (anim_time < 4)
	{
		CutX = 32;
		CutY = 0;
	}
	else if (anim_time < 6)
	{
		CutX = 64;
		CutY = 0;
	}
	else if (anim_time < 8)
	{
		CutX = 32;
		CutY = 0;
	}
	if (anim_time == 8)
	{
		anim_time = 0;
	}

	return 0;
}

void CTurtle::Draw()
{
	DrawRectGraph(pos.x, pos.y, CutX, CutY, ImgWidth, ImgHeight, img, true, false);
}