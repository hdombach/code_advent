import ast

def is_smaller(lhs, rhs):
    lhs_is_int = isinstance(lhs, int) or isinstance(lhs, float)
    rhs_is_int = isinstance(rhs, int) or isinstance(rhs, float)
    if lhs_is_int and rhs_is_int:
        return lhs < rhs
    
    if lhs_is_int:
        lhs_array = [lhs]
    else:
        lhs_array = lhs

    if rhs_is_int:
        rhs_array = [rhs]
    else:
        rhs_array = rhs

    for i, item in enumerate(lhs_array):
        if i >= len(rhs_array):
            return False
        elif item == rhs_array[i]:
            continue
        elif is_smaller(item, rhs_array[i]):
            return True
        else:
            return False
    return True 

def main():
    file = open("input.txt", "r")
    lines = file.readlines()

    result1 = 0
    index = 1

    items = []
    for line in lines:
        if line == "\n":
            continue
        items += [ ast.literal_eval(line) ]
        if len(items) == 2:
            if is_smaller(items[0], items[1]):
                print("True", index, result1, "+", index)
                result1 += index
            else:
                print("False", index, result1)
            items = []
            index += 1
    print(result1)


if __name__ == "__main__":
    main()
    #print(is_smaller([0, 4], 3))
    #print(is_smaller([0], 3))


#I give up
