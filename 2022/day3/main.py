file = open("input.txt", "r")
lines = file.readlines()

result_1 = 0

for line in lines:
    size = len(line) // 2
    if size == 0:
        break
    slice_a = slice(0, size)
    slice_b = slice(size, size * 2)
    a = line[slice_a]
    b = line[slice_b]
    for c in a:
        if c in b:
            b = c
            break

    if b.islower():
        result_1 += ord(b) - ord('a') + 1
    else:
        result_1 += ord(b) - ord('A') + 27

print(result_1)

result_2 = 0

group = []

for line in lines:
    group.append(line.strip('\n'))
    if len(group) == 3:

        common =''.join(set(group[0]).intersection(group[1])) 
        common =''.join(set(common).intersection(group[2])) 

        group = []
        if common[0].islower():
            result_2 += ord(common[0]) - ord('a') + 1
        else:
            result_2 += ord(common[0]) - ord('A') + 27
print(result_2)
