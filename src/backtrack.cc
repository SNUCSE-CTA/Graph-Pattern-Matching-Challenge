/**
 * @file backtrack.cc
 *
 */

#include "backtrack.h"
#include <vector>
#include <cmath>
using namespace std;

static Vertex *print_buf;         //both print buffer and the record for currently visited data vertexs
static vector<Vertex> search_seq; //sequence to visit the query vertex

static char *is_visited;             //is a query vertex visited?
static char *is_visited_data;        //is a graph(data) vertex visited?

static int found_count; //success count. terminate when 10^5

std::vector<std::vector<double>> edge_weight;

Backtrack::Backtrack() {}
Backtrack::~Backtrack() {}

/* search ordering */
void search_order(const Graph &data, const Graph &query, CandidateSet &cs)
{
  Vertex curr;
  double max = 0;
  double neighbor_count = 0;
  int preprocess = 0;
  /* query vertex search ordering: 
  0.the first query vertex to be visited is the one with the least element in its candidate set.
  1. next query vertex to be visited will be the one who has the most many neighbor in the already-visited vertex group. 
  2. if there is a tie in the number of neighbor, then choose the one with the least element
  */
  /* time complexity: query V ^2 */
  for (int i = 0; i < query.GetNumVertices(); i++){
      if (cs.GetCandidateSize(i) == 1)
      {
        search_seq.push_back(i);
        is_visited[i] = 1;
        preprocess++;
      }
  }

  for (int i = 0; i < query.GetNumVertices(); i++){
      if (cs.GetCandidateSize(i) == 2)
      {
        search_seq.push_back(i);
        is_visited[i] = 1;
        preprocess++;
      }
  }

  for (int i = 0; i < query.GetNumVertices(); i++){
      if (cs.GetCandidateSize(i) == 3)
      {
        search_seq.push_back(i);
        is_visited[i] = 1;
        preprocess++;
      }
  }

  for (int iter = 0; iter < query.GetNumVertices()-preprocess; iter++)
  {
    curr = -1;
    for (Vertex i = 0; i < query.GetNumVertices(); i++)
    {
      /* do not visit the query vertex more than once */
      if (is_visited[i])
      {
        continue;
      }

      /* count the number of neighbor */
      for (auto elem = search_seq.begin(); elem != search_seq.end(); elem++)
      {
        if (query.IsNeighbor(*elem, i))
        {
          neighbor_count++;
        }
      }

      /* always tie in the first iteration, since neighbor_count, graph_size_count is zero */
      if (curr == -1)
      {
        curr = i;
      }

      /* 1. choose the one with the most neighbor with the currently visited.*/
      if (neighbor_count > max)
      {
        curr = i;
        max = neighbor_count;
      }

      /* tie in neighbor_count */
      else if (neighbor_count == max)
      {
        /* 2. if the neighbor count is tie, than choose the one with less candidate. */
        if (cs.GetCandidateSize(i) < cs.GetCandidateSize(curr))
        {
          curr = i;
        }
      }
    }

    neighbor_count = 0;
    max = 0;
    is_visited[curr] = 1;
    search_seq.push_back(curr);
  }
}

/* initialize the weight of each vertex */
void weight_init(const Graph &data, const Graph &query, CandidateSet &cs)
{
  for (Vertex i = 0; i < query.GetNumVertices(); i++)
  {
    for (int j = 0; j < cs.GetCandidateSize(i); j++)
    {
      edge_weight[i][j] = 0;
    }
  }
}

/* calculate the weight of each vertex */
void weight_calculate(const Graph &data, const Graph &query, CandidateSet &cs)
{

  /* initialize the weight as zero */
  edge_weight.resize(query.GetNumVertices());
  for (Vertex i = 0; i < query.GetNumVertices(); i++)
  {
    edge_weight[i].resize(cs.GetCandidateSize(i));
    for (int j = 0; j < cs.GetCandidateSize(i); j++)
    {
      edge_weight[i].push_back(0);
    }
  }

  /* candidate-set weight calculation*/
  /* time-complexity: query V^2 * candidate size^2 ~= query V^2 or E*/
  /* 2^0: 1 path 2^10: 1024 path, -1 = invalid */
  /* 각 availabe_edge_count는 현재 vertex와 child 사이에 존재하는 edge의 개수이다. */
  /* '경로의 수'를 구하기 위해서는 그들끼리 곱해야 한다. 하지만, 각각의 a_e_c를 구할 때는 나올 때 마다 더해야 한다. */

  Vertex set, child;               //set: the set to fill in the weight. child: those who will be traversed later compared with 'current set', according to the search_seq.
  int child_neighbor_count = 0;    // number of connected child sets
  int has_child_flag = 0;          //does this set have the child to be connected?
  double available_edge_count = 0; //the number of edge between the current vertex and the child set.

  for (int set_n = query.GetNumVertices() - 1; set_n >= 0; set_n--)
  {
    set = search_seq[set_n];
    for (int child_n = set_n + 1; child_n < query.GetNumVertices(); child_n++)
    {
      child = search_seq[child_n];
      if (query.IsNeighbor(set, child))
      {
        has_child_flag = 1;
        for (Vertex set_elem = 0; set_elem < cs.GetCandidateSize(set); set_elem++)
        {
          for (Vertex child_elem = 0; child_elem < cs.GetCandidateSize(child); child_elem++)
          {

            if (cs.GetCandidate(set, set_elem) == cs.GetCandidate(child, child_elem))
              continue;

            /* log((a+b)/2) ~= log(a)+log(b) /2  => log(a+b) ~= log(a) + log(b) /2 +1*/
            /* 로그 a 와 로그 b가 있을 때 로그(a+b)를 정확히 계산하기 어려우므로 그냥 log a + log b를 한 뒤 이를 나중에 처리해 준다. */
            if (data.IsNeighbor(cs.GetCandidate(set, set_elem), cs.GetCandidate(child, child_elem)))
            {
              if (edge_weight[child][child_elem] >= 0)
              {
                child_neighbor_count++;
                available_edge_count += edge_weight[child][child_elem];
              }
            }
          }

          /* no connection, while it is needed! */
          if (child_neighbor_count == 0)
          {
            edge_weight[set][set_elem] = -1;
          }
          /* 마찬가지 */
          else if (available_edge_count < 0)
          {
            edge_weight[set][set_elem] = -1;
          }
          /* 로그 a 와 로그 b가 있을 때 로그(a+b)를 정확히 계산하기 어려우므로 log a+logb를 한 값을 바탕으로 그냥 근사하는 계산 과정*/
          else
          {
            available_edge_count /= child_neighbor_count;
            available_edge_count += log2(child_neighbor_count);
            edge_weight[set][set_elem] += available_edge_count;
          }

          available_edge_count = 0;
          child_neighbor_count = 0;
        }
      }
    }
    /* 만약 서열이 낮은 set와의 연결이 없을경우, 경우의 수 = 1(=2^0)이라고 생각한다. (가장 말단에 있는 vertex들) */
    if (has_child_flag == 0)
    {
      for (Vertex set_elem = 0; set_elem < cs.GetCandidateSize(set); set_elem++)
      {
        edge_weight[set][set_elem] = 0;
      }
    }
    else
    {
      has_child_flag = 0;
    }
  }
}

