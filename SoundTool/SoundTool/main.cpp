#pragma once

#include "InputControl_Lib.hpp"
#include "DxLib.h"
#include <string>

#include "BackGroundMusic.hpp"
#include "SoundEffects.hpp"
#include "ThirdDimensionalSoundEffects.hpp"


bool Init(const int t_winWidth, const int t_winHeight, const int t_bitColor, std::string t_projectName)
{
	//// �E�B���h�E�T�C�Y�����߂�
	//int winWidth = t_winWidth;
	//int winHeight = t_winHeight;
	//int bitColor = t_bitColor;

#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ���O�e�L�X�g�o�͂���
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ���O�e�L�X�g�o�͂��Ȃ�
#endif


	SetWindowText(t_projectName.c_str());					// ���C���E�C���h�E�̃E�C���h�E�^�C�g����ύX����
	SetBackgroundColor(125, 125, 125);			// �w�i�F��ύX
	ChangeWindowMode(TRUE);						// �E�B���h�E�Y���[�h�ɂ�����


	SetGraphMode(t_winWidth, t_winHeight, t_bitColor);			// ��ʃT�C�Y�ݒ�
	//GetDefaultState(&winWidth, &winHeight, &bitColor);		// �f�t�H���g�E�B���h�E�l�𓾂�
	SetWindowSize(t_winWidth, t_winHeight);						// �f�t�H���g�E�B���h�E�T�C�Y�ɍ��킹�ăQ�[���T�C�Y��ύX


	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return false;			// �G���[���N�����璼���ɏI��
	}


	SetDrawScreen(DX_SCREEN_BACK);	// �w�i�`��

	SetAlwaysRunFlag(TRUE);				// ����ʂł���ɃA�N�e�B�u�ɕύX
	SetDragFileValidFlag(TRUE);			// �h���b�O�A���h�h���b�v�̗L����


	return true;
}


/// --------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (Init(1280, 720, 32, "SoundTool") == false) return -1;

	InputControl::KeyData::UpDate();
	InputControl::MouseData::UpDate();

	SoundEffects m_soundEffects = SoundEffects();
	BackGroundMusic m_backGroundMusic = BackGroundMusic();
	ThirdDimensionalSoundEffects m_3DsoundEffects = ThirdDimensionalSoundEffects();


	// ���C�����[�v
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !InputControl::KeyData::IsCheckEnd())
	{
		InputControl::KeyData::UpDate();
		InputControl::MouseData::UpDate();

		DrawLine(1280 / 2, 0, 1280 / 2, 720, GetColor(0, 0, 0));
		DrawLine(0, 720 / 2, 1280 / 2, 720 / 2, GetColor(0, 0, 0));

		// �h���b�O�A���h�h���b�v���s��ꂽ�Ƃ�
		if (GetDragFileNum() > 0)
		{
			char filePath[MAX_PATH];				// �t�@�C���̃p�X���������鉼�u���ϐ�

			GetDragFilePath(filePath);				// �h���b�O�A���h�h���b�v�̃p�X���擾

			if (InputControl::MouseData::GetMouseArea().x < 1024 / 2)
			{
				if (InputControl::MouseData::GetMouseArea().y < 720 / 2)
				{
					m_soundEffects.Load(filePath);
				}
				else
				{
					m_3DsoundEffects.Load(filePath);
				}
			}
			else
			{
				m_backGroundMusic.Load(filePath);
			}
		}

		m_soundEffects.Draw();
		m_backGroundMusic.Draw();
		m_3DsoundEffects.Draw();
	}

	m_soundEffects.~SoundEffects();
	m_backGroundMusic.~BackGroundMusic();
	m_3DsoundEffects.~ThirdDimensionalSoundEffects();

	// �폜
	DxLib::DxLib_End();		// DX���C�u�����̌�n��


	return 0;
}