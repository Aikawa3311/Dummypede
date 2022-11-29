#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"
#include "Centipede.h"

#include "GameControl.h"

class Page_CentipedeGame : public WindowSystem {
private:
	int score;
	Vec2 item_pos;
	String item_name;
	Array<Vec2> bio;
	Centipede centipede;

	// アニメーション用の変数
	int anim_increment;		// カウントアップ用
	int animstate_gameover; // ゲームオーバーアニメの進行段階

	// tipsのカウント
	int tips_count = 0;

	// ハイスコア更新フラグ
	bool flag_highscore = false;

	// タイマー類
	Stopwatch timer;		// ゲームの制限時間用タイマー
	Stopwatch anim_timer;	// アニメーション用タイマー
	int time_limit;			// ゲームの制限時間

	// タイトルアニメーション中・タイトル画面・メインゲームアニメーション中・メインゲーム画面・ゲームオーバーアニメーション中・ゲームオーバー画面
	int state = 1;

	void Draw() const override;
	void Update() override;

	// ゲームオーバー起動
	void changestate_gameover_anim();
	// ゲーム画面起動
	void changestate_game();
	// ゲームオーバー中起動
	void changestate_gameover();
	// ゲームオーバー時のアニメーション
	void gameover_anim();

	void spawn_item();
	// ゲームオーバーアイテムとの接触を確認
	bool bio_intersect();
	// ムカデの先頭が自身の胴体と接触したかチェック
	bool centipede_selfintersect() const;

	// TIPSのdraw
	void draw_tips(Vec2 const & draw_pos, String const & text) const;

public:
	Page_CentipedeGame();

	// ムカデのconst参照を返す
	Centipede const& get_centipede() const;

	// スコアのインクリメント & スコア増加時の処理
	void score_increment();

	// stateを返す
	int get_state() const;
};

