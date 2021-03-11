//
// Created by RFMinePC on 2/21/2021.
//

#include "ModelTest.h"
#include "imgui.h"

test::ModelTest::ModelTest()
:m_Model("../res/models/obelisk/", "obelisk")
,m_Shader("../res/shaders/8_modelLoading/cube_vert.shader", "../res/shaders/8_modelLoading/cube_frag.shader")
,m_Camera(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0)) {

    for (auto & pLight : environment.pLights) {
        int randx = rand() % 10;
        int randy = rand() % 10;
        int randz = rand() % 10;

        pLight.pos = glm::vec3(randx, randy, randz);
    }
}

test::ModelTest::~ModelTest() {

}

void test::ModelTest::OnUpdate(float dt) {
    Test::OnUpdate(dt);
    m_Camera.Update(dt);
    m_Shader.Use();
    m_Shader.SetUniform4fv("pv", 1, GL_FALSE, m_Camera.GetProjView());
    m_Shader.SetUniform4fv("model", 1, GL_FALSE, glm::mat4(1.0));

    glm::vec3 diffuseColor = glm::vec3(1.f, 1.f, 1.f) * glm::vec3(1.f);
    glm::vec3 ambientColor = diffuseColor * glm::vec3(1.f);
    for (auto & pLight : environment.pLights) {
        pLight.SetColors(ambientColor, diffuseColor, glm::vec3(0.0));
        pLight.SetAttenuation(0.14f, 0.07f);
    }
    environment.dLights[0].dir = {0, 0, -1};
    environment.dLights[0].SetColors(ambientColor, diffuseColor, glm::vec3(1.0));

    //environment.sLights[0].SetColors(glm::vec3(0.0, 0.4, 0.7), glm::vec3(0.3, 0.2, 0.5), glm::vec3(1.0));
    environment.sLights[0].SetColors(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0));
    environment.sLights[0].SetIntensity(2.0f);
    environment.sLights[0].SetAttenuation(0.14f, 0.07f);
    //environment.sLights[0].pos = m_Camera.m_CamPos;
    //environment.sLights[0].dir = m_Camera.m_CameraFront;

    m_Shader.SetEnvironment("environment", environment);
    m_Model.m_Diff.Use(0);
    m_Model.m_Spec.Use(1);
    m_Shader.SetMaterial("material", m_Model.material);
}

void test::ModelTest::OnRender() {
    Test::OnRender();

    m_Model.Draw(m_Shader, m_IsWireframe);
}

void test::ModelTest::OnResize(int width, int height) {
    Test::OnResize(width, height);
}

void test::ModelTest::OnImGuiRender() {
    Test::OnImGuiRender();

    ImGui::Text("%0.4f %0.4f %0.4f", m_Camera.m_CameraFront.x, m_Camera.m_CameraFront.y, m_Camera.m_CameraFront.z);
    ImGui::Text("%0.4f %0.4f %0.4f", m_Camera.m_CamPos.x, m_Camera.m_CamPos.y, m_Camera.m_CamPos.z);

    ImGui::Checkbox("Wireframe", &m_IsWireframe);
}