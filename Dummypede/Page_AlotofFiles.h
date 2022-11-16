// 新 -> Page_Myriapodへ

// Pageのテンプレート
#pragma once
#include "WindowSystem.h"
#include "WindowSystemManager.h"

#include "Page_CentipedeGame.h"

class WindowSystemManager;

class Page_AlotofFiles : public WindowSystem {
private:
	WindowSystemManager & manager;
	Size file_size;
	Grid<bool> files;

	void Draw() const override;
	void Update() override;

public:
	Page_AlotofFiles(WindowSystemManager & manager);
};
