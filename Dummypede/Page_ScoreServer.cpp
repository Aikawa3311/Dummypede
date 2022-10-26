#include "stdafx.h"
#include "Page_ScoreServer.h"

void Page_ScoreServer::Draw() const {
	RectF(Vec2::Zero(), size).draw(Palette::Black);
	FontAsset(U"BigRegular")(U"- Centipede Scoreboard -").drawAt(Vec2(size.x / 2, 50), Palette::Green);

	bool flag_you = false;
	for (int i = 0; i < (int)players.size(); ++i) {
		FontAsset(U"BigDot")((i < 9 ? U" " : U"") + Format(i + 1)).draw(Arg::topLeft = Vec2(10, i * 30 + 80), Palette::Green);

		FontAsset(U"BigDot")(std::get<0>(players[i])).draw(Arg::topLeft = Vec2(45, i * 30 + 80), Palette::Green);
		if (std::get<1>(players[i]) == -1) {
			FontAsset(U"BigDot")(U"-").draw(Arg::topRight = Vec2(130, i * 30 + 80), Palette::Green);
		}
		else {
			FontAsset(U"BigDot")(Format(std::get<1>(players[i]))).draw(Arg::topRight = Vec2(140, i * 30 + 80), Palette::Green);
		}
		FontAsset(U"BigDot")(std::get<2>(players[i])).draw(Arg::topLeft = Vec2(170, i * 30 + 80), Palette::Green);
	}
}

void Page_ScoreServer::Update() {
	
}

void Page_ScoreServer::set_players(){
	players[0] = std::make_tuple(U"WOW", 115, U"piece of cake");
	players[1] = std::make_tuple(U"MUL", 16, U"cheater");
	players[2] = std::make_tuple(U"FOX", 11, U"kuso");
	players[3] = std::make_tuple(U"XXX", 8, U"bad rng");
	players[4] = std::make_tuple(U"EEZ", 0, U"mouse didn't respond");
	players[5] = std::make_tuple(U"XXX", -1, U"");
	players[6] = std::make_tuple(U"XXX", -1, U"");
	players[7] = std::make_tuple(U"XXX", -1, U"");
	players[8] = std::make_tuple(U"XXX", -1, U"");
	players[9] = std::make_tuple(U"XXX", -1, U"");
}

Page_ScoreServer::Page_ScoreServer()
	:WindowSystem(Vec2(400, 0), Size(420, 400), U"centipede score server"),
	players(10){
	set_players();
}
