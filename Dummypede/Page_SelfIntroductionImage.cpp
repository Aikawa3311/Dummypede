#include "stdafx.h"
#include "Page_SelfIntroductionImage.h"

void Page_SelfIntroductionImage::Draw() const{
	RectF(Vec2::Zero(), size).draw(Palette::Wheat);
	// elkの画像
	TextureAsset(U"elk").draw(Vec2(75, 45));

	RectF(Vec2::Zero(), size).draw(ColorF(0.1, 0.1, 0.1, 0.5));

	// 詳細
	FontAsset(U"SmallDot")(U"名前:elk_with_flower.jpg").draw(Arg::bottomRight = Vec2(240, 150), Palette::White);
	FontAsset(U"SmallDot")(U"撮影日時:2001/09/09").draw(Arg::bottomRight = Vec2(240, 170), Palette::White);
	FontAsset(U"SmallDot")(U"備考:パスコード備忘用").draw(Arg::bottomRight = Vec2(240, 190), Palette::White);
}

void Page_SelfIntroductionImage::Update(){
}

Page_SelfIntroductionImage::Page_SelfIntroductionImage()
	:WindowSystem(Vec2(500, 180), Size(250, 200), U"image"){
}
