#include"Dijkstra.h"


//���캯��
ArrayGraph::ArrayGraph(int length, int width)
{
	int count = 0;
	//��ʼ����ͼ������������
	this->length = length;
	this->width = width;
	this->vertexNum =(length+1)*(width+1);


	//Ϊ�ڽӾ��󿪱ٿռ�͸���ֵ
	vertexArr = new int[this->vertexNum];//�����
	graph_point = new Tpoint[this->vertexNum];//��ÿ����ŵ�����
    edgeArr = new int*[this->vertexNum];//���
   
	//��ÿ����ŵ�����
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
	//�����鿴

	/*for (int k=0;k< this->vertexNum;k++){

		
        printf("Point[%d]: X= %d,Y= %d\n",k,graph_point[k].getX(),graph_point[k].getY());
		
	}*/

	//��������ϵ������֮����ڽӾ��󣬲���������������ֵ��ӳ��
	for (int i = 0; i < vertexNum; i++)    //��䶥�����飬Ҳ�������붥��Ԫ��   
    {           
       vertexArr[i] = i; 
	   vertexMap.insert(pair<int, Tpoint>(vertexArr[i], graph_point[i])); 
    }  

	


	//�ڽӾ����ʼ��Ϊ�����
    for (int i = 0; i < this->vertexNum; i++) {
        edgeArr[i] = new int[this->vertexNum];
        for (int k = 0; k < this->vertexNum; k++) {
            
                edgeArr[i][k] = INT_MAX;
        }
    }


	//���ߵ�Ȩ��Ĭ��Ϊ 1
	  for (int j = 0; j < vertexNum; j++)   //���߹�ϵ   
    {  
		
		if(j<length){       //j<length��������һ��
		 edgeArr[j][j+1]=1;
		 edgeArr[j][j+length+1]=1;
		 //�Գ���
		 edgeArr[j+1][j]=1;
		 edgeArr[j+length+1][j]=1;
		}else if((j>=length)&&(j<vertexNum-length-1)){//�м���
					if((j-length)%(length+1) == 0){/*�ж��Ƿ������һ����*/
								edgeArr[j][j+length+1]=1;
								edgeArr[j+length+1][j]=1;
					}else{//�м���ͨ��
			          		 edgeArr[j][j+1]=1;
							 edgeArr[j][j+length+1]=1;
							 //�Գ���
							 edgeArr[j+1][j]=1;
							 edgeArr[j+length+1][j]=1;
					}
		}else { //���һ��
			if(j==vertexNum-1)//���һ����
			{
				edgeArr[j][j]=0;
			}else{
			  edgeArr[j][j+1]=1;
			  edgeArr[j+1][j]=1;
			}
		
		}

	  }


}
//��������
ArrayGraph:: ~ArrayGraph()
{
	
    for (int i = 0; i < this->vertexNum; i++) {
        delete this->edgeArr[i];
    }
    delete edgeArr;
	delete vertexArr;

}
//��ӡ�ڽӾ���	
void ArrayGraph::show()  
{  
  
  
    printf("\n\n����Ԫ������\n");  
    for (int i = 0; i < vertexNum; i++)  
    {  
          
        printf("%-5d", vertexArr[i]);  
    }  
    printf("\n\n");  
  
  
      
    puts("�߾�������\n\n");   
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
//�����·��
void ArrayGraph::Dijkstra(int begin)
{
	//���ȳ�ʼ�����ǵ�dis����
     dis = new Dis[this->vertexNum];
    for (int i = 0; i < this->vertexNum; i++) {
        //���õ�ǰ��·��
        dis[i].path = to_string(static_cast<long long>(begin)) + "-->" + to_string(static_cast<long long>(i));
        dis[i].value = edgeArr[begin][i];
    }
    //������㵽����·��Ϊ0
    dis[begin].value = 0;
    dis[begin].visit = true;

    int count = 1;
    //����ʣ��Ķ�������·����ʣ��this->vertexNum-1�����㣩
    while (count != this->vertexNum) {
        //temp���ڱ��浱ǰdis��������С���Ǹ��±�
        //min��¼�ĵ�ǰ����Сֵ
        int temp=0;
        int min = INT_MAX;
        for (int i = 0; i < this->vertexNum; i++) {
            if (!dis[i].visit && dis[i].value<min) {
                min = dis[i].value;
                temp = i;
            }
        }
        
        //��temp��Ӧ�Ķ�����뵽�Ѿ��ҵ������·���ļ�����
        dis[temp].visit = true;
        ++count;
        for (int i = 0; i < this->vertexNum; i++) {
            //ע�����������edgeArr[temp][i]!=INT_MAX����ӣ���Ȼ�����������Ӷ���ɳ����쳣
            if (!dis[i].visit && edgeArr[temp][i]!=INT_MAX && (dis[temp].value + edgeArr[temp][i]) < dis[i].value) {
                //����µõ��ı߿���Ӱ������Ϊ���ʵĶ��㣬�Ǿ;͸����������·���ͳ���
                dis[i].value = dis[temp].value + edgeArr[temp][i];
                dis[i].path = dis[temp].path + "-->" + to_string(static_cast<long long>(i));
            }
        }
    }
}
    //��ӡ���·��
void ArrayGraph::print_path(int begin)
{
	string str;
    str = "v" + to_string(static_cast<long long>(begin));
    cout << "��"<<str<<"Ϊ����ͼ�����·��Ϊ��" << endl;
    for (int i = 0; i != this->vertexNum; i++) {
        if(dis[i].value!=INT_MAX)
        cout << dis[i].path << "=" << dis[i].value << endl;
        else {
            cout << dis[i].path << "�������·����" << endl;
        }
    }
	
}

string ArrayGraph::DijkstraFindPath(int begin, int end)
{
	      

	     Dijkstra(begin);

	     if(dis[end].value!=INT_MAX)
              return dis[end].path;
            else {
            cout << dis[end].path << "�������·����" << endl;
			return "not found!!!";
        }
	
}
void ArrayGraph::releasePathHeap()
{

	delete [] dis;
}