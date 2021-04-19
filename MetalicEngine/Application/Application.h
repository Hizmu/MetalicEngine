#pragma once

#include "IApplication.h"



class Application : public IApplication
{
private:
	Application();
	~Application();
	static Application* getApplication();
public:
	 static LRESULT WINAPI WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
	 void InitApplication();
	 EventSystem* getEventSystem()override;
	 IRenderSystem* getRenderSystem()override;
	 ISystemClass* getSystemClass()override;
	 void Release()override;
	 void Run()override;
	

private:

	static Application* m_papp;
	SystemClass* m_psystem;
    EventSystem* m_pevent;
	RenderSystem* m_prender;
	friend class IApplication;
	friend class SystemClass;
}; 