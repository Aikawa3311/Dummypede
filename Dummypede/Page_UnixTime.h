// Pageのテンプレート
#pragma once
#include "WindowSystem.h"

class Page_UnixTime : public WindowSystem {
private:
	void Draw() const override;
	void Update() override;

	DateTime time;

public:
	Page_UnixTime();
};
