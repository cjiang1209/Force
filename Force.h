#ifndef _FORCE_HEADER
#define _FORCE_HEADER

#include "HyperGraph.h"

class Force
{
private:
	struct VarInfo
	{
		// Sum of centers of gravity
		double sum_cog;
		int num_occurs;
	};

	template<typename T>
	struct LessThan
	{
		const std::vector<T> _weights;

		LessThan(const std::vector<T> weights)
			: _weights(weights)
		{
		}

		bool operator()(int x, int y) const
		{
			return _weights[x] < _weights[y];
		}
	};

	static void construct_lookup(vector<int>& lookup, const vector<int>& source);

	const HyperGraph& _graph;

	long compute_sum_of_spans(const vector<int>& idx_of_var) const;

public:
	Force(const HyperGraph& graph);
	vector<int> execute() const;
};

#endif
