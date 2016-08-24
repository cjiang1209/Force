#include <iostream>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <utility>

#include "HyperGraph.h"
#include "HyperGraphReader.h"
#include "Force.h"

using namespace std;

double get_cpu_time()
{
	rusage ru;
	getrusage(RUSAGE_SELF, &ru);
	return static_cast<double>(ru.ru_utime.tv_sec) + static_cast<double>(ru.ru_utime.tv_usec) / 1e6;
}

int main(int argc, char* argv[])
{
	HyperGraphReader gr;
	HyperGraph graph = gr.build_graph(argv[1]);

	double start = get_cpu_time();

	Force force(graph);
	vector<int> order = force.execute();

	double end = get_cpu_time();

	for (const auto& var : order) {
		cout << var << " ";
	}
	cout << endl;

	cout << "Completed" << endl;
	cout << "Time: " << end - start << " s" << endl;

	return 0;
}
