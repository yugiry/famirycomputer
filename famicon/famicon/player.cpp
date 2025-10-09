#include "player.h"
#include "function.h"

CPlayer::CPlayer(Point p)
{
	pos = p;

	img = LoadGraph("image\\player.png");
	
	ImgWidth = 32;
	ImgHeight = 48;

	ID = PLAYER;
}

int CPlayer::Action(vector<unique_ptr<BaseVector>>& base)
{
	if (!CheckHitKey(KEY_INPUT_A) && !CheckHitKey(KEY_INPUT_D))
		vec.x = 0;
	vec.y += g;

	if (CheckHitKey(KEY_INPUT_A) && OnGround)
	{
		vec.x += -add_speed;
	}
	if (CheckHitKey(KEY_INPUT_D) && OnGround)
	{
		vec.x += add_speed;
	}

	if (vec.x < -SPEED)vec.x = -SPEED;
	if (vec.x > SPEED)vec.x = SPEED;

	if (CheckHitKey(KEY_INPUT_SPACE) && !Jump && OnGround)
	{
		vec.y -= 11.0f;
	}
	Jump = CheckHitKey(KEY_INPUT_SPACE);

	OnGround = false;

	for (auto i = base.begin(); i != base.end(); i++)
	{
		Point latepos{ pos.x + vec.x,pos.y + vec.y };
		if ((*i)->ID == GROUND)
		{
			if (HitCheck_box(this, (*i).get()))
			{
				vec.y = 0;
				pos.y = (*i)->pos.y - ImgHeight;
				OnGround = true;
			}
		}
		if ((*i)->ID == SCAF)
		{
			if (HitCheck_box(latepos.x, latepos.y + ImgHeight - 10, (*i)->pos.x, (*i)->pos.y, ImgWidth, 10, (*i)->ImgWidth, 5) && vec.y > 0)
			{
				vec.y = 0;
				pos.y = (*i)->pos.y - ImgHeight;
				OnGround = true;
			}
			if (HitCheck_box(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y + (*i)->ImgWidth - 10, ImgWidth, 10, (*i)->ImgWidth, 5) && vec.y < 0)
			{
				vec.y = 0;
			}
		}
	}

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

	return 0;
}

void CPlayer::Draw()
{
	DrawGraph(pos.x, pos.y, img, true);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "%f", vec.x);
}