#include "SelectorScene.h"

void SelectorScene::OnEnter()
{
	mciSendString(_T("play bgm_game repeat from 0"), NULL, 0, NULL);

	animation_peashooter.Set_Atlas(&atlas_peashooter_idle_right);
	animation_peashooter.Set_Interval(100);

	animation_sunflower.Set_Atlas(&atlas_sunflower_idle_right);
	animation_sunflower.Set_Interval(100);

	static const int OFFSET_X = 50;

	pos_img_VS.x = (getwidth() - img_VS.getwidth()) / 2;
	pos_img_VS.y = (getheight() - img_VS.getheight()) / 2;
	pos_img_tip.x = (getwidth() - img_selector_tip.getwidth()) / 2;
	pos_img_tip.y = getheight() - 125;
	pos_img_1P.x = (getwidth() / 2 - img_1P.getwidth()) / 2 - OFFSET_X;
	pos_img_1P.y = 35;
	pos_img_2P.x = getwidth() / 2 + (getwidth() / 2 - img_2P.getwidth()) / 2 + OFFSET_X;
	pos_img_2P.y = pos_img_1P.y;
	pos_img_1P_desc.x = (getwidth() / 2 - img_1P_desc.getwidth()) / 2 - OFFSET_X;
	pos_img_1P_desc.y = getheight() - 150;
	pos_img_2P_desc.x = getwidth() / 2 + (getwidth() / 2 - img_2P_desc.getwidth()) / 2 + OFFSET_X;
	pos_img_2P_desc.y = pos_img_1P_desc.y;
	pos_img_1P_gravestone.x = (getwidth() / 2 - img_gravestone_right.getwidth()) / 2 - OFFSET_X;
	pos_img_1P_gravestone.y = pos_img_1P.y + img_1P.getheight() + 35;
	pos_img_2P_gravestone.x = getwidth() / 2 + (getwidth() / 2 - img_gravestone_left.getwidth()) / 2 + OFFSET_X;
	pos_img_2P_gravestone.y = pos_img_1P_gravestone.y;
	pos_animation_1P.x = (getwidth() / 2 - atlas_peashooter_idle_right.get_image(0)->getwidth()) / 2 - OFFSET_X;
	pos_animation_1P.y = pos_img_1P_gravestone.y + 80;
	pos_animation_2P.x = getwidth() / 2 + (getwidth() / 2 - atlas_peashooter_idle_right.get_image(0)->getwidth()) / 2 + OFFSET_X;
	pos_animation_2P.y = pos_animation_1P.y;
	pos_img_1P_name.y = pos_animation_1P.y + 155;
	pos_img_2P_name.y = pos_img_1P_name.y;

	//1P玩家切换角色按键位置
	pos_1P_selector_btn_left.x = pos_img_1P_gravestone.x - img_1P_selector_btn_idle_left.getwidth();
	pos_1P_selector_btn_left.y = pos_img_1P_gravestone.y + (img_gravestone_right.getheight() - img_1P_selector_btn_idle_left.getheight()) / 2;
	pos_1P_selector_btn_right.x = pos_img_1P_gravestone.x + img_gravestone_left.getwidth();
	pos_1P_selector_btn_right.y = pos_1P_selector_btn_left.y;
	//2P玩家切换角色按键位置
	pos_2P_selector_btn_left.x = pos_img_2P_gravestone.x - img_2P_selector_btn_idle_left.getwidth();
	pos_2P_selector_btn_left.y = pos_1P_selector_btn_left.y;
	pos_2P_selector_btn_right.x = pos_img_2P_gravestone.x + img_gravestone_right.getwidth();
	pos_2P_selector_btn_right.y = pos_2P_selector_btn_left.y;
}

void SelectorScene::OnUpdate(int delta)
{
	animation_peashooter.On_Update(delta);
	animation_sunflower.On_Update(delta);

	selector_background_scorll_offset_x += 5;
	if (selector_background_scorll_offset_x >= (img_peashooter_selector_background_left.getheight()))
		selector_background_scorll_offset_x = 0;
}

