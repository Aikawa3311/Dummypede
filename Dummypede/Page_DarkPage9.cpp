#include "stdafx.h"
#include "Page_DarkPage9.h"

void Page_DarkPage9::DrawDark() const {
	FontAsset(U"HugeLucida")(U"0").drawAt((size / 2).movedBy(0, 10), Palette::Black);
}


Page_DarkPage9::Page_DarkPage9(WindowSystemManager& manager, Vec2 const& pos)
	:Page_DarkPageBase(manager, pos, U"tr")
{
}
