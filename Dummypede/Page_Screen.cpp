#include "stdafx.h"
#include "Page_Screen.h"

void Page_Screen::Draw() const{
	RectF(Vec2::Zero(), size).draw(col);
}

void Page_Screen::Update(){
	col = Color((int)pos.x % 256, (int)pos.y % 256, (int)(pos.x + pos.y) % 256);
	if (pos.x + size.x > Scene::Width()) {
		dir.x = -1;
	}
	else if (pos.x <= 0) {
		dir.x = 1;
	}
	if (pos.y + size.y > Scene::Height()) {
		dir.y = -1;
	}
	else if (pos.y <= 0) {
		dir.y = 1;
	}
	moveBy(dir * Scene::DeltaTime() * spd);
}

Page_Screen::Page_Screen()
	:WindowSystem(Vec2(400, 400), Size(300, 300), U"screen"),
	spd(30),
	dir(1, -1){
}

Color Page_Screen::get_color() const{
	return col;
}
