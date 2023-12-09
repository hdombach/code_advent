file = open("input.txt", "r")
lines = file.readlines()

max = 0

current = 0

top = []

for line in lines:
    line = line.strip("\n")
    if line == "":
        top.append(current)
        top.sort()
        if len(top) > 3:
            top.pop(0)
            
        current = 0
    else:
        current += int(line)

print(top[0] + top[1] + top[2])
