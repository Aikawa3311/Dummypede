#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"
#include "Page_DarkPageBase.h"

// ri
class Page_DarkPage2 : public Page_DarkPageBase {
private:
	void DrawDark() const override;

public:
	Page_DarkPage2(WindowSystemManager& manager, Vec2 const& pos);
};

