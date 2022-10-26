#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"
#include "Page_DarkPageBase.h"

// ad
class Page_DarkPage7 : public Page_DarkPageBase {
private:
	void DrawDark() const override;

public:
	Page_DarkPage7(WindowSystemManager& manager, Vec2 const& pos);
};

