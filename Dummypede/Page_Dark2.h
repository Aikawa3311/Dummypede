#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"
#include "GameControl.h"
#include "WindowSystemManager.h"

#include "Page_DarkPage7.h"
#include "Page_DarkPage8.h"
#include "Page_DarkPage9.h"
#include "Page_Sunset.h"

class Page_Dark2 : public WindowSystem {
private:
	WindowSystemManager& manager;
	Array<Circle> links;
	Array<Color> cols;
	Array<Vec2> positions;

	Rect link;

	void Draw() const override;
	void Update() override;

public:
	Page_Dark2(WindowSystemManager& manager);
};

