'''
Author: Touchette
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
