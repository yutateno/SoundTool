#pragma once

#include "DxLib.h"
#include <vector>
#include <string>


class BackGroundMusic
{
private:
	std::vector<std::string> m_name;
	std::vector<int> m_data;


public:
	BackGroundMusic();
	~BackGroundMusic();

	void Draw();

	void Process();

	void Load(char t_filePath[]);
};

