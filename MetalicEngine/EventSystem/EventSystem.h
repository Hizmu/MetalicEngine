
#ifndef _EVENT_SYSTEM_
#define _EVENT_SYSTEM_

#include "Event.h"
#include "MousePos.h"

#include <list>

#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))

class EventSystem
{
public:
	EventSystem();
	~EventSystem();
	void EventSubject(Event* e);
	void Unsubject(Event* e);
	void UnsubjectAll();
	void Notify(std::string name, std::shared_ptr<void> value);
	std::list<Event*>::iterator FindEvent(Event* e);
	void InputEventProc(unsigned int nMsg, __int64 wParam, __int64 lParam);
private:
	std::list <Event*> m_eventlist;
};

#endif
