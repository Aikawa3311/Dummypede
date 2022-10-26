// Pageのテンプレート
#pragma once
#include "WindowSystem.h"
#include "GameControl.h"

class Page_ScoreServer : public WindowSystem {
private:
	void Draw() const override;
	void Update() override;

	Array < std::tuple<String, int, String> > players;

	void set_players();

public:
	Page_ScoreServer();
};
