#include "stdafx.h"
#include "Page_Door.h"

int Page_Door::door_state = 0;

void Page_Door::Draw() const{
	// 背景
	RectF(Vec2::Zero(), size).draw(Palette::Black);
	// ドア
	if (door_state == 0) {
		TextureAsset(U"BigDoorClosed").drawAt((size / 2).movedBy(0, -20));
	}
	else if (door_state == 1) {
		TextureAsset(U"BigDoorOpen").drawAt((size / 2).movedBy(0, -20));
	}
	// テキストエリア
	textarea_rect.stretched(4).drawFrame(2, Palette::White);
	if (door_state == 0) {
		String const tmp_text = (textarea_active && state == 0) ? (text + U"|" + editing_text) : text;
		// FontAsset(U"RegularDot")(tmp_text).draw(textarea_rect, Palette::White);
		FontAsset(U"RegularDot")(tmp_text).drawAt(size.x/2, textarea_rect.y + textarea_rect.h/2 - 2, Palette::White);
	}
	else{
		// FontAsset(U"RegularDot")(U"centipede").draw(textarea_rect, Palette::White);
		FontAsset(U"RegularDot")(U"body").drawAt(size.x / 2, textarea_rect.y + textarea_rect.h / 2 - 2, Palette::White);
	}
}

void Page_Door::Update(){
	if (state == 1) {
		if (anim_timer.s() > 1) changestate_open();
	}

	if (!active) return;

	if (door_state == 1) {
		// ドアが開いている状態でクリック
		if (!GameControl::boss_win && RectF((size / 2).movedBy(-100, -120), Size(200, 200)).intersects(Cursor::PosF().movedBy(-pos))) {
			// Cursor::RequestStyle(CursorStyle::Hand);
			// Cursor::RequestStyle(U"hand");
			GameControl::decorator.RequestStyle(U"hand");
			if (MouseL.down()) {
				manager.add_page(std::make_shared<Page_Boss>(manager));
			}
		}
	}

	if (door_state == 1 || state != 0) return;
	// 長方形が押されたら入力状態をオンへ
	if (textarea_rect.movedBy(pos).intersects(Cursor::PosF())) {
		GameControl::decorator.RequestStyle(U"i");
	}
	if (MouseL.down()) {
		textarea_active = textarea_rect.movedBy(pos).intersects(Cursor::PosF());
	}
	// キーボード入力受け取り
	if (textarea_active) {
		if (!KeyEnter.pressed()) {
			// キー入力
			String tmp = text;
			TextInput::UpdateText(text);
			if (text != tmp) {
				AudioAsset(U"type").playOneShot(0.7);
			}
			editing_text = TextInput::GetEditingText();
			if (text.length() > 10) {
				text.pop_back();
			}
		}
		else if (editing_text == U"") {
			// エンターキー
			if (text.lowercased() == U"body") {
				changestate_wait();
			}
			else {
				AudioAsset(U"cancel").playOneShot(0.9);
				text = U"";
			}
		}
	}
}

Page_Door::Page_Door(WindowSystemManager& manager)
	: // WindowSystem(Scene::Size() / 2 - Size(400, 400) / 2, Size(400, 400), U"Door"),
	WindowSystem(GameControl::base_size/2 - Size(400, 400)/2, Size(400, 400), U"Door"),
	manager(manager),
	text(U""),
	editing_text(U""),
	textarea_rect((size/2).movedBy(-100, 130), Size(200, 30)),
	textarea_active(true),
	state(0)
	{
	// ドラッグできない
	set_draggable(false);
	// 既に剣を持っている場合は仕舞わせる
	GameControl::decorator.unset();
}

void Page_Door::changestate_wait(){
	state = 1;
	anim_timer.restart();
}

void Page_Door::changestate_open(){
	state = 2;
	door_state = 1;
	anim_timer.reset();
	AudioAsset(U"door_open").playOneShot();
}
