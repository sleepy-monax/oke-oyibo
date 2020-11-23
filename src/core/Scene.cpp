//
// Created by oslo on 11/23/20.
//

#include "Scene.h"

namespace core
{
    Scene::Scene() {}

    Scene::~Scene() {

    }

    void Scene::update(Time& time) {
        printf("Scene update");
        time.elapsed();
    }

    void Scene::render() {
        printf("Scene render");
    }

    void Scene::on_switch_in() {
        printf("Scene on switch in");
    }

    void Scene::on_switch_out() {
        printf("Scene on switch out");
    }
}
