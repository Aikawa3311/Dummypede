// Pageのテンプレート
#pragma once
#include "WindowSystem.h"
#include "WindowSystemManager.h"
#include "GameControl.h"

#include "Page_FeedFiles.h"

class Page_ISBN : public WindowSystem {
private:
	WindowSystemManager& manager;

	void Draw() const override;
	void Update() override;

	String page_name;

	String text;			// 入力した文字列
	String editing_text;	// 入力して変換中の文字列
	RectF textarea_rect;	// 入力欄
	bool textarea_active;	// 入力欄の活動状態

	bool donate_page = false;
	RectF donate_button;	// 寄付ボタン
	RectF link_button;		// リンク判定

	// エンターキー押下時の動作
	void jump_page();

public:
	Page_ISBN(WindowSystemManager& manager, String const & str = U"ISBN Code");
};
