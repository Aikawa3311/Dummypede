#include "stdafx.h"
#include "Page_DarkPageBase.h"

void Page_DarkPageBase::Draw() const{
	RectF(Vec2::Zero(), size).draw(Palette::Black);
	if (std::shared_ptr<Page_Light> p = manager.get_page_light().lock()) {
		Size s = p->get_size();
		Circle((p->get_pos() - pos).movedBy(s/2), s.x/2).draw(Palette::White);
		DrawDark();
	}
}

void Page_DarkPageBase::Update()
{
}

void Page_DarkPageBase::DrawDark() const{
}

Page_DarkPageBase::Page_DarkPageBase(WindowSystemManager & manager, Vec2 const& pos, String const & str)
	:WindowSystem(pos, Size(130, 130), str),
	manager(manager)
{
}
