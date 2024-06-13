
#include <gtest/gtest.h>
#include <memory>

#include "algorithm.hpp"
#include "graph.hpp"
#include "logger.hpp"
#include "parser.hpp"
#include "partitioner.hpp"


TEST(ReorderTests, ReorderSample1) {
  compress::GraphParser parser('#', '\t');
  compress::Graph sampleGraph1 = parser.parseFromFile("../graphs/sample_graph_2.txt");
  compress::CLILogger logger;
  compress::Reorderer reorder(std::make_unique<compress::RandomBiPartioner>(), logger); 

  auto ToVertexSet = [](const std::vector<compress::Vertex> vertexVector) {
    compress::VertexSet newVertexSet;

    for (auto& vertex : vertexVector)
      newVertexSet.insert(vertex);

    return newVertexSet;
  };

  compress::QDGraph constructed(ToVertexSet(sampleGraph1.vertices()), ToVertexSet(sampleGraph1.vertices()), sampleGraph1);
  compress::Order vertexOrder = reorder.reorder(constructed, 1, constructed.dataOrder());

  ASSERT_EQ(vertexOrder.size(), constructed.dataOrder());
}
