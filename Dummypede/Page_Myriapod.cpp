#include "stdafx.h"
#include "Page_Myriapod.h"

void Page_Myriapod::Draw() const {
	RectF(Vec2::Zero(), size).draw(Palette::Papayawhip);
	// 2001/09/09の次を問う
	// FontAsset(U"RegularMintyo")(U"what's next on 2001/09/09?").draw(Vec2(5, 35), Palette::White);

	FontAsset(U"RegularMintyo")(U"Welcome to the NEW ERA of Billion Seconds,\nFlower Magic-Using Unix Players!\nOur song goes in each billisecond for billion seconds,\nmore beautifully than madness.").draw(Vec2(20, 40), Palette::Black);
	FontAsset(U"RegularMintyo")(U"One second is long enough to be, or not to be.").draw(Vec2(20, 125), Palette::Black);
	FontAsset(U"RegularMintyo")(U"Any name space is volatile, leaving the eternal.").draw(Vec2(20, 160), Palette::Black);
	FontAsset(U"RegularMintyo")(U"The story began from 1970/01/01").draw(Arg::center = Vec2(size.x / 2, 370), Palette::Black);

	// 表1の描画
	Line(Vec2(40, 240), Vec2(290, 240)).draw(2, Palette::Black);
	Line(Vec2(40, 240 + 30), Vec2(290, 240 + 30)).draw(2, Palette::Black);
	Line(Vec2(40, 240 + 60), Vec2(290, 240 + 60)).draw(2, Palette::Black);
	Line(Vec2(40, 240 + 90), Vec2(290, 240 + 90)).draw(2, Palette::Black);

	Line(Vec2(40, 240), Vec2(40, 240 + 90)).draw(2, Palette::Black);
	Line(Vec2(160, 240), Vec2(160, 240 + 90)).draw(2, Palette::Black);
	Line(Vec2(290, 240), Vec2(290, 240 + 90)).draw(2, Palette::Black);

	FontAsset(U"RegularConsol")(U"2001/09/09").draw(Arg::bottomLeft = Vec2(40, 235), Palette::Black);
	FontAsset(U"RegularConsol")(U"10:46:39").draw(Arg::center = Vec2(100, 255 + 2), Palette::Black);
	FontAsset(U"RegularConsol")(U"10:46:40").draw(Arg::center = Vec2(100, 285 + 2), Palette::Black);
	FontAsset(U"RegularConsol")(U"10:46:41").draw(Arg::center = Vec2(100, 315 + 2), Palette::Black);
	FontAsset(U"RegularConsol")(U"999999999").draw(Arg::rightCenter = Vec2(285, 255 + 2), Palette::Black);
	FontAsset(U"RegularConsol")(U"1000000000").draw(Arg::rightCenter = Vec2(285, 285 + 2), Palette::Black);
	FontAsset(U"RegularConsol")(U"1000000001").draw(Arg::rightCenter = Vec2(285, 315 + 2), Palette::Black);

	// 表2の描画
	Line(Vec2(310, 240), Vec2(560, 240)).draw(2, Palette::Black);
	Line(Vec2(310, 240 + 30), Vec2(560, 240 + 30)).draw(2, Palette::Black);
	Line(Vec2(310, 240 + 60), Vec2(560, 240 + 60)).draw(2, Palette::Black);
	Line(Vec2(310, 240 + 90), Vec2(560, 240 + 90)).draw(2, Palette::Black);

	Line(Vec2(310, 240), Vec2(310, 240 + 90)).draw(2, Palette::Black);
	Line(Vec2(430, 240), Vec2(430, 240 + 90)).draw(2, Palette::Black);
	Line(Vec2(560, 240), Vec2(560, 240 + 90)).draw(2, Palette::Black);

	FontAsset(U"RegularConsol")(U"YYYY/MM/DD").draw(Arg::bottomLeft = Vec2(310, 235), Palette::Mediumvioletred);
	FontAsset(U"RegularConsol")(U"12:14:07").draw(Arg::center = Vec2(370, 255 + 2), Palette::Black);
	FontAsset(U"RegularConsol")(U"12:14:08").draw(Arg::center = Vec2(370, 285 + 2), Palette::Black);
	FontAsset(U"RegularConsol")(U"12:14:09").draw(Arg::center = Vec2(370, 315 + 2), Palette::Black);
	FontAsset(U"RegularConsol")(U"2147483647").draw(Arg::rightCenter = Vec2(555, 255 + 2), Palette::Black);
	FontAsset(U"RegularConsol")(U"-2147483648").draw(Arg::rightCenter = Vec2(555, 285 + 2), Palette::Black);
	FontAsset(U"RegularConsol")(U"-2147483647").draw(Arg::rightCenter = Vec2(555, 315 + 2), Palette::Black);


	for (auto y : step(files.height())) {
		for (auto x : step(files.width())) {
			if (!files[y][x]) continue;
			RectF(-file_size / 2 + file_size * Size(x, y), TextureAsset(U"file_feed" + Format((y + x) % 5)).size()).draw(Palette::Black);
			TextureAsset(U"file_feed" + Format((y + x) % 5)).draw(-file_size / 2 + file_size * Size(x, y));
		}
	}
	// centipede gameとやり取り
	auto& pages_centipedegame = manager.get_page_centipede_game();
	for (int i = 0; i < (int)pages_centipedegame.size(); ++i) {
		if (std::shared_ptr<Page_CentipedeGame> page = pages_centipedegame[i].lock()) {
			if (page->get_state() <= 2) return;
			ColorF blend(0.5, 0.5, 0.5);
			const ScopedColorMul2D colorMul{ page->get_state() == 5 ? blend : ColorF(1, 1, 1) };
			page->get_centipede().bodies_movedBy(page->get_pos() - get_pos()).Draw();
		}
	}
}

void Page_Myriapod::Update() {
	// centipede gameとやり取り
	auto& pages_centipedegame = manager.get_page_centipede_game();
	for (int i = 0; i < (int)pages_centipedegame.size(); ++i) {
		if (std::shared_ptr<Page_CentipedeGame> page = pages_centipedegame[i].lock()) {
			// stateがゲーム中なら処理を行う
			if (page->get_state() != 3) return;

			Centipede const& centipede = page->get_centipede();
			// centipedeの先頭の円とファイルの交差判定を行う
			Circle circ = centipede.get_body_front().get_circle().movedBy(page->get_pos() - get_pos());
			// myriapodがアクティブでなく、かつcentipedeがcentipede gameのウィンドウ内にいる場合は交差判定を行わない
			if (!active && page->rect().stretched(-10, -10).intersects(circ.center.movedBy(get_pos()))) return;
			for (auto y : step(files.height())) {
				for (auto x : step(files.width())) {
					if (!files[y][x] || !Rect(-file_size / 2 + file_size * Size(x, y), file_size).intersects(circ)) continue;

					// 交差している場合
					files[y][x] = false;
					page->score_increment();
				}
			}
		}
	}
}

Page_Myriapod::Page_Myriapod(WindowSystemManager& manager)
	:WindowSystem(Vec2(50, 150), Size(600, 400), U"myriapod"),
	manager(manager),
	file_size(30, 40),
	files(Size(600 / file_size.x + 1, 400 / file_size.y + 1), true) {

}
