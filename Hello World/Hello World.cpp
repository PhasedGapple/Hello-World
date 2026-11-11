#include <iostream>
#include <string>
#include <windows.h>

std::string toUtf8(const wchar_t* value)
{
	int size = WideCharToMultiByte(CP_UTF8, 0, value, -1, nullptr, 0, nullptr, nullptr);
	if (size <= 1)
		return "";

	std::string result(size, '\0');
	WideCharToMultiByte(CP_UTF8, 0, value, -1, result.data(), size, nullptr, nullptr);
	result.pop_back();
	return result;
}

int wmain(int argc, wchar_t* argv[])
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	if (argc > 2 && std::wstring(argv[1]) == L"encrypt")
	{
		const std::string input = toUtf8(argv[2]);
		if (input.size() != 16 || input.find_first_not_of("01") != std::string::npos)
		{
			std::cerr << "Encryption input must contain exactly 16 binary digits." << std::endl;
			return 1;
		}

		std::string text;

		std::string bits1[][2] = { {"00", "h"}, {"01", "һ"}, {"10", "հ"}, {"11", "𝗁"} };
		text += bits1[std::stoi(input.substr(0, 2), nullptr, 2)][1];

		std::string bits2[][2] = { {"00", "e"}, {"01", "е"}, {"10", "𝐞"}, {"11", "𝖾"} };
		text += bits2[std::stoi(input.substr(2, 2), nullptr, 2)][1];

		text += "ll";

		std::string bits3[][2] = { {"00", "o"}, {"01", "о"}, {"10", "օ"}, {"11", "ο"} };
		text += bits3[std::stoi(input.substr(4, 2), nullptr, 2)][1];

		std::string bits4[][2] = {
			{"00000", " "}, {"00001", " "}, {"00010", " "}, {"00011", " "},
			{"00100", " "}, {"00101", " "}, {"00110", " "}, {"00111", " "},
			{"01000", " "}, {"01001", " "}, {"01010", " "}, {"01011", " "},
			{"01100", " "}, {"01101", " "}, {"01110", "　"}, {"01111", "​"},
			{"10000", "‌"}, {"10001", "‍"}, {"10010", "⁠"}, {"10011", "﻿"},
			{"10100", " "}, {"10101", " "}, {"10110", "\t"}, {"10111", "\n"},
			{"11000", "\v"}, {"11001", "\f"}, {"11010", "\r"}, {"11011", toUtf8(L"\u0085")},
			{"11100", toUtf8(L"\u2028")}, {"11101", toUtf8(L"\u2029")}, {"11110", toUtf8(L"\u034F")}, {"11111", toUtf8(L"\u2063")}
		};
		text += bits4[std::stoi(input.substr(6, 5), nullptr, 2)][1];

		text += "w";

		std::string bits5[][2] = { {"00", "o"}, {"01", "о"}, {"10", "օ"}, {"11", "ο"} };
		text += bits5[std::stoi(input.substr(11, 2), nullptr, 2)][1];

		std::string bits6[][2] = { {"0", "r"}, {"1", "г"} };
		text += bits6[std::stoi(input.substr(13, 1), nullptr, 2)][1];

		text += "l";

		std::string bits7[][2] = { {"00", "d"}, {"01", "ԁ"}, {"10", "ⅾ"}, {"11", "𝖽"} };
		text += bits7[std::stoi(input.substr(14, 2), nullptr, 2)][1];

		std::cout << text << std::endl;
	}
	else if (argc > 2 && std::wstring(argv[1]) == L"decrypt")
	{
		const std::string input = toUtf8(argv[2]);
		std::string bits;
		size_t pos = 0;

		std::string bits1[][2] = { {"h", "00"}, {"һ", "01"}, {"հ", "10"}, {"𝗁", "11"} };
		std::string bits2[][2] = { {"e", "00"}, {"е", "01"}, {"𝐞", "10"}, {"𝖾", "11"} };
		std::string bits3[][2] = { {"o", "00"}, {"о", "01"}, {"օ", "10"}, {"ο", "11"} };
		std::string bits6[][2] = { {"r", "0"}, {"г", "1"} };
		std::string bits7[][2] = { {"d", "00"}, {"ԁ", "01"}, {"ⅾ", "10"}, {"𝖽", "11"} };
		std::string bits4[][2] = {
			{" ", "00000"}, {" ", "00001"}, {" ", "00010"}, {" ", "00011"},
			{" ", "00100"}, {" ", "00101"}, {" ", "00110"}, {" ", "00111"},
			{" ", "01000"}, {" ", "01001"}, {" ", "01010"}, {" ", "01011"},
			{" ", "01100"}, {" ", "01101"}, {"　", "01110"}, {"​", "01111"},
			{"‌", "10000"}, {"‍", "10001"}, {"⁠", "10010"}, {"﻿", "10011"},
			{" ", "10100"}, {" ", "10101"}, {"\t", "10110"}, {"\n", "10111"},
			{"\v", "11000"}, {"\f", "11001"}, {"\r", "11010"}, {toUtf8(L"\u0085"), "11011"},
			{toUtf8(L"\u2028"), "11100"}, {toUtf8(L"\u2029"), "11101"}, {toUtf8(L"\u034F"), "11110"}, {toUtf8(L"\u2063"), "11111"}
		};

		auto matchSymbol = [&](std::string table[][2], int size) -> std::string {
			for (int i = 0; i < size; i++) {
				const std::string& sym = table[i][0];
				if (input.compare(pos, sym.size(), sym) == 0) {
					pos += sym.size();
					return table[i][1];
				}
			}
			return "";
		};

		// Decode: h e l l o [space] w o r l d
		bits += matchSymbol(bits1, 4);  // h
		bits += matchSymbol(bits2, 4);  // e

		if (input.compare(pos, 1, "l") != 0) {
			std::cerr << "Invalid encoded text." << std::endl;
			return 1;
		}
		pos++;  // skip 'l'

		if (input.compare(pos, 1, "l") != 0) {
			std::cerr << "Invalid encoded text." << std::endl;
			return 1;
		}
		pos++;  // skip 'l'

		bits += matchSymbol(bits3, 4);  // o
		bits += matchSymbol(bits4, 32); // space

		if (input.compare(pos, 1, "w") != 0) {
			std::cerr << "Invalid encoded text." << std::endl;
			return 1;
		}
		pos++;  // skip 'w'

		bits += matchSymbol(bits3, 4);  // o
		bits += matchSymbol(bits6, 2);  // r

		if (input.compare(pos, 1, "l") != 0) {
			std::cerr << "Invalid encoded text." << std::endl;
			return 1;
		}
		pos++;  // skip 'l'

		bits += matchSymbol(bits7, 4);  // d

		if (pos != input.size() || bits.size() != 16) {
			std::cerr << "Invalid encoded text." << std::endl;
			return 1;
		}

		std::cout << bits << std::endl;
	}
	else
	{
		std::cout << "Usage:\n  encrypt 16BITVALUE - encrypts 16 bits\n  decrypt \"TEXT\" - decrypts text\n";
		}

	return 0;
}
