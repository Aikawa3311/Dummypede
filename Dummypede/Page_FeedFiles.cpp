#include "stdafx.h"
#include "Page_FeedFiles.h"

void Page_FeedFiles::Draw() const {
	RectF(Vec2::Zero(), size).draw(Palette::Black);
	Line(Vec2(0, 50), Vec2(size.x / 2 - 25, 50)).draw(5, Palette::Navajowhite);
	Line(Vec2(0, 60), Vec2(size.x / 2 - 25, 60)).draw(5, Palette::Navajowhite);

	Line(Vec2(size.x / 2 + 25, 50), Vec2(size.x, 50)).draw(5, Palette::Navajowhite);
	Line(Vec2(size.x / 2 + 25, 60), Vec2(size.x, 60)).draw(5, Palette::Navajowhite);

	TextureAsset(U"feed_food").drawAt(Vec2(size.x/2, 55));

	TextureAsset(U"mukade_feeder").draw(Vec2(-90, 65));
	// ウィンドウ枠
	RectF(Vec2(-10, 70), Vec2(120, 140)).drawFrame(3, Palette::Gray);
	RectF(Vec2(-10, 70), Vec2(120, 25)).draw(Arg::left = Palette::Blue, Arg::right = Palette::Dodgerblue.lerp(Palette::Blue, 0.2)).drawFrame(3, Palette::Gray);

	TextureAsset(U"file_feed0").draw(Vec2(130, 115));
	TextureAsset(U"file_feed1").draw(Vec2(170, 115));
	TextureAsset(U"file_feed2").draw(Vec2(210, 115));
	TextureAsset(U"file_feed3").draw(Vec2(250, 115));
	TextureAsset(U"file_feed4").draw(Vec2(290, 115));
}

void Page_FeedFiles::Update() {
	
}

Page_FeedFiles::Page_FeedFiles()
	:WindowSystem(Vec2(800, 100), Size(330, 190), U"feedfiles"){
}
