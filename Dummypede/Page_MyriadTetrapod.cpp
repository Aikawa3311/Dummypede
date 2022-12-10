#include "stdafx.h"
#include "Page_MyriadTetrapod.h"

void Page_MyriadTetrapod::Draw() const{
	RectF(Vec2::Zero(), size).draw(Palette::White);
	TextureAsset(U"tetra")(drag_pos, 500, 500).draw(Vec2::Zero(), ColorF(1, 1, 1, 0.7));
	screen_base.movedBy(-drag_pos).draw(Palette::Black);
	{
		Vec2 calibration = Vec2::Zero();
		calibration.x = Min(0.0, screen_base.x - drag_pos.x);
		calibration.y = Min(0.0, screen_base.y - drag_pos.y);

		bool lock_failure = true;
		auto& pages_screen = manager.get_page_screen();
		if (!pages_screen.isEmpty()) {
			if (std::shared_ptr<Page_Screen> p = pages_screen.back().lock()) {
				lock_failure = false;
				ScopedViewport2D viewport(screen.pos.movedBy(pos).asPoint(), screen.size.asPoint());
				for (int i = 0; i < item_num; ++i) {
					// TextureAsset(icons_name[i]).draw(icons_pos[i].movedBy(p->get_pos() + calibration));
					// TextureAsset(icons_name[i]).draw(icons_pos[i].movedBy(-screen.pos.movedBy(pos) - p->get_pos() + calibration));
					TextureAsset(icons_name[i]).draw(icons_pos[i].movedBy(-p->get_pos() + calibration), p->get_color());
				}
				TextureAsset(U"DoorClosed").draw(icon_door.movedBy(-p->get_pos() + calibration), Palette::Red);
			}
		}

		if(lock_failure) {
			FontAsset(U"Regular")(U"screen監視:未作動").drawAt(screen_base.pos.movedBy(-drag_pos + screen_base.size/2), Palette::White);
		}
	}
}

void Page_MyriadTetrapod::Update(){
	// スクリーンとの同期
	if (!RectF(drag_pos, size).intersects(screen_base)) {
		screen = RectF(0, 0, 0, 0);
	}
	else {
		screen = screen_base.movedBy(-drag_pos);
		screen.x = Max(0.0, screen.x);
		screen.y = Max(0.0, screen.y);
		screen.w = Clamp((screen_base.x > drag_pos.x) ? drag_pos.x + size.x - screen_base.x : screen_base.w - (drag_pos.x - screen_base.x), 0.0, 300.0);
		screen.h = Clamp((screen_base.y > drag_pos.y) ? drag_pos.y + size.y - screen_base.y : screen_base.h - (drag_pos.y - screen_base.y), 0.0, 300.0);
	}

	if (!active) return;
	if (rect_without_head_frame().intersects(Cursor::PosF())) {
		// Cursor::RequestStyle(CursorStyle::Cross);
		// Cursor::RequestStyle(U"grab1");
		GameControl::decorator.RequestStyle(U"grab1");
		if (MouseL.pressed()) {
			// マウス左入力で移動
			// Cursor::RequestStyle(U"grab2");
			GameControl::decorator.RequestStyle(U"grab2");
			drag_pos.moveBy(Cursor::PreviousPosF() - Cursor::PosF());
			drag_pos.clamp(RectF(0, 0, TextureAsset(U"tetra").size() - Size(500, 500)));
		}
	}
	// ドアクリック
	auto& pages_screen = manager.get_page_screen();
	if (!pages_screen.isEmpty()) {
		if (std::shared_ptr<Page_Screen> p = pages_screen.back().lock()) {
			Vec2 calibration = Vec2::Zero();
			calibration.x = Min(0.0, screen_base.x - drag_pos.x);
			calibration.y = Min(0.0, screen_base.y - drag_pos.y);
			//ClearPrint();
			//Print << screen.movedBy(pos).intersects(Cursor::PosF());
			//Print << RectF(icon_door.movedBy(pos + screen.pos - p->get_pos() + calibration), 30, 40).intersects(Cursor::PosF());
			if (screen.movedBy(pos).intersects(Cursor::PosF()) && RectF(icon_door.movedBy(pos + screen.pos - p->get_pos() + calibration), 30, 40).intersects(Cursor::PosF())) {
				// Cursor::RequestStyle(CursorStyle::Hand);
				// Cursor::RequestStyle(U"hand");
				GameControl::decorator.RequestStyle(U"hand");
				if (MouseL.down()) {
					manager.add_page(std::make_shared<Page_Door>(manager));
				}
			}
		}
	}
}

Page_MyriadTetrapod::Page_MyriadTetrapod(WindowSystemManager& manager)
	:WindowSystem(Vec2(0, 0), Size(500, 500), U"Myriad Tetrapod"),
	manager(manager),
	drag_pos(50, 200),
	screen_base(800, 500, 300, 300),
	screen(screen_base),
	item_num(50),
	icons_name(item_num),
	icons_pos(item_num)
{
	for (int i = 0; i < (int)icons_name.size(); ++i) {
		icons_name[i] = U"selfintroduction_" + Format(Random(0, 9));
		// icons_pos[i] = RandomVec2(RectF(Vec2::Zero(), Scene::Size()).stretched(-100));
		icons_pos[i] = RandomVec2(RectF(Vec2::Zero(), GameControl::base_size).stretched(-100));
	}
	// icon_door = RandomVec2(RectF(Vec2::Zero(), Scene::Size()).stretched(-50));
	icon_door = RandomVec2(RectF(Vec2::Zero(), GameControl::base_size).stretched(-50));
}
