#define TOLERANCE 0.01

#include "core/graph.hpp"

int main(int argc, char ** argv) {
	if (argc<3) {
		fprintf(stderr, "usage: pagerank [path] [iterations] [memory budget in GB]\n");
		exit(-1);
	}
	std::string path = argv[1];
	int iterations = atoi(argv[2]);
	long memory_bytes = (argc>=4)?atol(argv[3])*1024l*1024l*1024l:8l*1024l*1024l*1024l;

	Graph graph(path);
	graph.set_memory_bytes(memory_bytes);
	BigVector<VertexId> degree(graph.path+"/degree", graph.vertices);
	BigVector<float> pagerank(graph.path+"/pagerank", graph.vertices);
	BigVector<float> delta(graph.path+"/delta", graph.vertices);
	BigVector<float> sum(graph.path+"/sum", graph.vertices);
	BigVector<int> updates(graph.path+"/updated_values", graph.vertices);

	long vertex_data_bytes = (long)graph.vertices * ( sizeof(VertexId) + sizeof(float) + sizeof(float) );
	graph.set_vertex_data_bytes(vertex_data_bytes);

	double starting_time = get_time();

	updates.fill(0);
	pagerank.fill(0.15);
	delta.fill(1.0);

	degree.fill(0);
	graph.stream_edges<VertexId>(
		[&](Edge & e){
			write_add(&degree[e.source], 1);
			return 0;
		}, nullptr, 0, 0
	);
	printf("degree calculation used %.2f seconds\n", get_time() - starting_time);
	fflush(stdout);

	for (int iter=0;iter<iterations;iter++) {
		graph.hint(delta);
		graph.stream_edges<VertexId>(
			[&](Edge & e){
				float out = delta[e.source] / degree[e.source];
				if (out > TOLERANCE) {
					write_add(&sum[e.target], out);
					write_add(&updates[e.source], 1);
					if (updates[e.source] == degree[e.source]) {
						write_add(&pagerank[e.source], delta[e.source]);
						delta[e.source] = 0.0;
						updates[e.source] = 0;
					}
				}
				return 0;
			}, nullptr, 0, 1,
			[&](std::pair<VertexId,VertexId> source_vid_range){
				delta.lock(source_vid_range.first, source_vid_range.second);
			},
			[&](std::pair<VertexId,VertexId> source_vid_range){
				delta.unlock(source_vid_range.first, source_vid_range.second);
			}
		);

		graph.hint(delta, sum);
		graph.stream_vertices<VertexId>(
			[&](VertexId i){
				delta[i] = 0.85 * sum[i];
				sum[i] = 0;
				return 0;
			}, nullptr, 0,
			[&](std::pair<VertexId,VertexId> vid_range){
				delta.load(vid_range.first, vid_range.second);
				sum.load(vid_range.first, vid_range.second);
			},
			[&](std::pair<VertexId,VertexId> vid_range){
				delta.save();
				sum.save();
			}
		);
	}

	graph.stream_vertices<float>(
		[&](VertexId i){
			if (i < 10)
				printf("%d \t %f\n", i, pagerank[i]);
			return 0;
		}
	);
	printf("---------------------------\n");
	printf("Result: ");
	printf("%d PageRank Iterations ->  %.2f seconds\n", iterations, get_time() - starting_time);

}
