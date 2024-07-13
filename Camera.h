#pragma once
#include"Vector2D.h"
#include"Timer.h"


class Camera {
public:
	Camera(){
		m_Timer_Shaking.SetOneShot(true);
		m_Timer_Shaking.SetCallBack([&]()
			{
				m_Is_Shaking = false;
				Reset();
			});
	}
	~Camera() {}

	const Vector2D& Get_Pos() const {
		return m_Position;
	}

	void Reset() {
		m_Position.Reset();
	}

	void On_Update(int delta) {
		m_Timer_Shaking.OnUpDate(delta);

		if (m_Is_Shaking) {
			m_Position.m_X = (-50 + rand() % 100) / 50.0f * m_ShakingStrength;
			m_Position.m_Y = (-50 + rand() % 100) / 50.0f * m_ShakingStrength;
		}
	}

	void Shake(float strength, int duration) {
		m_Is_Shaking = true;
		m_ShakingStrength = strength;

		m_Timer_Shaking.SetWaitTime(duration);
		m_Timer_Shaking.Restart();
	}



private:
	Vector2D m_Position;			//摄像机位置
	Timer m_Timer_Shaking;			//摄像机抖动定时器
	bool m_Is_Shaking = false;		//摄像机是否正在抖动
	float m_ShakingStrength = 0;	//摄像机抖动幅度
};