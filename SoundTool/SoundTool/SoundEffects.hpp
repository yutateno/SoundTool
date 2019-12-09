#pragma once
#include "DxLib.h"
#include <vector>
#include <string>


class SoundEffects
{
private:
	std::vector<std::string> m_name;
	std::vector<int> m_data;


public:
	SoundEffects();
	~SoundEffects();

	void Draw();

	void Process();

	void Load(char t_filePath[]);
};

