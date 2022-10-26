#pragma once
#include <Siv3d.hpp>
#include "CursorDecorator.h"

//class GameControl{
//public:
//	GameControl();
//
//	// カードキーの所持状態
//	bool cardkey_flag;
//
//	// カードキーの入力文字列
//	String cardkey_date;
//
//	// Centipedeゲームのハイスコア
//	int centipede_highscore;
//};

namespace GameControl {
	// カードキー所持フラグ
	extern bool flag_cardkey;

	// カードキーの年月日
	extern String cardkey_date;

	// CentipedeGameのハイスコア
	extern int centipede_highscore;

	// カーソル描画
	extern CursorDecorator decorator;

	// ボス撃破フラグ
	extern bool boss_win;

	// クリアフラグ
	extern bool flag_clear;

	// シェーダーフラグ
	extern bool flag_shader;

	// readme書き換えフラグ
	extern bool flag_readme;

	namespace Achievement {
		// centipedeで100点以上
		extern bool hundred_centipede;
		// Bossノーダメージ撃破
		extern bool nodamage;
		// creapy検索
		extern bool creapy;
	}

	// カードキーの描画用
	String cardkey_str();

	// readme書き換え
	void readme_change();
}
