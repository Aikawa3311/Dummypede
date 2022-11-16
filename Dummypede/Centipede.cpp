#include "stdafx.h"
#include "Centipede.h"

// --------------------------------------------
// CentipedeBody
// --------------------------------------------

CentipedeBody::CentipedeBody(Vec2 const pos, int const size, double const noise_)
	: body(pos, size),
	dir(0, 0), noise(noise_),
	col(Palette::White),
	col_inner(Palette::Black),
	legs_anim_flag(true)
{
	if(noise == -1) noise = Random() * Math::TwoPi;
}

void CentipedeBody::Draw() const {
	body.draw(col_inner).drawFrame(2, col);
	Vec2 n = CG2D::normal(dir);
	if (legs_anim_flag) {
		Line(body.center + n * body.r * 1.4, body.center + n * body.r * 4 + Sin(Time::GetMillisec() * 0.009 + noise) * body.r * 0.8 * dir).draw(2, col);
		Line(body.center - n * body.r * 1.4, body.center - n * body.r * 4 + Cos(Time::GetMillisec() * 0.009 + noise) * body.r * 0.8 * dir).draw(2, col);
	}
	else {
		Line(body.center + n * body.r * 1.4, body.center + n * body.r * 4).draw(2, col);
		Line(body.center - n * body.r * 1.4, body.center - n * body.r * 4).draw(2, col);
	}
	// body.draw(Palette::White);
}

void CentipedeBody::moveBy(Vec2 const& v){
	body.moveBy(v);
}

void CentipedeBody::set_pos(Vec2 const pos_) {
	body.setPos(pos_);
}
void CentipedeBody::set_dir(Vec2 const dir_) {
	dir = dir_;
}
void CentipedeBody::set_col(Color const col_) {
	col = col_;
}
void CentipedeBody::set_col_inner(Color const col_) {
	col_inner = col_;
}
void CentipedeBody::set_legs_anim_flag(bool const flag){
	legs_anim_flag = flag;
}
Circle CentipedeBody::get_circle() const {
	return body;
}
Vec2 CentipedeBody::get_pos() const {
	return body.center;
}
Vec2 CentipedeBody::get_dir() const {
	return dir;
}

double CentipedeBody::get_noise() const{
	return noise;
}

// --------------------------------------------
// Centipede
// --------------------------------------------

Centipede::Centipede(Vec2 const pos, Vec2 const dest, int init_length, int const body_size)
	: spd(120),
	length(1),
	body_size(body_size),
	interval(body_size * 2 + 5),
	dest_ccw(0),
	dir_range(2, 100), // (2, 100)
	dest(dest),
	col_antenna(Palette::White),
	bodies(1, { pos, body_size })
{
	// init_lengthの分だけ胴体追加
	for (int i = 1; i < init_length; ++i) {
		add_body();
	}
	// 初期角度の設定
	if (bodies.front().get_pos().distanceFromSq(dest) < 1e-6) {
		// 目的地と近すぎる場合はデフォルト値にする
		bodies.front().set_dir(Vec2::Zero());
	}
	else {
		// bodies.front().set_dir(angle(bodies.front().get_body_pos(), dest));
		bodies.front().set_dir((dest - bodies.front().get_pos()).normalized());
	}
}

void Centipede::add_body() {
	++length;
	// bodies.emplace_back(bodies.back());
	CentipedeBody body = bodies.back();
	bodies.emplace_back(bodies.back().get_pos(), body_size, bodies.back().get_noise() - Math::QuarterPi);
	// bodies.emplace_back(body);
}

void Centipede::update_pos() {
	// 各胴体についてdirに基づいて移動
	for (int i = 0; i < length; ++i) {
		Vec2 p = bodies.at(i).get_pos();
		if (i != 0 && (bodies.at(i - 1).get_pos() - p).lengthSq() < interval * interval) continue; // 間隔が十分でない場合は飛ばす
		bodies.at(i).set_pos(p + (Scene::DeltaTime() * spd * bodies.at(i).get_dir()));
	}
}

