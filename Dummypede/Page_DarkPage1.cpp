#include "stdafx.h"
#include "Page_DarkPage1.h"

void Page_DarkPage1::DrawDark() const {
	FontAsset(U"HugeLucida")(U"1").drawAt((size / 2).movedBy(0, 10), Palette::Black);
	FontAsset(U"SmallMintyo")(U"Password begin").drawAt((size / 2).movedBy(0, 46), Palette::Black);
}


Page_DarkPage1::Page_DarkPage1(WindowSystemManager& manager, Vec2 const & pos)
	:Page_DarkPageBase(manager, pos, U"my")
{
}
