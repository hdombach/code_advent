from pickle import FALSE, TRUE


file = open("input.txt", "r")
lines = file.readlines()

sum = 0
sum2 = 0

for line in lines:
    line = line.strip("\n")
    if line == "":
        break
    numbers = []
    number = ""
    for char in line:
        if char.isdigit():
            number += char
        else:
            numbers.append(int(number))
            number = ""
    numbers.append(int(number))

    if numbers[0] <= numbers[2] and numbers[1] >= numbers[3]:
        sum += 1
    elif numbers[0] >= numbers[2] and numbers[1] <= numbers[3]:
        sum += 1

    if numbers[0] <= numbers[2] and numbers[1] >= numbers[2]:
        sum2 += 1
    elif numbers[2] <= numbers[0] and numbers[3] >= numbers[0]:
        sum2 += 1


print(sum, sum2)
