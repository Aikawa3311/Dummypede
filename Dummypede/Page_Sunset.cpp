#include "stdafx.h"
#include "Page_Sunset.h"

void Page_Sunset::Draw() const
{
	// RectF(Vec2::Zero(), size).draw(Palette::Green);

	// rt.clear(ColorF(0, 0, 0, 0));
	// rt.clear(ColorF(1, 1, 1, 0));


	// 太陽 -----
	rt_sun.clear(ColorF(1, 1, 1, 0));
	BlendState bs(BlendState::Default2D);
	bs.srcAlpha = Blend::One;
	bs.dstAlpha = Blend::Zero;
	bs.opAlpha = BlendOp::Add;
	{
		ScopedRenderTarget2D const target(rt_sun);
		ScopedRenderStates2D const blend(bs);

		// グラデーションSun
		for (int i = 0; i < (int)tris.size(); ++i) {
			// tris[i].drawFrame(2, col1);
			Color p0col = col1.lerp(col3, Math::Map(tris[i].p0.y, sun.center.y - sun.r, sun.center.y + sun.r, 0.0, 1.0));
			Color p1col = col1.lerp(col3, Math::Map(tris[i].p1.y, sun.center.y - sun.r, sun.center.y + sun.r, 0.0, 1.0));
			Color p2col = col1.lerp(col3, Math::Map(tris[i].p2.y, sun.center.y - sun.r, sun.center.y + sun.r, 0.0, 1.0));
			tris[i].draw(p0col, p1col, p2col);
			// tris[i].draw(ColorF{ p0col , 0.5 }, ColorF{ p1col , 0.5 }, ColorF{ p2col , 0.5 });
		}

		// 黒Line
		{
			int line_n = 6;
			double thickness = 30;
			double line_end = sun.center.y - 20;				// lineの上側の終端
			double line_start = sun.center.y + sun.r;	// lineの上側のスタート位置
			double margin = (line_start - line_end) / line_n;
			double t = Periodic::Sawtooth0_1(3s);
			for (int i = 0; i < line_n; ++i) {
				double y = line_start - (t + i) * margin;
				RectF(Vec2(sun.center.x - sun.r, y), Vec2(sun.r * 2, thickness * Math::Map(y, line_end, line_start, 0.0, 1.0))).draw({ Palette::White, 0 });
			}
		}

		// 適当な星
		for (auto const& star : stars) {
			Circle circ = star;
			circ.r += Random();
			circ.draw();
		}

		FontAsset(U"BigLucida")(U"Take a break...").draw(Vec2(15, 45), Palette::White);
	}

	// ぼかしを入れる
	Shader::GaussianBlur(rt_sun, gaussianB1, rt_sun);
	Shader::Downsample(rt_sun, gaussianA4);
	Shader::GaussianBlur(gaussianA4, gaussianB4, gaussianA4);
	Shader::Downsample(gaussianA4, gaussianA8);
	Shader::GaussianBlur(gaussianA8, gaussianB8, gaussianA8);

	bs.srcAlpha = Blend::One;
	bs.dstAlpha = Blend::InvSrcAlpha;
	bs.opAlpha = BlendOp::Add;
	bs.src = Blend::SrcAlpha;
	bs.dst = Blend::InvSrcAlpha;
	bs.op = BlendOp::Add;
	{
		ScopedRenderTarget2D const target(rt_sun);
		ScopedRenderStates2D const blend(bs);

		gaussianA4.resized(size).draw(AlphaF(0.8));
		gaussianA8.resized(size).draw(AlphaF(0.8));
	}

	// 格子 -----
	rt_lattice.clear(ColorF(1, 1, 1, 0));
	{
		ScopedRenderTarget2D const target(rt_lattice);
		ScopedRenderStates2D const blend(bs);

		int num_horizon = 12, num_vertical = 60;
		double y_start = size.y + 50;
		double x_end_w = 800, x_start_w = 3800;
		double t = Periodic::Sawtooth0_1(10s);

		// ぼかし用に下地として薄いグラデーション色を仕込んでおく
		RectF(Vec2(0, y_end), Vec2(size.x, y_start - y_end)).draw(Arg::top = ColorF{ col_line1.lerp(Palette::White, 0.7), 1 }, Arg::bottom = ColorF{ col_line2.lerp(Palette::White, 0.4), 1 });

		// 横線
		for (int i = 0; i < num_horizon; ++i) {
			double y_ratio = EaseOutSine((i + t) / num_horizon);
			double x_w = Math::Map(y_ratio, 0.0, 1.0, x_start_w, x_end_w);
			// double y = Math::Map((double)i / num_horizon, 0.0, 1.0, y_start, y_end);
			double y = y_start - (y_ratio * (y_start - y_end));
			Vec2 draw_pos(size.x / 2.0 - x_w / 2.0, y);
			Line(draw_pos, draw_pos.movedBy(x_w, 0)).draw(line_thickness, col_line2.lerp(col_line1, y_ratio));
		}
		Line(Vec2(size.x / 2.0 - x_end_w / 2.0, y_end), Vec2(size.x / 2.0 + x_end_w / 2.0, y_end)).draw(line_thickness, col_line1);
		// 縦線
		for (int i = 0; i < num_vertical + 1; ++i) {
			Vec2 p1(size.x / 2.0 - x_end_w / 2.0, y_end);
			Vec2 p2(size.x / 2.0 - x_start_w / 2.0, y_start);
			Line(p1.movedBy(x_end_w / num_vertical * i, 0), p2.movedBy(x_start_w / num_vertical * i, 0)).draw(line_thickness, col_line1, col_line2);
		}
	}

	// ぼかしを入れる
	Shader::GaussianBlur(rt_lattice, gaussianB1, rt_lattice);
	Shader::Downsample(rt_lattice, gaussianA4);
	Shader::GaussianBlur(gaussianA4, gaussianB4, gaussianA4);
	{
		ScopedRenderTarget2D const target(rt_lattice);
		ScopedRenderStates2D const blend(bs);

		gaussianA4.resized(size).draw(AlphaF(0.8));
	}

	bs.srcAlpha = Blend::One;
	bs.dstAlpha = Blend::InvSrcAlpha;
	bs.opAlpha = BlendOp::Add;
	bs.src = Blend::SrcAlpha;
	bs.dst = Blend::InvSrcAlpha;
	bs.op = BlendOp::Add;
	// bs = BlendState::Default2D;

	{
		// レンダーターゲットをRenderTextureへ変更
		ScopedRenderTarget2D const target(rt);
		ScopedRenderStates2D const blend(bs);

		// 背景
		RectF(Vec2::Zero(), size).draw(Arg::top = col1.gamma(0.4), Arg::bottom = col3.gamma(0.4));
		RectF(Vec2::Zero(), size).draw({ Palette::Black, 0.4 });
		// RectF(Vec2::Zero(), size).draw(ColorF(1, 0, 0, 1));

		rt_sun.draw(ColorF(1, 1, 1, a));

		// ワイヤ
		//for (int i = 0; i < points.height(); ++i) {
		//	for (int j = 0; j < points.width(); ++j) {
		//		// Circle(points[i][j], 2).draw(Palette::White);
		//		if (j < points.width()  - 1) Line(points[i][j], points[i][j + 1]).draw(1.5, Palette::White);
		//		if (i < points.height() - 1) Line(points[i][j], points[i + 1][j]).draw(1.5, Palette::White);
		//	}
		//}
		rt_lattice.draw();
		rt_sun(RectF(0, 0, size.x, sun.center.y + sun.r - 40)).flipped().draw(Vec2(0, y_end), Arg::top = AlphaF(0.8), Arg::bottom = AlphaF(-1));
	}

	Graphics2D::Flush();
	rt.resolve();

	rt.draw();

	
}

