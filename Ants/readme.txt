Readme!

We had some local competition like the GoogleAIChallenge one, the ants competition.
It's an entry in the contest, it's written in Java and basically the algorithm
works like this:

- the map is organized grid like
- in order to find the food it's used a BFS from each cell of the grid, the 
BFS stops when it finds the first available ant
- for exploration is used also BFS for the periferic cells
- the grid tiles have different values, the values are influenced by the "thing"
that resides in that grid tile, for example an inamic ant will give the tile a
higher score than food.