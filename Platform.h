#pragma once
#include"Util.h"
#include"Camera.h"

extern bool is_debug;


class Platform {
public:
	struct CollisionShape
	{
		float m_Y;
		float m_Left, m_Right;
	};

public:
	CollisionShape m_Shape;
	IMAGE* m_Img = nullptr;
	POINT m_RenderPosition = { 0 };

public:
	Platform() {};
	~Platform() {};

	void OnDraw(const Camera& camera) const {
		PutImage_Alpha(camera, m_RenderPosition.x, m_RenderPosition.y, m_Img);

		if (is_debug) {
			setlinecolor(RGB(255, 0, 0));
			DrawEdge(camera, (int)m_Shape.m_Left, (int)m_Shape.m_Y, (int)m_Shape.m_Right, (int)m_Shape.m_Y);
		}
	}
};