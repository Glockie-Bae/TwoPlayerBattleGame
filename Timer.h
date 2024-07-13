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
	int pass_time = 0;					//已过时间
	int wait_time = 0;					//等待时间
	bool paused = false;				//是否暂停
	bool shotted = false;				//是否触发
	bool one_shot = false;				//单次触发

	std::function<void()> callback;		//回调函数
};