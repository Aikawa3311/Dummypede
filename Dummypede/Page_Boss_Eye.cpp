#include "stdafx.h"
#include "Page_Boss_Eye.h"

void Page_Boss_Eye::Draw() const{
	RectF(Vec2::Zero(), size).draw(Palette::Black);
	// 目の描画
	Circle(eye_pos, eye_inner_r).draw(Palette::White);
	Circle(size / 2, eye_outer_r).drawFrame(4, Palette::White);
	if (state == 0) {
		TextureAsset(U"eye_black6").draw(Vec2::Zero());
	}
	else if (state == 1) {
		double t = anim_timer.ms() / 300.0;
		String str = U"eye_black6";
		if (t <= 1.0 / 6.0) str = U"eye_black6";
		else if (t <= 2.0 / 6.0) str = U"eye_black5";
		else if (t <= 3.0 / 6.0) str = U"eye_black4";
		else if (t <= 4.0 / 6.0) str = U"eye_black3";
		else if (t <= 5.0 / 6.0) str = U"eye_black2";
		else str = U"eye_black1";
		TextureAsset(str).draw(Vec2::Zero());
	}
	else if (state == 2) {
		// TextureAsset(U"eye_black1").draw(Vec2::Zero());
		// 攻撃中なら目を赤く表示
		if (attack_state == 1) {
			double e = EaseOutCubic(attack_timer.sF() / attack_charge_time);
			e = Clamp(e + Random(-0.05, 0.05), 0.0, 1.0) * 5;
			Circle(eye_pos, eye_inner_r * (5 - e)).draw(Palette::Red);
		}
		// 目の輪郭の描画(まばたき込み)
		String asset_name = U"eye_black1";
		if (anim_timer.isRunning()) {
			double const t = anim_timer.ms() / 300.0;
			double const e = Abs(0.5 - EaseInOutSine(t));
			if (e <= 1.0 / 12.0) asset_name = U"eye_black6";
			else if (e <= 2.0 / 12.0) asset_name = U"eye_black5";
			else if (e <= 3.0 / 12.0) asset_name = U"eye_black4";
			else if (e <= 4.0 / 12.0) asset_name = U"eye_black3";
			else if (e <= 5.0 / 12.0) asset_name = U"eye_black2";
			else asset_name = U"eye_black1";
		}
		TextureAsset(asset_name).draw(Vec2::Zero());
	}
}

void Page_Boss_Eye::Update(){
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

	// 移動
	double const e = EaseOutQuart(Min(move_next_timer.sF() / move_time, 1.0));
	set_pos(prev_pos.lerp(dest, e));

	// 各state固有の処理
	switch (state) {
	case 0:
		// 目を閉じている状態
		if (anim_timer.sF() >= 0.2) {
			changestate_eye_open();
		}
		break;
	case 1:
		// 目を開け始める状態
		if (anim_timer.sF() >= 0.3) {
			changestate_normal();
		}
		break;
	case 2:
		// 目を開け切った状態
		// まばたきのタイマーを切っておく
		if (anim_timer.sF() >= 0.3) {
			anim_timer.pause();
		}

		// 移動に関する動き
		if (move_next_timer.sF() >= move_next_time) {
			move_pos();
		}

		// 攻撃に関する動き
		switch (attack_state) {
		case 0:
			// 非攻撃時
			// 攻撃用タイマーの判定
			if (attack_timer.sF() >= attack_time) {
				changeattackstate_charge();
			}
			break;
		case 1:
			// 攻撃チャージ中
			if (attack_timer.sF() >= attack_charge_time) {
				attack();
			}
			break;
		}

		// まばたきの判定
		if (Periodic::Square0_1(50ms) == 1.0) {
			if (attack_state == 1 || blink_flag || anim_timer.isRunning()) return;
			blink_flag = true;
			if (Random() < 0.01) {
				blink();
			}
		}
		else {
			blink_flag = false;
		}
		break;
	}
}

void Page_Boss_Eye::changestate_eye_open(){
	state = 1;
	anim_timer.restart();
}

void Page_Boss_Eye::changestate_normal(){
	state = 2;
	anim_timer.reset();
	// 攻撃と移動の準備
	ready_to_attack();
	move_next_timer.start();
}

void Page_Boss_Eye::changeattackstate_charge(){
	attack_state = 1;
	attack_timer.restart();
	// 攻撃中は動けないようにしておく
	move_next_timer.pause();
	AudioAsset(U"charge").playOneShot(0.6);
}

void Page_Boss_Eye::ready_to_attack(){
	attack_time = Random(3.0, 8.0);
	attack_timer.restart();
}

void Page_Boss_Eye::attack(){
	// ビームを追加
	page_boss.add_beam(EyeBeam(eye_pos + pos));
	AudioAsset(U"beam").playOneShot(0.6);
	// 次の攻撃の準備
	attack_state = 0;
	ready_to_attack();
	// 動けない状態を解除
	move_next_timer.start();
}

void Page_Boss_Eye::move_pos(){
	// 移動先を決定
	// dest = RandomVec2(RectF(Vec2::Zero(), Scene::Size().movedBy(-size)));
	dest = RandomVec2(RectF(Vec2::Zero(), GameControl::base_size.movedBy(-size)));
	prev_pos = pos;
	// 次の移動の準備
	move_next_timer.restart();
	move_next_time = Random(3.0, 15.0);
}

Page_Boss_Eye::Page_Boss_Eye(Page_Boss& boss, Vec2 const& pos_)
	:WindowSystem(pos_, Size(400, 300), U"eye of the Internet"),
	page_boss(boss),
	eye_outer_r(45),
	eye_inner_r(20),
	eye_pos(size / 2),
	blink_flag(false),
	state(0),
	attack_state(0),
	attack_time(0),
	dest(pos),
	prev_pos(pos){
	// 最初のアニメーションタイマー起動
	set_light_focus(false);
	anim_timer.start();
}

void Page_Boss_Eye::blink(){
	anim_timer.restart();
}
