// Pageのテンプレート
#pragma once
#include "WindowSystem.h"
#include "WindowSystemManager.h"

#include "Page_CentipedeGame.h"
#include "Page_AYFABTU.h"

#include "GameControl.h"

class WindowSystemManager;

// 一番最初に作られるページ, 自動で消える

class Page_Opening : public WindowSystem {
private:
	WindowSystemManager& manager;

	int state = 0;
	Stopwatch timer;

	void Draw() const override;
	void Update() override;

public:
	void DrawDepth2() const;
	Page_Opening(WindowSystemManager& manager);
};