void Page_Sunset::Update()
{
	// line_tの更新
	//line_t = Periodic::Sawtooth0_1(3s);

	//// pointの位置更新
	//double y_end = 400, y_start = size.y + 50;
	//double end_x_margin = 5, start_x_margin = 60;
	//for (int i = 0; i < points.height(); ++i) {
	//	double x_margin = Math::Map(i + line_t, 0.0, (double)points.height(), start_x_margin, end_x_margin);
	//	double x_draw_start = size.x / 2 - x_margin * points.width() / 2;
	//	double y = Math::Map(((double)i + line_t) / points.height(), 0, 1, y_start, y_end);
	//	// double y = Math::Map(EaseOutSine(((double)i + line_t) / points.height()), 0, 1, y_start, y_end);
	//	for (int j = 0; j < points.width(); ++j) {
	//		// points[i][j].x = x_draw_start + Math::Map(points.width() - j - t, 0, points.width(), end_x_margin, start_x_margin);
	//		points[i][j].x = x_draw_start + x_margin * j;
	//		points[i][j].y = y;
	//	}
	//}

	//for (int i = 0; i < points.width(); ++i) {
	//	points[points.height() - 1][i].x = (size.x / 2 - end_x_margin * points.width() / 2) + end_x_margin * i;
	//	points[points.height() - 1][i].y = y_end;
	//}

	// a = Clamp(a + Mouse::Wheel() * 0.1, 0.0, 1.0);
	//SimpleGUI::Slider(U"alpha : {:.2f}"_fmt(a), a, 0.0, 1.0, Vec2{ 10, 50 }, 100, 200);
}

Page_Sunset::Page_Sunset(Vec2 const& pos)
	: // WindowSystem(pos, Scene::Size() - (pos * 2).asPoint(), U"Sunset"),
	WindowSystem(pos, GameControl::base_size - (pos * 2).asPoint(), U"Sunset"),
	rt(size),
	rt_sun(size),
	rt_lattice(size),
	gaussianB1(size),
	gaussianA4(size / 4), gaussianB4(size / 4),
	gaussianA8(size / 8), gaussianB8(size / 8),
	col1(0xFF, 0xAF, 0xCC),
	col2(0xFF, 0xFF, 0xFF),
	col3(0xA2, 0xD2, 0xFF),
	col_line1(Palette::Deepskyblue),
	col_line2(Palette::Darkviolet),
	sun((size / 2).movedBy(0, -40), 150),
	points(70, 15),
	stars(20)
{
	col_line1 = col_line1.lerp(Palette::Black, 0.3);
	col_line2 = col_line2.lerp(Palette::Black, 0.3);
	Polygon circ = sun.asPolygon(reso);
	tris.reserve(circ.num_triangles());
	for (int i = 0; i < (int)circ.num_triangles(); ++i) {
		tris.emplace_back(circ.triangle(i));
	}
	// 適当な星
	for (int i = 0; i < (int)stars.size(); ++i) {
		// もしsunと被っていたら再生成する
		do {
			stars[i].center = RandomVec2(RectF(Vec2(0, 0), Vec2(size.x, sun.center.y + sun.r)));
		} while ((stars[i].center - sun.center).lengthSq() < sun.r * sun.r);
		stars[i].r = Random(1.0, 3.0);
	}
}
