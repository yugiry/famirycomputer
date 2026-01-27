#pragma once
#include "objBase.h"

class CTitle :public CScene
{
private:
public:
	vector<unique_ptr<BaseVector>> base;

	//コンストラクタ
	CTitle(CManager*);

	//デストラクタ
	~CTitle();

	int Update();//更新処理
	void Draw();//描画処理

	int title_img{ -1 };
	int selector_img{ -1 };
	bool push{ false };

	Point selector_pos;

	//104,240
	//272
	//304
	//336

	//CCamera* camera;//カメラオブジェクト
};