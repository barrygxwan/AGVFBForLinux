/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: Controller_Direction_Speed
 *** Description: Tamplate for a simple Basic Function Block Type
 *** Version: 
 ***     0.0: 2018-07-24/4DIAC-IDE - 4DIAC-Consortium - 
 ***     1.0: 2016-05-26/AZ - fortiss GmbH - 
 *************************************************************************/

#include "Controller_Direction_Speed.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "Controller_Direction_Speed_gen.cpp"
#endif
#include <algorithm>
#include <string>
#include <list>


DEFINE_FIRMWARE_FB(FORTE_Controller_Direction_Speed, g_nStringIdController_Direction_Speed)

const CStringDictionary::TStringId FORTE_Controller_Direction_Speed::scm_anDataInputNames[] = { g_nStringIdQI, g_nStringIdpathMSG, g_nStringIdmy_position_x_y, g_nStringIdtarget_positon_y, g_nStringIdmy_positionLable, g_nStringIdArbitrationCMD, g_nStringIddistance };

const CStringDictionary::TStringId FORTE_Controller_Direction_Speed::scm_anDataInputTypeIds[] = { g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdINT };

const CStringDictionary::TStringId FORTE_Controller_Direction_Speed::scm_anDataOutputNames[] = { g_nStringIdQO, g_nStringIdstate, g_nStringIdcommandOutput };

const CStringDictionary::TStringId FORTE_Controller_Direction_Speed::scm_anDataOutputTypeIds[] = { g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdSTRING };

const TForteInt16 FORTE_Controller_Direction_Speed::scm_anEIWithIndexes[] = { 0, 3, 6, 10 };
const TDataIOID FORTE_Controller_Direction_Speed::scm_anEIWith[] = { 0, 6, 255, 0, 1, 255, 2, 3, 4, 255, 5, 255 };
const CStringDictionary::TStringId FORTE_Controller_Direction_Speed::scm_anEventInputNames[] = { g_nStringIdINIT, g_nStringIdPATH, g_nStringIdPOSITION, g_nStringIdARBITRATION };

const TDataIOID FORTE_Controller_Direction_Speed::scm_anEOWith[] = { 0, 255, 0, 2, 255, 1, 255 };
const TForteInt16 FORTE_Controller_Direction_Speed::scm_anEOWithIndexes[] = { 0, 2, 5, -1 };
const CStringDictionary::TStringId FORTE_Controller_Direction_Speed::scm_anEventOutputNames[] = { g_nStringIdINITO, g_nStringIdCNF, g_nStringIdVEHICLESTATE };

const CStringDictionary::TStringId FORTE_Controller_Direction_Speed::scm_anInternalsNames[] = { g_nStringIdArbitrateCommand, g_nStringIdDirection };

const CStringDictionary::TStringId FORTE_Controller_Direction_Speed::scm_anInternalsTypeIds[] = { g_nStringIdBOOL, g_nStringIdSTRING };

const SFBInterfaceSpec FORTE_Controller_Direction_Speed::scm_stFBInterfaceSpec = {
	4,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
	3,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  7,  scm_anDataInputNames, scm_anDataInputTypeIds,
	3,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
	0, 0
};


const SInternalVarsInformation FORTE_Controller_Direction_Speed::scm_stInternalVars = { 2, scm_anInternalsNames, scm_anInternalsTypeIds };



void FORTE_Controller_Direction_Speed::setInitialValues(){
  ArbitrateCommand() = 0;
  myAgv.direction = 1;
}

void FORTE_Controller_Direction_Speed::alg_initialize(void){

QO() = QI();
}

void FORTE_Controller_Direction_Speed::alg_deInitialize(void){

QO() = false;
}

void FORTE_Controller_Direction_Speed::alg_PathMSGParse(void){
	state() = 1;
	QO() = QI();

	for (std::vector<char*>::iterator k = Node.begin(); k != Node.end(); )
	{
		k = Node.erase(k);

	}



	//报文解析：1-->2-->3-->4
	char *path = pathMSG().getValue();
	char Path[1024];
	int num = 0;
	int i = 0;
	char *delim = "-->";
	while (*path)
	{
		Path[i++] = *path;
		*path++;
	}
	Path[i] = '\0';

	char *token = strtok(Path, delim);
	if (token != NULL)
	{
		Node.push_back(token);
	}
	while (token != NULL)
	{
		/* Get next token: */
		token = strtok(NULL, delim);
		/* Append to array */
		if (token != NULL)
		{
			Node.push_back(token);
		}
	}

	g_path = (int*)malloc(sizeof(int)*Node.size());
	pq = g_path;
	release = 0;
	int index = 0;
	for (index = 0; index < Node.size(); index++)
	{
		*(g_path + index) = atoi(Node[index]);
	}

	printf("%d\n", Node.size());
	//打印结果
	printf("Node sequences :");
	for (size_t j = 0; j < Node.size(); j++)
	{
		printf("%s\n", Node[j]);
	}

}

void FORTE_Controller_Direction_Speed::alg_Arbitrate(void){
	ArbitrateCommand() = !ArbitrateCommand();

	commandOutput() = ArbitrationCMD();
}

