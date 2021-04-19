#include "MouseEvent.h"

#include "SystemLog/Log.h"

EventMouseMove::EventMouseMove(std::string name) : Event(name) { pos.x = 0; pos.y = 0; }
EventMouseMove::~EventMouseMove() {}

EventMousePress::EventMousePress(std::string name) : Event(name) { keycodes = MouseKeyCodes::MOUSE_MAX; }
EventMousePress::~EventMousePress() {}

EventMouseRelease::EventMouseRelease(std::string name) : Event(name) { keycodes = MouseKeyCodes::MOUSE_MAX; }
EventMouseRelease::~EventMouseRelease() {}

EventMouseWheel::EventMouseWheel(std::string name) : Event(name) { scroll = 0; }
EventMouseWheel::~EventMouseWheel() {}

void EventMouseMove::setMousePos(MousePos pos)
{
	this->pos = pos;
}

MousePos EventMouseMove::getMousePos()
{
	return pos;
}
int EventMouseMove::getMouseX()
{
	return pos.x;
}
int EventMouseMove::getMouseY()
{
	return pos.y;
}
void EventMouseMove::Update(std::string name, std::shared_ptr<void> value)
{
	if (this->getName() != name)
		return;
	MousePos pos = (*reinterpret_cast<MousePos*> (value.get()));
	this->setMousePos(pos);
}


void EventMousePress::setMouseKeyCodes(MouseKeyCodes keycodes)
{
	this->keycodes = keycodes;
}
MouseKeyCodes EventMousePress::getMouseKeyCodes()
{
	return keycodes;
}

void EventMousePress::Update(std::string name, std::shared_ptr<void> value)
{

}

void EventMouseRelease::setMouseKeyCodes(MouseKeyCodes keycodes)
{
	this->keycodes = keycodes;
}
MouseKeyCodes EventMouseRelease::getMouseKeyCodes()
{
	return keycodes;
}
void EventMouseRelease::Update(std::string name, std::shared_ptr<void> value)
{

}

void EventMouseWheel::setMouseScrollWheel(float scroll)
{
	this->scroll = scroll;
}
float EventMouseWheel::getMouseScrollWheel()
{
	return scroll;
}
void EventMouseWheel::Update(std::string name, std::shared_ptr<void> value)
{

}