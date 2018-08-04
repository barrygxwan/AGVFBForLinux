#include"Dijkstra.h"


//构造函数
ArrayGraph::ArrayGraph(int length, int width)
{
	int count = 0;
	//初始化地图长、宽、顶点数
	this->length = length;
	this->width = width;
	this->vertexNum =(length+1)*(width+1);


	//为邻接矩阵开辟空间和赋初值
	vertexArr = new int[this->vertexNum];//存点标号
	graph_point = new Tpoint[this->vertexNum];//存每个标号的坐标
    edgeArr = new int*[this->vertexNum];//存边
   
	//存每个标号的坐标
	for (int j=0;j<= this->width;j++){

		for (int i=0;i<= this->length;i++){
			if(count<this->vertexNum){
				graph_point[count++].SetPoint(i,j);
			}else
			{
				printf("overflow!!!!");
			}
			
		}
	}
	//遍历查看

	/*for (int k=0;k< this->vertexNum;k++){

		
        printf("Point[%d]: X= %d,Y= %d\n",k,graph_point[k].getX(),graph_point[k].getY());
		
	}*/

	//创建坐标系各个点之间的邻接矩阵，并建立顶点与坐标值得映射
	for (int i = 0; i < vertexNum; i++)    //填充顶点数组，也就是输入顶点元素   
    {           
       vertexArr[i] = i; 
	   vertexMap.insert(pair<int, Tpoint>(vertexArr[i], graph_point[i])); 
    }  

	


	//邻接矩阵初始化为无穷大
    for (int i = 0; i < this->vertexNum; i++) {
        edgeArr[i] = new int[this->vertexNum];
        for (int k = 0; k < this->vertexNum; k++) {
            
                edgeArr[i][k] = INT_MAX;
        }
    }


	//填充边的权重默认为 1
	  for (int j = 0; j < vertexNum; j++)   //填充边关系   
    {  
		
		if(j<length){       //j<length，最下面一行
		 edgeArr[j][j+1]=1;
		 edgeArr[j][j+length+1]=1;
		 //对称性
		 edgeArr[j+1][j]=1;
		 edgeArr[j+length+1][j]=1;
		}else if((j>=length)&&(j<vertexNum-length-1)){//中间行
					if((j-length)%(length+1) == 0){/*判断是否是最后一条边*/
								edgeArr[j][j+length+1]=1;
								edgeArr[j+length+1][j]=1;
					}else{//中间普通行
			          		 edgeArr[j][j+1]=1;
							 edgeArr[j][j+length+1]=1;
							 //对称性
							 edgeArr[j+1][j]=1;
							 edgeArr[j+length+1][j]=1;
					}
		}else { //最后一行
			if(j==vertexNum-1)//最后一个点
			{
				edgeArr[j][j]=0;
			}else{
			  edgeArr[j][j+1]=1;
			  edgeArr[j+1][j]=1;
			}
		
		}

	  }


}
//析构函数
ArrayGraph:: ~ArrayGraph()
{
	
    for (int i = 0; i < this->vertexNum; i++) {
        delete this->edgeArr[i];
    }
    delete edgeArr;
	delete vertexArr;

}
//打印邻接矩阵	
void ArrayGraph::show()  
{  
  
  
    printf("\n\n顶点元素如下\n");  
    for (int i = 0; i < vertexNum; i++)  
    {  
          
        printf("%-5d", vertexArr[i]);  
    }  
    printf("\n\n");  
  
  
      
    puts("边矩阵如下\n\n");   
    printf("%-2d",' ');  
    for(int i=0;i<vertexNum;++i)  
      printf("%-5d",vertexArr[i]);  
    putchar('\n');    
      
      
      
    for (int j = 0; j < vertexNum; j++)  
    {  
        printf("%-2d",vertexArr[j]);  
        for (int i = 0; i < vertexNum; i++)  
        {  
			if(edgeArr[i][j]== INT_MAX)
				printf("*    ");
            else printf("%-5d",edgeArr[i][j]);  
  
        }  
        putchar('\n');  
    }  
      
    printf("\n\n");  
}  
//求最短路径
void ArrayGraph::Dijkstra(int begin)
{
	//首先初始化我们的dis数组
     dis = new Dis[this->vertexNum];
    for (int i = 0; i < this->vertexNum; i++) {
        //设置当前的路径
        dis[i].path = to_string(static_cast<long long>(begin)) + "-->" + to_string(static_cast<long long>(i));
        dis[i].value = edgeArr[begin][i];
    }
    //设置起点到起点的路径为0
    dis[begin].value = 0;
    dis[begin].visit = true;

    int count = 1;
    //计算剩余的顶点的最短路径（剩余this->vertexNum-1个顶点）
    while (count != this->vertexNum) {
        //temp用于保存当前dis数组中最小的那个下标
        //min记录的当前的最小值
        int temp=0;
        int min = INT_MAX;
        for (int i = 0; i < this->vertexNum; i++) {
            if (!dis[i].visit && dis[i].value<min) {
                min = dis[i].value;
                temp = i;
            }
        }
        
        //把temp对应的顶点加入到已经找到的最短路径的集合中
        dis[temp].visit = true;
        ++count;
        for (int i = 0; i < this->vertexNum; i++) {
            //注意这里的条件edgeArr[temp][i]!=INT_MAX必须加，不然会出现溢出，从而造成程序异常
            if (!dis[i].visit && edgeArr[temp][i]!=INT_MAX && (dis[temp].value + edgeArr[temp][i]) < dis[i].value) {
                //如果新得到的边可以影响其他为访问的顶点，那就就更新它的最短路径和长度
                dis[i].value = dis[temp].value + edgeArr[temp][i];
                dis[i].path = dis[temp].path + "-->" + to_string(static_cast<long long>(i));
            }
        }
    }
}
    //打印最短路径
void ArrayGraph::print_path(int begin)
{
	string str;
    str = "v" + to_string(static_cast<long long>(begin));
    cout << "以"<<str<<"为起点的图的最短路径为：" << endl;
    for (int i = 0; i != this->vertexNum; i++) {
        if(dis[i].value!=INT_MAX)
        cout << dis[i].path << "=" << dis[i].value << endl;
        else {
            cout << dis[i].path << "是无最短路径的" << endl;
        }
    }
	
}

string ArrayGraph::DijkstraFindPath(int begin, int end)
{
	      

	     Dijkstra(begin);

	     if(dis[end].value!=INT_MAX)
              return dis[end].path;
            else {
            cout << dis[end].path << "是无最短路径的" << endl;
			return "not found!!!";
        }
	
}
void ArrayGraph::releasePathHeap()
{

	delete [] dis;
}