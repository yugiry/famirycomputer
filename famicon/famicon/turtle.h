#pragma once
#include "objBase.h"

class CTurtle :public BaseVector
{
public:
	CTurtle(Point);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	float g{ 0.5f };			//重力
	float speed{ 0.5f };		//移動速度
	int anim_time{ 0 };			//アニメーションを動かす時間の計測用
	int level{ 0 };				//倒れた後に起き上がったか

	int fallup_time{ 0 };		//起き上がるまでの時間の計測用

	bool fall_down{ false };	//倒れているかどうか
	bool kick_off{ false };		//蹴られたかどうか
	bool turn{ false };			//false->右、true->左
};