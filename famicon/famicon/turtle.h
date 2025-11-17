#pragma once
#include "objBase.h"

class CTurtle :public BaseVector
{
public:
	CTurtle(bool);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	float g{ 0.5f };			//重力
	float speed{ 0.5f };		//移動速度
	int anim_time{ 0 };			//アニメーションを動かす時間の計測用
	int level{ 0 };				//倒れた後に起き上がったか

	int fallup_time{ 0 };		//起き上がるまでの時間の計測用

	bool fall_down{ false };	//倒れているかどうか
	bool kick_off{ false };		//蹴られたかどうか
	bool turn{ false };			//顔の向き：true->右、false->左
	bool in_pipe{ false };		//土管に入っている
	bool respawn{ false };		//上の土管に戻る判定
	bool spawn{ false };		//スポーン
	bool turn_anim{ false };
	bool OnGround{ false };		//地面に乗っているか
};