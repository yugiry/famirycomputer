//ゲームシーン
#include "DxLib.h"
#include "Scene_Manager.h"
#include "game.h"
#include "result.h"
#include "function.h"

#include "player.h"
#include "map.h"
#include "turtle.h"
#include "pipe.h"
#include "pow.h"

//コンストラクタ
CGame::CGame(CManager* p) :CScene(p){
	base.emplace_back((unique_ptr<BaseVector>)new CMap(base));
	Point pos{ 128,WINDOW_HEIGHT - 80 };
	base.emplace_back((unique_ptr<BaseVector>)new CPlayer(pos));
	pos.x = WINDOW_WIDTH - 32;
	//base.emplace_back((unique_ptr<BaseVector>)new CTurtle(pos));

	pos.x = WINDOW_WIDTH / 2; pos.y = WINDOW_HEIGHT / 2;
	base.emplace_back((unique_ptr<BaseVector>)new CPow(pos));

	//土管生成
	{
		pos.x = 0; pos.y = WINDOW_HEIGHT - 85;
		base.emplace_back((unique_ptr<BaseVector>)new CPipe(pos, 0));
		pos.x = WINDOW_WIDTH - 64;
		base.emplace_back((unique_ptr<BaseVector>)new CPipe(pos, 1));
		pos.x = 0; pos.y = 40;
		base.emplace_back((unique_ptr<BaseVector>)new CPipe(pos, 2));
		pos.x = WINDOW_WIDTH - 112;
		base.emplace_back((unique_ptr<BaseVector>)new CPipe(pos, 3));
	}
}

//更新処理
int CGame::Update(){

	if (Espawn_time == 0)
	{
		base.emplace_back((unique_ptr<BaseVector>)new CTurtle(true));
		turtle_num++;
	}
	else if (Espawn_time == spawn_cool)
	{
		base.emplace_back((unique_ptr<BaseVector>)new CTurtle(false));
		turtle_num++;
	}
	else if (Espawn_time == spawn_cool * 3)
	{
		base.emplace_back((unique_ptr<BaseVector>)new CTurtle(false));
		turtle_num++;
	}

	Espawn_time++;

	//亀がすべて倒れたらリザルトに行く
	if (turtle_num == 0)
	{
		manager->Scene_Delete();
		manager->scene = new CResult(manager);
	}

	//更新処理
	for (int i = 0; i < base.size(); i++)
		switch (base[i]->Action(base))
		{
		case 1:
			turtle_num--;
			break;
		}

	//削除処理
	for (auto i = base.begin(); i != base.end();)
		(*i)->FLAG ? i++ : i = base.erase(i);

	//オブジェクトのソート処理(クイックソート)
	ObjSort_Quick(base, 0, base.size() - 1);

	return 0;
}

//描画処理
void CGame::Draw()
{
	//オブジェクト個数
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Object_Count = %d", base.size());
	
	for (int i = 0; i < base.size(); i++)
		if(base[i]->FLAG) base[i]->Draw();

}

CGame::~CGame()
{

}
