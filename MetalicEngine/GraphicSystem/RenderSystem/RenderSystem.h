

#ifndef _RENDER_SYSTEM_
#define _RENDER_SYSTEM_

#include "IRenderSystem.h"
#define ProjectPath(string,size) GetCurrentDirectory(size,string)

class RenderSystem : public IRenderSystem
{
public:

	RenderSystem();
public:

	void Init();
	void Run();
	void Release();
	void SetViewPort();
	RenderingInterfaces getRenderInterfaces() { return m_interfaces; }

	void enableMultisampling() { m_Enable4xMsaa = true; }
	void disableMultisampling() { m_Enable4xMsaa = false; }
	bool getEnableMultisampling() {return m_Enable4xMsaa; };
	void enableVsync() { m_Vsync = true; };
	void disableVsync() { m_Vsync = false; };
	void setRenderInterfaces(RenderingInterfaces rend) { m_interfaces = rend; }

	void setBackgroundColor(COLOR color);
private:
	~RenderSystem();
private:
	RenderingInterfaces m_interfaces;
	bool m_Enable4xMsaa = false;
	bool m_Vsync = false;
	
	unsigned int m_videoCardMemory = 0;
	std::string m_videoCardDescription;
};



#endif