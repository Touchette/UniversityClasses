'''
Author: Touchette
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
