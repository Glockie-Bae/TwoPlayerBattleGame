#pragma once
#include"Player.h"
#include"PeaBullet.h"

extern Atlas atlas_peashooter_idle_left;						//豌豆射手朝向左的默认动画集
extern Atlas atlas_peashooter_idle_right;						//豌豆射手朝向右的默认动画集
extern Atlas atlas_peashooter_run_left;							//豌豆射手朝向左的奔跑动画集
extern Atlas atlas_peashooter_run_right;						//豌豆射手朝向右的奔跑动画集
extern Atlas atlas_peashooter_attack_ex_left;					//豌豆射手朝向左的特殊攻击动画集
extern Atlas atlas_peashooter_attack_ex_right;					//豌豆射手朝向右的特殊攻击动画集
extern Atlas atlas_peashooter_die_left;						//豌豆射手朝向左的死亡动画集
extern Atlas atlas_peashooter_die_right;						//豌豆射手朝向右的死亡动画集

class Peashooter : public Player {
public:
	Peashooter(bool facing_right = true) : Player(facing_right){
		m_Animation_idle_left.Set_Atlas(&atlas_peashooter_idle_left);
		m_Animation_idle_right.Set_Atlas(&atlas_peashooter_idle_right);
		m_Animation_run_left.Set_Atlas(&atlas_peashooter_run_left);
		m_Animation_run_right.Set_Atlas(&atlas_peashooter_run_right);
		m_Animation_attack_ex_left.Set_Atlas(&atlas_peashooter_attack_ex_left);
		m_Animation_attack_ex_right.Set_Atlas(&atlas_peashooter_attack_ex_right);
		m_Animation_die_left.Set_Atlas(&atlas_peashooter_die_left);
		m_Animation_die_right.Set_Atlas(&atlas_peashooter_die_right);
		
		m_Animation_idle_left.Set_Interval(75);
		m_Animation_idle_right.Set_Interval(75);
		m_Animation_run_left.Set_Interval(75);
		m_Animation_run_right.Set_Interval(75);
		m_Animation_attack_ex_left.Set_Interval(75);
		m_Animation_attack_ex_right.Set_Interval(75);
		m_Animation_die_left.Set_Interval(150);
		m_Animation_die_right.Set_Interval(150);

		m_Animation_die_left.Set_Loop(false);
		m_Animation_die_right.Set_Loop(false);

		SetSize(96, 96);

		timer_atrtack_ex.SetWaitTime(attack_ex_duration);
		timer_atrtack_ex.SetOneShot(true);
		timer_atrtack_ex.SetCallBack([&]()
			{
				is_attacking_ex = false;
			});

		timer_spwan_pea_ex.SetWaitTime(100);
		timer_spwan_pea_ex.SetCallBack([&]()
			{
				spawn_pea_bullet(speed_pea_ex);
			});
		
		m_Attack_CD = 100;

	}
	~Peashooter() {}

	void OnUpdate(int delta) {

		Player::OnUpdate(delta);

		if (is_attacking_ex) {
			main_camera.Shake(5, 100);
			timer_atrtack_ex.OnUpDate(delta);
			timer_spwan_pea_ex.OnUpDate(delta);
		}

	}

	void OnAttack() {
		spawn_pea_bullet(speed_pea);

		switch (rand() % 2)
		{
		case 0:
			mciSendString(_T("Play pea_shoot_1 from 0"), NULL, 0, NULL);
			break;
		case 1:
			mciSendString(_T("Play pea_shoot_2 from 0"), NULL, 0, NULL);
			break;
		default:
			break;
		}
	}

	void OnAttackEx() {
		is_attacking_ex = true;
		timer_atrtack_ex.Restart();

		is_facing_right ? m_Animation_attack_ex_right.Reset() : m_Animation_attack_ex_left.Reset();

		mciSendString(_T("play pea_shoot_ex from 0"), NULL, 0, NULL);
	}

private:
	const float speed_pea = 0.75f;			// 普通豌豆子弹攻击速度
	const float speed_pea_ex = 1.5f;		// 特殊攻击豌豆子弹速度
	const int attack_ex_duration = 2500;	// 特殊攻击状态持续时间

	Timer timer_atrtack_ex;			// 特殊攻击状态定时器
	Timer timer_spwan_pea_ex;		// 豌豆子弹发射定时器

private:
	void spawn_pea_bullet(float speed) {
		Bullet* bullet = new PeaBullet();
		Vector2D bullet_position, bullet_velocity;

		// 计算豌豆的位置以及速度
		const Vector2D& bullet_size = bullet->GetSize();
		// 根据角色的朝向不同，设置不同的发射位置
		bullet_position.m_X = is_facing_right ? m_Position.m_X + m_Size.m_X - bullet_size.m_X / 2 : m_Position.m_X - bullet_size.m_X / 2;
		bullet_position.m_Y = m_Position.m_Y;
		bullet_velocity.m_X = is_facing_right ? speed : -speed;
		bullet_velocity.m_Y = 0;

		// 设置子弹位置和速度
		bullet->SetPosition(bullet_position);
		bullet->SetVelocity(bullet_velocity);

		// 设置子弹碰撞目标
		bullet->SetCollideTarget(m_PlayerID == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);

		bullet->SetCallBack([&]() {  
			if (!is_attacking_ex)  
				m_MP += 25; 
			});

		bullet_list.push_back(bullet);
	}
};