void FORTE_Controller_Direction_Speed::alg_realTimeControl(void){

	//速度控制
	char *myPosition = my_position_x_y().getValue();
	char *targetPosition = target_positon_y().getValue();
	int speed,m_x,m_y,t_x,t_y;
	int index = 0;
	int realDistance;
	int Kp = 10;
	char myPosition_x[10];
	char myPosition_y[10];
	char targetPosition_x[10];
	char targetPosition_y[10];

	while (*myPosition&&*myPosition!='_')
	{
		myPosition_x[index++] = *myPosition++;
	}
	myPosition_x[index] = '\0';
	index = 0;
	*myPosition++;
	while (*myPosition)
	{
		myPosition_y[index++] = *myPosition++;
	}
	myPosition_y[index] = '\0';
	index = 0;

	while (*targetPosition&&*targetPosition != '_')
	{
		targetPosition_x[index++] = *targetPosition++;
	}
	targetPosition_x[index] = '\0';
	index = 0;
	*targetPosition++;
	while (*targetPosition)
	{
		targetPosition_y[index++] = *targetPosition++;
	}
	targetPosition_y[index] = '\0';
	index = 0;

	m_x = atoi(myPosition_x);
	m_y = atoi(myPosition_y);
	t_x = atoi(targetPosition_x);
	t_y = atoi(targetPosition_y);

	realDistance = sqrt((m_x - t_x)*(m_x - t_x) + (m_y - t_y)*(m_y - t_y));

	if (realDistance - distance()>=0)
	{
		speed = (realDistance - distance())*Kp;
	}
	else
	{
		speed = 0;
	}
	char str_speed[30];

	//itoa(speed, str_speed, 10);
	sprintf(str_speed, "%04d", speed);

	//方向控制
	//F1--左转；F2--右转；F3--前进；F5--掉头；F6--停止
	char *Position = my_positionLable().getValue();
	
	index = 0;
	if (!ArbitrateCommand())
	{
		//当前位置是否为Node的首个位置； std::vector<char*> Node;
		int Node_size = Node.size();
		//如果node节点中的元素为空，发送停止


		////////////////////////////////////////////////////////

		//任务完成停止
		if ((Node.size() == 0) && (release == 0))
		{
			if (myAgv.direction == 1) Direction() = "F6",myAgv.direction = 1;
			if (myAgv.direction == 2) Direction() = "F5",myAgv.direction = 1;
			if (myAgv.direction == 3) Direction() = "F1",myAgv.direction = 1;
			if (myAgv.direction == 4) Direction() = "F2",myAgv.direction = 1;
			state() = 0;
			sendOutputEvent(scm_nEventVEHICLESTATEID);
			//printf("Command: %s", commandToAGV());
			//命令封装Head+D_Direction_speed+End
			char buf[1024];
			strcpy(buf, "Head+D_");
			strcat(buf, Direction().getValue());
			strcat(buf, "_");
			strcat(buf, str_speed);
			strcat(buf, "+End");

			printf("current position is %s\n", Position);	
			commandOutput() = buf;

			printf("This command is: %s\n", buf);
			if (!release)
			{
				g_path = pq;
				free(g_path);
				release = 1;
			}



		}
		else if (Node.size() == 1)//当前处于最后一个位置
		{
			if (atoi(Position) == *g_path)
			{
				Direction() = "F6";
				g_path++;
				std::vector<char*>::iterator k = Node.begin();//删除第一个元素
				Node.erase(k);


			}
			else
			{
				Direction() = "F3";
			}
			//printf("Command: %s", commandToAGV());
			//命令封装Head+D_Direction_speed+End
			char buf[1024];
			strcpy(buf, "Head+D_");
			strcat(buf, Direction().getValue());
			strcat(buf, "_");
			strcat(buf, str_speed);
			strcat(buf, "+End");

           printf("current position is %s\n", Position);
			commandOutput() = buf;

			printf("This command is: %s\n", buf);
		}
		else if (Node.size() > 1)
		{

			if (atoi(Position) == *g_path)//当前处于有效位置
			{
				//判断下一个节点，决定转向，初始化方向为Y轴正方向
				if (*(g_path + 1) - *g_path > 1)//朝向Y+运动
				{
					switch (myAgv.direction)
					{
					case 1: Direction() = "F3";
						break;
					case 2: Direction() = "F5";
						break;
					case 3: Direction() = "F1";
						break;
					case 4: Direction() = "F2";
					default:
						break;
					}

					myAgv.direction = 1;
				}
				else if (*(g_path + 1) - *g_path<-1)//朝向Y轴负方向运动
				{
					switch (myAgv.direction)
					{
					case 1: Direction() = "F5";
						break;
					case 2: Direction() = "F3";
						break;
					case 3: Direction() = "F2";
						break;
					case 4: Direction() = "F1";
					default:
						break;
					}
					myAgv.direction = 2;
				}

				else if (*(g_path + 1) - *g_path == 1)//朝向X轴正方向运动
				{
					switch (myAgv.direction)
					{
					case 1:
						Direction() = "F2";
						break;
					case 2: Direction() = "F1";
						break;
					case 3: Direction() = "F3";
						break;
					case 4: Direction() = "F5";
					default:
						break;
					}
					myAgv.direction = 3;
				}

				else if (*(g_path + 1) - *g_path == -1)//朝向X轴负方向运动
				{
					switch (myAgv.direction)
					{
					case 1: Direction() = "F1";
						break;
					case 2: Direction() = "F2";
						break;
					case 3: Direction() = "F5";
						break;
					case 4: Direction() = "F3";
					default:
						break;
					}
					myAgv.direction = 4;
				}


				std::vector<char*>::iterator k = Node.begin();//删除第一个元素
				Node.erase(k);
				g_path++;




				//printf("Command: %s", &commandToAGV());
				//命令封装Head+D_Direction_speed+End
				char buf[1024];
				strcpy(buf, "Head+D_");
				strcat(buf, Direction().getValue());
				strcat(buf, "_");
				strcat(buf, str_speed);
				strcat(buf, "+End");

	            printf("current position is %s\n", Position);
				commandOutput() = buf;

				printf("This command is: %s\n", buf);


			}
			else if (release == 0)
			{
				Direction() = "F3";
				//命令封装Head+D_Direction_speed+End
				char buf[1024];
				strcpy(buf, "Head+D_");
				strcat(buf, Direction().getValue());
				strcat(buf, "_");
				strcat(buf, str_speed);
				strcat(buf, "+End");

				printf("current position is %s\n", Position);
				commandOutput() = buf;

				printf("This command is: %s\n", buf);
			}
			else {

				Direction() = "F6";
				//命令封装Head+D_Direction_speed+End
				char buf[1024];
				strcpy(buf, "Head+D_");
				strcat(buf, Direction().getValue());
				strcat(buf, "_");
				strcat(buf, "0");
				strcat(buf, "+End");

				printf("current position is %s\n", Position);
				commandOutput() = buf;

				printf("This command is: %s\n", buf);
			}
			

		}
		else
		{
			    Direction() = "F6";
				//命令封装Head+D_Direction_speed+End
				char buf[1024];
				strcpy(buf, "Head+D_");
				strcat(buf, Direction().getValue());
				strcat(buf, "_");
				strcat(buf, "0");
				strcat(buf, "+End");

				printf("current position is %s\n", Position);
				commandOutput() = buf;
		}




	}
	else
	{
		commandOutput() = "Head+D_F6_0000+End";
	}
}


