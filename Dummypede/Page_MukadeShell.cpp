#include "stdafx.h"
#include "Page_MukadeShell.h"

int Page_MukadeShell::access_level = 1;

void Page_MukadeShell::Draw() const{
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

void Page_MukadeShell::Update(){
	size_t tmp_text_length = text_length;

	if (active && rect_without_head_frame().intersects(Cursor::PosF())) {
		GameControl::decorator.RequestStyle(U"i");
	}

	switch (state){
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
		if (!active) return;
		if (!KeyEnter.pressed() && TextInput::GetEditingText() == U"") {
			String tmp_text = text;
			TextInput::UpdateText(text);
			if (text != tmp_text) {
				AudioAsset(U"type").playOneShot(0.7);
			}
		}
		if (KeyEnter.down() && TextInput::GetEditingText() == U"") {
			// 入力完了
			switch (state_input) {
			case 0:
				// 通常コマンド入力時
				add_text_log(text);
				command_process(text);
				break;
			case 1:
				// cardkeyのパスワード入力
				command_cardkey_password();
				break;
			case 2:
				// cardkeyの日付更新
				add_text_log(text);
				command_cardkey_set_date();
				break;
			}
			// text_botを流す
			changestate_anim(text_bot);
		}
		break;
	default:
		break;
	}
	
}

void Page_MukadeShell::add_text_log(String const& str){
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

void Page_MukadeShell::changestate_anim(String str){
	state = 0;
	if (state_input == 0) {
		// 次回が通常入力の場合"コマンド:"を出力するようにする
		if (str != U"") str += U"\n";
		str += U"コマンド:";
	}
	set_text_bot(str);
	pre_br_pos = 0;
	text_length = 0;
	anim_timer.restart();
}

void Page_MukadeShell::changestate_input(){
	state = 1;
	text = U"";
	text_bot = U"";
	anim_timer.reset();
}

String Page_MukadeShell::cardkey_str() const{
	String str = U"┏━━━━━━━━┓\n┃Cardkey 　　　　┃\n┃　┏━━━━━┓┃\n┣━┫" + GameControl::cardkey_date +  U"┣┫\n┗━┻━━━━━┻┛";
	return str;
}

void Page_MukadeShell::command_process(String str){
	str.lowercase();
	if (str == U"help") {
		command_help();
	}
	else if (str == U"cardkey") {
		command_cardkey();
	}
	else if (str == U"light" && access_level >= 2) {
		command_light();
	}
	else if (str == U"sword" && access_level >= 2) {
		command_sword();
	}
	else if (str == U"uninstall" && access_level >= 4) {
		command_uninstall();
	}
	else {
		command_unknown();
	}
}

void Page_MukadeShell::command_help() {
	String str = U"help\ncardkey\n";
	if (access_level >= 2) {
		str += U"light\n";
		str += U"sword\n";
	}
	if (access_level >= 4) {
		str += U"uninstall\n";
	}
	set_text_bot(U"現在のアクセスレベル:" + Format(access_level) + U"\n現在アクセスできるコマンドは\n" + str + U"以上です");
}

void Page_MukadeShell::command_cardkey(){
	if (GameControl::flag_cardkey == false) {
		set_text_bot(U"前回のアクセスから時間が経っています\n8桁のパスコードを入力してください");
		state_input = 1;
	}
	else {
		set_text_bot(cardkey_str() + U"\n変更後のコード(YYYY/MM/DD)を入力してください");
		state_input = 2;
	}
}

void Page_MukadeShell::command_light(){
	// ライトページを生成
	if (manager.exist_page_name(U"light")) {
		set_text_bot(U"既にlightが存在します");
		return;
	}
	std::shared_ptr<Page_Light> page = std::make_shared<Page_Light>();
	manager.add_page(page);
	manager.set_page_light(page);
	set_text_bot(U"lightオン");
}

void Page_MukadeShell::command_sword(){
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

void Page_MukadeShell::command_uninstall(){
	// 全ページ削除、エンディング
	manager.erase_all_window();
	GameControl::flag_clear = true;
	manager.add_page(std::make_shared<Page_Ending>());
}

void Page_MukadeShell::command_unknown(){
	Array<String> messages = { U"コマンドの内容が不明です\nhelpコマンドを利用してください", U"正しくないコマンドです\nhelpコマンドを利用してください", U"helpコマンドを利用してください"};
	set_text_bot(messages.choice());
}

void Page_MukadeShell::command_cardkey_password(){
	if (text == U"20010909") {
		// 認証
		text_bot = U"パスコードを確認しました\n";
		text_bot += cardkey_str();
		text_bot += U"\ncardkeyコマンドでコードを変えられます";
		GameControl::flag_cardkey = true;
	}
	else {
		// 認証コードミス
		text_bot = U"パスコードが違います";
	}
	state_input = 0;
}

void Page_MukadeShell::command_cardkey_set_date(){
	// バリデート
	if (text.length() != 10 ||
		!IsDigit(text[0]) ||
		!IsDigit(text[1]) ||
		!IsDigit(text[2]) ||
		!IsDigit(text[3]) ||
		text[4] != '/' ||
		!IsDigit(text[5]) ||
		!IsDigit(text[6]) ||
		text[7] != '/' ||
		!IsDigit(text[8]) ||
		!IsDigit(text[9])) {
		set_text_bot(U"YYYY/MM/DDの形式で入力してください");
	}
	else {
		GameControl::cardkey_date = text;
		set_text_bot(U"コードを" + text + U"に変更しました");
	}
	state_input = 0;
}

Page_MukadeShell::Page_MukadeShell(WindowSystemManager& manager)
	:WindowSystem(Vec2(670, 440), Size(420, 300), U"MukadeTalker"),
	manager(manager),
	text(U""),
	text_bot(U""),
	text_log(0),
	state(0),
	state_input(0),
	pre_br_pos(0),
	text_length(0) {
	changestate_anim(U"");
}

int Page_MukadeShell::get_access_level(){
	return access_level;
}

void Page_MukadeShell::set_text_bot(String const& str){
	text_bot = str;
}

void Page_MukadeShell::set_access_level(int const level){
	access_level = level;
}
