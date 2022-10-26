// Pageのテンプレート
#pragma once
#include "WindowSystem.h"


class Page_Eye : public WindowSystem {
private:
	double eye_outer_r;
	double eye_inner_r;
	Vec2 eye_pos;
	bool blink_flag;

	// アニメーション用
	Stopwatch anim_timer;

	void Draw() const override;
	void Update() override;

public:
	Page_Eye();

	// まばたき
	void blink();
};
