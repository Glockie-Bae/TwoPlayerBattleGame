#include<graphics.h>
#include<iostream>
#include"Scene.h"
#include"Util.h"
#include"Resources.h"
#include"SceneManager.h"
#include"Camera.h"
#include"MenuScene.h"
#include"SelectorScene.h"
#include"GameScene.h"
#include"Platform.h"
#include"Player.h"
#include"Bullet.h"
#pragma comment(lib, "Winmm.lib")

bool is_debug = false;  // 是否开启调试模式

void Load_Game_Rescource() {
	AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, NULL);

	loadimage(&img_menu_background, _T("resources/menu_background.png"));

	loadimage(&img_VS, _T("resources/VS.png"));
	loadimage(&img_1P, _T("resources/1P.png"));
	loadimage(&img_2P, _T("resources/2P.png"));
	loadimage(&img_1P_desc, _T("resources/1P_desc.png"));
	loadimage(&img_2P_desc, _T("resources/2P_desc.png"));
	loadimage(&img_gravestone_right, _T("resources/gravestone.png"));
	Flip_Image(&img_gravestone_right, &img_gravestone_left);
	loadimage(&img_selector_tip, _T("resources/selector_tip.png"));
	loadimage(&img_selector_background, _T("resources/selector_background.png"));
	loadimage(&img_1P_selector_btn_idle_right, _T("resources/1P_selector_btn_idle.png"));
	Flip_Image(&img_1P_selector_btn_idle_right, &img_1P_selector_btn_idle_left);
	loadimage(&img_1P_selector_btn_down_right, _T("resources/1P_selector_btn_down.png"));
	Flip_Image(&img_1P_selector_btn_down_right, &img_1P_selector_btn_down_left);
	loadimage(&img_2P_selector_btn_idle_right, _T("resources/2P_selector_btn_idle.png"));
	Flip_Image(&img_2P_selector_btn_idle_right, &img_2P_selector_btn_idle_left);
	loadimage(&img_2P_selector_btn_down_right, _T("resources/2P_selector_btn_down.png"));
	Flip_Image(&img_2P_selector_btn_down_right, &img_1P_selector_btn_down_left);
	loadimage(&img_peashooter_selector_background_right, _T("resources/peashooter_selector_background.png"));
	Flip_Image(&img_peashooter_selector_background_right, &img_peashooter_selector_background_left);
	loadimage(&img_sunflower_selector_background_right, _T("resources/sunflower_selector_background.png"));
	Flip_Image(&img_sunflower_selector_background_right, &img_sunflower_selector_background_left);

	loadimage(&img_sky, _T("resources/sky.png"));
	loadimage(&img_hills, _T("resources/hills.png"));
	loadimage(&img_platform_large, _T("resources/platform_large.png"));
	loadimage(&img_platform_small, _T("resources/platform_small.png"));

	loadimage(&img_1P_cursor, _T("resources/1P_cursor.png"));
	loadimage(&img_2P_cursor, _T("resources/2P_cursor.png"));

	atlas_peashooter_idle_right.Load_Image(_T("resources/peashooter_idle_%d.png"), 9);
	Flip_Atlas(atlas_peashooter_idle_right, atlas_peashooter_idle_left);
	atlas_peashooter_run_right.Load_Image(_T("resources/peashooter_run_%d.png"), 5);
	Flip_Atlas(atlas_peashooter_run_right, atlas_peashooter_run_left);
	atlas_peashooter_attack_ex_right.Load_Image(_T("resources/peashooter_attack_ex_%d.png"), 3);
	Flip_Atlas(atlas_peashooter_attack_ex_right, atlas_peashooter_attack_ex_left);
	atlas_peashooter_die_right.Load_Image(_T("resources/peashooter_die_%d.png"), 4);
	Flip_Atlas(atlas_peashooter_die_right, atlas_peashooter_die_left);

	atlas_sunflower_idle_right.Load_Image(_T("resources/sunflower_idle_%d.png"), 8);
	Flip_Atlas(atlas_sunflower_idle_right, atlas_sunflower_idle_left);
	atlas_sunflower_run_right.Load_Image(_T("resources/sunflower_run_%d.png"), 5);
	Flip_Atlas(atlas_sunflower_run_right, atlas_sunflower_run_left);
	atlas_sunflower_attack_ex_right.Load_Image(_T("resources/sunflower_attack_ex_%d.png"), 9);
	Flip_Atlas(atlas_sunflower_attack_ex_right, atlas_sunflower_attack_ex_left);
	atlas_sunflower_die_right.Load_Image(_T("resources/sunflower_die_%d.png"), 2);
	Flip_Atlas(atlas_sunflower_die_right, atlas_sunflower_die_left);

	loadimage(&img_peashooter, _T("resources/pea.png"));
	atlas_pea_break.Load_Image(_T("resources/pea_break_%d.png"), 3);
	atlas_sun.Load_Image(_T("resources/sun_%d.png"), 5);
	atlas_sun_explode.Load_Image(_T("resources/sun_explode_%d.png"), 5);
	atlas_sun_ex.Load_Image(_T("resources/sun_ex_%d.png"), 5);
	atlas_sun_ex_explode.Load_Image(_T("resources/sun_ex_explode_%d.png"), 5);
	atlas_sun_text.Load_Image(_T("resources/sun_text_%d.png"), 6);


	atlas_run_effect.Load_Image(_T("resources/run_effect_%d.png"), 4);
	atlas_jump_effect.Load_Image(_T("resources/jump_effect_%d.png"), 5);
	atlas_land_effect.Load_Image(_T("resources/land_effect_%d.png"), 2);

	loadimage(&img_1P_winner, _T("resources/1P_winner.png"));
	loadimage(&img_2P_winner, _T("resources/2P_winner.png"));
	loadimage(&img_winner_bar, _T("resources/winner_bar.png"));


	loadimage(&img_avatar_peashooter, _T("resources/avatar_peashooter.png"));
	loadimage(&img_avatar_sunflower, _T("resources/avatar_sunflower.png"));

	mciSendString(_T("open resources/bgm_game.mp3 alias bgm_game"), NULL, 0, NULL);
	mciSendString(_T("open resources/bgm_menu.mp3 alias bgm_menu"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_1.mp3 alias pea_break_1"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_2.mp3 alias pea_break_2"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_3.mp3 alias pea_break_3"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_1.mp3 alias pea_shoot_1"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_2.mp3 alias pea_shoot_2"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_ex.mp3 alias pea_shoot_ex"), NULL, 0, NULL);
	mciSendString(_T("open resources/sun_explode.mp3 alias sun_explode"), NULL, 0, NULL);
	mciSendString(_T("open resources/sun_explode_ex.mp3 alias sun_explode_ex"), NULL, 0, NULL);
	mciSendString(_T("open resources/sun_text.mp3 alias sun_text"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_confirm.wav alias ui_confirm"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_switch.wav alias ui_switch"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_win.wav alias ui_win"), NULL, 0, NULL);
}

// 场景全局变量
Scene* menu_scene = nullptr;
Scene* selector_scene = nullptr;
Scene* game_scene = nullptr;

// 场景切换 摄像机 平台物体列表
SceneManager scene_manager;
Camera main_camera;
std::vector<Platform> platform_list;

// 玩家
Player* player_1P = nullptr;
Player* player_2P = nullptr;

// 玩家状态条头像
IMAGE* img_player_1_avatar = nullptr;
IMAGE* img_player_2_avatar = nullptr;

// 子弹
std::vector<Bullet*> bullet_list;


int main() {

	ExMessage msg;
	const int FPS = 60;

	Load_Game_Rescource();

	initgraph(1280, 720);
	settextstyle(28, 0, _T("IPix"));
	setbkmode(TRANSPARENT);

	BeginBatchDraw();

	Scene* scene = new MenuScene();
	menu_scene = new MenuScene();
	selector_scene = new SelectorScene();
	game_scene = new GameScene();


	scene_manager.SetCurrenetScene(menu_scene);


	while (true) {
		DWORD frame_start_time = GetTickCount();


		while (peekmessage(&msg)) {
			scene_manager.OnInput(msg);
		}

		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_tick_time = current_tick_time - last_tick_time;
		scene_manager.OnUpdate(delta_tick_time);
		last_tick_time = current_tick_time;

		cleardevice();
		scene_manager.OnDraw(main_camera);


		FlushBatchDraw();


		DWORD frame_end_time = GetTickCount();
		DWORD frame_delta_time = frame_end_time - frame_start_time;

		if (frame_delta_time < 1000 / FPS) {
			Sleep(1000 / FPS - frame_delta_time);
		}

		
	}

	EndBatchDraw();

	return 0;
}