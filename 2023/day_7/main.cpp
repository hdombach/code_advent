#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

bool g_is_part_2 = false;

int parse_card(char c) {
	if (g_is_part_2) {
		switch (c) {
			case 'J': return 0;
			case '2': return 1;
			case '3': return 2;
			case '4': return 3;
			case '5': return 4;
			case '6': return 5;
			case '7': return 6;
			case '8': return 7;
			case '9': return 8;
			case 'T': return 9;
			case 'Q': return 10;
			case 'K': return 11;
			case 'A': return 12;
			default: return -1;
		}
	} else {
		switch (c) {
			case '2': return 0;
			case '3': return 1;
			case '4': return 2;
			case '5': return 3;
			case '6': return 4;
			case '7': return 5;
			case '8': return 6;
			case '9': return 7;
			case 'T': return 8;
			case 'J': return 9;
			case 'Q': return 10;
			case 'K': return 11;
			case 'A': return 12;
			default: return -1;
		}
	}
}

const char *card_str() {
	if (g_is_part_2) {
		return "J23456789TQKA";
	} else {
		return "23456789TJQKA";
	}
}

enum HandType {
	None = 0,
	OnePair,
	TwoPair,
	ThreeOfKind,
	FullHouse,
	FourOfKind,
	FiveOfKind,
};

struct Hand;

HandType hand_type(Hand&);

struct Hand {
	std::vector<int> cards;
	std::array<int, 13> counts;
	HandType type;
	int wild_cards;
	int bid;

	Hand(const char *c) {
		counts = std::array<int, 13>{};
		wild_cards = 0;
		while (*c != ' ') {
			int card = parse_card(*c);
			if (*c == 'J') wild_cards++;
			cards.push_back(card);
			counts[card]++;
			c++;
		}
		c++;
		bid = atoi(c);
		if (g_is_part_2) counts[0] = 0;
		std::sort(counts.begin(), counts.end());
		std::reverse(counts.begin(), counts.end());
		if (g_is_part_2) counts[0] += wild_cards;
		type = hand_type(*this);
	}

	std::ostream &print(std::ostream &os) {
		for (auto card : cards) {
			os << card_str()[card];
		}
		os << " ";
		for (auto count : counts) {
			os << count;
		}
		os << " (" << type << ") " << bid;
		return os;
	}

	bool operator<(const Hand &rhs) const {
		if (type < rhs.type) return true;
		if (type > rhs.type) return false;

		for (int i = 0; i < cards.size(); i++) {
			if (cards[i] == rhs.cards[i]) continue;
			return cards[i] < rhs.cards[i];
		}
		return false;
	}
};

HandType hand_type(Hand &hand) {
	auto &counts = hand.counts;
	if (counts[0] == 5) return HandType::FiveOfKind;
	if (counts[0] == 4) return HandType::FourOfKind;
	if (counts[0] == 3 && counts[1] == 2) return HandType::FullHouse;
	if (counts[0] == 3) return HandType::ThreeOfKind;
	if (counts[0] == 2 && counts[1] == 2) return HandType::TwoPair;
	if (counts[0] == 2) return HandType::OnePair;
	return HandType::None;
}

int main(int argc, char **argv) {
	if (argc != 2 && argc != 3) {
		std::cout << "use:" << std::endl;
		std::cout << "\t" << argv[0] << "<in_file>" << std::endl;
		return 1;
	}

	if (argc == 3) g_is_part_2 = true;

	std::ifstream file(argv[1]);
	auto hands = std::vector<Hand>{};
	std::string str;
	while (1) {
		std::getline(file, str);
		if (str.size() < 1) break;
		hands.push_back(Hand(str.c_str()));
	}

	std::sort(hands.begin(), hands.end());

	uint64_t part_1 = 0;
	for (uint64_t i = 0; i < hands.size(); i++) {
		auto &hand = hands[i];
		part_1 += hand.bid * (i+1);
	}

	for (auto &hand : hands) {
		hand.print(std::cout) << std::endl;
	}

	std::cout << "result: " << part_1 << std::endl;
}
