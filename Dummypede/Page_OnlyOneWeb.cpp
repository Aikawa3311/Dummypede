#include "stdafx.h"
#include "Page_OnlyOneWeb.h"

void Page_OnlyOneWeb::Draw() const{
	// 背景
	RectF(Vec2::Zero(), size).draw(Palette::Beige);
	TextureAsset(U"Search").drawAt((size / 2).movedBy(0, 16), ColorF(0.7, 0.7, 0.8, 0.5));
	// テキストエリア
	Color col_frame = textarea_active ? Palette::Royalblue : Palette::Gray;
	RoundRect(textarea_rect, 3).drawFrame(3, col_frame).draw(Palette::White);
	String const tmp_text = textarea_active ? (text + U"|" + editing_text) : text;
	// FontAsset(U"Regular")(tmp_text).draw(textarea_rect.pos.x + 5, textarea_rect.y + 2, Palette::Black);
	FontAsset(U"Regular")(tmp_text).draw(textarea_rect, Palette::Black);
	// ロゴ
	FontAsset(U"HugeDot")(U"Only 1 Web").drawAt(150, 80, Palette::Royalblue);
}

void Page_OnlyOneWeb::Update(){
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
		else if(editing_text == U"") {
			// エンターキーで検索したサイトへ飛ぶ
			jump_page();
		}
	}
}

void Page_OnlyOneWeb::jump_page() const{
	String tmp_text = text.lowercased();
	if (tmp_text == U"dummypede.net" || tmp_text == U"dummypede") {
		manager.add_page(std::make_shared<Page_Dummypede>(manager));
	}
	else if(tmp_text == U"myriapod.net" || tmp_text == U"myriapod") {
		// myriapodはオブジェクトがそれなりに大量に配置されているため多重で開けないようにしておく
		int num = manager.page_name_to_page_number(U"myriapod");
		if (num != -1) {
			manager.focus_page(num);
		}
		else {
			manager.add_page(std::make_shared<Page_Myriapod>(manager));
		}
	}
	else if (tmp_text == U"myriadtetrapod.net" || tmp_text == U"myriadtetrapod") {
		// myriad tetrapodは処理が重くなる可能性があるため多重で開けないようにしておく
		int num = manager.page_name_to_page_number(U"Myriad Tetrapod");
		if (num != -1) {
			manager.focus_page(num);
		}
		else {
			manager.add_page(std::make_shared<Page_MyriadTetrapod>(manager));
		}
	}
	else if (tmp_text == U"pigpen" || tmp_text == U"pigpen cipher" || tmp_text == U"pigpencipher") {
		manager.add_page(std::make_shared<Page_Pigpen>());
	}
	else if (tmp_text == U"isbn" || tmp_text == U"isbn-13" || tmp_text == U"isbn-13(jp)") {
		manager.add_page(std::make_shared<Page_ISBN>(manager));
	}
	else if (tmp_text == U"mikipedia") {
		manager.add_page(std::make_shared<Page_ISBN>(manager, U"Mikipedia"));
	}
	else if (tmp_text == U"creepy") {
		manager.add_page(std::make_shared<Page_Creepy>());
	}
	else if (tmp_text == U"evnnzqfef20") {
		manager.add_page(std::make_shared<Page_Evnnzqfef20>());
	}
	else {
		manager.add_page(std::make_shared<Page_404>());
	}
}

Page_OnlyOneWeb::Page_OnlyOneWeb(WindowSystemManager & manager)
	: WindowSystem(Vec2(150, 50), Size(300, 200), U"only1web"),
	manager(manager),
	text(U"o1w"),
	textarea_rect(Vec2(size.x/2 - 220/2, 130), Size(220, 30)),
	textarea_active(true){
}
