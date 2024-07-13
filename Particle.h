#pragma once
#include"Atlas.h"
#include"Vector2D.h"
#include"Util.h"

class Particle {
public:
	Particle() {}
	Particle(const Vector2D& position, Atlas* atlas, int lifespan)
		: m_position(position), m_atlas(atlas), m_lifespan(lifespan) { }
	~Particle() {}

	void SetAtlas(Atlas* atlas) {
		m_atlas = atlas;
	}

	void SetPosition(const Vector2D& position) {
		m_position = position;
	}

	void SetLifeSpan(int lifespan) {
		m_lifespan = lifespan;
	}

	bool CheckValid() const {
		return m_valid;
	}

	void OnUpdate(int delta) {
		m_timer += delta;
		if (m_timer > m_lifespan) {
			m_timer = 0;
			m_idx_frame++;
			if (m_idx_frame >= m_atlas->Get_Size()) {
				m_idx_frame = m_atlas->Get_Size() - 1;
				m_valid = false;
			}
		}
	}

	void OnDraw(const Camera& camera) const {
		PutImage_Alpha(camera, m_position.m_X, m_position.m_Y, m_atlas->get_image(m_idx_frame));
	}


private:
	int m_timer = 0;			// 粒子动画播放定时器
	int m_lifespan = 0;		// 单帧例子动画持续时长
	int m_idx_frame = 0;		// 当前正在播放的动画帧

	Vector2D m_position;		// 粒子的世界坐标位置
	bool m_valid = true;		// 粒子对象是否有效
	Atlas* m_atlas = nullptr;	// 粒子动画所使用的图集
};