void SelectorScene::OnDraw(const Camera& camera)
{
	IMAGE* img_p1_selector_background = nullptr;
	IMAGE* img_p2_selector_background = nullptr;

	// 绘制选人对面角色背景图
	switch (m_2Player_type) {
	case PlayerType::Peashooter:
		img_p1_selector_background = &img_peashooter_selector_background_right;
		break;
	case PlayerType::Sunflower:
		img_p1_selector_background = &img_sunflower_selector_background_right;
		break;
	default:
		img_p1_selector_background = &img_peashooter_selector_background_right;
		break;
	}

	switch (m_1Player_type) {
	case PlayerType::Peashooter:
		img_p2_selector_background = &img_peashooter_selector_background_left;
		break;
	case PlayerType::Sunflower:
		img_p2_selector_background = &img_sunflower_selector_background_left;
		break;
	default:
		img_p2_selector_background = &img_peashooter_selector_background_left;
		break;
	}

	putimage(0, 0, &img_selector_background);

	//绘制背景滚动图
	//1P背景滚动图右移
	PutImage_Alpha(selector_background_scorll_offset_x - img_p1_selector_background->getwidth(), 0, img_p1_selector_background);
	//1P背景左边生成图
	PutImage_Alpha(selector_background_scorll_offset_x, 0, img_p1_selector_background->getwidth() - selector_background_scorll_offset_x, 0, img_p1_selector_background, 0, 0);
	//2P背景滚动图左移
	PutImage_Alpha(getwidth() - img_p2_selector_background->getwidth(), 0, img_p2_selector_background->getwidth() - selector_background_scorll_offset_x, 0, img_p2_selector_background, selector_background_scorll_offset_x, 0);
	//2P背景右边生成图
	PutImage_Alpha(getwidth() - selector_background_scorll_offset_x, 0, img_p2_selector_background);

	// 绘制中间VS图
	PutImage_Alpha(camera, pos_img_VS.x, pos_img_VS.y, &img_VS);

	// 绘制玩家选角背景墓碑
	PutImage_Alpha(camera, pos_img_1P.x, pos_img_1P.y, &img_1P);
	PutImage_Alpha(camera,pos_img_2P.x, pos_img_2P.y, &img_2P);
	PutImage_Alpha(camera,pos_img_1P_gravestone.x, pos_img_1P_gravestone.y, &img_gravestone_right);
	PutImage_Alpha(camera,pos_img_2P_gravestone.x, pos_img_2P_gravestone.y, &img_gravestone_left);

	//绘制下方提示信息
	PutImage_Alpha(camera, pos_img_tip.x, pos_img_tip.y, &img_selector_tip);


	// 根据1P玩家选角，切换展示角色动图
	switch (m_1Player_type) {
	case PlayerType::Peashooter:
		animation_peashooter.On_Draw(camera, pos_animation_1P.x, pos_animation_1P.y);
		pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(m_PeashooterName)) / 2;
		outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, m_PeashooterName);
		break;
	case PlayerType::Sunflower:
		animation_sunflower.On_Draw(camera, pos_animation_1P.x, pos_animation_1P.y);
		pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(m_SunflowerName)) / 2;
		outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, m_PeashooterName);
		break;
	default:
		break;

	}

	// 根据2P玩家选角，切换展示角色动图
	switch (m_2Player_type) {
	case PlayerType::Peashooter:
		animation_peashooter.On_Draw(camera, pos_animation_2P.x, pos_animation_2P.y);
		pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(m_PeashooterName)) / 2;
		outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, m_PeashooterName);
		break;
	case PlayerType::Sunflower:
		animation_sunflower.On_Draw(camera, pos_animation_2P.x, pos_animation_2P.y);
		pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(m_SunflowerName)) / 2;
		outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, m_SunflowerName);
		break;
	default:
		break;
	}

	PutImage_Alpha(pos_1P_selector_btn_left.x, pos_1P_selector_btn_left.y,
		is_btn_1P_left_down ? &img_1P_selector_btn_down_left : &img_1P_selector_btn_idle_left);
	PutImage_Alpha(pos_1P_selector_btn_right.x, pos_1P_selector_btn_right.y,
		is_btn_1P_right_down ? &img_1P_selector_btn_down_right : &img_1P_selector_btn_idle_right);
	PutImage_Alpha(pos_2P_selector_btn_left.x, pos_2P_selector_btn_left.y,
		is_btn_2P_left_down ? &img_2P_selector_btn_down_left : &img_2P_selector_btn_idle_left);
	PutImage_Alpha(pos_2P_selector_btn_right.x, pos_2P_selector_btn_right.y,
		is_btn_2P_right_down ? &img_2P_selector_btn_down_right : &img_2P_selector_btn_idle_right);

	// 绘制玩家键位图
	PutImage_Alpha(camera,pos_img_1P_desc.x, pos_img_1P_desc.y, &img_1P_desc);
	PutImage_Alpha(camera,pos_img_2P_desc.x, pos_img_2P_desc.y, &img_2P_desc);

}

