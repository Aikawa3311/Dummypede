#include "stdafx.h"
#include "Page_CentipedeGame.h"

Page_CentipedeGame::Page_CentipedeGame()
	: WindowSystem(Vec2(2, 2), Scene::Size() - Point(4, 4), U"centipede"),
	score(0),
	item_pos(Vec2::Zero()),
	item_name(U""),
	bio(0),
	centipede(pos + size / 2, Vec2(0, 0), 5),
	time_limit(60)
{
	spawn_item();
}

Centipede const& Page_CentipedeGame::get_centipede() const{
	return centipede;
}

void Page_CentipedeGame::score_increment(){
	// スコアの追加
	++score;
	// 音
	AudioAsset(U"catsu").playOneShot(0.7);
	// spawn_item();
	// ムカデの状態変更
	centipede.add_body();
	centipede.set_spd(centipede.get_spd() + 6);
	centipede.set_dir_range(centipede.get_dir_range().movedBy(0.1, 0));
}

int Page_CentipedeGame::get_state() const{
	return state;
}

void Page_CentipedeGame::Draw() const{
	// 背景
	RectF(Vec2::Zero(), size).draw(Palette::Black);
	// タイトル画面
	if (state == 1) {
		FontAsset(U"HugeBit")(U"Centipede").drawAt(Vec2(size.x / 2, size.y / 3), Palette::White);
		FontAsset(U"BigBit")(U"-LEFT CLICK TO START-").drawAt(Vec2(size.x / 2, size.y * 2 / 3), Palette::White);
	}
	// ゲーム画面及びゲームオーバー画面
	if (state >= 2) {
		ColorF blend(0.5, 0.5, 0.5);
		const ScopedColorMul2D colorMul{ state == 5 ? blend : ColorF(1, 1, 1) };
		// アイテム
		if (item_name != U"") {
			TextureAsset(item_name).draw(item_pos, Palette::White);
		}
		for (auto const & i : bio) {
			TextureAsset(U"bio").drawAt(i, Palette::White);
		}
		// ムカデ
		centipede.Draw();
		// 左上の方に制限時間とスコアの表示

	}
	// ゲームオーバー中はゲームオーバーの文言を表示
	if (state == 5) {
		FontAsset(U"HugeBit")(U"GAME OVER").drawAt(Vec2(size.x / 2, size.y / 3), Palette::White);
		FontAsset(U"BigBit")(U"Score:{}"_fmt(score)).drawAt(Vec2(size.x / 2, size.y * 2 / 3), Palette::White);
		if (flag_highscore) {
			FontAsset(U"BigBit")(U"- NEW RECORD -").drawAt(Vec2(size.x / 2, size.y * 2 / 3 - 50), Palette::Orangered);
		}
	}
}

void Page_CentipedeGame::Update(){
	if (state == 1) {
		// タイトル画面
		if (active && rect_without_head_frame().leftClicked()) {
			// 左クリックされたらゲーム画面へ
			changestate_game();
		}
	}
	else if (state == 3) {
		// ゲーム画面時
		// タイトルにスコアとタイムを表示
		title = U"centipede {} {}"_fmt(score, time_limit - timer.s());
		
		// ムカデの挙動など
		centipede.set_dest(Cursor::PosF() - pos);
		centipede.Update();
		// ゲームオーバーフラグ設定
		if (score >= 3 && centipede_selfintersect()) {
			changestate_gameover_anim();
		}
		// 制限時間オーバーで強制ゲームオーバー
		if (time_limit - timer.s() <= 0) {
			changestate_gameover_anim();
		}

		// ムカデとファイルの接触を感知
		if (centipede.get_bodies().front().get_circle().intersects(RectF(item_pos.movedBy(5, 5), Size(20, 30)))) {
			// スコアの追加
			score_increment();
			spawn_item();
			//// ゲームオーバーアイテムの追加
			//if (score % 3 == 0) {
			//	// もし既に接触していたらアウト
			//	Vec2 tmp;
			//	unsigned index;
			//	double min_dist = std::numeric_limits<double>::max();
			//	auto const & bodies = centipede.get_bodies();
			//	do {
			//		tmp = RandomVec2(RectF(Vec2::Zero(), size).stretched(-20));
			//		for (index=0; index < bodies.size(); ++index) {
			//			double d = bodies.at(index).get_pos().distanceFromSq(tmp);
			//			if (d >= min_dist) continue;
			//			min_dist = d;
			//		}
			//	} while (min_dist < 20*20);
			//	bio.emplace_back(tmp);
			//}
		}
	}
	else if (state == 4) {
		// ゲームオーバーアニメーション
		gameover_anim();
	}
	else if (state == 5) {
		// ゲームオーバー中
		// 左クリックでタイトルへ
		if (active && rect_without_head_frame().leftClicked()) {
			state = 1;
			title = U"centipede";
		}
	}
}

