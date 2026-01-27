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

	selector_pos = { 104,240 };
}

int CTitle::Update() {

	//ƒQ[ƒ€‚ÉˆÚ“®
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		manager->Scene_Delete();
		manager->scene = new CGame(manager);
	}

	return 0;
}

void CTitle::Draw()
{
	DrawGraph(0, 0, title_img, true);
	DrawGraph(selector_pos.x, selector_pos.y, selector_img, true);
}

CTitle::~CTitle()
{

}