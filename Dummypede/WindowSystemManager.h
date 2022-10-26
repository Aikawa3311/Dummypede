#pragma once
#include <Siv3D.hpp>
#include "WindowSystem.h"
// ★ここにリアクションページのインクルード追加
// #include "Page1.h"
#include "Page_CentipedeGame.h"
#include "Page_Light.h"
#include "Page_Screen.h"
#include "Page_Boss_Body.h"

// ★ここにリアクションページの前方宣言追加
// class Page1;
class Page_CentipedeGame;
class Page_Light;
class Page_Screen;
class Page_Boss_Body;

class WindowSystemManager {
private:
	Array<std::shared_ptr<WindowSystem>> pages;
	// イテレート中にページが増えることを避けるための予約
	Array<std::shared_ptr<WindowSystem>> booked_pages;
	// フォーカスするページの予約
	Optional<int> booked_focus_page;
	// レンダーテクスチャの用意


	// ★ここに他のページとやり取りする/やり取りされるページのstd::weak_ptrを追加
	// std::weak_ptr<Page1> page1;
	std::weak_ptr<Page_CentipedeGame> page_centipedegame;
	std::weak_ptr<Page_Light> page_light;
	std::weak_ptr<Page_Screen> page_screen;
	std::weak_ptr<Page_Boss_Body> page_boss_body;

	// pages配列の最後尾のpageのフォーカスを外し、index番目のpageを配列の最後尾に送ってそれをフォーカスする
	bool focus_window(int index);

public:
	void Update();
	void Draw();

	// 予約にページを追加
	void add_page(std::shared_ptr<WindowSystem> page, bool const audio = true);

	// 添え字を指定してフォーカス予約
	void focus_page(int const index);

	// 名前が一致するウィンドウが存在するかどうかチェック
	bool exist_page_name(String const& str);

	// 名前が一致するウィンドウの、pages配列における添え字を取得(存在しない場合-1を返す)
	int page_name_to_page_number(String const& str);

	// 与えられた座標にウィンドウが存在するかどうかを返す 存在していた場合true
	bool exist_window_at(Vec2 const & pos) const;

	// ウィンドウの消去
	void erase_all_window();

	// ウィンドウを選択して消去フラグを立てる
	void erase_window(int const idx);

	// ★ここにリアクションページのセッター
	// void set_page1(std::shared_ptr<Page1>& page1_);
	void set_page_centipedegame(std::shared_ptr<Page_CentipedeGame>& page_);
	void set_page_light(std::shared_ptr<Page_Light>& page_);
	void set_page_screen(std::shared_ptr<Page_Screen>& page_);
	void set_page_boss_body(std::shared_ptr<Page_Boss_Body>& page_);

	// ★ここにリアクションページのゲッター
	// std::weak_ptr<Page1>& get_page1();
	std::weak_ptr<Page_CentipedeGame>& get_page_centipede_game();
	std::weak_ptr<Page_Light>& get_page_light();
	std::weak_ptr<Page_Screen>& get_page_screen();
	std::weak_ptr<Page_Boss_Body>& get_page_boss_body();

	// ページ一覧のrefを返す
	Array<std::shared_ptr<WindowSystem>>& get_pages();
	// ページ一覧のconst refを返す
	Array<std::shared_ptr<WindowSystem>> const& get_pages() const;
};

