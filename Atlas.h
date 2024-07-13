#pragma once
#include<vector>
#include<graphics.h>


class Atlas {
public:
	Atlas() {};
	~Atlas() {};

	void Load_Image(LPCTSTR path_template, int num) {
		m_ImgList.clear();
		m_ImgList.resize(num);

		TCHAR path_file[256];
		for (int i = 0; i < num; i++) {
			_stprintf_s(path_file, path_template, i + 1);
			loadimage(&m_ImgList[i], path_file);
		}
	}

	void Clear() {
		m_ImgList.clear();
	}

	int Get_Size() {
		return (int)m_ImgList.size();
	}

	IMAGE* get_image(int idx) {
		if (idx < 0 || idx >= m_ImgList.size()) {
			return nullptr;
		}
		return &m_ImgList[idx];
	}


	void Add_Image(const IMAGE& img) {
		m_ImgList.push_back(img);
	}

private:
	std::vector<IMAGE> m_ImgList;
};