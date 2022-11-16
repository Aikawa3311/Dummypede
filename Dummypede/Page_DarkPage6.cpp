#include "stdafx.h"
#include "Page_DarkPage6.h"

void Page_DarkPage6::DrawDark() const {
	FontAsset(U"HugeLucida")(U"5").drawAt((size / 2).movedBy(0, 10), Palette::Black);
	FontAsset(U"SmallMintyo")(U"Password end").drawAt((size / 2).movedBy(0, 46), Palette::Black);
}

Page_DarkPage6::Page_DarkPage6(WindowSystemManager& manager, Vec2 const& pos)
	:Page_DarkPageBase(manager, pos, U"et")
{
}
