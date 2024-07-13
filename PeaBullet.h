#pragma once
#include"Bullet.h"
#include"Animation.h"

extern IMAGE img_peashooter;			// �㶹�ӵ�ͼƬ
extern Atlas atlas_pea_break;			// �㶹�ӵ����鶯��


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

	// �����㶹�ӵ������鷽��
	void OnCollide() {
		Bullet::OnCollide();

		// ��������ӵ��������Ч
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

		// �ӵ���Ч�󣬿��Բ������鶯��
		if (!valid)
			animation_break.On_Update(delta);

		// �ж��ӵ��Ƿ��뿪����
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
	Animation animation_break;		// �㶹�ӵ����鶯��
};