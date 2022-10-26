// Pageのテンプレート
#pragma once
#include "WindowSystem.h"
#include "Centipede.h"

class Page_FeedFiles : public WindowSystem {
private:
	void Draw() const override;
	void Update() override;

	Centipede centipede;

public:
	Page_FeedFiles();
};
