import re
#import curses
#from curses import wrapper
import time

class World:
    def __init__(self):
        self.width = 0
        self.height = 0
        self.max_x = 1000
        self.max_y = -1000
        self.data = []
        self.is_done = False
        self.sand = Point(["500", "0"], self)
        self.sands = 0

    def update_min_max(self, x, y):
        if self.max_x < x:
            self.max_x = x
        if self.max_y < y:
            self.max_y = y

    def load_world(self):
        self.data = []
        for _ in range(self.max_y + 1):
            self.data += [ [' '] * (self.max_x + 1) ]

    def draw_line(self, line):
        if line.is_horizontal:
            y = line.start_point.y
            if line.start_point.x < line.end_point.x:
                index = 1
            else:
                index = -1
            for x in range(line.start_point.x, line.end_point.x + index, index):
                self.set_point(x, y, "#")
        else:
            x = line.start_point.x
            if line.start_point.y < line.end_point.y:
                index = 1
            else:
                index = -1
            for y in range(line.start_point.y, line.end_point.y + index, index):
                self.set_point(x, y, "#")
        
    def draw_lines(self, lines):
        for line in lines:
            self.draw_line(line)

    def render(self, stdsrc, x=0, y=0):
        rows, cols = stdsrc.getmaxyx()
        for i, line in enumerate(self.data):
            if i >= rows:
                return
            stdsrc.addnstr(y+i, x, "".join(line), cols - 1)

    def get_point(self, x, y):
        return self.data[y][x]
    def set_point(self, x, y, value):
        self.data[y][x] = value


    def tick(self):
        if self.sand.y + 1 >= len(self.data):
            self.is_done = True
            self.sand = Point(["500", "0"], self)

        if self.get_point(self.sand.x, self.sand.y + 1) == ' ':
            self.sand.y += 1
        elif self.get_point(self.sand.x - 1, self.sand.y + 1) == ' ':
            self.sand.y += 1
            self.sand.x -= 1
        elif self.get_point(self.sand.x + 1, self.sand.y + 1) == ' ':
            self.sand.y += 1
            self.sand.x += 1
        else:
            self.set_point(self.sand.x, self.sand.y, 'o')
            self.sands += 1
            self.sand = Point(["500", "0"], self)
            if self.get_point(self.sand.x, self.sand.y) == 'o':
                self.is_done = True



class Point:
    def __init__(self, words, world):
        self.x = int(words[0])
        self.y = int(words[1])
        world.update_min_max(self.x, self.y)
    def __repr__(self) -> str:
        return f"({self.x}, {self.y})"

class Line:
    def __init__(self, p1, p2):
        self.start_point = p1
        self.end_point = p2
    def __repr__(self) -> str:
        return f"{self.start_point}->{self.end_point}"
    @property
    def is_vertical(self):
        return self.start_point.x == self.end_point.x
    @property
    def is_horizontal(self):
        return self.start_point.y == self.end_point.y

def parse_line(line, world):
    result = []
    words = re.split(' |,', line)

    last = Point(words[0:2], world)
    for i in range(3, len(words), 3):
        next = Point(words[i:i+2], world)
        result += [ Line(last,next) ]
        last = next
    return result
        
def parse_lines(lines, world):
    result = []
    for line in lines:
        result += parse_line(line.strip(), world)
    return result

def main(stdsrc, part):
    file = open("input.txt", "r")
    world = World()
    lines = parse_lines(file.readlines(), world)
    max_y = world.max_y + 2
    if part == 2:
        lines += [ Line(Point(["0", f"{max_y}"], world), Point(["1000", f"{max_y}"], world)) ]
    world.load_world()
    world.draw_lines(lines)

    while not world.is_done:
        #print(world.sand, world.get_point(world.sand.x, world.sand.y))
        world.tick()

    print(world.sands)

   

if __name__ == "__main__":
    #wrapper(main)
    #main(curses.initscr())
    main(4, 1)
    main(4, 2)
