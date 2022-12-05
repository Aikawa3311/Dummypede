#include "stdafx.h"
#include "page_Boss_Body.h"

// --------------------------------------------
// BossBodyFile
// --------------------------------------------

BossBodyFile::BossBodyFile()
	:pos(Vec2::Zero()),
	base(Vec2::Zero()),
	coeff(Vec2::Zero()),
	name(U""),
	spd(0.001),
	length(100),
	theta(0){
}

void BossBodyFile::Draw() const{
	TextureAsset(name).drawAt(pos.movedBy(base));
}

void BossBodyFile::Update(){
	Vec2 tmp_pos = Vec2(Cos(Time::GetMillisec() * spd) * coeff.x, Sin(Time::GetMillisec() * spd) * coeff.y) * length;
	pos.x = tmp_pos.x * Cos(theta) + tmp_pos.y * (-Sin(theta));
	pos.y = tmp_pos.x * Sin(theta) + tmp_pos.y * Cos(theta);
}

void BossBodyFile::moveBy(Vec2 const& v){
	pos.moveBy(v);
}

void BossBodyFile::set_pos(Vec2 const& pos_){
	pos = pos_;
}

void BossBodyFile::set_base(Vec2 const& base_){
	base = base_;
}

void BossBodyFile::set_coeff(Vec2 const& coeff_) {
	coeff = coeff_;
}

void BossBodyFile::set_name(String const& name_) {
	name = name_;
}

void BossBodyFile::set_spd(double const& spd_){
	spd = spd_;
}

void BossBodyFile::set_length(double const& length_){
	length = length_;
}

void BossBodyFile::set_theta(double const& theta_){
	theta = theta_;
}

Vec2 BossBodyFile::get_pos() const{
	return pos;
}

Vec2 BossBodyFile::get_coeff() const {
	return coeff;
}

String BossBodyFile::get_name() const {
	return name;
}

// --------------------------------------------
// Page_Boss_Body
// --------------------------------------------

void Page_Boss_Body::Draw() const{
	switch (state) {
	case 4:
		// 撃破中
		if (Periodic::Square0_1(0.2s)) TextureAsset(U"boss").drawAt(pos_body, ColorF(1, 1, 1, Max(1 - (anim_timer.sF() / 3.0), 0.0)));
		hp_guage.drawFrame(4, ColorF(1, 1, 1, Max(1 - (anim_timer.sF() / 3.0), 0.0)));
		break;
	default:
		if (invincible_timer.isRunning()) {
			// ダメージ食らい中
			if(Periodic::Square0_1(0.2s)) TextureAsset(U"boss").drawAt(pos_body);
		}
		else {
			TextureAsset(U"boss").drawAt(pos_body);
		}

		// HPゲージ
		if (state >= 2) {
			hp_guage.drawFrame(4, Palette::White);
			if (state == 2) {
				RectF(hp_guage.x + 5, hp_guage.y + 5, (hp_guage.w - 10) * ((double)anim_increment / files_num_base), hp_guage.h - 10).draw(Palette::White);
			}
			else if (state == 3) {
				RectF(hp_guage.x + 5, hp_guage.y + 5, (hp_guage.w - 10) * ((double)files_num / files_num_base), hp_guage.h - 10).draw(Palette::White);
			}
		}
		break;
	}

	for (auto const& i : bodies) {
		i.Draw();
	}

}

