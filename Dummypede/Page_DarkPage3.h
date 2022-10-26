#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"
#include "Page_DarkPageBase.h"

// ap
class Page_DarkPage3 : public Page_DarkPageBase {
private:
	void DrawDark() const override;

public:
	Page_DarkPage3(WindowSystemManager& manager, Vec2 const& pos);
};

