#pragma once

#include"Camera.h"
#include"Vector2D.h"
#include"Animation.h"
#include"PlayerID.h"
#include"Platform.h"
#include"Bullet.h"
#include"Particle.h"

#include<iostream>
#include<graphics.h>

extern bool is_debug;

extern std::vector<Bullet*> bullet_list;
extern std::vector<Platform> platform_list;

extern IMAGE img_1P_cursor;									//1P 指示光标图片
extern IMAGE img_2P_cursor;									//2P 指示光标图片

extern Atlas atlas_run_effect;								//奔跑特效动画图集
extern Atlas atlas_jump_effect;								//跳跃特效动画图集
extern Atlas atlas_land_effect;								//落地特效动画图集

class Player {
public:
	Player(bool facing_right = true) : is_facing_right(facing_right) {
		current_animation = is_facing_right ? &m_Animation_idle_right : &m_Animation_idle_left;

		// 设置普通攻击定时器
		m_Timer_Attack_CD.SetWaitTime(m_Attack_CD);
		m_Timer_Attack_CD.SetOneShot(true);
		m_Timer_Attack_CD.SetCallBack([&]()
			{
				m_CanAttack = true;
			});

		// 总无敌帧时间为750ms
		timer_invulnerable.SetWaitTime(750);
		timer_invulnerable.SetOneShot(true);
		timer_invulnerable.SetCallBack([&]() {
			is_invulnerable = false;
			});

		// 一次闪烁时间为75ms
		timer_invulnerable_bink.SetWaitTime(75);
		timer_invulnerable_bink.SetCallBack([&]() {
			// 闪烁一次，切换一次
			is_showing_sketch_frame = !is_showing_sketch_frame;
			});

		// 跑动特效计时器
		timer_run_effect_generation.SetWaitTime(75);
		timer_run_effect_generation.SetCallBack([&]()
			{
				Vector2D particle_position;
				IMAGE* frame = atlas_run_effect.get_image(0);
				particle_position.m_X = m_Position.m_X + (m_Size.m_X - frame->getwidth()) / 2;
				particle_position.m_Y = m_Position.m_Y + m_Size.m_Y - frame->getheight();
				particle_list.emplace_back(particle_position, &atlas_run_effect, 45);
			});

		timer_die_effect_generation.SetWaitTime(35);
		timer_die_effect_generation.SetCallBack([&]()
			{
				Vector2D particle_position;
				IMAGE* frame = atlas_run_effect.get_image(0);
				particle_position.m_X = m_Position.m_X + (m_Size.m_X - frame->getwidth()) / 2;
				particle_position.m_Y = m_Position.m_Y + m_Size.m_Y - frame->getheight();
				particle_list.emplace_back(particle_position, &atlas_run_effect, 150);
			});

		// 设置玩家跳跃动画
		m_Animation_jump_effect.Set_Atlas(&atlas_jump_effect);
		m_Animation_jump_effect.Set_Interval(25);
		m_Animation_jump_effect.Set_Loop(false);
		m_Animation_jump_effect.Set_CallBack([&]() {
			is_jump_effect_visible = false;
			});

		// 设置玩家落地动画
		m_Animation_land_effect.Set_Atlas(&atlas_land_effect);
		m_Animation_land_effect.Set_Interval(50);
		m_Animation_land_effect.Set_Loop(false);
		m_Animation_land_effect.Set_CallBack([&]() {
			is_land_effect_visible = false;
			});

		timer_cursor_visibility.SetWaitTime(2500);
		timer_cursor_visibility.SetOneShot(true);
		timer_cursor_visibility.SetCallBack([&]()
			{
				is_cursor_visible = false;
			});

	}
	~Player() {}

