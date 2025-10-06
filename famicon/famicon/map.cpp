#pragma once
#include "map.h"

#include "ground.h"
#include "scaf.h"

#include <fstream>
#include <sstream>

CMap::CMap(vector<unique_ptr<BaseVector>>& base)
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			map[x + y * MAP_WIDTH] = -1;
		}
	}

	int i, j;
	//データロード
	ifstream fromFile("map\\map.csv");
	//ファイルがあるかどうかチェック
	if (!fromFile)
		return;

	string data;
	std::istringstream ss;
	i = 0;
	j = 0;
	//ファイルの終わりまで回す
	while (fromFile.eof() == false)
	{
		j = 0;
		//ファイルから一行分列のdataに格納
		getline(fromFile, data);
		data.insert(data.size(), ",");//行の端末に","をつける
		//取得した行から数字を取得
		while (data.size())
		{
			//セルの","までの文字数を探す
			int num_end = data.find(",");
			string num_str = data.substr(0, num_end);//数字を取得
			//数字を数値にしてmapに入れる
			ss = istringstream(num_str);
			ss >> map[j + i * MAP_WIDTH];
			//"数字,"までを削除
			data = data.erase(0, num_end + 1);
			j++;
		}
		i++;
	}

	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			Point p{ x * BLOCK_WIDTH,y * BLOCK_HEIGHT };
			switch (map[x + y * MAP_WIDTH])
			{
			case 0:
				base.emplace_back((unique_ptr<BaseVector>)new CGround(p));
				break;
			case 1:
				base.emplace_back((unique_ptr<BaseVector>)new CScaf(p));
				break;
			}
		}
	}
}

int CMap::Action(vector<unique_ptr<BaseVector>>& base)
{
	return 0;
}

void CMap::Draw()
{

}