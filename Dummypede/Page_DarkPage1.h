#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"
#include "WindowSystemManager.h"
#include "Page_DarkPageBase.h"

// my
class Page_DarkPage1 : public Page_DarkPageBase {
private:
	void DrawDark() const override;

public:
	Page_DarkPage1(WindowSystemManager & manager, Vec2 const & pos);
};

