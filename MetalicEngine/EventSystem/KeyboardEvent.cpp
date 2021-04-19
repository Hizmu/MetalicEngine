
#include "KeyboardEvent.h"
#include "Application/IApplication.h"

EventKeyPress::EventKeyPress(std::string name) :Event(name) { m_keycodes = EventKeyCodes::KEY_NONE; }
EventKeyPress::~EventKeyPress() {}
EventKeyRelease::EventKeyRelease(std::string name) : Event(name) { m_keycodes = EventKeyCodes::KEY_NONE; }
EventKeyRelease::~EventKeyRelease() {}
void EventKeyPress::Update(std::string name, std::shared_ptr<void> value)
{

	if (this->getName() != name)
		return;

	EventKeyCodes val = (*reinterpret_cast<EventKeyCodes*> (value.get()));


	this->setKeyCodes(val);
	if (this->getKeyCodes() == EventKeyCodes::KEY_ESCAPE)
		IApplication::getApplication()->getSystemClass()->CloseWindow();
		
}

void EventKeyPress::setKeyCodes(EventKeyCodes key)
{
	m_keycodes = key;
}

EventKeyCodes EventKeyPress::getKeyCodes()
{
	return m_keycodes;
}

void EventKeyRelease::Update(std::string name, std::shared_ptr<void> value)
{
	if (this->getName() != name)
		return;
	

}

void EventKeyRelease::setKeyCodes(EventKeyCodes key)
{
	m_keycodes = key;
}

EventKeyCodes EventKeyRelease::getKeyCodes()
{
	return m_keycodes;
}