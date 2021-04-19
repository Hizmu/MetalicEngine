#pragma once


#include <string>
enum class WindowEventList
{
	NONE = 0,
	WindowClose,
	WindowMaximaize,
	WindowMinimaize,
	WindowFullscreenMode,
	WindowWindowsMode,
	WindowError,
	WindowErrorDebug,
};

class WindowMessage
{
public:
	WindowMessage() ;
	WindowMessage(std::string message,WindowEventList eventlist);
	~WindowMessage();
	std::string getWindowMessage();
	WindowEventList getWindowEventList();
private:
	std::string m_message;
	WindowEventList m_eventlist;
};
