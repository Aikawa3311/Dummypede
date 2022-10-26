#include "stdafx.h"
#include "Page_Eye.h"

void Page_Eye::Draw() const{
	RectF(Vec2::Zero(), size).draw(Palette::White);
	// Bezier3(Vec2(50, size.y / 2), Vec2(170, 50), Vec2(230, 50), Vec2(350, size.y / 2)).draw(10, Palette::Green);
	// 目の描画
	Circle(eye_pos, eye_inner_r).draw(Palette::Black);
	Circle(size / 2, eye_outer_r).drawFrame(4, Palette::Black);
	// 目の輪郭の描画
	String asset_name = U"eye1";
	if (anim_timer.isRunning()) {
		double const t = anim_timer.ms() / 300.0;
		double const e = Abs(0.5 - EaseInOutSine(t));
		if (e <= 1.0 / 12.0) asset_name = U"eye6";
		else if (e <= 2.0 / 12.0) asset_name = U"eye5";
		else if (e <= 3.0 / 12.0) asset_name = U"eye4";
		else if (e <= 4.0 / 12.0) asset_name = U"eye3";
		else if (e <= 5.0 / 12.0) asset_name = U"eye2";
		else asset_name = U"eye1";
	}
	TextureAsset(asset_name).draw(Vec2::Zero());
}

void Page_Eye::Update(){
	// タイマーを切っておく
	if (anim_timer.sF() >= 0.3) {
		anim_timer.pause();
	}

	// 目の位置の変更
	Vec2 c_pos = Cursor::PosF().movedBy(-pos);
	if (c_pos.distanceFromSq(size / 2) > Pow(eye_outer_r - eye_inner_r, 2)) {
		// 目の外側にカーソルがある場合
		Vec2 e = (size / 2 - c_pos).normalized();
		eye_pos = size / 2 - e * (eye_outer_r - eye_inner_r);
	}
	else {
		// 目の内側にカーソルがある場合
		eye_pos = c_pos;
	}

	// まばたき判定
	if (Periodic::Square0_1(50ms) == 1.0) {
		if (blink_flag || anim_timer.isRunning()) return;
		blink_flag = true;
		if (Random() < 0.01) {
			blink();
		}
	}
	else {
		blink_flag = false;
	}
}

Page_Eye::Page_Eye()
	:WindowSystem(Vec2(700, 70), Size(400, 300), U"eye"),
	eye_outer_r(45),
	eye_inner_r(20),
	eye_pos(size/2),
	blink_flag(false){
}

void Page_Eye::blink(){
	anim_timer.restart();
}
