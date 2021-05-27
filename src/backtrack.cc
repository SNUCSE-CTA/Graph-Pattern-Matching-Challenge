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

  //recursiveBacktrack(data, query, cs, embedding, 0);
  size_t queryVertexNum = query.GetNumVertices();

    std::vector<std::pair<double, Vertex>> rank;
  for (size_t i = 0; i < queryVertexNum; i++) {
    rank.push_back(std::make_pair(cs.GetCandidateSize(i) / (0.01 * queryVertexNum / data.GetNumLabels() + query.GetDegree(i)), i));
  }
    
  std::sort(rank.begin(), rank.end());

  std::vector<std::pair<Vertex, Vertex>> backStack; // Stack for backtracking. Storing pair of <qVertex, dVertexId>

  Vertex qVertexId = 0;
  Vertex dVertex = 0;

  int total = 0;

  for (size_t i = 0; i < cs.GetCandidateSize(rank.at(qVertexId).second); i++){ // for each candidate v
            dVertex = cs.GetCandidate(rank.at(qVertexId).second, i);
            backStack.push_back(std::make_pair(qVertexId, dVertex));
  }


  while(!backStack.empty()) {
    qVertexId = backStack.back().first;
     // std::cout << qVertexId << " ";
    dVertex = backStack.back().second;
    embedding.push_back(std::make_pair(rank.at(qVertexId).second, dVertex));
    // std::cout << "qVertex " << qVertex << std::endl;
    // conditional branch(1): if |M| = |V(q)|
    if (qVertexId == queryVertexNum - 1) {
        // TODO : Validation
        printEmbedding(embedding);
        backStack.pop_back();
        embedding.pop_back();
        total ++;

        while (backStack.back().first < qVertexId) {
            qVertexId = backStack.back().first;
            visited.at(backStack.back().second) = false;
            embedding.pop_back();
            backStack.pop_back();
        }

    }
    else {
        visited.at(dVertex) = true;
        // conditional branch(2) and (3)
        size_t numCandidates = cs.GetCandidateSize(rank.at(qVertexId + 1).second); // C(r) : Number of candidates for root vertex

        for (size_t i = 0; i < numCandidates; i++){ // for each candidate v
            dVertex = cs.GetCandidate(rank.at(qVertexId + 1).second, i);

            // Injective Mapping Condition
            if (!visited.at(dVertex)) {
                if (checkEdgeConnection(data, query, embedding, dVertex, rank.at(qVertexId + 1).second)) {
                    backStack.push_back(std::make_pair(qVertexId + 1, dVertex));
                }
            }
        }


        // Dead end, none pushed to stack
        if (qVertexId == backStack.back().first) {
            visited.at(backStack.back().second) = false;
            backStack.pop_back();
            embedding.pop_back();

            while (backStack.back().first < qVertexId) {
                qVertexId = backStack.back().first;
                visited.at(backStack.back().second) = false;
                embedding.pop_back();
                backStack.pop_back();
            }

        }

    }
  }
    std::cout << " " << total << " ";
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

    //std::cout << "qVertex " << qVertex << std::endl;
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
        //std::cout << "dVertex " << dVertex << std::endl;
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


