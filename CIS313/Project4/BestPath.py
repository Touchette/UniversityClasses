'''
Author: Touchette
Project Three: Calculate "Best Path" in a search tree
Completion Date: 2018-03-12

A simple Binary Search Tree with limited functionality
to support finding the best path in the tree, defined as that
with the highest number of "5"s along the path.
'''
import sys


class Node(object):
    '''
    Node class to build the tree.
    '''

    def __init__(self, data):
        self.data = data
        self.leftChild = None
        self.rightChild = None

    def find_successor(self, node):
        current = node

        # Find the leftmost leaf to replace this node
        while(current.leftChild is not None):
            current = current.leftChild

        return current

    def insert(self, data):
        # Data less than the root data is placed in the left subtree of
        # the root, otherwise it's on the right subtree. Also handle the
        # case of duplicates here
        if self.data == data:
            return False
        elif data < self.data:
            if self.leftChild:
                return self.leftChild.insert(data)
            else:
                self.leftChild = Node(data)
                return True
        else:
            if self.rightChild:
                return self.rightChild.insert(data)
            else:
                self.rightChild = Node(data)
                return True

    def delete(self, data):
        if self is None:
            return

        # If current node's data is smaller than root, then it's in the
        # left subtree, if it's greater it's in the right subtree
        if data < self.data:
            self.leftChild = self.leftChild.delete(data)
        elif data > self.data:
            self.rightChild = self.rightChild.delete(data)
        else:
            # Deleting node with one child
            if self.leftChild is None:
                temp = self.rightChild
                self = None
                return temp
            elif self.rightChild is None:
                temp = self.leftChild
                self = None
                return temp

            # Deleting node with two children, need successor first so
            # grab it with find_successor().
            temp = self.find_successor(self.rightChild)
            self.data = temp.data
            self.rightChild = self.rightChild.delete(temp.data)

        return self


class BST():
    '''
    Simple Binary Search Tree to be used in getting the path.
    Node does most of the work here.
    '''
    class BSTException(Exception):
        # Exception class to be used when messing up.
        def __init__(self, data=None):
            super().__init__()

    def __init__(self):
        self.root = None

    def insert(self, data):
        '''
        Defined in Node() class.
        '''
        if self.root:
            return self.root.insert(data)
        else:
            self.root = Node(data)
            return True

    def delete(self, data):
        '''
        Defined in Node() class.
        '''
        if self.root is not None:
            return self.root.delete(data)

    def _best_path(self, node):
        '''
        Returns the so called "best path" of the tree, defined as the
        path that contains the highest amount of "5"s in the keys.
        '''
        if node is None:
            return 0

        left = self._best_path(node.leftChild)
        right = self._best_path(node.rightChild)
        return max(left, right) + str(node.data).count('5')

    def best_path(self):
        '''
        Helper function to call best_path(node) with the root as its
        argument to make for easier printing without accessing private
        variables.
        '''
        path = self._best_path(self.root)
        if path == 0:
            raise BST.BSTException("Path not found!")
        return path


# this function runs the program according to the problem specification
def driver():
    bst = BST()
    with open(sys.argv[1]) as f:
        n = int(f.readline().strip())
        for _ in range(n):
            in_data = f.readline().strip().split()
            action, value_option = in_data[0], in_data[1:]
            # Insert
            if action == "insert":
                value = int(value_option[0])
                bst.insert(value)
            # Print best path
            elif action == "bpv":
                try:
                    print(bst.best_path())
                except BST.BSTException:
                    print("TreeError")
            # Remove
            elif action == "remove":
                value = int(value_option[0])
                try:
                    bst.delete(value)
                except AttributeError:
                    print("TreeError")


if __name__ == "__main__":
    driver()
