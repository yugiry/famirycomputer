#pragma once
#include "objBase.h"

class CTurtle :public BaseVector
{
public:
	CTurtle();

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();
};