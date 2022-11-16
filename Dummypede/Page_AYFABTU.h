// Pageのテンプレート
#pragma once
#include "WindowSystem.h"
// ★ここに必要なものをinclude


class Page_AYFABTU : public WindowSystem {
private:
	void Draw() const override;

	void Update() override;

public:
	Page_AYFABTU();
};
