#pragma once
// 子弹基类

#include"Vector2D.h"
#include"PlayerID.h"
#include"Camera.h"

#include<graphics.h>
#include<iostream>
#include<functional>

extern bool is_debug;

class Bullet {
public:
	Bullet() {}
	~Bullet() {}

	// 设置子弹伤害
	void SetDamage(int damage) {
		m_Damage = damage;
	}

	// 返回子弹伤害
	int GetDamage() {
		return m_Damage;
	}

	// 设置子弹位置
	void SetPosition(const Vector2D& position) {
		m_Position = position;
	}

	// 返回子弹位置
	const Vector2D& GetPosition() const {
		return m_Position;
	}
	
	// 返回子弹大小
	const Vector2D& GetSize() const {
		return m_Size;
	}

	// 设置子弹速度
	void SetVelocity(const Vector2D& velocity) {
		m_Velocity = velocity;
	}

	// 设置子弹碰撞目标
	void SetCollideTarget(PlayerID id) {
		target_id = id;
	}

	// 返回子弹碰撞目标
	PlayerID GetCollideTarget() {
		return target_id;
	}

	// 设置回调函数
	void SetCallBack(std::function<void()> callback) {
		this->callback = callback;
	}

	// 设置子弹是否有效
	void SetValid(bool valid) {
		this->valid = valid;
	}

	// 返回子弹是否有效状态
	bool GetValid() {
		return valid;
	}

	// 设置子弹是否可删除
	void SetRemove(bool remove) {
		this->remove = remove;
	}

	// 返回子弹可删除状态
	bool GetRemove() const {
		return remove;
	}

	// 子弹发生碰撞 执行回调函数
 	virtual void OnCollide() {
		// 执行回调函数
		if (callback) {
			callback();
		}
	}

	// 参数：角色的位置和大小
	virtual bool CheckCollision(const Vector2D& position, const Vector2D& size) {
		return m_Position.m_X + m_Size.m_X / 2 >= position.m_X
			&& m_Position.m_X + m_Size.m_X / 2 <= position.m_X + size.m_X
			&& m_Position.m_Y + m_Size.m_Y / 2 >= position.m_Y
			&& m_Position.m_Y + m_Size.m_Y / 2 <= position.m_Y + size.m_Y;

	}

	virtual void OnUpdate(int delta){ }

	virtual void OnDraw(const Camera& camera) const {
		if (is_debug) {
			setfillcolor(RGB(255, 255, 255));
			setlinecolor(RGB(255, 255, 255));
			rectangle((int)m_Position.m_X, (int)m_Position.m_Y,
				(int)(m_Position.m_X + m_Size.m_X), (int)(m_Position.m_Y + m_Size.m_Y));
			solidcircle((int)(m_Position.m_X + m_Size.m_X / 2), (int)(m_Position.m_Y + m_Size.m_Y / 2), 5);
		}
	}

protected:
	Vector2D m_Size;						// 子弹大小
	Vector2D m_Position;					// 子弹位置
	Vector2D m_Velocity;					// 子弹速度
	int m_Damage = 10;						// 子弹伤害

	// 需要将子弹分成三个状态：有效状态，碰撞后进入无效状态，播放爆炸动画后进入销毁状态
	bool valid = true;						// 子弹是否有效
	bool remove = false;					// 子弹是否可以被删除
	std::function<void()> callback;			// 回调函数

	PlayerID target_id = PlayerID::P1;		// 子弹攻击的目标对象

protected:
	bool Check_If_Exceeds_Screen() {
		return (m_Position.m_X + m_Size.m_X <= 0 || m_Position.m_X >= getwidth()
			|| m_Position.m_Y + m_Size.m_Y <= 0 || m_Position.m_Y >= getheight());
	}

};