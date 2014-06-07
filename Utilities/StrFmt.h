#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <sstream>
#include <cstdio>

#if defined(_MSC_VER)
#define snprintf _snprintf
#endif



//int CmpNoCase(const std::string &str, const std::string &str2)
//{
//	bool same;
//	if (str.size() > str2.size())
//	{
//		same = std::equal(str.cbegin(), str.cend(), str2.cbegin(), [](const char a, const char b) -> bool{ return tolower(a) == tolower(b); });
//	}
//	else
//	{
//		same = std::equal(str2.cbegin(), str2.cend(), str.cbegin(), [](const char a, const char b) -> bool{ return tolower(a) == tolower(b); });
//	}
//	if (same)
//	{
//		return 0;
//	}
//	else
//	{
//		return 1;
//	}
//}

namespace fmt{
	using std::string;
	using std::ostream;
	using std::ostringstream;

	struct empty_t{};

	extern const string placeholder;

	template <typename T>
	std::string AfterLast(const std::string& source, T searchstr)
	{
		size_t search_pos = source.rfind(searchstr);
		search_pos = search_pos == std::string::npos ? 0 : search_pos;
		return source.substr(search_pos);
	}

	template <typename T>
	std::string BeforeLast(const std::string& source, T searchstr)
	{
		size_t search_pos = source.rfind(searchstr);
		search_pos = search_pos == std::string::npos ? 0 : search_pos;
		return source.substr(0, search_pos);
	}

	template <typename T>
	std::string AfterFirst(const std::string& source, T searchstr)
	{
		size_t search_pos = source.find(searchstr);
		search_pos = search_pos == std::string::npos ? 0 : search_pos;
		return source.substr(search_pos);
	}

	template <typename T>
	std::string BeforeFirst(const std::string& source, T searchstr)
	{
		size_t search_pos = source.find(searchstr);
		search_pos = search_pos == std::string::npos ? 0 : search_pos;
		return source.substr(0, search_pos);
	}

	// write `fmt` from `pos` to the first occurence of `fmt::placeholder` to
	// the stream `os`. Then write `arg` to to the stream. If there's no
	// `fmt::placeholder` after `pos` everything in `fmt` after pos is written
	// to `os`. Then `arg` is written to `os` after appending a space character
	template<typename T>
	empty_t write(const string &fmt, ostream &os, string::size_type &pos, T &&arg)
	{
		string::size_type ins = fmt.find(placeholder, pos);

		if (ins == string::npos)
		{
			os.write(fmt.data() + pos, fmt.size() - pos);
			os << ' ' << arg;

			pos = fmt.size();
		}
		else
		{
			os.write(fmt.data() + pos, ins - pos);
			os << arg;

			pos = ins + placeholder.size();
		}
		return{};
	}

	// typesafe version of a sprintf-like function. Returns the printed to
	// string. To mark positions where the arguments are supposed to be
	// inserted use `fmt::placeholder`. If there's not enough placeholders
	// the rest of the arguments are appended at the end, seperated by spaces
	template<typename  ... Args>
	string SFormat(const string &fmt, Args&& ... parameters)
	{
		ostringstream os;
		string::size_type pos = 0;
		std::initializer_list<empty_t> { write(fmt, os, pos, parameters)... };

		if (!fmt.empty())
		{
			os.write(fmt.data() + pos, fmt.size() - pos);
		}

		string result = os.str();
		return result;
	}

	//small wrapper used to deal with bitfields
	template<typename T>
	T by_value(T x) { return x; }

	//wrapper to deal with advance sprintf formating options with automatic length finding
	//can't take strings by reference because of "va_start", so overload it with char *
	string FormatV(const char *fmt, va_list args);

	string FormatV(string fmt, va_list args);

	//wrapper to deal with advance sprintf formating options with automatic length finding
	template<typename  ... Args>
	string Format(const string &fmt, Args&& ... parameters)
	{
		size_t length = 256;
		string str;

		for (;;)
		{
			std::vector<char> buffptr(length);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
			size_t printlen = snprintf(buffptr.data(), length, fmt.c_str(), std::forward<Args>(parameters)...);
#pragma clang diagnostic pop
			if (printlen < length)
			{
				str = string(buffptr.data(), printlen);
				break;
			}
			length *= 2;
		}
		return str;
	}

//#ifdef wxGUI
	//convert a wxString to a std::string encoded in utf8
	//CAUTION, only use this to interface with wxWidgets classes
	std::string ToUTF8(const wxString& right);

	//convert a std::string encoded in utf8 to a wxString
	//CAUTION, only use this to interface with wxWidgets classes
	wxString FromUTF8(const string& right);
//#endif

	//TODO: remove this after every snippet that uses it is gone
	//WARNING: not fully compatible with CmpNoCase from wxString
	int CmpNoCase(const std::string& a, const std::string& b);

	//TODO: remove this after every snippet that uses it is gone
	//WARNING: not fully compatible with CmpNoCase from wxString
	void Replace(std::string &str, const std::string &searchterm, const std::string& replaceterm);

	std::vector<std::string> rSplit(const std::string& source, const std::string& delim);
}
