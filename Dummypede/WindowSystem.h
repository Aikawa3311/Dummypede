#pragma once
#include <Siv3D.hpp>
#include "WindowHeadFrame.h"

class WindowSystem {
private:
	//// 上側の長方形枠
	//RectF frame_head;
	//// 閉じるボタン
	//RectF close_button;
	WindowHeadFrame frame_head;
	bool dragging = false;
	bool focused = false;
	virtual void Draw() const;
	virtual void Update();

protected:
	// ウィンドウのアクティブ状況
	bool active = false;
	// ドラッグ可能状態
	bool draggable = true;
	// ウィンドウ消去可能状態
	bool erasable = true;
	// フォーカス可能状態
	bool focusable = true;
	// 非フォーカス中はヘッダー部分を暗くするフラグ
	bool light_focus = true;

	// 削除フラグ, 立ったフレームにそのページが削除される
	bool flag_erase = false;
	
	// ウィンドウタイトル
	String title = U"<no name>";
	Vec2 pos;
	Size size;
	double window_alpha;			// ウィンドウの透明度、現在未使用
	RenderTexture render_texture;	// ウィンドウの描画用、現在未使用
	// Array<std::unique_ptr<GameObject>> objects;

	// 矩形領域描画
	void draw_frame() const;

public:
	WindowSystem(Vec2 const& pos_ = Vec2(100, 100), Size const& size_ = Size(200, 200), String const& title_ = U"<no name>");

	// 枠なども含めた描画
	void DrawWindow() const;

	// ウィンドウ操作などを含めた更新
	void UpdateWindow();

	// 絶対座標による深さ2の描画(Drawよりも上の描画をしたい場合)
	virtual void DrawDepth2() const;

	// 右上や左上にあるウィンドウ閉じるボタン、押されたらtrue
	bool close_button_down() const;

	// ウィンドウに当たる長方形を返す
	RectF rect() const;

	// ウィンドウのヘッダ枠を取り除いた長方形を返す
	RectF rect_without_head_frame() const;

	// ウィンドウを動かす
	void moveBy(Vec2 const & v);

	// タイトル名を取得
	String get_title() const {
		return title;
	}

	// 座標を取得
	Vec2 get_pos() const {
		return pos;
	}

	// サイズを取得
	Size get_size() const {
		return size;
	}

	// ウィンドウのアクティブ状況を取得
	bool get_active() const {
		return active;
	}

	// フォーカス可能状態の取得
	bool get_focusable() const;

	// 削除フラグの確認
	bool get_flag_erase() const;

	// ウィンドウのアクティブ状況を変更
	void set_active(bool const active_) {
		active = active_;
	}

	// ウィンドウを指定の位置に配置する
	void set_pos(Vec2 pos_);

	// ドラッグ可能状態の変更
	void set_draggable(bool const b);

	// ウィンドウ消去可能状態の変更
	void set_erasable(bool const b);

	// フォーカス可能状態の変更
	void set_focusable(bool const b);

	// 非フォーカス時に暗く表示するかどうかのフラグ
	void set_light_focus(bool const b);

	// 削除フラグのセット(自力でページを閉じる際などに利用)
	void set_flag_erase(bool const b);

	// void add_object(std::unique_ptr<GameObject> object);
};

