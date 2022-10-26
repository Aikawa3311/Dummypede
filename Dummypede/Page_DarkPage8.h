#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"
#include "Page_DarkPageBase.h"

// te
class Page_DarkPage8 : public Page_DarkPageBase {
private:
	void DrawDark() const override;

public:
	Page_DarkPage8(WindowSystemManager& manager, Vec2 const& pos);
};

