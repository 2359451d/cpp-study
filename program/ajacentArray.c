/* 
    邻接矩阵存储图
 */
#include<stdio.h>

#define MAX_SIZE 100
#define INFINITY 65535

typedef char Vertex;

typedef struct Graph {
    Vertex vertexArray[MAX_SIZE];//一维顶点数组
    int edges[MAX_SIZE][MAX_SIZE];//二维边数组
    int edgeNum, vexNum;
}Graph;

void createGraph(Graph* graph);

//example from video
void prim1(Graph* graph, int start){
    int lowcost[graph->vexNum], vSet[graph->vexNum];// vSet: 加入生成树的顶点
    int v, k, min;
    int sum;//最小花费
    for (int i = 0; i < graph->vexNum; i++)
    {
        lowcost[i] = graph->edges[start][i];//记录start邻接的所有点的权重
        vSet[i] = 0;//设置所有点未访问过
    }
    v = start;
    vSet[v] = 1;//设置起点start已访问
    sum=0;

    for (int i = 0; i < graph->vexNum; i++)
    {
        min = INFINITY;
        for (int j = 0; j < graph->vexNum; i++)
        {
            if (vSet[j]!=1 && lowcost[j]<min)
            {
                min = lowcost[j];
                k = j;
            }
        }
        vSet[k] = 1;//k点加入生成树，已访问
        sum +=min;
        for (int j = 0; j < graph->vexNum; j++)
        {
            if (vSet[j]!=1 && graph->edges[k][j] < lowcost[j])
                lowcost[j] = graph->edges[k][j];
        }
        
    }
    

    
}

//example
void prim(Graph* graph, int start){
    int lowcost[MAX_SIZE], adjvex[MAX_SIZE];//所有顶点权重, 与下标编号顶点邻接的边
    int k,min=INFINITY;

    int sum;//最小代价
    for (int i=0; i<graph->vexNum; i++)
    {
        lowcost[i] = graph->edges[start][i];//存入与start邻接的所有边权重
        adjvex[i] = start;
    }
    lowcost[start]=0;// start起点加入生成树
    adjvex[start]=start; //表示start,start权重为0

    for (int i = 0; i < graph->vexNum; i++)
    {
        // 查找最小权重
        for (int j=0; j<graph->vexNum;j++)
        {
            if (lowcost[j]!=0 && lowcost[j]<min){
                //j顶点不在生成树中，且权重小
                min = lowcost[j];
                k=j;//记录当前最小权重下标
            }

        }
        printf("最小权重边(%d, %d)\n", adjvex[k], k);

        //k点放入生成树
        lowcost[k] = 0;
        for (int j = 0; j < graph->vexNum; j++)
        {
            if (lowcost[j]!=0 && graph->edges[k][j]<lowcost[j]){
                // 若与k邻接的点j不在生成树中， 找小于其初始权重的边
                lowcost[j] = graph->edges[k][j];
                //关联 (k, j)
                adjvex[j] = k;
            }
        }
        
    }
    
    
}

void createGraph(Graph* graph){
    int x,y,weight;
    // 初始化邻接矩阵
    scanf("%d %d",&graph->vexNum, &graph->edgeNum);
    for (int i = 0; i < graph->vexNum; i++)
    {
        scanf("%d",&graph->vertexArray[i]);//录入所有顶点
    }

    for (int i = 0; i < graph->vexNum; i++)
    {
        for (int j =0; j< graph->vexNum;j++)
        {
            graph->edges[i][j] = NULL;//初始化边为空
        }
    }
    for(int i=0; i<graph->edgeNum; i++){
        scanf("%d %d",&x,&y,&weight);
        graph->edges[x][y] = weight;
        graph->edges[y][x] = weight;
    }
        
}