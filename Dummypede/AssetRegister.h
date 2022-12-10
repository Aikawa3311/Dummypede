#pragma once
#include <Siv3D.hpp>

class AssetRegister {
public:
	static void Regist() {
		// --------------------------------------------
		// フォントアセット
		// --------------------------------------------
		// Regular
		FontAsset::Register(U"Regular", 20, Typeface::Medium);													// AYFABTUのYou should...のメッセージなど
		FontAsset::Register(U"SmallRegular", 16, Typeface::Regular);											// UnixTimeページの日付表記など
		FontAsset::Register(U"BoldRegular", 20, Typeface::Bold);												// 寄付のお願いなど
		FontAsset::Register(U"BigRegular", 30, Typeface::Medium);												// パスワードページの合言葉の表記など
		FontAsset::Register(U"HugeRegular", 50, Typeface::Medium);												// ISBNページの記事タイトル部分
		FontAsset::Register(U"RegularBit", 22, Typeface::Medium, FontStyle::Bitmap);							// CentipedeGameのLEFT CLICK TO STARTなど
		FontAsset::Register(U"BigBit", 24, Typeface::Regular, FontStyle::Bitmap);								// CentipedeGameのLEFT CLICK TO STARTなど
		FontAsset::Register(U"HugeBit", 50, Typeface::Medium, FontStyle::Bitmap);								// CentipedeGameのタイトル画面など
		// o ロックンロール
		FontAsset::Register(U"WindowTitle", 16, Resource(U"font/RocknRollOne-Regular.ttf"));					// ウィンドウのタイトル
		// o DotGothic
		FontAsset::Register(U"SmallDotBold", 14, Resource(U"font/DotGothic16-Regular.ttf"), FontStyle::Bold);	// デスクトップアイコン名など
		FontAsset::Register(U"SmallDot", 16, Resource(U"font/DotGothic16-Regular.ttf"));						// AYFABTUのYou should...のメッセージなど
		FontAsset::Register(U"RegularDot", 18, Resource(U"font/DotGothic16-Regular.ttf"));						// AYFABTUのYou should...のメッセージなど
		FontAsset::Register(U"BigDot", 22, Resource(U"font/DotGothic16-Regular.ttf"), FontStyle::Bold);			// スコアボード
		FontAsset::Register(U"HugeDot", 50, Resource(U"font/DotGothic16-Regular.ttf"), FontStyle::Bitmap);		// Only 1 Webの題字など
		FontAsset::Register(U"ExtraHugeDot", 100, Resource(U"font/DotGothic16-Regular.ttf"));					// BossのGameoverの表示など
		// - Lucida
		FontAsset::Register(U"HugeLucida", 70, FileSystem::GetFolderPath(SpecialFolder::SystemFonts) + U"Palab.ttf");							// 404ページの404表記など
		FontAsset::Register(U"BigLucida", 40, FileSystem::GetFolderPath(SpecialFolder::SystemFonts) + U"Palab.ttf");							// 404ページの404表記など
		// - Edwardian
		// FontAsset::Register(U"BigEdwardian", 50, Resource(U"font/edwardian.TTF"));								// 自己紹介ページのトップ
		// - MS明朝
		FontAsset::Register(U"RegularThinMintyo", 20, FileSystem::GetFolderPath(SpecialFolder::SystemFonts) + U"msmincho.ttc");	// mikipedia本文
		// - HG明朝
		FontAsset::Register(U"RegularMintyo", 20, FileSystem::GetFolderPath(SpecialFolder::SystemFonts) + U"BIZ-UDMinchoM.ttc");	// 404ページ本文
		FontAsset::Register(U"SmallMintyo", 16, FileSystem::GetFolderPath(SpecialFolder::SystemFonts) + U"BIZ-UDMinchoM.ttc");		// 暗闇ページのpassword beginの文言
		FontAsset::Register(U"HugeMintyo", 50, FileSystem::GetFolderPath(SpecialFolder::SystemFonts) + U"BIZ-UDMinchoM.ttc");		// EndingのEnd表記
		// - Console
		FontAsset::Register(U"RegularConsol", 20, FileSystem::GetFolderPath(SpecialFolder::SystemFonts) + U"consola.ttf");			// myriapodの時間表記など
		// - Imprish
		// FontAsset::Register(U"BigImprisha", 40, Resource(U"font/IMPRISHA.TTF"));								// ISBNページのフォント
		// o DSEG
		FontAsset::Register(U"RegularDSEG", 28, Resource(U"font/DSEG7ClassicMini-Bold.ttf"));					// UNIXTIMEなど

		// --------------------------------------------
		// 画像アセット
		// --------------------------------------------
		// アイコン画像
		// ウィンドウ
		TextureAsset::Register(U"close", 0xf00d_icon, 18);
		// Centipede関連
		TextureAsset::Register(U"file_feed0", 0xf15b_icon, 40);
		TextureAsset::Register(U"file_feed1", 0xf1c7_icon, 40);
		TextureAsset::Register(U"file_feed2", 0xf1c5_icon, 40);
		TextureAsset::Register(U"file_feed3", 0xf15c_icon, 40);
		TextureAsset::Register(U"file_feed4", 0xf1c8_icon, 40);
		TextureAsset::Register(U"bio", 0xf780_icon, 40);
		TextureAsset::Register(U"file_feed_regular0", U"icon/file-audio-regular.png");
		TextureAsset::Register(U"feed_food", 0xf2e7_icon, 30);

		// カスタムカーソル
		TextureAsset::Register(U"cursor_normal", Resource(U"image/cursor.png"));
		TextureAsset::Register(U"cursor_hand", Resource(U"image/cursor_hand.png"));
		TextureAsset::Register(U"cursor_grab1", Resource(U"image/cursor_grab1.png"));
		TextureAsset::Register(U"cursor_grab2", Resource(U"image/cursor_grab2.png"));
		TextureAsset::Register(U"cursor_i", Resource(U"image/cursor_i.png"));

		// 自己紹介ページなどで使うアイコン
		TextureAsset::Register(U"selfintroduction_0", 0xf0c7_icon, 30);
		TextureAsset::Register(U"selfintroduction_1", 0xf188_icon, 30);
		TextureAsset::Register(U"selfintroduction_2", 0xf044_icon, 30);
		TextureAsset::Register(U"selfintroduction_3", 0xf07c_icon, 30);
		TextureAsset::Register(U"selfintroduction_4", 0xf0c4_icon, 30);
		TextureAsset::Register(U"selfintroduction_5", 0xf3ed_icon, 30);
		TextureAsset::Register(U"selfintroduction_6", 0xf1b2_icon, 30);
		TextureAsset::Register(U"selfintroduction_7", 0xf70b_icon, 30);
		TextureAsset::Register(U"selfintroduction_8", 0xf163_icon, 30);
		TextureAsset::Register(U"selfintroduction_9", 0xf780_icon, 30);
		TextureAsset::Register(U"selfintroduction_twitter", 0xf099_icon, 30);
		TextureAsset::Register(U"selfintroduction_youtube", 0xf167_icon, 30);

		// 自己紹介ページのSelfintroductionの文字
		TextureAsset::Register(U"selfintroduction", Resource(U"image/selfintroduction.png"));

		// DummypedeからDarkページへのショートカットアイコン
		TextureAsset::Register(U"shortcut", 0xf35d_icon, 30);

		// DesktopIcon関連
		// TextureAsset::Register(U"Shortcut", 0xf26b_icon, 20);
		// TextureAsset::Register(U"Only1Web", 0xf015_icon, 40);
		// TextureAsset::Register(U"Only1Web", 0xe163_icon, 40);
		// TextureAsset::Register(U"Only1Web", 0xf26b_icon, 40);
		TextureAsset::Register(U"Only1Web", 0xf57e_icon, 40);

		// MyriadTetrapodのドア
		TextureAsset::Register(U"DoorClosed", 0xf52a_icon, 30);

		// Page_Doorの巨大ドア
		TextureAsset::Register(U"BigDoorClosed", 0xf52a_icon, 200);
		TextureAsset::Register(U"BigDoorOpen", 0xf52b_icon, 200);
		TextureAsset::Register(U"Key", 0x30d_icon, 40);

		// 各ページのアクセント関連
		TextureAsset::Register(U"Search", 0xf002_icon, 160);
		TextureAsset::Register(U"MiniBoss", 0xf0ac_icon, 30);
		TextureAsset::Register(U"MikipediaIcon", 0xf57e_icon, 50);
		TextureAsset::Register(U"MikipediaSearch", 0xf002_icon, 20);
		TextureAsset::Register(U"Smile", 0xf118_icon, 30);

		// その他画像系
		TextureAsset::Register(U"ayfabtu", Resource(U"image/mukade.PNG"));
		TextureAsset::Register(U"mukade_feeder", Resource(U"image/mukade2.png"));
		TextureAsset::Register(U"elk", Resource(U"image/elk.png"));
		TextureAsset::Register(U"eye1", Resource(U"image/eye1.PNG"));
		TextureAsset::Register(U"eye2", Resource(U"image/eye2.PNG"));
		TextureAsset::Register(U"eye3", Resource(U"image/eye3.PNG"));
		TextureAsset::Register(U"eye4", Resource(U"image/eye4.PNG"));
		TextureAsset::Register(U"eye5", Resource(U"image/eye5.PNG"));
		TextureAsset::Register(U"eye6", Resource(U"image/eye6.PNG"));
		TextureAsset::Register(U"numbers", Resource(U"image/numbers.PNG"));
		TextureAsset::Register(U"arrow", Resource(U"image/arrow.PNG"));
		TextureAsset::Register(U"Sword", Resource(U"image/sword.PNG"));
		TextureAsset::Register(U"Pigpen", Resource(U"image/pigpen.PNG"));
		TextureAsset::Register(U"Mlogo", Resource(U"image/M.png"));

		// bossの画像
		TextureAsset::Register(U"eye_black1", Resource(U"image/eye_black1.png"));
		TextureAsset::Register(U"eye_black2", Resource(U"image/eye_black2.png"));
		TextureAsset::Register(U"eye_black3", Resource(U"image/eye_black3.png"));
		TextureAsset::Register(U"eye_black4", Resource(U"image/eye_black4.png"));
		TextureAsset::Register(U"eye_black5", Resource(U"image/eye_black5.png"));
		TextureAsset::Register(U"eye_black6", Resource(U"image/eye_black6.png"));
		TextureAsset::Register(U"boss", 0xf0ac_icon, 100);

		// Staffroll用
		TextureAsset::Register(U"staffroll_pen", 0xf15c_icon, 50);
		TextureAsset::Register(U"staffroll_program", 0xf1c9_icon, 50);
		TextureAsset::Register(U"staffroll_image", 0xf1c5_icon, 50);
		TextureAsset::Register(U"staffroll_audio", 0xf1c7_icon, 50);
		TextureAsset::Register(U"staffroll_font", 0xf031_icon, 50);
		TextureAsset::Register(U"staffroll_testplayer", 0xf007_icon, 50);

		// new factory(https://new-factory.jp/)の素材
		TextureAsset::Register(U"tetra", Resource(U"image/tetra.jpg"));

		// --------------------------------------------
		// 効果音アセット
		// --------------------------------------------
		AudioAsset::Register(U"daon", Resource(U"sound/daon.wav"));
		AudioAsset::Register(U"catsu", Resource(U"sound/catsu.mp3"));
		AudioAsset::Register(U"message", Resource(U"sound/message.wav"));
		AudioAsset::Register(U"enter", Resource(U"sound/enter.mp3"));
		AudioAsset::Register(U"enter2", Resource(U"sound/enter2.mp3"));
		AudioAsset::Register(U"cancel", Resource(U"sound/cancel.mp3"));
		AudioAsset::Register(U"eyeappear", Resource(U"sound/eyeappear.mp3"));
		AudioAsset::Register(U"type", Resource(U"sound/typing2.mp3"));
		// AudioAsset::Register(U"type", Resource(U"sound/catsu.mp3"));
		AudioAsset::Register(U"beam", Resource(U"sound/beam.mp3"));
		AudioAsset::Register(U"charge", Resource(U"sound/eyecharge.mp3"));
		AudioAsset::Register(U"door_open", Resource(U"sound/door_open2.mp3"));
		// AudioAsset::Register(U"scanning", Resource(U"sound/scanning.mp3"));
		AudioAsset::Register(U"scanning", Resource(U"sound/scanning3.mp3"), Loop::Yes);

		// 剣
		AudioAsset::Register(U"sword", Resource(U"sound/sword1.mp3"));

		// pc音
		AudioAsset::Register(U"pc", Resource(U"sound/pc3.wav"), Loop::Yes);
		AudioAsset::Register(U"pc_end", Resource(U"sound/pc_end.mp3"));
		AudioAsset::Register(U"pc_start", Resource(U"sound/pc_start_fade.mp3"));

		// --------------------------------------------
		// カスタムカーソルの登録(現在未使用)
		// --------------------------------------------
		Image image(Resource(U"image/cursor.png"));
		Cursor::RegisterCustomCursorStyle(U"normal", image);
		image = Image(Resource(U"image/cursor_hand.png"));
		Cursor::RegisterCustomCursorStyle(U"hand", image, Point(5, 0));
		image = Image(Resource(U"image/cursor_grab1.png"));
		Cursor::RegisterCustomCursorStyle(U"grab1", image);
		image = Image(Resource(U"image/cursor_grab2.png"));
		Cursor::RegisterCustomCursorStyle(U"grab2", image);

	}
};
