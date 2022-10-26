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

class Page_Dummypede : public WindowSystem {
private:
	WindowSystemManager& manager;

	// 起動時アニメーション中・起動中
	int state = 0;
	Stopwatch anim_timer;
	Vec2 dest;

	Centipede centipede;

	void Draw() const override;
	void Update() override;

public:
	Page_Dummypede(WindowSystemManager & manager);
};
