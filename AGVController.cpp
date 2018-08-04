/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: AGVController
 *** Description: Tamplate for a simple Basic Function Block Type
 *** Version: 
 ***     0.0: 2018-06-08/4DIAC-IDE - 4DIAC-Consortium - 
 ***     1.0: 2016-05-26/AZ - fortiss GmbH - 
 *************************************************************************/

#include "AGVController.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "AGVController_gen.cpp"
#endif
#include <algorithm>
#include <string>
#include <list>
std::vector<char*> Node;
int* g_path;
int release;

DEFINE_FIRMWARE_FB(FORTE_AGVController, g_nStringIdAGVController)

const CStringDictionary::TStringId FORTE_AGVController::scm_anDataInputNames[] = {g_nStringIdQI, g_nStringIdPathMSG, g_nStringIdCurrentPosition, g_nStringIdLastPosition, g_nStringIdArbitrateCOMD};

const CStringDictionary::TStringId FORTE_AGVController::scm_anDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING};

const CStringDictionary::TStringId FORTE_AGVController::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdState, g_nStringIdcommandToAGV};

const CStringDictionary::TStringId FORTE_AGVController::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdSTRING};

const TForteInt16 FORTE_AGVController::scm_anEIWithIndexes[] = {0, 2, 5, 8};
const TDataIOID FORTE_AGVController::scm_anEIWith[] = {0, 255, 0, 1, 255, 2, 3, 255, 4, 255};
const CStringDictionary::TStringId FORTE_AGVController::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdPATHRecv, g_nStringIdPositionRecv, g_nStringIdArbitration};

const TDataIOID FORTE_AGVController::scm_anEOWith[] = {0, 255, 0, 1, 2, 255, 1, 255};
const TForteInt16 FORTE_AGVController::scm_anEOWithIndexes[] = {0, 2, 6, -1};
const CStringDictionary::TStringId FORTE_AGVController::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF, g_nStringIdTaskDone};

const CStringDictionary::TStringId FORTE_AGVController::scm_anInternalsNames[] = {g_nStringIdArbitrateCommand};

const CStringDictionary::TStringId FORTE_AGVController::scm_anInternalsTypeIds[] = {g_nStringIdBOOL};

const SFBInterfaceSpec FORTE_AGVController::scm_stFBInterfaceSpec = {
  4,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  3,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  5,  scm_anDataInputNames, scm_anDataInputTypeIds,
  3,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


int *p;
const SInternalVarsInformation FORTE_AGVController::scm_stInternalVars = {1, scm_anInternalsNames, scm_anInternalsTypeIds};
MyAGV Agv = MyAGV();

void FORTE_AGVController::setInitialValues(){
  ArbitrateCommand() = 0;
  Agv.direction = 1;
  State() = 0;
}

void FORTE_AGVController::alg_initialize(void){

QO() = QI();
}

void FORTE_AGVController::alg_deInitialize(void){

QO() = false;
}

void FORTE_AGVController::alg_PathMSGParse(void){
	State() = 1;
	QO() = QI();

	for (std::vector<char*>::iterator k = Node.begin(); k != Node.end(); )
	{
		k=Node.erase(k);

	}
	


	//报文解析：v1-->v2-->v3-->v4
	char *path = PathMSG().getValue();
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
	p = g_path;
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
		printf("%s\n",Node[j]);
	}
}

void FORTE_AGVController::alg_Arbitrate(void){

    ArbitrateCommand() = !ArbitrateCommand();
	commandToAGV() = ArbitrateCOMD();
	
}

