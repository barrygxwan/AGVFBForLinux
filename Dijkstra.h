#include <string> 
#include <cstring>  
#include <iostream>
#include <stdio.h>
#include <map>
#define INT_MAX 2147483647
using namespace std; 


/*
本程序是使用Dijkstra算法实现求解最短路径的问题
采用的邻接矩阵来存储图
*/
//记录起点到每个顶点的最短路径的信息
struct Dis {
    string path;
    int value;
    bool visit;
    Dis() {
        visit = false;
        value = 0;
        path = "";
    }
};
//记录每个标号点的坐标值
class Tpoint{
private:
	int X,Y;
public:
	void SetPoint(int x, int y){X=x;Y=y;}
	int getX(){return X;}
	int getY(){return Y;}
};


class ArrayGraph{

private:
	int *vertexArr;//记录图的顶点矩阵
	int **edgeArr; //邻接矩阵
	int vertexNum; //图的顶点数
	int length;    //坐标系的X轴
	int width;     //坐标系的Y轴
	Dis *dis;   //记录各个顶点最短路径的信息
    map<int, Tpoint> vertexMap;  //记录顶点与坐标系的关系
	Tpoint *graph_point;//记录每个顶点的坐标系值
	string path;
	 
public:

	//构造函数
    ArrayGraph(int length, int width);
    //析构函数
    ~ArrayGraph();
	
	map<int, Tpoint> getvertexMap(){return vertexMap;}
	Tpoint *getgraph_point(){return graph_point;}
	void show();//打印邻接矩阵

	 //求最短路径
    void Dijkstra(int begin);
    //打印最短路径
    void print_path(int begin);

	string DijkstraFindPath(int begin, int end);

	void releasePathHeap();

   
	

};



