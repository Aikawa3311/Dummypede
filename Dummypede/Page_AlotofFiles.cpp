#include "stdafx.h"
#include "Page_AlotofFiles.h"

void Page_AlotofFiles::Draw() const{
	RectF(Vec2::Zero(), size).draw(Palette::Black);
	// 2001/09/09の次を問う
	FontAsset(U"BigLucida")(U"what's next on\n2001/09/09?").drawAt(size/2, Palette::Red);

	for (auto y : step(files.height())) {
		for (auto x : step(files.width())) {
			if (!files[y][x]) continue;
			RectF(-file_size / 2 + file_size * Size(x, y), TextureAsset(U"file_feed" + Format((y + x) % 5)).size()).draw(Palette::Black);
			TextureAsset(U"file_feed" + Format((y + x) % 5)).draw(-file_size/2 + file_size * Size(x, y));
		}
	}
	// centipede gameとやり取り
	if (std::shared_ptr<Page_CentipedeGame> page = manager.get_page_centipede_game().lock()) {
		if (page->get_state() <= 2) return;
		page->get_centipede().bodies_movedBy(page->get_pos() - get_pos()).Draw();
	}
}

void Page_AlotofFiles::Update(){
	// centipede gameとやり取り
	if (std::shared_ptr<Page_CentipedeGame> page = manager.get_page_centipede_game().lock()) {
		// stateがゲーム中なら処理を行う
		if (page->get_state() != 3) return;

		Centipede const & centipede = page->get_centipede();
		// centipedeの先頭の円とファイルの交差判定を行う
		Circle circ = centipede.get_body_front().get_circle().movedBy(page->get_pos() - get_pos());
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

Page_AlotofFiles::Page_AlotofFiles(WindowSystemManager& manager)
	:WindowSystem(Vec2(50, 50), Size(300, 300), U"myriapod"),
	manager(manager),
	file_size(30, 40),
	files(Size(500 / file_size.x + 1, 300 / file_size.y + 1), true){

}
