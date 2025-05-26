#include "functions.h"


std::string utf8_to_ansi(const std::string& utf8_str) {
    // ��һ����UTF-8 ת��Ϊ UTF-16�����ַ���
    int wide_len = MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(), -1, nullptr, 0);
    if (wide_len == 0) return "";

    std::wstring wide_str(wide_len, 0);
    MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(), -1, &wide_str[0], wide_len);

    // �ڶ�����UTF-16�����ַ��� ת ANSI��GBK ���룩
    int ansi_len = WideCharToMultiByte(CP_ACP, 0, wide_str.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (ansi_len == 0) return "";

    std::string ansi_str(ansi_len, 0);
    WideCharToMultiByte(CP_ACP, 0, wide_str.c_str(), -1, &ansi_str[0], ansi_len, nullptr, nullptr);

    return ansi_str;
}
