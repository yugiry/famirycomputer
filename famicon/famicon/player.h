#pragma once
#include "objBase.h"

class CPlayer :public BaseVector
{
public:
	CPlayer(Point);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	float add_speed{ 0.2f };
	float SPEED{ 2.0f };

	float g{ 0.5f };

	bool Jump{ false };
	bool OnGround{ false };

	int walk_anim{ false };

	bool direction{ false };
};