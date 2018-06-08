'''
Author: Touchette
Project Two: Check for well-formatted brackets and braces
Completion Date: 2018-02-15

This will check if a set of brackets is well-formatted; ie they have
no opening bracket without a closing bracket, no closing bracket comes first,
etc. It does this by using the stack that we defined last project and pushing
onto it when encountering an open bracket, popping off when encountering a
closing one.
'''

import sys
import stack


class BracketChecker():

    def __init__(self):
        # looking up the values in this is O(4), effectively O(1)
        self.bracketDict = {"}": "{",
                            "]": "[",
                            ")": "(",
                            ">": "<"}
        # stack I implemented for project one
        self.stack = stack.Stack()

    def checkFormat(self, line):
        for char in line:
            if char in self.bracketDict.values():
                self.stack.push(char)  # push onto stack if opening bracket
            elif self.bracketDict[char] == self.stack.peek():
                self.stack.pop()  # pop if its closing bracket pair is found
            else:
                print("NO")  # if neither, print NO and return False
                return False
        if not self.stack.is_empty():
            print("NO")  # final check
            return False
        print("YES")
        return True


# this function runs the program according to the problem specification
def driver():
    b = BracketChecker()
    with open(sys.argv[1]) as f:
        n = int(f.readline().strip())
        for _ in range(n):
            line = f.readline().strip()
            b.checkFormat(line)


if __name__ == "__main__":
    driver()
