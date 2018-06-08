'''
Author: Touchette
Project Three: Binary Search Tree Implementation
Completion Date: 2018-02-25

A class that implements a binary search tree providing the methods for
traversals, inserts, removals, searches, etc. Also contains the driver
for running the program and performing the tests. (I wanted to write
a separate driver file but I didn't have the time to get it done and
test it)
'''
import sys


class BST:
    class Node():
        '''
        Node class to build the tree. I decided that after looking at
        a lot of tutorials and online material that having the helper
        functions to return various information about the node, including
        whether or not it is a root, leaf, has children, etc. These will
        be used mostly in the deletion method, as that is the most complicated
        part of the search tree.
        '''

        def __init__(self, x=None, left=None, right=None,
                     parent=None):
            self.data = x
            self.left = left
            self.right = right
            self.parent = parent

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

        def has_child(self):
            # Returns true if a single child is not None
            return self.left is not None or self.right is not None

        def has_multiple_children(self):
            # Returns true if both children are not None
            return self.left is not None and self.right is not None

        def find_successor(self):
            '''
            This will find the left-most child of any given node's
            right child. This is used in handling case 3 of the deletion
            function. There are three cases when finding a successor:
            the node has a right child, therefore the successor is the left
            most node in the right subtree; the node has no child and is the
            left child of its parent, making the parent the successor; and
            the node is the right child and has no child, the successor of this
            is the successor of its parent.
            '''

            def getmin(self):
                '''
                Same as the minimum() function from the BST class itself pretty
                much, but this one is used specifically to find the minimum
                inside of the Node class to avoid any errors (which were coming
                up when I tried using the BST minimum here instead).
                '''
                current = self
                while current.left_child() is not None:
                    current = current.left
                return current

            successor = None
            if self.right_child():
                # Case 1
                successor = getmin(self.right)
            else:
                if self.parent:
                    # Case 2
                    if self.is_left():
                        successor = self.parent
                    # Case 3
                    else:
                        self.parent.right = None
                        successor = self.parent.find_successor()
                        self.parent.right = self
            return successor

        def cut(self):
            '''
            This is pretty much a search and delete method to be used
            in handling case 3 of the deletion function. This is better
            than calling delete recursively because we do not want to search
            the tree more than once, this handles the removal elegantly and
            without having to use recursion.
            '''
            if self.is_leaf_node():
                if self.is_left():
                    self.parent.left = None
                else:
                    self.parent.right = None
            elif self.has_child():
                if self.left_child():
                    if self.is_left():
                        self.parent.left = self.left
                    else:
                        self.parent.right = self.left
                    self.left.parent = self.parent
                else:
                    if self.is_left():
                        self.parent.left = self.right
                    else:
                        self.parent.right = self.right
                    self.right.parent = self.parent

        def swap(self, x, left, right):
            '''
            Swapping function for case 3 of the deletion function. This will
            be used to handle the simpler cases of the deletion, where the
            methods "cut" and "find_successor" are not used.
            '''
            self.data = x
            self.left = left
            self.right = right
            if self.left_child():
                self.left.parent = self
            if self.right_child():
                self.right.parent = self

    class BSTException(Exception):
        # Exception class
        def __init__(self, data=None):
            super().__init__()

    def __init__(self):
        self.root = None
        self.size = 0

    def node_insert(self, current, x):
        '''
        Function is described in the insert method.
        '''
        if x < current.data:
            if current.left_child():
                self.node_insert(current.left, x)
            else:
                current.left = BST.Node(x, parent=current)
        else:
            if current.right_child():
                self.node_insert(current.right, x)
            else:
                current.right = BST.Node(x, parent=current)

    def insert(self, x):
        '''
        Starting at the root, we check if it actually exists. If it
        doesn't, then we simply create a new node and put it there. The
        root node's parent will always be none, so we don't have to set it.
        If the root does exist, then we call the recursive function for
        inserting, node_insert. This takes the starting position, which
        will be the root, and works its way down the tree until it finds
        the position at which to insert the node. Finally, we increment the
        size by one regardless of which method we used to insert a node.
        '''
        if not self.root:
            self.root = BST.Node(x)
        else:
            self.node_insert(self.root, x)
        self.size += 1

    def delete(self, x):
        '''
        When deleting a node, first we need to search for it. If we find
        it, there are 3 cases that can occur: the node has no children,
        the node has one child, and the node has two children. In the first
        case, the job is simple: just delete the node and remove the parent's
        pointers to the node. In the second case, it is a bit more complex.
        We need to consider many cases, whether the node is a left or right
        child, which side the node's single child is on, etc. This provides
        six cases, 3 for the right side and 3 for the left side. In the third
        case, we need to find the successor for the node to be replaced with.
        To find the successor, we implement a method in the node class to find
        the left-most child of any given node's right child. This is the node
        that we will use to replace the node we are deleting via the node
        class' built-in swap. This successor can have no more than one child,
        so we can remove it using the previous cases' deletion methods.
        '''
        if self.size == 0:
            raise BST.BSTException("Deletion on empty tree!")
        if self.size > 1:
            removed = self.search_node(self.root, x)
            if removed:
                self.remove(removed)
                self.size -= 1
            else:
                raise BST.BSTException("Deletion error! Node not found!")
        elif self.size == 1 and self.root.data == x:
            self.root = None
            self.size -= 1

    def remove(self, current):
        '''
        How this works is described in the Node class, as well as in the
        delete function.
        '''
        # Case 1, the node to remove is a leaf
        if current.is_leaf_node():
            if current.parent:
                if current == current.parent.left:
                    current.parent.left = None
                else:
                    current.parent.right = None

        # Case 3, the node to remove has two children
        elif current.has_multiple_children():
            successor = current.find_successor()
            successor.cut()
            current.data = successor.data

        # Case 2, the node to remove has one child
        else:
            if current.left_child():
                if current.is_left():
                    current.left.parent = current.parent
                    current.parent.left = current.left
                elif current.is_right():
                    current.left.parent = current.parent
                    current.parent.right = current.right
                else:
                    current.swap(current.left.data,
                                 current.left.left, current.left.right)
            else:
                if current.is_left():
                    current.right.parent = current.parent
                    current.parent.left = current.right
                elif current.is_right():
                    current.right.parent = current.parent
                    current.parent.right = current.right
                else:
                    current.swap(current.right.data,
                                 current.right.left, current.right.right)

    def search(self, x):
        '''
        This simply traverses the tree downwards looking for the node
        with the specified data until it reaches the end. It does this
        recursively and will throw an error if the tree is empty or if it
        reaches the end of the tree. We can use __getitem__ to use the
        functionality of this method.
        '''
        if self.size == 0:
            raise BST.BSTException("Search error! Search on empty tree?")
        if self.root is not None:
            ret = self.search_node(self.root, x)
            if ret:
                return ret.data
            else:
                raise BST.BSTException("Did not find specified node!")

    def search_node(self, current, x):
        '''
        The recursive part of the search function, will simply go down the
        tree checking if the value we are looking for is greater than or
        less than the node we are currently visiting. Will go down to the
        bottom of the tree, returning None if the value isn't found.
        '''
        if current is None:
            return None
        elif current.data == x:
            return current
        elif x < current.data:
            return self.search_node(current.left, x)
        elif x > current.data:
            return self.search_node(current.right, x)

    def maximum(self, x=None):
        '''
        Traverses the tree downwards and finds the maximum value,
        this is simply going down the rightt side of the tree (or
        subtree when used in the node class) until it reaches the
        bottom. Returns the final node, whose child is "None".
        '''
        if self.size == 0:
            raise BST.BSTException("Maximum on empty tree!")
        current = x
        if x is None:
            current = self.root
        while current.right is not None:
            current = current.right
        return current.data

    def minimum(self, x=None):
        '''
        Traverses the tree downwards and finds the minimum value,
        this is simply going down the left side of the tree (or
        subtree when used in the node class) until it reaches the
        bottom. Returns the final node, whose child is "None".
        '''
        if self.size == 0:
            raise BST.BSTException("Minimum on empty tree!")
        current = x
        if x is None:
            current = self.root
        while current.left is not None:
            current = current.left
        return current.data

    def best_path(self, node):
        '''
        Returns the so called "best path" of the tree, defined as the
        path that contains the highest amount of "5"s in the keys.
        '''
        if node is None:
            return 0

        left = self.best_path(node.left)
        right = self.best_path(node.right)
        return max(left, right) + str(node.data).count('5')

    def _to_list_preorder(self, node):
        '''
        This prints out the tree according to the pre-order traversal
        in a recursive manner. I use sys.stdout.write() here so I can
        keep it all on one line. Checks if the tree is empty first.
        '''
        if self.size == 0:
            raise BST.BSTException("Traversal on empty heap!")
        if node:
            sys.stdout.write(str(node.data) + " ")
            self._to_list_preorder(node.left)
            self._to_list_preorder(node.right)

    def to_list_preorder(self):
        '''
        Actually runs the printing and makes it look proper due to
        ghetto usage of sys.stdout.write... but this fits the
        implementation specifications so I don't think it's wrong.
        '''
        self._to_list_preorder(self.root)
        sys.stdout.write("\n")

    def _to_list_inorder(self, node=None):
        '''
        This prints out the tree according to the in-order traversal
        in a recursive manner. I use sys.stdout.write() here so I can
        keep it all on one line. Checks if the tree is empty first.
        '''
        if self.size == 0:
            raise BST.BSTException("Traversal on empty heap!")
        if node:
            self._to_list_inorder(node.left)
            sys.stdout.write(str(node.data) + " ")
            self._to_list_inorder(node.right)

    def to_list_inorder(self):
        # Helper function for printing inorder.
        self._to_list_inorder(self.root)
        sys.stdout.write("\n")

    def _to_list_postorder(self, node):
        '''
        This prints out the tree according to the post-order traversal
        in a recursive manner. I use sys.stdout.write() here so I can
        keep it all on one line. Checks if the tree is empty first.
        '''
        if self.size == 0:
            raise BST.BSTException("Traversal on empty heap!")
        if node:
            self._to_list_postorder(node.left)
            self._to_list_postorder(node.right)
            sys.stdout.write(str(node.data) + " ")

    def to_list_postorder(self):
        self._to_list_postorder(self.root)
        sys.stdout.write("\n")


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
                # print("Insert: inserted {}!".format(value))
            # Remove
            elif action == "remove":
                value = int(value_option[0])
                try:
                    bst.delete(value)
                except BST.BSTException:
                    print("TreeError")
            # Search
            elif action == "search":
                value = int(value_option[0])
                try:
                    bst.search(value)
                    print("Found")
                except BST.BSTException:
                    print("NotFound")
            # Maximum
            elif action == "max":
                try:
                    print(bst.maximum())
                except BST.BSTException:
                    print("Empty")
            # Minimum
            elif action == "min":
                try:
                    print(bst.minimum())
                except BST.BSTException:
                    print("Empty")
            # Pre-Order Traversal Print
            elif action == "preprint":
                try:
                    bst.to_list_preorder()
                except BST.BSTException:
                    print("Empty")
            # In-Order Traversal Print
            elif action == "inprint":
                try:
                    bst.to_list_inorder()
                except BST.BSTException:
                    print("Empty")
            # Post-Order Traversal Print
            elif action == "postprint":
                try:
                    bst.to_list_postorder()
                except BST.BSTException:
                    print("Empty")


if __name__ == "__main__":
    driver()
