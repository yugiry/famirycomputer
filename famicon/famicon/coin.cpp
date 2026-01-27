#pragma once
#include "coin.h"
#include "function.h"

CCoin::CCoin(bool _turn)
{
	turn = _turn;

	img = LoadGraph("image\\coin.png");
	CutY = 0;

	ImgWidth = 16;
	ImgHeight = 32;
}

int CCoin::Action(vector<unique_ptr<BaseVector>>& base)
{
	if (in_pipe)
	{
		
	}
	else
	{
		vec.y += g;

		//“–‚½‚è”»’è
		Point latepos{ pos.x,pos.y + vec.y };
		for (auto i = 0; i < base.size(); i++)
		{
			if (base[i]->ID == GROUND)
			{
				if (HitCheck_box(latepos.x, latepos.y + ImgHeight / 2, base[i]->pos.x, base[i]->pos.y, ImgWidth, ImgHeight / 2, base[i]->ImgWidth, 5))
				{
					vec.y = 0;
					pos.y = base[i]->pos.y - ImgHeight;
					on_ground = true;
					break;
				}
			}
			if (base[i]->ID == SCAF)
			{
				if (HitCheck_box(latepos.x, latepos.y + ImgHeight / 2, base[i]->pos.x, base[i]->pos.y, ImgWidth, ImgHeight / 2, base[i]->ImgWidth, 5))
				{
					if (base[i]->vec.y != 0.0f)
					{
						get_coin = true;
					}

					vec.y = 0;
					pos.y = base[i]->pos.y - ImgHeight;
					on_ground = true;
					break;
				}
			}
			if (base[i]->ID == PLAYER)
			{
				if (HitCheck_box(latepos.x, latepos.y, base[i]->pos.x, base[i]->pos.y, ImgWidth, ImgHeight, base[i]->ImgWidth, base[i]->ImgHeight))
				{
					get_coin = true;
				}
			}
		}

		if (get_coin)
		{
			FLAG = false;
			return 3;
		}

		//ˆÚ“®ˆ—
		{
			if (turn)
			{
				vec.x = speed;
			}
			else
			{
				vec.x = -speed;
			}

			pos.x += vec.x;
			pos.y += vec.y;

			if (pos.x > WINDOW_WIDTH)pos.x = -ImgWidth;
			if (pos.x < -ImgWidth)pos.x = WINDOW_WIDTH;
		}
	}

	if (anim_time == 4)
	{
		CutX = 16;
	}
	else if (anim_time == 8)
	{
		CutX = 32;
	}
	else if (anim_time == 12)
	{
		CutX = 48;
	}
	else if (anim_time == 16)
	{
		CutX = 64;
	}
	else if (anim_time == 20)
	{
		anim_time = 0;
		CutX = 0;
	}

	anim_time++;

	return 0;
}

void CCoin::Draw()
{
	DrawRectGraph(pos.x, pos.y, CutX, CutY, ImgWidth, ImgHeight, img, true);
}