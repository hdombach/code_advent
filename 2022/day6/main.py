file = open("input.txt", "r")
line = file.readlines()[0]

stack = []
i = 0
while i < 4:
    stack.append(line[i])
    i += 1
while len(stack) != len(set(stack)):
    i += 1
    stack.pop(0)
    stack += [ line[i] ]

print(i + 1)

#part 2
stack = []
i = 0
while i < 14:
    stack.append(line[i])
    i += 1
while len(stack) != len(set(stack)):
    i += 1
    stack.pop(0)
    stack += [ line[i] ]

print(i + 1)

