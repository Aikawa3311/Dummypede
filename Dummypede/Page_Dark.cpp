#include "stdafx.h"
#include "Page_Dark.h"

void Page_Dark::Draw() const{
	RectF(Vec2::Zero(), size).draw(Palette::Black);
	// TextureAsset(U"arrow").draw(Vec2::Zero());
	Line(Vec2::Zero().movedBy(10, size.y / 2), Vec2::Zero().movedBy(size.x - 10, size.y / 2)).drawArrow(3, Vec2(20, 20));
	for (int i = 0; i < (int)links.size(); ++i) {
		links[i].draw(cols[i]);
	}
}

void Page_Dark::Update(){
	if (!active) return;
	// ハイライトする
	for (int i = 0; i < (int)links.size(); ++i) {
		if (links[i].intersects(Cursor::PosF().movedBy(-pos))) {
			cols[i] = Palette::Cornflowerblue;
			// Cursor::RequestStyle(CursorStyle::Hand);
			// Cursor::RequestStyle(U"hand");
			GameControl::decorator.RequestStyle(U"hand");
		}else{
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
				// my
				manager.add_page(std::make_shared<Page_DarkPage1>(manager, positions[i]));
				break;
			case 1:
				// ri
				manager.add_page(std::make_shared<Page_DarkPage2>(manager, positions[i]));
				break;
			case 2:
				// ap
				manager.add_page(std::make_shared<Page_DarkPage3>(manager, positions[i]));
				break;
			case 3:
				// od
				manager.add_page(std::make_shared<Page_DarkPage4>(manager, positions[i]));
				break;
			case 4:
				// .n
				manager.add_page(std::make_shared<Page_DarkPage5>(manager, positions[i]));
				break;
			case 5:
				// et
				manager.add_page(std::make_shared<Page_DarkPage6>(manager, positions[i]));
				break;
			}
		}
	}
}

Page_Dark::Page_Dark(WindowSystemManager& manager)
	:manager(manager),
	WindowSystem(Vec2(100, 100), Size(500, 300), U"dark"),
	links(6),
	cols(6, Palette::White),
	positions(6){
	// ここで6つのリンクの描画位置とウィンドウ出現場所を設定
	/*
	links[0] = Circle(150, 84, 16);
	links[1] = Circle(250, 80, 16);
	links[2] = Circle(150, 160, 16);
	links[3] = Circle(150, 224, 16);
	links[4] = Circle(250, 220, 16);
	links[5] = Circle(350, 212, 16);
	positions[0] = Vec2(700, 100);
	positions[1] = Vec2(500, 300);
	positions[2] = Vec2(500, 500);
	positions[3] = Vec2(500, 100);
	positions[4] = Vec2(700, 500);
	positions[5] = Vec2(300, 300);
	*/
	/*
	links[0] = Circle(150, 160, 16);
	links[1] = Circle(150, 224, 16);
	links[2] = Circle(250, 80, 16);
	links[3] = Circle(150, 84, 16);
	links[4] = Circle(250, 220, 16);
	links[5] = Circle(350, 212, 16);
	positions[0] = Vec2(Scene::Width() / 2 - (30 * 9) / 2 + 30 * 3, Scene::Height() / 2 - 200 / 2);
	positions[1] = Vec2(Scene::Width() / 2 - (30 * 9) / 2 + 30 * 2, Scene::Height() / 2 - 200 / 2);
	positions[2] = Vec2(Scene::Width() / 2 - (30 * 9) / 2 + 30 * 0, Scene::Height() / 2 - 200 / 2);
	positions[3] = Vec2(Scene::Width() / 2 - (30 * 9) / 2 + 30 * 1, Scene::Height() / 2 - 200 / 2);
	positions[4] = Vec2(Scene::Width() / 2 - (30 * 9) / 2 + 30 * 7, Scene::Height() / 2 - 200 / 2);
	positions[5] = Vec2(Scene::Width() / 2 - (30 * 9) / 2 + 30 * 8, Scene::Height() / 2 - 200 / 2);
	*/
	int margin = 32 + 19;
	links[0] = Circle(30, size.y / 2, 16);
	links[1] = Circle(30 + margin, size.y / 2, 16);
	links[2] = Circle(30 + margin * 5, size.y / 2, 16);
	links[3] = Circle(30 + margin * 6, size.y / 2, 16);
	links[4] = Circle(30 + margin * 7, size.y / 2, 16);
	links[5] = Circle(30 + margin * 8, size.y / 2, 16);
	/*positions[0] = Vec2(15, Scene::Height() / 2 - 75);
	positions[1] = Vec2(145, Scene::Height() / 2 - 75);
	positions[2] = Vec2(665, Scene::Height() / 2 - 75);
	positions[3] = Vec2(795, Scene::Height() / 2 - 75);
	positions[4] = Vec2(925, Scene::Height() / 2 - 75);
	positions[5] = Vec2(1055, Scene::Height() / 2 - 75);*/
	positions[0] = Vec2(15, GameControl::base_size.y / 2 - 75);
	positions[1] = Vec2(145, GameControl::base_size.y / 2 - 75);
	positions[2] = Vec2(665, GameControl::base_size.y / 2 - 75);
	positions[3] = Vec2(795, GameControl::base_size.y / 2 - 75);
	positions[4] = Vec2(925, GameControl::base_size.y / 2 - 75);
	positions[5] = Vec2(1055, GameControl::base_size.y / 2 - 75);

	// Darkページ到達フラグをオンに
	GameControl::flag_visited_dark = true;
}
