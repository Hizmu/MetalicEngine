
#include "Application/IApplication.h"
#include "EventSystem/KeyboardEvent.h"
#include "EventSystem/MouseEvent.h"
#include "EventSystem/WindowEvent.h"


bool ApplicationVerify();

int WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPWSTR lpCmdLine,int nCmdShow)
{
	if (!ApplicationVerify())
		return -1;

	IApplication* app = IApplication::getApplication();
	ISystemClass* system = app->getSystemClass();
	IRenderSystem* render = app->getRenderSystem();
	app->getEventSystem()->EventSubject(new EventKeyPress("EventKeyPress"));
	app->getEventSystem()->EventSubject(new EventMouseMove("EventMouseMove"));
	app->getEventSystem()->EventSubject(new WindowEvent("Error Window"));
	app->getEventSystem()->EventSubject(new WindowEvent("Error Render"));
	system->RegisterWindow();
	system->CreateWindowME();
	render->Init();
	app->Run();
	app->Release();
	return 0;
}

bool ApplicationVerify()
{
	if (!DirectX::XMVerifyCPUSupport()) {
		MessageBox(NULL, L"Your platform does not support DirectXMath. Please contact support.", L"Error", MB_ICONERROR | MB_OK);
		return false;
	}
	return true;
}