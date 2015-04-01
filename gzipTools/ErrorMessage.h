#pragma once

#define NULLVALUE_CHECK(value,fName) if(NULL == value){\
        OutputDebugStringA(#fName);\
        OutputDebugString(_T(" ")); \
        OutputDebugStringA(#value) ;\
        OutputDebugString(_T(" ")); \
        OutputDebugString(_T("can't NULL !\r\n")) ;\
        return FALSE;}

#define NULLVALUE_CHECK_NO_RETURN(value,fName) if(NULL == value){\
        OutputDebugStringA(#fName);\
        OutputDebugString(_T(" ")); \
        OutputDebugStringA(#value) ;\
        OutputDebugString(_T(" ")); \
        OutputDebugString(_T("can't NULL !\r\n")) ;\
        return ;}

class CErrorMessage
{
public:
        CErrorMessage(void);
        ~CErrorMessage(void);
} ;
void ProcessErrorMessage(LPTSTR pszErrorText);



