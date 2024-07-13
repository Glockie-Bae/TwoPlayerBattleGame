#pragma once
// �ӵ�����

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

	// �����ӵ��˺�
	void SetDamage(int damage) {
		m_Damage = damage;
	}

	// �����ӵ��˺�
	int GetDamage() {
		return m_Damage;
	}

	// �����ӵ�λ��
	void SetPosition(const Vector2D& position) {
		m_Position = position;
	}

	// �����ӵ�λ��
	const Vector2D& GetPosition() const {
		return m_Position;
	}
	
	// �����ӵ���С
	const Vector2D& GetSize() const {
		return m_Size;
	}

	// �����ӵ��ٶ�
	void SetVelocity(const Vector2D& velocity) {
		m_Velocity = velocity;
	}

	// �����ӵ���ײĿ��
	void SetCollideTarget(PlayerID id) {
		target_id = id;
	}

	// �����ӵ���ײĿ��
	PlayerID GetCollideTarget() {
		return target_id;
	}

	// ���ûص�����
	void SetCallBack(std::function<void()> callback) {
		this->callback = callback;
	}

	// �����ӵ��Ƿ���Ч
	void SetValid(bool valid) {
		this->valid = valid;
	}

	// �����ӵ��Ƿ���Ч״̬
	bool GetValid() {
		return valid;
	}

	// �����ӵ��Ƿ��ɾ��
	void SetRemove(bool remove) {
		this->remove = remove;
	}

	// �����ӵ���ɾ��״̬
	bool GetRemove() const {
		return remove;
	}

	// �ӵ�������ײ ִ�лص�����
 	virtual void OnCollide() {
		// ִ�лص�����
		if (callback) {
			callback();
		}
	}

	// ��������ɫ��λ�úʹ�С
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
	Vector2D m_Size;						// �ӵ���С
	Vector2D m_Position;					// �ӵ�λ��
	Vector2D m_Velocity;					// �ӵ��ٶ�
	int m_Damage = 10;						// �ӵ��˺�

	// ��Ҫ���ӵ��ֳ�����״̬����Ч״̬����ײ�������Ч״̬�����ű�ը�������������״̬
	bool valid = true;						// �ӵ��Ƿ���Ч
	bool remove = false;					// �ӵ��Ƿ���Ա�ɾ��
	std::function<void()> callback;			// �ص�����

	PlayerID target_id = PlayerID::P1;		// �ӵ�������Ŀ�����

protected:
	bool Check_If_Exceeds_Screen() {
		return (m_Position.m_X + m_Size.m_X <= 0 || m_Position.m_X >= getwidth()
			|| m_Position.m_Y + m_Size.m_Y <= 0 || m_Position.m_Y >= getheight());
	}

};