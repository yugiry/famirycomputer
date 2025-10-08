#pragma once
#include "objBase.h"

class CPlayer :public BaseVector
{
public:
	CPlayer(Point);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	float SPEED{ 4.0f };

	float g{ 0.5f };

	bool Jump{ false };
	bool OnGround{ false };
};