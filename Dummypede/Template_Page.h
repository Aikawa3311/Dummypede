// Pageのテンプレート
#pragma once
#include "WindowSystem.h"
// ★ここに必要なものをinclude


class Page1 : public WindowSystem {
private:
	void Draw() const override;

	void Update() override;

public:
	Page1() : WindowSystem(Vec2(300, 100), Size(300, 300), U"page1") {
	}


};
