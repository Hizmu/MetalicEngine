

#ifndef _MOUSE_EVENT_
#define _MOUSE_EVENT_

#include "Event.h"
#include "MousePos.h"

class EventMouseMove : public Event
{
public:
	EventMouseMove(std::string name);

	~EventMouseMove()override;      
	virtual void Update(std::string name, std::shared_ptr<void> value) override;
public:
	void setMousePos(MousePos pos);
	int getMouseX();
	int getMouseY();
	MousePos getMousePos();
private:
	MousePos pos;
};

class EventMousePress : public Event
{
public:
	EventMousePress(std::string name);

	~EventMousePress()override;
	void Update(std::string name, std::shared_ptr<void> value) override;
	void setMouseKeyCodes(MouseKeyCodes keycodes);
	MouseKeyCodes getMouseKeyCodes();
private:
	MouseKeyCodes keycodes;
};

class EventMouseRelease : public Event
{
public:
	EventMouseRelease(std::string name);
	~EventMouseRelease()override;
	void Update(std::string name, std::shared_ptr<void> value) override;
	void setMouseKeyCodes(MouseKeyCodes keycodes);
	MouseKeyCodes getMouseKeyCodes();
private:
	MouseKeyCodes keycodes;
};
class EventMouseWheel : public Event
{
public:
	EventMouseWheel(std::string name);
	~EventMouseWheel()override;

	void setMouseScrollWheel(float scroll);
	float getMouseScrollWheel();
	void Update(std::string name, std::shared_ptr<void> value) override;
private:
	float scroll;
};


#endif