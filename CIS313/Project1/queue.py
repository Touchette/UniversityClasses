'''
Author: Touchette
Project One: Queue and Stack using a LinkedList implementation
Completion Date: 2018-01-28

This is the queue file that will take the DoubleLinkedList implementation and
produce a queue capable of enqueuing and dequeueing items in a fitrst-in,
first-out manner.
'''
import sys
import DoubleLinkedList


class Queue():
    '''
    All the methods here are technically "inherited" or "implemented" from
    the original DoubleLinkedList.py class. Due to the way I implemented it,
    I don't even need to do any type of exception handling here.
    '''
    def __init__(self):
        self.linked_list = DoubleLinkedList.DoubleLL()

    def enqueue(self, x):
        # How this works is defined in DoubleLinkedList.py
        return self.linked_list.queue_enqueue(x)

    def dequeue(self):
        # How this works is defined in DoubleLinkedList.py
        return self.linked_list.pop()

    def is_empty(self):
        # How this works is defined in DoubleLinkedList.py
        return self.linked_list.is_empty()


# args: q, Queue
def print_queue(q):
    '''
    The print function, which will take a single argument (the queue)
    and print out its contents. It does this by dequeueing every item in the
    queue until it is empty, appending each item to a list as it goes. Once
    it reaches the end, it will print out the items and then reconstruct the
    queue by enqueueing them once more.
    '''
    if q.is_empty():
        print("Empty")
        return False
    else:
        itemList = []
        while not q.is_empty():
            node = q.dequeue()
            itemList.append(str(node))
        print(' '.join(itemList))
        for item in itemList:
            q.enqueue(int(item))
    return True


# this function runs the program according to the problem specification
def driver():
    q = Queue()
    with open(sys.argv[1]) as f:
        n = int(f.readline().strip())
        for _ in range(n):
            in_data = f.readline().strip().split()
            action, value_option = in_data[0], in_data[1:]
            if action == "enqueue":
                value = int(value_option[0])
                q.enqueue(value)
            elif action == "dequeue":
                try:
                    print(str(q.dequeue()))
                except DoubleLinkedList.DoubleLL.Underflow:
                    print("QueueError")
            elif action == "print":
                print_queue(q)


if __name__ == "__main__":
    driver()
