// Pageのテンプレート
#pragma once
#include "WindowSystem.h"
#include "WindowSystemManager.h"

#include "Page_CentipedeGame.h"

class WindowSystemManager;

class Page_Myriapod : public WindowSystem {
private:
	WindowSystemManager& manager;
	Size file_size;
	Grid<bool> files;

	void Draw() const override;
	void Update() override;

public:
	Page_Myriapod(WindowSystemManager& manager);
};
