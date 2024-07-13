#include "GameScene.h"

void GameScene::OnEnter()
{
	is_game_over = false;
	is_slide_out_started = false;

	// 设置结算窗口位置
	pos_img_winner_background.x = -img_winner_bar.getwidth();
	pos_img_winner_background.y = (getheight() - img_winner_bar.getheight()) / 2;
	pos_x_img_winner_background_dst = (getwidth() - img_winner_bar.getwidth()) / 2;

	pos_img_winner_text.x = pos_img_winner_background.x;
	pos_img_winner_text.y = (getheight() - img_1P_winner.getheight()) / 2;
	pos_x_img_winner_text_dst = (getwidth() - img_1P_winner.getwidth()) / 2;

	// 设置滑入滑出定时器
	timer_winner_slide_in.Restart();
	timer_winner_slide_in.SetWaitTime(2500);
	timer_winner_slide_in.SetOneShot(true);
	timer_winner_slide_in.SetCallBack([&]()
		{
			is_slide_out_started = true;
		});

	timer_winner_slide_out.Restart();
	timer_winner_slide_out.SetWaitTime(1000);
	timer_winner_slide_out.SetOneShot(true);
	timer_winner_slide_out.SetCallBack([&]()
		{
			scene_manager.SwitchScene(SceneManager::SceneType::Menu);
		});


	pos_img_sky.x = (getwidth() - img_sky.getwidth()) / 2;
	pos_img_sky.y = (getheight() - img_sky.getheight()) / 2;

	pos_img_hills.x = (getwidth() - img_hills.getwidth()) / 2;
	pos_img_hills.y = (getheight() - img_hills.getheight()) / 2;

	Init_Platform(4);

	player_1P->SetPosition(200, 50);
	player_2P->SetPosition(975, 50);

	status_bar_1P.SetAvatar(img_player_1_avatar);
	status_bar_2P.SetAvatar(img_player_2_avatar);
	status_bar_1P.SetPosition(235, 625);
	status_bar_2P.SetPosition(625, 625);

	mciSendString(_T("play bgm_game repeat from 0"), NULL, 0, NULL);

}

void GameScene::OnUpdate(int delta)
{
	player_1P->OnUpdate(delta);
	player_2P->OnUpdate(delta);

	main_camera.On_Update(delta);

	// erase 函数移除list中元素子弹，配合remove_if遍历整个列表
	// 如果 子弹 remove 为 true 则 delete 该子弹
	bullet_list.erase(std::remove_if(
		bullet_list.begin(), bullet_list.end(),
		[](const Bullet* bullet) {
			bool deletable = bullet->GetRemove();
			if (deletable) delete bullet;
			return deletable;
		}),
		bullet_list.end());


	for (Bullet* bullet : bullet_list) {
		bullet->OnUpdate(delta);
	}

	// 获取玩家位置
	const Vector2D& position_player_1 = player_1P->GetPosition();
	const Vector2D& position_player_2 = player_2P->GetPosition();
	if (position_player_1.m_Y >= getheight())
		player_1P->SetHP(0);
	if (position_player_2.m_Y >= getheight())
		player_2P->SetHP(0);

	status_bar_1P.SetHP(player_1P->GetHP());
	status_bar_1P.SetMP(player_1P->GetMP());
	status_bar_2P.SetHP(player_2P->GetHP());
	status_bar_2P.SetMP(player_2P->GetMP());

	if (player_1P->GetHP() <= 0 || player_2P->GetHP() <= 0) {
		if (!is_game_over) {
			mciSendString(_T("stop bgm_game"), NULL, 0, NULL);
			mciSendString(_T("play ui_win from 0"), NULL, 0, NULL);
		}

		is_game_over = true;
	}

	if (is_game_over) {
		pos_img_winner_background.x += (int)(speed_winner_background * delta);
		pos_img_winner_text.x += (int)(speed_winner_text * delta);

		if (!is_slide_out_started) {
			timer_winner_slide_in.OnUpDate(delta);
			if (pos_img_winner_background.x >= pos_x_img_winner_background_dst)
				pos_img_winner_background.x = pos_x_img_winner_background_dst;
			if (pos_img_winner_text.x >= pos_x_img_winner_text_dst)
				pos_img_winner_text.x = pos_x_img_winner_text_dst;
		}
		else
			timer_winner_slide_out.OnUpDate(delta);
	}

}

