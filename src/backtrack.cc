/**
 * @file backtrack.cc
 *
 */

#include "backtrack.h"
#include <stdio.h>
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

vector<Node> findDAG(const Graph &query, const CandidateSet &cs){
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
  int deletedcnt = 0;

  vector<int> candidateArr[num_vertices];

  for (int i = 0; i < num_vertices; i++){
    cs_size = cs.GetCandidateSize(i);
    for (int j = 0; j < cs_size; j++){
      candidateArr[i].push_back(cs.GetCandidate(i, j));
    }
  }

  /*
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
            //printf("%d %d\n", prev, next);
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
  */

  
  // t edge
  int cnt = 0;
  int take[num_vertices];
  int maxindex[num_vertices];
  int index[num_vertices] = {
      0,
  };

  bool failure = false;

  for(int i = 0; i < num_vertices; i++){
    maxindex[i] = candidateArr[i].size()-1;
  }

  bool end = true;
  bool add = false;
  int point = 1;

  while (true)
  {
    failure = false;
    end = false;
    add = false;
  
    for (int i = 0; i < num_vertices; i++){
      if(index[i] != maxindex[i]){
        break;
      }
      if(i == num_vertices-1){
        end = true;
      }
    }

    if(end == true)
      break;
      
    for (int i = 0; i < point; i++)
    {
      if (index[i] < maxindex[i])
      {
        index[i]++;
        add = true;
        break;
      }
      else if (index[i] == maxindex[i])
      {
        index[i] = 0;
      }
    }

    if(add == false){
      while(point < num_vertices){
        if(index[point] < maxindex[point]){
          index[point]++;
          point++;
          break;
        }
        else{
          point++;
        }
      }
      if(point == num_vertices)
        break;
    }
  /*
    for (int i = 0; i < num_vertices; i++){
        printf("%d ", index[i]);
      }
    printf("\n");
*/
    
    int temp;
    for (int i = 0; i < num_vertices; i++)
    {
      tempsize = DAGvec[i].next.size();
      for (int j = 0; j < tempsize; j++){
        temp = DAGvec[i].next[j];
        if (!data.IsNeighbor(candidateArr[i][index[i]], candidateArr[temp][index[temp]]))
        {
          failure = true;
          //printf("%d %d\n", candidateArr[i][index[i]], candidateArr[temp][index[temp]]);
          break;
        }
      }
      if(failure == true){
        break;
      }
    }

    if(failure == false){
      for (int i = 0; i < num_vertices; i++){
        printf("%d ", candidateArr[i][index[i]]);
      }
      printf("\n");
    }
  }

  /*

  while(cnt < 10){
    bool visited[num_vertices];
    int take[num_vertices];
    int index[num_vertices] = {0, };

    // 가져간 index들은 -1로, visited는 false로 초기화
    for (int i = 0; i < num_vertices; i++){
      visited[i] = false;
      take[i] = -1;
    }

    int target = 0;
    bool done = true;
    bool change = false;
    bool choose = false;
    
    printf("start matching\n");

    while (true)
    {
      done = true;
      choose = false;
      // target에 대한 처리와 take 변경
      printf("target: %d\n", target);
      int length = DAGvec[target].prev.size();
      int length_ = candidateArr[target].size();

      printf("length: %d, length_: %d\n", length, length_);
      int number;
      if (length == 0)
        choose = true; // 흠..
      
      for (int j = 0; j < length_; j++)
      {
        number = candidateArr[target][j];
        for (int i = 0; i < length; i++)
        {
          if(take[DAGvec[target].prev[i]] == -1)
            break;
          if (!data.IsNeighbor(take[DAGvec[target].prev[i]], number))
          {
            break;
          }
          if(i == length - 1){
            choose = true;
          }
        }
        if(choose == true)
          break;
      }

      visited[target] = true;
      take[target] = number;
      change = false;
      for (int i = 0; i < num_vertices; i++)
      {
        if(visited[i] == false){
          done = false;
          break;
        }
      }

      if(done == true) break;
      while(change == false)
      {
        cs_size = candidateArr[target].size();
        tempsize = DAGvec[target].next.size();

        for (int j = 0; j < cs_size; j++)
        {
          int success = 0;
          if(tempsize == 0) // edge가 0인 경우 넘어 감
            break;

          for (int k = 0; k < tempsize; k++){
            int next = DAGvec[target].next[k];
            if (visited[next] == false){
              target = next;
              change = true;
              break;
            }
          }
          if(change == true)
            break;
        }

        if(change == false){
          if(target == num_vertices-1)
            target = 0;
          for (int i = target + 1; i < num_vertices; i++)
          {
            if(visited[i] == true){
              target = i;
              change = true;
              break;
            }
          }
        }

        if(change == false){
          printf("no way\n");
          break;
        }
      }

      if(change == false){
        break;
      }
    }

    for (int i = 0; i < num_vertices; i++)
      {
        printf("%d ", take[i]);
      }
      printf("\n");
  }

  cnt++;
  */
}