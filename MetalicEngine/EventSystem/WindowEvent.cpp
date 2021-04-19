#include "WindowEvent.h"
#include <Application/IApplication.h>
#include  "SystemLog/Log.h"
WindowEvent::WindowEvent(std::string name) : Event(name){}
WindowEvent::~WindowEvent(){}

WindowMessage WindowEvent::getWindowMessage()
{
	return m_windowmessage;
}

void WindowEvent::setWindowEvent(WindowMessage windowevent)
{
	m_windowmessage = windowevent;
}

void WindowEvent::Update(std::string name, std::shared_ptr<void> value)
{
	if (this->getName() != name && name != "Error Render")
		return;

	WindowMessage val = (*reinterpret_cast<WindowMessage*>(value.get()));

	this->setWindowEvent(val);
	switch (this->getWindowMessage().getWindowEventList())
	{
	case WindowEventList::WindowErrorDebug:
#ifdef _DEBUG
		Logs::Log::GetLog()->MsgPrint(this->getWindowMessage().getWindowMessage().c_str(), Logs::TypeLogs::ErrorDebug);
		IApplication::getApplication()->getSystemClass()->CloseWindow();
		IApplication::getApplication()->Release();
		exit(-1);
#endif
		break;
	case WindowEventList::WindowError:
		Logs::Log::GetLog()->MsgPrint(this->getWindowMessage().getWindowMessage().c_str(), Logs::TypeLogs::Error);
		IApplication::getApplication()->getSystemClass()->CloseWindow();
		IApplication::getApplication()->Release();
		exit(-1);
		break;
	default:
		break;
	}
}