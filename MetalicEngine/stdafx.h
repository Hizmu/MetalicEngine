

#ifdef _WIN32
#ifdef _WIN64

#ifdef _MSC_VER
#if _MSC_VER < 1900
#error Error. Please install Microsoft Visual C ++ 2015 or higher version
#endif
#include <Windows.h>
#include <DirectXMath.h>
#include <d3d11.h>
#include <DirectXColors.h>
#endif
#else
#error Dont support Windows32. Please contact support.
#endif
#elif defined (__linux__) || (LINUX)
#error Dont support Linux. Please contact support.
#elif defined (__APPLE__)
#error Dont support Apple. Please contact support.
#endif