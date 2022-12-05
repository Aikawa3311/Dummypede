#include "stdafx.h"
#include "Page_Opening.h"

void Page_Opening::Draw() const{
}

void Page_Opening::Update(){
	// 存在している間は常にカーソルを非表示
	GameControl::decorator.RequestStyle(U"hidden");

	if (timer.sF() >= 5) {
		// 自分が消える
		AudioAsset(U"pc").setVolume(0.5);
		AudioAsset(U"pc").play();
		auto const& pages = manager.get_pages();
		for (int i = 0; i < (int)pages.size(); ++i) {
			if (pages[i]->get_title() == U"Opening") {
				manager.erase_window(i);
			}
		}
		// centipede gameとayfabtuを作る
		manager.add_page(std::make_shared<Page_AYFABTU>(), false);
		std::shared_ptr<Page_CentipedeGame> page_centipedegame = std::make_shared<Page_CentipedeGame>();
		manager.add_page(page_centipedegame, false);
		manager.set_page_centipedegame(page_centipedegame);
	}
}

void Page_Opening::DrawDepth2() const{
	// Scene::Rect().draw(Palette::Black);
	Rect(Point::Zero(), GameControl::base_size).draw(Palette::Black);
}

Page_Opening::Page_Opening(WindowSystemManager& manager)
	: // WindowSystem(Vec2(-50, -50), Size(Scene::Size()).movedBy(100, 100), U"Opening"),
	WindowSystem(Vec2(-50, -50), GameControl::base_size.movedBy(100, 100), U"Opening"),
	manager(manager)
{
	AudioAsset(U"pc_start").setVolume(0.4);
	AudioAsset(U"pc_start").play();
	timer.start();
}
