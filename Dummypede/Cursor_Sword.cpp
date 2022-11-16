#include "stdafx.h"
#include "Cursor_Sword.h"

CursorSword::CursorSword(){
}

void CursorSword::Draw() const{
	TextureAsset(U"Sword").rotatedAt(Vec2(20, 140), dir.getAngle()).draw(Cursor::PosF().movedBy(-20, -140));
	// Line(Cursor::PosF(), Cursor::PosF() + dir * length).draw(Palette::White);
}

void CursorSword::Update(){
	if (Cursor::Pos() == Cursor::PreviousPos()) return;
	if (!MouseL.pressed()) {
		dir = dir.lerp((Cursor::PosF() - Cursor::PreviousPosF()).normalized(), 0.2).normalize();
	}
}

Line CursorSword::get_hitbox() const{
	return Line(Cursor::PosF(), Cursor::PosF() + dir * length);
}
