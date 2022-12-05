#include "stdafx.h"
#include "Page_Password.h"

void Page_Password::Draw() const{
	RectF(Vec2::Zero(), size).draw(Palette::Darkkhaki);
	// 合言葉
	FontAsset(U"BigRegular")(U"Password / 合言葉").drawAt((size/2).movedBy(0, -40), Palette::Black);
	// テキストエリア
	Color col_frame = textarea_active ? Palette::Royalblue : Palette::Gray;
	RoundRect(textarea_rect, 3).drawFrame(3, col_frame).draw(Palette::White);
	String const tmp_text = textarea_active ? (text + U"|" + editing_text) : text;
	FontAsset(U"Regular")(tmp_text).draw(textarea_rect, Palette::Black);

	// メッセ―ジ欄
	RoundRect(message_rect, 6).stretched(2).drawFrame(3, Palette::Lightgray);
	RoundRect(message_rect, 6).drawFrame(5, Palette::Gray).draw(ColorF(0, 0, 0.5, 1));

	// メッセージを表示
	if (message_timer.isRunning()) {
		FontAsset(U"RegularDot")(message).drawAt(size.x / 2, message_rect.y + message_rect.h / 2, ColorF(0, 0.8, 0, 1 - EaseInExpo(message_timer.sF() / 4.0)));
		// FontAsset(U"RegularDot")(message).drawAt(size.x / 2, message_rect.y + message_rect.h / 2);
	}

	// 画面風エフェクト
	for (int i = 0; i < message_rect.h; ++i) {
		if (sync_anim_function(((int)i / message_rect.h) + anim_timer.sF() / 14.0)) {
			Line(message_rect.x + 1, message_rect.y + message_rect.h - i, message_rect.x + message_rect.w - 1, message_rect.y + message_rect.h - i).draw(ColorF(0.4, 0.4, 0.9, 0.5));
		}
	}
	RoundRect(message_rect, 6).drawFrame(1.5, Palette::Lightgray);
}

void Page_Password::Update(){
	if (message_timer.s() > 4) {
		message_timer.pause();
	}
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
			// パスワード照合
			password_confirm();
		}
		if (KeyEnter.down() && editing_text != U"") {
			text += editing_text;
			editing_text = U"";
		}
	}
}

void Page_Password::password_confirm(){
	String str = U"";
	if (text == U"フリンドル" || text == U"フリンドル！" || text == U"フリンドル!") {
		if (Page_MukadeShell::get_access_level() >= 2) {
			str = U"既に有効化された合言葉です";
			AudioAsset(U"cancel").playOneShot(0.9);
		}
		else {
			Page_MukadeShell::set_access_level(2);
			str = U"アクセスレベルアップ : " + Format(Page_MukadeShell::get_access_level());
			AudioAsset(U"enter2").playOneShot(0.7);
		}
	}
	else if (text == U"199501715") {
		// 851624693
		if (Page_MukadeShell::get_access_level() >= 3) {
			str = U"既に有効化されたPasswordです";
			AudioAsset(U"cancel").playOneShot(0.9);
		}
		else {
			Page_MukadeShell::set_access_level(3);
			str = U"アクセスレベルアップ : " + Format(Page_MukadeShell::get_access_level());
			AudioAsset(U"enter2").playOneShot(0.7);
		}
	}
	else if (text.lowercased() == U"free") {
		if (Page_MukadeShell::get_access_level() >= 4) {
			str = U"既に有効化されたPasswordです";
			AudioAsset(U"cancel").playOneShot(0.9);
		}
		else {
			Page_MukadeShell::set_access_level(4);
			str = U"アクセスレベルアップ : " + Format(Page_MukadeShell::get_access_level());
			AudioAsset(U"enter2").playOneShot(0.7);
		}
	}
	else {
		// str = U"Passwordもしくは合言葉が違います";
		str = U"入力内容に誤りがあります";
		AudioAsset(U"cancel").playOneShot(0.9);
	}
	message_display(str);
}

bool Page_Password::sync_anim_function(double const x) const{
	double d = x / 0.1;			// 分母の数を大きくすると間隔が狭くなる
	return ((int)d % 2) == 0;	// % n のnの数を大きくすると波の出現頻度が低くなる
}

void Page_Password::message_display(String const& str){
	message = str;
	message_timer.restart();
}

Page_Password::Page_Password(WindowSystemManager& manager)
	: // WindowSystem(Scene::Center() - Size(400, 200) / 2, Size(400, 200), U"password"),
	WindowSystem(GameControl::base_size / 2 - Size(400, 200) / 2, Size(400, 200), U"password"),
	manager(manager),
	text(U""),
	editing_text(U""),
	textarea_rect(size.x/2 - 100, size.y/2 - 10, 200, 30),
	textarea_active(false),
	message_rect(size.x/2 - 150, size.y/2 + 40, 300, 30),
	message(U"")
{
	anim_timer.start();
}
