'''
Author: Touchette
Project One: Queue and Stack using a LinkedList implementation
Completion Date: 2018-01-28

Linked List class to be used by other files to implement a stack and queue
respectively. This was taken from the Week02-LinearDataStructures.pdf file
available on canvas, and modified heavily to support the necessary operations
for both a stack and queue.
'''


class DoubleLL(object):
    class LLNode(object):
        '''
        Defining the node objects that will fill the stack/queue, as per a
        linked list these nodes point to the next object in the stack via the
        self.next variable. The self.prev points to the previous variable in
        the case of the queue.
        '''
        def __init__(self, prv=None, nxt=None, data=None):
            self.data = data  # what is stored in the node
            self.next = nxt  # what the node points to
            self.prev = prv  # previous node it points to

    class Underflow(Exception):
        '''
        The exception class that will be used by both the stack and queue to
        let the user know when a pop has been performed on an empty stack or
        queue.
        '''
        def __init__(self, data=None):
            super().__init__()

    def __init__(self):
        '''
        Initializing the linked list, the size starts at 0 and the initial
        head/tail is None. This None value is what the first node of the list
        will ALWAYS point to, and is sometimes how we check the existence of a
        next node, as well as checking if the stack is empty.
        '''
        self.size = 0
        self.head = None
        self.tail = None

    def represent(self):
        '''
        The stack represented by a python list, used to print it out. Due to
        the way the linked list is implemented, I start by inserting the last
        object I put in and working my way down. This was given in the sample
        code from Week2's powerpoint (slide 19), and modified to be able to
        return both the stack and the queue as well as handle empty cases. I
        left it in my DoubleLinkedList class to be able to test the class
        independently of the stack and queue "implementations" by adding an
        if __name__ == "__main__" clause at the bottom of this file. Not used
        for anything anymore!
        '''
        if self.is_empty():  # empty stack, cut function by returning here
            return ["Empty"]  # list so ' '.join() works properly
        itemList = []  # the list itself where we will store each node
        node = self.head   # this is the top node in the list
        while node is not None:  # checking that a next node actually exists
            itemList.append(str(node.data))  # insert next node to print
            node = node.next  # move on to the next node to print out
        return itemList

    def is_empty(self):
        # self explanatory
        return self.size == 0

    def stack_push(self, x):
        '''
        This is the "append" method for the stack implementation, and it pretty
        much implements the method as if it were a singly linked list; there is
        no need to keep track of a previous node pointer for the stack.
        '''
        newNode = self.LLNode(None, None, x)  # make node with given data
        newNode.next = self.head  # first node points to None
        self.head = newNode  # changing the head for new nodes to point to
        self.size += 1  # increment the size as we added a node
        return self.head.data

    def peek(self):
        '''
        Just a peek method for the stack to check the content of the head
        '''
        return self.head.data

    def queue_enqueue(self, x):
        '''
        This is the "append" method for the queue, and it implements the method
        as if it were a doubly linked list. Very similar to the stack_push()
        method except for the fact that we now take care of a tail as well.
        '''
        newNode = self.LLNode(None, None, x)  # make node with given data
        if self.head is None:
            self.head = self.tail = newNode  # empty, new node is head & tail
        else:
            newNode.prev = self.tail  # node goes in at the end, points to None
            newNode.next = None  # points to the next item
            self.tail.next = newNode  # old tail (None) points to new node
            self.tail = newNode  # new node is now new tail
        self.size += 1  # increment the size as we added a node
        return self.tail.data

    def pop(self):
        '''
        Pop is the same method for both the stack and the queue, as it removes
        the same element for both. The fundamental difference between the stack
        and queue implementations (besides method names) is the order in which
        objects are added to the data structure. Where queues append at the end
        (back of the queue), stacks append at the beginning (top of the stack).
        '''
        if self.is_empty():  # check if empty, can't pop if true
            raise DoubleLL.Underflow()
        while self.head is not None:  # check that the next node exists
            popped = self.head  # last node in is the node we're removing
            self.head = self.head.next  # new head, the node 'popped' gave
            self.size -= 1  # decrement size by one, we removed a node
            return popped.data  # return the data we popped
�������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������MinHeap.py������������������������������������������������������������������������������������������0000664�0001750�0001750�00000011463�13241500050�011406� 0����������������������������������������������������������������������������������������������������ustar  �nate����������������������������nate�������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������'''
Author: Nate Letz
Project Two: Implement a min-heap
Completion Date: 2018-02-15

Simply implements a min-heap that maintains the min-heap property
using a simple python list and a function that is called whenever
the heap is modified.
'''
import sys


class MinHeap():

    class HeapError(Exception):
        '''
        The exception class that will be used to raise HeapErrors
        when certain operations are attempted in remove(), to_string(),
        and look().
        '''
        def __init__(self, data=None):
            super().__init__()

    def __init__(self):
        # The list is initialized with None to use simple integer division
        # in the min_heapify function
        self.list = [None]
        self.size = 0

    def min_heapify(self, index):
        '''
        We only need to check first i // 2 nodes, because others are trivially
        leaves. Check from the last one to the first one, any node's parent
        is always (node // 2) indices below itself. We always check if the
        node's parent is bigger, if it is, then the min_heap property isn't
        satisfied; we must perform the swap. If not, move on. Keep going until
        the (node // 2) index is 0, which means we have reached the root.
        '''
        # check that it is not the root node
        while index // 2 > 0:
            # check if parent is bigger
            if self.list[index] < self.list[index // 2]:
                # grab the parent
                parent = self.list[index // 2]
                # swap the parent and the child
                self.list[index // 2] = self.list[index]
                self.list[index] = parent
            # move to next node
            index = index // 2

    def is_empty(self):
        # Self-explanatory
        return self.size == 0

    def look(self):
        # Will raise an "underflow" exception if the heap is empty.
        # Otherwise, it returns the root, which is the "highest priority"
        # item due to always being the lowest value key.
        if self.is_empty():
            raise MinHeap.HeapError()
        return self.list[1]

    def insert(self, x):
        '''
        Insert just appends the item onto the list, which will be the
        bottom of the heap, and then increases the size. The item just
        appended may not be in the correct position, though, so we must
        maintain the heap property by calling min_heapify.
        '''
        self.list.append(x)
        self.size += 1
        self.min_heapify(self.size)

    def remove(self):
        '''
        Remove will always return the highest priority item on the heap,
        which in this case is the root node due to the fact that this is a
        min-heap. This function will first store the root in a variable, then
        swap the root and the last item in the heap. It pops the (stored) root
        off and then decrements the size, and finally maintains the heap
        property by min_heapifying the heap again. Finally it returns that root
        we stored at the beginning.
        '''
        if self.size == 0:
            raise MinHeap.HeapError()  # check underflow
        returned = self.list[1]  # get root, will return this
        self.list[1] = self.list[-1]  # swap root with last item
        del self.list[-1]  # delete old root
        self.size -= 1  # decrement size
        self.min_heapify(self.size)  # maintain min-heap property
        return returned

    def to_string(self):
        # Simple print function of everything in the list. Always works
        # because the heap property is being maintained from the get-go.
        if self.is_empty():
            raise MinHeap.HeapError()
        slicedlist = self.list[1:]  # I get the heap without the start "None"
        print(' '.join(slicedlist))

    def get_size(self):
        # Self-explanatory
        return self.size


# this function runs the program according to the problem specification
def driver():
    mh = MinHeap()
    with open(sys.argv[1]) as f:
        n = int(f.readline().strip())
        for _ in range(n):
            in_data = f.readline().strip().split()
            action, value_option = in_data[0], in_data[1:]
            if action == "insert":
                mh.insert(value_option[0])
            elif action == "remove":
                try:
                    print(mh.remove())
                except MinHeap.HeapError:
                    print("HeapError")
            elif action == "print":
                try:
                    mh.to_string()
                except MinHeap.HeapError:
                    print("Empty")
            elif action == "best":
                try:
                    print(mh.look())
                except MinHeap.HeapError:
                    print("HeapError")
            elif action == "size":
                print(mh.get_size())


if __name__ == "__main__":
    driver()
�������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������README����������������������������������������������������������������������������������������������0000664�0001750�0001750�00000000712�13241470444�010403� 0����������������������������������������������������������������������������������������������������ustar  �nate����������������������������nate�������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������Nate Letz

Problem 1: python3 CollageChecker.py dummyinput.input >> output.output && diff output.output dummyoutput.output
Problem 2: python3 WellFormattedBrackets.py dummyinput.input >> output.output && diff output.output dummyoutput.output
Problem 3: python3 RestaurantTest.py dummyinput.input >> output.output && diff output.output dummyoutput.output
Problem 4: python3 MinHeap.py dummyinput.input >> output.output && diff output.output dummyoutput.output������������������������������������������������������RestaurantTest.py�����������������������������������������������������������������������������������0000664�0001750�0001750�00000004217�13241500335�013062� 0����������������������������������������������������������������������������������������������������ustar  �nate����������������������������nate�������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������'''
Author: Nate Letz
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
        self.energy -= self.list[self.tail].gives
        self.energy += self.list[self.tail].req
        if self.tail == (self.size - 1):
            self.tail == 0
        else:
            self.tail += 1
        if self.tail == self.head:
            if self.head == (self.size - 1):
                print("Failure")
                return False
            else:
                self.head += 1

    def advanceHead(self):
        self.energy -= self.list[self.head].req
        self.energy += self.list[self.head].gives
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
���������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������stack.py��������������������������������������������������������������������������������������������0000664�0001750�0001750�00000005313�13240653025�011201� 0����������������������������������������������������������������������������������������������������ustar  �nate����������������������������nate�������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������'''
Author: Nate Letz
Project One: Queue and Stack using a LinkedList implementation
Completion Date: 2018-01-28

This is the stack file that will take the DoubleLinkedList implementation and
produce a stack capable of pushing and popping items in a first-in,
last-out manner.
'''
import sys
import DoubleLinkedList


class Stack():
    '''
    The implementation of a stack according to the DoubleLinkedList.py
    linked list implementation. According to the docstrings inside of
    DoubleLinkedList.py, this is pretty much implemented using a singly
    linked list. No exception handling is required here.
    '''
    def __init__(self):
        self.linked_list = DoubleLinkedList.DoubleLL()

    def push(self, x):
        # How this works is defined in DoubleLinkedList.py
        return self.linked_list.stack_push(x)

    def pop(self):
        # How this works is defined in DoubleLinkedList.py
        return self.linked_list.pop()

    def is_empty(self):
        # How this works is defined in DoubleLinkedList.py
        return self.linked_list.is_empty()

    def peek(self):
        # How this works is defined in DoubleLinkedList.py
        return self.linked_list.peek()


# args: s, Stack
def print_stack(s):
    '''
    The print function, which will take a single argument (the stack)
    and print out its contents. It does this by popping every item in the
    stack until it is empty, appending each item to a list as it goes. Once
    it reaches the end, it will print out the items and then reconstruct the
    stack by pushing them back on. It pushes a reversed order list because the
    items came out from the top to bottom and we want to reconstruct the stack
    from bottom to top.
    '''
    if s.is_empty():
        print("Empty")
        return False
    else:
        itemList = []
        while not s.is_empty():
            node = s.pop()
            itemList.append(str(node))
        print(' '.join(itemList))
        for item in reversed(itemList):
            s.push(int(item))
    return True


# this function runs the program according to the problem specification
def driver():
    s = Stack()
    with open(sys.argv[1]) as f:
        n = int(f.readline().strip())
        for _ in range(n):
            in_data = f.readline().strip().split()
            action, value_option = in_data[0], in_data[1:]
            if action == "push":
                value = int(value_option[0])
                s.push(value)
            elif action == "pop":
                try:
                    print(str(s.pop()))
                except DoubleLinkedList.DoubleLL.Underflow:
                    print("StackError")
            elif action == "print":
                print_stack(s)


if __name__ == "__main__":
    driver()
���������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������WellFormattedBrackets.py����������������������������������������������������������������������������0000664�0001750�0001750�00000003256�13241477423�014337� 0����������������������������������������������������������������������������������������������������ustar  �nate����������������������������nate�������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������'''
Author: Nate Letz
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
������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
