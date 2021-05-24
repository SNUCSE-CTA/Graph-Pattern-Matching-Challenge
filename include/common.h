/**
 * @file common.h
 * @brief common headers and type definitions
 *
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

using Vertex = int32_t;
using Label = int32_t;
using Embedding = std::vector<std::pair<Vertex, Vertex>>;
using Visited = std::vector<bool>;

#endif  // COMMON_H_
