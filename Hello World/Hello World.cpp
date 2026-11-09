#include <iostream>
#include <string>
#include <windows.h>


int main(int argc, char* argv[])
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	if (argc > 1 && std::string(argv[1]) == "encrypt")
	{
		std::string text;
		std::string bits1[][2] = { {"00", "h"}, {"01", "һ"}, {"10", "հ"}, {"11", "𝗁"}};
		text += bits1[std::stoi(std::string(argv[2]).substr(0, 2), nullptr, 2)][1];

		std::string bits2[][2] = { {"00", "e"}, {"01", "е"}, {"10", "𝐞"}, {"11", "𝖾"} };
		text += bits2[std::stoi(std::string(argv[2]).substr(2, 2), nullptr, 2)][1];

        text += "ll";

		std::string bits3[][2] = { {"00", "o"}, {"01", "о"}, {"10", "օ"}, {"11", "ο"} };
		text += bits3[std::stoi(std::string(argv[2]).substr(4, 2), nullptr, 2)][1];

        std::string bits4[][2] = {
            {"00000", " "},
            {"00001", " "},
            {"00010", " "},
            {"00011", " "},
            {"00100", " "},
            {"00101", " "},
            {"00110", " "},
            {"00111", " "},
            {"01000", " "},
            {"01001", " "},
            {"01010", " "},
            {"01011", " "},
            {"01100", " "},
            {"01101", " "},
            {"01110", "　"},
            {"01111", "​"},
            {"10000", "‌"},
            {"10001", "‍"},
            {"10010", "⁠"},
            {"10011", "﻿"},
            {"10100", " "},
            {"10101", " "},
            {"10110", "\t"},
            {"10111", "\n"},
            {"11000", "\v"},
            {"11001", "\f"},
            {"11010", "\r"},
            {"11011", "\u0085"},
            {"11100", "\u2028"},
            {"11101", "\u2029"},
            {"11110", "\u034F"},
            {"11111", "\u2063"}
        };
        text += bits4[std::stoi(std::string(argv[2]).substr(6, 5), nullptr, 2)][1];

		text += "w";

        std::string bits6[][2] = { {"00", "o"}, {"01", "о"}, {"10", "օ"}, {"11", "ο"} };
        text += bits6[std::stoi(std::string(argv[2]).substr(12, 2), nullptr, 2)][1];

        std::string bits7[][2] = { {"0", "r"}, {"1", "г"} };
        text += bits7[std::stoi(std::string(argv[2]).substr(14, 1), nullptr, 2)][1];

		text += "l";

        std::string bits8[][2] = { {"00", "d"}, {"01", "ԁ"}, {"10", "ⅾ"}, {"11", "𝖽"} };
        text += bits8[std::stoi(std::string(argv[2]).substr(15, 2), nullptr, 2)][1];

		std::cout << text << std::endl;
	}
    else if (argc > 1 && std::string(argv[1]) == "decrypt")
    {
        std::string text;
        std::string bits1[][2] = { {"h", "00"}, {"һ", "01"}, {"հ", "10"}, {"𝗁", "11"} };
        text += bits1[std::stoi(std::string(argv[2]).substr(0, 1), nullptr, 2)][1];

        std::string bits2[][2] = { {"e", "00"}, {"е", "01"}, {"𝐞", "10"}, {"𝖾", "11"} };
        text += bits2[std::stoi(std::string(argv[2]).substr(1, 1), nullptr, 2)][1];

        text += "ll";

        std::string bits3[][2] = { {"o", "00"}, {"о", "01"}, {"օ", "10"}, {"ο", "11"} };
        text += bits3[std::stoi(std::string(argv[2]).substr(4, 1), nullptr, 2)][1];

        std::string bits4[][2] = {
            {" ", "00000"},
            {" ", "00001"},
            {" ", "00010"},
            {" ", "00011"},
            {" ", "00100"},
            {" ", "00101"},
            {" ", "00110"},
            {" ", "00111"},
            {" ", "01000"},
            {" ", "01001"},
            {" ", "01010"},
            {" ", "01011"},
            {" ", "01100"},
            {" ", "01101"},
            {"　", "01110"},
            {"​", "01111"},
            {"‌", "10000"},
            {"‍", "10001"},
            {"⁠", "10010"},
            {"﻿", "10011"},
            {" ", "10100"},
            {" ", "10101"},
            {"\t", "10110"},
            {"\n", "10111"},
            {"\v", "11000"},
            {"\f", "11001"},
            {"\r", "11010"},
            {"\u0085", "11011"},
            {"\u2028", "11100"},
            {"\u2029", "11101"},
            {"\u034F", "11110"},
            {"\u2063", "11111"}
        };
        text += bits4[std::stoi(std::string(argv[2]).substr(5, 1), nullptr, 2)][1];

        text += "w";

        std::string bits6[][2] = { {"o", "00"}, {"о", "01"}, {"օ", "10"}, {"ο", "11"} };
        text += bits6[std::stoi(std::string(argv[2]).substr(6, 1), nullptr, 2)][1];

        std::string bits7[][2] = { {"r", "0"}, {"г", "1"} };
        text += bits7[std::stoi(std::string(argv[2]).substr(7, 1), nullptr, 2)][1];

        text += "l";

        std::string bits8[][2] = { {"d", "00"}, {"ԁ", "01"}, {"ⅾ", "10"}, {"𝖽", "11"} };
        text += bits8[std::stoi(std::string(argv[2]).substr(9, 1), nullptr, 2)][1];

        std::cout << text << std::endl;
    }
	return 0;
}