void GameScene::OnDraw(const Camera& camera)
{
	PutImage_Alpha(camera, pos_img_sky.x, pos_img_sky.y, &img_sky);
	PutImage_Alpha(camera, pos_img_hills.x, pos_img_hills.y, &img_hills);

	for (const Platform& platform : platform_list) {
		platform.OnDraw(camera);
	}

	if (is_debug) {
		settextcolor(RGB(255, 0, 0));
		outtextxy(15, 15, _T("已开启调试模式， 按'Q'键关闭"));
	}

	player_1P->OnDraw(camera);
	player_2P->OnDraw(camera);

	for (Bullet* bullet : bullet_list) {
		bullet->OnDraw(camera);
	}

	if (is_game_over) {
		PutImage_Alpha(pos_img_winner_background.x, pos_img_winner_background.y, &img_winner_bar);
		PutImage_Alpha(pos_img_winner_text.x, pos_img_winner_text.y, player_1P->GetHP() > 0 ? &img_1P_winner : &img_2P_winner);
	}
	else {
		status_bar_1P.OnDraw();
		status_bar_2P.OnDraw();
	}


	
}

void GameScene::OnInput(const ExMessage& msg)
{
	player_1P->OnInput(msg);
	player_2P->OnInput(msg);

	switch(msg.message)
	{
	case WM_KEYUP:
		// "Q"
		if (msg.vkcode == 0x51)
			is_debug = !is_debug;
		break;
	default:
		break;
	}
}

void GameScene::on_exit()
{
	delete player_1P; player_1P = nullptr;
	delete player_2P; player_2P = nullptr;

	is_debug = false;

	bullet_list.clear();
	main_camera.Reset();
}

void GameScene::Init_Platform(int num)
{
	platform_list.resize(num);
	
	// 初始化大平台
	Platform& large_platform = platform_list[0];

	large_platform.m_Img = &img_platform_large;
	large_platform.m_RenderPosition.x = 122;
	large_platform.m_RenderPosition.y = 455;
	// 碰撞体积比渲染体积要小
	large_platform.m_Shape.m_Left = (float)large_platform.m_RenderPosition.x + 30;
	large_platform.m_Shape.m_Right = (float)large_platform.m_RenderPosition.x + img_platform_large.getwidth() - 30;
	large_platform.m_Shape.m_Y = (float)large_platform.m_RenderPosition.y + 60;

	//初始化三个小平台
	Platform& small_platform_1 = platform_list[1];
	small_platform_1.m_Img = &img_platform_small;
	small_platform_1.m_RenderPosition.x = 175;
	small_platform_1.m_RenderPosition.y = 360;
	small_platform_1.m_Shape.m_Left = (float)small_platform_1.m_RenderPosition.x + 40;
	small_platform_1.m_Shape.m_Right = (float)small_platform_1.m_RenderPosition.x + img_platform_small.getwidth() - 40;
	small_platform_1.m_Shape.m_Y = (float)small_platform_1.m_RenderPosition.y + img_platform_small.getheight() / 2;
	
	Platform& small_platform_2 = platform_list[2];
	small_platform_2.m_Img = &img_platform_small;
	small_platform_2.m_RenderPosition.x = 855;
	small_platform_2.m_RenderPosition.y = 360;
	small_platform_2.m_Shape.m_Left = (float)small_platform_2.m_RenderPosition.x + 40;
	small_platform_2.m_Shape.m_Right = (float)small_platform_2.m_RenderPosition.x + img_platform_small.getwidth() - 40;
	small_platform_2.m_Shape.m_Y = (float)small_platform_2.m_RenderPosition.y + img_platform_small.getheight() / 2;

	Platform& small_platform_3 = platform_list[3];
	small_platform_3.m_Img = &img_platform_small;
	small_platform_3.m_RenderPosition.x = 515;
	small_platform_3.m_RenderPosition.y = 225;
	small_platform_3.m_Shape.m_Left = (float)small_platform_3.m_RenderPosition.x + 40;
	small_platform_3.m_Shape.m_Right = (float)small_platform_3.m_RenderPosition.x + img_platform_small.getwidth() - 40;
	small_platform_3.m_Shape.m_Y = (float)small_platform_3.m_RenderPosition.y + img_platform_small.getheight() / 2;
}
