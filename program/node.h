#ifndef NODE
#define NODE

// 定义顶点数组/表节点
#define MAX_SIZE 100
typedef struct{
    char data;//顶点data类型, data
    Edge* firstEdge;//第一个邻接点
} Vertex, VertexArray[MAX_SIZE];

typedef struct {
    //边表节点
    int adjvex;//边表节点在顶点表中下表 
    Edge* next;// 下个邻接点指针
    int weight;//权重
} Edge;

#endif