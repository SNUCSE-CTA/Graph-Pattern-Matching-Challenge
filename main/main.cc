/**
 * @file main.cc
 *
 */

#include "backtrack.h"
#include "candidate_set.h"
#include "common.h"
#include "graph.h"
#include <time.h>
int main(int argc, char* argv[]) {
    clock_t tStart = clock();
  if (argc < 4) {
    std::cerr << "Usage: ./program <data graph file> <query graph file> "
                 "<candidate set file>\n";
    return EXIT_FAILURE;
  }

  std::string data_file_name = argv[1];
  std::string query_file_name = argv[2];
  std::string candidate_set_file_name = argv[3];

  Graph data(data_file_name);
  Graph query(query_file_name, true);
  CandidateSet candidate_set(candidate_set_file_name);

  Backtrack backtrack;

  backtrack.PrintAllMatches(data, query, candidate_set);
    
        /* Do your stuff here */
        printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
  return EXIT_SUCCESS;
}
