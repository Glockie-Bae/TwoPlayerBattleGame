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
	int m_timer = 0;			// ���Ӷ������Ŷ�ʱ��
	int m_lifespan = 0;		// ��֡���Ӷ�������ʱ��
	int m_idx_frame = 0;		// ��ǰ���ڲ��ŵĶ���֡

	Vector2D m_position;		// ���ӵ���������λ��
	bool m_valid = true;		// ���Ӷ����Ƿ���Ч
	Atlas* m_atlas = nullptr;	// ���Ӷ�����ʹ�õ�ͼ��
};