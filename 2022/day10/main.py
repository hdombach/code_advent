file = open("input.txt", "r")
lines = file.readlines()

class State:
    def __init__(self):
        self.clock_cycle = 0
        self.important_cycles = {20, 60, 100, 140, 180, 220}
        self.signal_strength_sum = 0
        self.x_register = 1
        self.screen = ""


    def next_cycle(self):
        self.draw_on_screen()
        self.clock_cycle += 1
        if self.clock_cycle in self.important_cycles:
            self.signal_strength_sum += self.clock_cycle * self.x_register

    def draw_on_screen(self):
        current_pos = self.clock_cycle % 40
        if abs(current_pos - self.x_register) > 1:
            self.screen += " "
        else:
            self.screen += "#"
        if current_pos == 39:
            self.screen += "\n"


    def change_x_register(self, value):
        self.x_register += value

state = State()

for line in lines:
    words = line.strip().split(' ')
    if len(words) < 1:
        break

    if words[0] == 'noop':
        state.next_cycle()
    else:
        state.next_cycle()
        state.next_cycle()
        state.change_x_register(int(words[1]))
        

print(state.signal_strength_sum)
print(state.screen)
