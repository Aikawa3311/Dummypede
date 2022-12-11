// Pageのテンプレート
#pragma once
#include "WindowSystem.h"
// ★ここに必要なものをinclude


class Page_Evnnzqfef20 : public WindowSystem {
private:
	void Draw() const override;

	void Update() override;

	Array<String> users_text;
	Array<String> genius_text;
	Array<String> whole_text;

	void set_texts();

	int user_text_num = 0;
	int user_text_seek = 0;
	int genius_text_num = 0;
	int genius_text_seek = 0;

	double const input_lag_start = 0.3;
	double const input_lag_continue = 0.1;
	bool input_start = false;

	Stopwatch genius_text_timer;
	Stopwatch input_timer;
	Stopwatch input_lag;	// 立ち上げ時の入力ラグ

	// 0でuser側・1でgenius側
	bool turn = 0;

	void turn_change();

public:
	Page_Evnnzqfef20();
};
