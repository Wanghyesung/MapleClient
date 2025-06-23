#include "pch.h"
#include "NetFunc.h"

unordered_map<string, wstring> GHashWstringName = {};
unordered_map<wstring, string> GHashStringName = {};

wstring StringToWString(const string& str)
{
    if (GHashWstringName.find(str) != GHashWstringName.end())
        return GHashWstringName[str];

    size_t llSize = str.size() + 1; //널문자
    std::wstring wstr(llSize, 0);   //크기 미리 할당

    size_t llNumCvt = 0;
    mbstowcs_s(&llNumCvt, &wstr[0], llSize, str.c_str(), llSize - 1);

    while (TRUE)
    {
        if (wstr.back() == L'\0')
        {
            //널문자 만나기 까지
            wstr.pop_back();
            break;
        }   
        wstr.pop_back();
    }
    
    GHashWstringName[str] = wstr;
    return wstr;
}

string WstringToString(const wstring& _str)
{
    if (GHashStringName.find(_str) != GHashStringName.end())
        return GHashStringName[_str];

    int iSize = WideCharToMultiByte(CP_UTF8, 0, _str.c_str(), -1, NULL, 0, NULL, NULL);
    string str(iSize, 0);
    WideCharToMultiByte(CP_UTF8, 0, _str.c_str(), -1, &str[0], iSize, NULL, NULL);

    GHashStringName[_str] = str;

    return str;
}
