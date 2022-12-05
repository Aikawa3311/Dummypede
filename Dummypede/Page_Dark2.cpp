#include "stdafx.h"
#include "Page_Dark2.h"

void Page_Dark2::Draw() const {
	RectF(Vec2::Zero(), size).draw(Palette::Black);
	// TextureAsset(U"arrow").draw(Vec2::Zero());
	Line(Vec2::Zero().movedBy(10, size.y / 2), Vec2::Zero().movedBy(size.x - 10, size.y / 2)).drawArrow(3, Vec2(20, 20));
	for (int i = 0; i < (int)links.size(); ++i) {
		links[i].draw(cols[i]);
	}


	// take a break...
	FontAsset(U"RegularConsol")(U"take a break").draw(Arg::bottomRight = size.movedBy(-10, -10), Palette::White);
	Line(link.pos.movedBy(0, link.h), link.pos.movedBy(link.w, link.h)).draw(1.5, Palette::White);
}

void Page_Dark2::Update() {
	if (!active) return;
	// ハイライトする
	for (int i = 0; i < (int)links.size(); ++i) {
		if (links[i].intersects(Cursor::PosF().movedBy(-pos))) {
			cols[i] = Palette::Cornflowerblue;
			// Cursor::RequestStyle(CursorStyle::Hand);
			// Cursor::RequestStyle(U"hand");
			GameControl::decorator.RequestStyle(U"hand");
		}
		else {
			cols[i] = Palette::White;
		}
	}
	// クリックされたらページを表示
	// ──┐  1 2 3      5 7 1
	// ┌─┘  4 5 6  →  9 2 3
	// └─→  7 8 9      6 4 8
	for (int i = 0; i < (int)links.size(); ++i) {
		if (links[i].movedBy(pos).leftClicked()) {
			switch (i) {
			case 0:
				// ad
				manager.add_page(std::make_shared<Page_DarkPage7>(manager, positions[i]));
				break;
			case 1:
				// te
				manager.add_page(std::make_shared<Page_DarkPage8>(manager, positions[i]));
				break;
			case 2:
				// tr
				manager.add_page(std::make_shared<Page_DarkPage9>(manager, positions[i]));
				break;
			}
		}
	}

	// リンクの押下判定
	if (link.intersects(Cursor::PosF().movedBy(-pos))) {
		GameControl::decorator.RequestStyle(U"hand");
		if (MouseL.down()) {
			int num = manager.page_name_to_page_number(U"Sunset");
			if (num != -1) {
				manager.focus_page(num);
			}
			else {
				manager.add_page(std::make_shared<Page_Sunset>());
			}
		}
	}
}

Page_Dark2::Page_Dark2(WindowSystemManager& manager)
	:manager(manager),
	WindowSystem(Vec2(100, 100), Size(500, 300), U"darker"),
	links(3),
	cols(3, Palette::White),
	positions(3),
	link(size.movedBy(-144, -40), Size(138, 32))
{
	int margin = 32 + 19;
	/*
	links[0] = Circle(350, 80, 16);
	links[1] = Circle(350, 150, 16);
	links[2] = Circle(250, 152, 16);
	positions[0] = Vec2(700, 300);
	positions[1] = Vec2(300, 500);
	positions[2] = Vec2(300, 100);
	*/
	links[0] = Circle(30 + margin * 2, size.y / 2, 16);
	links[1] = Circle(30 + margin * 3, size.y / 2, 16);
	links[2] = Circle(30 + margin * 4, size.y / 2, 16);
	// positions[0] = Vec2(275, Scene::Height() / 2 - 75);
	// positions[1] = Vec2(405, Scene::Height() / 2 - 75);
	// positions[2] = Vec2(535, Scene::Height() / 2 - 75);
	positions[0] = Vec2(275, GameControl::base_size.y / 2 - 75);
	positions[1] = Vec2(405, GameControl::base_size.y / 2 - 75);
	positions[2] = Vec2(535, GameControl::base_size.y / 2 - 75);

	// Darkページ到達フラグをオンに
	GameControl::flag_visited_darker = true;
}
