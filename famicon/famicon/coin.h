#pragma once
#include"objBase.h"

class CCoin :public BaseVector
{
public:
	CCoin(bool);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	int anim_time{ 0 };
	bool turn;

	float g{ 0.5f };
	float speed{ 1.5f };

	bool get_coin{ false };
	bool on_ground{ false };
	bool in_pipe{ false };
};