#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"
#include "Page_DarkPageBase.h"

// et
class Page_DarkPage6 : public Page_DarkPageBase {
private:
	void DrawDark() const override;

public:
	Page_DarkPage6(WindowSystemManager& manager, Vec2 const& pos);
};

