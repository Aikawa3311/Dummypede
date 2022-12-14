#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"
#include "Page_DarkPageBase.h"

// tr
class Page_DarkPage9 : public Page_DarkPageBase {
private:
	void DrawDark() const override;

public:
	Page_DarkPage9(WindowSystemManager& manager, Vec2 const& pos);
};

