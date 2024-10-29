#include "pch.h"
#include "TextFile.h"

TextFile::TextFile(const std::wstring& filename)
{
	Create(filename);
}

TextFile::~TextFile()
{
	CloseFile();
}

bool TextFile::Create(const std::wstring& filename)
{
	if (file_)
		return true;

	file_ = _wfsopen(filename.c_str(), L"at", _SH_DENYNO);
	if (!file_)
		return false;

	return true;
}

void TextFile::CloseFile()
{
	if (file_ == nullptr)
		return;
	std::fflush(file_);
	std::fclose(file_);
	file_ = nullptr;
}

void TextFile::Write(const std::string& text)
{
	if (file_ == nullptr)
		return;
	std::fwrite(text.c_str(), sizeof(char), text.length(), file_);
	std::fflush(file_);
}




std::string WstringToMultibyte(const WCHAR* wstr)
{
	return std::string(CW2A(wstr));
}

std::string WstringToMultibyte(const std::wstring& wstr)
{
	return std::string(CW2A(wstr.c_str()));
}

std::wstring MultibyteToWstring(const char* mbcs)
{
	if (mbcs == nullptr)
	{
		return L"";
	}
	return std::wstring(CA2W(mbcs));
}

std::wstring MultibyteToWstring(const std::string& mbcs)
{
	return std::wstring(CA2W(mbcs.c_str()));
}

std::string Utf8ToMultibyte(const std::string& utf8)
{
	// utf8->unicode
	std::wstring wstr(Utf8ToWstring(utf8));
	// unicode->multi
	return WstringToMultibyte(wstr);
}

std::string MultibyteToUtf8(const std::string& mbcs)
{
	// multi->unicode
	std::wstring strUni = MultibyteToWstring(mbcs);
	// unicode->utf8
	return WstringToUtf8(strUni);
}
std::wstring Utf8ToWstring(const std::string& utf8)
{
	size_t len = utf8.length() + 1;
	wchar_t* szUni = new wchar_t[len];
	memset(szUni, 0, len * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), (int)utf8.length(), szUni, (int)len);
	std::wstring strUni(szUni);
	SAFE_DELETE_ARRAY(szUni);
	return strUni;
}

std::string WstringToUtf8(const std::wstring& wstr)
{
	return std::string(CW2A(wstr.c_str(), CP_UTF8));
}