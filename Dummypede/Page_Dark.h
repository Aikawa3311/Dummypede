#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"
#include "GameControl.h"
#include "WindowSystemManager.h"

#include "Page_DarkPage1.h"
#include "Page_DarkPage2.h"
#include "Page_DarkPage3.h"
#include "Page_DarkPage4.h"
#include "Page_DarkPage5.h"
#include "Page_DarkPage6.h"

class Page_Dark : public WindowSystem {
private:
	WindowSystemManager& manager;
	Array<Circle> links;
	Array<Color> cols;
	Array<Vec2> positions;

	void Draw() const override;
	void Update() override;

public:
	Page_Dark(WindowSystemManager& manager);
};

