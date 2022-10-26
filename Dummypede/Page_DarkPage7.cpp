#include "stdafx.h"
#include "Page_DarkPage7.h"

void Page_DarkPage7::DrawDark() const{
	FontAsset(U"HugeLucida")(U"9").drawAt((size / 2).movedBy(0, 10), Palette::Black);
}

Page_DarkPage7::Page_DarkPage7(WindowSystemManager& manager, Vec2 const& pos)
	:Page_DarkPageBase(manager, pos, U"ad")
{
}
