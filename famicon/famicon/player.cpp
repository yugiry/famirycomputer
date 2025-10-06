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
	vec.x = 0;
	vec.y = g;

	if (CheckHitKey(KEY_INPUT_A))
	{
		vec.x = -SPEED;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		vec.x = SPEED;
	}

	for (auto i = base.begin(); i != base.end(); i++)
	{
		Point latepos{ pos.x + vec.x,pos.y + vec.y };
		if ((*i)->ID == GROUND)
		{
			if (HitCheck_box(this, (*i).get()))
			{
				vec.y = 0;
			}

		}
		if ((*i)->ID == SCAF)
		{
			if (HitCheck_box(this, (*i).get()))
			{
				vec.y = 0;
			}
		}
	}

	pos.x += vec.x;
	pos.y += vec.y;

	return 0;
}

void CPlayer::Draw()
{
	DrawGraph(pos.x, pos.y, img, true);
}