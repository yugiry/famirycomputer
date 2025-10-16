#pragma once
#include "objBase.h"

class CTurtle :public BaseVector
{
public:
	CTurtle(Point);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	float g{ 0.5f };
	float speed{ 0.5f };
	int anim_time{ 0 };

	bool fall_down{ false };
};