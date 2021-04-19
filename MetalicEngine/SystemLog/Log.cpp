

#include "Log.h"
#include <errno.h>
#include <Windows.h>
#include <string>
#include <locale>
namespace Logs {

	Log* Log::m_Inst  = nullptr;
	
	Log* Log::GetLog()
	{
		return m_Inst = (m_Inst != nullptr) ? m_Inst : new Log();
	}
	Log::Log()
	{
		m_Inst = this;

		if (!Init()) {
			MessageBox(NULL, L"Init Log false",L"ERROR", MB_OK | MB_ICONERROR);
			return;
		}

	}

	Log::~Log()
	{

	}
	bool Log::Init()
	{
		_wmkdir(L"InfoLogs");
		char* buff = new char[256];
		strcpy_s(buff, 256, "InfoLogs\\");
		strcat_s(buff, 256,OnTime((char*)"%H.%M.%S %F.log"));


		fopen_s(&m_File, buff , "w+");


		if (!m_File)
		{
			perror("File opening failed");
			m_Inst = nullptr;
			return FALSE;
		}

		fputs("----------------------------------", m_File);
		fputs( "ENLOGFILE!!!", m_File);
		fputs("----------------------------------", m_File);
		return TRUE;
	}




	void Log::m_print(const char* msg)
	{

		fprintf_s(m_File, "\n %s   %s", OnTime((char*)"%X %x"), msg);

	}

	void Log::Release()
	{
		if (!m_File)
			m_Inst = nullptr;
		else {
			fputs("\n----------------------------------", m_File);
			fputs("ENDLOGFILE!!!", m_File);
			fputs("----------------------------------", m_File);
			fclose(m_File);
			m_File = nullptr;
		}
	}


	void Log::MsgPrint(const char* message, TypeLogs _type)
	{
#ifdef NDEBUG
		if (_type == Logs::TypeLogs::Debug || _type == Logs::TypeLogs::ErrorDebug)
			return;
#endif

			if (!m_File)
			{
				MessageBox(NULL, L"File create false", L"ERROR LOG MsgWarning", MB_OK | MB_ICONERROR);
				Log::~Log();
			}

			char* temp = nullptr;
			switch (_type)
			{
			case Logs::TypeLogs::Debug:

				temp = new char[strlen("Debug :") + 1];
				temp = (char*)"Debug : ";

				break;
			case Logs::TypeLogs::Print:
				temp = new char[strlen("Printf :") + 1];
				temp = (char*)"Print : ";
				break;
			case Logs::TypeLogs::Error:
				temp = new char[strlen("Error :") + 1];
				temp = (char*)"Error : ";
				break;
			case Logs::TypeLogs::Warning:
				temp = new char[strlen("Warning :") + 1];
				temp = (char*)"Warning : ";
				break;
			case Logs::TypeLogs::ErrorDebug:
				temp = new char[strlen("ErrorDebug :") + 1];
				temp = (char*)"ErrorDebug : ";
				break;
			default:
				return;
			}
			size_t SIZE = strlen(temp) + strlen(message) + 1;
			char* buff = new char[SIZE];

			strcpy_s(buff, SIZE, temp);

			strcat_s(buff, SIZE, message);

			Log::m_print(buff);

			delete[]buff;
		
	}
	char* Log::OnTime(char*format)
	{
		struct tm m;
		__time32_t t;

		_time32(&t);

		_localtime32_s(&m, &t);

		static char timebuff[40];

		strftime(timebuff, 40, format, &m);
		return timebuff;
	}
}