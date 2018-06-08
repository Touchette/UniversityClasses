'''
Author: Touchette
Project Two: Check which restaurant to begin journey
Completion Date: 2018-02-15

No idea what I was doing here, the idea was to only increment the "head",
which is the leading pointer, if it was possible to do so, if not, increment
the "tail". The tail was the starting position pointer. I didn't know how
to execute these while loops correctly and maintain multiple array indices
at the same time. It may almost be functioning, didn't have time to check.
'''
import sys


class RestaurantChecker():
    class Node():
        def __init__(self, given=None, req=None):
            self.gives = given
            self.req = req

    def __init__(self):
        self.list = []
        self.size = 0
        self.energy = 0
        self.tail = 0
        self.head = 0

    def insert(self, x):
        self.list.append(x)
        self.size += 1

    def advanceTail(self):
        self.energy += self.list[self.tail].gives
        self.energy -= self.list[self.tail].req
        if self.tail == (self.size - 1):
            self.tail = 0
        else:
            self.tail += 1
        if self.tail == self.head:
            if self.head == (self.size - 1):
                print("Failure")
                return False
            else:
                self.head += 1

    def advanceHead(self):
        self.energy += self.list[self.head].gives
        self.energy -= self.list[self.head].req
        if self.head == (self.size - 1):
            print("Failure")
            return False
        else:
            self.head += 1

    def checkRestaurant(self):
        solved = False
        while not solved:
            while self.list[self.head + 1].req > self.energy:
                self.advanceTail()
            self.advanceHead()


# this function runs the program according to the problem specification
def driver():
    r = RestaurantChecker()
    with open(sys.argv[1]) as f:
        n = int(f.readline().strip())
        for _ in range(n):
            in_data = f.readline().strip().split()
            gained, required = int(in_data[0]), int(in_data[1])
            r.queue.enqueue(gained, required)
        pass


if __name__ == "__main__":
    driver()
