// Pageのテンプレート
#pragma once
#include "WindowSystem.h"
// ★ここに必要なものをinclude


class Page_LastPassword : public WindowSystem {
private:
	void Draw() const override;

	void Update() override;

public:
	Page_LastPassword();
};
