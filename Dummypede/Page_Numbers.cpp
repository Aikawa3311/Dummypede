#include "stdafx.h"
#include "Page_Numbers.h"

void Page_Numbers::Draw() const{
	RectF(Vec2::Zero(), size).draw(Palette::Black);
	rect.drawFrame(2, Palette::White);
	TextureAsset(U"numbers").draw(rect.pos);
	Shape2D::RectBalloon(RectF(rect.pos.movedBy(190, 35), 180, 135), rect.pos.movedBy(210, 190)).drawFrame(2, Palette::White);
	RectF(rect.pos, Vec2(rect.size.x, 30)).draw(Palette::Black).drawFrame(2, Palette::White);
	FontAsset(U"RegularDot")(U"I've seen this\nsomewhere...").draw(rect.pos.movedBy(200, 75), Palette::White);
	thinking_tex.resized(40).drawAt((size/2).movedBy(0, 125));
}

void Page_Numbers::Update(){
}

Page_Numbers::Page_Numbers()
	: // WindowSystem(Scene::CenterF() - Size(500, 300) / 2, Size(500, 300), U"numbersnumbers"),
	WindowSystem(GameControl::base_size / 2 - Size(500, 300) / 2, Size(500, 300), U"numbersnumbers"),
	rect((size / 2).movedBy(-200, -100), Size(400, 200)),
	thinking_tex(U"🤔"_emoji) {
}
