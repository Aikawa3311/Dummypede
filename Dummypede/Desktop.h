#pragma once
#include <Siv3d.hpp>
#include "WindowSystemManager.h"

#include "Page_OnlyOneWeb.h"
#include "Page_404.h"

// デスクトップアイコン
class DesktopIcon {
protected:
	String asset_name;	// アセット名
	String name;		// 表示名
	WindowSystemManager & manager;
	Vec2 pos;

public:
	DesktopIcon(WindowSystemManager & manager, Vec2 const& pos);

	void Update() {}
	void Draw() const;

	Vec2 get_pos() const;
};

// デスクトップ
class Desktop{
private:
	// Array<DesktopIcon> icons;
	int icon_num;	// 現在のアイコン数、各アイコンは処理を番号と紐づける
	WindowSystemManager & manager;
	Color col_bg;
	String texture_bg;

	// 描画・位置関連
	Vec2 icon_base = Vec2(40, 40);		// アイコンの基本描画位置(中心)
	Vec2 icon_margin = Vec2(20, 30);	// アイコン同士の間隔

	// idx番目のアイコンの矩形領域を生成
	RectF rect_icon(int const idx) const;

public:
	Desktop(WindowSystemManager& manager);

	void Update();
	void Draw() const;

	// idx番目のアイコンを描画
	void draw_icon(int const idx) const;

	// アイコン数のセット
	void set_icon_num(int const num);
};

