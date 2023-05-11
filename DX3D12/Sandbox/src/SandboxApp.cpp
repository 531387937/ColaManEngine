#include <wtypes.h>
#include "ColaMan.h"

class TestLayer :public ColaMan::Layer
{
public:
	TestLayer() :Layer("Test")
	{

	}

	void OnUpdate() override
	{
		CM_INFO("TesteLayer::Update");
	}

	void OnEvent(ColaMan::Event& event) override
	{
		CM_TRACE("{0}", event);
	}
};

class Sandbox :public ColaMan::Application
{
public:
	Sandbox()
	{
		
	}
	Sandbox(HINSTANCE hInstance) :Application(hInstance) {
		PushLayer(new TestLayer());
	}
	~Sandbox()
	{

	}

};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE preInstance, PSTR cmdLine, int showCmd)
{
	AllocConsole();

	ColaMan::Log::Init();
	CM_CORE_WARN("Initialized log!");
	CM_TRACE("Hello!");
	Sandbox *app = new Sandbox(hInstance);

	return app->Run(hInstance);
}