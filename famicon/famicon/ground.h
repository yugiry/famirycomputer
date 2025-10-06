#pragma once
#include "objBase.h"

class CGround :public BaseVector
{
public:
	CGround(Point);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();
};