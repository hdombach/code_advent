file = open("input.txt", "r")
lines = file.readlines()

tail_locations = set()

class Rope:
    def __init__(self, head_x=0, head_y=0, tail_x=0, tail_y=0):
        self.head_x = head_x
        self.head_y = head_y
        self.tail_x = tail_x
        self.tail_y = tail_y

    def move_unit(self, dir_x, dir_y):
        self.head_x += dir_x
        self.head_y += dir_y
        if abs(self.head_x - self.tail_x) > 1 or abs(self.head_y - self.tail_y) > 1:
            if self.head_x > self.tail_x:
                self.tail_x += 1
            elif self.head_x < self.tail_x:
                self.tail_x -= 1
            if self.head_y > self.tail_y:
                self.tail_y += 1
            elif self.head_y < self.tail_y:
                self.tail_y -= 1

    def tail_desc(self):
        return f"{self.tail_x},{self.tail_y}"
    def __repr__(self) -> str:
        return f"({self.head_x}, {self.head_y})->({self.tail_x}, {self.tail_y})"


rope = Rope()
points = set({rope.tail_desc()})

for line in lines:
    words = line.strip().split(' ')
    steps = int(words[1])
    if words[0] == 'U':
        for _ in range(steps):
            rope.move_unit(0, 1)
            points.update({rope.tail_desc()})
    elif words[0] == 'D':
        for _ in range(steps):
            rope.move_unit(0, -1)
            points.update({rope.tail_desc()})
    elif words[0] == 'R':
        for _ in range(steps):
            rope.move_unit(1, 0)
            points.update({rope.tail_desc()})
    elif words[0] == 'L':
        for _ in range(steps):
            rope.move_unit(-1, 0)
            points.update({rope.tail_desc()})

print(len(points)) # 6337

# part 2
class Point:
    def __init__(self, x=0, y=0, tail=None):
        self.x = x
        self.y = y
        self.tail = tail

    def link_x(self):
        return self.x
    def link_y(self):
        return self.y
    def move_unit(self, dir_x, dir_y):
        self.x += dir_x
        self.y += dir_y
        if self.tail is not None:
            self.tail.update_link(self)
    def tail_desc(self):
        return f"{self.x},{self.y}"


class Chain:
    def __init__(self, x=0, y=0, tail=None):
        self.x = x
        self.y = y
        self.tail = tail
    def update_link(self, head):
        if abs(head.link_x() - self.x) > 1 or abs(head.link_y() - self.y) > 1:
            if head.link_x() > self.x:
                self.x += 1
            elif head.link_x() < self.x:
                self.x -= 1
            if head.link_y() > self.y:
                self.y += 1
            elif head.link_y() < self.y:
                self.y -= 1
        if self.tail is not None:
            self.tail.update_link(self)
    def link_x(self):
        return self.x
    def link_y(self):
        return self.y
    def tail_desc(self):
        return f"{self.x},{self.y}"

head = Point()
tail = head 
for _ in range(9):
    new_tail = Chain()
    tail.tail = new_tail
    tail = new_tail

points = set({tail.tail_desc()})

for line in lines:
    words = line.strip().split(' ')
    steps = int(words[1])
    for _ in range(steps):
        if words[0] == 'U':
            head.move_unit(0, 1)
        elif words[0] == 'D':
            head.move_unit(0, -1)
        elif words[0] == 'R':
            head.move_unit(1, 0)
        elif words[0] == 'L':
            head.move_unit(-1, 0)
        points.update({tail.tail_desc()}) 
print(len(points))
