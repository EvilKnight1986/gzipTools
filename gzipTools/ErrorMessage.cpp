#include "StdAfx.h"
#include "ErrorMessage.h"

CErrorMessage::CErrorMessage(void)
{
}

CErrorMessage::~CErrorMessage(void)
{
}

void ProcessErrorMessage(LPTSTR pszErrorText)
{
        TCHAR Temp[MAX_PATH] = {0} ;

        LPVOID lpMsgBuf = NULL ;
        FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER 
                | FORMAT_MESSAGE_FROM_SYSTEM,
                NULL,
                GetLastError(),
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                (LPTSTR) &lpMsgBuf,
                0,
                NULL 
                );
        _stprintf_s(Temp, 
                TEXT("WARNING:  %s Failed with the following error: %s"),
                pszErrorText,
                lpMsgBuf, 
                MAX_PATH); 
        MessageBox(NULL, Temp, TEXT("Application Error"), MB_ICONSTOP);
        LocalFree(lpMsgBuf);
}
