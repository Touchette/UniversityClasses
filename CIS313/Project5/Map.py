'''
Author: Touchette
CIS313 Intermediate Data Structures
Map implementation using Red-Black Tree
TODO
'''
from RBT.py import *
import sys


class Map():
    def __init__(self):
        self.rbt = RBT.RBTree()

    def insert(self, key, value):
        if key not in self.rbt:
            self.rbt.insert(key, value)
            return True
        else:
            return False

    def reassign(self, key, value):
        try:
            node = self.rbt.search(key)
        except self.rbt.RBTreeException:
            return False
        if node:
            pass

    def lookup(self, key):
        node = self.rbt.search(key)
        return True if node else False

    def fetch(self, key):
        node = self.rbt.search(key)
        return node if node else False

    def remove(self, key):
        self.rbt.delete(key)


# runs to program specifications
def driver():
    with open(sys.argv[1]) as f:
        next(f)
    pass