void Page_Boss_Body::Update(){
	switch (state){
	case 0:
		// 本体アイコン登場中
		pos_body = pos_first.lerp(size/2, Min(anim_timer.sF() / 5, 1.0));
		if (anim_timer.sF() >= 8) {
			changestate_fileappearing();
		}
		break;
	case 1:
		// 周りのファイル登場アニメーション
		if (bodies.size() < files_num_base && anim_timer.sF() >= anim_increment * (3.0 / files_num_base)) {
			++anim_increment;
			++files_num;
			bodies.emplace_back(BossBodyFile());
			bodies.back().set_base(size / 2);
			bodies.back().set_coeff(RandomVec2());
			bodies.back().set_length(Random(50.0, 150.0));
			bodies.back().set_name(U"file_feed" + Format(Random(0, 4)));
			bodies.back().set_spd(Random(0.0005, 0.002));
			bodies.back().set_theta(Random(0.0, Math::Pi));
			AudioAsset(U"daon").playOneShot(0.5);
		}
		if (anim_timer.sF() > 4) {
			changestate_hpappearing();
		}
		break;
	case 2:
		// hpが出現するアニメーション
		if (anim_increment < files_num && anim_timer.sF() >= anim_increment * (4.0 / files_num)) {
			++anim_increment;
			AudioAsset(U"daon").playOneShot(0.5);
		}
		if (anim_timer.sF() > 5) {
			changestate_battle();
		}
		break;
	case 3:
		// 戦闘中
		// anim_timerで名前が少しずつ浮かび上がる
		if (title != page_name) {
			int length = (int)(anim_timer.sF() * 2);
			title = page_name.substr(0, length);
			if (title == page_name) anim_timer.pause();
		}
		break;
	case 4:
		// 撃破中
		if (anim_timer.sF() >= 5) {
			changestate_complete();
		}
		break;
	}

	// 剣の判定とダメージ判定など
	if (std::shared_ptr<CursorSword> sword = GameControl::decorator.get_sword().lock()) {
		Line line = sword->get_hitbox();
		// 一定以上動いている場合に限る
		if (!invincible_timer.isRunning() && Cursor::PosF().distanceFromSq(Cursor::PreviousPosF()) >= 50 && line.intersects(Circle((size / 2).movedBy(pos), 50)) && files_num > 0) {
			damaged();
		}
	}
	if (invincible_timer.isRunning() && invincible_timer.sF() >= 1) {
		invincible_timer.pause();
	}

	// 移動
	double const e = EaseInOutQuad(Min(move_next_timer.sF() / move_time, 1.0));
	set_pos(prev_pos.lerp(dest, e));

	// タイマーの更新
	if (move_next_timer.sF() > move_next_time) {
		update_dest();
	}

	for (auto& i : bodies) {
		i.Update();
	}
}

void Page_Boss_Body::changestate_fileappearing(){
	state = 1;
	anim_timer.restart();
}

void Page_Boss_Body::changestate_hpappearing(){
	state = 2;
	anim_timer.restart();
	anim_increment = 0;
}

void Page_Boss_Body::changestate_battle(){
	state = 3;
	move_next_timer.start();
	// 最後に名前が少しずつ出現する演出でanim_timerを使用
	anim_timer.restart();
}

void Page_Boss_Body::changestate_death(){
	state = 4;
	move_next_timer.pause();
	invincible_timer.reset();
	anim_timer.restart();
}

void Page_Boss_Body::changestate_complete(){
	state = 5;
}

void Page_Boss_Body::damaged(){
	invincible_timer.restart();
	files_num = Max(files_num - 2, 0);
	bodies.pop_back_N(2);
	if (files_num <= 0) {
		changestate_death();
	}
	AudioAsset(U"sword").playOneShot(0.7);
}

void Page_Boss_Body::update_dest(){
	// dest = RandomVec2(RectF(Vec2::Zero(), Scene::Size().movedBy(-size)));
	dest = RandomVec2(RectF(Vec2::Zero(), GameControl::base_size.movedBy(-size)));
	prev_pos = pos;
	move_next_time = Random(10.0, 15.0);
	move_next_timer.restart();
}

Page_Boss_Body::Page_Boss_Body(WindowSystemManager& manager)
	: // WindowSystem((Scene::Size() / 2).movedBy(-250, -350), Size(500, 400), U""),
	WindowSystem((GameControl::base_size / 2).movedBy(-250, -350), Size(500, 400), U""),
	manager(manager),
	files_num(0),
	bodies(0),
	prev_pos(pos),
	dest(pos),
	pos_body((size/2).movedBy(0, -400)),
	hp_guage((size/2).movedBy(-200, 150), 400, 35),
	state(0),
	pos_first(pos_body),
	anim_increment(0)
{
	// 消せない・動かせない・フォーカス不可
	set_erasable(false);
	set_draggable(false);
	set_focusable(false);
	set_light_focus(false);

	anim_timer.start();
	/*for (int i = 0; i < files_num; ++i) {
		bodies[i].set_base(size / 2);
		bodies[i].set_coeff(RandomVec2());
		bodies[i].set_length(Random(50.0, 150.0));
		bodies[i].set_name(U"file_feed" + Format(Random(0, 4)));
		bodies[i].set_spd(Random(0.0005, 0.002));
		bodies[i].set_theta(Random(0.0, Math::Pi));
	}
	move_next_timer.start();
	*/
}

int Page_Boss_Body::get_state() const{
	return state;
}

int Page_Boss_Body::get_hp() const{
	return files_num;
}
