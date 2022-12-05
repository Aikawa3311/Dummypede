#include "stdafx.h"
#include "GameControl.h"

//GameControl::GameControl() :
//	cardkey_flag(false),
//	cardkey_date(U"2001/09/09"),
//	centipede_highscore(0){
//}

Size GameControl::base_size = Size(1200, 800);

bool GameControl::flag_cardkey = false;

String GameControl::cardkey_date = U"2001/09/09";

int GameControl::centipede_highscore = 0;

CursorDecorator GameControl::decorator = CursorDecorator();

bool GameControl::boss_win = false;

bool GameControl::flag_clear = false;

bool GameControl::flag_shader = true;

bool GameControl::flag_readme = false;

bool GameControl::flag_visited_dark = false;

bool GameControl::flag_visited_darker = false;

String GameControl::cardkey_str(){
	String str = U"┏━━━━━━━━┓\n┃Cardkey 　　　　┃\n┃　┏━━━━━┓┃\n┣━┫" + GameControl::cardkey_date + U"┣┫\n┗━┻━━━━━┻┛";
	return str;
}

void GameControl::readme_change(){
	// readme.mdが無い場合は実行しない
	if (!FileSystem::Exists(U"./readme.md")) return;

	// 以降の処理中断
	return;

	// readmeをREADMEにリネーム
	FileSystem::Rename(U"readme.md", U"README.md");

	TextWriter tw(U"README.md");

	tw.writeln(U"# README");
	tw.writeln(U"## 縺ｯ縺倥ａ縺ｫ");
	// tw.writeln(U"Dummypede縺ｯ繧｢繝峨?繝ｳ繝archaic internet√Ε繝ｼ繧ｲ繝ｼ繝?縺ｧ縺");
	tw.writeln(U"Dummypede is an adventure game with archaic internet motif");
	tw.writeln(U"");
	tw.writeln(U"");
	tw.writeln(U"## 蜍穂ｽ懃｢ｺ隱咲腸蠅");
	tw.writeln(U"- Windows 10 Home");
	tw.writeln(U"");
	tw.writeln(U"");
	tw.writeln(U"## 謫堺ｽ懈婿豕");
	tw.writeln(U"- 蟾ｦ繧ｯ繝ｪ繝?け : 繧､繝ｳ繧ｿ繝ｩ繧ｯ繝");
	tw.writeln(U"- 繧ｭ繝ｼ繝懊?繝 : 謨ｰ蛟､縺ｪ縺ｩ縺ｮ蜈･蜉");
	tw.writeln(U"- ctrl : 繧ｷ繧ｧ繝ｼ繝?繝ｼ繧ｪ繝ｳ/繧ｪ繝");
	tw.writeln(U"- Alt + Enter : 繝輔Ν繧ｹ繧ｯ繝ｪ繝ｼ繝ｳ繝｢繝ｼ繝");
	tw.writeln(U"");
	tw.writeln(U"");
	tw.writeln(U"## Hint");
	tw.writeln(U"- Fullscreen mode (Alt + Enter) is useful for more powerful presence");
	tw.writeln(U"- This game may require knowledge and website in reality");
}


