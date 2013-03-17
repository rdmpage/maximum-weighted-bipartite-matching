#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>

#include <GTL/GTL.h>
#include "mygraph.h"
#include "mwbmatching.h"

clock_t t0;
clock_t t1;

void ShowTimeUsed (clock_t &t0, clock_t &t1);
void Tokenise (std::string s, std::string delimiters, std::vector<std::string> &tokens);

// -------------------------------------------------------------------------------------------------
void ShowTimeUsed (clock_t &t0, clock_t &t1)
{
	cout << "CPU time used = " << (float)(t1 - t0)/(float)CLOCKS_PER_SEC << " seconds" << endl;
}

// -------------------------------------------------------------------------------------------------
void Tokenise (std::string s, std::string delimiters, std::vector<std::string> &tokens)
{
	tokens.erase (tokens.begin(), tokens.end());
	int start, stop;
	int n = s.length();
	start = s.find_first_not_of (delimiters);
	while ((start >= 0) && (start < n))
	{
		stop = s.find_first_of (delimiters, start);
		if ((stop < 0) || (stop > n)) stop = n;
		tokens.push_back (s.substr(start, stop - start));
		start = stop + delimiters.length();
	}
}

// -------------------------------------------------------------------------------------------------
int main (int argc, const char * argv[]) 
{
	if (argc < 2)
	{
		cout << "Usage: matching <file-name>" << endl;
		exit(1);
	}
	char filename[256];
	strcpy (filename, argv[1]);
	
  	// ---------------------------------------------------------	
  	// Read graph	

 	MyGraph G;
 	
 	G.read_labels_as_weights();
	
	t0 = clock();
	GML_error err  = G.load (filename);
	t1 = clock();
	if (err.err_num != GML_OK)
	{
		cerr << "Error (" << err.err_num << ") loading graph from file \"" << filename << "\"";
		switch (err.err_num)
		{
			case GML_FILE_NOT_FOUND: cerr << "A file with that name doesn't exist."; break;
			case GML_TOO_MANY_BRACKETS: cerr << "A mismatch of brackets was detected, i.e. there were too many closing brackets (])."; break;
			case GML_OPEN_BRACKET: cerr << "Now, there were too many opening brackets ([)";  break;
			case GML_TOO_MANY_DIGITS: cerr << "The number of digits a integer or floating point value can have is limited to 1024, this should be enough :-)";  break;
			case GML_PREMATURE_EOF: cerr << "An EOF occured, where it wasn't expected, e.g. while scanning a string."; break;
			case GML_SYNTAX: cerr << "The file isn't a valid GML file, e.g. a mismatch in the key-value pairs."; break;
			case GML_UNEXPECTED: cerr << "A character occured, where it makes no sense, e.g. non-numerical characters"; break;
			case GML_OK: break;
		}
		cerr << endl;
		exit(1);
	}
	else
	{
		//cout << "Graph read from file \"" << filename << "\" has " << G.number_of_nodes() << " nodes and " << G.number_of_edges() << " edges" << endl;
	}
	//ShowTimeUsed (t0, t1);
	
	edge_map<int> weights(G, 100);
	graph::edge_iterator eit = G.edges_begin();
	graph::edge_iterator eend = G.edges_end ();
	while (eit != eend)
	{
		weights[*eit] = G.get_edge_weight(*eit);
		eit++;
	}

	list<edge> L = MAX_WEIGHT_BIPARTITE_MATCHING(G,weights);
	
	// Create the matching and save it by hiding all edges in the original graph,
	// then restoring just those in the matching
	list <edge> edges;
	eit = G.edges_begin();
	eend = G.edges_end ();
	while (eit != eend)
	{
		edges.push_back (*eit);
		eit++;
	}
	
	list<edge>::iterator lit = edges.begin();
	list<edge>::iterator lend = edges.end();
	while (lit != lend)
	{
		G.hide_edge(*lit);
		lit++;
	}
	
	// The matching
	int numMatches = L.size();
	int *order = new int[numMatches];
		
	// JSON	
	// Output a list of the ordering of the second list versus the first
	cout << "{\n";
	cout << "\"matching\":[";
	
	list<edge>::iterator it = L.begin();
	while ( it != L.end() ) 
	{
		edge e = *it;
		G.restore_edge(e);
		
		node a = e.source();
		node b = e.target();
		
		order[b.id()] = a.id();	
		
		cout << "[" << b.id() << "," << a.id() << "]";
		
		it++;
		
		if (it != L.end())
		{
			cout << ",";
		}
		//cout << endl;
	}
	cout << "]\n";
	cout << "}\n";	
	
	if (0)
	{
		G.save("matching.gml");
	}
	
   return 0;
}
