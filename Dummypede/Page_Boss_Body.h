#pragma once
#include "WindowSystem.h"
// ★ここに必要なものをinclude
#include "WindowSystemManager.h"
#include "GameControl.h"
#include "CursorDecorator.h"

class WindowSystemManager;

class BossBodyFile {
private:
	Vec2 pos;
	Vec2 base;
	Vec2 coeff;
	String name;
	double spd;
	double length;
	double theta;

public:
	BossBodyFile();

	void Draw() const;
	void Update();

	void moveBy(Vec2 const & v);

	void set_pos(Vec2 const& pos_);
	void set_base(Vec2 const& base_);
	void set_coeff(Vec2 const& coeff_);
	void set_name(String const& name_);
	void set_spd(double const& spd_);
	void set_length(double const& length_);
	void set_theta(double const& theta_);

	Vec2 get_pos() const;
	Vec2 get_coeff() const;
	String get_name() const;
};

class Page_Boss_Body : public WindowSystem {
private:
	WindowSystemManager& manager;
	int const files_num_base = 50;
	int files_num;
	Array<BossBodyFile> bodies;

	// 移動用のタイマー
	Stopwatch move_next_timer;	// 次の移動までのタイマー
	double move_next_time = 1;	// 次の移動が何秒後か
	double move_time = 1.5;		// 移動にどれだけ時間をかけるか
	Vec2 prev_pos;
	Vec2 dest;
	String page_name = U"Dummypede Body";

	// 本体の座標
	Vec2 pos_body;

	// HPゲージ(実際のライフはfiles_numで)
	RectF hp_guage;

	// 登場中・登場後アニメーション・HP描画アニメーション・戦闘中
	int state;

	// アニメーション用
	Stopwatch anim_timer;
	Vec2 pos_first;
	int anim_increment;

	// 被ダメ時の無敵時間タイマー
	Stopwatch invincible_timer;

	void Draw() const override;
	void Update() override;

	// stateの変更
	void changestate_fileappearing();
	void changestate_hpappearing();
	void changestate_battle();
	void changestate_death();
	void changestate_complete();

	// 被ダメ
	void damaged();

	// destの更新
	void update_dest();

public:
	Page_Boss_Body(WindowSystemManager& manager);

	int get_state() const;
	int get_hp() const;
};
