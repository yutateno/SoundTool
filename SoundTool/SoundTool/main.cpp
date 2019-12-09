#pragma once

#include "InputControl_Lib.hpp"
#include "DxLib.h"
#include <string>

#include "BackGroundMusic.hpp"
#include "SoundEffects.hpp"
#include "ThirdDimensionalSoundEffects.hpp"


bool Init(const int t_winWidth, const int t_winHeight, const int t_bitColor, std::string t_projectName)
{
	//// ウィンドウサイズを決める
	//int winWidth = t_winWidth;
	//int winHeight = t_winHeight;
	//int bitColor = t_bitColor;

#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ログテキスト出力する
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ログテキスト出力しない
#endif


	SetWindowText(t_projectName.c_str());					// メインウインドウのウインドウタイトルを変更する
	SetBackgroundColor(125, 125, 125);			// 背景色を変更
	ChangeWindowMode(TRUE);						// ウィンドウズモードにさせる


	SetGraphMode(t_winWidth, t_winHeight, t_bitColor);			// 画面サイズ設定
	//GetDefaultState(&winWidth, &winHeight, &bitColor);		// デフォルトウィンドウ値を得る
	SetWindowSize(t_winWidth, t_winHeight);						// デフォルトウィンドウサイズに合わせてゲームサイズを変更


	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return false;			// エラーが起きたら直ちに終了
	}


	SetDrawScreen(DX_SCREEN_BACK);	// 背景描画

	SetAlwaysRunFlag(TRUE);				// 裏画面でも常にアクティブに変更
	SetDragFileValidFlag(TRUE);			// ドラッグアンドドロップの有効化


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


	// メインループ
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !InputControl::KeyData::IsCheckEnd())
	{
		InputControl::KeyData::UpDate();
		InputControl::MouseData::UpDate();

		DrawLine(1280 / 2, 0, 1280 / 2, 720, GetColor(0, 0, 0));
		DrawLine(0, 720 / 2, 1280 / 2, 720 / 2, GetColor(0, 0, 0));

		// ドラッグアンドドロップが行われたとき
		if (GetDragFileNum() > 0)
		{
			char filePath[MAX_PATH];				// ファイルのパスを所持する仮置き変数

			GetDragFilePath(filePath);				// ドラッグアンドドロップのパスを取得

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

	// 削除
	DxLib::DxLib_End();		// DXライブラリの後始末


	return 0;
}