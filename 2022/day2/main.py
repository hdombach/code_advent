file = open("input.txt", "r")
lines = file.readlines()

score = 0

oppenent_value = {
        "A": 0,
        "B": 1,
        "C": 2,
        }
your_value = {
        "X": 0,
        "Y": 1,
        "Z": 2,
        }

score = 0

score_2 = 0

for line in lines:
    if len(line) != 4:
        break
    opponent_move = oppenent_value[line[0]]
    your_move = your_value[line[2]]
    score += your_move + 1
    if your_move == (opponent_move + 1) % 3:
        score += 6
    elif your_move == opponent_move:
        score += 3

    if your_move == 0:
        score_2 += (opponent_move - 1) % 3 + 1
    elif your_move == 1:
        score_2 += opponent_move + 4
    else:
        score_2 += (opponent_move + 1) % 3 + 7
        
print(score)
print(score_2)
