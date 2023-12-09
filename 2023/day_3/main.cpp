#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Cell {
	char value;
	int symbol_index;
	bool symbol_counted;
};

struct Grid {
	std::vector<std::vector<Cell>> items;
	std::vector<std::string> lines;

	Cell &get(int x, int y) {
		return items[y][x];
	}

	int get_num(int x, int y) {
		Cell cell = get(x, y);
		if (!isdigit(cell.value)) return 0;
		Cell &src_cell = get(x - cell.symbol_index, y);
		if (src_cell.symbol_counted) return 0;
		src_cell.symbol_counted = true;
		const char *str = &lines[y].c_str()[x - cell.symbol_index];
		return atoi(str);
	}

	void reset_counted() {
		for (auto &row : items) {
			for (auto &cell : row) {
				cell.symbol_counted = false;
			}
		}
	}

	Grid(std::ifstream &file) {
		std::string str;

		while (std::getline(file, str)) {
			int symbol_index = -1;
			Cell cell;
			std::vector<Cell> row;

			for (auto c : str) {
				cell.value = c;
				cell.symbol_counted = false;
				if (isdigit(c)) {
					symbol_index++;
					cell.symbol_index = symbol_index;
				} else {
					symbol_index = -1;
					cell.symbol_index = -1;
				}
				row.push_back(cell);
			}
			lines.push_back(str);
			items.push_back(row);
		}
	}

	void print_debug() {
		for (int y = 0; y < items.size(); y++) {
			std::cout << lines[y] << std::endl;
			for (int x = 0; x < items[0].size(); x++) {
				Cell cell = get(x, y);
				if (cell.symbol_index >= 0) {
					std::cout << cell.symbol_index;
				} else {
					std::cout << ' ';
				}
			}
			std::cout << std::endl;
		}
	}

	int get_sum() {
		int result = 0;
		for (int y = 0; y < items.size(); y++) {
			for (int x = 0; x < items[0].size(); x++) {
				auto cell = get(x, y);
				if (cell.value == '.' || cell.symbol_index >= 0) continue;

				for (int cx = -1; cx <= 1; cx++) {
					for (int cy = -1; cy <= 1; cy++) {
						int realx = x + cx;
						int realy = y + cy;
						if (realx >= items[0].size() || realx < 0) break;
						if (realy >= items.size() || realy < 0) break;
						int temp = get_num(realx, realy);
						result += temp;
					}
				}
			}
		}
		return result;
	}

	int get_gear_sum() {
		int result = 0;
		for (int y = 0; y < items.size(); y++) {
			for (int x = 0; x < items[0].size(); x++) {

				int gears = 0;
				int gear_value = 1;
				auto cell = get(x, y);
				if (cell.value != '*') continue;
				reset_counted();
				for (int cx = -1; cx <= 1; cx++) {
					for (int cy = -1; cy <= 1; cy++) {
						int realx = x + cx;
						int realy = y + cy;
						if (realx >= items[0].size() || realx < 0) break;
						if (realy >= items.size() || realy < 0) break;
						int gear = get_num(realx, realy);
						if (gear > 0) {
							gear_value *= gear;
							gears++;
						}
					}
				}
				if (gears == 2) {
					result += gear_value;
				}
			}
		}
		return result;
	}
};

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "use:" << std::endl;
		std::cout << "\t" << argv[0] << "<in_file>" << std::endl;
	}

	std::ifstream file(argv[1]);

	auto grid = Grid{file};

	int sum = grid.get_sum();
	std::cout << "part 1 " << sum << std::endl;

	std::cout << "par 2 " << grid.get_gear_sum() << std::endl;

	return 0;
}
