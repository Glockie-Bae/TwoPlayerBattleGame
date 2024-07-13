#pragma once
#include<graphics.h>
#include"Atlas.h"
#include"Camera.h"
#pragma comment(lib, "MSIMG32.LIB")

inline void PutImage_Alpha(int dst_x, int dst_y, IMAGE* img) {
	int width = img->getwidth();
	int height = img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, width, height,
		GetImageHDC(img), 0, 0, width, height, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

inline void PutImage_Alpha(const Camera& camera,  int dst_x, int dst_y, IMAGE* img) {
	int width = img->getwidth();
	int height = img->getheight();
	const Vector2D& pos_camera = camera.Get_Pos();
	AlphaBlend(GetImageHDC(GetWorkingImage()), (int)(dst_x - pos_camera.m_X), (int)(dst_y - pos_camera.m_Y), width, height,
		GetImageHDC(img), 0, 0, width, height, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

inline void PutImage_Alpha(int dst_x, int dst_y, int width, int height, IMAGE* img, int src_x, int src_y) {
	int w = width >= 0 ? width : 0;
	int h = height > 0 ? height : img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h, GetImageHDC(img), src_x, src_y, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

inline void Flip_Image(IMAGE* src, IMAGE* dst) {
	int width = src->getwidth();
	int height = src->getheight();

	Resize(dst, width, height);

	DWORD* src_buffer = GetImageBuffer(src);
	DWORD* dst_buffer = GetImageBuffer(dst);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int idx_src = y * width + x;
			int idx_dst = y * width + (width - 1 - x);
			dst_buffer[idx_dst] = src_buffer[idx_src];
		}
	}
}

inline void Flip_Atlas(Atlas& src, Atlas& dst) {
	dst.Clear();
	for (int i = 0; i < src.Get_Size(); i++) {
		IMAGE img_flipped;
		Flip_Image(src.get_image(i), &img_flipped);
		dst.Add_Image(img_flipped);
	}
}

// »æÖÆÍ¼Ïñ±ß¿ò£¬ÓÃÓÚµ÷ÊÔ¼ì²âÎïÌåÅö×²
inline void DrawEdge(const Camera& camera, int x1, int y1, int x2, int y2) {
	const Vector2D& camera_position = camera.Get_Pos();
	line((int)(x1 - camera_position.m_X), (int)(y1 - camera_position.m_Y), (int)(x2 - camera_position.m_X), (int)(y2 - camera_position.m_Y));
}


inline void sketch_image(IMAGE* src, IMAGE* dst) {
	int w = src->getwidth();
	int h = src->getheight();

	Resize(dst, w, h);
	DWORD* src_buffer = GetImageBuffer(src);
	DWORD* dst_buffer = GetImageBuffer(dst);
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int idx = y * w + x;
			dst_buffer[idx] = BGR(RGB(255, 255, 255)) | (src_buffer[idx] & 0xFF000000);
		}
	}
}


