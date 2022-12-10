#include "stdafx.h"
#include "WindowSystemManager.h"

void WindowSystemManager::Update() {
	// クリックを検知してアクティブ状況を変更 & クリックされたウィンドウの優先順を変更して一番上へ
	if (MouseL.down() || MouseR.down()) {
		int index = (int)pages.size() - 1;
		for (; index >= 0; --index) {
			if (pages[index]->rect().intersects(Cursor::PosF())) break;
		}
		// ウィンドウではない場所がクリックされたら処理はしない
		if (index != -1 && pages[index]->get_focusable()) {
			focus_window(index);
			/*pages.back()->set_active(false);
			pages[index]->set_active(true);
			for (++index; index < (int)pages.size(); ++index) {
				pages[index].swap(pages[index - 1]);
			}*/
		}
	}

	// 全ページのUpdateを起動
	for (auto const& i : pages) {
		i->UpdateWindow();
	}

	// 全pageの閉じるボタン & 削除フラグをチェック
	bool erase_flag = false;
	for (auto it = pages.begin(); it != pages.end();) {
		if ((*it)->close_button_down() || (*it)->get_flag_erase()) {
			// 削除
			// もしこれが最後のページだった場合、一つ後ろのウィンドウにフォーカスする
			if (it == pages.end() - 1 && it != pages.begin()) {
				(*(it - 1))->set_active(true);
			}
			it = pages.erase(it);
			erase_flag = true;
		}
		else {
			++it;
		}
	}

	// ウィンドウが消されている場合、page_centipedegameとpage_screenの更新をする
	if (erase_flag) {
		// centipedegame
		for (auto it = page_centipedegame.begin(); it != page_centipedegame.end();) {
			if ((*it).expired()) {
				// 削除
				it = page_centipedegame.erase(it);
			}
			else {
				++it;
			}
		}

		// screen
		for (auto it = page_screen.begin(); it != page_screen.end();) {
			if ((*it).expired()) {
				// 削除
				it = page_screen.erase(it);
			}
			else {
				++it;
			}
		}
	}

	// エスケープキーが押された場合最も上のウィンドウを閉じる
	/*if (pages.size() >= 1 && KeyEscape.down()) {
		pages.pop_back();
		pages.back()->set_active(true);
	}*/

	// 追加が予約されていたページをここで追加する
	if (booked_pages.size() != 0) {
		// 現在一番上のウィンドウのフォーカスを切る
		if (!pages.empty()) pages.back()->set_active(false);
		for (auto& i : booked_pages) {
			pages.emplace_back(std::move(i));
		}
		// 追加されたウィンドウの一番上をフォーカスする
		pages.back()->set_active(true);
		booked_pages.clear();
		// pages.emplace_back(std::move(booked_page));
	}

	// フォーカスが予約されているページ
	if (booked_focus_page.has_value()) {
		focus_window(booked_focus_page.value());

		booked_focus_page.reset();
	}
}

void WindowSystemManager::Draw() {
	for (auto const& i : pages) {
		i->DrawWindow();
	}
	// DrawDepth2があるなら
	for (auto const& i : pages) {
		i->DrawDepth2();
	}
}

void WindowSystemManager::add_page(std::shared_ptr<WindowSystem> page, bool const audio) {
	// pages.emplace_back(std::move(page));
	if(audio) AudioAsset(U"enter").playOneShot(0.7);
	booked_pages.emplace_back(std::move(page));
}

void WindowSystemManager::focus_page(int const index){
	booked_focus_page = index;
}

bool WindowSystemManager::exist_page_name(String const& str){
	for (auto const& i : pages) {
		if (i->get_title() == str) {
			return true;
		}
	}
	return false;
}

int WindowSystemManager::page_name_to_page_number(String const& str){
	for (int i = 0; i < (int)pages.size(); ++i) {
		if (pages[i]->get_original_title() == str) {
			return i;
		}
	}
	return -1;
}

bool WindowSystemManager::focus_window(int index){
	if (index < 0 || index >= (int)pages.size() || pages[index]->get_focusable() == false) return false;
	pages.back()->set_active(false);
	pages[index]->set_active(true);
	for (++index; index < (int)pages.size(); ++index) {
		pages[index].swap(pages[index - 1]);
	}
	return true;
}

bool WindowSystemManager::exist_window_at(Vec2 const & pos) const{
	for (int i=(int)pages.size() - 1; i >= 0; --i) {
		if (pages[i]->rect().intersects(pos)) return true;
	}
	return false;
}

void WindowSystemManager::erase_all_window(){
	for (auto& i : pages) {
		i->set_flag_erase(true);
	}
}

void WindowSystemManager::erase_window(int const idx){
	pages[idx]->set_flag_erase(true);
}

void WindowSystemManager::set_page_centipedegame(std::shared_ptr<Page_CentipedeGame>& page_){
	std::weak_ptr<Page_CentipedeGame> ptr = page_;
	page_centipedegame.emplace_back(std::move(ptr));
	// page_centipedegame = page_;
}

void WindowSystemManager::set_page_light(std::shared_ptr<Page_Light>& page_){
	page_light = page_;
}

void WindowSystemManager::set_page_screen(std::shared_ptr<Page_Screen>& page_){
	std::weak_ptr<Page_Screen> ptr = page_;
	page_screen.emplace_back(std::move(ptr));
	// page_screen = page_;
}

void WindowSystemManager::set_page_boss_body(std::shared_ptr<Page_Boss_Body>& page_){
	page_boss_body = page_;
}

Array<std::weak_ptr<Page_CentipedeGame>>& WindowSystemManager::get_page_centipede_game(){
	return page_centipedegame;
}

std::weak_ptr<Page_Light>& WindowSystemManager::get_page_light(){
	return page_light;
}

Array<std::weak_ptr<Page_Screen>>& WindowSystemManager::get_page_screen(){
	return page_screen;
}

std::weak_ptr<Page_Boss_Body>& WindowSystemManager::get_page_boss_body(){
	return page_boss_body;
}

Array<std::shared_ptr<WindowSystem>>& WindowSystemManager::get_pages() {
	return pages;
}

Array<std::shared_ptr<WindowSystem>> const& WindowSystemManager::get_pages() const {
	return pages;
}
