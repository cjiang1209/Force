#include "HyperGraphReader.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

HyperGraph HyperGraphReader::build_graph(const char* file_name)
{
	ifstream in(file_name, ifstream::in);
	if (!in.is_open()) {
		cerr << "Cannot open file: " << file_name << endl;
		exit(0);
	}

	vector<vector<int>> edges;
	size_t num_vertices = 0;
	string line;
	while (getline(in, line)) {
		stringstream ss(line);
		vector<int> edge;
		int vertice;
		while (!ss.eof()) {
			ss >> vertice;
			edge.push_back(vertice);
			if (num_vertices < vertice + 1) {
				num_vertices = vertice + 1;
			}
		}
		edges.push_back(edge);
	}

	HyperGraph graph(num_vertices);
	for (const auto& e : edges) {
		HyperEdge& edge = graph.create_edge();
		for (const auto& vertice : e) {
			edge.add_vertex(vertice);
		}
	}

	return graph;
}
