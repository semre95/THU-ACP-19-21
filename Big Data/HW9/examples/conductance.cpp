#include "core/graph.hpp"
#include <iostream>
#include <algorithm> 

int main(int argc, char ** argv) {
	if (argc<2) {
		fprintf(stderr, "usage: conductance [path] [memory budget in GB]\n");
		exit(-1);
	}
	std::string path = argv[1];
	long memory_bytes = (argc>=3)?atol(argv[2])*1024l*1024l*1024l:8l*1024l*1024l*1024l;

	Graph graph(path);
	graph.set_memory_bytes(memory_bytes);
	graph.set_vertex_data_bytes( graph.vertices * sizeof(VertexId) );

	double starting_time = get_time();
	int red_edges = graph.stream_edges<VertexId>([&](Edge & e){
		return e.source % 2;
	});

	int cross_over_edges = graph.stream_edges<VertexId>([&](Edge & e){
		return (e.source % 2) == (e.target % 2);
	});
	double ending_time = get_time();
	int black_edges = graph.edges - red_edges;

	printf("Results\n");
	printf("-----------------------\n");
	printf("Red Edges: %d\n", red_edges);
	printf("Other Edges(Black): %d\n", black_edges);
	printf("Crossover Edges: %d\n", cross_over_edges);
	printf("Conductance: %d\n", cross_over_edges / (std::min(red_edges,black_edges)));
	printf("Total time: %.2f seconds.\n", ending_time - starting_time);

	return 0;
}