	virtual void OnUpdate(int delta) {
		int direction = is_right_key_down - is_left_key_down;

		// direction 不为0时 表示有移动按键被按下 需要考虑更新朝向
		if (direction != 0) {
			// 大于0表示 向右移动按键被按下 需要朝向右边
			if(!is_attacking_ex)
				is_facing_right = direction > 0;
			
			current_animation = is_facing_right ? &m_Animation_run_right : &m_Animation_run_left;
			float distance = direction * m_RunSpeed * delta;
			OnRun(distance);
		}
		else {
			current_animation = is_facing_right ? &m_Animation_idle_right : &m_Animation_idle_left;
			timer_run_effect_generation.Pause();
		}

		if (is_attacking_ex)
			current_animation = is_facing_right ? &m_Animation_attack_ex_right : &m_Animation_attack_ex_left;

		
		// 更新当前角色动画
		current_animation->On_Update(delta);
		// 更新角色跳跃动画
		m_Animation_jump_effect.On_Update(delta);
		// 更新角色落地动画
		m_Animation_land_effect.On_Update(delta);

		// 更新攻击间隔CD
		m_Timer_Attack_CD.OnUpDate(delta);

		// 更新角色无敌帧
		timer_invulnerable.OnUpDate(delta);
		// 更新角色闪烁
		timer_invulnerable_bink.OnUpDate(delta);
		
		// 更新角色跑动特效
		timer_run_effect_generation.OnUpDate(delta);

		// 更新玩家提示光标
		timer_cursor_visibility.OnUpDate(delta);

		if (m_HP <= 0) {
			current_animation = last_hurt_direction.m_X < 0 ? &m_Animation_die_left : &m_Animation_die_right;
			timer_die_effect_generation.OnUpDate(delta);
		}

		particle_list.erase(std::remove_if(
			particle_list.begin(), particle_list.end(),
			[](const Particle& particle) {
				return !particle.CheckValid();
			}),
			particle_list.end());

		for (Particle& particle : particle_list) {
			particle.OnUpdate(delta);
		}

		if (is_showing_sketch_frame)
			sketch_image(current_animation->Get_Frame_Img(), &img_sketch);

		Move_and_Collide(delta);
	}

	// 角色绘制
	virtual void OnDraw(const Camera& camera) {
		// 跳跃时
		if (is_jump_effect_visible)
			m_Animation_jump_effect.On_Draw(camera, (int)position_jump_effect.m_X, (int)position_jump_effect.m_Y);

		// 落地时
		if (is_land_effect_visible)
			m_Animation_land_effect.On_Draw(camera, (int)position_land_effect.m_X, (int)position_land_effect.m_Y);

		if (is_cursor_visible) {
			switch (m_PlayerID)
			{
			case PlayerID::P1:
				PutImage_Alpha(camera, (int)(m_Position.m_X + (m_Size.m_X - img_1P_cursor.getwidth()) / 2),
					(int)(m_Position.m_Y - img_1P_cursor.getheight()), &img_1P_cursor);
				break;
			case PlayerID::P2:
				PutImage_Alpha(camera, (int)(m_Position.m_X + (m_Size.m_X - img_2P_cursor.getwidth()) / 2),
					(int)(m_Position.m_Y - img_2P_cursor.getheight()), &img_2P_cursor);
				break;
			default:
				break;
			}
		}
			

		for (const Particle& particle : particle_list) {
			particle.OnDraw(camera);
		}

		// 无敌帧动画
		if (m_HP > 0 && is_invulnerable && is_showing_sketch_frame)
			PutImage_Alpha(camera, (int)m_Position.m_X, (int)m_Position.m_Y, &img_sketch);
		else
		current_animation->On_Draw(camera, (int)m_Position.m_X, (int)m_Position.m_Y);

		// debug阶段
		if (is_debug) {
			setlinecolor(RGB(0, 125, 125));
			rectangle((int)m_Position.m_X, (int)m_Position.m_Y, (int)(m_Position.m_X + m_Size.m_X), (int)(m_Position.m_Y + m_Size.m_Y));
		}


	}

