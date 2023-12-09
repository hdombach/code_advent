#include <fstream>
#include <iostream>
#include <ostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

enum Direction {
	RIGHT,
	LEFT,
};

std::vector<Direction> parse_direction(std::string &str) {
	std::vector<Direction> result;
	for (auto c : str) {
		if (c == 'R') {
			result.push_back(RIGHT);
		} else {
			result.push_back(LEFT);
		}
	}
	return result;
}

struct Instruction {
	std::string label, left, right;
	Instruction() = default;
	Instruction(const char *c) {
		label = std::string{c, 3};

		while (*c != '(') c++;
		c++;

		left = std::string{c, 3};

		while (*c != ' ') c++;
		c++;


		right = std::string{c, 3};
	}

	std::string &next(Direction direction) {
		if (direction == Direction::RIGHT) {
			return right;
		} else {
			return left;
		}
	}

	std::ostream &print(std::ostream &os) {
		os << label << " = (" << left << ", " << right << ")";
		return os;
	}
};

struct Instructions {
	std::unordered_map<std::string, Instruction> instructions;
	Instructions(std::ifstream &file) {
		std::string str;

		while (1) {
			std::getline(file, str);
			if (str.size() < 2) break;
			auto instruction = Instruction{str.c_str()};
			instructions.insert({instruction.label, instruction});
		}
	}

	std::ostream &print(std::ostream &os) {
		for (auto &instruction : instructions) {
			os << instruction.first << ": ";
			instruction.second.print(os) << std::endl;;
		}
		return os;
	}
};

int part_1(Instructions &sets, std::vector<Direction> &directions) {
	int result = 0;

	auto current = sets.instructions["AAA"];
	while (1) {
		for (auto direction : directions) {
			auto next = sets.instructions[current.next(direction)];
			//std::cout << " " << current.label << " " << current.next(direction) << " " << next.label << std::endl;
			current = next;
			result++;
		}
		if (current.label == "ZZZ") break;
	}
	return result;
}

uint64_t part_2(Instructions &sets, std::vector<Direction> &directions) {
	auto current = std::vector<Instruction *>{};
	for (auto &set : sets.instructions) {
		if (set.first[2] == 'A') {
			current.push_back(&set.second);
		}
	}

	uint64_t result = 0;
	while (1) {
		bool is_done;
		for (auto direction : directions) {
			is_done = true;
			for (int i = 0; i < current.size(); i++) {
				current[i] = &sets.instructions[current[i]->next(direction)];
				if (current[i]->label[2] != 'Z') is_done = false;
			}
			result++;
			if (result % 1000000 == 0) std::cout << "progress: " << result << std::endl;
		}
		if (is_done) break;
	}
	return result;
}

int main(int argc, char **argv) {
	if (argc != 2 && argc != 3) {
		std::cout << "use:" << std::endl;
		std::cout << "\t" << argv[0] << "<in_file>" << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);
	std::string str;

	std::getline(file, str);
	auto directions = parse_direction(str);
	std::getline(file, str); //empty line

	auto instructions = Instructions{file};

	//std::cout << "part 1: " << part_1(instructions, directions) << std::endl;

	int part_2_value = part_2(instructions, directions);
	std::cout << "part 2: " << part_2_value << std::endl;

	return 0;
}
