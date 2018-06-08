'''
Author: Touchette
Project Three: Red Black Tree Implementation
Completion Date: 2018-03-12

A Red-Black Tree built from the implementation in the book as
well as Professor Sventek's slides.
'''
import sys
black = "BLACK"
red = "RED"
nil = "NIL"


class Node():
    '''
    Node class to build the tree. I decided that after looking at
    a lot of tutorials and online material that having the helper
    functions to return various information about the node, including
    whether or not it is a root, leaf, has children, etc. Many of these
    are legacy from the Binary Search Tree implementation.
    '''

    def __init__(self, data=None, left=None,
                 right=None, parent=None, color=None):
        self.data = data
        self.left = left
        self.right = right
        self.parent = parent
        self.color = color

    def right_child(self):
        # Returns true if the right child exists.
        return self.right

    def left_child(self):
        # Returns true if the left child exists.
        return self.left

    def is_right(self):
        # Returns true if this node is the right child of
        # its parent (if it has one).
        return self.parent and self.parent.right == self

    def is_left(self):
        # Returns true if this node is the left child of
        # its parent (if it has one).
        return self.parent and self.parent.left == self

    def is_root(self):
        # Returns true if the node is the root, just checks
        # for a None parent to do this.
        return self.parent is None

    def is_leaf_node(self):
        # Returns true if it's a leaf, checks by seeing if
        # children are None
        return self.left is None and self.right is None

    def has_multiple_children(self):
        # Returns true if both children are not None
        return self.left is not None and self.right is not None


