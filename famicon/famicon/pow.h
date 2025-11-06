#pragma once
#include "objBase.h"

class CPow :public BaseVector
{
public:
	CPow(Point);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	int plosion_time{ 3 };
};