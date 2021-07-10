# Graph Pattern Matching Challenge
***You may use basic pruning techniques, but since the challenge aims to find a good matching order, you are not expected to use complicated pruning techniques (like Failing Set of DAF).***
## Compile and Execute 
### main program
```
mkdir build
cd build
cmake ..
make
./main/program <data graph file> <query graph file> <candidate set file>
```
### executable program that outputs a candidate set
```
./executable/filter_vertices <data graph file> <query graph file>
```

## Challenge winnners
|  | Members | Repository |
| :---: | :---: | :---: |
| Gold | 구\*호, 이\*진 | https://github.com/ialy1595/Graph-Pattern-Matching-Challenge |
| Silver | 설\*환, 김\*형 | https://github.com/JinhwanSul/Graph-Pattern-Matching-Challenge |
| Bronze | 이\*원, 박\*근 | https://github.com/tonypark7277/Graph-Pattern-Matching-Challenge |
| Bronze | 박\*현, 이\*훈 | https://github.com/dlwl0088/PMC21 |

### References
[1] Myoungji Han, Hyunjoon Kim, Geonmo Gu, Kunsoo Park, and Wook-Shin Han. 2019. Efficient Subgraph Matching: Harmonizing Dynamic Programming, Adaptive Matching Order, and Failing Set Together. In Proceedings of the 2019 International Conference on Management of Data (SIGMOD '19). Association for Computing Machinery, New York, NY, USA, 1429–1446. DOI:https://doi.org/10.1145/3299869.3319880
