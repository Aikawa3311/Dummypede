#include "CG2D.h"

Vec2 CG2D::normal(Vec2 const& v) {
	return Vec2(v.y, -v.x);
}

Vec2 CG2D::normal(Line const& l) {
	return normal(l.vector());
}

// 左回り判定用列挙型
enum class CG2D::CCWResultType {
	CCW,			// 反時計回り
	CW,				// 時計回り
	ONLINE_BACK,    // 直線上、p0より後ろ
	ONLINE_FRONT,   // 直線上、p1より奥
	ON_SEGMENT      // 線分上、あるいはp0上かp1上
};

// 角度から正規化したベクトルを返す
Vec2 CG2D::angle_to_vec2(double const angle) {
	return Vec2(Cos(angle), Sin(angle));
}

// 2つの位置ベクトルから角度を計算
double CG2D::angle(Vec2 const& from, Vec2 const& to) {
	return atan2(to.y - from.y, to.x - from.x);
}

double CG2D::angle_between_vec(Vec2 const& vec1, Vec2 const& vec2){
	double denom = vec1.length() * vec2.length();
	if (denom < 1e-9) {
		return 0;
	}
	double res = vec1.dot(vec2) / denom;
	if (res < 1e-9) {
		return 0;
	}
	if (1 - res < 1e-9) {
		return 0;
	}
	res = Acos(res);

	double c = vec1.cross(vec2);
	if (c < 0.0) {
		res = -res;
	}
	return res;
	

}

// 直線と点の距離(ベクトルから見て左側なら負)
double CG2D::dist_l_p(Line const& l, Vec2 const& p) {
	Vec2 const v = l.vector();
	return v.cross(p - l.begin) / v.length();
}

// 点を直線上に投影
Vec2 CG2D::projection(Line const& l, Vec2 const& p) {
	Vec2 v1 = l.vector(), v2 = p - l.begin;
	double d = v2.dot(v1) / v1.length();
	return l.begin + d * v1.normalized();
}

// 点を直線に鏡映
Vec2 CG2D::reflection(Line const& l, Vec2 const& p) {
	Vec2 v = projection(l, p);
	return 2 * v - p;
}

// p1-p2-p3を結んだ線分が時計回りか反時計回りか
CG2D::CCWResultType CG2D::ccw(Vec2 const& p1, Vec2 const& p2, Vec2 const& p3) {
	Vec2 v1 = p2 - p1, v2 = p3 - p1;
	double c = v1.cross(v2);
	if (c > EPS) return CCWResultType::CCW;
	else if (c < -EPS) return CCWResultType::CW;
	else if (v1.dot(v2) < 0) return CCWResultType::ONLINE_BACK;
	else if (v1.length() < v2.length()) return CCWResultType::ONLINE_FRONT;
	return CCWResultType::ON_SEGMENT;
}
