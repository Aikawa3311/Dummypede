#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"

#include "WindowSystemManager.h"

class Page_DarkPageBase : public WindowSystem {
private:
	WindowSystemManager& manager;

	void Draw() const override;
	void Update() override;

	// 暗闇の中に描画する内容(黒限定)
	virtual void DrawDark() const;

public:
	Page_DarkPageBase(WindowSystemManager & manager, Vec2 const & pos, String const & str);
};

