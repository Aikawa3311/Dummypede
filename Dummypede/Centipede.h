#pragma once
#include <Siv3D.hpp>
#include "CG2D.h"

// ムカデゲームのムカデ胴体部分
class CentipedeBody
{
private:
	Circle body;
	Vec2 dir;
	double noise;
	Color col;
	Color col_inner;
	bool legs_anim_flag; // 脚を動かすかどうか

public:
	CentipedeBody(Vec2 const pos = Vec2(0, 0), int const size = 10, double const noise = -1);
	void Draw() const;

	// 位置だけを動かす
	void moveBy(Vec2 const& v);

	void set_pos(Vec2 const pos_);
	void set_dir(Vec2 const dir_);
	void set_col(Color const col_);
	void set_col_inner(Color const col_);
	void set_legs_anim_flag(bool const flag);
	Circle get_circle() const;
	Vec2 get_pos() const;
	Vec2 get_dir() const;
	double get_noise() const;
};

// ムカデゲームのムカデそのもの
class Centipede {
private:
	double spd;		// 速度
	int length;		// 現在の胴体の長さ(bodies.sizeと同じ)
	int body_size;	// 胴体の円の大きさ(半径)
	int interval;	// 胴体と胴体の間隔
	int dest_ccw;	// destが後ろ方向にあるときに右回りか左回りかを示す値
	Vec2 dir_range;	// 横・前方向の投影位置(回転の速度)
	Vec2 dest;
	Color col_antenna;
	Array<CentipedeBody> bodies;

	// 移動可能フラグ、移動を制限したい場合はfalseにする
	bool flag_movable = true;

	// 移動
	void update_pos();
	// 胴全体のdirを調整
	void update_dir();

public:
	Centipede(Vec2 const pos = { 0, 0 }, Vec2 const dest = { 0, 0 }, int init_length = 1, int const body_size = 10);

	// 体の追加
	void add_body();
	void Update();
	void Draw() const;

	// 全体をずらして返す
	Centipede bodies_movedBy(Vec2 const & v) const;

	// 体の取得
	Array<CentipedeBody> const & get_bodies() const;
	double get_spd() const;
	Vec2 get_dir_range() const;
	int get_length() const;
	int get_body_size() const;
	// 体の一番前を取得
	CentipedeBody const& get_body_front() const;

	// 目的地の変更
	void set_dest(Vec2 const dest_);
	void set_spd(double const spd_);
	void set_dir_range(Vec2 const dir);
	void set_interval(int const interval_);
	void set_col_body(Color const col, int const idx);
	void set_col_body_all(Color const col);
	void set_col_body_inner_all(Color const col);
	void set_col_antenna(Color const col);
	void set_legs_anim_flag(bool const flag);

	void set_flag_movable(bool const b);
};

