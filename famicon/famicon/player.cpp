#pragma once
#include "player.h"
#include "turtle.h"
#include "function.h"

CPlayer::CPlayer(Point p)
{
	pos = p;

	img = LoadGraph("image\\player.png");
	
	ImgWidth = 32;
	ImgHeight = 48;

	CutX = 0;
	CutY = 0;

	ID = PLAYER;
}

int CPlayer::Action(vector<unique_ptr<BaseVector>>& base)
{

	if (!death)
	{
		//AキーとDキーが押されていないかつ地面に足がついている場合
		//xベクトルと歩くアニメーションを０にする
		if (!CheckHitKey(KEY_INPUT_A) && !CheckHitKey(KEY_INPUT_D) && OnGround)
		{
			walk_anim = 0;

			if (vec.x > 0)
			{
				vec.x += -add_speed;
				CutX = 0;
				CutY = 48;
			}
			if (vec.x < 0)
			{
				vec.x += add_speed;
				CutX = 0;
				CutY = 48;
			}
		}
		vec.y += g;

		//移動
		if (CheckHitKey(KEY_INPUT_A) && OnGround)
		{
			if (vec.x > 0)
			{
				CutX = 0;
				CutY = 48;
				walk_anim = 0;
			}
			vec.x += -add_speed;
		}
		if (CheckHitKey(KEY_INPUT_D) && OnGround)
		{
			if (vec.x < 0)
			{
				CutX = 0;
				CutY = 48;
				walk_anim = 0;
			}
			vec.x += add_speed;
		}

		//AキーもしくはDキーが押されているとアニメーションを動かす
		if ((CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_D)) && OnGround)
		{
			walk_anim++;
		}

		//移動速度が"SPEED"以上にならないようにする
		if (vec.x < -SPEED)vec.x = -SPEED;
		if (vec.x > SPEED)vec.x = SPEED;

		//ジャンプ
		if (CheckHitKey(KEY_INPUT_SPACE) && !Jump && OnGround)
		{
			vec.y -= 11.0f;
		}
		Jump = CheckHitKey(KEY_INPUT_SPACE);

		OnGround = false;

		//ブロックとの当たり判定
		Point latepos{ pos.x + vec.x,pos.y + vec.y };
		for (auto i = base.begin(); i != base.end(); i++)
		{
			if ((*i)->ID == GROUND)
			{
				if (HitCheck_box(latepos.x, latepos.y + ImgHeight - 10, (*i)->pos.x, (*i)->pos.y, ImgWidth, 10, (*i)->ImgWidth, 5))
				{
					vec.y = 0;
					pos.y = (*i)->pos.y - ImgHeight;
					OnGround = true;
					break;
				}
			}
			if ((*i)->ID == SCAF)
			{
				if (HitCheck_box(latepos.x, latepos.y + ImgHeight - 10, (*i)->pos.x, (*i)->pos.y, ImgWidth, 10, (*i)->ImgWidth, 5) && vec.y > 0)
				{
					vec.y = 0;
					pos.y = (*i)->pos.y - ImgHeight;
					OnGround = true;
					break;
				}
				if (HitCheck_box(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y + (*i)->ImgWidth - 10, ImgWidth, 10, (*i)->ImgWidth, 5) && vec.y < 0)
				{
					vec.y = 0;
					break;
				}
			}
		}

		//敵との当たり判定
		for (auto i = base.begin(); i != base.end(); i++)
		{
			if ((*i)->ID == TURTLE)
			{
				if (HitCheck_box(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y, ImgWidth, ImgHeight, (*i)->ImgWidth, (*i)->ImgHeight))
				{
					CTurtle* turtle = (CTurtle*)(*i).get();
					if (!turtle->fall_down)
					{
						death = true;
						CutX = 64;
						CutY = 48;
						vec.x = 0;
						vec.y = 0;
						fall_time = 30;
						break;
					}
					else
					{

					}
				}
			}
		}
	}
	else
	{

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

	//移動処理
	pos.x += vec.x;
	pos.y += vec.y;

	//移動ベクトルによってプレイヤーの向きを変更
	if (vec.x < 0)
	{
		direction = true;
	}
	else if (vec.x > 0)
	{
		direction = false;
	}

	//ジャンプアニメーション
	if (!OnGround && !death)
	{
		CutX = 32;
		CutY = 48;
	}
	//歩きアニメーション
	else
	{
		if (!death)
		{
			if (walk_anim == 0 && vec.x == 0.0f)
			{
				CutX = 0;
				CutY = 0;
			}
			if (walk_anim == 2)
			{
				CutX = 32;
				CutY = 0;
			}
			if (walk_anim == 4)
			{
				CutX = 64;
				CutY = 0;
			}
			if (walk_anim == 6)
			{
				CutX = 96;
				CutY = 0;
				walk_anim = 1;
			}
		}
	}

	return 0;
}

void CPlayer::Draw()
{
	if (!direction)
		DrawRectGraph(pos.x, pos.y, CutX, CutY, ImgWidth, ImgHeight, img, true, false);
	else
		DrawRectGraph(pos.x, pos.y, CutX, CutY, ImgWidth, ImgHeight, img, true, true);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "%f", vec.x);
}