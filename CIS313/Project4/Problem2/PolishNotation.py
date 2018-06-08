'''
Author: Touchette
Project Three: Calculate and Properly Print Polish Notation
Completion Date: 2018-03-12

A Syntax Tree class (provided to me) that keeps track of prefix
mathematical notation, also known as Polish Notation. The class
has two methods to print out what the arithmetic expression looks
like as well as its result.
'''
import sys


class STNode:
    '''
    Given node class
    '''
    def __init__(self, x):
        self.data = x
        self.left = None
        self.right = None


class SyntaxTree:
    '''
    Syntax tree given as starter code
    '''
    def init_helper(self, i, l):
        if i >= len(l):
            return None

        node = STNode(l[i])
        # changed these slightly to provide for 0-based indexing
        node.left = self.init_helper(2 * i + 1, l)
        node.right = self.init_helper(2 * i + 2, l)
        return node

    def __init__(self, l):
        # changed slightly to provide for 0-based indexing
        self.root = self.init_helper(0, l)
        self.ops = ['+', '-', '*']

    def _make_polish(self, node, li=[]):
        '''
        This creates the actual expression that is (more) human
        readable. It does this by doing an in-order traversal of
        the tree and printing out opening and closing parentheses
        based on whether or not the node we're currently visiting is
        a mathematical operator. It creates a list recursively as it
        goes along which will be used to print out the expression.
        '''
        if node is None:
            return
        if str(node.data) in self.ops:
            li.append("(")
        self._make_polish(node.left, li)
        li.append(node.data)
        self._make_polish(node.right, li)
        if str(node.data) in self.ops:
            li.append(")")
        return li

    def make_polish(self):
        '''
        This is the helper function that will simply join the list we
        created recursively in the member function _make_polish(self, node)
        and return it.
        '''
        li = self._make_polish(self.root)
        return ''.join(li)

    def _compute_polish(self, node, ret=0):
        '''
        Computes Polish Notation mathematical expressions via postorder
        traversals that keep count of which operator we're currently visiting.
        When visiting an operator, we perform the correct math and add that
        to a running sum that we build recursively and return at the end of the
        function to be printed later.
        '''
        if node is None:
            return
        if node.data in self.ops:
            if node.data == "+":
                v = self._compute_polish(node.left, ret) + \
                    self._compute_polish(node.right, ret)
                ret += v
            if node.data == "-":
                v = self._compute_polish(node.left, ret) - \
                    self._compute_polish(node.right, ret)
                ret += v
            if node.data == "*":
                v = self._compute_polish(node.left, ret) * \
                    self._compute_polish(node.right, ret)
                ret += v
        else:
            return int(node.data)
        return ret

    def print_polish(self):
        '''
        Helper function to actually print what the member function
        _compute_polish(self, node, ret) returns at a later point.
        '''
        ret = self._compute_polish(self.root)
        return ret


# this function runs the program according to the problem specification
def driver():
    with open(sys.argv[1]) as f:
        next(f)  # skip first line
        data = f.readline().strip().split()  # get data for tree
        st = SyntaxTree(data)  # make tree
        print(st.make_polish())  # show the expression
        print(st.print_polish())  # show the result of the expression


if __name__ == "__main__":
    driver()
