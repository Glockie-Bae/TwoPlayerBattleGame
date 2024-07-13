#pragma once
#include"Bullet.h"
#include"Animation.h"

extern Atlas atlas_sun;										//�չ⶯��ͼ��
extern Atlas atlas_sun_explode;								//�չⱬը����ͼ��

extern Camera main_camera;		

class SunBullet : public Bullet {
public: 
	SunBullet() 
	{
		m_Size.m_X = 96;
		m_Size.m_Y = 96;

		m_Damage = 20;

		// �����չ�ը������
		animation_idle.Set_Atlas(&atlas_sun);
		animation_idle.Set_Interval(50);

		// �����չ�ը����ը����
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
	const float gravity = 1e-3f;							// �չ�ը������

	Animation animation_idle;								// �չ�ը��Ĭ�϶���
	Animation animation_explode;							// �չ�ը����ը����
	Vector2D explode_render_offset;							// ��ը������Ⱦƫ��
};