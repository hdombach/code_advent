#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <set>
#include <string>
#include <vector>

struct Card {
	std::set<int> winning;
	std::vector<int> numbers;

	Card(std::string &str) {
		const char *c = str.c_str();
		while (*c != ':') c++;
		c++;
		while (*c == ' ') c++;

		while (1) {
			int num = atoi(c);
			winning.insert(num);
			while (*c != ' ') c++;
			while (*c == ' ') c++;
			if (*c == '|') break;
		}
		c++;

		while (1) {
			while (*c == ' ') c++;
			if (*c == '\n' || *c == '\0') break;
			int num = atoi(c);
			numbers.push_back(num);
			while (isdigit(*c)) c++;

		}
	}

	std::ostream &print(std::ostream &os) {
		os << "winning: ";
		for (auto num : winning) {
			os << num << " ";
		}
		os << "actual: ";
		for (auto num : numbers) {
			os << num << " ";
		}
		return os;
	}

	int score() {
		int num = num_matching(), result = 0;
		if (num > 0) {
			result = 1;
			num--;
		}
		while (num) {
			result *= 2;
			num--;
		}
		return result;
	}

	int num_matching() {
		int result = 0;
		for (auto num : numbers) {
			if (winning.count(num)) result++;
		}
		return result;
	}
};

int part_1(std::vector<Card> &cards) {
	int result = 0;

	for (auto &card : cards) {
		result += card.score();
	}

	return result;
}

int part_2(std::vector<Card> &cards) {
	auto counts = std::vector<int>(cards.size(), 1);
	int i = 0;
	for (auto &card : cards) {
		int count = card.num_matching();
		for (int offset = 1; offset <= count; offset++) {
			counts[offset + i] += counts[i];
		}
		i++;
	}

	int result = 0;
	for (auto count : counts) {
		result += count;
	}
	return result;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "use:" << std::endl;
		std::cout << "\t" << argv[0] << "<in_file>" << std::endl;
	}

	std::ifstream file(argv[1]);
	std::string str;

	std::vector<Card> cards;
	while (std::getline(file, str)) {
		if (str.empty()) break;
		auto card = Card{str};
		cards.push_back(card);
	}

	std::cout << "part 1: " << part_1(cards) << std::endl;

	std::cout << "part 2: " << part_2(cards) << std::endl;
	return 0;
}
