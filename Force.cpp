#include <algorithm>
#include <climits>
#include <cassert>
#include <iostream>

#include "Force.h"

Force::Force(const HyperGraph& graph)
	: _graph(graph)
{
}

/**
 * Return a lookup array of the given array.
 * For example, the source array = { [0 : 1], [1 : 2], [2 : 0] } ([index : value]).
 * Then the lookup array = { [0 : 2], [1 : 0], [2 : 1] }.
 */
void Force::construct_lookup(vector<int>& lookup, const vector<int>& source)
{
	assert(lookup.size() == source.size());
	size_t size = source.size();
	for (size_t i = 0; i < size; i++) {
		lookup[source[i]] = i;
	}
}

long Force::compute_sum_of_spans(const vector<int>& idx_of_var) const
{
	long sum_spans = 0;
	const vector<HyperEdge>& edges = _graph.edges();
	for (const auto& edge : edges) {
		assert(edge.size() > 0);

		int bottom = INT_MAX;
		int top = INT_MIN;
		for (const auto& var : edge) {
			int idx = idx_of_var[var];
			if (bottom > idx) {
				bottom = idx;
			}
			if (top < idx) {
				top = idx;
			}
		}
		sum_spans += (top - bottom);
	}
	return sum_spans;
}

vector<int> Force::execute() const
{
	size_t num_vars = _graph.num_vertices();

    vector<int> idx_of_var;
    idx_of_var.reserve(num_vars);
    vector<int> var_of_idx;
    var_of_idx.reserve(num_vars);
    for (int i = 0; i < num_vars; i++) {
    	idx_of_var.push_back(i);
    	var_of_idx.push_back(i);
    }

    // Random initial order
    std::shuffle(var_of_idx.begin(), var_of_idx.end(), default_random_engine());
    construct_lookup(idx_of_var, var_of_idx);

    long best_sum_spans = compute_sum_of_spans(idx_of_var);
    vector<int> best_order(var_of_idx);

    vector<VarInfo> infos;
    int num = 5 * std::log(num_vars);
    for (int i = 0; i < num; i++) {
    	infos.assign(num_vars, { 0.0, 0 });

    	const vector<HyperEdge>& edges = _graph.edges();
    	for (const auto& edge : edges) {
    		assert(edge.size() > 0);

    		int sum = 0;
    		for (const auto& var : edge) {
    			sum += idx_of_var[var];
    		}
    		double cog_of_edge = (double) sum / edge.size();
    		for (const auto& var : edge) {
    			VarInfo& vi = infos[var];
    			vi.sum_cog += cog_of_edge;
    			vi.num_occurs++;
    		}
    	}

    	// Average center of gravity
    	vector<double> cog_of_var;
    	cog_of_var.reserve(num_vars);
    	for (size_t j = 0; j < num_vars; j++) {
    		VarInfo& vi = infos[j];
    		cog_of_var.push_back(vi.num_occurs == 0 ? 0.0 : vi.sum_cog / vi.num_occurs);
    	}

    	std::sort(var_of_idx.begin(), var_of_idx.end(), LessThan<double>(cog_of_var));
    	construct_lookup(idx_of_var, var_of_idx);

    	long sum_spans = compute_sum_of_spans(idx_of_var);
    	cout << sum_spans << endl;
    	if (sum_spans < best_sum_spans) {
    		best_sum_spans = sum_spans;
    		best_order.assign(var_of_idx.begin(), var_of_idx.end());
    	}
    }

    return best_order;
}
