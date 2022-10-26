// Pageのテンプレート
#pragma once
#include "WindowSystem.h"
#include "WindowSystemManager.h"

#include "Page_Screen.h"
#include "Page_Door.h"

class Page_MyriadTetrapod : public WindowSystem {
private:
	WindowSystemManager& manager;
	Vec2 drag_pos;
	RectF screen_base;
	RectF screen;

	int item_num;
	Array<String> icons_name;
	Array<Vec2> icons_pos;
	Vec2 icon_door;

	void Draw() const override;
	void Update() override;

public:
	Page_MyriadTetrapod(WindowSystemManager & manager);
};
