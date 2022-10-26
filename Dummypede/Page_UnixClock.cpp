#include "stdafx.h"
#include "Page_UnixClock.h"

void Page_UnixClock::Draw() const {
	// 背景
	RectF(Vec2::Zero(), size).draw(Palette::Lightskyblue);
	// 背景のbit表示
	int32 unix = calc_unix_time();
	Vec2 rec_size = Vec2(size.x / 8.0, size.y / 4.0);
	for (int i = 0; i < 32; ++i) {
		if ((unix & (1 << i)) == 0) continue;
		RectF(Vec2(rec_size.x * ((31 - i) % 8), rec_size.y * ((31 - i) / 8)), rec_size).draw((i == 31) ? ColorF{ Palette::Blue, 0.2 } : ColorF{ Palette::Gray, 0.2 });
		// RectF(Vec2(rec_size.x * (i % 8), rec_size.y * (i / 8)), rec_size).draw({ Palette::Gray, 0.5 });
	}

	// what is unix time? (+-6時間以内もしくは1000000000で出現)
	if ((2147483648 - Abs(unix) > 10 && 2147483648 - Abs(unix) < 21600) || unix == 1000000000) {
		FontAsset(U"Regular")(U"What is UNIX time?").draw(link_unix.pos, Palette::Blue);
	}

	// 枠
	circle.draw().drawFrame(10, Palette::Gray);

	// 端っこの区切り線
	for (auto i : Range(0, 59)){
		const Vec2 cpos = OffsetCircular{ circle.center, circle.r - 5, i * 6_deg };
		// Circle{ pos, (i % 5 ? 3 : 6) }.draw(ColorF{ 0.25 });
		Line(cpos, cpos.lerp(circle.center, i % 5 ? 0.04 : 0.1)).draw(5, Palette::Gray);
	}

	// 年針・月針・日針
	bool flag_grab = hands_grab.any([](bool const b) -> bool { return b == true; });
	bool flag_blue = false;
	for (int i = 0; i < (int)hands.size(); ++i) {
		if ( active && ((flag_grab && hands_grab[i]) || (!flag_grab && (!flag_blue && hands[i].stretched(10).intersects(Cursor::PosF().movedBy(-pos))))) ) {
			hands[i].draw(Palette::Skyblue);
			flag_blue = true;
		}
		else {
			hands[i].draw(ColorF(0.2));
		}
	}

	// 中心の時刻表記
	Color col = (unix == 2147483647 || unix == 1000000000) ? Palette::Goldenrod : Color(34, 187, 52);
	digital_frame.draw(Palette::Black);
	FontAsset(U"RegularDSEG")(U"8888888888").draw(digital_frame.rect.pos.movedBy(15, 5), { Palette::Gray, 0.5});
	String month = (datetime.month < 10 ? U"0" + Format(datetime.month) : Format(datetime.month));
	String day = (datetime.day < 10 ? U"0" + Format(datetime.day) : Format(datetime.day));
	FontAsset(U"RegularDSEG")(Format(datetime.year) + U"-" + month + U"-" + day).draw(digital_frame.rect.pos.movedBy(15, 5), col);

	FontAsset(U"RegularDSEG")(U"88:88:88").drawAt((size / 2).movedBy(0, -1), { Palette::Gray, 0.5 });
	String hour = (datetime.hour < 10 ? U"0" + Format(datetime.hour) : Format(datetime.hour));
	String minute = (datetime.minute < 10 ? U"0" + Format(datetime.minute) : Format(datetime.minute));
	String second = (datetime.second < 10 ? U"0" + Format(datetime.second) : Format(datetime.second));
	FontAsset(U"RegularDSEG")(hour + U":" + minute + U":" + second).drawAt((size / 2).movedBy(0, -1), col);

	FontAsset(U"RegularDSEG")(U"88888888888").draw(digital_frame.rect.pos.movedBy(5, 65), { Palette::Gray, 0.5 });
	String unix_str = Format(unix);
	while (unix_str.length() < 11) unix_str.push_front('!');
	FontAsset(U"RegularDSEG")(unix_str).draw(digital_frame.rect.pos.movedBy(5, 65), col);
}

void Page_UnixClock::Update() {
	if (!active) return;

	// カーソルをgrab1に変更
	if (hands_grab.all([](bool const b) -> bool { return b == false; })) {
		if (hands.any([&](Quad const& hand) -> bool { return hand.stretched(10).intersects(Cursor::PosF().movedBy(-pos)); })) {
			GameControl::decorator.RequestStyle(U"grab1");
		}
	}
	// カーソルgrab2に変更
	if (hands_grab.any([](bool const b) -> bool { return b == true; })) {
		GameControl::decorator.RequestStyle(U"grab2");
	}

	// 各針が掴まれたかどうかを判定
	grab_hand();

	// 各針のアングル変更
	update_hand_angle();

	// 角度から日付の計算
	calc_datetime_from_angle();

	// 針のquadを計算
	calc_hand_quad();

	// リンクの押下判定
	int32 unix_time = calc_unix_time();
	if ((2147483648 - Abs(unix_time) > 10 && 2147483648 - Abs(unix_time) < 21600) || unix_time == 1000000000) {
		if (link_unix.movedBy(pos).intersects(Cursor::PosF())) {
			GameControl::decorator.RequestStyle(U"hand");
			if (MouseL.down()) {
				// SimpleHTTP::
				AudioAsset(U"enter").playOneShot(0.7);
				System::LaunchBrowser(U"https://ja.wikipedia.org/wiki/UNIX%E6%99%82%E9%96%93");
			}
		}
	}
}

