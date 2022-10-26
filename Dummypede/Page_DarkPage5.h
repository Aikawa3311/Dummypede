#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"
#include "Page_DarkPageBase.h"

// .n
class Page_DarkPage5 : public Page_DarkPageBase {
private:
	void DrawDark() const override;

public:
	Page_DarkPage5(WindowSystemManager& manager, Vec2 const& pos);
};

