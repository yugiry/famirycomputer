#pragma once
#include "objBase.h"

class CPipe :public BaseVector
{
public:
	//À•WAí—Ş
	CPipe(Point, int);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	int type{ -1 };

	Point hit{ 0,0 };
};