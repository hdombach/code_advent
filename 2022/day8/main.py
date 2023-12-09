file = open("input.txt", "r")
lines = file.readlines()

width = len(lines[0]) - 1 # strip \n
height = len(lines)

def is_visible(x, y, dir_x, dir_y):
    tree_height = int(lines[y][x])
    x += dir_x
    y += dir_y
    while 0 <= x < width and 0 <= y < height:
        if int(lines[y][x]) >= tree_height:
            return False
        x += dir_x
        y += dir_y
    return True

def scenic_view_in_dir(x, y, dir_x, dir_y):
    tree_height = int(lines[y][x])
    x += dir_x
    y += dir_y
    scenic_view = 0
    while 0 <= x < width and 0 <= y < height:
        scenic_view += 1
        if int(lines[y][x]) >= tree_height:
            break;
        x += dir_x
        y += dir_y
    return scenic_view

def scene_view(x, y):
    return scenic_view_in_dir(x, y, 0, 1) * scenic_view_in_dir(x, y, 0, -1) * scenic_view_in_dir(x, y, 1, 0) * scenic_view_in_dir(x, y, -1, 0)

visible_trees = 0
for x in range(width):
    for y in range(height):
        if is_visible(x, y, 0, 1) or is_visible(x, y, 0, -1) or is_visible(x, y, 1, 0) or is_visible(x, y, -1, 0):
            visible_trees += 1

print(visible_trees)

best_scene_view = 0
best_position = (0, 0)
best_height = 0
for x in range(width):
    for y in range(height):
        temp_view = scene_view(x, y)
        print(temp_view)
        if temp_view > best_scene_view:
            best_scene_view = temp_view
            best_position = (x, y)
            best_height = lines[y][x]
print(best_scene_view, best_position, best_height)
