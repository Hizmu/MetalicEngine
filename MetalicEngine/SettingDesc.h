
#define DefClassName L"MetalicEngine" 

#ifndef _SETTINGDESC_
#define _SETTINGDESC_

struct SettingDesc
{
	long m_width = 0;
	long m_height = 0;
	int m_x = 0;
	int m_y = 0;
	wchar_t* m_wndclass = (wchar_t*)DefClassName;
};

#endif