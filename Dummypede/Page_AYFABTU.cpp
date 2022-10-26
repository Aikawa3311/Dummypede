#include "stdafx.h"
#include "Page_AYFABTU.h"

void Page_AYFABTU::Draw() const{
	TextureAsset(U"ayfabtu").draw(0, 5);
	// Shape2D::RectBalloon(RectF(190, 35, 180, 130), Vec2(150, 60)).drawFrame(2, Palette::Black);
	Shape2D::RectBalloon(RectF(190, 35, 180, 135), Vec2(210, 190)).drawFrame(2, Palette::Black);
	FontAsset(U"SmallRegular")(U"You should visit\ndummypede.net\nand solve the riddle\nor all of your data\nare deleted!").draw(200, 40, Palette::White);
	FontAsset(U"RegularDot")(U"search!→ ISBN-13").draw(Arg::bottomRight = size.movedBy(-10, -3), Palette::Cadetblue);
}

void Page_AYFABTU::Update(){
}

Page_AYFABTU::Page_AYFABTU()
	: WindowSystem(Scene::Size() - Size(400, 200), Size(400, 200), U"ayfabtu"){
	set_erasable(false);
	window_alpha = 0.5;
}
