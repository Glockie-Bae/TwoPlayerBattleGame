#pragma once
#include"Atlas.h"
#include"Util.h"
#include"Camera.h"
#include<functional>


inline void PutImage_Alpha(int dst_x, int dst_y, IMAGE* img);

class Animation {
public:
	Animation() {}
	~Animation() {}

	void Reset() {
		m_Timer = 0;
		m_Idx_Frame = 0;
	}

	void Set_Atlas(Atlas* new_atlas) {
		Reset();
		m_Atlas = new_atlas;
	}

	void Set_Loop(bool flag) {
		m_Is_Loop = flag;
	}

	void Set_Interval(int interval) {
		m_Interval = interval;
	}

	int Get_Idx_Frame() {
		return m_Idx_Frame;
	}

	IMAGE* Get_Frame_Img() {
		return m_Atlas->get_image(m_Idx_Frame);
	}

	bool Check_Finished() {
		if (m_Is_Loop) return false;

		return (m_Idx_Frame == m_Atlas->Get_Size() - 1);
	}

	void On_Update(int delta) {
		m_Timer += delta;
		if (m_Timer >= m_Interval) {
			m_Timer = 0;
			m_Idx_Frame++;
			if (m_Idx_Frame >= m_Atlas->Get_Size()) {
				m_Idx_Frame = m_Is_Loop ? 0 : m_Atlas->Get_Size() - 1;
				if (!m_Is_Loop && m_CallBack)
					m_CallBack();
			}
		}
	}

	void On_Draw(const Camera& camera, int x, int y) const {
		PutImage_Alpha(camera, x, y, m_Atlas->get_image(m_Idx_Frame));
	}

	void Set_CallBack(std::function<void()> callback) {
		m_CallBack = callback;
	}

private:
	int m_Timer = 0;				//计时器
	int m_Interval = 0;			//帧间隔
	int m_Idx_Frame = 0;			//帧索引
	bool m_Is_Loop = true;		//是否循环
	Atlas* m_Atlas = nullptr;

	std::function<void()> m_CallBack;
};