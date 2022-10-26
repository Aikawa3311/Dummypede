#include "stdafx.h"
#include "Page_Boss_MukadeShell.h"

void Page_Boss_MukadeShell::Draw() const{
}

void Page_Boss_MukadeShell::Update(){
	size_t tmp_text_length = text_length;
	if (rect_without_head_frame().intersects(Cursor::PosF())) {
		GameControl::decorator.RequestStyle(U"i");
	}
	switch (state) {
	case 0:
		// アニメーション中
		// 改行文字が出てくるのを検知
		text_length = Min(anim_timer.ms() / 50Ui64, text_bot.size() - 1);
		if (text_length != tmp_text_length) {
			AudioAsset(U"message").playOneShot(Random(0.7, 0.9));
		}
		if (text_bot.at(text_length) == '\n' && text_length >= pre_br_pos) {
			add_text_log(text_bot.substr(pre_br_pos, text_length - pre_br_pos));
			pre_br_pos = text_length + 1;
		}
		if (text_length >= text_bot.size() - 1) {
			add_text_log(text_bot.substr(pre_br_pos, text_length + 1 - pre_br_pos));
			changestate_input();
		}
		break;
	case 1:
		// 入力受付
		if (!KeyEnter.pressed() && TextInput::GetEditingText() == U"") {
			String tmp_text = text;
			TextInput::UpdateText(text);
			if (text != tmp_text) {
				AudioAsset(U"type").playOneShot(0.7);
			}
		}
		if (KeyEnter.down() && TextInput::GetEditingText() == U"") {
			// 入力完了
			add_text_log(text);
			command_process();
			// text_botを流す
			changestate_anim(text_bot);
		}
		break;
	default:
		break;
	}
}

void Page_Boss_MukadeShell::add_text_log(String const& str){
	// もし改行が入っていたら改行部分で分割する
	size_t br_pos = 0, pre_pos = 0;
	while (br_pos != String::npos) {
		br_pos = str.indexOf('\n', br_pos);
		text_log.push_front(str.substr(pre_pos, (br_pos == String::npos) ? br_pos : br_pos - pre_pos));
		pre_pos = br_pos + 1;
	}
	while (text_log.size() > 10) {
		text_log.pop_back();
	}
}

void Page_Boss_MukadeShell::changestate_anim(String const& str){
	state = 0;
	set_text_bot(str);
	pre_br_pos = 0;
	text_length = 0;
	anim_timer.restart();
}

void Page_Boss_MukadeShell::changestate_input(){
	state = 1;
	text = U"";
	text_bot = U"";
	anim_timer.reset();
}

void Page_Boss_MukadeShell::command_process(){
	String str = text.lowercase();
	if (str == U"help") {
		command_help();
	}
	else if (str == U"cardkey") {
		command_unusable();
	}
	else if (str == U"light") {
		command_unusable();
	}
	else if (str == U"sword") {
		command_sword();
	}
	else {
		command_unknown();
	}
}

void Page_Boss_MukadeShell::command_help(){
	String str = U"help\ncardkey [アクセス制限中]\nlight [アクセス制限中]\nsword\n";
	set_text_bot(U"現在使用できるコマンドは\n" + str + U"以上です");
}

void Page_Boss_MukadeShell::command_sword(){
	if (GameControl::decorator.get_cursor_state() == 2) {
		// 既に剣着用時
		GameControl::decorator.unset();
		set_text_bot(U"swordを外します");
	}
	else {
		GameControl::decorator.set_sword();
		set_text_bot(U"swordを着用します");
	}
}

void Page_Boss_MukadeShell::command_unusable(){
	set_text_bot(U"現在アクセスできません");
}

void Page_Boss_MukadeShell::command_unknown(){
	Array<String> messages = { U"コマンドの内容が不明です", U"そのようなコマンドは知りません", U"正しくないコマンドです", U"helpコマンドを使ってください", U"よくわかりません" };
	set_text_bot(messages.choice());
}

Page_Boss_MukadeShell::Page_Boss_MukadeShell(WindowSystemManager& manager)
	:WindowSystem(Scene::Size().movedBy(-400, -300), Size(400, 300), U"MukadeTalker"),
	manager(manager),
	text(U""),
	text_bot(U""),
	text_log(0),
	state(0),
	state_input(0),
	pre_br_pos(0),
	text_length(0){
	// 消去不可・ドラッグ不可・フォーカス不可
	set_erasable(false);
	set_draggable(false);
	set_focusable(false);
	set_light_focus(false);
	changestate_anim(U"command:");
}

void Page_Boss_MukadeShell::DrawDepth2() const{
	// ウィンドウ枠を描画
	draw_frame();
	// ここから先は相対座標に戻す
	{
		ScopedViewport2D viewport(pos.asPoint(), size);
		// 背景
		RectF(Vec2::Zero(), size).draw(ColorF(0.0, 0.0, 0.0, 0.5));
		// ログ
		for (int i = 0; i < (int)text_log.size(); ++i) {
			FontAsset(U"RegularDot")(text_log.at(i)).draw(5, size.y - 50 - 24 * i, Palette::Lightgreen);
		}
		// 入力中の文字列など
		String text_tmp;
		switch (state) {
		case 0:
			// アニメーション中
			text_tmp = text_bot.substr(pre_br_pos, (text_length <= pre_br_pos) ? 0 : text_length - pre_br_pos);
			break;
		case 1:
			// 入力受付中
			text_tmp = text;
			break;
		}
		FontAsset(U"RegularDot")(text_tmp).draw(5, size.y - 26, Palette::Lightgreen);
	}
}

void Page_Boss_MukadeShell::set_text_bot(String const& str){
	text_bot = str;	
}
