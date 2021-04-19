#pragma once
#include "EventSystem/Event.h"
#include "WindowMessage.h"




class WindowEvent : public Event
{
public:
	WindowEvent(std::string name);
	~WindowEvent();
	void Update(std::string name, std::shared_ptr<void> value)override;
	void setWindowEvent(WindowMessage windowevent);
	WindowMessage getWindowMessage();
private:
	WindowMessage m_windowmessage;
};

