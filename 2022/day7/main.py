file = open("input.txt", "r")
lines = file.readlines()

class File:
    def __init__(self, name, size, parent):
        self.name = name
        self.size = int(size)
        self.parent = parent

    def get_size(self):
        return self.size
    def get_capped_size(self):
        return 0
    def is_dir(self):
        return False
    def __repr__(self) -> str:
        return "file %s (%s)" % (self.name, self.size)

class Dir:
    def __init__(self, name, parent):
        self.name = name
        self.parent = parent
        self.children = []

    def add_dir(self, name):
        self.children.append(Dir(name, self))

    def is_dir(self):
        return True
    
    def add_file(self, name, size):
        self.children.append(File(name ,size, self))

    def get_size(self):
        size = 0
        for child in self.children:
            size += child.get_size()
        return size

    def get_capped_size(self):
        capped_size = 0
        for child in self.children:
            capped_size += child.get_capped_size()
        size = self.get_size()
        if size < 100000:
            capped_size += size
        return capped_size

    def get_child(self, name):
        return next(child for child in self.children if child.name == name)

    def run_function(self, func):
        func(self)
        for child in self.children:
            if child.is_dir():
                child.run_function(func)

    def __repr__(self) -> str:
        return "dir %s %s" % (self.name, self.children)

    def closest_size(self, min_size):
        result = self.get_size()
        for child in self.children:
            if child.is_dir():
                size = child.closest_size(min_size)
                if size < result and size >= min_size:
                    result = size
        return result

root = Dir('/', None)
current_node = root

for line in lines:
    words = line.strip().split(' ')
    if words[0] == '$':
        if words[1] == 'cd':
            if words[2] == '..':
                current_node = current_node.parent
            elif words[2] == '/':
                current_node = root
            else:
                current_node = current_node.get_child(words[2])
    elif words[0] == 'dir':
        current_node.add_dir(words[1])
    else:
        current_node.add_file(words[1], words[0])

print(root.get_capped_size())

total_space = 70000000
require_space = 30000000

min_size = root.get_size() + require_space - total_space

print(root.closest_size(min_size))
