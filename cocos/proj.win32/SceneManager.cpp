#include "SceneManager.h"
#include "MenuScene.h"    // �������ĳ�����ͷ�ļ�
#include "FarmScene.h"
//#include "HomeScene.h"
#include "MinesScene.h"
//#include "ShedScene.h"
#include <iostream>

// ���캯�����������г���
SceneManager::SceneManager() {
    // ���س���
    loadScene(std::make_shared<MenuScene>());
    loadScene(std::make_shared<FarmScene>());
    loadScene(std::make_shared<HomeScene>());
    loadScene(std::make_shared<MinesScene>());
    loadScene(std::make_shared<ShedScene>());
}

// ����һ������
void SceneManager::loadScene(const std::shared_ptr<Scene>& scene) {
    scenes.push_back(scene);
}

// �л�����
void SceneManager::switchScene(const std::string& sceneName) {
    // ���Ҳ��л���ָ�����Ƶĳ���
    for (auto& scene : scenes) {
        if (scene->getName() == sceneName) {
            currentScene = scene;
            currentScene->init();  // ��ʼ������
            std::cout << "Switched to " << sceneName << std::endl;
            break;
        }
    }
}

// ���µ�ǰ����
void SceneManager::update() {
    if (currentScene) {
        currentScene->update();
    }
}

// ��Ⱦ��ǰ����
void SceneManager::render() {
    if (currentScene) {
        currentScene->render();
    }
}

// ��������
SceneManager::~SceneManager() {
    // ����ָ����Զ�������Դ�ͷţ�����Ҫ�ֶ��ͷ�
}
