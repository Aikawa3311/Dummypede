#include "stdafx.h"
#include "Page_DarkPage2.h"

void Page_DarkPage2::DrawDark() const {
	FontAsset(U"HugeLucida")(U"9").drawAt((size / 2).movedBy(0, 10), Palette::Black);
}


Page_DarkPage2::Page_DarkPage2(WindowSystemManager& manager, Vec2 const& pos)
	:Page_DarkPageBase(manager, pos, U"ri")
{
}
