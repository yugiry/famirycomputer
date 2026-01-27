#pragma once
#include "DxLib.h"
#include "Scene_Manager.h"
#include "title.h"
#include "game.h"
#include "function.h"

CTitle::CTitle(CManager* p) :CScene(p) {
	title_img = LoadGraph("image\\title.png");
	selector_img = LoadGraph("image\\selector.png");
	push = true;

	point = 0;
}

int CTitle::Update() {

	//ƒQ[ƒ€‚ÉˆÚ“®
	if (CheckHitKey(KEY_INPUT_RETURN) && !push)
	{
		manager->Scene_Delete();
		manager->scene = new CGame(manager);
	}

	if (CheckHitKey(KEY_INPUT_W) && !push)
	{
		point--;
	}
	if (CheckHitKey(KEY_INPUT_S) && !push)
	{
		point++;
	}
	push = CheckHitKey(KEY_INPUT_W) | CheckHitKey(KEY_INPUT_S) | CheckHitKey(KEY_INPUT_RETURN);

	if (point < 0)point = 0;
	if (point > 3)point = 3;

	return 0;
}

void CTitle::Draw()
{
	DrawGraph(0, 0, title_img, true);
	DrawGraph(selector_pos[point].x, selector_pos[point].y, selector_img, true);
}

CTitle::~CTitle()
{

}