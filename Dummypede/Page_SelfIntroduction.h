// Pageのテンプレート
#pragma once
#include "WindowSystem.h"

#include "WindowSystemManager.h"
#include "Page_MukadeShell.h"
#include "Page_SelfIntroductionImage.h"

class Page_SelfIntroduction : public WindowSystem {
private:
	WindowSystemManager& manager;

	String name_column, name;
	String twitter_column, twitter_name;
	String youtube_column, youtube_name;

	void Draw() const override;
	void Update() override;

	// 任意ケタの数字を文字列として生成
	String random_digit_str(int const digit);

public:
	Page_SelfIntroduction(WindowSystemManager & manager);
};