void FORTE_Controller_Direction_Speed::enterStateSTART(void){
  m_nECCState = scm_nStateSTART;
}

void FORTE_Controller_Direction_Speed::enterStateInit(void){
  m_nECCState = scm_nStateInit;
  alg_initialize();
  sendOutputEvent( scm_nEventINITOID);
}

void FORTE_Controller_Direction_Speed::enterStateInitialized(void){
  m_nECCState = scm_nStateInitialized;
}

void FORTE_Controller_Direction_Speed::enterStateDeInit(void){
  m_nECCState = scm_nStateDeInit;
  alg_deInitialize();
  sendOutputEvent( scm_nEventINITOID);
}

void FORTE_Controller_Direction_Speed::enterStatePathParse(void){
  m_nECCState = scm_nStatePathParse;
  alg_PathMSGParse();
}

void FORTE_Controller_Direction_Speed::enterStateArbitrateControl(void){
  m_nECCState = scm_nStateArbitrateControl;
  alg_Arbitrate();
  sendOutputEvent( scm_nEventCNFID);
}

void FORTE_Controller_Direction_Speed::enterStatePositionRealTimeControl(void){
  m_nECCState = scm_nStatePositionRealTimeControl;
  alg_realTimeControl();
  sendOutputEvent( scm_nEventCNFID);
}

void FORTE_Controller_Direction_Speed::executeEvent(int pa_nEIID){
  bool bTransitionCleared;
  do{
    bTransitionCleared = true;
    switch(m_nECCState){
      case scm_nStateSTART:
        if((scm_nEventINITID == pa_nEIID) && ((true == QI())))
          enterStateInit();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateInit:
        if(1)
          enterStateInitialized();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateInitialized:
        if((scm_nEventINITID == pa_nEIID) && ((false == QI())))
          enterStateDeInit();
        else
        if(scm_nEventPATHID == pa_nEIID)
          enterStatePathParse();
        else
        if(scm_nEventARBITRATIONID == pa_nEIID)
          enterStateArbitrateControl();
        else
        if(scm_nEventPOSITIONID == pa_nEIID)
          enterStatePositionRealTimeControl();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateDeInit:
        if(1)
          enterStateSTART();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStatePathParse:
        if(1)
          enterStateInitialized();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateArbitrateControl:
        if(1)
          enterStateInitialized();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStatePositionRealTimeControl:
        if(1)
          enterStateInitialized();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      default:
      DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 6.", m_nECCState.operator TForteUInt16 ());
        m_nECCState = 0; //0 is always the initial state
        break;
    }
    pa_nEIID = cg_nInvalidEventID;  // we have to clear the event after the first check in order to ensure correct behavior
  }while(bTransitionCleared);
}


