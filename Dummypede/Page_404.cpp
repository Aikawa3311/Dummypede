#include "stdafx.h"
#include "Page_404.h"

void Page_404::Draw() const{
	RectF(Vec2::Zero(), size).draw(Palette::White);
	FontAsset(U"HugeLucida")(U"404 Not Found").drawAt(Vec2(size.x / 2, 100), Palette::Black);
	Line(Vec2(20, 160), Vec2(size.x - 20, 160)).draw(2, Palette::Darkgray);
	FontAsset(U"RegularMintyo")(U"指定されたページが見つかりませんでした").drawAt(Vec2(size.x / 2, 200), Palette::Black);

	//FontAsset(U"HugeMintyo")(U"404 Not Found").drawAt(Vec2(size.x / 2, 80), Palette::Black);
	//FontAsset(U"BigMintyo")(U"指定されたページが見つかりませんでした").drawAt(Vec2(size.x / 2, 180), Palette::Black);
}

void Page_404::Update(){

}

Page_404::Page_404(Vec2 const & pos)
	: WindowSystem(pos, Size(700, 500), U"404"){
}
