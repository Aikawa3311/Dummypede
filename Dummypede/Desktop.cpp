#include "stdafx.h"
#include "Desktop.h"

// --------------------------------------------
// DesktopIcon
// --------------------------------------------

DesktopIcon::DesktopIcon(WindowSystemManager& manager, Vec2 const& pos)
	: manager(manager),
	pos(pos){
}

void DesktopIcon::Draw() const{
	TextureAsset(asset_name).draw(pos);
	FontAsset(U"SmallDotBold")(name).draw(pos.movedBy(0, 30));
}

Vec2 DesktopIcon::get_pos() const{
	return pos;
}

// --------------------------------------------
// Desktop
// --------------------------------------------

Desktop::Desktop(WindowSystemManager& manager)
	: manager(manager),
	icon_num(1),
	col_bg(Palette::Cadetblue){
}

void Desktop::Update() {
	// デスクトップ上で左クリックされたかどうかを判定する
	if (MouseL.down() && !manager.exist_window_at(Cursor::PosF())) {
		// 各アイコンと衝突判定を行う
		/*for (auto& i : icons) {
			if (!RectF(i.get_pos(), Size(30, 30)).intersects(Cursor::PosF())) continue;
			i.reaction();
			break;
		}*/
		for (int i = 0; i < icon_num; ++i) {
			if (!rect_icon(i).intersects(Cursor::PosF())) continue;
			// アイコンがクリックされていた場合は処理
			switch (i) {
			case 0:
				// Only 1 Web
				manager.add_page(std::make_shared<Page_OnlyOneWeb>(manager));
				break;
			}
			break;
		}
	}
}

void Desktop::Draw() const{
	// 背景色
	Scene::Rect().draw(col_bg);
	for (int i = 0; i < icon_num; ++i) {
		draw_icon(i);
	}
}

RectF Desktop::rect_icon(int const idx) const {
	return RectF(icon_base.movedBy(-20, idx * (icon_margin.y + 40) - 20), Size(40, 40));
}

void Desktop::draw_icon(int const idx) const{
	String asset_name;
	String name;
	switch (idx) {
	case 0:
		// Only 1 Web
		asset_name = U"Only1Web";
		name = U"o1w";
		break;
	}
	Vec2 draw_pos = icon_base.movedBy(0, idx * (icon_margin.y + 40));
	TextureAsset(asset_name).drawAt(draw_pos, Palette::Darkblue);
	FontAsset(U"SmallDotBold")(name).drawAt(draw_pos.movedBy(0, 30));
}

void Desktop::set_icon_num(int const num){
	icon_num = num;
}