void FORTE_AGVController::alg_mainControl(void){
	char *Position= CurrentPosition().getValue();
	char *Last=LastPosition().getValue();
	int index = 0;
	if (!ArbitrateCommand())
	{
		//当前位置是否为Node的首个位置； std::vector<char*> Node;
		int Node_size = Node.size();
		//如果node节点中的元素为空，发送停止


////////////////////////////////////////////////////////
		
		//任务完成停止
		if (Node.size()== 0)
		{
			if (Agv.direction== 1)  commandToAGV() = "STOP";
			if (Agv.direction == 2) commandToAGV() = "TURNBACKANDSTOP";
			if (Agv.direction == 3) commandToAGV() = "TURNLEFTANDSTOP";
			if (Agv.direction == 4) commandToAGV() = "TURNRIGHTANDSTOP";
			State() = 0;
			sendOutputEvent(scm_nEventTaskDoneID);
			//printf("Command: %s", commandToAGV());
			if (!release)
			{
				g_path = p;
				free(g_path);
				release = 1;
			}
			
			
			
		}
		else if (Node.size() == 1)//当前处于最后一个位置
		{
			if (atoi(Position) == *g_path)
			{
				commandToAGV() = "STOP";
				g_path++;
				std::vector<char*>::iterator k = Node.begin();//删除第一个元素
				Node.erase(k);

				
			}
			else
			{
				commandToAGV() = "FORWARD";
			}
			//printf("Command: %s", commandToAGV());
		}
		else 
		{
			
			if (atoi(Position) == *g_path)//当前处于有效位置
			{
				//判断下一个节点，决定转向，初始化方向为Y轴正方向

				if (*(g_path + 1) - *g_path > 1)//朝向Y+运动
				{	
						switch (Agv.direction)
					   {
							case 1: commandToAGV() = "FORWARD";
								break;
							case 2: commandToAGV() = "TURNBACK";
								break;
							case 3: commandToAGV() = "TURNLEFT";
								break;
							case 4: commandToAGV() = "TURNRIGHT";
							default:
								break;
						}

						Agv.direction = 1;
				}
				else if (*(g_path + 1) - *g_path<-1)//朝向Y轴负方向运动
				{
					switch (Agv.direction)
					{
					case 1: commandToAGV() = "TURNBACK";
						break;
					case 2: commandToAGV() = "FORWARD";
						break;
					case 3: commandToAGV() = "TURNRIGHT";
						break;
					case 4: commandToAGV() = "TURNLEFT";
					default:
						break;
					}
					Agv.direction = 2;
				}

				else if (*(g_path + 1) - *g_path==1)//朝向X轴正方向运动
				{
					switch (Agv.direction)
					{
					case 1: 
						commandToAGV() = "TURNRIGHT";
						break;
					case 2: commandToAGV() = "TURNLEFT";
						break;
					case 3: commandToAGV() = "FORWARDT";
						break;
					case 4: commandToAGV() = "TURNBACK"; 
					default:
						break;
					}
					Agv.direction = 3;
				}
				
				else if (*(g_path + 1) - *g_path == -1)//朝向X轴负方向运动
				{
					switch (Agv.direction)
					{
					case 1: commandToAGV() = "TURNLEFT";
						break;
					case 2: commandToAGV() = "TURNRIGHT";
						break;
					case 3: commandToAGV() = "TURNBACK";
						break;
					case 4: commandToAGV() = "FORWARDT";
					default:
						break;
					}
					Agv.direction = 4;
				}

				std::vector<char*>::iterator k = Node.begin();//删除第一个元素
				Node.erase(k);
				g_path++;
				
				//printf("Command: %s", &commandToAGV());


			}
			else
			{
				printf("current position is %s\n", Position);

			}


		}

		

	}
}


void FORTE_AGVController::enterStateSTART(void){
  m_nECCState = scm_nStateSTART;
}

void FORTE_AGVController::enterStateInit(void){
  m_nECCState = scm_nStateInit;
  alg_initialize();
  sendOutputEvent( scm_nEventINITOID);
}

void FORTE_AGVController::enterStatePathParse(void){
  m_nECCState = scm_nStatePathParse;
  alg_PathMSGParse();
}

void FORTE_AGVController::enterStateInitialized(void){
  m_nECCState = scm_nStateInitialized;
}

void FORTE_AGVController::enterStateDeInit(void){
  m_nECCState = scm_nStateDeInit;
  alg_deInitialize();
  sendOutputEvent( scm_nEventINITOID);
}

void FORTE_AGVController::enterStatearbitrateControl(void){
  m_nECCState = scm_nStatearbitrateControl;
  alg_Arbitrate();
  sendOutputEvent( scm_nEventCNFID);
}

void FORTE_AGVController::enterStatePositionControl(void){
  m_nECCState = scm_nStatePositionControl;
  alg_mainControl();
  sendOutputEvent( scm_nEventCNFID);
}

void FORTE_AGVController::executeEvent(int pa_nEIID){
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
      case scm_nStatePathParse:
        if(1)
          enterStateInitialized();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateInitialized:
        if(scm_nEventPATHRecvID == pa_nEIID)
          enterStatePathParse();
        else
        if((scm_nEventINITID == pa_nEIID) && ((false == QI())))
          enterStateDeInit();
        else
        if(scm_nEventArbitrationID == pa_nEIID)
          enterStatearbitrateControl();
        else
        if(scm_nEventPositionRecvID == pa_nEIID)
          enterStatePositionControl();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateDeInit:
        if(1)
          enterStateSTART();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStatearbitrateControl:
        if(1)
          enterStateInitialized();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStatePositionControl:
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


