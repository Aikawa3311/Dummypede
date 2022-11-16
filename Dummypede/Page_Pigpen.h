// Pageのテンプレート
#pragma once
#include "WindowSystem.h"
#include "Centipede.h"

class Page_Pigpen : public WindowSystem {
private:
	void Draw() const override;
	void Update() override;

public:
	Page_Pigpen();
};
