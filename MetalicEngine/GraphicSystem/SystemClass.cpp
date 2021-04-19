#include "SystemClass.h"

#include "Application/Application.h"

#include "SystemLog/Log.h"

#include "EventSystem/WindowEvent.h"

#include "Main.h"

SystemClass::SystemClass()
{ 
	m_thishwnd = nullptr;
}

SystemClass::~SystemClass() {}

SettingDesc SystemClass::getSettingDesc()
{
	return m_desc;
}
bool SystemClass::RegisterWindow()
{
	SettingDesc desc;
	return RegisterWindow(desc);
}
bool SystemClass::RegisterWindow(SettingDesc desc )
{
	Logs::Log::GetLog()->MsgPrint((char*)"Register Window", Logs::TypeLogs::Print);
	if (!WindowEventSubject())
		return false;

	RECT rect;
	m_desc = desc;
	if ((m_desc.m_height == 0 || m_desc.m_width == 0) ) {
		rect = { 0,0,800,600 };
	}
	else {
		rect = { 0,0,m_desc.m_height,m_desc.m_width };
	}


	WNDCLASSEX wnd;
	HMODULE hInst = GetModuleHandle(NULL);
	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.style = CS_HREDRAW | CS_VREDRAW;
	wnd.lpfnWndProc = Application::WndProc;
	wnd.hInstance = hInst;
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.lpszClassName = m_desc.m_wndclass;
	wnd.hCursor = LoadCursor(0, IDC_ARROW);
	wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wnd.hIconSm = wnd.hIcon;
	wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wnd.lpszMenuName = nullptr;


	if (!RegisterClassEx(&wnd))
	{
		IApplication::getApplication()->getEventSystem()->Notify("Error Window",std::make_shared<WindowMessage>( "Error. Window registration error",WindowEventList::WindowErrorDebug));
		MessageBox(nullptr, L"Error register window .", L"ERROR", MB_OK| MB_ICONERROR);
		return false;
	}
	setWindowedMode();
	return true;
}

bool SystemClass::WindowEventSubject()
{
	if (IApplication::getApplication()->getEventSystem() == nullptr)
		return false;

	IApplication::getApplication()->getEventSystem()->EventSubject(new WindowEvent("Error Window"));
	return true;
}

void SystemClass::setFullScreenMode()
{
	
	DEVMODE screensetting;
	memset(&screensetting, NULL, sizeof(screensetting));
	screensetting.dmPelsWidth = GetSystemMetrics(SM_CYSCREEN);
	screensetting.dmPelsHeight = GetSystemMetrics(SM_CXSCREEN);
	screensetting.dmBitsPerPel = 32;
	screensetting.dmSize = sizeof(screensetting);
	screensetting.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

	ChangeDisplaySettings(&screensetting, CDS_FULLSCREEN);

	m_desc.m_height = GetSystemMetrics(SM_CYSCREEN);
	m_desc.m_width = GetSystemMetrics(SM_CXSCREEN);

	m_desc.m_x = 0;
	m_desc.m_y = 0;
	is_fullscreen = true;
}

bool SystemClass::CreateWindowME()
{
	HMODULE hInst = GetModuleHandle(NULL);


	m_thishwnd = CreateWindowEx(NULL,
		DefClassName,
		L"MyWmd", WS_VISIBLE | WS_POPUP,
		m_desc.m_x, m_desc.m_y, m_desc.m_width, m_desc.m_height,
		NULL, NULL, hInst, Application::getApplication());

	if (!m_thishwnd)
		return false;

	m_isClose = false;
	return true;
}


void SystemClass::setWindowedMode()
{
	DEVMODE screensetting;
	memset(&screensetting, NULL, sizeof(screensetting));
	screensetting.dmPelsWidth = GetSystemMetrics(SM_CYSCREEN) / 2;
	screensetting.dmPelsHeight = GetSystemMetrics(SM_CXSCREEN) / 2;
	screensetting.dmBitsPerPel = 32;
	screensetting.dmSize = sizeof(screensetting);
	screensetting.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

	ChangeDisplaySettings(&screensetting, CDS_FULLSCREEN);

	m_desc.m_height = 600;
	m_desc.m_width = 800;


	m_desc.m_y = ( GetSystemMetrics(SM_CYSCREEN) - getHeight()) / 2;
	m_desc.m_x = (GetSystemMetrics(SM_CXSCREEN) - getWidth()) / 2;
	is_fullscreen = false;
}

bool SystemClass::getWindowMode()
{
	return is_fullscreen;
}

int SystemClass::getWidth()
{
	return  m_desc.m_width;
}

void SystemClass::Run()
{

	if (m_thishwnd == nullptr)
		return;
	ShowWindow(m_thishwnd, SW_SHOW);
	SetForegroundWindow(m_thishwnd);
	SetFocus(m_thishwnd);
	Main();

	while (!m_isClose)
	{
		Frame();
		updateWindowState();
	}
}

void SystemClass::CloseWindow()
{
	Logs::Log::GetLog()->Release();
	m_isClose = true;
}

void SystemClass::Release()
{
	DestroyWindow(m_thishwnd);
}

void SystemClass::RunMessage()
{
	MSG msg;

	while (PeekMessage(&msg, m_thishwnd, NULL, NULL, PM_REMOVE))
	{
		if (m_isClose)
			break;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void SystemClass::Frame()
{
	RunMessage();
	IApplication::getApplication()->getRenderSystem()->Run();
}
void SystemClass::updateWindowState()
{
	::UpdateWindow(m_thishwnd);
}

int SystemClass::getHeight()
{
	return m_desc.m_height;
}

HWND SystemClass::getWindowHwnd()
{
	return m_thishwnd;
}