void Page_CentipedeGame::changestate_gameover_anim(){
	// フラグ変更/変数設定
	state = 4;
	animstate_gameover = 0;
	anim_increment = 0;
	centipede.set_legs_anim_flag(false);
	// ハイスコア更新設定
	if (score > GameControl::centipede_highscore) {
		GameControl::centipede_highscore = score;
		flag_highscore = true;
	}
	// アニメーション用タイマー起動
	anim_timer.restart();
}

void Page_CentipedeGame::changestate_game(){
	// フラグ変更/変数設定
	state = 3;
	centipede = Centipede(size / 2, Vec2(0, 0), 5);
	score = 0;
	flag_highscore = false;
	// アイテム出現
	spawn_item();
	// ゲームの制限時間タイマー起動
	timer.restart();
}

void Page_CentipedeGame::gameover_anim(){
	switch (animstate_gameover) {
	case 0:
		// 1秒待つフェイズ
		if (anim_timer.s() < 1) return;
		anim_timer.restart();
		++animstate_gameover;
		break;
	case 1:
		// 胴体の色を順番に赤にするフェイズ
		if (anim_timer.ms() > (anim_increment + 1) * 100) {
			centipede.set_col_body(Palette::Red, centipede.get_length() - anim_increment - 1);
			++anim_increment;
			AudioAsset(U"daon").setVolume(0.6);
			AudioAsset(U"daon").playOneShot();
			if (anim_increment == centipede.get_length()) {
				++animstate_gameover;
				anim_timer.restart();
			}
		}
		break;
	case 2:
		// 触角の色を変えて1秒待つフェイズ
		centipede.set_col_antenna(Palette::Red);
		if (anim_timer.s() < 1) return;
		// ゲームオーバー画面の表示
		anim_timer.reset();
		++animstate_gameover;
		state = 5;
		break;
	}
}

void Page_CentipedeGame::spawn_item(){
	// item_code = item_code_base.choice();
	item_name = U"file_feed" + Format(Random(4));
	do {
		item_pos = RandomVec2(RectF(Vec2::Zero(), size).stretched(-200));
	} while (centipede.get_bodies().front().get_circle().scaled(2).intersects(item_pos));
}

bool Page_CentipedeGame::bio_intersect(){
	

	return false;
}

bool Page_CentipedeGame::centipede_selfintersect() const {
	if (centipede.get_length() <= 2) return false;
	// 先頭と二番目の胴体が重なり合っているときは判定しない
	auto const& bodies = centipede.get_bodies();
	double threshold = Pow(centipede.get_body_size() * 2, 2);
	// if (bodies.front().get_pos().distanceFromSq(bodies.at(1).get_pos()) < threshold) return false;

	for (int i = 2; i < centipede.get_length(); ++i) {
		if (bodies.front().get_pos().distanceFromSq(bodies.at(i).get_pos()) < threshold) {
			return true;
		}
	}
	return false;
}

