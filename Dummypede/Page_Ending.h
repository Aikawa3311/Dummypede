// Pageのテンプレート
#pragma once
#include "WindowSystem.h"
// ★ここに必要なものをinclude
#include "Centipede.h"
#include "GameControl.h"

class Staffroll {
private:
	String asset_name;
	String staff;
	Vec2 pos;

public:
	Staffroll(String const& asset_name, String const& staff);
	void Draw() const;

	void moveBy(Vec2 const & v);
	Vec2 get_pos() const;
};

class Page_Ending : public WindowSystem {
private:
	int state;
	Stopwatch timer;

	// ムカデの演出用
	Centipede centipede;
	Array<Staffroll> staffs;
	int anim_increment;

	void Draw() const override;
	void Update() override;

	// state
	void changestate_1();
	void changestate_2();
	void changestate_3();
	void changestate_4();

	// スタッフの用意
	void make_staffroll();

public:
	void DrawDepth2() const override;

	Page_Ending();
};