void Centipede::update_dir() {
	// 先頭の場合、destを現在の方向に幅を持たせた直線上に投影(クランプ)させ、その後dir_range.yの分だけ前方にある直交する直線上に投影する
	// まず幅を持たせた方向ベクトルに投影
	Vec2 p1 = dest, p2 = bodies.front().get_pos(), p3 = bodies.front().get_dir(), p4 = p2 + p3 * dir_range.y, n = CG2D::normal(p3);
	Line v1(p2 + n * dir_range.x, p2 + n * dir_range.x + p3), v2(p2 - n * dir_range.x, p2 - n * dir_range.x + p3);
	double d1 = CG2D::dist_l_p(v1, p1), d2 = CG2D::dist_l_p(v2, p1);
	if (d1 * d2 > 0) {
		if (d1 < 0) p1 = CG2D::projection(v1, p1);
		else p1 = CG2D::projection(v2, p1);
	}
	// 胴体前方方向に投影
	p1 = CG2D::projection(Line(p4, p4 + n), p1);
	
	// DeltaTimeをかますために一旦angleに直す
	double a = CG2D::angle_between_vec(p3.normalized(), (p1 - p2).normalized());
	a = CG2D::angle(Vec2::Zero(), p3) + Scene::DeltaTime() * a * 50;

	// 方向をセット
	// p1 = (p1 - p2).normalized();
	p1 = CG2D::angle_to_vec2(a);
	bodies.front().set_dir(p1);

	// 各胴体について目的地p1への角度を測る
	for (int i = 1; i < length; ++i) {
		p1 = p2;
		p2 = bodies.at(i).get_pos();
		if (p1.distanceFromSq(p2) < CG2D::EPS) continue; // 間隔が十分でない場合は飛ばす
		bodies.at(i).set_dir((p1 - p2).normalized());
		// bodies.at(i).set_dir(angle(p2, p1));
	}
}

void Centipede::Update() {
	if (flag_movable) {
		update_pos();
		update_dir();
	}
}

void Centipede::Draw() const {
	// 触角
	// 触角の方向ベクトルを両方求める
	Vec2 v1 = ( bodies.front().get_dir() * body_size * 1.5 + CG2D::normal(bodies.front().get_dir()) * body_size * 0.7).normalized();
	Vec2 v2 = CG2D::reflection(Line(Vec2::Zero(), bodies.front().get_dir()), v1);
	Line(bodies.front().get_pos() + v1 * body_size * 1.5, bodies.front().get_pos() + v1 * body_size * 3.5).draw(2, col_antenna);
	Line(bodies.front().get_pos() + v2 * body_size * 1.5, bodies.front().get_pos() + v2 * body_size * 3.5).draw(2, col_antenna);
	// Line(bodies.front().get_body_pos() + v2 * body_size * 1.5, bodies.front().get_body_pos() + v2 * body_size * 4).draw(2, Palette::White);

	for (auto const& body : bodies) {
		body.Draw();
	}
}

Centipede Centipede::bodies_movedBy(Vec2 const& v) const{
	Centipede res = *this;
	for (auto& i : res.bodies) {
		i.moveBy(v);
	}
	return res;
}

Array<CentipedeBody> const& Centipede::get_bodies() const {
	return bodies;
}

double Centipede::get_spd() const {
	return spd;
}

Vec2 Centipede::get_dir_range() const {
	return dir_range;
}

int Centipede::get_length() const {
	return length;
}

int Centipede::get_body_size() const {
	return body_size;
}

CentipedeBody const& Centipede::get_body_front() const{
	return bodies.front();
}

void Centipede::set_dest(Vec2 const dest_) {
	dest = dest_;
}

void Centipede::set_spd(double const spd_) {
	spd = spd_;
}

void Centipede::set_dir_range(Vec2 const dir) {
	dir_range = dir;
}

void Centipede::set_interval(int const interval_){
	interval = interval_;
}

void Centipede::set_col_body(Color const col, int const idx) {
	bodies.at(idx).set_col(col);
}

void Centipede::set_col_body_all(Color const col){
	for (auto& i : bodies) {
		i.set_col(col);
	}
}

void Centipede::set_col_body_inner_all(Color const col) {
	for (auto& i : bodies) {
		i.set_col_inner(col);
	}
}

void Centipede::set_col_antenna(Color const col){
	col_antenna = col;
}

void Centipede::set_legs_anim_flag(bool const flag){
	for (auto& i : bodies) {
		i.set_legs_anim_flag(flag);
	}
}

void Centipede::set_flag_movable(bool const b){
	flag_movable = b;
}
