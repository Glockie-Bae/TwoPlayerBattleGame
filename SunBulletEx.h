#pragma once
#include"Bullet.h"
#include"Animation.h"

extern Atlas atlas_sun_ex;										//�����չ�ͼ��
extern Atlas atlas_sun_ex_explode;								//�����չⱬըͼ��

extern Camera main_camera;

class SunBulletEx : public Bullet {
public:
	SunBulletEx() 
	{
		m_Size.m_X = 288;
		m_Size.m_Y = 288;

		m_Damage = 20;

		animation_idle.Set_Atlas(&atlas_sun_ex);
		animation_idle.Set_Interval(50);

		animation_explode.Set_Atlas(&atlas_sun_ex_explode);
		animation_explode.Set_Interval(50);
		animation_explode.Set_Loop(false);
		animation_explode.Set_CallBack([&]() {return remove = true; });

		IMAGE* frame_idle = animation_idle.Get_Frame_Img();
		IMAGE* frame_explode = animation_explode.Get_Frame_Img();
		explode_render_offset.m_Y = (frame_explode->getheight() - frame_idle->getheight()) / 2;
		explode_render_offset.m_X = (frame_explode->getwidth() - frame_idle->getwidth()) / 2;
	}

	~SunBulletEx() {}

	
	void OnCollide() {
		Bullet::OnCollide();

		main_camera.Shake(20, 250);

		mciSendString(_T("play sun_explode_ex from 0"), NULL, 0, NULL);
	}

	// �չ��ը�� �Ա߽���ײΪ����׼�� ����ͨը������������
	bool CheckCollision(const Vector2D& position, const Vector2D& size) {
		bool is_collide_x = (max(m_Position.m_X + m_Size.m_X, position.m_X + size.m_X) - min(m_Position.m_X, position.m_X)) <= (m_Size.m_X + size.m_X);
		bool is_collide_y = (max(m_Position.m_Y + m_Size.m_Y, position.m_Y + size.m_Y) - min(m_Position.m_Y, position.m_Y)) <= (m_Size.m_Y + size.m_Y);

		return is_collide_x && is_collide_y;
	}

	void OnUpdate(int delta) {
		if (valid) {
			m_Position += m_Velocity * (float)delta;
		}
		
		if (!valid) {
			animation_explode.On_Update(delta);
		}
		else
			animation_idle.On_Update(delta);

		if (Check_If_Exceeds_Screen())
			remove = true;
	}

	void OnDraw(const Camera& camera) const {
		if (valid) {
			animation_idle.On_Draw(camera, m_Position.m_X, m_Position.m_Y);
		}
		else {
			animation_explode.On_Draw(camera, (int)(m_Position.m_X + explode_render_offset.m_X), (int)(m_Position.m_Y + explode_render_offset.m_Y));
		}

		Bullet::OnDraw(camera);

	}


private:
	Animation animation_idle;					// �չ��ը������
	Animation animation_explode;					// �չ��ը����ը����
	Vector2D explode_render_offset;				// ��ը����λ��ƫ��
};
