#include <iostream>
#include <string>
#include <sstream>
#include <locale>
#include <codecvt>
#include <iomanip>

std::string convertToUCS2LE(const std::string& input)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;
    std::wstring ucs2Str = converter.from_bytes(input);
    std::stringstream ss;
    ss << std::hex;
    for (const auto& c : ucs2Str) {
        ss << std::setw(4) << std::setfill('0') << static_cast<unsigned short>(c);
    }
    return ss.str();
}

