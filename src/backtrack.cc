/**
 * @file backtrack.cc
 *
 */

#include "backtrack.h"
#include "stdio.h"
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

struct Node {
  int data;
  vector<int> next;
  vector<int> prev;

  Node(int i)
  {
    next.clear();
    prev.clear();
    data = i;
  }

  void AddNext(int add){
    next.push_back(add);
  }

  void AddPrev(int add){
    prev.push_back(add);
  }
};

Backtrack::Backtrack() {}
Backtrack::~Backtrack() {}

vector<Node> findDAG(const Graph &query,
                                const CandidateSet &cs){

  int num_vertices = query.GetNumVertices();

  vector<Node> NodeVec;
  Node *a;

  for (int i = 0; i < num_vertices; i++){
    a = new Node(i);

    for (int k = query.GetNeighborStartOffset(i); k < query.GetNeighborEndOffset(i); k++)
    {
      if(query.GetNeighbor(k) > i)
        a->AddNext(query.GetNeighbor(k));
      else{
        a->AddPrev(query.GetNeighbor(k));
      }
    }

    // sort(a->next.begin(), a->next.end());
    NodeVec.push_back(*a);
  }

  return NodeVec;
}

void Backtrack::PrintAllMatches(const Graph &data, const Graph &query,
                                const CandidateSet &cs) {
  std::cout << "t " << query.GetNumVertices() << "\n";
  // implement your code here.
  // DAG 구현
  int num_vertices = query.GetNumVertices();
  vector<Node> DAGvec = findDAG(query, cs);
  int cs_size;
  int tempsize;
  int tempsize2;

  vector<int> candidateArr[num_vertices];

  for (int i = 0; i < num_vertices; i++){
    cs_size = cs.GetCandidateSize(i);
    for (int j = 0; j < cs_size; j++){
      candidateArr[i].push_back(cs.GetCandidate(i, j));
    }
  }

  // 딱 한 번만 필터링 해봄.. 함수화 시킬 예정

  for (int i = 0; i < num_vertices; i++)
  {
    cs_size = candidateArr[i].size();
    tempsize = DAGvec[i].next.size();
    

    for (int j = 0; j < cs_size; j++)
    {
      int success = 0;
      int prev = candidateArr[i][j];

      if(tempsize == 0) // edge가 0인 경우 넘어 감
        break;

      for (int k = 0; k < tempsize; k++)
      {
        int temp = candidateArr[DAGvec[i].next[k]].size();

        for (int l = 0; l < temp; l++)
        {
          int next = candidateArr[DAGvec[i].next[k]][l];
          if (data.IsNeighbor(prev, next)){
            printf("%d %d\n", prev, next);
            success++;
            break;
          }
        }
      }
      if(success < tempsize){
        vector<int> v = candidateArr[i];
        printf("deleted %d\n", prev);
        v.erase(v.begin() + j);
      }
    }
  }
  
  /*
  printf("\nNEXT\n");
  for (int i = 0; i < num_vertices; i++){
    printf("%d: ", i);
    for (int j = 0; j < DAGvec[i].next.size(); j++)
    {
      printf("%d ", DAGvec[i].next[j]);
    }
    printf("\n");
  }
  */

  /*

  printf("\nPREV\n");
  for (int i = 0; i < num_vertices; i++){
    printf("%d: ", i);
    for (int j = 0; j < DAGvec[i].prev.size(); j++)
    {
      printf("%d ", DAGvec[i].prev[j]);
    }
    printf("\n");
  }
  */

}