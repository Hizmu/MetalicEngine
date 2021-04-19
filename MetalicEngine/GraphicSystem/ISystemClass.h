#pragma once
#include "SettingDesc.h"

#include <type_traits>
#include <Windows.h>
#include <thread>

struct ISystemClass
{
	ISystemClass() = default;
	~ISystemClass() = default;
	virtual SettingDesc getSettingDesc() = 0;
	virtual HWND getWindowHwnd() = 0;
	virtual void setFullScreenMode() = 0;
	virtual void setWindowedMode() = 0;
	virtual bool getWindowMode() = 0;
	
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;

	virtual bool RegisterWindow() = 0;
	virtual bool RegisterWindow(SettingDesc desc) = 0;
	virtual bool CreateWindowME() = 0;
	virtual void updateWindowState() = 0;
	virtual void CloseWindow() = 0;
	virtual void Release() = 0;
	ISystemClass& operator=(const ISystemClass&) = delete;
};

