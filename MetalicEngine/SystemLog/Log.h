
#ifndef _LOGS_
#define _LOGS_
#include <stdio.h>

#undef logs
#define logs Logs::Log::GetLog() 

namespace Logs {											

	enum class TypeLogs
	{
		Debug, ErrorDebug,
		Print,
		Error,
		Warning
	};

	class Log
	{
	public:
		
		Log();
		~Log();
		static Log* GetLog();

		bool Init();

		void Release();
		void MsgPrint(const char* message, TypeLogs  );

	

	private:

		static  Log*  m_Inst;
		FILE* __restrict m_File;
		TypeLogs m_type;
		void m_print(const char* msg);
		char* OnTime(char* format);
	
	};	

}
#endif