#include "EventSystem.h"

#include <Windows.h>



EventSystem::EventSystem()
{

}

EventSystem::~EventSystem()
{

}
void EventSystem::EventSubject(Event* e)
{
	m_eventlist.push_back(e);
}

void EventSystem::Unsubject(Event* e)
{
	if (!m_eventlist.empty()) {
		auto it = FindEvent(e);
		if (it != m_eventlist.end())
			m_eventlist.erase(it);
	}
}
void EventSystem::UnsubjectAll()
{
	if (!m_eventlist.empty())
		m_eventlist.clear();
}

void EventSystem::Notify(std::string name, std::shared_ptr<void> value)
{ 
	if (!m_eventlist.empty())
	{
		for (auto i : m_eventlist)
			i->Update(name,value);
	}
}

std::list<Event*>::iterator EventSystem::FindEvent(Event* e)
{
	if (!m_eventlist.empty())
	{
		for (auto it = m_eventlist.begin(); it != m_eventlist.end(); it++)
		{
			if ((*it)->getName() == e->getName())
			{
				return it;
			}
		}
	}
	return m_eventlist.end();
}

void EventSystem::InputEventProc(unsigned int nMsg, __int64 wParam, __int64 lParam)
{
	switch (nMsg)
	{
	case WM_KEYDOWN:
		Notify("EventKeyPress", std::make_shared<EventKeyCodes>(static_cast<EventKeyCodes>(wParam)));
		break;
	case WM_KEYUP:
		Notify("EventKeyRelease", std::make_shared<EventKeyCodes>(static_cast<EventKeyCodes>(wParam)));
		break;
	case WM_MOUSEMOVE:
		Notify("EventMouseMove", std::make_shared<MousePos>(MousePos({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) })));
		break;
	case WM_LBUTTONDOWN:
		Notify("EventMousePress", std::make_shared<MouseKeyCodes>(MouseKeyCodes::MOUSE_LEFT));
		break;
	case WM_RBUTTONDOWN:
		Notify("EventMousePress", std::make_shared<MouseKeyCodes>(MouseKeyCodes::MOUSE_RIGHT));
		break;
	case WM_MBUTTONDOWN:
		Notify("EventMousePress", std::make_shared<MouseKeyCodes>(MouseKeyCodes::MOUSE_MIDDLE));
		break;
	case WM_MOUSEHWHEEL:
		Notify("EventMousePress", std::make_shared<float>(GET_WHEEL_DELTA_WPARAM(wParam)));
		break;
	}
}