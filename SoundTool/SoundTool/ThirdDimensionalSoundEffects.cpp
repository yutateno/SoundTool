#include "ThirdDimensionalSoundEffects.hpp"

ThirdDimensionalSoundEffects::ThirdDimensionalSoundEffects()
{
	std::vector<std::string>().swap(m_name);
	std::vector<int>().swap(m_data);
}

ThirdDimensionalSoundEffects::~ThirdDimensionalSoundEffects()
{
	for (size_t i = 0; i < m_data.size(); ++i)
	{
		DeleteSoundMem(m_data.at(i));
	}
	std::vector<int>().swap(m_data);
	std::vector<std::string>().swap(m_name);
}

void ThirdDimensionalSoundEffects::Draw()
{
	for (size_t i = 0; i < m_name.size(); ++i)
	{
		DrawFormatString(1280 / 2, i * 50, GetColor(255, 255, 255), "%s", m_name.at(i).c_str());
		DrawFormatString(1280 / 2, i * 50 + 20, GetColor(255, 255, 255), "%d", m_data.at(i));
	}
}

void ThirdDimensionalSoundEffects::Process()
{
}

void ThirdDimensionalSoundEffects::Load(char t_filePath[])
{
	SetCreate3DSoundFlag(TRUE);
	m_name.push_back(t_filePath);
	m_data.push_back(LoadSoundMem(t_filePath));
	SetCreate3DSoundFlag(FALSE);
}
