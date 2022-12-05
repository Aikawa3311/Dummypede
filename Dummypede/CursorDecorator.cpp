#include "stdafx.h"
#include "CursorDecorator.h"

int CursorDecorator::cursor_state = 0;
int CursorDecorator::cursor_style = 0;

void CursorDecorator::Update(){
	// cursor_stateが0でない場合カーソルを消す
	// (現在常時Hidden状態なので特に必要なし)
	if (cursor_state != 0) {
		// Cursor::RequestStyle(CursorStyle::Hidden);
	}

	if (item) {
		item->Update();
	}
}

void CursorDecorator::Draw() const{
	if (item) {
		item->Draw();
	}
}

void CursorDecorator::DrawCursor() const{
	if (cursor_state != 0) return;

	// cursor_styleに合わせてcursor画像を描画
	// cursorの描画位置はカーソル位置に依存しているが、Transformer2Dでカーソル位置を変換しているため描画はズレない
	switch (cursor_style) {
	case 0:
		TextureAsset(U"cursor_normal").draw(Cursor::PosF());
		break;
	case 1:
		TextureAsset(U"cursor_hand").draw(Cursor::PosF().movedBy(-5, 0));
		break;
	case 2:
		TextureAsset(U"cursor_grab1").draw(Cursor::PosF().movedBy(-5, -5));
		break;
	case 3:
		TextureAsset(U"cursor_grab2").draw(Cursor::PosF().movedBy(-5, -5));
		break;
	case 4:
		TextureAsset(U"cursor_i").draw(Cursor::PosF().movedBy(0, -7));
		break;
	}
}

void CursorDecorator::RequestStyle(String const str){
	if (str == U"normal") {
		cursor_style = 0;
	}
	else if (str == U"hand") {
		cursor_style = 1;
	}
	else if (str == U"grab1") {
		cursor_style = 2;
	}
	else if (str == U"grab2") {
		cursor_style = 3;
	}
	else if (str == U"i") {
		cursor_style = 4;
	}
	else if (str == U"hidden") {
		cursor_style = -1;
	}
}

void CursorDecorator::unset(){
	item.reset();
	cursor_state = 0;
}

void CursorDecorator::set_sword(){
	std::shared_ptr<CursorSword> s = std::make_shared<CursorSword>();
	item = s;
	sword = s;
	s.reset();
	cursor_state = 2;
}

std::weak_ptr<CursorSword>& CursorDecorator::get_sword(){
	return sword;
}

int CursorDecorator::get_cursor_state() const{
	return cursor_state;
}
