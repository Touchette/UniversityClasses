'''
Author: Touchette
Project Three: Sort IP Addresses using Priority Queue
Completion Date: 2018-02-25

Implementing Professor Sventek's heap interface and using it
along with rich comparison operators to sort incoming IP
addresses by priority of tier and an integer.
'''
import sys


class IPNode():
    '''
    This is the node for the IP Address object that uses the
    rich comparison operators to make Professor Sventek's heap
    interface continue to work despite comparing objects of a
    funky type. It uses priority to check equality, as well as
    having a timestamp attribute to make sure that we maintain
    sort stability. All of these operators use ternaries because
    I wanted the logic to be explicit.
    '''
    def __init__(self, address=None,
                 tier=None,
                 priority=None,
                 timestamp=None):
        self.address = address
        self.tier = tier
        self.priority = priority
        self.timestamp = timestamp

    def __str__(self):
        return self.address

    def __eq__(self, other):
        return True if self.priority == other.priority else False

    def __ne__(self, other):
        return False if self.__eq__(other) else True

    def __lt__(self, other):
        return True if self.priority < other.priority else False

    def __le__(self, other):
        return True if self.__eq__(other) or self.__lt__(other) else False

    def __gt__(self, other):
        return True if self.priority > other.priority else False

    def __ge__(self, other):
        return True if self.__eq__(other) or self.__gt__(other) else False


class BinaryHeap():
    '''
    This is Professor Sventek's heap class from the lecture slides.
    '''
    class Underflow(Exception):
        # Used when look() or remove() are used on
        # an empty binary heap to generate an exception
        def __init__(self, data=None):
            super().__init__(data)

    def __init__(self, array=None):
        if array is None:
            self.bhsize = 0
            self.length = 1025
            self.array = [None] * self.length
        else:
            self.length = len(array) + 1
            self.array = [None] * self.length
            for i in range(len(array)):
                self.array[i + 1] = array[i]
            self.bhsize = self.length - 1
            i = self.length // 2
            while i > 0:
                self.sift_down(i)
                i -= 1

    def __len__(self):
        return self.size()

    def __str__(self):
        return self.to_string()

    def __iter__(self):
        i = 1
        while i <= self.bhsize:
            yield self.array[i]
            i += 1

    def sift_down(self, i):
        left = 2 * i
        right = left + 1
        smallest = i
        if left <= self.bhsize and self.array[left] < self.array[smallest]:
            smallest = left
        if right <= self.bhsize and self.array[right] < self.array[smallest]:
            smallest = right
        if smallest != i:
            x = self.array[i]
            self.array[i] = self.array[smallest]
            self.array[smallest] = x
            self.sift_down(smallest)

    def sift_up(self, i):
        parent = i // 2
        while i > 1 and self.array[parent] >= self.array[i]:
            if self.array[i] == self.array[parent]:
                if self.array[i].timestamp < self.array[parent].timestamp:
                    break
            x = self.array[parent]
            self.array[parent] = self.array[i]
            self.array[i] = x
            i = parent
            parent = i // 2

    def insert(self, x):
        '''
        This resizes the heap based on new entries if it would have gone
        over the size of the default heap.
        '''
        if self.bhsize >= self.length - 1:
            nlength = 2 * self.length
            narray = [None] * nlength
            for i in range(1, self.bhsize + 1):
                narray[i] = self.array[i]
            self.length = nlength
            self.array = narray
        self.bhsize += 1
        self.array[self.bhsize] = x
        self.sift_up(self.bhsize)

    def remove(self):
        if self.bhsize == 0:
            raise BinaryHeap.Underflow("remove() called on empty heap")
        minimum = self.array[1]
        self.array[1] = self.array[self.bhsize]
        self.bhsize -= 1
        self.sift_down(1)
        return minimum

    def look(self):
        if self.bhsize == 0:
            raise BinaryHeap.Underflow("look() called on empty heap")
        return self.array[1]

    def size(self):
        return self.bhsize

    def is_empty(self):
        if self.bhsize == 0:
            return True
        return False

    def to_string(self):
        if self.bhsize == 0:
            result = 'Empty'
        else:
            li = []
            for i in range(1, self.bhsize + 1):
                li.append(str(self.array[i]))
            result = ' '.join(li)
        return result


# this function runs the program according to the problem specification
def driver():
    a_heap = BinaryHeap()
    b_heap = BinaryHeap()
    with open(sys.argv[1]) as f:
        # Get the number of lines
        n = int(f.readline().strip())
        for i in range(n):
            '''
            We use the loop counter here to keep track of the "timestamp"
            of a certain node, ie; when it was inserted into the heap. This
            allows us to maintain stability in our sort.
            '''
            in_data = f.readline().strip().split()
            nn = IPNode(in_data[0], in_data[1], int(in_data[2]), i)
            if nn.tier == "A":
                a_heap.insert(nn)
            else:
                b_heap.insert(nn)
        for _ in range(a_heap.bhsize):
            item = a_heap.remove()
            print(item)
        for _ in range(b_heap.bhsize):
            item = b_heap.remove()
            print(item)


if __name__ == "__main__":
    driver()
