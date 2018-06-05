from collections import defaultdict

class Graph:
 
    def __init__(self):
 
        # store graph
        self.graph = defaultdict(list)
 
    # add an edge to graph
    def addEdge(self,u,v):
        self.graph[u].append(v)
 
    # BFS of graph
    def BFS(self, s):
 
        # vertices as not visited
        visited = [False] * (len(self.graph))
 
        # Create a queue for BFS
        queue = []
 
        # Mark the source node as 
        # visited and enqueue it
        queue.append(s)
        visited[s] = True
 
        while queue:
 
            # Dequeue a vertex from 
            # queue and print it
            s = queue.pop(0)
            print (s, end = " ")
 
            # Get all adjacent vertices of the
            # dequeued vertex s. If a adjacent
            # has not been visited, then mark it
            # visited and enqueue it
            for i in self.graph[s]:
                if visited[i] == False:
                    queue.append(i)
                    visited[i] = True
 
	def DFS(self,v):
 
			# Mark all the vertices as not visited
			visited = [False]*(len(self.graph))
 
			# Call the recursive helper function to print
			# DFS traversal
			self.DFSUtil(v,visited)
 
# Create a graph given in
# the above diagram
g = Graph()
for i in range (0, n):
	for j in range(i+1, n):
		k = random.randint(0,1)
		if (k == 1)
			g.addEdge(i, j)
 
print "The ordering starts from the first piece."
g.BFS(1)
g.DFS(1)
