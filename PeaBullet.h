#pragma once
#include"Bullet.h"
#include"Animation.h"

extern IMAGE img_peashooter;			// 豌豆子弹图片
extern Atlas atlas_pea_break;			// 豌豆子弹破碎动画


class PeaBullet : public Bullet {
public:
	PeaBullet() 
	{
		m_Size.m_X = 64, m_Size.m_Y = 64;

		m_Damage = 10;

		animation_break.Set_Atlas(&atlas_pea_break);
		animation_break.Set_Interval(100);
		animation_break.Set_Loop(false);
		animation_break.Set_CallBack([&]() {remove = true; });
	}
	~PeaBullet() {}

	// 更新豌豆子弹的破碎方法
	void OnCollide() {
		Bullet::OnCollide();

		// 随机播放子弹破碎的音效
		switch (rand() % 3)
		{
		case 0:
			mciSendString(_T("play pea_break_1 from 0"), NULL, 0, NULL);
			break;
		case 1:
			mciSendString(_T("play pea_break_2 from 0"), NULL, 0, NULL);
			break;
		case 2:
			mciSendString(_T("play pea_break_3 from 0"), NULL, 0, NULL);
			break;
		default:
			break;
		}
	}

	void OnUpdate(int delta) {
		m_Position.m_X += m_Velocity.m_X * (float)delta;

		// 子弹无效后，可以播放破碎动画
		if (!valid)
			animation_break.On_Update(delta);

		// 判断子弹是否离开画面
		if (Check_If_Exceeds_Screen()) {
			remove = true;
		}
	}

	void OnDraw(const Camera& camera) const {
		if (valid)
			PutImage_Alpha(camera, (int)m_Position.m_X, (int)m_Position.m_Y, &img_peashooter);
		else
			animation_break.On_Draw(camera, (int)m_Position.m_X, (int)m_Position.m_Y);

		Bullet::OnDraw(camera);
	}

private:
	Animation animation_break;		// 豌豆子弹破碎动画
};