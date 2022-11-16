#include "stdafx.h"
#include "Page_CardkeyReader.h"

void Page_CardkeyReader::changestate_anim(){
	guage_timer.restart();
	state = 1;
	str = U"認証中";
	AudioAsset(U"scanning").setVolume(0.3);
	AudioAsset(U"scanning").play();
}

void Page_CardkeyReader::changestate_done(){
	guage_timer.pause();
	state = 2;
	AudioAsset(U"scanning").stop();
}

void Page_CardkeyReader::changestate_idle(){
	state = 0;
}

double Page_CardkeyReader::sync_anim_function(int const i) const{
	double thr = anim_timer.sF() * reader.w / 3;
	if (i > thr) return 0;
	return Max(0.0, (60 - (thr - i)) / 60.0);
}

void Page_CardkeyReader::Draw() const{
	RectF(Vec2::Zero(), size).draw(Palette::Black);
	RectF rect = reader.stretched(10);
	FontAsset(U"RegularDot")(str).drawAt((size/2).movedBy(0, 124), Palette::Green);
	Vec2 p0 = rect.pos, p1 = p0.movedBy(rect.w, 0), p2 = p0.movedBy(0, rect.h), p3 = p1.movedBy(0, rect.h);
	reader.drawFrame(3, Palette::Green);
	guage.drawFrame(3, Palette::Green);

	// click hereの文字
	if (state != 1) {
		FontAsset(U"RegularDot")(U"click here").drawAt((size / 2).movedBy(0, -20), Palette::Green);
	}

	// スキャン風のエフェクト
	for (int i = 0; i < reader.w; ++i) {
		Line(reader.x + i, reader.y, reader.x + i, reader.y + reader.h).draw(ColorF(1, 1, 1, sync_anim_function(i)));
	}

	reader.drawFrame(3, Palette::Green);
	guage.drawFrame(3, Palette::Green);

	// 枠の描画
	Line(p0, p0.movedBy( rect.w * 0.2,  0)).draw(3, Palette::Green);
	Line(p0, p0.movedBy( 0,  rect.h * 0.2)).draw(3, Palette::Green);
	Line(p1, p1.movedBy(-rect.w * 0.2,  0)).draw(3, Palette::Green);
	Line(p1, p1.movedBy( 0,  rect.h * 0.2)).draw(3, Palette::Green);
	Line(p2, p2.movedBy( rect.w * 0.2,  0)).draw(3, Palette::Green);
	Line(p2, p2.movedBy( 0, -rect.h * 0.2)).draw(3, Palette::Green);
	Line(p3, p3.movedBy(-rect.w * 0.2,  0)).draw(3, Palette::Green);
	Line(p3, p3.movedBy( 0, -rect.h * 0.2)).draw(3, Palette::Green);

	RectF(size.x / 2 - 90 + 5, size.y/2 + 75, (guage.w - 10) * (guage_timer.sF() / 2.0), guage.h - 10).draw(Palette::Green);

	if (state == 1) {
		// FontAsset(U"RegulardDot")(GameControl::cardkey_str()).drawAt((size).movedBy(0, -10), Palette::Green);
		FontAsset(U"RegularDot")(GameControl::cardkey_str()).drawAt((size/2).movedBy(0, -21), Palette::Green);
		// RectF(guage.stretched(-5 - guage.w * (1 - guage_timer.sF() / 2.0), -5)).draw(Palette::Green);
	}

	// スキャン風のエフェクト
	for (int i = 0; i < reader.w; ++i) {
		Line(reader.x + i, reader.y, reader.x + i, reader.y + reader.h).draw(ColorF(1, 1, 1, sync_anim_function(i)));
	}
}

void Page_CardkeyReader::Update(){
	if (anim_timer.s() > 4) {
		anim_timer.restart();
	}
	switch (state) {
	case 0:
		// カードキーの待機中
		if (!active) return;
		if (GameControl::flag_cardkey && reader.movedBy(pos).leftClicked()) {
			changestate_anim();
		}
		break;
	case 1:
		// カードキーアニメーション中
		if (guage_timer.sF() > 2) {
			changestate_done();
		}
		break;
	case 2:
		// 認証完了時ページジャンプ
		str = Format(GameControl::cardkey_date) + U":認証成功";
		if (GameControl::cardkey_date == U"2001/09/09") {
			manager.add_page(std::make_shared<Page_Numbers>());
		}
		else if (GameControl::cardkey_date == U"2000/01/01") {
			manager.add_page(std::make_shared<Page_Dark>(manager));
		}
		else if (GameControl::cardkey_date == U"2038/01/19") {
			manager.add_page(std::make_shared<Page_Dark2>(manager));
		}
		else if (GameControl::cardkey_date == U"1970/01/01") {
			manager.add_page(std::make_shared<Page_UnixClock>());
		}
		else {
			str = Format(GameControl::cardkey_date) + U":認証失敗";
			AudioAsset(U"cancel").playOneShot(0.9);
		}
		changestate_idle();
		break;
	}
	
	//if (GameControl::flag_cardkey && reader.movedBy(pos).leftClicked()) {
	//	// カードキーの文字列照合
	//	if (GameControl::cardkey_date == U"2001/09/09") {
	//		manager.add_page(std::make_shared<Page_Numbers>());
	//	}
	//	else if (GameControl::cardkey_date == U"2000/01/01") {
	//		manager.add_page(std::make_shared<Page_Dark>(manager));
	//	}
	//	else if (GameControl::cardkey_date == U"2038/01/19") {
	//		manager.add_page(std::make_shared<Page_Dark2>(manager));
	//	}
	//}
}

Page_CardkeyReader::Page_CardkeyReader(WindowSystemManager & manager)
	:WindowSystem(Vec2(50, 470), Size(300, 300), U"cardkey reader"),
	manager(manager),
	reader(size.x/2 - 90, size.y/2 - 80, 180, 120),
	guage(size.x / 2 - 90, size.y/2 + 70, 180, 30),
	state(0),
	str(U"待機中") {
	anim_timer.start();
}
