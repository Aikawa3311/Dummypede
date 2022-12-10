#include "stdafx.h"
#include "Page_Ending.h"

// --------------------------------------------
// Staffroll
// --------------------------------------------

Staffroll::Staffroll(String const& asset_name, String const& staff)
	:asset_name(asset_name),
	staff(staff)
{
	// pos = Scene::CenterF().movedBy(900, 0);
	pos = (GameControl::base_size / 2.0).movedBy(GameControl::base_size.x / 2 + 300, 0);
}

void Staffroll::Draw() const{
	TextureAsset(asset_name).drawAt(pos.movedBy(0, -10), Palette::Black);
	FontAsset(U"RegularDot")(staff).draw(Arg::topCenter = pos.movedBy(0, 20), Palette::Black);
}

void Staffroll::moveBy(Vec2 const& v){
	pos += v;
}

Vec2 Staffroll::get_pos() const{
	return pos;
}

// --------------------------------------------
// Page_Ending
// --------------------------------------------

void Page_Ending::Draw() const{
}

void Page_Ending::Update(){
	switch (state) {
	case 0:
		// グラデ終わるまで待機
		if (timer.sF() >= 6.0) {
			// ここでシェーダーを切る
			// GameControl::flag_shader = false;
		}
		if (timer.sF() >= 7.0) {
			changestate_1();
		}
		break;
	case 1:
		// centipede発進中
		centipede.Update();
		// if (centipede.get_body_front().get_pos().distanceFromSq(Scene::CenterF().moveBy(-200, 0)) <= 1) {
		// if (Scene::CenterF().x - 200 - centipede.get_body_front().get_pos().x <= 0) {
		if (GameControl::base_size.x / 2.0 - 200 - centipede.get_body_front().get_pos().x <= 0) {
			changestate_2();
		}
		break;
	case 2:
		// 右からスタッフロール
		staffs[anim_increment].moveBy(Vec2(-Scene::DeltaTime() * 130, 0.0));
		// if (staffs[anim_increment].get_pos().distanceFromSq(Scene::CenterF().moveBy(-180, 0)) <= 1) {
		// if (staffs[anim_increment].get_pos().x - (Scene::CenterF().x - 180) <= 0) {
		if (staffs[anim_increment].get_pos().x - (GameControl::base_size.x / 2.0 - 180) <= 0) {
			if (anim_increment + 1 == (int)staffs.size()) {
				AudioAsset(U"daon").playOneShot(0.7);
				changestate_3();
			}
			else {
				AudioAsset(U"daon").playOneShot(0.7);
				++anim_increment;
				// centipede.add_body();
			}
		}
		break;
	case 3:
		// ムカデフェードアウト
		centipede.Update();
		// if (centipede.get_bodies().back().get_pos().x - (Scene::Width() + 150) > 0) {
		if (centipede.get_bodies().back().get_pos().x - (GameControl::base_size.x + 150) > 0) {
			changestate_4();
		}
		break;
	case 4:
		// Dummypede End
		break;
	}
}

void Page_Ending::changestate_1(){
	state = 1;
	timer.restart();
	// centipede.set_dest(Vec2(Scene::CenterF()));
	centipede.set_dest(Vec2(GameControl::base_size / 2.0));
}

void Page_Ending::changestate_2(){
	state = 2;
	centipede.set_flag_movable(false);
	anim_increment = 0;
}

void Page_Ending::changestate_3(){
	state = 3;
	centipede.set_flag_movable(true);
}

void Page_Ending::changestate_4(){
	state = 4;
	timer.restart();
}

void Page_Ending::make_staffroll(){
	 staffs.emplace_back(U"staffroll_pen", U"企画\nAikawa");
	 staffs.emplace_back(U"staffroll_program", U"プログラム\nAikawa");
	 staffs.emplace_back(U"staffroll_image", U"アイコン・画像素材\nFont Awesome\nNew Factory");
	 staffs.emplace_back(U"staffroll_audio", U"効果音素材\n効果音ラボ");
	 staffs.emplace_back(U"staffroll_font", U"フォント素材\nDSEG (created by けしかん)");
	 staffs.emplace_back(U"staffroll_testplayer", U"テストプレイ\nDaylight\niyoK\nJim\nTano\nTozan");
}

void Page_Ending::DrawDepth2() const{
	// 背景
	switch (state) {
	case 0:
		// 最初はグラデ描画
		// Scene::Rect().draw(ColorF(1, 1, 1, Min(timer.sF() / 4.0, 1.0)));
		Rect(Point::Zero(), GameControl::base_size).draw(ColorF(1, 1, 1, Min(timer.sF() / 4.0, 1.0)));
		break;
	default:
		// Scene::Rect().draw(Palette::White);
		Rect(Point::Zero(), GameControl::base_size).draw(Palette::White);
		break;
	}
	// スタッフ
	/*for (auto const& i : staffs) {
		i.Draw();
	}*/
	if (state == 2) {
		staffs[anim_increment].Draw();
	}else if(state == 4){
		// FontAsset(U"ExtraHugeDot")(U"D U M M Y P E D E").drawAt(Scene::CenterF(), Palette::Black);
		FontAsset(U"ExtraHugeDot")(U"D U M M Y P E D E").drawAt(GameControl::base_size / 2.0, Palette::Black);
		if (timer.sF() >= 1.5) {
			// FontAsset(U"HugeDot")(U"END").drawAt(Scene::CenterF().movedBy(300, 200), Palette::Black);
			FontAsset(U"HugeDot")(U"END").drawAt((GameControl::base_size / 2.0).movedBy(300, 200), Palette::Black);
		}
	}
	centipede.Draw();
}

Page_Ending::Page_Ending()
	: // WindowSystem(Vec2(-50, -50), Size(Scene::Size()).movedBy(100, 100), U"Ending"),
	WindowSystem(Vec2(-50, -50), Size(GameControl::base_size).movedBy(100, 100), U"Ending"),
	state(0),
	// centipede(Vec2(-60, Scene::Height()/2), Scene::CenterF(), 5, 15),
	centipede(Vec2(-60, GameControl::base_size.y / 2), GameControl::base_size / 2.0, 5, 15),
	anim_increment(0)
{
	centipede.set_interval(35);
	centipede.set_col_body_all(Palette::Black);
	centipede.set_col_antenna(Palette::Black);
	centipede.set_col_body_inner_all(Palette::White);
	timer.start();
	make_staffroll();
	AudioAsset(U"pc").stop();
	AudioAsset(U"pc_end").playOneShot(0.6);
}

