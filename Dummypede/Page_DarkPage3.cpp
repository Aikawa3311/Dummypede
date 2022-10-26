#include "stdafx.h"
#include "Page_DarkPage3.h"

void Page_DarkPage3::DrawDark() const {
	FontAsset(U"HugeLucida")(U"1").drawAt((size / 2).movedBy(0, 10), Palette::Black);
}


Page_DarkPage3::Page_DarkPage3(WindowSystemManager& manager, Vec2 const& pos)
	:Page_DarkPageBase(manager, pos, U"ap")
{
}
