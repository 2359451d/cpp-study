#ifndef _uGraph_H
#define _UGraph_H

#include "node.h"

typedef struct {
    // 无向图邻接表
    VertexArray vArray;
    int verNum, edgeNum;
} uGraph;

#endif