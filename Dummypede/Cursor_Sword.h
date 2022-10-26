#pragma once
#include <Siv3d.hpp>
#include "CursorBase.h"

// カーソル剣
class CursorSword : public CursorBase {
private:
	Vec2 dir = Vec2(0, 1);
	double length = 140;

public:
	CursorSword();

	void Draw() const override;
	void Update() override;

	Line get_hitbox() const;
};

