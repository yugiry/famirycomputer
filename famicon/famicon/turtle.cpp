#pragma once
#include "turtle.h"
#include "function.h"

CTurtle::CTurtle(bool _turn)
{
	img = LoadGraph("image\\turtle.png");

	ImgWidth = 32;
	ImgHeight = 32;

	CutX = 0;
	CutY = 0;

	vec.x = -speed;

	turn = _turn;

	if (!turn)
	{
		pos = { float((WINDOW_WIDTH - 112) + ImgWidth),48 };
	}
	else
	{
		pos = { float(112 - ImgWidth),48 };
	}

	spawn = true;

	fall_down = false;

	ID = TURTLE;

	pri = 2;
}

int CTurtle::Action(vector<unique_ptr<BaseVector>>& base)
{
	if (spawn)
	{
		anim_time++;
		if (!turn)
		{
			if (pos.x >= WINDOW_WIDTH - 112 - ImgWidth)pos.x -= 1.0f;
			if (pos.x < WINDOW_WIDTH - 112 - ImgWidth)
			{
				spawn = false;
			}
		}
		else
		{
			if (pos.x <= 112)pos.x += 1.0f;
			if (pos.x > 112)
			{
				spawn = false;
			}
		}

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
		if (!in_pipe)
			vec.y += g;
		anim_time++;

		//土管に入った時
		if (in_pipe)
		{
			if (pos.y >= WINDOW_HEIGHT - (44 + ImgWidth))pos.y -= 1.0f;
			else if (!respawn)
			{
				//亀の向き
				if (!turn)
				{
					if (pos.x >= 32)pos.x -= 1.0f;
					else
					{
						turn = respawn = true;
						pos = { float(112 - ImgWidth),48 };
					}
				}
				else
				{
					if (pos.x <= WINDOW_WIDTH - 32)pos.x += 1.0f;
					else
					{
						turn = false;
						respawn = true;
						pos = { float((WINDOW_WIDTH - 112) + ImgWidth),48 };
					}
				}
			}
			else if (respawn)
			{
				if (!turn)
				{
					if (pos.x >= WINDOW_WIDTH - 112 - ImgWidth)pos.x -= 1.0f;
					if (pos.x < WINDOW_WIDTH - 112 - ImgWidth)
					{
						in_pipe = respawn = false;
					}
				}
				else
				{
					if (pos.x <= 112)pos.x += 1.0f;
					if (pos.x > 112)
					{
						in_pipe = respawn = false;
					}
				}
			}
		}
		else
		{
			//時間が来たら起き上がる
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

			//通常時の当たり判定
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

			//向きによって移動方向を変更
			if (!turn_anim)
			{
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
			}
		}

		for (int i = 0; i < base.size(); i++)
		{
			if (base[i]->ID == TURTLE)
			{
				if (pos.x != base[i]->pos.x || pos.y != base[i]->pos.y)
					if (HitCheck_box(pos.x + vec.x, pos.y + vec.y, base[i]->pos.x + base[i]->vec.x, base[i]->pos.y + base[i]->vec.y, ImgWidth, ImgHeight))
					{
						CTurtle* turtle = (CTurtle*)base[i].get();
						turn_anim = true;
						anim_time = 0;
						turtle->turn_anim = true;
						turtle->anim_time = 0;
					}
			}
		}

		if (turn_anim)
		{
			if (anim_time < 10)
			{
				CutY = 160;
			}
			else if (anim_time < 20)
			{
				if (turn)turn = false;
				else turn = true;
			}
			else if (anim_time == 30)turn_anim = false;
		}
		//アニメーション関係
		else
		{
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

	}

	return 0;
}

void CTurtle::Draw()
{
	if (!turn)
		DrawRectGraph(pos.x, pos.y, CutX, CutY, ImgWidth, ImgHeight, img, true, false);
	else
		DrawRectGraph(pos.x, pos.y, CutX, CutY, ImgWidth, ImgHeight, img, true, true);
}