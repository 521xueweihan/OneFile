#! /usr/bin/python3

import random


class Block:
    def __init__(self):
        self.value = 0
        self.mask = False

    def __str__(self) -> str:
        if self.mask:
            return "?"
        if self.get_empty():
            return " "
        elif self.get_mine():
            return "*"
        elif self.get_number() != -1:
            return str(self.value)
        return ""

    def set_empty(self):
        self.value = 0

    def set_number(self, n: int) -> bool:
        if n <= 0 or n > 8:
            return False
        self.value = n
        return True

    def plus_number(self, p=1) -> int:
        if self.get_mine():
            return -1
        else:
            self.set_number(self.value + p)
            return self.value

    def set_mine(self):
        self.value = -1

    def get_empty(self) -> bool:
        return self.value == 0

    def get_number(self) -> int:
        if self.value <= 0 or self.value > 8:
            return -1
        return self.value

    def get_mine(self) -> bool:
        return self.value == -1


class Points:
    def __init__(self):
        self.p = {}

    def add(self, x: int, y: int):
        self.p[f"{x}:{y}"] = True

    def remove(self, x: int, y: int):
        self.p[f"{x}:{y}"] = False

    def get(self, x: int, y: int) -> bool:
        if f"{x}:{y}" not in self.p:
            return False
        return self.p[f"{x}:{y}"]

    def list(self) -> list:
        r = []
        for k, v in self.p.items():
            k: str
            v: bool
            x, y = k.split(":")
            x = int(x)
            y = int(y)
            if v:
                r.append([x, y])
        return r


HEIGHT = 10
WIDTH = 10
MINES = 15


def main():
    # prepare buffer
    buffer = []
    for i in range(HEIGHT):
        b = []
        for j in range(WIDTH):
            obj = Block()
            obj.mask = True
            b.append(obj)
        buffer.append(b)
    # fill map
    # mine
    for i in range(MINES):
        while True:
            x, y = random.choice(range(HEIGHT)), random.choice(range(WIDTH))
            if buffer[x][y].get_mine():
                continue
            buffer[x][y].set_mine()
            break
    # numbers
    for i in range(HEIGHT):
        for j in range(WIDTH):
            if buffer[i][j].get_mine():
                # middle left number
                if not (j - 1 < 0):
                    buffer[i][j - 1].plus_number()
                # middle right number
                if not (j + 1 > WIDTH - 1):
                    buffer[i][j + 1].plus_number()
                # middle top number
                if not (i - 1 < 0):
                    buffer[i - 1][j].plus_number()
                # middle bottom number
                if not (i + 1 > HEIGHT - 1):
                    buffer[i + 1][j].plus_number()
                # top left number
                if not (i - 1 < 0 or j - 1 < 0):
                    buffer[i - 1][j - 1].plus_number()
                # top right number
                if not (i - 1 < 0 or j + 1 > WIDTH - 1):
                    buffer[i - 1][j + 1].plus_number()
                # bottom left number
                if not (i + 1 > HEIGHT - 1 or j - 1 < 0):
                    buffer[i + 1][j - 1].plus_number()
                # bottom right number
                if not (i + 1 > HEIGHT - 1 or j + 1 > WIDTH - 1):
                    buffer[i + 1][j + 1].plus_number()

    def play():
        # input position
        pos_str = input("input x y:")
        pos_list = pos_str.split(" ")
        if len(pos_list) != 2:
            # 2 numbers without space
            pos_list = [pos_str[0], pos_str[1]]
        pos_x = int(pos_list[0])
        pos_y = int(pos_list[1])
        # is it a mine?
        if buffer[pos_x][pos_y].get_mine():
            buffer[pos_x][pos_y].mask = False
            raise Exception("boom")
        # is it a number?
        if buffer[pos_x][pos_y].get_number() != -1:
            buffer[pos_x][pos_y].mask = False
            return
        # nothing in it?
        if buffer[pos_x][pos_y].get_empty():
            points = Points()
            points.add(pos_x, pos_y)
            points_len = len(points.list())
            # unmask this area
            while True:
                for point in points.list():
                    point: list
                    # top
                    for i in range(point[0]):
                        i = point[0] - i - 1
                        if buffer[i][point[1]].get_number() != -1:
                            break
                        points.add(i, point[1])
                    # bottom
                    for i in range(point[0] + 1, HEIGHT):
                        if buffer[i][point[1]].get_number() != -1:
                            break
                        points.add(i, point[1])
                    # left
                    for i in range(point[1]):
                        i = point[1] - i - 1
                        if buffer[point[0]][i].get_number() != -1:
                            break
                        points.add(point[0], i)
                    # right
                    for i in range(point[1] + 1, WIDTH):
                        if buffer[point[0]][i].get_number() != -1:
                            break
                        points.add(point[0], i)
                # nothing new added?
                if len(points.list()) == points_len:
                    break
                points_len = len(points.list())
            # unmask
            for i in points.list():
                buffer[i[0]][i[1]].mask = False
    while True:
        # display
        print(end="x  y ")
        for i in range(WIDTH):
            print(i, end="  ")
        print()
        for i in range(HEIGHT):
            print(i, end="|   ")
            for j in range(WIDTH):
                print(buffer[i][j], end="  ")
            print()
        # check if you win
        win_flag = True
        for i in range(HEIGHT):
            for j in range(WIDTH):
                if not(buffer[i][j].mask and buffer[i][j].get_mine()):
                    win_flag = False
                    break
        if win_flag:
            raise Exception("you win!")
        play()


if __name__ == '__main__':
    main()
