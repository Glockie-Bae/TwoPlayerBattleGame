#pragma once
#include"Util.h"

#include<graphics.h>


class StatusBar {
public:
	StatusBar() {}
	~StatusBar() {}

	void SetAvatar(IMAGE* img) {
		img_avatar = img;
	}

	void SetPosition(int x, int y) {
		Position.x = x;
		Position.y = y;
	}

	void SetHP(int hp) {
		HP = hp;
	}

	void SetMP(int mp) {
		MP = mp;
	}

	void OnDraw() {
		PutImage_Alpha(Position.x, Position.y, img_avatar);

		setfillcolor(RGB(5, 5, 5));
		solidroundrect(Position.x + 100, Position.y + 10, Position.x + 100 + width + 3 * 2, Position.y + 36, 8, 8);
		solidroundrect(Position.x + 100, Position.y + 45, Position.x + 100 + width + 3 * 2, Position.y + 71, 8, 8);

		setfillcolor(RGB(67, 47, 47));
		solidroundrect(Position.x + 100, Position.y + 10, Position.x + 100 + width + 3, Position.y + 33, 8, 8);
		solidroundrect(Position.x + 100, Position.y + 45, Position.x + 100 + width + 3, Position.y + 68, 8, 8);

		float hp_bar_width = width * max(0, HP) / 100.0f;
		float mp_bar_width = width * min(100, MP) / 100.0f;

		setfillcolor(RGB(197, 61, 67));
		solidroundrect(Position.x + 100, Position.y + 10, Position.x + 100 + (int)hp_bar_width + 3, Position.y + 33, 8, 8);

		setfillcolor(RGB(83, 131, 195));
		solidroundrect(Position.x + 100, Position.y + 45, Position.x + 100 + (int)mp_bar_width + 3, Position.y + 68, 8, 8);
	}

private:
	const int width = 275;			// 状态条宽度

private:
	int HP = 0;						// 需要显示的生命值
	int MP = 0;						// 需要显示的能量值
	POINT Position = { 0 };			// 渲染位置
	IMAGE* img_avatar = nullptr;	// 角色头像图片
};