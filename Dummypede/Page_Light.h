#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"
#include "GameControl.h"


class Page_Light : public WindowSystem {
private:
	void Draw()const override;
	void Update() override;

public:
	Page_Light();
};

