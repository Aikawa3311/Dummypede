#pragma once
#include <Siv3d.hpp>

// カーソルに効果を付与するアイテムの基底クラス
class CursorBase{
public:
	virtual void Draw() const = 0;
	virtual void Update() = 0;
	
};

