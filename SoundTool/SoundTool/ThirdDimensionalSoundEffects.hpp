#pragma once

#include "DxLib.h"
#include <vector>
#include <string>


class ThirdDimensionalSoundEffects
{
private:
	std::vector<std::string> m_name;
	std::vector<int> m_data;


public:
	ThirdDimensionalSoundEffects();
	~ThirdDimensionalSoundEffects();

	void Draw();

	void Process();

	void Load(char t_filePath[]);
};

