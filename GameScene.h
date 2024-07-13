#pragma once
#include"Scene.h"
#include"SceneManager.h"
#include"Util.h"
#include"Platform.h"
#include"Player.h"
#include"Sunflower.h"
#include"Peashooter.h"
#include"StatusBar.h"


// 引入玩家
extern Player* player_1P;
extern Player* player_2P;

// 引入玩家状态栏头像
extern IMAGE* img_player_1_avatar;								//1P 玩家状态栏头像
extern IMAGE* img_player_2_avatar;								//2P 玩家状态栏头像

// 引入游戏背景图
extern IMAGE img_sky;											//天空图片
extern IMAGE img_hills;											//山脉图片
extern IMAGE img_platform_large;								//大型平台图片
extern IMAGE img_platform_small;								//小型平台图片

// 引入玩家获胜图
extern IMAGE img_1P_winner;										//1P 获胜文本图片
extern IMAGE img_2P_winner;										//2P 获胜文本图片
extern IMAGE img_winner_bar;									//获胜玩家文本背景图片


// 引入摄像机
extern Camera main_camera;										//摄像机
// 引入场景管理变量
extern SceneManager scene_manager;
//引入平台列表
extern std::vector<Platform> platform_list;

class GameScene : public Scene {
public:
	GameScene() {}
	~GameScene() {}

	virtual void OnEnter();
	virtual void OnUpdate(int delta);
	virtual void OnDraw(const Camera& camera);
	virtual void OnInput(const ExMessage& msg);
	virtual void on_exit();

	void Init_Platform(int num);

private:
	const float speed_winner_background = 3.0f;					// 结算动效背景移动速度
	const float speed_winner_text = 1.5f;						// 结算动效文本移动速度

	
	bool is_game_over = false;									// 判断游戏是否结束

	POINT pos_img_winner_background = { 0 };					// 结算动效背景位置
	POINT pos_img_winner_text = { 0 };							// 结算动效文本位置
	int pos_x_img_winner_background_dst = 0;					// 结算动效背景移动的目标位置
	int pos_x_img_winner_text_dst = 0;							// 结算动效文本移动的目标位置

	Timer timer_winner_slide_in;								// 结算动效滑入定时器
	Timer timer_winner_slide_out;								// 结算动效滑出定时器
	bool is_slide_out_started = false;							// 判断结算动效是否开始滑出

private:
	POINT pos_img_sky = { 0 };									// 天空背景图位置
	POINT pos_img_hills = { 0 };								// 山脉背景图位置

	StatusBar status_bar_1P;									// 玩家 1 的状态条
	StatusBar status_bar_2P;									// 玩家 2 的状态条
};