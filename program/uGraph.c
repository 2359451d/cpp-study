#include<stdio.h>
#include<stdlib.h>
#include"node.h"
#include"uGraph.h"

typedef int Boolean;
#define TRUE 1
#define FALSE 0

Boolean visited[100];

void create(uGraph* graph);

int main(int argc, char const *argv[])
{
    // 无向图邻接表
    uGraph* g = (uGraph*) malloc(sizeof(uGraph));
    create(g);//创建无向图

    return 0;
}

void bfs(uGraph* graph, int i ){
    Edge* p;//遍历用节点
    int queue[MAX_SIZE];
    int front=0, rear=0;//front, rear用于手动计算队列index
    int j;
    visited[i] = 1;//访问起始点

    rear =(rear+1)%MAX_SIZE;//队列尾插index, 设置sentinel
    queue[rear] = i;//起始点入队尾
    // 队列始终有元素时
    while(front!=rear){
        front = (front+1)%MAX_SIZE;//手动计算front, 队头索引
        j = queue[front];//每次取出队头元素
        // 访问该元素的邻接点[边表节点]
        p = graph->vArray[j].firstEdge;
        while(p!=NULL){
            if (!visited[p->adjvex])//当前顶点的边表节点未被访问过
            {
                visited[p->adjvex] = TRUE;//访问它
                // printf("%d")
                // 入队
                rear = (rear+1) % MAX_SIZE
                queue[rear] = p->adjvex;
            }
            // 移动指针，继续访问边表节点
            p = p->next;
        }
    }


}

void dfs(const uGraph* graph, int start){
    Edge* p;
    //当前访问过的点标记
    visited[start] = TRUE;

    //访问其边表
    p = graph->vArray[start].firstEdge;
    while(p)
    {
        if (!visited[p->adjvex])
        {
            dfs(graph, p->adjvex);
        }
        p  = p->next;
    }
}

void traverse(uGraph* graph){
    int i;
    for (i = 0; i < graph->verNum; i++)
    {
        visited[i]=FALSE;
    }
    for (i=0;i<graph->edgeNum;i++)
    {
        if (!visited[i])
            dfs(graph, i);
    }
}

void create(uGraph* graph){
    int x,y;// edge number
    scanf("%d %d", &graph->verNum, &graph->edgeNum);
    // 初始化顶点数组
    for (int i = 0; i < graph->verNum; i++)
    {
        scanf("%d", &graph->vArray[i].data);
        //每个顶点的边表初始化为null
        graph->vArray[i].firstEdge = NULL;
    }

    //建立边表
    for (int k = 0; k < graph->edgeNum; k++)
    {
        scanf("%d %d", &x, &y);
        Edge* eNode = (Edge*) malloc(sizeof(Edge));

        eNode->adjvex = y;
        eNode->next = graph->vArray[x].firstEdge;
        graph->vArray[x].firstEdge = eNode;

        // 无向图: 重复建立
        eNode = (Edge*) malloc(sizeof(Edge));
        eNode->adjvex =x;
        eNode->next = graph->vArray[y].firstEdge;
        graph->vArray[y].firstEdge = eNode;
    }
}