# Seventh Assignment in CIS 212
CIS 212 Assignment Seven, completed November 2017. This program simulates a producer-consumer relationship via multithreading.

# Regular
The regular version of this assignment simply has a single producer produce 1000 strings in a LinkedBlockingQueue with a capacity of 100. After it has filled to 100, the consumers will begin to consume the strings, making sure to be synchronized so that the end result is always accurate. Both the producer and consumer maintain a list of what they have consumed and print out every 150 events consumed/produced. This supports an arbitrary number of consumers.

# Extra
The extra credit for this project consists of a relationship between an arbitrary number of producers and consumers. It does the same as the regular version, but this time using the LinkedList data structure, thus requiring manual synchronization of all objects and methods.
