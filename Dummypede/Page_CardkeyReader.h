#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"
#include "GameControl.h"
#include "WindowSystemManager.h"

#include "Page_Numbers.h"
#include "Page_Dark.h"
#include "Page_Dark2.h"
#include "Page_UnixTime.h"
#include "Page_UnixClock.h"

class Page_CardkeyReader : public WindowSystem {
private:
	WindowSystemManager& manager;
	RectF reader;
	RectF guage;
	Stopwatch anim_timer;
	Stopwatch guage_timer;
	String str;
	
	// 待機中・認証アニメ中・認証完了
	int state;

	// state変更
	void changestate_anim();
	void changestate_done();
	void changestate_idle();

	double sync_anim_function(int const i) const;

	void Draw() const override;
	void Update() override;

public:
	Page_CardkeyReader(WindowSystemManager & manager);

};

