#pragma once
#include"Scene.h"
#include"SceneManager.h"
#include"Animation.h"
#include"Player.h"
#include"Sunflower.h"
#include"Peashooter.h"

extern Player* player_1P;
extern Player* player_2P;
	
extern IMAGE* img_player_1_avatar;								//1P ���״̬��ͷ��
extern IMAGE* img_player_2_avatar;								//2P ���״̬��ͷ��

extern IMAGE img_avatar_peashooter;								//�㶹����ͷ��ͼƬ
extern IMAGE img_avatar_sunflower;								//���տ�ͷ��ͼƬ

extern SceneManager scene_manager;
extern IMAGE img_VS;											//VS������ͼƬ
extern IMAGE img_1P;											//1P �ı�ͼƬ
extern IMAGE img_2P;											//2P �ı�ͼƬ
extern IMAGE img_1P_desc;										//1P ��λ����ͼƬ
extern IMAGE img_2P_desc;										//2P ��λ����ͼƬ
extern IMAGE img_gravestone_left;								//������ߵ�Ĺ��ͼƬ
extern IMAGE img_gravestone_right;								//�����ұߵ�Ĺ��ͼƬ
extern IMAGE img_selector_tip;									//ѡ�ǽ�����ʾ��Ϣ�ı�ͼƬ
extern IMAGE img_selector_background;							//ѡ�ǽ��汳��ͼ
extern IMAGE img_1P_selector_btn_idle_left;						//1P����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_1P_selector_btn_idle_right;					//1P����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_1P_selector_btn_down_left;						//1P����ѡ��ť����״̬ͼƬ
extern IMAGE img_1P_selector_btn_down_right;					//1P����ѡ��ť����״̬ͼƬ
extern IMAGE img_2P_selector_btn_idle_left;						//2P����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_2P_selector_btn_idle_right;					//2P����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_2P_selector_btn_down_left;						//2P����ѡ��ť����״̬ͼƬ
extern IMAGE img_2P_selector_btn_down_right;					//2P����ѡ��ť����״̬ͼƬ
extern IMAGE img_peashooter_selector_background_left;			//ѡ�ǽ��泯����㶹���ֱ���ͼƬ
extern IMAGE img_peashooter_selector_background_right;			//ѡ�ǽ��泯�ҵ��㶹���ֱ���ͼƬ
extern IMAGE img_sunflower_selector_background_left;			//ѡ�ǽ��泯�ҵ����տ�����ͼƬ
extern IMAGE img_sunflower_selector_background_right;			//ѡ�ǽ��泯�ҵ����տ�����ͼƬ

extern Atlas atlas_peashooter_idle_right;						//�㶹���ֳ������Ĭ�϶�����
extern Atlas atlas_sunflower_idle_right;						//���տ��������Ĭ�϶�����

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
	POINT pos_img_VS = { 0 };								//VS ������ͼƬλ��
	POINT pos_img_tip = { 0 };								//��ʾ��Ϣ�ı�ͼƬλ��
	POINT pos_img_1P = { 0 };								//1P �ı�ͼƬλ��
	POINT pos_img_2P = { 0 };								//2P �ı�ͼƬλ��
	POINT pos_img_1P_desc = { 0 };							//1P ��λ����ͼƬλ��
	POINT pos_img_2P_desc = { 0 };							//2P ��λ����ͼƬλ��
	POINT pos_img_1P_name = { 0 };							//1P ��ɫ�����ı�λ��
	POINT pos_img_2P_name = { 0 };							//2P ��ɫ�����ı�λ��
	POINT pos_animation_1P = { 0 };							//1P ��ɫ����λ��
	POINT pos_animation_2P = { 0 };							//2P ��ɫ����λ��
	POINT pos_img_1P_gravestone = { 0 };					//1P Ĺ��ͼƬλ��
	POINT pos_img_2P_gravestone = { 0 };					//2P Ĺ��ͼƬλ��
	POINT pos_1P_selector_btn_left = { 0 };					//1P �����л���ťλ��
	POINT pos_1P_selector_btn_right = { 0 };				//1P �����л���ťλ��
	POINT pos_2P_selector_btn_left = { 0 };					//2P �����л���ťλ��
	POINT pos_2P_selector_btn_right = { 0 };				//2P �����л���ťλ��

	Animation animation_peashooter;							// �㶹���ֶ���
	Animation animation_sunflower;							// ���տ�����

	PlayerType m_1Player_type = PlayerType::Peashooter;		//1PĬ���㶹����
	PlayerType m_2Player_type = PlayerType::Sunflower;		//2PĬ�����տ�

	LPCTSTR m_PeashooterName = _T("������");				// �㶹������Ϸ��
	LPCTSTR m_SunflowerName = _T("���տ�");					// ���տ���Ϸ��

	int selector_background_scorll_offset_x = 0;			// �������������

	bool is_btn_1P_left_down = false;						//1P �����л���ť�Ƿ���
	bool is_btn_1P_right_down = false;						//1P �����л���ť�Ƿ���
	bool is_btn_2P_left_down = false;						//2P �����л���ť�Ƿ���
	bool is_btn_2P_right_down = false;						//2P �����л���ť�Ƿ���

private:
	void outtextxy_shaded(int x, int y, LPCTSTR str) {
		settextcolor(RGB(45, 45, 45));
		outtextxy(x + 3, y + 3, str);
		settextcolor(RGB(255, 255, 255));
		outtextxy(x, y, str);
	}

};
