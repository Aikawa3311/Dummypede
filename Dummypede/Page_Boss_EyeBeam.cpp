#include "stdafx.h"
#include "Page_Boss_EyeBeam.h"

EyeBeam::EyeBeam(Vec2 const pos_)
	:pos(pos_) {
	// マウスカーソルの方向を向く
	dir = (Cursor::PosF() - pos).normalized();
	hitbox = Line(pos, pos + dir * length);
}

void EyeBeam::Draw() const {
	hitbox.draw(8, Palette::Red);
}

void EyeBeam::Update() {
	hitbox.moveBy(dir * Scene::DeltaTime() * 1200);
}

Line const& EyeBeam::get_hitbox() const {
	return hitbox;
}
