#include "stdafx.h"
#include "Page_ISBN.h"

void Page_ISBN::Draw() const{
	RectF(Vec2::Zero(), size).draw(Palette::White);

	// テキストエリア
	TextureAsset(U"MikipediaSearch").draw(textarea_rect.pos.movedBy(-28, 6), Palette::Darkgray);
	Color col_frame = textarea_active ? Palette::Royalblue : Palette::Gray;
	RoundRect(textarea_rect, 3).drawFrame(3, col_frame).draw(Palette::White);
	String const tmp_text = textarea_active ? (text + U"|" + editing_text) : text;
	// FontAsset(U"Regular")(tmp_text).draw(textarea_rect.pos.x + 5, textarea_rect.y + 2, Palette::Black);
	FontAsset(U"Regular")(tmp_text).draw(textarea_rect, Palette::Black);

	// ロゴ
	// Circle(Vec2(50, 70), 30).drawFrame(3, Palette::Black);
	TextureAsset(U"MikipediaIcon").drawAt(Vec2(50, 70), { Palette::Cadetblue, 0.7 });
	// FontAsset(U"BigImprisha")(U"M").drawAt(Vec2(50, 70), Palette::Black);
	TextureAsset(U"Mlogo").scaled(0.5).drawAt(Vec2(50, 70));
	FontAsset(U"RegularMintyo")(U"Mikipedia").draw(Arg::center = Vec2(130, 60), Palette::Black);
	FontAsset(U"SmallMintyo")(U"総合辞典").draw(Arg::center = Vec2(130, 80), Palette::Black);

	// 説明本文
	Vec2 base(30, 80);
	FontAsset(U"HugeRegular")(page_name).draw(base + Vec2(20, 30), Palette::Black);
	Line(base + Vec2(20, 100), base + Vec2(size.x - 20 - base.x, 100)).draw(2, Palette::Darkgray);
	if(page_name == U"ISBN Code") {
		// ISBN Code
		FontAsset(U"RegularThinMintyo")(U"書籍を特定するためのコード。\n現在では数字13桁で表す方式が主流である。").draw(base + Vec2(10, 120), Palette::Black);
		FontAsset(U"HugeMintyo")(U"9784XXXXXXXXX").drawAt((size/2).movedBy( 0, (int)base.y - 50), Palette::Black);
		Line(base + Vec2(90 - base.x, 226), base + Vec2(182 - base.x, 226)).draw(4, Palette::Black);
		Line(base + Vec2(190 - base.x, 226), base + Vec2(410 - base.x, 226)).draw(4, Palette::Black);
		FontAsset(U"Regular")(U"4桁(固定)").draw(base + Vec2(94 - base.x, 234), Palette::Black);
		FontAsset(U"Regular")(U"9桁(可変)").draw(base + Vec2(250 - base.x, 234), Palette::Black);
		FontAsset(U"RegularThinMintyo")(U"日本では上位4桁が9784で固定されるため、\n実質下位9桁によって書籍を特定することが\n可能である。").draw(base + Vec2(10, 280), Palette::Black);
		FontAsset(U"RegularThinMintyo")(U"外部リンク").draw(base + Vec2(10, 360), Palette::Black);
		FontAsset(U"RegularThinMintyo")(U"https://www.books.or.jp/").draw(base + Vec2(10, 380), Palette::Blue);
		Line(base + Vec2(10, 402), base + Vec2(250, 402)).draw(1, Palette::Blue);
	}
	else if (page_name == U"Mikipedia") {
		// Mikipediaトップページ
		FontAsset(U"RegularThinMintyo")(U"Mikipediaへようこそ").draw(base + Vec2(10, 120), Palette::Black);
	}
	else if (page_name == U"Overflow") {
		// オーバーフロー
		FontAsset(U"RegularThinMintyo")(U"コンピュータ上の数値計算で発生する現象。\n例えば3桁の二進数では、8(二進数で1000)以上を\n表現することができないため、7+1などの演算で\n正しくない結果を返してしまい、これを\nオーバーフローと呼ぶ。").draw(base + Vec2(10, 120), Palette::Black);
		FontAsset(U"RegularThinMintyo")(U"符号付き32桁の二進数で整数を表現することが\nしばしばあり、この際の正の上限は\n2,147,483,647である。これに1を足すと\n値が-2,147,483,648となり、以降負の値が続く。").draw(base + Vec2(10, 240), Palette::Black);
		// FontAsset(U"RegularThinMintyo")(U"現在では、時間(UNIX time)のオーバーフローが\n懸念されている事例が有名。").draw(base + Vec2(10, 340), Palette::Black);

		/*
		// 表の描画
		Line(base + Vec2(40, 180), base + Vec2(400, 180)).draw(2, Palette::Black);
		Line(base + Vec2(40, 180), base + Vec2(400, 180)).draw(2, Palette::Black);
		Line(base + Vec2(40, 180 + 30), base + Vec2(400, 180 + 30)).draw(2, Palette::Black);
		Line(base + Vec2(40, 180 + 60), base + Vec2(400, 180 + 60)).draw(2, Palette::Black);
		Line(base + Vec2(40, 180 + 90), base + Vec2(400, 180 + 90)).draw(2, Palette::Black);

		Line(base + Vec2(40, 180), base + Vec2(40, 180 + 90)).draw(2, Palette::Black);
		Line(base + Vec2(290, 180), base + Vec2(290, 180 + 90)).draw(2, Palette::Black);
		Line(base + Vec2(400, 180), base + Vec2(400, 180 + 90)).draw(2, Palette::Black);

		FontAsset(U"RegularConsol")(U"JST").draw(Arg::bottomLeft = base + Vec2(40, 205), Palette::Black);
		FontAsset(U"RegularConsol")(U"1970/01/01 09:00:00").draw(base + Vec2(50, 215 + 2), Palette::Black);
		FontAsset(U"RegularConsol")(U"10:46:40").draw(Arg::center = base + Vec2(100, 255 + 2), Palette::Black);
		FontAsset(U"RegularConsol")(U"10:46:41").draw(Arg::center = base + Vec2(100, 285 + 2), Palette::Black);
		
		FontAsset(U"RegularConsol")(U"1000000000").draw(Arg::rightCenter = base + Vec2(285, 255 + 2), Palette::Black);
		FontAsset(U"RegularConsol")(U"1000000001").draw(Arg::rightCenter = base + Vec2(285, 285 + 2), Palette::Black);

		FontAsset(U"RegularThinMintyo")(U"2001年9月9日10時46分40秒に値が10桁となり、\nその際に様々な問題が懸念された(2001年問題)。").draw(base + Vec2(10, 280), Palette::Black);
		FontAsset(U"RegularThinMintyo")(U"").draw(base + Vec2(10, 260), Palette::Black);
		*/
	}
	else {
		// Not Found & 寄付ページ
		FontAsset(U"RegularThinMintyo")(U"問い合わせに合致する検索結果は\nありませんでした。").draw(base + Vec2(10, 120), Palette::Black);
		RectF(base.movedBy(0, 205), Vec2(460, 195)).drawFrame(4, Palette::Red);
		RectF(base.movedBy(0, 205), Vec2(460, 30)).draw(Palette::Red);
		FontAsset(U"BoldRegular")(U"寄付のお願い（ご一読ください）").draw(base + Vec2(10, 205), Palette::White);
		FontAsset(U"RegularThinMintyo")(U"Mikipediaは多くの支援により成立していますが、\n依然として厳しい資金難に直面しています。\nMikipediaを、あなたの力で支えませんか。").draw(base + Vec2(10, 240), Palette::Black);
		if (active && donate_button.movedBy(pos).intersects(Cursor::PosF())) {
			donate_button.drawFrame(3, Palette::Blueviolet).draw(Palette::Red);
			FontAsset(U"Regular")(U"莉翫縺仙ｯ?ｻ倥繧").drawAt(donate_button.center(), Palette::White);
		}
		else {
			donate_button.drawFrame(3, Palette::Darkgray).draw(Palette::Ghostwhite);
			FontAsset(U"Regular")(U"今すぐ寄付する").drawAt(donate_button.center(), Palette::Black);
		}
		FontAsset(U"RegularThinMintyo")(U"寄付のご協力ありがとうございます。").draw(base + Vec2(10, 360), Palette::Black);
	}

	/*Vec2 base(30, 60);
	FontAsset(U"HugeRegular")(U"ISBN Code").draw(base + Vec2(20, 30), Palette::Black);
	Line(base + Vec2(20, 100), base + Vec2(size.x - 20 - base.x, 100)).draw(2, Palette::Darkgray);
	FontAsset(U"RegularThinMintyo")(U"書籍を特定するためのコード。\n現在では数字13桁で表す方式が主流である。").draw(base + Vec2(10, 140), Palette::Black);
	FontAsset(U"HugeMintyo")(U"9784XXXXXXXXX").drawAt((size / 2).movedBy(base.x + 0, base.y - 10), Palette::Black);
	Line(base + Vec2(90, 266), base + Vec2(182, 266)).draw(4, Palette::Black);
	Line(base + Vec2(190, 266), base + Vec2(410, 266)).draw(4, Palette::Black);
	FontAsset(U"Regular")(U"4桁(固定)").draw(base + Vec2(94, 274), Palette::Black);
	FontAsset(U"Regular")(U"9桁(可変)").draw(base + Vec2(250, 274), Palette::Black);
	FontAsset(U"RegularThinMintyo")(U"日本では上の4桁が9784で固定されるため、\n実質下位9桁によって書籍を特定することが\n可能である。").draw(base + Vec2(10, 340), Palette::Black);*/
}

