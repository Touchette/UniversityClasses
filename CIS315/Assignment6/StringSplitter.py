'''
Author: Touchette
Completed: 2018-06-01
CIS 315 Assignment Six
Splits strings into the English words that constitute them should
all words in the string be valid words given in a dictionary file.
'''
import sys
import os
import fcntl
from collections import defaultdict


class FileGrabber():
    '''
    Gets all the files for me. Loads the dictionary into a dictionary,
    loads the file full of sample sentences into a list. Checks for
    empty lines.
    '''

    def __init__(self):
        self.dictionary = defaultdict(int)
        self.teststrings = []

    def LoadDictionary(self, filename=None):
        '''
        Loads the dictionary file
        '''
        if filename:
            with open(filename) as f:
                for line in f:
                    line = line.strip()
                    self.dictionary[line] += 1
        else:
            print("Need a dictionary filename.")
            quit(1)

    def LoadFile(self, filename=None):
        '''
        Loads the sentences to be tested
        '''
        if filename:
            next(filename)
            for i in filename:
                    # Check for empty line
                if len(i.strip()) == 0:
                    pass
                else:
                    line = i.strip()
                    self.teststrings.append(line)
        else:
            print("Need a filename.")
            quit(1)

    def GetDictionary(self):
        return self.dictionary

    def GetFile(self):
        return self.teststrings

    def Tests(self):
        '''
        Just used these to make sure I was loading the files correctly
        '''
        if len(self.dictionary) > 1:
            print("Dictionary has more than one object loaded.")
            print("Here are (up to) 10 items from the dictionary:\n\t")
            try:
                for i in range(10):
                    print(self.dictionary[i])
            except IndexError:
                pass

        print("\n")

        if len(self.teststrings) > 1:
            print("Test list has more than one object loaded.")
            print("Here are (up to) 10 items from the test list:\n\t")
            try:
                for i in range(10):
                    print(self.teststrings[i])
            except IndexError:
                pass


class StringChecker():
    '''
    Actually does the iterative and memoized string splitting.
    Uses the FG class to get the dictionary and sentences to split.
    '''

    def __init__(self, dictname, testname):
        self.fg = FileGrabber()
        self.split = ""

        if not dictname or not testname:
            print("Insufficient filenames given.")
            quit(1)
        else:
            self.fg.LoadDictionary(dictname)
            self.fg.LoadFile(testname)

    def IterativeSplitter(self, s, empty):
        '''
        Iterative version of the sentence splitter will split the
        sentence by checking each character in the string and seeing
        if the word built so far is in the dictionary. If it is,
        it returns True. It does this all the way to the end of the
        string before stopping, and only returns True if it reaches the
        end and all prior words were in the dictionary.
        '''
        word = ""

        if len(s) == 0:
            self.split = empty
            return True
        else:
            for i in range(len(s)):
                word += s[i]
                if word in self.fg.GetDictionary():
                    if self.IterativeSplitter(s[i + 1:], empty + word + " "):
                        return True
        return False

    def MemoizedSplitter(self, s, empty, memory=defaultdict(int)):
        '''
        Memoized version of the sentence splitter will split the
        sentence by checking each character in the string and seeing
        if the word built so far is in the dictionary. If it is,
        it returns True. It does this all the way to the end of the
        string before stopping, and only returns True if it reaches the
        end and all prior words were in the dictionary. Also, as a bonus
        to the iterative version, it will build a memory up over the
        function calls. If anything is seen in the memory before checking
        for words in the dictionary, it returns false which improves the
        runspeed of the program.
        '''
        word = ""

        if len(s) == 0:
            self.split = empty
            return True
        elif s in memory:
            return False
        else:
            for i in range(len(s)):
                word += s[i]
                if word in self.fg.GetDictionary():
                    if self.MemoizedSplitter(s[i + 1:], empty + word + " ",
                                             memory):
                        return True
        memory[s] += 1
        return False

    def GetSize(self):
        return len(self.fg.GetFile())

    def GetString(self, i):
        return self.fg.GetFile()[i]

    def GetSplit(self):
        return self.split

    def Tests(self):
        return self.fg.Tests()


# Actually runs the program
def main():
    # These lines are for checking if there's an input
    fd = sys.stdin.fileno()
    fl = fcntl.fcntl(fd, fcntl.F_GETFL)
    fcntl.fcntl(fd, fcntl.F_SETFL, fl | os.O_NONBLOCK)

    try:
        sc = StringChecker("diction10k.txt", sys.stdin)
    except IOError:
        print("Need file to work with.")
        quit(1)

    for i in range(sc.GetSize()):
        print("phrase number: {}".format(i + 1))
        print("{}\n".format(sc.GetString(i)))

        print("iterative attempt:")
        print("YES, can be split\n" + sc.GetSplit() +
              "\n" if sc.IterativeSplitter(sc.GetString(i), "") else
              "NO, cannot be split\n")

        print("memoized attempt:")
        print("YES, can be split\n" + sc.GetSplit() +
              "\n" if sc.MemoizedSplitter(sc.GetString(i), "") else
              "NO, cannot be split\n")

        print("\n")


if __name__ == "__main__":
    main()
