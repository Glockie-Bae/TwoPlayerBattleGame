#pragma once
#include"Player.h"
#include"SunBullet.h"
#include"SunBulletEx.h"

extern Atlas atlas_sunflower_idle_left;						//向日葵朝向左的默认动画集
extern Atlas atlas_sunflower_idle_right;						//向日葵朝向右的默认动画集
extern Atlas atlas_sunflower_run_left;							//向日葵朝向左的奔跑动画集
extern Atlas atlas_sunflower_run_right;						//向日葵朝向右的奔跑动画集

extern Atlas atlas_sunflower_attack_ex_left;					//向日葵朝向左的特殊攻击动画集
extern Atlas atlas_sunflower_attack_ex_right;					//向日葵朝向右的特殊攻击动画集
extern Atlas atlas_sun_text;									//"日"文本动画图集

extern Atlas atlas_sunflower_die_left;							//向日葵朝向左的死亡动画集
extern Atlas atlas_sunflower_die_right;						//向日葵朝向右的死亡动画集

extern Player* player_1P;				
extern Player* player_2P;

class Sunflower : public Player {

public:
	Sunflower(bool facing_right = true) : Player(facing_right) {
		m_Animation_idle_left.Set_Atlas(&atlas_sunflower_idle_left);
		m_Animation_idle_right.Set_Atlas(&atlas_sunflower_idle_right);
		m_Animation_run_left.Set_Atlas(&atlas_sunflower_run_left);
		m_Animation_run_right.Set_Atlas(&atlas_sunflower_run_right);
		m_Animation_attack_ex_left.Set_Atlas(&atlas_sunflower_attack_ex_left);
		m_Animation_attack_ex_right.Set_Atlas(&atlas_sunflower_attack_ex_right);
		m_Animation_sun_text.Set_Atlas(&atlas_sun_text);
		m_Animation_die_left.Set_Atlas(&atlas_sunflower_die_left);
		m_Animation_die_right.Set_Atlas(&atlas_sunflower_die_right);

		m_Animation_idle_left.Set_Interval(75);
		m_Animation_idle_right.Set_Interval(75);
		m_Animation_run_left.Set_Interval(75);
		m_Animation_run_right.Set_Interval(75);
		m_Animation_attack_ex_left.Set_Interval(100);
		m_Animation_attack_ex_right.Set_Interval(100);
		m_Animation_die_left.Set_Interval(150);
		m_Animation_die_right.Set_Interval(150);
		 
		m_Animation_attack_ex_left.Set_Loop(false);
		m_Animation_attack_ex_right.Set_Loop(false);
		m_Animation_sun_text.Set_Loop(false);
		m_Animation_die_left.Set_Loop(false);
		m_Animation_die_right.Set_Loop(false);

		m_Animation_attack_ex_left.Set_CallBack([&]()
			{
				is_attacking_ex = false;
				is_sun_text_visible = false;
			});

		m_Animation_attack_ex_right.Set_CallBack([&]()
			{
				is_attacking_ex = false;
				is_sun_text_visible = false;
			});


		SetSize(96, 96);

		m_Attack_CD = 250;
	}
	~Sunflower() {}

	void OnUpdate(int delta) {
		Player::OnUpdate(delta);

		if (is_sun_text_visible)
			m_Animation_sun_text.On_Update(delta);
	}

	void OnDraw(const Camera& camera) {
		Player::OnDraw(camera);

		if (is_sun_text_visible) {
			Vector2D text_position;
			IMAGE* frame = m_Animation_sun_text.Get_Frame_Img();
			text_position.m_X = m_Position.m_X - (m_Size.m_X - frame->getwidth()) / 2;
			text_position.m_Y = m_Position.m_Y - frame->getheight();
			m_Animation_sun_text.On_Draw(camera, (int)text_position.m_X, (int)text_position.m_Y);
		}
	}

	void OnAttack() {
		Bullet* bullet = new SunBullet();

		// 将子弹位置设置在人物头顶
		Vector2D bullet_position;
		const Vector2D& bullet_size = bullet->GetSize();
		bullet_position.m_X = m_Position.m_X + (m_Size.m_X - bullet_size.m_X) / 2;
		bullet_position.m_Y = m_Position.m_Y;

		// 设置子弹位置和速度
		bullet->SetPosition(bullet_position);
		bullet->SetVelocity(is_facing_right ? velocity_sun : Vector2D(-velocity_sun.m_X, velocity_sun.m_Y));

		bullet->SetCollideTarget(m_PlayerID == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);

		bullet->SetCallBack([&]() {m_MP += 35; });

		bullet_list.push_back(bullet);
	}

	void OnAttackEx() {
		is_attacking_ex = true;
		is_sun_text_visible = true;

		m_Animation_sun_text.Reset();
		is_facing_right ? m_Animation_attack_ex_right.Reset() : m_Animation_attack_ex_left.Reset();

		Bullet* bullet = new SunBulletEx();
		Player* target_player = (m_PlayerID == PlayerID::P1 ? player_2P : player_1P);

		Vector2D bullet_position, bullet_velocity;
		const Vector2D& bullet_size = bullet->GetSize();
		const Vector2D& target_position = target_player->GetPosition();
		const Vector2D& target_size = target_player->GetSize();


		bullet_position.m_X = target_position.m_X + (target_size.m_X - bullet_size.m_X) / 2;
		bullet_position.m_Y = -m_Size.m_Y;

		bullet_velocity.m_X = 0;
		bullet_velocity.m_Y = speed_sun_ex;

		bullet->SetPosition(bullet_position);
		bullet->SetVelocity(bullet_velocity);

		bullet->SetCollideTarget(m_PlayerID == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);

		bullet->SetCallBack([&]() {m_MP += 50; });

		bullet_list.push_back(bullet);

		mciSendString(_T("play sun_text from 0"), NULL, 0, NULL);
	}

private:

	const float speed_sun_ex = 0.15f;					// 大型日光炸弹下落速度
	const Vector2D velocity_sun = { 0.25f, -0.5f };		// 小型日光炸弹抛射速度


	Animation m_Animation_sun_text;		// 头顶文本动画
	bool is_sun_text_visible = false;	// 是否显示头顶动画


};