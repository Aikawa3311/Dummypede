// Pageのテンプレート
#pragma once
#include "WindowSystem.h"

#include "GameControl.h"

class Page_UnixClock : public WindowSystem {
private:
	void Draw() const override;
	void Update() override;

	DateTime datetime;
	Circle circle;

	// 年針・月針・日針
	Array<Quad> hands;
	// 各針の角度(degree)
	Array<double> hands_angle;
	// 各針のグラブ判定
	Array<bool> hands_grab;

	// 中心の四角形の大きさ
	RoundRect digital_frame;

	// リンクの判定
	RectF link_unix;

	std::pair<int, int> year_range;

	// 符号付き32bitでUnix時間(日本標準時)を計算
	int calc_unix_time() const;

	// 各針のQuadを計算
	void calc_hand_quad();

	// 各角度から日時を計算
	void calc_datetime_from_angle();

	// 針を掴んでいるかどうかの判定など
	void grab_hand();

	// 針のアングル変更
	void update_hand_angle();

public:
	Page_UnixClock();


};
