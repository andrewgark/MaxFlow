#ifndef _GRAPH
#define _GRAPH

#include <fstream>

using namespace std;

typedef int i32;
typedef long long i64;
typedef unsigned int ui32;
typedef unsigned long long ui64;

class Graph {
public:
    virtual ui32 getNumberVertices() = 0;
    virtual ui32 getDegree(ui32 vertex) = 0;
    virtual void read(istream &in) = 0;
};

#endif
