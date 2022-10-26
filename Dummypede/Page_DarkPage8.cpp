#include "stdafx.h"
#include "Page_DarkPage8.h"

void Page_DarkPage8::DrawDark() const {
	FontAsset(U"HugeLucida")(U"5").drawAt((size / 2).movedBy(0, 10), Palette::Black);
}

Page_DarkPage8::Page_DarkPage8(WindowSystemManager& manager, Vec2 const& pos)
	:Page_DarkPageBase(manager, pos, U"te")
{
}
