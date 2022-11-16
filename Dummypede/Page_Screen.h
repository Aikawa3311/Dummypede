#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"

class Page_Screen : public WindowSystem {
private:
	int spd;
	Vec2 dir;
	Color col;

	void Draw() const override;
	void Update() override;

public:
	Page_Screen();

	Color get_color() const;
};