class RBTree():
    class RBTreeException(Exception):
        def __init__(self, data=None):
            super().__init__()

    def __init__(self):
        '''
        Initialize the nil_node here, which is the leaf node for all
        other "would-be" leaves as well as the parent to the root. This
        node is important for many things, and makes a lot of the math easier.
        It is essentially the "sentinel" of our data structure.
        '''
        self.root = None
        self.nil_node = Node(data=None, parent=None, color=nil)
        self.size = 0

    def search(self, x):
        '''
        This simply traverses the tree downwards looking for the node
        with the specified data until it reaches the end. It does this
        recursively and will throw an error if the tree is empty or if it
        reaches the end of the tree.
        '''
        if self.size == 0:
            raise RBTree.RBTreeException("Search error! Search on empty tree?")
        if self.root is not None:
            ret = self.search_node(self.root, x)
            if ret:
                return ret.data
            else:
                raise RBTree.RBTreeException("Did not find specified node!")

    def search_node(self, current, x):
        '''
        The recursive part of the search function, will simply go down the
        tree checking if the value we are looking for is greater than or
        less than the node we are currently visiting. Will go down to the
        bottom of the tree, returning None if the value isn't found.
        '''
        if current is None or current.data == x:
            return current
        try:
            if x < current.data:
                return self.search_node(current.left, x)
            else:
                return self.search_node(current.right, x)
        except TypeError:
            pass

    def maximum(self, x=None):
        '''
        Traverses the tree downwards and finds the maximum value,
        this is simply going down the rightt side of the tree (or
        subtree when used in the node class) until it reaches the
        bottom. Returns the final node.
        '''
        try:
            if self.size == 0:
                raise RBTree.RBTreeException("Maximum on empty tree!")
            current = x
            if x is None:
                current = self.root
            while current.right.data is not None:
                current = current.right
            return current
        except AttributeError:
            raise RBTree.RBTreeException("Maximum on empty tree!")

    def minimum(self, x=None):
        '''
        Traverses the tree downwards and finds the minimum value,
        this is simply going down the left side of the tree (or
        subtree when used in the node class) until it reaches the
        bottom. Returns the final node,.
        '''
        try:
            if self.size == 0:
                raise RBTree.RBTreeException("Minimum on empty tree!")
            current = x
            if x is None:
                current = self.root
            while current.left.data is not None:
                current = current.left
            return current
        except AttributeError:
            raise RBTree.RBTreeException("Minimum on empty tree!")

    def print_min_max(self, w):
        '''
        Printer function for the minimum and maximum. Handles both cases.
        '''
        if w == "min":
            mini = self.minimum(self.root)
            return mini.data
        if w == "max":
            maxi = self.maximum(self.root)
            return maxi.data

    def left_rotate(self, x):
        '''
        Rotations restore the red-black properties when we insert a node
        or delete one. Rotations are nothing more than pointer structure
        changes that maintain the binary search tree properties. These
        operations change slightly based on which children a given node has.
        A left rotation, for example, cannot rotate node x if its right child
        is the nil_node.
        '''
        y = x.right  # set y
        x.right = y.left  # turn y's left subtree into x's right subtree
        if y.left != self.nil_node:
            y.left.parent = x
        y.parent = x.parent  # link x's parent to y
        if x.parent == self.nil_node:
            self.root = y
        elif x == x.parent.left:
            x.parent.left = y
        else:
            x.parent.right = y
        y.left = x  # put x on y's left
        x.parent = y

    def right_rotate(self, x):
        '''
        Documentation can be seen in "left_rotate(self, x)".
        '''
        y = x.left  # set y
        x.left = y.right  # turn y's right subtree into x's left subtree
        if y.right != self.nil_node:
            y.right.parent = x
        y.parent = x.parent  # link x's parent to y
        if x.parent == self.nil_node:
            self.root = y
        elif x == x.parent.right:
            x.parent.right = y
        else:
            x.parent.left = y
        y.right = x  # put x on y's right
        x.parent = y

    def insert_fixup(self, z):
        '''
        This fixes the violations that could happen when we insert
        a node into the tree. The violations that could occur are as
        follows:
            ・ Property 2, that the root is black
            ・ Property 4, that any red node cannot have a red child
        If z is the first node inserted, it violates property 2 by virture
        of being red. Line 17 fixes this problem.
        The loop invariant describing fixing problem 4 can be found in slides
        Week06-EfficientSearchIntroAndRB.pdf pages 17-...
        '''
        while z.parent.color == red:
            if z.parent == z.parent.parent.left:
                y = z.parent.parent.right
                if y.color == red:  # case 1
                    z.parent.color = black  # case 1
                    y.color = black  # case 1
                    z.parent.parent.color = red  # case 1
                    z = z.parent.parent  # case 1
                else:
                    if z == z.parent.right:
                        z = z.parent  # case 2
                        self.left_rotate(z)  # case 2
                    z.parent.color = black  # case 3
                    z.parent.parent.color = red  # case 3
                    self.right_rotate(z.parent.parent)  # case 3
            else:
                y = z.parent.parent.left
                if y.color == red:  # case 1
                    z.parent.color = black  # case 1
                    y.color = black  # case 1
                    z.parent.parent.color = red  # case 1
                    z = z.parent.parent  # case 1
                else:
                    if z == z.parent.left:
                        z = z.parent  # case 2
                        self.right_rotate(z)  # case 2
                    z.parent.color = black  # case 3
                    z.parent.parent.color = red  # case 3
                    self.left_rotate(z.parent.parent)  # case 3
        self.root.color = black

    def insert(self, z):
        '''
        Fix-up describes how this function could violate the red-black
        properties and how to fix them. Otherwise, this sets the root
        if it does not exist yet, colors it red (which is bad and fixed
        later), and sets its children, etc.
        '''
        if not self.root:
            self.root = Node(data=z, left=self.nil_node,
                             right=self.nil_node, parent=self.nil_node,
                             color=black)
            self.size += 1
            return
        z = Node(data=z)
        y = self.nil_node
        x = self.root
        while x != self.nil_node:
            y = x
            if z.data < x.data:
                x = x.left
            else:
                x = x.right
        z.parent = y
        if y == self.nil_node:
            self.root = z
        elif z.data < y.data:
            y.left = z
        else:
            y.right = z
        z.left = self.nil_node
        z.right = self.nil_node
        z.color = red
        self.insert_fixup(z)
        self.size += 1

    def transplant(self, u, v):
        '''
        This is the transplant from a binary search tree
        modified for deleting a node from a red-black tree.
        '''
        if u.parent == self.nil_node:
            self.root = v
        elif u == u.parent.left:
            u.parent.left = v
        else:
            u.parent.right = v
        v.parent = u.parent

    def delete_fixup(self, x):
        '''
        Violations that this function can fix include that the
        node removed was the root; if both x and its parent are red;
        moving y around the tree could have caused its ancestors to violate
        property 5; when removing a black node could cause a node to be neither
        red nor black. This function addresses all violations.
        '''
        while x != self.root and x.color == black:
            if x == x.parent.left:
                w = x.parent.right
                if w.color == red:
                    w.color = black  # case 1
                    x.parent.color = red  # case 1
                    self.left_rotate(x.parent)  # case 1
                    w = x.parent.right  # case 1
                if w.left.color == black and w.right.color == black:
                    w.color = red  # case 2
                    x = x.parent  # case 2
                else:
                    if w.right.color == black:
                        w.left.color = black  # case 3
                        w.color = red  # case 3
                        self.right_rotate(w)  # case 3
                        w = x.parent.right  # case 3
                    w.color = x.parent.color  # case 4
                    x.parent.color = black  # case 4
                    w.right.color = black  # case 4
                    self.left_rotate(x.parent)  # case 4
                    x = self.root  # case 4
            else:
                w = x.parent.left
                if w.color == red:
                    w.color = black  # case 1
                    x.parent.color = red  # case 1
                    self.right_rotate(x.parent)  # case 1
                    w = x.parent.left  # case 1
                if w.right.color == black and w.left.color == black:
                    w.color = red  # case 2
                    x = x.parent  # case 2
                else:
                    if w.left.color == black:
                        w.rightt.color = black  # case 3
                        w.color = red  # case 3
                        self.left_rotate(w)  # case 3
                        w = x.parent.leftt  # case 3
                    w.color = x.parent.color  # case 4
                    x.parent.color = black  # case 4
                    w.left.color = black  # case 4
                    self.right_rotate(x.parent)  # case 4
                    x = self.root  # case 4
        x.color = black

    def delete(self, z):
        '''
        This is almost the same as the tree-delete function for a binary
        search tree, where we replace "None" checks with checks for the
        nil_node. Our new red-black transplant is used here as well. We
        make sure to remember the node we removed from the tree as well as
        its color so that we can make sure to fix the tree should a violation
        occur due to its removal. If the node was originally red, all
        properties will hold and nothing needs to be fixed, otherwise we
        use delete_fixup(self, x) to fix it.
        '''
        try:
            if self.size == 0:
                raise RBTree.RBTreeException("Delete on empty tree!")
            z = self.search_node(self.root, z)
            y = z
            y_original_color = y.color
            if z.left == self.nil_node:
                x = z.right
                self.transplant(z, z.right)
            elif z.right == self.nil_node:
                x = z.left
                self.transplant(z, z.left)
            else:
                y = self.minimum(z.right)
                y_original_color = y.color
                x = y.right
                if y.parent == z:
                    x.parent = y
                else:
                    self.transplant(y, y.right)
                    y.right = z.right
                    y.right.parent = y
                self.transplant(z, y)
                y.left = z.left
                y.left.parent = y
                y.color = z.color
            if y_original_color == black:
                self.delete_fixup(x)
        except AttributeError:
            raise RBTree.RBTreeException("Delete on empty tree!")

    def _to_list_inorder(self, node, li):
        '''
        This prints out the tree according to the in-order traversal
        in a recursive manner. I use sys.stdout.write() here so I can
        keep it all on one line. Checks if the tree is empty first.
        '''
        li = li
        if self.size == 0:
            raise RBTree.RBTreeException("Traversal on empty tree!")
        if node.data is not None:
            self._to_list_inorder(node.left, li)
            li.append(str(node.data))
            # sys.stdout.write(str(node.data) + " ")
            self._to_list_inorder(node.right, li)
        return li

    def to_list_inorder(self):
        '''
        Actually runs the printing and makes it look proper due to
        ghetto usage of sys.stdout.write... but this fits the
        implementation specifications so I don't think it's wrong.
        '''
        li = self._to_list_inorder(self.root, [])
        if li:
            return ' '.join(li)
        else:
            raise RBTree.RBTreeException("Empty print!")


# this function runs the program according to the problem specification
def driver():
    rbt = RBTree()
    with open(sys.argv[1]) as f:
        n = int(f.readline().strip())
        for _ in range(n):
            in_data = f.readline().strip().split()
            action, value_option = in_data[0], in_data[1:]
            # Insert
            if action == "insert":
                value = int(value_option[0])
                rbt.insert(value)
            # Remove
            elif action == "remove":
                value = int(value_option[0])
                try:
                    rbt.delete(value)
                except RBTree.RBTreeException:
                    print("TreeError")
            # Search
            elif action == "search":
                value = int(value_option[0])
                try:
                    rbt.search(value)
                    print("Found")
                except RBTree.RBTreeException:
                    print("NotFound")
            # Maximum
            elif action == "max":
                try:
                    print(rbt.print_min_max("max"))
                except RBTree.RBTreeException:
                    print("Empty")
            # Minimum
            elif action == "min":
                try:
                    print(rbt.print_min_max("min"))
                except RBTree.RBTreeException:
                    print("Empty")
            # In-Order Traversal Print
            elif action == "inprint":
                try:
                    print(rbt.to_list_inorder())
                except RBTree.RBTreeException:
                    print("Empty")


if __name__ == "__main__":
    driver()
