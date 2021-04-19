#pragma once


#include "GraphicSystem/RenderSystem/RenderSystem.h"
#include "GraphicSystem/SystemClass.h"
#include "EventSystem/EventSystem.h"




class IApplication
{
protected:
	IApplication();
	virtual ~IApplication();
public:
	virtual void InitApplication() = 0;

	static IApplication* getApplication();
public:
	virtual EventSystem* getEventSystem() = 0;
	virtual IRenderSystem* getRenderSystem() = 0;
	virtual ISystemClass* getSystemClass() = 0;
	virtual void Run() = 0;
	
public:
	virtual void Release() = 0;
private:
	static IApplication* m_app;
};