void SelectorScene::OnInput(const ExMessage& msg)
{
	switch (msg.message) 
	{
	case WM_KEYDOWN:
		switch (msg.vkcode)
		{
			//"A"
		case 0x41:
			is_btn_1P_left_down = true;
			break;
			//"D"
		case 0x44:
			is_btn_1P_right_down = true;
			break;
			//"⬅"
		case VK_LEFT:
			is_btn_2P_left_down = true;
			break;
		case VK_RIGHT:
			is_btn_2P_right_down = true;
			break;
		default:
			break;
		}
		break;
	case WM_KEYUP:
		switch (msg.vkcode)
		{
			//"A"
		case 0x41:
			is_btn_1P_left_down = false;
			m_1Player_type = (PlayerType)(((int)PlayerType::Invalid + (int)m_1Player_type - 1) % (int)PlayerType::Invalid);
			mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
			break;
			//"D"
		case 0x44:
			is_btn_1P_right_down = false;
			is_btn_1P_right_down = false;

			m_1Player_type = (PlayerType)(((int)PlayerType::Invalid + (int)m_1Player_type + 1) % (int)PlayerType::Invalid);
			mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
			break;
			//"⬅"
		case VK_LEFT:
			is_btn_2P_left_down = false;
			is_btn_2P_left_down = false;
			m_2Player_type = (PlayerType)(((int)m_2Player_type - 1 + (int)PlayerType::Invalid) % (int)PlayerType::Invalid);
			mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
			break;
		case VK_RIGHT:
			is_btn_2P_right_down = false;
			is_btn_2P_right_down = false;
			m_2Player_type = (PlayerType)(((int)m_2Player_type + 1 + (int)PlayerType::Invalid) % (int)PlayerType::Invalid);
			mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
			break;
		case VK_RETURN:
			scene_manager.SwitchScene(SceneManager::SceneType::Game);
			mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}



}

void SelectorScene::on_exit()
{
	// 根据选角 创建玩家角色
	switch (m_1Player_type) 
	{
	case PlayerType::Peashooter:
		player_1P = new Peashooter();
		img_player_1_avatar = &img_avatar_peashooter;
		break;
	case PlayerType::Sunflower:
		player_1P = new Sunflower();
		img_player_1_avatar = &img_avatar_sunflower;
		break;
	default:
		break;
	}
	player_1P->SetID(PlayerID::P1);

	switch (m_2Player_type)
	{
	case PlayerType::Peashooter:
		player_2P = new Peashooter(false);
		img_player_2_avatar = &img_avatar_peashooter;
		break;
	case PlayerType::Sunflower:
		player_2P = new Sunflower(false);
		img_player_2_avatar = &img_avatar_sunflower;
		break;
	default:
		break;
	}
	player_2P->SetID(PlayerID::P2);

	mciSendString(_T("stop bgm_menu"), NULL, 0, NULL);
}

