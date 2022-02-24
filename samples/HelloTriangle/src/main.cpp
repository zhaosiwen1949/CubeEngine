#include "framework/VulkanApp.h"
#include "framework/TriangleRenderer.h"

struct MyApp: public CameraApp
{
	MyApp()
	: CameraApp(-95, -95)
	, triangleRenderer(ctx_)
	{
        onScreenRenderers_.emplace_back(triangleRenderer);
	}

	void drawUI() override {}

	void draw3D() override {}

	void update(float deltaSeconds) override
	{
		CameraApp::update(deltaSeconds);
	}

private:
    TriangleRenderer triangleRenderer;
};

int main()
{
	MyApp app;
	app.mainLoop();
	return 0;
}
