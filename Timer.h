#pragma once
#include<functional>

class Timer {
public:
	Timer() {};
	~Timer() {};

	void Restart() {
		pass_time = 0;
		shotted = false;
	}

	void SetWaitTime(int waittime) {
		wait_time = waittime;
	}

	void SetOneShot(bool isoneshot) {
		one_shot = isoneshot;
	}

	void SetCallBack(std::function<void()> callback) {
		this->callback = callback;
	}

	void Pause() {
		paused = true;
	}

	void Resume() {
		paused = false;
	}

	void OnUpDate(int delta) {
		if (paused == true)
			return;
		
		pass_time += delta;
		if (pass_time >= wait_time) {
			if ((!one_shot || (one_shot && !shotted)) && callback) {
				callback();
			}
			shotted = true;
			pass_time = 0;
		}
	}

private:							
	int pass_time = 0;					//�ѹ�ʱ��
	int wait_time = 0;					//�ȴ�ʱ��
	bool paused = false;				//�Ƿ���ͣ
	bool shotted = false;				//�Ƿ񴥷�
	bool one_shot = false;				//���δ���

	std::function<void()> callback;		//�ص�����
};