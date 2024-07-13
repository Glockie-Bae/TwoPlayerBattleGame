#pragma once
#include"Bullet.h"
#include"Animation.h"

extern Atlas atlas_sun;										//日光动画图集
extern Atlas atlas_sun_explode;								//日光爆炸动画图集

extern Camera main_camera;		

class SunBullet : public Bullet {
public: 
	SunBullet() 
	{
		m_Size.m_X = 96;
		m_Size.m_Y = 96;

		m_Damage = 20;

		// 构造日光炸弹动画
		animation_idle.Set_Atlas(&atlas_sun);
		animation_idle.Set_Interval(50);

		// 构造日光炸弹爆炸动画
		animation_explode.Set_Atlas(&atlas_sun_explode);
		animation_explode.Set_Interval(50);
		animation_explode.Set_Loop(false);
		animation_explode.Set_CallBack([&]() {remove = true; });

		IMAGE* frame_idle = animation_idle.Get_Frame_Img();
		IMAGE* frame_explode = animation_explode.Get_Frame_Img();
		explode_render_offset.m_X = (frame_idle->getwidth() - frame_explode->getwidth()) / 2.0f;
		explode_render_offset.m_Y = (frame_idle->getheight() - frame_explode->getheight()) / 2.0f;
		
	}
	~SunBullet() {}

	void OnCollide() {
		Bullet::OnCollide();

		main_camera.Shake(5, 250);

		mciSendString(_T("play sun_explode from 0"), NULL, 0, NULL);

	}

	void OnUpdate(int delta) {
		if (valid) {
			m_Velocity.m_Y += delta * gravity;
			m_Position += m_Velocity * (float)delta;
		}

		if (!valid) {
			animation_explode.On_Update(delta);
		}
		else {
			animation_idle.On_Update(delta);
		}

		if (Check_If_Exceeds_Screen()) {
			remove = true;
		}
	}

	void OnDraw(const Camera& camera) const {
		if (valid) {
			animation_idle.On_Draw(camera, m_Position.m_X, m_Position.m_Y);
		}
		else {
			animation_explode.On_Draw(camera, 
				(int)(m_Position.m_X + explode_render_offset.m_X),
				(int)(m_Position.m_Y + explode_render_offset.m_Y));
		}

		Bullet::OnDraw(camera);

	}

	

private:
	const float gravity = 1e-3f;							// 日光炸弹重力

	Animation animation_idle;								// 日光炸弹默认动画
	Animation animation_explode;							// 日光炸弹爆炸动画
	Vector2D explode_render_offset;							// 爆炸动画渲染偏移
};