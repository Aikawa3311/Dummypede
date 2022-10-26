#include "stdafx.h"
#include "Page_DarkPage5.h"

void Page_DarkPage5::DrawDark() const {
	FontAsset(U"HugeLucida")(U"1").drawAt((size / 2).movedBy(0, 10), Palette::Black);
}


Page_DarkPage5::Page_DarkPage5(WindowSystemManager& manager, Vec2 const& pos)
	:Page_DarkPageBase(manager, pos, U".n")
{
}
