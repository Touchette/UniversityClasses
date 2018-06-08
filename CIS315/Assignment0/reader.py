'''
Author: Touchette
Completion Date: Wed 2018-04-04
Read numbers from a file, add them and multiply them. Outputs
to stdout.

Usage: python3 reader.py < dummy_input
'''
import sys


class Reader():
    '''
    Don't actually need this to be a class but I don't like
    function definitions strewn around globally.
    '''

    def __init__(self):
        pass

    def read_file(self):
        '''
        Reads file, prints the data as it comes.
        '''
        no_lines = int(sys.stdin.readline())
        for _ in range(no_lines):
            data = sys.stdin.readline().split()
            x = int(data[0])
            y = int(data[1])
            print("{} {}".format((x + y), (x * y)))


# Runs the program to the problem specifications
def driver():
    r = Reader()
    r.read_file()


if __name__ == "__main__":
    driver()
