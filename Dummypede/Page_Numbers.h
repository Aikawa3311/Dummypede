#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"
#include "GameControl.h"

class Page_Numbers : public WindowSystem {
private:
	RectF rect;
	Texture const thinking_tex;

	void Draw() const override;
	void Update() override;

public:
	Page_Numbers();

};

