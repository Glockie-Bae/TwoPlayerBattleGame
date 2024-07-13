#pragma once
#include"Scene.h"
#include"SceneManager.h"
#include"Util.h"
#include"Platform.h"
#include"Player.h"
#include"Sunflower.h"
#include"Peashooter.h"
#include"StatusBar.h"


// �������
extern Player* player_1P;
extern Player* player_2P;

// �������״̬��ͷ��
extern IMAGE* img_player_1_avatar;								//1P ���״̬��ͷ��
extern IMAGE* img_player_2_avatar;								//2P ���״̬��ͷ��

// ������Ϸ����ͼ
extern IMAGE img_sky;											//���ͼƬ
extern IMAGE img_hills;											//ɽ��ͼƬ
extern IMAGE img_platform_large;								//����ƽ̨ͼƬ
extern IMAGE img_platform_small;								//С��ƽ̨ͼƬ

// ������һ�ʤͼ
extern IMAGE img_1P_winner;										//1P ��ʤ�ı�ͼƬ
extern IMAGE img_2P_winner;										//2P ��ʤ�ı�ͼƬ
extern IMAGE img_winner_bar;									//��ʤ����ı�����ͼƬ


// ���������
extern Camera main_camera;										//�����
// ���볡���������
extern SceneManager scene_manager;
//����ƽ̨�б�
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
	const float speed_winner_background = 3.0f;					// ���㶯Ч�����ƶ��ٶ�
	const float speed_winner_text = 1.5f;						// ���㶯Ч�ı��ƶ��ٶ�

	
	bool is_game_over = false;									// �ж���Ϸ�Ƿ����

	POINT pos_img_winner_background = { 0 };					// ���㶯Ч����λ��
	POINT pos_img_winner_text = { 0 };							// ���㶯Ч�ı�λ��
	int pos_x_img_winner_background_dst = 0;					// ���㶯Ч�����ƶ���Ŀ��λ��
	int pos_x_img_winner_text_dst = 0;							// ���㶯Ч�ı��ƶ���Ŀ��λ��

	Timer timer_winner_slide_in;								// ���㶯Ч���붨ʱ��
	Timer timer_winner_slide_out;								// ���㶯Ч������ʱ��
	bool is_slide_out_started = false;							// �жϽ��㶯Ч�Ƿ�ʼ����

private:
	POINT pos_img_sky = { 0 };									// ��ձ���ͼλ��
	POINT pos_img_hills = { 0 };								// ɽ������ͼλ��

	StatusBar status_bar_1P;									// ��� 1 ��״̬��
	StatusBar status_bar_2P;									// ��� 2 ��״̬��
};