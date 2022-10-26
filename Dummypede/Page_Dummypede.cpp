#include "stdafx.h"
#include "Page_Dummypede.h"

void Page_Dummypede::Draw() const{
	RectF(Vec2::Zero(), size).draw(Palette::Black);
	// Circle(dest, 20).draw(Palette::Red);
	centipede.Draw();
}

void Page_Dummypede::Update(){
	switch (state) {
	case 0:
		// アニメーション中
		//dest = Vec2(size.x * 0.2 + (1 - Periodic::Sine0_1(5000ms)) * size.x * 0.6, -200 + 600 * (3000 - anim_timer.ms())/3000.0);
		dest = Vec2(size.x / 2 + Sin(anim_timer.ms() * 0.002) * size.x * 0.4, -200 + 600 * (3000 - anim_timer.ms()) / 3000.0);
		centipede.set_dest(dest);
		centipede.Update();
		if (anim_timer.s() >= 3) {
			state = 1;
		}
		break;
	case 1:
		// 起動中
		if (!active) return;
		auto const& bodies = centipede.get_bodies();
		for (int i = 0; i < centipede.get_length(); ++i) {
			// ハイライトする
			if (bodies.at(i).get_circle().intersects(Cursor::PosF().movedBy(-pos))) {
				// Cursor::RequestStyle(CursorStyle::Hand);
				// Cursor::RequestStyle(U"hand");
				GameControl::decorator.RequestStyle(U"hand");
				centipede.set_col_body(Palette::Cornflowerblue, i);
				if (i == 0) centipede.set_col_antenna(Palette::Cornflowerblue);
			}
			else {
				centipede.set_col_body(Palette::White, i);
				if(i == 0) centipede.set_col_antenna(Palette::White);
			}
			// クリックで飛ぶ
			if (bodies.at(i).get_circle().movedBy(pos).leftClicked()) {
				switch (i) {
				case 0:
					// 自己紹介ページ
					manager.add_page(std::make_shared<Page_SelfIntroduction>(manager));
					break;
				case 1:
					// 目線ページ
					manager.add_page(std::make_shared<Page_Eye>());
					break;
				case 2:
					// MukadeTalker
					manager.add_page(std::make_shared<Page_MukadeShell>(manager));
					break;
				case 3:
					// スクリーンページ
					{
						std::shared_ptr<Page_Screen> page = std::make_shared<Page_Screen>();
						manager.add_page(page);
						manager.set_page_screen(page);
					}
					break;
				case 4:
					// カードキーリーダーページ
					{
						int num = manager.page_name_to_page_number(U"cardkey reader");
						if (num != -1) {
							manager.focus_page(num);
						}
						else {
							manager.add_page(std::make_shared<Page_CardkeyReader>(manager));
						}
					}
					break;
				case 5:
					// パスワード照合ページ
					{
						int num = manager.page_name_to_page_number(U"password");
						if (num != -1) {
							manager.focus_page(num);
						}
						else {
							manager.add_page(std::make_shared<Page_Password>(manager));
						}
					}

					/*if (manager.exist_page_name(U"password")) break;
					manager.add_page(std::make_shared<Page_Password>(manager));*/
					break;
				case 6:
					// centipede game
					{
						std::shared_ptr<Page_CentipedeGame> page = std::make_shared<Page_CentipedeGame>();
						manager.add_page(page);
						manager.set_page_centipedegame(page);
					}
					break;
				}
			}
		}
		break;
	}
}

Page_Dummypede::Page_Dummypede(WindowSystemManager& manager)
	:WindowSystem(Vec2(300, 100), Size(600, 600), U"Dummypede"),
	manager(manager),
	centipede(Vec2(size.x/2 - 100, size.y + size.y * 0.12), size.movedBy(size.x/2, 0), 7, 15),
	dest(Vec2::Zero()){
	// centipedeの設定など
	centipede.set_interval(15 * 2 + 30);
	centipede.set_legs_anim_flag(false);
	centipede.set_spd(210);
	centipede.set_dir_range(Vec2(2, 100));
	anim_timer.restart();
}
