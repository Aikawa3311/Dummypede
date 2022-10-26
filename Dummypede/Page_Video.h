#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"

class Page_Video : public WindowSystem {
private:
	VideoTexture const video;

	void Draw() const override;
	void Update() override;

public:
	Page_Video();

};

