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

	fall_down = false;

	ID = TURTLE;

	pri = 2;
}

int CTurtle::Action(vector<unique_ptr<BaseVector>>& base)
{
	if (!pipe_in)
		vec.y += g;
	anim_time++;

	if (fallup_time == 600)
	{
		level++;
		fall_down = false;
		fallup_time = 0;
		vec.x = -speed * 3;
		anim_time = 0;
	}

	//起き上がるまでの時間
	if (fall_down)
	{
		fallup_time++;
	}
	
	if (!kick_off)
	{
		//当たり判定
		Point latepos{ pos.x,pos.y + vec.y };
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
					if ((*i)->vec.y != 0.0f)
					{
						if (fall_down)
						{
							vec.y = -7.0f;
							vec.x = -speed * 3;;
							pos.y = (*i)->pos.y - ImgHeight;
							fall_down = false;
							fallup_time = 0;
							anim_time = 0;
							level++;
						}
						else
						{
							vec.y = -7.0f;
							vec.x = 0.0f;
							pos.y = (*i)->pos.y - ImgHeight;
							fall_down = true;
							anim_time = 0;
						}
						break;
					}
					else
					{
						vec.y = 0;
						pos.y = (*i)->pos.y - ImgHeight;
						break;
					}
				}
			}
		}
	}
	
	//画面端に行ったとき、反対側の画面端から出るようにする
	if (!kick_off)
	{
		if (pos.x + vec.x + ImgWidth < 0)
		{
			pos.x = WINDOW_WIDTH;
		}
		if (pos.x + vec.x > WINDOW_WIDTH)
		{
			pos.x = -ImgWidth;
		}
	}

	if (!turn)
	{
		pos.x += vec.x;
		pos.y += vec.y;
	}
	else
	{
		pos.x -= vec.x;
		pos.y += vec.y;
	}

	if (!fall_down)
	{
		//歩くアニメーション
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
	}
	else
	{
		//ごろごろアニメーション
		if (anim_time < 30)
		{
			CutX = 96;
			CutY = 0;
		}
		else if (anim_time < 60)
		{
			CutX = 128;
			CutY = 0;
		}
		if (anim_time == 60)
		{
			anim_time = 0;
		}
	}

	if (level > 2)level = 2;

	//起き上がり１回目
	if (level == 1)
	{
		CutY = 32;
	}
	//起き上がり２回目もしくは最後の１匹
	if (level == 2)
	{
		CutY = 64;
	}

	//マリオに蹴られた後に画面下に行くと消す
	if (kick_off && pos.y > WINDOW_HEIGHT)
		FLAG = false;

	return 0;
}

void CTurtle::Draw()
{
	if (!turn)
		DrawRectGraph(pos.x, pos.y, CutX, CutY, ImgWidth, ImgHeight, img, true, false);
	else
		DrawRectGraph(pos.x, pos.y, CutX, CutY, ImgWidth, ImgHeight, img, true, true);
}