int32 Page_UnixClock::calc_unix_time() const{
	return static_cast<int32>( ( DurationCast<Seconds>(DateTime::Subtract(datetime, DateTime(Date(1970, 1, 1), 9))) ).count() );
}

void Page_UnixClock::calc_hand_quad(){
	hands[0] = RectF((size / 2).movedBy(-9, -150), Size(18, 160)).rotatedAt(size / 2, hands_angle[0]);
	hands[1] = RectF((size / 2).movedBy(-6, -160), Size(12, 180)).rotatedAt(size / 2, hands_angle[1]);
	hands[2] = RectF((size / 2).movedBy(-4, -170), Size(8, 200)).rotatedAt(size / 2, hands_angle[2]);
	hands[3] = RectF((size / 2).movedBy(-2, -180), Size(4, 220)).rotatedAt(size / 2, hands_angle[3]);
	hands[4] = RectF((size / 2).movedBy(-2, -190), Size(4, 240)).rotatedAt(size / 2, hands_angle[4]);
	hands[5] = RectF((size / 2).movedBy(-2, -200), Size(4, 260)).rotatedAt(size / 2, hands_angle[5]);
}

void Page_UnixClock::calc_datetime_from_angle(){
	int daysinmonth = Date::DaysInMonth(datetime.year, datetime.month);
	int y = year_range.first + (int)(hands_angle[0] * (year_range.second - year_range.first) / Math::TwoPi);
	int m = Min(12, 1 + (int)(hands_angle[1] * 12.0 / Math::TwoPi));
	int d = Min(daysinmonth, 1 + (int)(hands_angle[2] * (daysinmonth) / Math::TwoPi));
	datetime.year = y;
	datetime.month = m;
	datetime.day = d;

	int h = Min(23, (int)(hands_angle[3] * 24.0 / Math::TwoPi));
	int mi = Min(59, (int)(hands_angle[4] * 60.0 / Math::TwoPi));
	int s = Min(59, (int)(hands_angle[5] * 60.0 / Math::TwoPi));
	datetime.hour = h;
	datetime.minute = mi;
	datetime.second = s;
}

void Page_UnixClock::grab_hand(){
	// まだつかんでいない場合は各種判定
	if (hands_grab.all([](bool const b) -> bool { return b == false; })) {
		for (int i = 0; i < (int)hands.size(); ++i) {
			if (hands[i].stretched(10).intersects(Cursor::PosF().movedBy(-pos)) &&
			MouseL.down()) {
				hands_grab[i] = true;
				break;
			}
		}
	}

	// マウスがリリースされたらフラグをもとに戻す
	if (MouseL.up()) {
		hands_grab.fill(false);
	}
}

void Page_UnixClock::update_hand_angle(){
	// 針の角度変更
	for (int i = 0; i < (int)hands.size(); ++i) {
		if (hands_grab[i]) {
			hands_angle[i] = OffsetCircular(size / 2, Cursor::PosF().movedBy(-pos)).theta;
			if (hands_angle[i] < 0) {
				hands_angle[i] = Math::TwoPi + hands_angle[i];
			}
		}
	}
}

Page_UnixClock::Page_UnixClock()
	:WindowSystem(Vec2(300, 100), Size(600, 600), U"UNIX clock"),
	datetime(DateTime::Now()),
	// datetime(2038, 1, 19, 12, 14, 7),
	circle(size/2, 250),
	hands(6),
	hands_angle(6, 0),
	hands_grab(6, false),
	digital_frame((size / 2).movedBy(-130, -50), Vec2(260, 100), 6),
	link_unix(Vec2(10, size.y - 30), Size(200, 25)),
	year_range(1970, 2050){
	hands_angle[0] = ((double)(datetime.year - year_range.first) / (year_range.second - year_range.first) * Math::TwoPi);
	hands_angle[1] = ((double)(datetime.month - 1) / 12 * Math::TwoPi) + 1e-9;
	hands_angle[2] = ((double)(datetime.day - 1) / Date::DaysInMonth(datetime.year, datetime.month) * Math::TwoPi) + 1e-9;
	hands_angle[3] = ((double)(datetime.hour) / 24 * Math::TwoPi);
	hands_angle[4] = ((double)(datetime.minute) / 60 * Math::TwoPi);
	hands_angle[5] = ((double)(datetime.second) / 60 * Math::TwoPi);
}

#if 0
#include "stdafx.h"
#include "Page_UnixClock.h"

