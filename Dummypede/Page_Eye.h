// Pageのテンプレート
#pragma once
#include "WindowSystem.h"
#include "WindowSystemManager.h"

#include "Page_Light.h"

class Page_Eye : public WindowSystem {
private:
	WindowSystemManager& manager;
	double eye_outer_r;
	double eye_inner_r;
	Vec2 eye_pos;
	bool blink_flag;
	bool on_light;

	// アニメーション用
	Stopwatch anim_timer;

	void Draw() const override;
	void Update() override;

public:
	Page_Eye(WindowSystemManager& manager);

	// まばたき
	void blink();
};
