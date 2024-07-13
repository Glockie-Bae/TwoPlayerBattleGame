#pragma once
#include"Scene.h"
#include"SceneManager.h"
#include"Animation.h"
#include"Player.h"
#include"Sunflower.h"
#include"Peashooter.h"

extern Player* player_1P;
extern Player* player_2P;
	
extern IMAGE* img_player_1_avatar;								//1P 玩家状态栏头像
extern IMAGE* img_player_2_avatar;								//2P 玩家状态栏头像

extern IMAGE img_avatar_peashooter;								//豌豆射手头像图片
extern IMAGE img_avatar_sunflower;								//向日葵头像图片

extern SceneManager scene_manager;
extern IMAGE img_VS;											//VS艺术字图片
extern IMAGE img_1P;											//1P 文本图片
extern IMAGE img_2P;											//2P 文本图片
extern IMAGE img_1P_desc;										//1P 键位描述图片
extern IMAGE img_2P_desc;										//2P 键位描述图片
extern IMAGE img_gravestone_left;								//朝向左边的墓碑图片
extern IMAGE img_gravestone_right;								//朝向右边的墓碑图片
extern IMAGE img_selector_tip;									//选角界面提示信息文本图片
extern IMAGE img_selector_background;							//选角界面背景图
extern IMAGE img_1P_selector_btn_idle_left;						//1P向左选择按钮默认状态图片
extern IMAGE img_1P_selector_btn_idle_right;					//1P向右选择按钮默认状态图片
extern IMAGE img_1P_selector_btn_down_left;						//1P向左选择按钮按下状态图片
extern IMAGE img_1P_selector_btn_down_right;					//1P向右选择按钮按下状态图片
extern IMAGE img_2P_selector_btn_idle_left;						//2P向左选择按钮默认状态图片
extern IMAGE img_2P_selector_btn_idle_right;					//2P向右选择按钮默认状态图片
extern IMAGE img_2P_selector_btn_down_left;						//2P向左选择按钮按下状态图片
extern IMAGE img_2P_selector_btn_down_right;					//2P向右选择按钮按下状态图片
extern IMAGE img_peashooter_selector_background_left;			//选角界面朝左的豌豆射手背景图片
extern IMAGE img_peashooter_selector_background_right;			//选角界面朝右的豌豆射手背景图片
extern IMAGE img_sunflower_selector_background_left;			//选角界面朝右的向日葵背景图片
extern IMAGE img_sunflower_selector_background_right;			//选角界面朝右的向日葵背景图片

extern Atlas atlas_peashooter_idle_right;						//豌豆射手朝向左的默认动画集
extern Atlas atlas_sunflower_idle_right;						//向日葵朝向左的默认动画集

extern SceneManager scene_manager;


class SelectorScene : public Scene {
public:
	SelectorScene() {};
	~SelectorScene() {};

	virtual void OnEnter();
	virtual void OnUpdate(int delta);
	virtual void OnDraw(const Camera& camera);
	virtual void OnInput(const ExMessage& msg);
	virtual void on_exit();



private:
	enum class PlayerType {
		Peashooter = 0,
		Sunflower,
		Invalid
	};

private:
	POINT pos_img_VS = { 0 };								//VS 艺术字图片位置
	POINT pos_img_tip = { 0 };								//提示信息文本图片位置
	POINT pos_img_1P = { 0 };								//1P 文本图片位置
	POINT pos_img_2P = { 0 };								//2P 文本图片位置
	POINT pos_img_1P_desc = { 0 };							//1P 键位描述图片位置
	POINT pos_img_2P_desc = { 0 };							//2P 键位描述图片位置
	POINT pos_img_1P_name = { 0 };							//1P 角色姓名文本位置
	POINT pos_img_2P_name = { 0 };							//2P 角色姓名文本位置
	POINT pos_animation_1P = { 0 };							//1P 角色动画位置
	POINT pos_animation_2P = { 0 };							//2P 角色动画位置
	POINT pos_img_1P_gravestone = { 0 };					//1P 墓碑图片位置
	POINT pos_img_2P_gravestone = { 0 };					//2P 墓碑图片位置
	POINT pos_1P_selector_btn_left = { 0 };					//1P 向左切换按钮位置
	POINT pos_1P_selector_btn_right = { 0 };				//1P 向右切换按钮位置
	POINT pos_2P_selector_btn_left = { 0 };					//2P 向左切换按钮位置
	POINT pos_2P_selector_btn_right = { 0 };				//2P 向右切换按钮位置

	Animation animation_peashooter;							// 豌豆射手动画
	Animation animation_sunflower;							// 向日葵动画

	PlayerType m_1Player_type = PlayerType::Peashooter;		//1P默认豌豆射手
	PlayerType m_2Player_type = PlayerType::Sunflower;		//2P默认向日葵

	LPCTSTR m_PeashooterName = _T("婉逗射手");				// 豌豆射手游戏名
	LPCTSTR m_SunflowerName = _T("龙日葵");					// 向日葵游戏名

	int selector_background_scorll_offset_x = 0;			// 背景板滚动距离

	bool is_btn_1P_left_down = false;						//1P 向左切换按钮是否按下
	bool is_btn_1P_right_down = false;						//1P 向右切换按钮是否按下
	bool is_btn_2P_left_down = false;						//2P 向左切换按钮是否按下
	bool is_btn_2P_right_down = false;						//2P 向右切换按钮是否按下

private:
	void outtextxy_shaded(int x, int y, LPCTSTR str) {
		settextcolor(RGB(45, 45, 45));
		outtextxy(x + 3, y + 3, str);
		settextcolor(RGB(255, 255, 255));
		outtextxy(x, y, str);
	}

};
