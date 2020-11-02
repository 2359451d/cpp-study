// 邻接多重表表示
#define MAX_SIZE 100

typedef struct Node;

typedef struct Vertex{
    int data;
    Node* firstEdge;
}Vertex, VertexArray[MAX_SIZE];

typedef struct Node{
    int iVex;
    Node* iNext;
    int vVex;
    Node* vNext;
    // int weight;
}Node;

typedef struct Graph{
    // 顶点表
    Vertex vertexArray[MAX_SIZE];
    // VertexArray verArray;
    int verNum, edgeNum;
}Graph;