#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"
#include "WindowSystemManager.h"

#include "GameControl.h"

#include "Page_Boss.h"

class Page_Door : public WindowSystem {
private:
	WindowSystemManager& manager;

	// 0で閉・1で開
	static int door_state;

	String text;			// 入力した文字列
	String editing_text;	// 入力して変換中の文字列
	RectF textarea_rect;	// 入力欄
	bool textarea_active;	// 入力欄の活動状態

	// 待機中・ドアが開くまでのウェイト・ドアが開いてからのウェイト
	int state;
	Stopwatch anim_timer;

	// anim_stateの変更
	void changestate_wait();
	void changestate_open();

	void Draw() const override;
	void Update() override;

public:
	Page_Door(WindowSystemManager& manager);
};

