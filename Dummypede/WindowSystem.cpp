#include "stdafx.h"
#include "WindowSystem.h"

WindowSystem::WindowSystem(Vec2 const& pos_, Size const& size_, String const& title_)
	: title(title_),
	pos(pos_),
	size(size_),
	render_texture(size, Palette::White),
	frame_head(pos_, Size(size_.x, 30)),
	window_alpha(1.0)
{
	// Print << RectF(pos, Size(size.x, 20)) << U" " << frame_head;
}

void WindowSystem::Update() {}

void WindowSystem::Draw() const {}

void WindowSystem::DrawDepth2() const{}

void WindowSystem::DrawWindow() const{
	// ウィンドウ内容の描画
	{
		// ScopedRenderTarget2D const target(render_texture.clear(ColorF(1, 1, 1, window_alpha)));
		ScopedViewport2D const viewport(pos.asPoint(), size);
		Draw();
	}
	// render_texture.draw(pos);
	// フレーム(枠部分)の描画
	draw_frame();
}

void WindowSystem::UpdateWindow() {
	// ウィンドウの操作
	// ドラッグ操作(非アクティブ時は不可 = 重なっている場合は不可)
	if (dragging && active && draggable) {
		Vec2 d = Cursor::PosF() - Cursor::PreviousPosF();
		moveBy(d);
	}

	if (MouseL.down() && frame_head.get_frame().intersects(Cursor::PosF())) {
		dragging = true;
	}

	if (MouseL.up()) {
		dragging = false;
	}

	// ウィンドウの更新
	Update();
}

void WindowSystem::draw_frame() const {
	if (!active && light_focus) {
		const ScopedColorAdd2D colorAdd{ ColorF(0.4, 0.4, 0.4) };
		frame_head.Draw();
	}
	else {
		frame_head.Draw();
	}
	// FontAsset(U"WindowTitle")(title).draw(pos.movedBy(10, 2), RectF(pos, size.movedBy(-30, 0)));
	FontAsset(U"WindowTitle")(title).draw(RectF(pos.movedBy(10, 2), frame_head.get_frame().size.movedBy(-45, 0)));
	RectF(pos, size).drawFrame(2, Palette::Gray);
	RectF(pos.movedBy(0, frame_head.get_frame().h), SizeF(frame_head.get_frame().w, 2)).draw(Palette::Gray);
}

bool WindowSystem::close_button_down() const {
	if (active && erasable && frame_head.get_close_button().leftClicked()) {
		return true;
	}
	return false;
}

RectF WindowSystem::rect() const {
	return RectF(pos, size);
}

RectF WindowSystem::rect_without_head_frame() const{
	double h = frame_head.get_frame().h;
	return RectF(Vec2(pos.x, pos.y + h), SizeF(size.x, size.y - h));
}

void WindowSystem::moveBy(Vec2 const& v){
	set_pos(pos + v);
}

bool WindowSystem::get_focusable() const {
	return focusable;
}

bool WindowSystem::get_flag_erase() const {
	return flag_erase;
}

void WindowSystem::set_pos(Vec2 pos_){
	// 画面内に収まるようにする
	pos_.clamp(Rect(-size.x + 30, 0, size.x + Scene::Width() - 45, Scene::Height() - 10));
	pos = pos_;
	frame_head.set_pos(pos_);
}

void WindowSystem::set_draggable(bool const b) {
	draggable = b;
}

void WindowSystem::set_erasable(bool const b) {
	erasable = b;
	frame_head.set_erasable(b);
}

void WindowSystem::set_focusable(bool const b) {
	focusable = b;
}

void WindowSystem::set_flag_erase(bool const b) {
	flag_erase = b;
}

void WindowSystem::set_light_focus(bool const b) {
	light_focus = b;
}

//void WindowSystem::Update() {
//	for (auto& i : objects) {
//		i->Update();
//	}
//}

//void WindowSystem::Draw() const {
//	// 矩形領域描画
//	RectF(pos, size).drawFrame(2, Palette::White);
//
//	for (auto const & i : objects) {
//		i->Draw();
//	}
//}

//void WindowSystem::add_object(std::unique_ptr<GameObject> object) {
//	objects.push_back(object);
//}
