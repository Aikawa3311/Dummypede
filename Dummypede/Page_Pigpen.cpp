#include "stdafx.h"
#include "Page_Pigpen.h"

void Page_Pigpen::Draw() const{
	RectF(Vec2::Zero(), size).draw(Palette::Lightgoldenrodyellow);
	FontAsset(U"HugeLucida")(U"Pigpen\n   Cipher").draw(Vec2::Zero().movedBy(10, 40), Palette::Black);
	TextureAsset(U"Pigpen").resized(Vec2(400, 400)).draw(Vec2(200, 200));
}

void Page_Pigpen::Update(){


}

Page_Pigpen::Page_Pigpen()
	:WindowSystem(Vec2::Zero(), Size(600, 600), U"Pigpen Cipher"){
}
