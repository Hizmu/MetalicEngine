
#include "Event.h"

Event::Event(std::string name)
{
	m_name = name;
}

std::string Event::getName()
{
	return m_name;
}