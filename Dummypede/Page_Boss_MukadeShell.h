#pragma once
#include "WindowSystem.h"
// ★ここに必要なものをinclude
#include "WindowSystemManager.h"
#include "GameControl.h"
#include "CursorDecorator.h"

class WindowSystemManager;

class Page_Boss_MukadeShell : public WindowSystem {
private:
	WindowSystemManager& manager;

	String text;			// 入力した文字列
	String text_bot;		// コンピュータ側の文字列
	Array<String> text_log;	// これまでのテキストログ

	// アニメーション中・入力中
	int state;
	// コマンド入力
	int state_input;
	Stopwatch anim_timer;
	size_t pre_br_pos;		// 直近の改行文字の位置
	size_t text_length;		// 現在の文字列の表示する長さ

	void Draw() const override;
	void Update() override;

	// text_logにtextを流す
	void add_text_log(String const& str);

	// stateをアニメーションへ変更
	void changestate_anim(String const& str);
	void changestate_input();

	// コマンド処理
	void command_process();
	void command_help();
	void command_sword();
	void command_unusable();
	void command_unknown();

public:
	Page_Boss_MukadeShell(WindowSystemManager& manager);

	// 画面は一番上に描画したいのでこちらに書く
	void DrawDepth2() const override;

	void set_text_bot(String const& str);
};
