// Pageのテンプレート
#pragma once
#include "WindowSystem.h"

class Page_Sunset : public WindowSystem {
private:
	void Draw() const override;
	void Update() override;

	MSRenderTexture rt;
	RenderTexture rt_sun;
	RenderTexture rt_lattice;
	RenderTexture gaussianB1;
	RenderTexture gaussianA4, gaussianB4;
	RenderTexture gaussianA8, gaussianB8;

	double a = 1;
	double y_end = 400;	// 地平線の位置

	Color col1;
	Color col2;
	Color col3;
	Color col_line1;
	Color col_line2;
	double line_thickness = 3;

	Circle sun;
	double line_t = 0;

	int reso = 48;
	Array<Triangle> tris;
	Grid<Vec2> points;

	Array<Circle> stars;

public:
	Page_Sunset(Vec2 const& pos = Vec2(200, 100));
};