/* sort the vertex according to its weight */
void weight_sort(const Graph &data, const Graph &query, CandidateSet &cs)
{
  /* find_max_sort */
  double max_weight = -999;
  Vertex tmp;
  for (int iter = 0; iter < query.GetNumVertices(); iter++)
  {
    for (int vert = 0; vert < cs.GetCandidateSize(iter); vert++)
    {
      max_weight = -999;
      for (int j = vert; j < cs.GetCandidateSize(iter); j++)
      {
        if (edge_weight[iter][j] > max_weight)
        {
          /* swap */
          max_weight = edge_weight[iter][j];
          edge_weight[iter][j] = edge_weight[iter][vert];
          edge_weight[iter][vert] = max_weight;

          //fprintf(stderr, "iter: %d, vert: %d, j: %d\n", iter, vert, j);
          tmp = cs.GetCandidate(iter, vert);
          cs.cs_[iter][vert] = cs.cs_[iter][j];
          cs.cs_[iter][j] = tmp;
        }
      }
    }
  }
}

/* backtrack */
void rec_Backtrack(const Graph &data, const Graph &query, CandidateSet &cs, int count)
{
  int success_flag = 1;
  Vertex set = search_seq[count];
  /* end of the search: print */
  if (count == query.GetNumVertices())
  {
    found_count++;
    cout << "a ";
    for (Vertex i = 0; i < count; i++)
    {
      cout << print_buf[i] << " ";
    }
    cout << endl;
    if (found_count == 100000)
    {
      exit(0);
    }
    return;
  }

  int max = -999;
  Vertex tmp;
  for (Vertex candidate = 0; candidate < cs.GetCandidateSize(set); candidate++)
  {

    if(edge_weight[search_seq[count]][candidate] < 0){
      return;
    }

    if (is_visited_data[cs.GetCandidate(set, candidate)] == 1)
    {
      /* already used vertex */
      continue;
    }

    for (int i = 0; i < count; i++)
    {
      /* check query connection for previous visited vertexes*/
      if (query.IsNeighbor(search_seq[i], set))
      {
        /* if they were connected on query, check if it is also connected in original graph */
        /* matched at query vertex no. i*/
        if (data.IsNeighbor(print_buf[search_seq[i]], cs.GetCandidate(set, candidate)))
        {
        }
        /* failed */
        else
        {
          success_flag = 0;
          break;
        }
      }
    }
    if (success_flag)
    {
      /* matched */
      print_buf[set] = cs.GetCandidate(set, candidate);
      is_visited_data[print_buf[set]] = 1;
      rec_Backtrack(data, query, cs, count + 1);

      /* delete the visited flag after return*/
      is_visited_data[print_buf[set]] = 0;
    }
    else
    {
      success_flag = 1;
    }
  }
  return;
}

void Backtrack::PrintAllMatches(const Graph &data, const Graph &query,
                                CandidateSet &cs)
{
  print_buf = new Vertex[query.GetNumVertices()];
  is_visited = new char[query.GetNumVertices()];
  is_visited_data = new char[data.GetNumVertices()];

  for (int i = 0; i < query.GetNumVertices(); i++)
  {
    is_visited[i] = 0;
  }

  for (int i = 0; i < data.GetNumVertices(); i++)
  {
    is_visited_data[i] = 0;
  }

  cout << "t " << query.GetNumVertices() << "\n";

  search_order(data, query, cs);

  weight_calculate(data, query, cs);

  weight_sort(data, query, cs);

  /* start the backtracking */
  rec_Backtrack(data, query, cs, 0);
}
