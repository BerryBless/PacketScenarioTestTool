#pragma once
#include <shlobj_core.h>

//////////////////////////////////
// 파일 관리 클래스
// utf8로 파일 저장 하기
//////////////////////////////////
class TextFile
{
public:
	TextFile() = default;
	TextFile(const std::wstring& filename);
	~TextFile();
	bool Create(const std::wstring& filename);
	void CloseFile();
	void Write(const std::string& text);
private:
	FILE* file_ = nullptr;
};


// 문자셋 변환 함수들

//! https://msdn.microsoft.com/ko-kr/library/ms235631.aspx
//! https://msdn.microsoft.com/en-us/library/87zae4a3.aspx
std::string WstringToMultibyte(const WCHAR* wstr);
std::string WstringToMultibyte(const std::wstring& wstr);
std::string WstringToUtf8(const std::wstring& wstr);

std::wstring MultibyteToWstring(const char* mbcs);
std::wstring MultibyteToWstring(const std::string& mbcs);
std::string MultibyteToUtf8(const std::string& mbcs);

std::string Utf8ToMultibyte(const std::string& utf8);
std::wstring Utf8ToWstring(const std::string& utf8);