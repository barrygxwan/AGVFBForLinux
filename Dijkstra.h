#include <string> 
#include <cstring>  
#include <iostream>
#include <stdio.h>
#include <map>
#define INT_MAX 2147483647
using namespace std; 


/*
��������ʹ��Dijkstra�㷨ʵ��������·��������
���õ��ڽӾ������洢ͼ
*/
//��¼��㵽ÿ����������·������Ϣ
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
//��¼ÿ����ŵ������ֵ
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
	int *vertexArr;//��¼ͼ�Ķ������
	int **edgeArr; //�ڽӾ���
	int vertexNum; //ͼ�Ķ�����
	int length;    //����ϵ��X��
	int width;     //����ϵ��Y��
	Dis *dis;   //��¼�����������·������Ϣ
    map<int, Tpoint> vertexMap;  //��¼����������ϵ�Ĺ�ϵ
	Tpoint *graph_point;//��¼ÿ�����������ϵֵ
	string path;
	 
public:

	//���캯��
    ArrayGraph(int length, int width);
    //��������
    ~ArrayGraph();
	
	map<int, Tpoint> getvertexMap(){return vertexMap;}
	Tpoint *getgraph_point(){return graph_point;}
	void show();//��ӡ�ڽӾ���

	 //�����·��
    void Dijkstra(int begin);
    //��ӡ���·��
    void print_path(int begin);

	string DijkstraFindPath(int begin, int end);

	void releasePathHeap();

   
	

};



