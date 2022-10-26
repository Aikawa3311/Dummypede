#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"
#include "GameControl.h"
#include "WindowSystemManager.h"

#include "GameControl.h"

#include "Page_MukadeShell.h"

class Page_Password : public WindowSystem {
private:
	WindowSystemManager& manager;

	String text;			// 入力した文字列
	String editing_text;	// 入力して変換中の文字列
	RectF textarea_rect;	// 入力欄
	bool textarea_active;	// 入力欄の活動状態

	RectF message_rect;		// メッセージ表示領域
	Stopwatch anim_timer;

	String message;
	Stopwatch message_timer;

	void Draw() const override;
	void Update() override;

	// パスワード照合
	void password_confirm();

	// アニメーション用関数
	bool sync_anim_function(double const x) const;

	// メッセージ表示
	void message_display(String const & str);

public:
	Page_Password(WindowSystemManager& manager);
};

