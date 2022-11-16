// Pageのテンプレート
#pragma once
#include "WindowSystem.h"
#include "WindowSystemManager.h"
#include "Centipede.h"

#include "Page_SelfIntroduction.h"
#include "Page_Eye.h"
#include "Page_MukadeShell.h"
#include "Page_Screen.h"
#include "Page_CardkeyReader.h"
#include "Page_Password.h"
#include "Page_CentipedeGame.h"

#include "Page_Dark.h"
#include "Page_Dark2.h"

class Page_Dummypede : public WindowSystem {
private:
	WindowSystemManager& manager;

	// 起動時アニメーション中・起動中
	int state = 0;
	Stopwatch anim_timer;
	Vec2 dest;

	// Darkページへのショートカット
	Vec2 darkpage_shortcut_pos;
	Vec2 darkerpage_shortcut_pos;
	Color darkpage_shorcut_col;
	Color darkerpage_shorcut_col;

	Centipede centipede;

	void Draw() const override;
	void Update() override;

public:
	Page_Dummypede(WindowSystemManager & manager);
};
