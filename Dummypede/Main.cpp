# include <Siv3D.hpp> // OpenSiv3D v0.6.3

#include "CG2D.h"
#include "AssetRegister.h"
#include "WindowSystem.h"
#include "WindowSystemManager.h"
#include "Desktop.h"
#include "GameControl.h"
#include "CursorDecorator.h"

#include "Page_CentipedeGame.h"
#include "Page_AYFABTU.h"

#include "Page_SelfIntroduction.h"
#include "Page_Eye.h"
#include "Page_Password.h"
// #include "Page_MukadeShell.h"
#include "Page_Dark.h"
#include "Page_AlotofFiles.h"
#include "Page_Myriapod.h"
#include "Page_MyriadTetrapod.h"
#include "Page_Door.h"
#include "Page_Boss.h"
#include "Page_LastPassword.h"
#include "Page_Opening.h"
#include "Page_Pigpen.h"
#include "Page_ISBN.h"
#include "Page_UnixTime.h"
#include "Page_ScoreServer.h"
#include "Page_UnixClock.h"
#include "Page_Ending.h"
#include "Page_Sunset.h"

// シェーダーの定数バッファ
struct PSPixelSize{
	Float2 pixelSize;
};

struct PSCounter {
	float counter;
};

void Main()
{
	GameControl::readme_change();

	// 背景の色を設定
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// 設定ファイルの読み込み
	INI const ini(U"config.ini");
	Size window_size(GameControl::base_size);
	if (ini) {
		if (!ini[U"Window.auto"].isEmpty() && Parse<int>(ini[U"Window.auto"]) != 0) {
			// 自動で解像度変更
			// モニタサイズを取得
			Size monitor_reso = System::GetCurrentMonitor().fullscreenResolution;
			if (window_size.x > monitor_reso.x || window_size.y > monitor_reso.y) {
				// 1200 x 800がモニターサイズを超過してしまう場合
				// 比率を保ちつつ、モニターサイズに収まるようにリサイズ
				double r = Min((double)monitor_reso.x / window_size.x, (double)monitor_reso.y / window_size.y);
				r -= 0.1;
				window_size.x = static_cast<int32>(window_size.x * r);
				window_size.y = static_cast<int32>(window_size.y * r);
			}
		}
		else {
			// width, heightの読み込み
			if (!ini[U"Window.width"].isEmpty()) {
				window_size.x = Clamp(Parse<int>(ini[U"Window.width"]), 800, 1920);
			}
			if (!ini[U"Window.height"].isEmpty()) {
				window_size.y = Clamp(Parse<int>(ini[U"Window.height"]), 600, 1080);
			}
		}
	}

	Window::Resize(window_size);
	Window::SetTitle(U"Dummypede");
	// Window::SetFullscreen(true);

	// もろもろのアセット登録
	AssetRegister::Regist();

	// シェーダー準備
	// PixelShader const ps = HLSL{ U"example/shader/hlsl/rgb_shift.hlsl", U"PS" };
	PixelShader const ps = HLSL{ Resource(U"shader/CRT.hlsl"), U"PS" };
	if (!ps) {
		throw Error{ U"Failed to load a shader file" };
	}

	// シェーダーに渡す定数バッファの準備
	// const ConstantBuffer<CRTShader> constant_buffer{ { (Float2{ 1.0f, 1.0f } / Scene::Size()) } };
	Float2 pixel_size = { (float)Scene::Width(), (float)Scene::Height() };
	// Float2 pixel_size = { (float)GameControl::base_size.x, (float)GameControl::base_size.y };
	const ConstantBuffer<PSPixelSize> constant_buffer1{ { pixel_size } };
	ConstantBuffer<PSCounter> constant_buffer2;

	// gameControlの準備
	// GameControl gamectrl;

	// ウィンドウ機能の準備
	WindowSystemManager manager;
	// 以下デバグ用 -----
	// manager.add_page(std::make_shared<Page_AYFABTU>(), false);
	// std::shared_ptr<Page_CentipedeGame> page_centipedegame = std::make_shared<Page_CentipedeGame>();
	// manager.add_page(page_centipedegame, false);
	// manager.set_page_centipedegame(page_centipedegame);
	// manager.add_page(std::make_shared<Page_MukadeShell>(manager), false);
	// manager.add_page(std::make_shared<Page_Password>(manager), false);
	// manager.add_page(std::make_shared<Page_SelfIntroduction>(manager));
	// manager.add_page(std::make_shared<Page_Dummypede>(manager));
	// manager.add_page(std::make_shared<Page_Dark>(manager));
	// manager.add_page(std::make_shared<Page_AlotofFiles>(manager));
	// manager.add_page(std::make_shared<Page_Dark2>(manager));
	// manager.add_page(std::make_shared<Page_MyriadTetrapod>(manager));
	// manager.add_page(std::make_shared<Page_Door>(manager));
	// manager.add_page(std::make_shared<Page_Boss>(manager));
	// manager.add_page(std::make_shared<Page_LastPassword>());
	// manager.add_page(std::make_shared<Page_Pigpen>());
	// manager.add_page(std::make_shared<Page_ISBN>(manager, U"ISBN"));
	// manager.add_page(std::make_shared<Page_Myriapod>(manager));
	// manager.add_page(std::make_shared<Page_UnixTime>());
	// manager.add_page(std::make_shared<Page_ScoreServer>());
	// manager.add_page(std::make_shared<Page_UnixClock>());
	// manager.add_page(std::make_shared<Page_Ending>());
	// manager.add_page(std::make_shared<Page_Sunset>());
	// -----

	manager.add_page(std::make_shared<Page_Opening>(manager), false);

	// Desktopを生成
	Desktop desktop(manager);

	// レンダーテクスチャの用意
	// MSRenderTexture msrt_scene(Scene::Size(), Palette::Black);
	MSRenderTexture msrt_scene(Size(GameControl::base_size), Palette::Black);
	/*BlendState msrt_blend(BlendState::Default2D);
	msrt_blend.src = Blend::SrcAlpha;
	msrt_blend.dst = Blend::DestAlpha;
	msrt_blend.srcAlpha = Blend::One;
	msrt_blend.dstAlpha = Blend::InvSrcAlpha;*/

	while (System::Update())
	{
		/*System::Sleep(100ms);
		ClearPrint();
		Print << Profiler::FPS();*/

		// マウスカーソルの位置を解像度に合わせる
		Transformer2D const transformer{ Mat3x2::Identity(), Mat3x2::Scale((double)window_size.x / GameControl::base_size.x, (double)window_size.y / GameControl::base_size.y) };

		if (KeyControl.down()) {
			GameControl::flag_shader ^= 1;
		}

		// 特にカーソル画像の変更命令が無い場合はnormalを維持
		// Cursor::RequestStyle(U"normal");
		Cursor::RequestStyle(CursorStyle::Hidden);
		GameControl::decorator.RequestStyle(U"normal");

		// 各Update処理
		desktop.Update();

		manager.Update();

		GameControl::decorator.Update();

		{
			// マルチサンプルレンダーテクスチャへの描画
			ScopedRenderTarget2D target(msrt_scene.clear(Palette::Black));
			// ScopedRenderTarget2D target(msrt_scene.clear(ColorF(0, 0, 0, 0)));
			// ScopedRenderStates2D renderstate(msrt_blend);
			
			desktop.Draw();
			manager.Draw();
			GameControl::decorator.Draw();
			GameControl::decorator.DrawCursor();
			
		}

		// 2d描画をフラッシュ、マルチサンプルレンダーテクスチャの内容を確定
		Graphics2D::Flush();
		// マルチサンプルテクスチャを通常の描画可能なテクスチャへ変更
		msrt_scene.resolve();

		{
			// レンダーテクスチャの内容をシェーダーを通して描画
			if (GameControl::flag_shader == true) {
				// シェーダーを使う場合：シェーダーに定数バッファを渡す
				Graphics2D::SetPSConstantBuffer(1, constant_buffer1);
				constant_buffer2->counter = Time::GetMillisec() / 1000.0f;
				Graphics2D::SetPSConstantBuffer(2, constant_buffer2);

				const ScopedCustomShader2D shader{ ps };
				msrt_scene.resized(window_size).draw();
			}
			else {
				msrt_scene.resized(window_size).draw();
			}
		}
	}
}
