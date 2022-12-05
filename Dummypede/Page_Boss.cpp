#include "stdafx.h"
#include "Page_Boss.h"

void Page_Boss::Draw() const{
	RectF(Vec2::Zero(), size).draw(Palette::Black);
}

void Page_Boss::Update(){
	if (state_gameover == 0 && health <= 0) {
		// ゲームオーバー開始
		changestategameover_nohealth();
	}

	// ゲームオーバー時の処理など
	if (state_gameover == 1) {
		if (anim_timer.sF() >= 2) {
			changestategameover_display();
		}
	}
	else if (state_gameover >= 2) {
		if (anim_timer.sF() >= 4) {
			gameover();
		}
	}

	// state1のときに実行:
	if (state == 0) {
		if (anim_timer.sF() >= 5) {
			changestate_bossapeear();
		}
	}

	// bossの状態確認
	if (std::shared_ptr<Page_Boss_Body> page = manager.get_page_boss_body().lock()) {
		int boss_state = page->get_state();
		// ボスの演出が終わったらstateを2に変える
		if (boss_state == 3 && state == 1) {
			changestate_battle();
		}
		// 勝利時の処理
		if (boss_state == 4 && state == 2) {
			changestate_win();
		}
		if (boss_state == 5) {
			win();
		}
	}

	// mukade_shell登場
	if (mukade_shell_timer.sF() >= 20) {
		mukade_shell_timer.reset();
		manager.add_page(std::make_shared<Page_Boss_MukadeShell>(manager));
	}

	// EyeBeamの移動と判定
	for (auto it = eyebeams.begin(); it != eyebeams.end();) {
		it->Update();
		Line const& line = it->get_hitbox();
		// 当たり判定 & 削除判定
		if (line.intersects(Circle(Cursor::PosF(), 5))) {
			// 当たった時は削除 & ダメージ
			health = Max(health - 10, 0.0);
			it = eyebeams.erase(it);
			AudioAsset(U"daon").playOneShot(0.7);
		}
		// else if (!line.begin.intersects(Scene::Rect()) && !line.end.intersects(Scene::Rect())) {
		else if (!line.begin.intersects(Rect(Point::Zero(), GameControl::base_size)) && !line.end.intersects(Rect(Point::Zero(), GameControl::base_size))) {
			// 外に出たときも削除
			it = eyebeams.erase(it);
		}
		else {
			++it;
		}
	}

	// 目の出現
	if (eye_timer.sF() >= eye_time) {
		spawn_eye();
	}
}

void Page_Boss::changestate_bossapeear(){
	state = 1;
	anim_timer.reset();
	std::shared_ptr<Page_Boss_Body> page = std::make_shared<Page_Boss_Body>(manager);
	manager.add_page(page, false);
	manager.set_page_boss_body(page);
}

void Page_Boss::changestate_battle(){
	state = 2;
	eye_timer.restart();
	centipede_timer.restart();
	// mukadeshell登場までの秒読み開始
	mukade_shell_timer.start();
}

void Page_Boss::changestate_win(){
	state = 3;
	eye_timer.pause();
	// 邪魔なものは消しておく
	bool flag = false;
	GameControl::decorator.unset();
	auto const& pages = manager.get_pages();
	for (int i = 0; i < (int)pages.size(); ++i) {
		if (flag) {
			manager.erase_window(i);
			// Print << pages[i]->get_title() << U" " << pages[i]->get_flag_erase();
		}
		if (!flag && pages[i]->get_title() == U"Dummypede Body") {
			flag = true;
		}
	}
}

void Page_Boss::changestategameover_nohealth(){
	state_gameover = 1;
	// gameover, 全てのタイマーを止める
	eye_timer.pause();
	mukade_shell_timer.pause();
	anim_timer.restart();
}

void Page_Boss::changestategameover_display(){
	state_gameover = 2;
	anim_timer.restart();
}

void Page_Boss::spawn_eye(){
	int num = 3;
	// ライフが少ない時はより多く出現させる
	if (std::shared_ptr<Page_Boss_Body> page = manager.get_page_boss_body().lock()) {
		if (page->get_hp() <= 10) {
			num = 5;
		}
		else if (page->get_hp() <= 25) {
			num = 4;
		}
	}

	// 目玉の数は100を超えない
	int page_size = (int)manager.get_pages().size();
	if (num + page_size > 100) {
		num = 100 - page_size;
	}

	if (num >= 0) {
		// Vec2 eye_pos = RandomVec2(RectF(Vec2::Zero(), Scene::Size().movedBy(-400, -300)));
		Vec2 eye_pos = RandomVec2(RectF(Vec2::Zero(), GameControl::base_size.movedBy(-400, -300)));
		for (int i = 0; i < num; ++i) {
			manager.add_page(std::make_shared<Page_Boss_Eye>(*this, eye_pos), false);
		}
		AudioAsset(U"eyeappear").playOneShot(0.6);
	}

	eye_timer.restart();
	eye_time = Random(9.0, 12.0);
}

void Page_Boss::gameover(){
	bool flag = false;
	GameControl::decorator.unset();
	// 自分含む自分以降のウィンドウをすべて消去する
	auto const& pages = manager.get_pages();
	for (int i = 0; i < (int)pages.size(); ++i) {
		if (!flag && pages[i]->get_title() == U"Internet Abyss") {
			flag = true;
		}
		if (flag) {
			manager.erase_window(i);
			// Print << pages[i]->get_title() << U" " << pages[i]->get_flag_erase();
		}
	}
}

void Page_Boss::win(){
	GameControl::boss_win = true;
	// ウィンドウを消す
	gameover();
	// 最後のアクセス権限開放パスワードページを出現させる
	manager.add_page(std::make_shared<Page_LastPassword>(), false);
}

Page_Boss::Page_Boss(WindowSystemManager& manager)
	: // WindowSystem(Vec2(-50, -50), Size(Scene::Size()).movedBy(100, 100), U"Internet Abyss"),
	WindowSystem(Vec2(-50, -50), GameControl::base_size.movedBy(100, 100), U"Internet Abyss"),
	manager(manager),
	state(0),
	state_gameover(0),
	health(health_max),
	health_bar_size(60, 10)
{
	anim_timer.start();
	set_draggable(false);
	set_erasable(false);
	set_focusable(false);
	set_light_focus(false);
	// 既に剣を持っている場合は外させる
	GameControl::decorator.unset();
}

void Page_Boss::DrawDepth2() const{
	// ビームの描画
	for (int i = 0; i < (int)eyebeams.size(); ++i) {
		eyebeams[i].Draw();
	}
	if (state == 2) {
		Vec2 draw_pos = Cursor::PosF().movedBy(-health_bar_size.x / 2 + 4, 26);
		RectF(draw_pos, health_bar_size.x * ((double)health / health_max), health_bar_size.y).draw(Palette::Green);
		RectF(draw_pos, health_bar_size).drawFrame(2, Palette::White);
	}

	// ゲームオーバーの描画
	if (state_gameover >= 2) {
		// FontAsset(U"ExtraHugeDot")(U"GAME OVER").drawAt(Scene::Size() / 2, Palette::White);
		FontAsset(U"ExtraHugeDot")(U"GAME OVER").drawAt(GameControl::base_size / 2, Palette::White);
	}
}

void Page_Boss::add_beam(EyeBeam const& beam){
	eyebeams.emplace_back(beam);
}
