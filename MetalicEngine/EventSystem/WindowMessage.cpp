#include "WindowMessage.h"

WindowMessage::WindowMessage(): m_eventlist(WindowEventList::NONE) {};
WindowMessage::WindowMessage(std::string message, WindowEventList eventlist)
{
	this->m_message = message;
	this->m_eventlist = eventlist;
}
WindowMessage::~WindowMessage(){}

std::string WindowMessage::getWindowMessage()
{
	return m_message;
}

WindowEventList WindowMessage::getWindowEventList()
{
	return m_eventlist;
}