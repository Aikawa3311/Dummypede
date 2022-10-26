#include "stdafx.h"
#include "Page_Light.h"

void Page_Light::Draw() const
{
}

void Page_Light::Update()
{
}

Page_Light::Page_Light()
	:WindowSystem(Scene::Size() - Size(250, 250), Size(200, 200), U"light")
{
}
