maximum-weighted-bipartite-matching
===================================

C++ program to compute the maximum weighted bipartite matching of a graph

#### Overview
This is a C++ program to compute the [maximum weighted bipartite matching](http://en.wikipedia.org/wiki/Matching_%28graph_theory%29#Maximum_matchings_in_bipartite_graphs) of a graph. The input graph must be a directed graph in [GML format](http://en.wikipedia.org/wiki/Graph_Modelling_Language), with the edges labelled by their weight. The program partitions the graph into source and target nodes, then computes the maximum weighted bipartite matching. The matching is output in JSON format, with each match represented as a pair of integers corresponding to the order of the nodes in the input file.

#### Dependencies
The program uses the Graph Template Library (GTL) which is available from [http://www.fim.uni-passau.de/fileadmin/files/lehrstuhl/brandenburg/projekte/gtl/GTL-1.2.4-lgpl.tar.gz](http://www.fim.uni-passau.de/fileadmin/files/lehrstuhl/brandenburg/projekte/gtl/GTL-1.2.4-lgpl.tar.gz)

#### Building
If you are building from this repository you will need to do the standard things:

* aclocal
* autoconf
* automake
* ./configure
* make

If you get errors about missing files, such as COPYING, you will need to do the following:

* automake —add-missing

#### Notes on building on a Mac
If you are building on a clean, new Mac (e.g., macOS Sierra) you may need to install the install some missing GNU tools, see [Install Autoconf and Automake on OS X El Capitan](https://gist.github.com/justinbellamy/2672db1c78f024f2d4fe). I also had to run
```
autoreconf -i
```
To get past the error **possibly undefined macro: AM_INIT_AUTOMAKE**

#### Example

The examples folder contains a bipartite graph:

![Example](https://github.com/rdmpage/maximum-weighted-bipartite-matching/raw/master/examples/bipartite.png)

Running the program on this graph

* matching examples/bipartite.gml

outputs the matching in JSON. The source nodes in the graph are numbered 0 - m, the target nodes m+1 - n.

```javascript
{
"matching":[[1,4],[0,5],[2,6],[3,8]]
}
```