void Page_UnixClock::Draw() const {
	RectF(Vec2::Zero(), size).draw(Palette::Lightskyblue);
	// 枠
	circle.draw().drawFrame(10, Palette::Gray);

	// 端っこの区切り線
	for (auto i : Range(0, 59)) {
		const Vec2 cpos = OffsetCircular{ circle.center, circle.r - 5, i * 6_deg };
		// Circle{ pos, (i % 5 ? 3 : 6) }.draw(ColorF{ 0.25 });
		Line(cpos, cpos.lerp(circle.center, i % 5 ? 0.04 : 0.1)).draw(5, Palette::Gray);
	}

	// 年針・月針・日針
	year_hand.draw(ColorF(0.2));
	month_hand.draw(ColorF(0.2));
	day_hand.draw(ColorF(0.2));
}

void Page_UnixClock::Update() {
	if (!active) return;

	// カーソルをgrab1に変更
	if (!flag_year_hand && !flag_month_hand && !flag_day_hand) {
		if (year_hand.stretched(10).intersects(Cursor::PosF().movedBy(-pos)) ||
			month_hand.stretched(10).intersects(Cursor::PosF().movedBy(-pos)) ||
			day_hand.stretched(10).intersects(Cursor::PosF().movedBy(-pos))) {
			GameControl::decorator.RequestStyle(U"grab1");
		}
	}
	// カーソルgrab2に変更
	if (flag_year_hand || flag_month_hand || flag_day_hand) {
		GameControl::decorator.RequestStyle(U"grab2");
	}

	// 各針が掴まれたかどうかを判定
	grab_hand();

	// 各針のアングル変更

	ClearPrint();
	/*year_angle = OffsetCircular(size / 2, Cursor::PosF().movedBy(-pos)).theta;
	if (year_angle < 0) {
		year_angle = Math::TwoPi + year_angle;
	}*/
	Seconds seconds = DurationCast<Seconds>(DateTime::Subtract(datetime, DateTime(Date(1970, 1, 1), 9)));
	Print << datetime;
	Print << seconds;
	Print << year_angle;
	Print << flag_year_hand;
	Print << flag_month_hand;
	Print << flag_day_hand;

	calc_datetime_from_angle();
	calc_hand_quad();
}

void Page_UnixClock::calc_hand_quad() {
	// const double year = ((double)(datetime.year - year_range.first) / (year_range.second - year_range.first) * 360_deg);
	year_hand = RectF((size / 2).movedBy(-9, -110), Size(18, 110)).rotatedAt(size / 2, year_angle);

	// const double month = ((double)datetime.month / 12 * 360_deg);
	month_hand = RectF((size / 2).movedBy(-4, -180), Size(8, 180)).rotatedAt(size / 2, month_angle);

	// const double day = ((double)datetime.day / Date::DaysInMonth(datetime.year, datetime.month) * 360_deg);
	day_hand = RectF((size / 2).movedBy(-2, -180), Size(4, 220)).rotatedAt(size / 2, day_angle);
}

void Page_UnixClock::calc_datetime_from_angle() {
	int daysinmonth = Date::DaysInMonth(datetime.year, datetime.month);
	int y = year_range.first + (int)(year_angle * (year_range.second - year_range.first) / Math::TwoPi);
	int m = Min(12, 1 + (int)(month_angle * 12.0 / Math::TwoPi));
	int d = Min(daysinmonth, 1 + (int)(day_angle * (daysinmonth) / Math::TwoPi));
	datetime.year = y;
	datetime.month = m;
	datetime.day = d;
}

void Page_UnixClock::grab_hand() {
	// まだつかんでいない場合は各種判定
	if (!flag_year_hand && !flag_month_hand && !flag_day_hand) {
		if (year_hand.stretched(10).intersects(Cursor::PosF().movedBy(-pos)) &&
			MouseL.down()) {
			flag_year_hand = true;
		}
		else if (month_hand.stretched(10).intersects(Cursor::PosF().movedBy(-pos)) &&
			MouseL.down()) {
			flag_month_hand = true;
		}
		else if (day_hand.stretched(10).intersects(Cursor::PosF().movedBy(-pos)) &&
			MouseL.down()) {
			flag_day_hand = true;
		}
	}

	// マウスがリリースされたらフラグをもとに戻す
	if (MouseL.up()) {
		flag_year_hand = false;
		flag_month_hand = false;
		flag_day_hand = false;
	}
}

void Page_UnixClock::update_hand_angle() {
	if (flag_year_hand) {
		year_angle = OffsetCircular(size / 2, Cursor::PosF().movedBy(-pos)).theta;
		if (year_angle < 0) {
			year_angle = Math::TwoPi + year_angle;
		}
	}
}

Page_UnixClock::Page_UnixClock()
	:WindowSystem(Vec2(300, 100), Size(600, 600), U"UNIX clock"),
	datetime(DateTime::Now()),
	circle(size / 2, 250),
	year_hand(),
	month_hand(),
	day_hand(),
	year_range(1970, 2050) {
	year_angle = ((double)(datetime.year - year_range.first) / (year_range.second - year_range.first) * Math::TwoPi);
	month_angle = ((double)datetime.month / 12 * Math::TwoPi);
	day_angle = ((double)datetime.day / Date::DaysInMonth(datetime.year, datetime.month) * Math::TwoPi);
}

#endif