	virtual void OnInput(const ExMessage& msg) {
		switch (msg.message)
		{
		case WM_KEYDOWN:
			switch (m_PlayerID)
			{
			case PlayerID::P1:
				// P1 玩家操作
				switch (msg.vkcode) 
				{
					// 'A'
				case 0x41:
					is_left_key_down = true;
					break;
					// 'D'
				case 0x44:
					is_right_key_down = true;
					break;
					// 'W'
				case 0x57:
					// 跳跃
					OnJump();
					break;
					// 'F'
				case 0x46:
					// 如果可以攻击
					if (m_CanAttack) {
						// 执行普通攻击
						OnAttack();
						m_CanAttack = false;
						// 重置计时器
						m_Timer_Attack_CD.Restart();
					}
					break;
					// 'G'
				case 0x47:
					// 满蓝，可以释放技能
					if (m_MP >= 100) {
						OnAttackEx();
						m_MP = 0;
					}
				}
				break;
			case PlayerID::P2:
				// P2 玩家操作
				switch (msg.vkcode)
				{
					// '⬅'
				case VK_LEFT:
					is_left_key_down = true;
					break;
					// '➡'
				case VK_RIGHT:
					is_right_key_down = true;
					break;
					// '⬆'
				case VK_UP:
					OnJump();
					break;
					// '.'
				case VK_OEM_PERIOD:
					if (m_CanAttack) {
						OnAttack();  
						m_CanAttack = false;
						m_Timer_Attack_CD.Restart();
					}
					break;
					// '/'
				case VK_OEM_2:
					if (m_MP >= 100) {
						OnAttackEx();
						m_MP = 0;
					}
					break;
				}
				break;
			default:
				break;
			}
			break;
		case WM_KEYUP:
			switch (m_PlayerID)
			{
			case PlayerID::P1:
				// P1 玩家操作
				switch (msg.vkcode)
				{
					// 'A'
				case 0x41:
					is_left_key_down = false;
					break;
					// 'D'
				case 0x44:
					is_right_key_down = false;
					break;
				}
				break;
			case PlayerID::P2:
				// P2 玩家操作
				switch (msg.vkcode)
				{
					// '⬅'
				case VK_LEFT:
					is_left_key_down = false;
					break;
					// '➡'
				case VK_RIGHT:
					is_right_key_down = false;
					break;
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}


	// 角色移动
	virtual void OnRun(float distance) {
		if (is_attacking_ex)
			return;

		m_Position.m_X += distance;
		timer_run_effect_generation.Resume();
	}

	virtual void OnJump() {
		if (is_attacking_ex)
			return;

		if (first_jump == true && sec_jump == true && m_Velocity.m_Y!=0) {
			return;
		}
		if (first_jump == false && sec_jump == false) {
			is_jump_effect_visible = true;
			m_Velocity.m_Y = m_JumpSpeed;
			first_jump = true;
			m_Animation_jump_effect.Reset();
			IMAGE* effect_frame = m_Animation_jump_effect.Get_Frame_Img();
			position_jump_effect.m_X = m_Position.m_X + (m_Size.m_X - effect_frame->getwidth()) / 2;
			position_jump_effect.m_Y = m_Position.m_Y + m_Size.m_Y - effect_frame->getheight();
		}
		else if (first_jump == true && sec_jump == false) {
			is_jump_effect_visible = true;
			m_Velocity.m_Y = m_JumpSpeed / 1.5;
			sec_jump = true;
			m_Animation_jump_effect.Reset();
			IMAGE* effect_frame = m_Animation_jump_effect.Get_Frame_Img();
			position_jump_effect.m_X = m_Position.m_X + (m_Size.m_X - effect_frame->getwidth()) / 2;
			position_jump_effect.m_Y = m_Position.m_Y + m_Size.m_Y - effect_frame->getheight();
		}
	}

	virtual void OnLand() {
		is_land_effect_visible = true;
		m_Animation_land_effect.Reset();

		IMAGE* effect_frame = m_Animation_land_effect.Get_Frame_Img();
		position_land_effect.m_X = m_Position.m_X + (m_Size.m_X - effect_frame->getwidth()) / 2;
		position_land_effect.m_Y = m_Position.m_Y + m_Size.m_Y - effect_frame->getheight();
	}

	// 角色攻击函数
	virtual void OnAttack() {}

	// 角色特殊攻击函数
	virtual void OnAttackEx() {}

	void MakeInvulnerable() {
		is_invulnerable = true;
		timer_invulnerable.Restart();
	}

	// 设置玩家1P 2P
	void SetID(PlayerID id) {
		m_PlayerID = id;
	}

	// 设置角色位置
	void SetPosition(float x, float y) {
		m_Position.m_X = x;
		m_Position.m_Y = y;
	}

	const Vector2D& GetPosition() const {
		return m_Position;
	}

	const Vector2D& GetSize() const {
		return m_Size;
	}

	// 设置角色大小
	void SetSize(float x, float y) {
		m_Size.m_X = x;
		m_Size.m_Y = y;
	}

	

protected:
	int m_HP = 100;							// 角色生命值
	int m_MP = 0;							// 角色能量

public:
	// 设置角色血量
	void SetHP(int hp) {
		m_HP = hp;
	}


	// 获取玩家的血量
	int GetHP() const {
		return m_HP;
	}

	// 获取玩家的蓝量
	int GetMP() const {
		return m_MP;
	}

protected:
	const float gravity = 1.9e-3f;			// 玩家重力
	const float m_RunSpeed = 0.55f;			// 跑动速度
	const float m_JumpSpeed = -0.85f;		// 跳跃速度
	bool first_jump = false;
	bool sec_jump = false;
protected:
	Vector2D m_Velocity;					// 玩家速度
	Vector2D m_Position;					// 玩家位置信息
protected:
	Vector2D m_Size;						// 玩家角色大小

	// 攻击设置
protected:
	bool m_CanAttack = true;				// 角色是否可以释放普通攻击
	int m_Attack_CD = 500;					// 角色普通攻击的时间间隔
	Timer m_Timer_Attack_CD;				// 普通攻击冷却定时器
	bool is_attacking_ex = false;			// 是否正在释放普通攻击

protected:
	Animation m_Animation_idle_left;		// 默认向左动画
	Animation m_Animation_idle_right;		// 默认向右动画
	Animation m_Animation_run_left;			// 奔跑向左动画
	Animation m_Animation_run_right;		// 奔跑向左动画
	Animation m_Animation_jump_effect;		// 跳跃粒子动画
	Animation m_Animation_land_effect;		// 落地粒子动画
	Animation m_Animation_die_left;			// 向左死亡动画
	Animation m_Animation_die_right;			// 向右死亡动画

protected:
	bool is_jump_effect_visible = false;	// 跳跃动画是否可见
	bool is_land_effect_visible = false;	// 落地动画是否可见

	Vector2D position_jump_effect;
	Vector2D position_land_effect;

protected:
	Animation m_Animation_attack_ex_left;	// 向左的特殊攻击动画
	Animation m_Animation_attack_ex_right;	// 向右的特殊攻击动画

	PlayerID m_PlayerID = PlayerID::P1;		// 玩家ID

	Animation* current_animation = nullptr;	//当前正在播放的动画

	// 玩家按键操作
	bool is_left_key_down;					// 向左移动是否按下
	bool is_right_key_down;					// 向左移动是否按下

	bool is_facing_right = true;			// 角色是否朝向右侧


protected:
	IMAGE img_sketch;						// 动画帧剪影图片

	bool is_invulnerable = false;			// 是否为无敌状态
	bool is_showing_sketch_frame = false;	// 当前帧是否应该显示剪影
	Timer timer_invulnerable;				// 无敌状态定时器
	Timer timer_invulnerable_bink;			// 无敌状态闪烁定时器

	std::vector<Particle> particle_list;	// 粒子对象列表

	Timer timer_run_effect_generation;		// 跑动特效粒子定时器
	Timer timer_die_effect_generation;		// 死亡特效粒子定时器

	Vector2D last_hurt_direction;			// 最后一次受击的方向

	bool is_cursor_visible = true;			// 玩家光标指示器是否显示
	Timer timer_cursor_visibility;			// 玩家光标指示器定时器

	

protected:
	// 死亡击飞函数
	void Die_and_Move(const Vector2D& last_pos) {
		m_Velocity.m_X = last_pos.m_X < 0 ? 0.35f : -0.35;
		m_Velocity.m_Y = -1.0f;
	}

	// 碰撞检测函数
	void Move_and_Collide(int delta) {
		float last_velocity_y = m_Velocity.m_Y;

		m_Velocity.m_Y += gravity * delta;
		m_Position += m_Velocity * (delta);

		if (m_HP <= 0)
			return;

		// 当玩家向下移动时，碰撞检验
		if (m_Velocity.m_Y > 0) {
			for (const Platform& platform : platform_list) {
				const Platform::CollisionShape& shape = platform.m_Shape;
				// 判断角色是否踩在边界上
				bool is_collide_x = (max(m_Position.m_X + m_Size.m_X, shape.m_Right) - min(m_Position.m_X, shape.m_Left)
					<= m_Size.m_X + (shape.m_Right - shape.m_Left));

				// 判断角色跳跃时，是否碰到平台
				bool is_collide_y = shape.m_Y >= m_Position.m_Y && shape.m_Y <= m_Position.m_Y + m_Size.m_Y;

				if (is_collide_x && is_collide_y) {
					// 计算移动距离
					float delta_pos_y = m_Velocity.m_Y * delta;
					// 回退上一帧角色Y轴所在位置
					float last_tick_foot_pos_y = m_Position.m_Y + m_Size.m_Y - delta_pos_y;
					// 如果角色上一帧在平台上方
					if (last_tick_foot_pos_y <= shape.m_Y) {
						// 将角色置于平台上
						m_Position.m_Y = shape.m_Y - m_Size.m_Y;
						m_Velocity.m_Y = 0;

						// 落到平台后才可以继续二段跳
						first_jump = false;
						sec_jump = false;

						// 上一帧下降速度不为0，当前帧为0，视为落地
						if (last_velocity_y != 0)
							OnLand();
						break;
					}
				}
			}
		}

		if (!is_invulnerable) {
			for (Bullet* bullet : bullet_list) {
				// 检查子弹是否有效、子弹目标是否为当前任务目标
				if (!bullet->GetValid() || bullet->GetCollideTarget() != m_PlayerID)
					continue;

				// 检查子弹是否发生碰撞 
				if (bullet->CheckCollision(m_Position, m_Size)) {
					// 进入无敌帧
					MakeInvulnerable();
					// 执行碰撞函数
					bullet->OnCollide();
					bullet->SetValid(false);
					// 玩家扣血
					m_HP -= bullet->GetDamage();

					// 存储玩家最后一次受到伤害的方向
					last_hurt_direction = bullet->GetPosition() - m_Position;
					if(m_HP <= 0)
						Die_and_Move(last_hurt_direction);
				}
			}
		}

	}
};
