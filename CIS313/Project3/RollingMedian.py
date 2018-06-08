'''
Author: Touchette
Project Three: Calculate Rolling Median
Completion Date: 2018-02-25

A class that implements a calculator to keep tracking of the
rolling median of a continuous input of numbers.
'''
import sys
import heapq


class RollingMedianCalc():
    def __init__(self):
        '''
        Initialize the max-heap and min-heap by using lists,
        the built-in python heapq module can handle these in order
        to keep the heap properties (albeit in a slightly weird
        way for a max-heap). We also have the size of each of the
        heaps here.
        '''
        self.minheap = []
        self.maxheap = []
        self.maxsize = 0
        self.minsize = 0

    def minheap_add(self, x):
        '''
        Adding to a min-heap is very straightforward, just need to
        use the built-in push method for the heapq module on our
        list. It maintains the min-heap property by default. We
        also increment the size.
        '''
        self.minsize += 1
        heapq.heappush(self.minheap, (x))

    def minheap_pop(self):
        '''
        Popping from the min-heap is equally as easy using the
        built-in method, here we decrement the size by one.
        '''
        self.minsize -= 1
        return heapq.heappop(self.minheap)

    def maxheap_add(self, x):
        '''
        Creating a max-heap via the built-in heapq methods is slightly
        weirder than making a min-heap. Because there isn't a built-in
        method to maintain a max-heap property, we can keep track of it
        by simply inverting the numbers to negative -- whenever we need
        to pop them back out we convert them back and our max-heap
        property is satisfied. We also increment the size here.
        '''
        self.maxsize += 1
        heapq.heappush(self.maxheap, (x * -1))

    def maxheap_pop(self):
        '''
        Same as the min-heap pop, except we had to invert the number back
        to positive. Could have also used abs() here but I thought the
        multiplication was more explicit.
        '''
        self.maxsize -= 1
        popped = heapq.heappop(self.maxheap)
        return (popped * -1)

    def compare_roots_add(self, x):
        '''
        This will add a number to the min-heap or the max-heap depending
        on if the number to be added is smaller than the root of the
        max-heap. If it is, it goes into the min-heap instead. We can
        use list indexing notation to access the root of each heap,
        they are located at index 0. This method uses the previous
        methods to add to the heaps, and is the one actually used when
        adding numbers after reading the file input.
        '''
        if x < (self.maxheap[0] * -1):
            self.maxheap_add(x)
        else:
            self.minheap_add(x)

    def balance_heaps(self):
        '''
        This method is called every time we add a number to the heaps. We
        need to check if they are balanced, ie; they are not bigger than
        each other by a value more than one. We can check if one is bigger
        than the other by more than one, if so, we pop the root of the
        bigger one and add it onto the smaller one. This ensures that our
        heapsizes are always within one of each other.
        '''
        if (self.minsize - self.maxsize) > 1:
            item = self.minheap_pop()
            self.maxheap_add(item)
        elif (self.maxsize - self.minsize) > 1:
            item = self.maxheap_pop()
            self.minheap_add(item)
        else:
            return

    def calculate_median(self):
        '''
        The actual function to calculate the median, this makes 3 checks
        to see which calculation we need. If the two heaps are the same size,
        we take the sum of their roots and divide by 2 to acquire the median.
        If they have differing sizes, we simply return the root of the larger
        one. This will always give us our median assuming that the heaps are
        balanced and properly formed, which they are due to the checks we made
        previously; especially balancing the heaps which happens every time
        this function is called.
        '''
        self.balance_heaps()
        if self.minsize == self.maxsize:
            median = ((self.maxheap[0] * -1) + self.minheap[0]) / 2
        elif self.minsize > self.maxsize:
            median = self.minheap[0]
        elif self.maxsize > self.minsize:
            median = self.maxheap[0] * -1
        if (median % 2) == 0:
            median = int(median)
        return round(median, 1)


# this function runs the program according to the problem specification
def driver():
    rmc = RollingMedianCalc()
    with open(sys.argv[1]) as f:
        # Get the number of lines
        n = int(f.readline().strip())
        # Reduce the number of lines by two, as the first two numbers entered
        # are special
        n -= 2
        # Grabbing the first two "special" numbers
        first = int(f.readline().strip())
        second = int(f.readline().strip())
        # First number in is always the median by itself as there is nothing
        # else entered as of yet
        print("Median:\t", first)
        # The smallest of the two first numbers goes into the max-heap, the
        # largest goes into the min-heap.
        if first < second:
            rmc.maxheap_add(first)
            rmc.minheap_add(second)
        else:
            rmc.minheap_add(first)
            rmc.maxheap_add(second)
        # Grab the median of the first two numbers.
        print("Median:\t", rmc.calculate_median())
        # Begin doing the rest of the numbers in the file.
        for _ in range(n):
            value = int(f.readline().strip())
            rmc.compare_roots_add(value)
            print("Median:\t", rmc.calculate_median())


if __name__ == "__main__":
    driver()
