#include "stdafx.h"
#include "Page_LastPassword.h"

void Page_LastPassword::Draw() const{
	RectF(Vec2::Zero(), size).draw(Palette::Bisque);
	RectF rect = RectF(Vec2::Zero(), size).stretched(-30, -25).movedBy(0, 15);
	rect.drawShadow(Vec2(4, 4), 5).draw(Palette::Deepskyblue);
	// TextureAsset(U"MiniBoss").drawAt(rect.pos.movedBy(0, 10), Palette::Darkblue);
	FontAsset(U"BigRegular")(U"FREE").drawAt((size / 2).movedBy(0, 15), Palette::White);
}

void Page_LastPassword::Update(){
}

Page_LastPassword::Page_LastPassword()
	:WindowSystem(Scene::Center().movedBy(-125, -50), Size(250, 100), U"Last Password"){
}
