
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iostream>


struct Round {
	int r, g, b;

	bool valid() {
		return r <= 12 && g <= 13 && b <= 14;
	}
};

struct Game {
	Game(const char *s) {
		while (*s != ':') s++;
		Round cur_round = {0, 0, 0};
		while (*s) {
			while (*s != ' ' && *s) s++;
			s++;
			int cur_value = atoi(s);
			while (*s != ' ' && *s) s++;
			s++;
			if (*s == 'r') cur_round.r = cur_value;
			if (*s == 'g') cur_round.g = cur_value;
			if (*s == 'b') cur_round.b = cur_value;
			while (1) {
				if (*s == ';') {
					rounds.push_back(cur_round);
					cur_round = {0, 0, 0};
					break;
				}
				if (*s == ',' || !*s) break;
				s++;
			}
		}
		rounds.push_back(cur_round);
	}

	bool is_valid() {
		for (auto round : rounds) {
			if (!round.valid()) return false;
		}
		return true;
	}

	int power() {
		int r = 0, g = 0, b = 0;
		for (auto round : rounds) {
			if (round.r > r) r = round.r;
			if (round.g > g) g = round.g;
			if (round.b > b) b = round.b;
		}
		return r * g * b;
	}

	std::vector<Round> rounds;
};

std::ostream &operator<<(std::ostream &os, Game &game) {
	os << "Game";
	for (auto round : game.rounds) {
		os << ", (" << round.r << ", " << round.g << ", " << round.b << ")";
	}
	return os;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "use:" << std::endl;
		std::cout << "\t" << argv[0] << "<in_file>" << std::endl;
	}

	std::ifstream file(argv[1]);
	std::string str;

	int result_1 = 0, result_2 = 0;
	int id = 1;
	while (std::getline(file, str)) {
		if (str.empty()) break;
		auto game = Game{str.c_str()};
		if (game.is_valid()) result_1 += id;
		result_2 += game.power();
		id++;
	}
	std::cout << "1: " << result_1 << std::endl;
	std::cout << "2: " << result_2 << std::endl;

	return 0;
}
