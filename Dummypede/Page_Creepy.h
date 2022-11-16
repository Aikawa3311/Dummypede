#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"

class Page_Creepy : public WindowSystem {
private:
	void Draw() const override;
	void Update() override;

public:
	Page_Creepy();
};

