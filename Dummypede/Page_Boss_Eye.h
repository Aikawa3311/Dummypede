// Pageのテンプレート
#pragma once
#include "WindowSystem.h"

#include "Page_Boss.h"
#include "Page_Boss_EyeBeam.h"

class Page_Boss;


class Page_Boss_Eye : public WindowSystem {
private:
	Page_Boss& page_boss;

	double eye_outer_r;
	double eye_inner_r;
	Vec2 eye_pos;
	bool blink_flag;

	// 目を閉じている状態・目を開け始める状態・目を開け切った状態
	int state;
	// 非攻撃時・攻撃チャージ中・攻撃時
	int attack_state;

	// アニメーション用
	Stopwatch anim_timer;

	// 攻撃用
	double attack_charge_time = 1;	// 攻撃準備から攻撃にかかるまでの時間
	double attack_time;				// 次の攻撃までの時間
	Stopwatch attack_timer;

	// 動き用
	Vec2 dest;
	Vec2 prev_pos;
	double move_time = 1;			// 移動にかかる時間
	double move_next_time = 0.3;	// 次の移動が何秒後か
	Stopwatch move_next_timer;		// 次の移動までの時間

	void Draw() const override;
	void Update() override;

	// 状態変更用
	void changestate_eye_open();
	void changestate_normal();
	void changeattackstate_charge();

	// 攻撃準備
	void ready_to_attack();

	// 攻撃
	void attack();

	// 移動
	void move_pos();

public:
	Page_Boss_Eye(Page_Boss& boss, Vec2 const& pos_ = {0, 0});

	// まばたき
	void blink();
};
