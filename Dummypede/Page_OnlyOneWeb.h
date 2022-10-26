// Pageのテンプレート
#pragma once
#include "WindowSystem.h"
// ★ここに必要なものをinclude
#include "WindowSystemManager.h"

#include "GameControl.h"

// 接続先
#include "Page_404.h"
#include "Page_Dummypede.h"
#include "Page_AlotofFiles.h"
#include "Page_Myriapod.h"
#include "Page_MyriadTetrapod.h"
#include "Page_Pigpen.h"
#include "Page_ISBN.h"

class Page_OnlyOneWeb : public WindowSystem {
private:
	WindowSystemManager & manager;

	String text;			// 入力した文字列
	String editing_text;	// 入力して変換中の文字列
	RectF textarea_rect;	// 入力欄
	bool textarea_active;	// 入力欄の活動状態

	void Draw() const override;
	void Update() override;

	// 現在のtextから特定のページへジャンプ
	void jump_page() const;

public:
	Page_OnlyOneWeb(WindowSystemManager & manager);
};
