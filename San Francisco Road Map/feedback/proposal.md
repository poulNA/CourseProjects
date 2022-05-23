### Regrade

Not Yet Competent (70%)

Please select a specific SCC algorithm as well as explain how you would apply it on the road network. Are the edges in road network dataset undirected or directed? If undirected, then SCC reduces to disjoint set, which is invalid as a **uncovered** graph algorithm (so we need to pick a different algorithm/problem). If directed, could you explain how to interpret directed roads?

### Grade

Incomplete (0%)

Must resubmit with leading question and uncovered graph algorithm!

### Checklist

This checklist is extracted from the [grading rubric](https://docs.google.com/spreadsheets/d/18y-mFuQ1Y1oMzlyGbYXx878J810Uu_ZWdZLiNiQxVgU/edit#gid=0). Please visit the sheet to see more detailed explanation.

Leading question
- [ ] Question or expected result
- [ ] How the dataset and algorithms will answer this

Dataset
- [x] Data format (Nodes, Edges, PoI with OCN, PoI)
- [x] Acquire (utah spatial dataset)
- [ ] How to process and store the data
- [x] Data correction for potential errors (negative lat/lon, validate ID, node ID positive)

Algorithm
- [x] One graph traversal (BFS)
  - [ ] Input and output
  - [x] Run-time efficiency
- [x] One algorithm in class (Dijkstra's)
  - [ ] Input and output
  - [x] Run-time efficiency
- [ ] One algorithm not in class
  - [ ] Input and output
  - [ ] Run-time efficiency

Timeline
- [x] Reasonable date on every major benchmark.

### Comments

One of two primary issues is that the lack of details about **leading question**. The "Aim" section only mentions a general seach tool which connects the proposed algorithms (SSSP, traversal for searching, SCC). What is the use case for our "general search tool"? What is the leading question/problem we are trying to solve?

Another one is that we miss another uncovered graph algorithm (or equivalent). Please take a look at this [list of examples](https://docs.google.com/document/d/10VL05FxUCQZMLb_jQfsfOMNR56ecxy0aIaqPH6KumBQ/edit) and select one more graph algorithm.
- The earlier part of proposal mentions strongly connected components (SCC) but the algorithm section hasn't explained it. If you do choose SCC, don't forget to choose a specific algorithm. Also, justify the selection with relation to the leading question.

Good job on the **dataset** survey. The descriptions are concise and to the point, but might need a bit more interpretation (how it can answer to the leading question). Two areas to improve are describing 1) how we would process and store the data? and 2) data correction might need to be amended. I'd recommend actually inspecting the dataset to discover any unexpected feature.

A few comments on the **algorithm** section:
- Dijkstra's with O(|E| + |V| log |V|) requires an advanced data structure (Fibonacci heap) which can be tricky to implement. I recommend writing a simpler version O((|E| + |V|) log |V|) with binary heap for initial version while aimming for the optimal version as an optional extension.

Please take a look at the checklist above for other missing details as well. Feel free to contact me if you have any further question or need clarification. Keep up the great work!