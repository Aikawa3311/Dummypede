#include "stdafx.h"
#include "Page_Evnnzqfef20.h"

void Page_Evnnzqfef20::Draw() const
{
	RectF(Vec2::Zero(), size).draw(Palette::Darkblue);
	// テキストを下から描画
	double drawpos_y = size.y - 30;
	for (int i = 0; i < (int)whole_text.size(); ++i) {
		bool tmp_turn = (whole_text.size() + i + 1) % 2;
		double wobble = i == 0 ? (Periodic::Sine0_1(1s) - 0.5) * 4 : 0;
		if (tmp_turn) {
			Vec2 drawpos = Vec2(30, drawpos_y);
			FontAsset(U"RegularConsol")(whole_text[i]).draw(Arg::bottomLeft = drawpos, Palette::White);
			// FontAsset(U"RegularConsol")(whole_text[i]).region(Arg::bottomLeft = drawpos).stretched(10).drawFrame(3, Palette::White);
			Shape2D::RectBalloon(FontAsset(U"RegularConsol")(whole_text[i]).region(Arg::bottomLeft = drawpos).stretched(10 + wobble), drawpos.movedBy(0, 25)).drawFrame(3, Palette::White);
		}
		else {
			Vec2 drawpos = Vec2(size.x - 30, drawpos_y);
			FontAsset(U"RegularConsol")(whole_text[i]).draw(Arg::bottomRight = drawpos, Palette::White);
			// FontAsset(U"RegularConsol")(whole_text[i]).region(Arg::bottomRight = drawpos).stretched(10).drawFrame(3, Palette::White);
			Shape2D::RectBalloon(FontAsset(U"RegularConsol")(whole_text[i]).region(Arg::bottomRight = drawpos).stretched(10 + wobble), drawpos.movedBy(0, 25)).drawFrame(3, Palette::White);
		}
		drawpos_y -= FontAsset(U"RegularConsol")(whole_text[i]).region().h + 50;
	}
	FontAsset(U"RegularConsol")(U"-Input text and press enter to send message-").drawAt(size.x / 2, drawpos_y, Palette::White);
}

void Page_Evnnzqfef20::Update()
{
	if (!active) return;

	// textが全て出たら処理を止める
	if (genius_text_num >= (int)genius_text.size()) {
		return;
	}

	// input_lagを止める
	if (input_lag.sF() > 0.5) {
		input_lag.reset();
	}

	if (turn == 0) {
		// user側
		// input_timerの制御
		if (input_timer.sF() > 0.1) {
			input_timer.reset();
		}

		// textの更新
		if (!Keyboard::GetAllInputs().isEmpty() && !input_lag.isRunning()) {
			if (KeyEnter.pressed()) {
				if (user_text_seek >= users_text[user_text_num].length()) {
					// text送り
					AudioAsset(U"cancel").playOneShot(0.9);
					++user_text_num;
					turn_change();
				}
			}
			else {
				if (!KeyEnter.up() && user_text_seek < users_text[user_text_num].length() && !input_timer.isRunning()) {
					++user_text_seek;
					whole_text.front() = users_text[user_text_num].substr(0, user_text_seek);
					AudioAsset(U"type").playOneShot(0.7);
					input_timer.restart();
				}
			}
		}
	}
	else {
		// genius側
		if (!genius_text_timer.isRunning() && genius_text_seek < genius_text[genius_text_num].length()) {
			// 文字タイマーの起動
			genius_text_timer.restart();
		}
		if (genius_text_timer.sF() > 0.02) {
			// textの更新
			if (genius_text_seek < genius_text[genius_text_num].length()) {
				++genius_text_seek;
				whole_text.front() = genius_text[genius_text_num].substr(0, genius_text_seek);
				genius_text_timer.restart();
				AudioAsset(U"message").playOneShot(Random(0.7, 0.9));
			}
			else {
				// text送り
				AudioAsset(U"cancel").playOneShot(0.9);
				++genius_text_num;
				turn_change();
			}
		}
	}
}

void Page_Evnnzqfef20::set_texts(){
	users_text.emplace_back(U"Hello chat");
	users_text.emplace_back(U"What does \"evnnzqfef20\" mean?");
	genius_text.emplace_back(U"Hello I'm chatbot.\nAsk me anything.");
	genius_text.emplace_back(U"Sorry I don't know what about \"evnnzqfef20\".\nBut one famous website seems to know this word...");
}

void Page_Evnnzqfef20::turn_change()
{
	user_text_seek = 0;
	genius_text_seek = 0;
	if (genius_text_num < (int)genius_text.size()) {
		whole_text.push_front(U" ");
	}
	genius_text_timer.reset();
	turn ^= 1;
}

Page_Evnnzqfef20::Page_Evnnzqfef20()
	: WindowSystem(Vec2(160, 190), Size(600, 300), U"Genius chat")
{
	set_texts();
	whole_text.push_front(U" ");
	input_lag.restart();
}
