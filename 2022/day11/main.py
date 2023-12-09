import math

def get_words(line_iter):
    return next(line_iter).strip().split(' ')


class Monkey:
    def __init__(self, items = [], operation = [], divisible_value = 1, true_monkey = 0, false_monkey = 0):
        self.items: list[int] = items
        self.operation: list[str] = operation
        self.divisible_value: int = divisible_value
        self.true_monkey: int = true_monkey
        self.false_monkey: int = false_monkey
        self.number_of_inspects = 0

    def add_item(self, item):
        self.items.append(item)

    def __get_operation_value(self, value, old_item):
        try:
            return int(value)
        except:
            return old_item

    def __do_operation(self, old_item):
        lhs = self.__get_operation_value(self.operation[0], old_item)
        rhs = self.__get_operation_value(self.operation[2], old_item)
        if self.operation[1] == "+":
            return lhs + rhs
        else:
            return lhs * rhs

    def turn(self, monkeys, decrease_worry):
        for item in self.items:
            self.number_of_inspects += 1
            item = self.__do_operation(item)
            if decrease_worry:
                item = math.floor(item / 3)
            else:
                item = item % 9699690
            if item % self.divisible_value == 0:
                monkeys[self.true_monkey].add_item(item)
            else:
                monkeys[self.false_monkey].add_item(item)
        self.items = []

    def __repr__(self) -> str:
        #return f"{{Monkey items: {self.items}, operation: {self.operation}, divisible_value: {self.divisible_value}, true_monkey: {self.true_monkey}, false_monkey: {self.false_monkey}}}"
        return f"{{Monkey items: {self.items}, inspects: {self.number_of_inspects}}}"


    @staticmethod
    def parse(line_iter):
        try:
            while get_words(line_iter)[0] != "Monkey":
                continue
        except StopIteration:
            return None

        words = get_words(line_iter)
        items = []
        for word in words:
            try:
                items += [ int(word.strip(',')) ]
            except:
                pass

        words = get_words(line_iter)
        operation = words[3:6]

        words = get_words(line_iter)
        divisible_value = int(words[3])

        words = get_words(line_iter)
        true_monkey = int(words[5])

        words = get_words(line_iter)
        false_monkey = int(words[5])
        return Monkey(items, operation, divisible_value, true_monkey, false_monkey)

def do_round(monkeys, decrease_worry=True):
    for monkey in monkeys:
        monkey.turn(monkeys, decrease_worry)

def parse_monkeys(lines: list[str]):
    result = []
    line_iter = iter(lines)
    while True:
        monkey = Monkey.parse(line_iter)
        if monkey is None:
            return result
        else:
            result += [ monkey ]

file = open("input.txt", "r")
lines = file.readlines()

#part 1
monkeys = parse_monkeys(lines)
for _ in range(20):
    do_round(monkeys)

top_inspects = []
for monkey in monkeys:
    top_inspects.append(monkey.number_of_inspects)
    if len(top_inspects) > 2:
        top_inspects.sort()
        top_inspects.pop(0)
print(top_inspects[0] * top_inspects[1])

#part 2
monkeys = parse_monkeys(lines)
for i in range(10000):
    #print(f"progress: {i}")
    do_round(monkeys, False)

top_inspects = []
for monkey in monkeys:
    top_inspects.append(monkey.number_of_inspects)
    if len(top_inspects) > 2:
        top_inspects.sort()
        top_inspects.pop(0)
print(top_inspects[0] * top_inspects[1])

