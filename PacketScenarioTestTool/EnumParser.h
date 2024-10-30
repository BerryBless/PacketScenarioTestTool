#pragma once

//////////////////////////////////////////////////////////////////////////
// enum <-> wstring
// unordered_map 으로 매핑
// enum을 일일히 추가해줘야한다....
//////////////////////////////////////////////////////////////////////////

template <typename T, typename K = std::string>
class EnumParser
{
public:
	EnumParser() {}
	static T StringToEnum(const K& value)
	{
		auto iter = enum_map_.find(value);
		if (iter != std::end(enum_map_))
			return iter->second;
		return static_cast<T>(-1);
	}
	static bool  StringToEnum(T& result, const K& value)
	{
		auto iter = enum_map_.find(value);
		if (iter != std::end(enum_map_))
		{
			result = iter->second;
			return true;
		}
		return false;
	}

	static K EnumToString(T value)
	{
		for (auto iter : enum_map_)
		{
			if (iter.second == value)
				return iter.first;
		}
		return K();
	}

private:
	static std::unordered_map<K, T> enum_map_;
};

/*
// 사용법.
enum class MyColor
{
  White,
  Red,
  Blue,
  Black,
  Count,
};

std::unordered_map<std::wstring, MyColor> EnumParser<MyColor>::enum_map_ =
{
  { "white", MyColor::White },
  { "red", MyColor::Red },
  { "blue", MyColor::Blue }
};

MyColor white_color = EnumParser<MyColor>::StringToEnum("white");
MyColor red_color = EnumParser<MyColor>::StringToEnum("red");
MyColor blue_color = EnumParser<MyColor>::StringToEnum("blue");
MyColor orange_color = EnumParser<MyColor>::StringToEnum("orange");

std::format("{}",EnumParser<MyColor, std::wstring>::EnumToString(MyColor::White));
*/
