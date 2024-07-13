#pragma once
#include"Camera.h"

#include<graphics.h>
#include<iostream>

class Scene {
public:
	Scene(){}
	~Scene(){}

	virtual void OnEnter(){}
	virtual void OnUpdate(int delta) {}
	virtual void OnDraw(const Camera& camera) {}
	virtual void OnInput(const ExMessage& msg) {}
	virtual void on_exit() {}

private:

};