#include "stdafx.h"
#include "WindowHeadFrame.h"

WindowHeadFrame::WindowHeadFrame(Vec2 const& pos, Size const& size)
	: frame(pos, size),
	close_button(pos.movedBy(size.x - 26, 5), Size(22, 22)),
	frame_col(Palette::Blue),
	frame_col2(Palette::Dodgerblue.lerp(Palette::Blue, 0.2)),
	flag_erasable(true){

}

void WindowHeadFrame::Draw() const {
	frame.draw(Arg::left = frame_col, Arg::right = frame_col2);
	if (flag_erasable) {
		RoundRect(close_button, 2).drawFrame(2, Palette::Red.lerp(Palette::White, 0.7));
		RoundRect(close_button, 2).draw(Palette::Red);
		// close_button.draw(Palette::Red);
		// TextureAsset(U"close").draw(close_button.pos.movedBy(3.5, 4), Palette::Red.lerp(Palette::White, 0.9));
		// FontAsset(U"Regular")(U"×").draw(close_button.pos.movedBy(4.5, -5), Palette::Red.lerp(Palette::White, 0.9));
		Line(Vec2(close_button.pos.movedBy(6, 6)), Vec2(close_button.pos.movedBy(16, 16))).draw(2, Palette::Red.lerp(Palette::White, 0.9));
		Line(Vec2(close_button.pos.movedBy(16, 6)), Vec2(close_button.pos.movedBy(6, 16))).draw(2, Palette::Red.lerp(Palette::White, 0.9));
	}
}

void WindowHeadFrame::moveBy(Vec2 const& v) {
	frame.moveBy(v);
	close_button.moveBy(v);
}

RectF const& WindowHeadFrame::get_frame() const {
	return frame;
}

RectF const& WindowHeadFrame::get_close_button() const {
	return close_button;
}

void WindowHeadFrame::set_col(Color const c) {
	frame_col = c;
}

void WindowHeadFrame::set_pos(Vec2 const& pos) {
	frame.setPos(pos);
	close_button.setPos(pos.movedBy(frame.w - 25, 5));
}

void WindowHeadFrame::set_erasable(bool const b){
	flag_erasable = b;
}