void Page_ISBN::Update(){
	if (!active) return;
	// 長方形が押されたら入力状態をオンへ
	if (textarea_rect.movedBy(pos).intersects(Cursor::PosF())) {
		GameControl::decorator.RequestStyle(U"i");
	}
	if (MouseL.down()) {
		textarea_active = textarea_rect.movedBy(pos).intersects(Cursor::PosF());
	}
	// キーボード入力受け取り
	if (textarea_active) {
		if (!KeyEnter.pressed()) {
			// キー入力
			String tmp = text;
			TextInput::UpdateText(text);
			if (text != tmp) {
				AudioAsset(U"type").playOneShot(0.7);
			}
			editing_text = TextInput::GetEditingText();
		}
		if (KeyEnter.down() && editing_text == U"") {
			// エンターキーの挙動
			jump_page();
		}
		if (KeyEnter.down() && editing_text != U"") {
			text += editing_text;
			editing_text = U"";
		}
	}

	// 寄付ボタンの押下
	if (donate_page == true && donate_button.movedBy(pos).intersects(Cursor::PosF())) {
		GameControl::decorator.RequestStyle(U"hand");
		if (MouseL.down()) {
			manager.add_page(std::make_shared<Page_FeedFiles>());
		}
	}

	// リンクの押下
	if (page_name == U"ISBN Code" && link_button.movedBy(pos).intersects(Cursor::PosF())) {
		GameControl::decorator.RequestStyle(U"hand");
		if (MouseL.down()) {
			// SimpleHTTP::
			AudioAsset(U"enter").playOneShot(0.7);
			System::LaunchBrowser(U"https://www.books.or.jp/");
		}
	}
}

void Page_ISBN::jump_page(){
	AudioAsset(U"enter").playOneShot(0.7);
	String low = text.lowercased();

	donate_page = false;

	if (low == U"isbn" || low == U"isbn code" || low == U"isbn-code" || low == U"isbncode" || low == U"isbn-13" || low == U"isbn13") {
		page_name = U"ISBN Code";
	}
	else if (low == U"mikipedia") {
		page_name = U"Mikipedia";
	}
	else {
		donate_page = true;
		page_name = text;
	}

	if (page_name == U"Mikipedia") {
		title = U"Mikipedia";
	}
	else {
		title = page_name + U" - Mikipedia";
	}
}

Page_ISBN::Page_ISBN(WindowSystemManager& manager, String const & str)
	:WindowSystem(Vec2(350, 150), Size(500, 500), str + U" - Mikipedia"),
	manager(manager),
	page_name(str),
	text(U""),
	textarea_rect(Vec2(240, 60), Size(220, 30)),
	textarea_active(true),
	donate_button(Vec2(120, 394), Vec2(250, 35)),
	link_button(Vec2(40, 465), Vec2(240, 25)){

}
