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
