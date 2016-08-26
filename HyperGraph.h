#ifndef _HYPERGRAPH_HEADER
#define _HYPERGRAPH_HEADER

#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

class HyperEdge
{
private:
	vector<int> _vertices;

public:
	typedef vector<int>::iterator iterator;
	typedef vector<int>::const_iterator const_iterator;

	HyperEdge()
	{
	}

	void add_vertex(int vertex)
	{
		_vertices.push_back(vertex);
	}

	size_t size() const
	{
		return _vertices.size();
	}

	iterator begin()
	{
		return _vertices.begin();
	}

	iterator end()
	{
		return _vertices.end();
	}

	const_iterator begin() const
	{
		return _vertices.begin();
	}

	const_iterator end() const
	{
		return _vertices.end();
	}

	int operator[](int index) const
	{
		assert(index >= 0 && index < _vertices.size());
		return _vertices[index];
	}

	friend ostream& operator<<(ostream& out, const HyperEdge& edge)
	{
		for (const auto& vertice : edge) {
			out << vertice << " ";
		}
		out << endl;
		return out;
	}
};

class HyperGraph
{
private:
	size_t _num_vertices;
	vector<HyperEdge> _edges;

public:
	HyperGraph(size_t num_vertices)
		: _num_vertices(num_vertices)
	{
	}

	size_t num_vertices() const
	{
		return _num_vertices;
	}

	HyperEdge& create_edge()
	{
		_edges.push_back(HyperEdge());
		return _edges.back();
	}

	const vector<HyperEdge>& edges() const
	{
		return _edges;
	}

	friend ostream& operator<<(ostream& out, const HyperGraph& graph)
	{
		out << "Edges: " << graph.edges().size() << endl;
		const vector<HyperEdge>& edges = graph.edges();
		for (const auto& edge : edges) {
			out << edge;
		}
		return out;
	}
};

#endif
