#include "stdafx.h"
#include "Page_Video.h"

void Page_Video::Draw() const{
	video.draw(Vec2(0, 16));
}

void Page_Video::Update(){
	video.advance();
}

Page_Video::Page_Video():
	WindowSystem(Scene::CenterF() - Size(600, 400)/2, Size(600, 400), U"Trailer"),
	video(U"video/playthrough.mp4") {

}
