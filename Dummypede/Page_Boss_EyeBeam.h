#pragma once
#include <Siv3D.hpp>

class EyeBeam {
private:
	double length = 70;
	Vec2 pos;
	Vec2 dir;

	Line hitbox;

public:
	EyeBeam(Vec2 const pos_);
	void Draw() const;
	void Update();

	Line const& get_hitbox() const;
};
