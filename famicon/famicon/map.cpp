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
	//�f�[�^���[�h
	ifstream fromFile("map\\map.csv");
	//�t�@�C�������邩�ǂ����`�F�b�N
	if (!fromFile)
		return;

	string data;
	std::istringstream ss;
	i = 0;
	j = 0;
	//�t�@�C���̏I���܂ŉ�
	while (fromFile.eof() == false)
	{
		j = 0;
		//�t�@�C�������s�����data�Ɋi�[
		getline(fromFile, data);
		data.insert(data.size(), ",");//�s�̒[����","������
		//�擾�����s���琔�����擾
		while (data.size())
		{
			//�Z����","�܂ł̕�������T��
			int num_end = data.find(",");
			string num_str = data.substr(0, num_end);//�������擾
			//�����𐔒l�ɂ���map�ɓ����
			ss = istringstream(num_str);
			ss >> map[j + i * MAP_WIDTH];
			//"����,"�܂ł��폜
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