#include "stdafx.h"
#include "Page_SelfIntroduction.h"

void Page_SelfIntroduction::Draw() const{
	RectF(Vec2::Zero(), size).draw(Palette::Wheat);
	TextureAsset(U"elk").draw(Vec2(250, 100));
	// ページタイトル
	// FontAsset(U"BigEdwardian")(U"Self Introduction").drawAt((size / 2).movedBy(0, -130), Palette::Black);
	TextureAsset(U"selfintroduction").drawAt((size / 2).movedBy(0, -130));
	// 名前
	Vec2 draw_pos(40, 180);

	// アクセスレベルに応じて内容変化
	int const access_level = Page_MukadeShell::get_access_level();

	// Twitter
	Line(Vec2(20, 280), Vec2(135, 280)).draw(3, Palette::Black);
	Line(Vec2(160, 280), Vec2(370, 280)).draw(3, Palette::Black);
	if (access_level < 2) {
		draw_pos = Vec2(25, 270);
		for (auto const& glyph : FontAsset(U"BigRegular").getGlyphs(twitter_column)) {
			TextureAsset(U"selfintroduction_" + Format(glyph.codePoint)).draw(Arg::bottomLeft = draw_pos, Palette::Deepskyblue);
			draw_pos.x += 36;
		}
		draw_pos = Vec2(160, 270);
		for (auto const& glyph : FontAsset(U"BigRegular").getGlyphs(twitter_name)) {
			TextureAsset(U"selfintroduction_" + Format(glyph.codePoint)).draw(Arg::bottomLeft = draw_pos, Palette::Black);
			draw_pos.x += 36;
		}
	}
	else {
		TextureAsset(U"selfintroduction_twitter").draw(Arg::bottomLeft = Vec2(25, 270), Palette::Deepskyblue);
		FontAsset(U"RegularDot")(U"@elk20000101").draw(Arg::bottomLeft = Vec2(160, 276), Palette::Black);
	}

	// Youtube
	Line(Vec2(20, 360), Vec2(135, 360)).draw(3, Palette::Black);
	Line(Vec2(160, 360), Vec2(370, 360)).draw(3, Palette::Black);
	if (access_level < 3) {
		draw_pos = Vec2(25, 350);
		for (auto const& glyph : FontAsset(U"BigRegular").getGlyphs(youtube_column)) {
			TextureAsset(U"selfintroduction_" + Format(glyph.codePoint)).draw(Arg::bottomLeft = draw_pos, Palette::Red);
			draw_pos.x += 36;
		}
		draw_pos = Vec2(160, 350);
		for (auto const& glyph : FontAsset(U"BigRegular").getGlyphs(youtube_name)) {
			TextureAsset(U"selfintroduction_" + Format(glyph.codePoint)).draw(Arg::bottomLeft = draw_pos, Palette::Black);
			draw_pos.x += 36;
		}
	}
	else {
		TextureAsset(U"selfintroduction_youtube").draw(Arg::bottomLeft = Vec2(25, 350), Palette::Red);
		FontAsset(U"RegularDot")(U"evnnzqfef20").draw(Arg::bottomLeft = Vec2(160, 356), Palette::Black);
	}

	// 名前
	Line(Vec2(34, 190), Vec2(220, 190)).draw(3, Palette::Black);
	if (access_level < 4) {
		draw_pos = Vec2(40, 180);
		for (auto const& glyph : FontAsset(U"BigRegular").getGlyphs(name)) {
			TextureAsset(U"selfintroduction_" + Format(glyph.codePoint)).draw(Arg::bottomLeft = draw_pos, Palette::Black);
			draw_pos.x += 36;
		}
	}
	else {
		FontAsset(U"RegularDot")(U"dummypede").draw(Arg::bottomLeft = Vec2(40, 186), Palette::Black);
	}
}

void Page_SelfIntroduction::Update(){
	if (!active) return;
	// 画像がリンクになっている
	if (RectF(Vec2(250, 100), Size(100, 100)).intersects(Cursor::PosF().movedBy(-pos))) {
		// Cursor::RequestStyle(CursorStyle::Hand);
		// Cursor::RequestStyle(U"hand");
		GameControl::decorator.RequestStyle(U"hand");
		if (MouseL.down()) {
			manager.add_page(std::make_shared<Page_SelfIntroductionImage>());
		}
	}
}

String Page_SelfIntroduction::random_digit_str(int const digit){
	String tmp = U"";
	for (int i = 0; i < digit; ++i) {
		tmp += Format(Random(0, 9));
	}
	return tmp;
}

Page_SelfIntroduction::Page_SelfIntroduction(WindowSystemManager & manager)
	:WindowSystem(Vec2(160, 190), Size(400, 400), U"self introduction"),
	manager(manager){

	name_column = random_digit_str(4);
	name = random_digit_str(5);
	twitter_column = random_digit_str(3);
	twitter_name = random_digit_str(6);
	youtube_column = random_digit_str(3);
	youtube_name = random_digit_str(5);

	int const access_level = Page_MukadeShell::get_access_level();
	if (access_level >= 2) {
		twitter_column = U"twitter";
		twitter_name = U"@dummypede15821015";
	}
	else if (access_level >= 3) {
		youtube_column = U"youtube";
		youtube_name = U"evnnzqfef26932126";
	}
}
