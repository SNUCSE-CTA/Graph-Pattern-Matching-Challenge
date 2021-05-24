/**
 * @file backtrack.h
 *
 */

#ifndef BACKTRACK_H_
#define BACKTRACK_H_

#include "candidate_set.h"
#include "common.h"
#include "graph.h"

class Backtrack {
 public:
  Backtrack();
  ~Backtrack();


  Visited visited;

  void PrintAllMatches(const Graph &data, const Graph &query,
                       const CandidateSet &cs);

  void printEmbedding(const Embedding &embedding);

  void recursiveBacktrack(const Graph &data, const Graph &query,
                           const CandidateSet &cs, Embedding &embedding, Vertex qVertex);


  bool checkEdgeConnection(const Graph &graph, const Graph &query, const Embedding &embedding, Vertex dVertex,
                        Vertex qVertex);
};

#endif  // BACKTRACK_H_

