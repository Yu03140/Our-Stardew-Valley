#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <memory>
#include <vector>
#include <string>
#include "Scene.h"  // ������� Scene ��ͷ�ļ�

// ����������������
class SceneManager {
private:
    std::shared_ptr<Scene> currentScene;  // ��ǰ��ĳ���
    std::vector<std::shared_ptr<Scene>> scenes;  // ���м��صĳ���

public:
    // ���캯�����������г���
    SceneManager();

    // ����һ������
    void loadScene(const std::shared_ptr<Scene>& scene);

    // �л���ָ���ĳ���
    void switchScene(const std::string& sceneName);

    // ���µ�ǰ����
    void update();

    // ��Ⱦ��ǰ����
    void render();

    // ��������
    ~SceneManager();
};

#endif // SCENEMANAGER_H
