#include <fstream>
#include <string>
#include <iostream>
#include <array>

bool g_part_2 = false;

int comp_substr(const char *needle, const char *haystack) {
	while (*needle) {
		if (*needle != *haystack) return 0;
		if (!*haystack) return 0;
		needle++;
		haystack++;
	}
	return 1;
}

int get_digit(char const *c, int *result) {
	if (isdigit(*c)) {
		*result = *c - '0';
		return 1;
	}

	if (!g_part_2) return 0;

	std::array<const char *, 10> numbers{
		"zero",
		"one",
		"two",
		"three",
		"four",
		"five",
		"six",
		"seven",
		"eight",
		"nine"
	};
	for (int i = 0; i < numbers.size(); i++) {
		if (comp_substr(numbers[i], c)) {
			*result = i;
			return 1;
		}
	}
	return 0;
}

int calibration_value(std::string &str) {
	int first = -1, last = -1;
	char const *c = str.c_str();
	while (*c) {
		int digit;
		if (get_digit(c, &digit)) {
			if (first == -1) first = digit;
			last = digit;
		}
		c++;
	}
	
	if (first == -1) return 0;
	return first * 10 + last;
}

int main(int argc, char **argv) {
	if (argc != 2 && argc != 3) {
		std::cout << "use:" << std::endl;
		std::cout << "\t" << argv[0] << "<in_file> <is_part_2>" << std::endl;
	}

	if (argc == 3) {
		g_part_2 = true;
	}

	std::ifstream file(argv[1]);
	std::string str;

	int result = 0;
	while (std::getline(file, str)) {
		result += calibration_value(str);
	}
	std::cout << result << std::endl;
	return 0;
}
