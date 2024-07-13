#pragma once
#include"Scene.h"
#include"Animation.h"
#include"SceneManager.h"
#include"Camera.h"
#include"Timer.h"

#include<iostream>

extern IMAGE img_menu_background;
extern Atlas atlas_peashooter_run_right;
extern SceneManager scene_manager;

class MenuScene : public Scene {
public:
	MenuScene() {}
	~MenuScene() {}


	virtual void OnEnter();
	virtual void OnUpdate(int delta);
	virtual void OnDraw(const Camera& camera);
	virtual void OnInput(const ExMessage& msg);
	virtual void on_exit();

private:
};