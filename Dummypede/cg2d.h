#pragma once
#include <Siv3D.hpp>

namespace CG2D
{
	double const EPS = 1e-6;

	// ベクトルの法線(右回り方向)
	Vec2 normal(Vec2 const& v);

	Vec2 normal(Line const& l);

	// 左回り判定用列挙型
	enum class CCWResultType;

	// 角度から正規化したベクトルを返す
	Vec2 angle_to_vec2(double const angle);

	// 2つの位置ベクトルから角度を計算
	double angle(Vec2 const& from, Vec2 const& to);

	// 2つの正規化ベクトルがなす符号付角度を計算
	double angle_between_vec(Vec2 const& vec1, Vec2 const& vec2);

	// 直線と点の距離(ベクトルから見て左側なら負)
	double dist_l_p(Line const& l, Vec2 const& p);

	// 点を直線上に投影
	Vec2 projection(Line const& l, Vec2 const& p);

	// 点を直線に鏡映
	Vec2 reflection(Line const& l, Vec2 const& p);

	// p1-p2-p3を結んだ線分が時計回りか反時計回りか
	CCWResultType ccw(Vec2 const& p1, Vec2 const& p2, Vec2 const& p3);
};
