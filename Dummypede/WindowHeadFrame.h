#pragma once
#include <Siv3D.hpp>

class WindowHeadFrame {
private:
	RectF frame;
	RectF close_button;
	Color frame_col;
	Color frame_col2;
	bool flag_erasable;

public:
	WindowHeadFrame(Vec2 const& pos, Size const& size);

	void Draw() const;

	void moveBy(Vec2 const& v);

	RectF const& get_frame() const;
	RectF const& get_close_button() const;
	void set_col(Color const c);
	void set_pos(Vec2 const& pos);
	void set_erasable(bool const b);

};

