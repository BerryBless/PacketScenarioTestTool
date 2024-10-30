#include "pch.h"
#include "TestOptionManager.h"
#include "json.hpp"
#include "TextFile.h"

#include <codecvt>  // for wstring_convert
#include <fstream>

bool TestOptionManager::LoadSetting(std::wstring path)
{
	std::ifstream file(path);
	if (file.is_open() == false) 
	{
		LOG_ERROR(L"Fail load file [{}]", path);
		return false;
	}

	try 
	{
		nlohmann::json j;
		file >> j;

		test_option_.bot_count = j.value("bot_count", 0);
		test_option_.thread_count = j.value("thread_count", 0);
		test_option_.is_auto_login = j.value("is_auto_login", false);
		test_option_.is_repeat = j.value("is_repeat", false);


		std::vector<std::wstring> action_list;
		for (const auto& action : j["action_list"]) {
			action_list.push_back(Utf8ToWstring(action.get<std::string>()));
		}
		test_option_.action_list.clear();
		test_option_.action_list.reserve(action_list.size());
		for (auto iter : action_list)
		{
			test_option_.action_list.emplace_back(EnumParser<ActionType, std::wstring>::StringToEnum(iter));
		}

	}
	catch (const std::exception& e) {
		LOG_ERROR("Error extracting settings: ", e.what());
	}
	return true;
}

void TestOptionManager::ExtractSetting(std::wstring path)
{

	FILE* file = _wfsopen(path.c_str(), L"w", _SH_DENYNO);
	if (file == nullptr)
	{
		LOG_ERROR(L"Fail load file [{}]", path);
		return ;
	}

	try 
	{
		nlohmann::json j;
		j["bot_count"] = test_option_.bot_count;
		j["thread_count"] = test_option_.thread_count;
		j["is_auto_login"] = test_option_.is_auto_login;
		j["is_repeat"] = test_option_.is_repeat;

		std::vector<std::string> action_str;
		action_str.reserve(test_option_.action_list.size());
		for (auto iter : test_option_.action_list)
		{
			action_str.emplace_back(WstringToUtf8(EnumParser<ActionType, std::wstring>::EnumToString(iter)));
		}
		j["action_list"] = action_str;


		// 파일에 JSON 형식으로 쓰기
		auto str = j.dump(4);
		std::fwrite(str.c_str(), sizeof(char), str.length(), file);
	}
	catch (const std::exception& e)
	{
		LOG_ERROR("Error extracting settings: ", e.what());
	}

	std::fclose(file);
}
