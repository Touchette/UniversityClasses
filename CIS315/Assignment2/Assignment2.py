'''
Author: Touchette
Completion Date: Sunday 2018-04-22
Read graphs from a file in the form of nodes and
edges, then calculate how many paths, the shortest
path, and the longest path. Pardon the verbose comments,
I use them to study from later! I also like having
nice documentation for when I put these on GitHub when
the term is over.

Usage: python3 reader.py < dummy_input
'''
import sys
from collections import defaultdict


class DagMeasures():
    def __init__(self):
        '''
        This will be a dictionary who has keys that are
        the nodes in a given graph

        >>> dm = DagMeasures()
        >>> print(dm.get_graph())
        defaultdict(None, {})
        '''
        self.graph = defaultdict()

    def edge_dict_build(self, edgelist):
        '''
        Using a default dictionary, we are able to easily
        build a dictionary for the nodes using a list of
        lists and some simple Python for loop properties

        >>> edgelist = [[1, 2], [1, 3], [2, 3]]
        >>> dm.edge_dict_build(edgelist)
        >>> print(dm.get_graph())
        defaultdict(None, {1: [2, 3], 2: [3]})
        '''
        for k, v in edgelist:
            self.graph.setdefault(k, []).append(v)  # dict[node] = [edges]

    def find_paths(self, dict_graph, end):
        '''
        This finds the total number of paths from the start
        of a directed acyclic graph to a destination node, end.
        This works pretty much in the same manner as a breadth-first
        search without keeping track of visited nodes, etc.

        >>> edgelist = [[1, 2], [1, 3], [2, 3]]
        >>> dm.edge_dict_build(edgelist)
        >>> print(dm.find_paths(dm.get_graph(), 3))
        2
        '''
        paths = [0] * (end + 1)
        paths[1] = 1
        for i in range(1, end):
            for j in self.graph[i]:
                paths[j] += paths[i]
        return paths[end]

    def longest_path(self, dict_graph, start, end):
        '''
        Returns the longest path from a start node to an end
        node in a given graph. This works in O(V + E) time
        assuming the graph is topologically sorted 1, 2, .., n.
        Works by finding the max distances from the previously
        visited nodes adjanency lists.

        >>> edgelist = [[1, 2], [1, 3], [2, 3]]
        >>> dm.edge_dict_build(edgelist)
        >>> print(dm.longest_path(dm.get_graph(), 1, 3))
        2
        '''
        distances = [0] * (end + 1)
        for i in range(1, end):
            for j in self.graph[i]:
                distances[j] = max(distances[j], distances[i] + 1)
        return max(distances[1], distances[-1])

    def shortest_path(self, dict_graph, start, end):
        '''
        Finds the shortest path fro ma start node to an end node
        in a given graph. This works in O(V + E) time assuming that
        the graph is topologically sorted 1, 2, .., n. This wrks
        by performing a breadth-first search and keeping track of
        visited nodes, as well as using a queue data structure to
        hold the adjacent nodes that are yet to be visited.

        >>> edgelist = [[1, 2], [1, 2], [2, 3]]
        >>> dm.edge_dict_build(edgelist)
        >>> print(dm.shortest_path(dm.get_graph(), 1, 3))
        2
        '''
        visited = []
        queue = [[start]]

        if start == end:
            return None

        while queue:
            path = queue.pop(0)
            node = path[-1]
            if node not in visited:
                v = dict_graph[node]
                for u in v:
                    newpath = list(path)
                    newpath.append(u)
                    queue.append(newpath)
                    if u == end:
                        return len(newpath) - 1

                visited.append(node)

    def clear(self):
        '''
        Simply calls the clear method on our dictionary to empty
        it for the next graph to use.

        >>> edgelist = [[1, 2], [1, 3], [2, 3]]
        >>> dm.edge_dict_build(edgelist)
        >>> print(dm.get_graph())
        defaultdict(None, {1: [2, 3], 2: [3]})
        >>> dm.clear()
        >>> print(dm.get_graph())
        defaultdict(None, {})
        '''
        self.graph.clear()

    def get_graph(self):
        '''
        Getter method for the dictionary so as to not access
        it directly.

        >>> edgelist = [[1, 2], [1, 3], [2, 3]]
        >>> dm.edge_dict_build(edgelist)
        >>> print(dm.get_graph())
        defaultdict(None, {1: [2, 3], 2: [3]})
        '''
        return self.graph


def driver():
    dm = DagMeasures()
    num_graphs = int(sys.stdin.readline())

    # Perform this as many times as we have graphs,
    # the first line we read in is that number
    for i in range(num_graphs):

        # Initialize all the info we need to build the graph,
        # we will need to have the number of nodes, the number
        # of edges, and then initialize the list of edges to
        # build the dictionary we make inside the DagMeasures class
        graph_nodes = int(sys.stdin.readline().strip())
        graph_edges = int(sys.stdin.readline().strip())
        edgelist = []

        # This is building the edgelist we initialized prior in order
        # to build the dictionary for DagMeasures
        for _ in range(graph_edges):
            edge = sys.stdin.readline().strip().split(' ')
            edge = list(map(int, edge))
            edgelist.append(edge)

        # Build the dictionary
        dm.edge_dict_build(edgelist)

        # Long ugly print statement that handles printing out the answer
        # for the specific graph we're working on. We subtract 1 from the
        # lengths to exclude the node we're starting from
        graph_no = i + 1
        total_paths = dm.find_paths(dm.get_graph(), graph_nodes)
        shortest = dm.shortest_path(dm.get_graph(), 1, graph_nodes)
        longest = dm.longest_path(dm.get_graph(), 1, graph_nodes)
        print(("Graph Number: {}\n"
               "Shortest Path: {}\n"
               "Longest Path: {}\n"
               "Number of Paths: {}\n").format(graph_no,
                                               shortest,
                                               longest,
                                               total_paths))

        # Clear the dictionary to be used for the next graph
        dm.clear()


if __name__ == "__main__":
    driver()
