/**
 * @file backtrack.cc
 *
 */

#include "backtrack.h"



Backtrack::Backtrack() {}
Backtrack::~Backtrack() {}

void Backtrack::PrintAllMatches(const Graph &data, const Graph &query,
                                const CandidateSet &cs) {
  std::cout << "t " << query.GetNumVertices() << "\n";


  // implement your code here.
  Embedding embedding;

  visited.clear();
  visited.resize(data.GetNumVertices());
  std::fill(visited.begin(), visited.end(), false);

  recursiveBacktrack(data, query, cs, embedding, 0);

}


/*
 * PSEUDO CODE FOR BACKTRACKING
 * REFERENCE: Efficient Subgraph Matching:
 *            Harmonizing Dynamic Programming, Adaptive Matching Order, and Failing Set Together
 * Backtrack(q, q_D, CS, M)
 * if |M| = |V(q)| then
 *      Report M;
 * else if |M| = 0 then
 *      foreach v in C(r) do
 *      M <- {(r, v)};
 *      Mark v as visited;
 *      Backtrack(q, q_D, CS, M);
 *      Mark v as unvisited;
 * else
 *      u <- extentable vertex with min weight w_m(u);
 *      foreach v in C_M(u) do
 *          if v is unvisited then
 *              M' <- M \union {(u, v}};
 *              Mark v as visited;
 *              Backtrack(q, q_D, CS, M');
 *              Mark v as unvisited;
 * return
 */



// TODO: query.GetNumVertices, data.GetNumVertices to static variable


void Backtrack::recursiveBacktrack(const Graph &data, const Graph &query, const CandidateSet &cs,
                                   Embedding &embedding, Vertex qVertex) {

//    std::cout << "qVertex " << qVertex << std::endl;
    // conditional branch(1): if |M| = |V(q)|
    if (qVertex == query.GetNumVertices()) {
        // TODO : Validation
        printEmbedding(embedding);
        return;
    }

    // conditional branch(2) and (3)
    size_t numCandidates = cs.GetCandidateSize(qVertex); // C(r) : Number of candidates for root vertex


    for (size_t i = 0; i < numCandidates; i++){ // for each candidate v

        Vertex dVertex = cs.GetCandidate(qVertex, i);
//        std::cout << "dVertex " << dVertex << std::endl;
        // Injective Mapping Condition
        if (!visited.at(dVertex)) {
            if (checkEdgeConnection(data, query, embedding, dVertex, qVertex)) {
                embedding.push_back(std::make_pair(qVertex, dVertex));
                visited.at(dVertex) = true;
                recursiveBacktrack(data, query, cs, embedding, qVertex + 1);
                embedding.pop_back();
                visited.at(dVertex) = false;
            }
        }

    }

}



bool Backtrack::checkEdgeConnection(const Graph &data, const Graph &query, const Embedding &embedding, Vertex dVertex, Vertex qVertex) {

    bool edgeMatches = true;

    // for all vertices in advance of vertex(queryVertex)
    for (Embedding ::const_iterator iter = embedding.begin(); iter != embedding.end(); iter++) {
        if (!data.IsNeighbor(dVertex, iter->second) && query.IsNeighbor(qVertex, iter->first)) {
            edgeMatches = false;
            return edgeMatches;
        }
    }

    return edgeMatches;
}

void Backtrack::printEmbedding(const Embedding &embedding) {
    std::cout << "a";
    for (Embedding ::const_iterator iter = embedding.begin(); iter != embedding.end(); iter++) {
        std::cout << " " << iter->second;
    }
    std::cout << std::endl;
}



