#pragma once
#include "WindowSystem.h"
// ★ここに必要なものをinclude
#include "WindowSystemManager.h"
#include "GameControl.h"
#include "CursorDecorator.h"

#include "Page_Light.h"
#include "Page_Ending.h"

class Page_MukadeShell : public WindowSystem {
private:
	static int access_level;	// アクセスレベル
	WindowSystemManager& manager;

	String text;			// 入力した文字列
	String text_bot;		// コンピュータ側の文字列
	Array<String> text_log;	// これまでのテキストログ

	// アニメーション中・入力中
	int state;
	// コマンド入力・cardkeyのパスワード入力・cardkeyの日数入力
	int state_input;
	Stopwatch anim_timer;
	size_t pre_br_pos;		// 直近の改行文字の位置
	size_t text_length;		// 現在の文字列の表示する長さ

	void Draw() const override;
	void Update() override;

	// text_logにtextを流す
	void add_text_log(String const & str);

	// stateをアニメーションへ変更
	void changestate_anim(String str);
	void changestate_input();

	// カードキーの文字列を返す
	String cardkey_str() const;

	// コマンド内容を理解
	void command_process(String str);
	// 各コマンドの処理関数
	void command_help();
	void command_cardkey();
	void command_light();
	void command_sword();
	void command_uninstall();
	void command_unknown();

	// 各コマンドの処理に用いる関数
	void command_cardkey_password();
	void command_cardkey_set_date();

public:
	Page_MukadeShell(WindowSystemManager& manager);

	// access_levelを取得
	static int get_access_level();

	// text_botに文字列を代入
	void set_text_bot(String const & str);

	// access_levelを変更
	static void set_access_level(int const level);
};
