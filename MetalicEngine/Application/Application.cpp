#include "Application.h"


Application* Application::m_papp = nullptr;

Application::Application() { m_psystem = nullptr; m_pevent = nullptr; m_prender = nullptr; }
Application::~Application() {}

Application* Application::getApplication()
{
	if (!m_papp) {
		m_papp = new Application();
	}
	return m_papp;
}

LRESULT WINAPI Application::WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	Application* pthis;
	if (nMsg == WM_NCCREATE)
	{
		pthis = static_cast<Application*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		SetLastError(0);
		if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pthis)))
		{
			if (GetLastError() != 0)
				return FALSE;
		}
	}
	else
	{
		pthis = reinterpret_cast<Application*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}
	if (pthis)
	{
		switch (nMsg)
		{
		case WM_KEYDOWN:case WM_KEYUP:	case WM_MOUSEMOVE:	case WM_LBUTTONDOWN:	case WM_RBUTTONDOWN:	case WM_MBUTTONDOWN:case WM_MOUSEHWHEEL:
			pthis->m_pevent->InputEventProc(nMsg, wParam, lParam);
			break;
		case WM_DESTROY:
	        pthis->m_psystem->m_isActive = false;
			pthis->m_psystem->m_isClose = true;
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, nMsg, wParam, lParam);
		}
	}
	return 0;
}

void Application::InitApplication()
{
	m_psystem = new SystemClass();
	m_pevent = new EventSystem();
	m_prender = new RenderSystem();
}

void Application::Release()
{
	m_psystem->Release();
	delete m_pevent;
	m_prender->Release();

}

void Application::Run()
{
	m_psystem->Run();
}

ISystemClass* Application::getSystemClass()
{
	return (ISystemClass*)m_psystem;
}

EventSystem* Application::getEventSystem()
{
	return m_pevent;
}
IRenderSystem* Application::getRenderSystem()
{
	return (IRenderSystem*)m_prender;
}