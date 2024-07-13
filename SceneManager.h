#pragma once
#include"Scene.h"


extern Scene* menu_scene;
extern Scene* game_scene;
extern Scene* selector_scene;



class SceneManager {
public:
	enum class SceneType {
		Menu,
		Selector,
		Game
	};

public:

	SceneManager() {};
	~SceneManager() {};

	void SetCurrenetScene(Scene* scene) {
		m_CurrentScene = scene;
		m_CurrentScene->OnEnter();
	}

	void SwitchScene(SceneType type) {
		m_CurrentScene->on_exit();

		switch (type) 
		{
		case SceneType::Menu:
			m_CurrentScene = menu_scene;
			break;
		case SceneType::Selector:
			m_CurrentScene = selector_scene;
			break;
		case SceneType::Game:
			m_CurrentScene = game_scene;
			break;
		default:
			break;
		}
		m_CurrentScene->OnEnter();
	}


	void OnUpdate(int delta) {
		m_CurrentScene->OnUpdate(delta);
	}

	void OnInput(const ExMessage& msg) {
		m_CurrentScene->OnInput(msg);
	}

	void OnDraw(const Camera& camera) {
		m_CurrentScene->OnDraw(camera);
	}

private:
	Scene* m_CurrentScene = nullptr;
};