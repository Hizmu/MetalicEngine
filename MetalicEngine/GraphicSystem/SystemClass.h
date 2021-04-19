



#ifndef _SYSTEMCLASS_
#define _SYSTEMCLASS_

#define WIN32_LEAN_AND_MEAN
#include "EventSystem/EventSystem.h"
#include "ISystemClass.h"

class SystemClass : public ISystemClass
{
public:
	SystemClass();

	SystemClass(const SystemClass&) = delete;
	SystemClass& operator = (const SystemClass&) = delete;
	~SystemClass();
public :

	bool RegisterWindow(SettingDesc desc);
	bool RegisterWindow();
	bool WindowEventSubject();
	bool CreateWindowME();
	void Run();
	void RunMessage();

public:
	SettingDesc getSettingDesc()override;
	void setFullScreenMode()override;
	void setWindowedMode()override;
	bool getWindowMode()override;
	HWND getWindowHwnd()override;
	int getWidth() override;
	int getHeight() override;
	void updateWindowState() override;
	void CloseWindow() override;
	void Release() override;
private:
	void Frame();
private:
    SettingDesc m_desc;
private:
	HWND m_thishwnd;
	bool m_status = false;
	bool m_isActive = false;
	bool m_isClose = true;
	bool is_minimaze = false;
	bool is_fullscreen = false;
	friend class Application;
};




#endif