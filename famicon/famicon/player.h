#pragma once
#include "objBase.h"

class CPlayer :public BaseVector
{
public:
	CPlayer(Point);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	int respawn_img{ -1 };

	float add_speed{ 0.25f };
	float SPEED{ 2.0f };

	float g{ 0.5f };

	bool Jump{ false };
	bool OnGround{ false };

	int walk_anim{ 0 };
	int drop_anim{ 0 };

	bool direction{ false };

	bool death{ false };
	int fall_time{ 0 };
	bool drop{ false };
	bool respawn{ false };

	int HP{ 0 };
};