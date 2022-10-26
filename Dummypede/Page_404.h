// Pageのテンプレート
#pragma once
#include "WindowSystem.h"

class Page_404 : public WindowSystem {
private:
	void Draw() const override;
	void Update() override;

public:
	Page_404(Vec2 const & pos = Vec2(250, 150));
};
