#include "stdafx.h"
#include "Page_UnixTime.h"

void Page_UnixTime::Draw() const {
	RectF(Vec2::Zero(), size).draw(Palette::White);

	// ビット描画
	int32 bit = (int32)Time::GetSecSinceEpoch();
	double x_size = size.x / 32.0;
	for (int i = 0; i < 32; ++i) {
		if (i == 31) {
			RectF(Vec2(x_size * (32 - 1 - i), 0), Vec2(x_size, size.y)).draw(ColorF(0.7, 0.7, 1.0, 0.5));
			continue;
		}
		if ((bit & (0b1 << i)) == 0) continue;
		RectF(Vec2(x_size * (32 - 1 - i), 0), Vec2(x_size, size.y)).draw(ColorF(0.8, 0.8, 0.8, 0.5));
	}

	// 年月日
	String y = U"", mo = U"", d = U"";
	y = Format(time.year);
	if (time.month < 10) {
		mo = U"0";
	}
	mo += Format(time.month);
	if (time.day < 10) {
		d = U"0";
	}
	d += Format(time.day);

	FontAsset(U"SmallRegular")(U"{}/{}/{}"_fmt(y, mo, d)).draw(Arg::topLeft = Vec2(20, 35), Palette::Black);

	// 時間
	String h = U"", m = U"", s = U"";
	if (time.hour < 10) {
		h = U"0";
	}
	h += Format(time.hour);
	if (time.minute < 10) {
		m = U"0";
	}
	m += Format(time.minute);
	if (time.second < 10) {
		s = U"0";
	}
	s += Format(time.second);

	FontAsset(U"BigRegular")(U"{}:{}:{}"_fmt(h, m, s)).draw(Arg::center = Vec2(90, 75), Palette::Black);

	FontAsset(U"BigRegular")(U"{}"_fmt(Time::GetSecSinceEpoch())).draw(Arg::rightCenter = Vec2(380, 75), Palette::Black);
}

void Page_UnixTime::Update(){
	time = DateTime::Now();
}

Page_UnixTime::Page_UnixTime()
	:WindowSystem(Vec2(400, 300), Size(400, 100), U"UNIX time"),
	time(DateTime::Now()){
}
