#pragma once

#ifndef _KEYBOARD_EVENT_
#define _KEYBOARD_EVENT_
#include "Event.h"

class EventKeyPress : public Event
{
public:
	EventKeyPress(std::string name);
	~EventKeyPress()override;
public:
	void Update(std::string name, std::shared_ptr<void> value) override;
	EventKeyCodes getKeyCodes();
	void setKeyCodes(EventKeyCodes);
private:
	EventKeyCodes m_keycodes;
};

class EventKeyRelease : public Event
{
public:
	EventKeyRelease(std::string name);
	~EventKeyRelease()override;
public:
	void Update(std::string name, std::shared_ptr<void> value) override;
	EventKeyCodes getKeyCodes();
	void setKeyCodes(EventKeyCodes);
private:
	EventKeyCodes m_keycodes;
};
#endif // !_KEYBORD_EVENT_


