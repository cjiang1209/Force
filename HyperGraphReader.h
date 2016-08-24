#ifndef _GRAPHREADER_HEADER
#define _GRAPHREADER_HEADER

#include "HyperGraph.h"

class HyperGraphReader
{
public:
	HyperGraph build_graph(const char* file_name);
};

#endif
