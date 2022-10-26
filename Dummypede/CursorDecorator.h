#pragma once
#include <Siv3D.hpp>
#include "CursorBase.h"
#include "Cursor_Sword.h"

class CursorSword;

// カーソルに効果を付加する
class CursorDecorator{
private:
	// 通常(Styleの適用)・鍵・剣
	static int cursor_state;
	// スタイル(-1:hidden 0:normal 1:hand 2:grab1 3:grab2)
	static int cursor_style;
	// カーソルに適用されてるアイコン
	std::shared_ptr<CursorBase> item;
	std::weak_ptr<CursorSword> sword;

public:
	void Update();
	void Draw() const;

	// カーソルのDraw
	void DrawCursor() const;

	// カーソルスタイルの変更
	void RequestStyle(String const str);

	// 現在カーソルに着けているものを外す
	void unset();

	// 剣をセット
	void set_sword();

	// swordを取得
	std::weak_ptr<CursorSword> & get_sword();

	// カーソルの状態を取得
	int get_cursor_state() const;
};

