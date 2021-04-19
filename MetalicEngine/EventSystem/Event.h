#pragma once

#ifndef _EVENT_
#define _EVENT_

#include <string>
#include <memory>
#include "KeyCodes.h"

class Event
{
public:
	Event() = default;
	Event(std::string);

	virtual ~Event() = default;
public :
	virtual void Update(std::string name, std::shared_ptr<void> value) = 0;
	virtual std::string getName();
private:
	std::string m_name;
};

#endif