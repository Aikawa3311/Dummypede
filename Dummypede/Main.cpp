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

	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });
	Window::Resize(1200, 800);
	Window::SetTitle(U"Dummypede");
	// Window::SetFullscreen(true);

	// もろもろのアセット登録
	// FontAsset::Register(U"WindowTitle", 16, U"example/font/RocknRoll/RocknRollOne-Regular.ttf");
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
	RenderTexture rt_scene(Scene::Size(), Palette::Black);
	MSRenderTexture msrt_scene(Scene::Size(), Palette::Black);

	while (System::Update())
	{
		/*System::Sleep(100ms);
		ClearPrint();
		Print << Profiler::FPS();*/

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
			// レンダーテクスチャへの描画
			/*ScopedRenderTarget2D target(rt_scene);
			rt_scene.clear(Palette::Black);
			desktop.Draw();
			manager.Draw();
			GameControl::decorator.Draw();
			GameControl::decorator.DrawCursor();*/
		}

		{
			// マルチサンプルレンダーテクスチャへの描画
			ScopedRenderTarget2D target(msrt_scene);
			rt_scene.clear(Palette::Black);
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
				msrt_scene.draw();
			}
			else {
				msrt_scene.draw();
			}
		}
	}
}
