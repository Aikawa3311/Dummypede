#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"
#include "Page_DarkPageBase.h"

// od
class Page_DarkPage4 : public Page_DarkPageBase {
private:
	void DrawDark() const override;

public:
	Page_DarkPage4(WindowSystemManager& manager, Vec2 const& pos);
};

