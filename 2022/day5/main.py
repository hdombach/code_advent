file = open("input.txt", "r")
lines = file.readlines()


def make_stacks(lines):
    columns = []
    for column_number in range(1, 37, 4):
        column =  []
        for row_number in range(7, -1, -1):
            char = lines[row_number][column_number]
            if char != ' ':
                column += [ char ]
        columns += [ column ]
    return columns

stacks = make_stacks(lines)

command_number = 10
while command_number < len(lines):
    line = lines[command_number].strip()
    words = line.split(' ')

    if len(words) < 6:
        break

    for _ in range(int(words[1])):
        thing = stacks[int(words[3]) - 1].pop()
        stacks[int(words[5]) - 1].append(thing)

    command_number += 1

result = ""
for stack in stacks:
    result += stack[-1]
print(result)

# part 2
stacks = make_stacks(lines)

command_number = 10
while command_number < len(lines):
    line = lines[command_number].strip()
    words = line.split(' ')

    if len(words) < 6:
        break

    stack = []
    for _ in range(int(words[1])):
        stack += [stacks[int(words[3]) - 1].pop()]
    for _ in range(len(stack)):
        stacks[int(words[5]) - 1].append(stack.pop())


    command_number += 1

result = ""
for stack in stacks:
    result += stack[-1]
print(result)
