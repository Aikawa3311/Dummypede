#include "stdafx.h"
#include "Page_Creepy.h"

void Page_Creepy::Draw() const {
	RectF(Vec2::Zero(), size).draw(Palette::White);
	double rot = Math::Pi * 3.2;

	RectF balloon = RectF(Point(10, 40), size.movedBy(-10 * 2, -90));
	balloon.drawFrame(2, Palette::Mediumblue);
	int n = 40;
	double bal_wh = (balloon.w + balloon.h) / n;
	double stripe_t = Periodic::Sawtooth0_1(2s);
	{
		ScopedViewport2D viewport(balloon.movedBy(pos).asRect());
		for (int i = 0; i < n + 1; ++i) {
			Line(Vec2(-balloon.h + bal_wh * i + stripe_t * bal_wh, 0), Vec2(bal_wh * i + stripe_t * bal_wh, balloon.h)).draw(3, ColorF(Palette::Mediumblue, 0.1));
		}
		/*for (int i = 0; i < n; ++i) {
			Line(Vec2(-balloon.h + bal_wh * i - stripe_t * bal_wh, balloon.h), Vec2(bal_wh * i - stripe_t * bal_wh, 0)).draw(3, ColorF(Palette::Mediumblue, 0.1));
		}*/
	}

	double smile_t = Periodic::Sine0_1(6s);
	Vec2 smile_pos = Vec2(15 + smile_t * (size.x - 30), size.y).movedBy(-15, -30);
	FontAsset(U"RegularDot")(U"YOU ARE BRAVE BUT NOTHING HERE :)").draw(Arg::center = (size / 2).movedBy(0, -8), Palette::Mediumblue);
	// Shape2D::RectBalloon(RectF(Point(10, 40), size.movedBy(-10 * 2, -90)), smile_pos.movedBy(15, -10), 0.2).drawFrame(2, Palette::Mediumblue);
	TextureAsset(U"Smile").rotatedAt(TextureAsset(U"Smile").size() / 2.0, smile_t * rot - rot / 2).draw(smile_pos, Palette::Black);
}

void Page_Creepy::Update() {
	if (!active) return;
}

Page_Creepy::Page_Creepy()
	: // WindowSystem(Vec2(Scene::Width() / 2 - 400 / 2, Scene::Height() / 2 - 150 / 2), Size(400, 150), U"Creepy?")
	WindowSystem(Vec2(GameControl::base_size.x / 2 - 400 / 2, GameControl::base_size.y / 2 - 150 / 2), Size(400, 150), U"Creepy?")
{
}
