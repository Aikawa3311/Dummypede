#include "stdafx.h"
#include "Page_DarkPage4.h"

void Page_DarkPage4::DrawDark() const {
	FontAsset(U"HugeLucida")(U"7").drawAt((size / 2).movedBy(0, 10), Palette::Black);
}


Page_DarkPage4::Page_DarkPage4(WindowSystemManager& manager, Vec2 const& pos)
	:Page_DarkPageBase(manager, pos, U"od")
{
}
