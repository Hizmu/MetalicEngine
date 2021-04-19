#include "IApplication.h"
#include "Application.h"

IApplication* IApplication::m_app = nullptr;

IApplication::IApplication(){}
IApplication::~IApplication(){}

IApplication* IApplication::getApplication() 
{ 
	if (m_app == nullptr) {
		m_app = Application::getApplication();
		m_app->InitApplication();
	}
	return (IApplication*)m_app;
}
