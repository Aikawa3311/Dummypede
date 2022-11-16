#pragma once
#include "WindowSystem.h"
// ★ここに必要なものをinclude
#include "WindowSystemManager.h"
#include "GameControl.h"
#include "CursorDecorator.h"
#include "Centipede.h"

#include "Page_Boss_Body.h"
#include "Page_Boss_Eye.h"
#include "Page_Boss_EyeBeam.h"
#include "Page_Boss_MukadeShell.h"
#include "Page_LastPassword.h"

class WindowSystemManager;
class Page_Boss_Eye;

class Page_Boss : public WindowSystem {
private:
	WindowSystemManager& manager;

	// 最初の待機時間・ボス演出中・戦闘中・勝利時
	int state;
	// 何もなし・ライフ0時・ゲームオーバー表示
	int state_gameover;
	Stopwatch anim_timer;

	// プレイヤーのライフ
	double health_max = 100;
	double health;
	Size health_bar_size;

	// 目出現までのタイマー
	Stopwatch eye_timer;
	double eye_time = 3;		// 目出現までの時間
	Array<EyeBeam> eyebeams;

	// Mukadeshell登場までのタイマー
	Stopwatch mukade_shell_timer;

	// Centiepde出現までのタイマー
	Stopwatch centipede_timer;
	Array<Centipede> centipedes;

	void Draw() const override;
	void Update() override;

	// changestate
	void changestate_bossapeear();
	void changestate_battle();
	void changestate_win();
	void changestategameover_nohealth();
	void changestategameover_display();

	// 目出現
	void spawn_eye();

	// ゲームオーバー
	void gameover();

	// 勝利
	void win();

public:
	Page_Boss(WindowSystemManager& manager);

	// ビームやプレイヤーのライフは一番上に描画しなければならないのでこっちに書く
	void DrawDepth2() const override;

	// ビームを追加
	void add_beam(EyeBeam const & beam);
};
