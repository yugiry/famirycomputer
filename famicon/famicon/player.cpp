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
		//A�L�[��D�L�[��������Ă��Ȃ����n�ʂɑ������Ă���ꍇ
		//x�x�N�g���ƕ����A�j���[�V�������O�ɂ���
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

		//�ړ�
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

		//A�L�[��������D�L�[��������Ă���ƃA�j���[�V�����𓮂���
		if ((CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_D)) && OnGround)
		{
			walk_anim++;
		}

		//�ړ����x��"SPEED"�ȏ�ɂȂ�Ȃ��悤�ɂ���
		if (vec.x < -SPEED)vec.x = -SPEED;
		if (vec.x > SPEED)vec.x = SPEED;

		//�W�����v
		if (CheckHitKey(KEY_INPUT_SPACE) && !Jump && OnGround)
		{
			vec.y -= 11.0f;
		}
		Jump = CheckHitKey(KEY_INPUT_SPACE);

		OnGround = false;

		//�u���b�N�Ƃ̓����蔻��
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

		//�G�Ƃ̓����蔻��
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

	//��ʒ[�ɍs�����Ƃ��A���Α��̉�ʒ[����o��悤�ɂ���
	if (pos.x + vec.x + ImgWidth < 0)
	{
		pos.x = WINDOW_WIDTH;
	}
	if (pos.x + vec.x > WINDOW_WIDTH)
	{
		pos.x = -ImgWidth;
	}

	//�ړ�����
	pos.x += vec.x;
	pos.y += vec.y;

	//�ړ��x�N�g���ɂ���ăv���C���[�̌�����ύX
	if (vec.x < 0)
	{
		direction = true;
	}
	else if (vec.x > 0)
	{
		direction = false;
	}

	//�W�����v�A�j���[�V����
	if (!OnGround && !death)
	{
		CutX = 32;
		CutY = 48;
	}
	//�����A�j���[�V����
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