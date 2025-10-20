#pragma once
#include "objBase.h"

class CPipe :public BaseVector
{
public:
	//座標、向き
	CPipe(Point, bool);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	bool turn{ false };		//false->左、true->右
};