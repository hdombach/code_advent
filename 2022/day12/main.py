import queue
import math

class Node:
    def __init__(self, letter, part):
        self.height = ord(letter) - ord('a')
        self.neighbors = []
        self.previous = None
        self.distance = math.inf
        self.visited = False
        self.is_start = False
        self.is_end = False
        self.position = (0,0)
        self.letter = letter

        if letter == 'S' or (part == 2 and letter == 'a'):
            self.height = 0
            self.is_start = True
            self.distance = 0
        elif letter == 'E':
            self.height = 25
            self.is_end = True

    def __repr__(self):
        return f"{{Node height: {self.height}, distance: {self.distance}}}"

    def __lt__(self, rhs):
        return self.distance < rhs.distance
    def __gt__(self, rhs):
        return self.distance > rhs.distance
    def __le__(self, rhs):
        return self.distance <= rhs.distance
    def __ge__(self, rhs):
        return self.distance >= rhs.distance
    def __eq__(self, rhs):
        return self.distance == rhs.distance
    def __ne__(self, rhs):
        return self.distance != rhs.distance

def get_view(nodes, width, height):
    result_array = []
    for _ in range(height):
        row = []
        for _ in range(width):
            row += ['']
        result_array += [ row ] 

    for node in nodes:
        (x, y) = node.position
        text = str(node.height)
        if node.visited:
            text += ">"
        else:
            text += " "
        result_array[y][x] = text
    result = ""
    for row in result_array:
        for item in row:
            result += ' ' * (3 - len(item)) + item

        result += "\n"
    return result
    

def parse_nodes(lines, part):
    result = []
    grid = []
    for line in lines:
        row = []
        for char in line.strip():
            node = Node(char, part)
            row += [ node ]
            result += [node]
        grid += [ row ]

    for y, row in enumerate(grid):
        for x, node in enumerate(row):
            node.position = (x,y)
            if x > 0:
                node.neighbors += [ grid[y][x - 1] ]
                #if grid[y][x - 1].height + 1 <= node.height:
            if x < len(row) - 1:
                node.neighbors += [ grid[y][x + 1] ]
                #if grid[y][x + 1].height + 1 <= node.height:
            if y > 0:
                node.neighbors += [ grid[y - 1][x] ]
                #if grid[y - 1][x].height + 1 <= node.height:
            if y < len(grid) - 1:
                node.neighbors += [grid[y + 1][x] ]
                #if grid[y + 1][x].height + 1 <= node.height:

    return result

def thing(all_nodes):
    end_node = None
    unvisited = all_nodes.copy()
    unvisited.sort()
    while len(unvisited) > 0 and end_node is None:
        unvisited.sort()
        #print(get_view(all_nodes, width, height))
        cur = unvisited.pop(0)
        next_distance = cur.distance + 1
        for neighbor in cur.neighbors:
            if neighbor.height <= (cur.height + 1):
                if neighbor.is_end:
                    neighbor.distance = next_distance
                    neighbor.previous = cur
                    end_node = neighbor
                    break
                if not neighbor.visited and neighbor.distance > next_distance:
                    neighbor.distance = next_distance
                    neighbor.previous = cur
        cur.visited = True
    steps = 0
    node = end_node
    while not node.is_start:
        steps += 1
        node = node.previous
    print(steps)


def main(part=1):
    file = open("input.txt", "r")
    lines = file.readlines()
    height = len(lines)
    width = len(lines[0])

    unvisited = parse_nodes(lines, part)
    all_nodes = unvisited.copy()

    thing(all_nodes)

if __name__ == "__main__":
    main()
    main(2)

