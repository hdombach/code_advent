
//dist = (time - speed) * speed
//dist = time * speed - speed * speed
//0 = -dist + time * speed - speed * speed
//a = -1, b = time, c = -dist
//speed = (-b + sqrt(b*b - 4ac)) / 2a
//speed = (-time + sqrt(time * time - 4 * dist)) / -2

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Race {
	float time, dist;

	std::ostream &print(std::ostream &os) {
		os << "{time: " << time << ", dist: " << dist << "}";
		return os;
	}
};

std::vector<float> parse_num_list(std::string &str) {
	auto numbs = std::vector<float>{};
	const char *c = str.c_str();
	while (*c != ':') c++;
	c++;
	while (1) {
		while (*c == ' ') c++;
		if (!*c || *c == '\n') break;
		numbs.push_back(atoi(c));
		while (isdigit(*c)) c++;
	}
	return numbs;
}

float parse_chunk_num(std::ifstream &file) {
	std::string str;
	std::getline(file, str);
	float result = 0;
	for (auto c : str) {
		if (isdigit(c)) {
			result = result * 10 + c - '0';
		}
	}
	return result;
}

std::vector<Race> parse_races(std::ifstream &fstream) {
	auto races = std::vector<Race>{};
	std::string str;

	std::getline(fstream, str);
	auto times = parse_num_list(str);

	std::getline(fstream, str);
	auto dist = parse_num_list(str);

	for (int i = 0; i < times.size(); i++) {
		races.push_back({times[i], dist[i]});
	}

	return races;
}

//dist = (time - speed) * speed
//dist = time * speed - speed * speed
//0 = -dist + time * speed - speed * speed
//a = -1, b = time, c = -dist
//speed = (-b +0 sqrt(b*b - 4ac)) / 2a
//speed = (-time +- sqrt(time * time - 4 * dist)) / -2


int get_ways(Race &race) {
	float min = (-race.time + sqrt(race.time * race.time - 4 * race.dist)) / -2;
	float max = (-race.time - sqrt(race.time * race.time - 4 * race.dist)) / -2;

	if (race.dist == race.time * ceil(min) - ceil(min) * ceil(min)) min++;
	if (race.dist == race.time * floor(max) - floor(max) * floor(max)) max--;

	//std::cout << ceil(min) << ", " << floor(max) << ", ";
	//std::cout << min << ", " << max << ", ";

	return floor(max) - ceil(min) + 1;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "use:" << std::endl;
		std::cout << "\t" << argv[0] << "<in_file>" << std::endl;
		return 1;
	}

	auto file = std::ifstream{argv[1]};
	auto races = parse_races(file);
	int part_1 = 1;
	for (auto &race : races) {
		part_1 *= get_ways(race);
	}

	std::cout << "part 1: " << part_1 << std::endl;

	file.clear();
	file.seekg(0);

	auto race = Race{parse_chunk_num(file), parse_chunk_num(file)};
	std::cout << "part 2: " << get_ways(race) << std::endl;
	//had to subtract 1 for part 2 but what ever
}
