#ifndef _EDGE
#define _EDGE

using namespace std;

typedef int i32;
typedef long long i64;
typedef unsigned int ui32;
typedef unsigned long long ui64;

class Edge {
public:
    virtual ui32 getBegin() = 0;
    virtual ui32 getEnd() = 0;
};

#endif
