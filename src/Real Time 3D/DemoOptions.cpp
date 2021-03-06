
#include "SceneManager.h"
#include "Win32Codes.h"
#include "DemoOptions.h"
#include "Demo.h"

DemoOptions::DemoOptions()
{
    texture.setTexture("data/img/back.png", GL_CLAMP_TO_EDGE);
    texture.getMatrix()->ortho(vec2(0, 1280), vec2(0, 720), vec2(-1, 1));;
    texture.setPosition(vec3(0, 0, 0), vec3(1280, 720, 0));
    texture.prepare();

    header.setText("Demo Options");
    header.setFont("data/img/MavenPro-Regular.ttf");
    header.setPosition(vec2(400, 550));
    header.setSize(100);

    showCollisionBoxes.setPosition("Show Collision Boxes?", vec2(450, 400), vec2(400, 100));
    showCollisionBoxes.getTexture()->setShade(vec4(1.0, 0.0, 0.0, 1.0));
    enablePostEffects.setPosition("Enable Post FX Effects", vec2(450, 250), vec2(400, 100));
    enablePostEffects.getTexture()->setShade(vec4(1.0, 0.0, 0.0, 1.0));
    enableWireframe.setPosition("Enable Wireframe", vec2(450, 100), vec2(400, 100));
    enableWireframe.getTexture()->setShade(vec4(1.0, 0.0, 0.0, 1.0));
    backButton.setPosition("Back", vec2(10, 625), vec2(200, 50));
    backButton.getTexture()->setShade(vec4(1.0, 0.0, 0.0, 1.0));
}

DemoOptions::~DemoOptions()
{
}

void DemoOptions::mousePress(int Key, int State, int x, int y)
{
    if (enableWireframe.mouseState(Key, State, x, y))
    {
        if (Demo::demoSettings.enableFx)
        {
            activateButton(&enablePostEffects);
        }

        Demo::demoSettings.wireframeEnabled = !Demo::demoSettings.wireframeEnabled;
        Demo::demoSettings.enableFx = false;
        activateButton(&enableWireframe);
    }

    if (showCollisionBoxes.mouseState(Key, State, x, y))
    {
        Demo::demoSettings.showBoundingBoxes = !Demo::demoSettings.showBoundingBoxes;
        activateButton(&showCollisionBoxes);
    }

    if (enablePostEffects.mouseState(Key, State, x, y))
    {
        Demo::demoSettings.enableFx = !Demo::demoSettings.enableFx;
        activateButton(&enablePostEffects);
    }

    if (backButton.mouseState(Key, State, x, y))
        SceneManager::get()->switchTo(1);
}

void DemoOptions::activateButton(Button * button)
{
    auto t = button->getTexture();
    auto v = t->getShade();

    if (v == vec4(0.0, 1.0, 0.0, 1.0))
    {
        v = vec4(1.0, 0.0, 0.0, 1.0);
    }
    else
    {
        v = vec4(0.0, 1.0, 0.0, 1.0);
    }

    t->setShade(v);
}

void DemoOptions::onUpdate()
{
    texture.onUpdate();
    header.onUpdate();
}

void DemoOptions::render()
{
    renderer.render2D(GL_FALSE);

    glDisable(GL_DEPTH_TEST);

    renderer.renderTexture(&texture);

    showCollisionBoxes.render(&renderer);
    enablePostEffects.render(&renderer);
    enableWireframe.render(&renderer);
    backButton.render(&renderer);
    header.render();

    glEnable(GL_DEPTH_TEST);

    renderer.render2D(Demo::demoSettings.wireframeEnabled);
}