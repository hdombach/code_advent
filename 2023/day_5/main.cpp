#include <cstdlib>
#include <iostream>
#include <limits>
#include <ostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

std::vector<uint64_t> parse_seeds(std::string &str) {
	auto result = std::vector<uint64_t>();
	const char *c = str.c_str();
	while (*c != ':') c++;

	while (1) {
		while (*c != ' ' && *c) c++;
		if (!*c) break;
		c++;
		result.push_back(atoi(c));
		while (isdigit(*c)) c++;
	}

	return result;
}

struct MapSeg {
	uint64_t dest, source, length;
	MapSeg(std::string &str) {
		const char *c = str.c_str();
		dest = atoi(c);
		while (*c != ' ') c++;
		c++;
		source = atoi(c);
		while (*c != ' ') c++;
		c++;
		length = atoi(c);
	}

	bool contains(uint64_t value) {
		return (value >= source) && (value < (source + length));
	}

	uint64_t convert(uint64_t value) {
		return value - source + dest;
	}

	std::ostream &print(std::ostream &os) {
		os << "(" << dest << ", " << source << ", " << length << ")";
		return os;
	}
};

struct {
	bool operator()(MapSeg &small, MapSeg &big) {
		return small.source < big.source;
	}
} comp;

struct Map {
	std::vector<MapSeg> segs;
	std::string name;
	Map() = default;
	Map(std::ifstream &fstream) {
		std::string str;
		while (1) {
			std::getline(fstream, str);
			if (isalpha(str[0])) break;
		}
		name = str;

		while (1) {
			std::getline(fstream, str);
			if (!isdigit(str[0])) break;
			segs.push_back(MapSeg(str));
		}
	}

	uint64_t convert(uint64_t value) {
		for (auto &seg : segs) {
			if (seg.contains(value)) {
				return seg.convert(value);
			}
		}
		return value;
	}

	std::ostream &print(std::ostream &os) {
		for (auto &seg : segs) {
			seg.print(os);
		}
		return os;
	}
};

std::vector<Map> parse_maps(std::ifstream &file) {
	std::string str;
	auto maps = std::vector<Map>();
	while (1) {
		maps.push_back(Map(file));
		if (maps.back().name == "humidity-to-location map:") break;
	}
	return maps;
}

struct SeedRange {
	uint64_t start, length;
};

std::vector<SeedRange> parse_seed_ranges(std::vector<uint64_t> &seeds) {
	auto ranges = std::vector<SeedRange>{};
	for (int i = 0; i < seeds.size(); i += 2) {
		ranges.push_back({seeds[i], seeds[i + 1]});
	}
	return ranges;
}

uint64_t convert(uint64_t seed, std::vector<Map> &maps) {
		for (auto &map : maps) {
			seed = map.convert(seed);
		}
		return seed;
}

Map join(Map &lhs, Map &rhs) {
	Map result;
	auto lhs_list = lhs.segs;
	std::sort(lhs_list.begin(), lhs_list.end(), comp);
	auto rhs_list = rhs.segs;
	std::sort(rhs_list.begin(), rhs_list.end(), comp);
	//TODO: should be a smarter way
}

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "use:" << std::endl;
		std::cout << "\t" << argv[0] << "<in_file>" << std::endl;
		return 1;
	}


	auto file = std::ifstream{argv[1]};

	uint64_t part_1 = std::numeric_limits<uint64_t>::max();
	uint64_t part_2 = std::numeric_limits<uint64_t>::max();
	std::string str;
	std::getline(file, str);
	auto seeds = parse_seeds(str);
	auto maps = parse_maps(file);

	for (uint64_t seed : seeds) {
		seed = convert(seed, maps);
		if (seed < part_1) part_1 = seed;
	}

	auto ranges = parse_seed_ranges(seeds);
	int i = 0;
	for (auto &range : ranges) {
		int i2 = 0;
		for (uint64_t seed = range.start; seed < range.start + range.length; seed++) {
			if (i2 % 1000000 == 0) {
				std::cout << i << "/" << ranges.size() << ", " << i2 << std::endl;
			}
			uint64_t c_seed = convert(seed, maps);
			if (c_seed < part_2) part_2 = c_seed;
			i2++;
		}
		i++;
	}

	std::cout << "part 1: " << part_1 << std::endl;
	std::cout << "part 2: " << part_2 << std::endl;
}
