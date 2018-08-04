/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: MapAndPath
 *** Description: Tamplate for a simple Basic Function Block Type
 *** Version: 
 ***     0.0: 2018-06-04/4DIAC-IDE - 4DIAC-Consortium - 
 ***     1.0: 2016-05-26/AZ - fortiss GmbH - 
 *************************************************************************/

#include "MapAndPath.h"
#include"Dijkstra.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "MapAndPath_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_MapAndPath, g_nStringIdMapAndPath)

const CStringDictionary::TStringId FORTE_MapAndPath::scm_anDataInputNames[] = {g_nStringIdQI, g_nStringIdLengthAndWeight, g_nStringIdAlgorithmSelection, g_nStringIdBeginEndPosition};

const CStringDictionary::TStringId FORTE_MapAndPath::scm_anDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdINT, g_nStringIdSTRING};

const CStringDictionary::TStringId FORTE_MapAndPath::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdState, g_nStringIdresult};

const CStringDictionary::TStringId FORTE_MapAndPath::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdSTRING};

const TForteInt16 FORTE_MapAndPath::scm_anEIWithIndexes[] = {0, 2, 4};
const TDataIOID FORTE_MapAndPath::scm_anEIWith[] = {0, 255, 1, 255, 2, 3, 255};
const CStringDictionary::TStringId FORTE_MapAndPath::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdCreateMap, g_nStringIdPathPlan};

const TDataIOID FORTE_MapAndPath::scm_anEOWith[] = {0, 255, 1, 255, 2, 255};
const TForteInt16 FORTE_MapAndPath::scm_anEOWithIndexes[] = {0, 2, 4, -1};
const CStringDictionary::TStringId FORTE_MapAndPath::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdmap_CNF, g_nStringIdPath_CNF};

const CStringDictionary::TStringId FORTE_MapAndPath::scm_anInternalsNames[] = {g_nStringIdmaxNum};

const CStringDictionary::TStringId FORTE_MapAndPath::scm_anInternalsTypeIds[] = {g_nStringIdINT};

const SFBInterfaceSpec FORTE_MapAndPath::scm_stFBInterfaceSpec = {
  3,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  3,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  4,  scm_anDataInputNames, scm_anDataInputTypeIds,
  3,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


const SInternalVarsInformation FORTE_MapAndPath::scm_stInternalVars = {1, scm_anInternalsNames, scm_anInternalsTypeIds};

//构建全局变量
ArrayGraph *myGraph;

void FORTE_MapAndPath::alg_initialize(void){

QO() = QI();
}

void FORTE_MapAndPath::alg_deInitialize(void){

QO() = false;
}

void FORTE_MapAndPath::alg_creatMap(void){
	
//解析报文Head+map_length_height+end 
	int m;
    int n ;

 char* recvMsg =LengthAndWeight().getValue();
 
 char temp1[5];
 char temp2[5];
 int i =0,j=0;

 do { temp1[i++] = *recvMsg; } while (*recvMsg && *recvMsg++ != '_');
 while (*recvMsg) temp2[j++] = *recvMsg++;


 /*while( *recvMsg && *recvMsg++!='_' ) ;
 while( *recvMsg && *recvMsg!='_' ) temp1[i++]=*recvMsg++;
 *recvMsg++;
 while( *recvMsg && *recvMsg!='+' ) temp2[j++]=*recvMsg++;*/
    temp1[i]='\0';
	temp2[j]='\0';

   m = atoi(temp1);
   n = atoi(temp2);
   maxNum() = (m + 1)*(n + 1);
   printf("Length = %d, weidth = %d\n",m,n);
   
  
	//构建图
   myGraph =new ArrayGraph(m,n);
    State() = "OK";
}

void FORTE_MapAndPath::alg_PathPlan(void){

	//解析任务的起始点和终点
	int begin;
	int end;
	char* recvMsg = BeginEndPosition().getValue();
	char temp1[5];
	char temp2[5];
	int i = 0, j = 0;
	do { temp1[i++] = *recvMsg; } while (*recvMsg && *recvMsg++ != '_');
	while (*recvMsg ) temp2[j++] = *recvMsg++;
	
	temp1[i] = '\0';
	temp2[j] = '\0';

	begin = atoi(temp1);
	end = atoi(temp2);

//	printf("Length = %d, weidth = %d\n", begin, end);
	if ((begin<=maxNum())&&(end <= maxNum()))
	{
		string path;
		switch (AlgorithmSelection())
		{
		case 1:path = (myGraph->DijkstraFindPath(begin, end));
			break;
		default:
			break;
		}

		char temp[1024];
		strcpy(temp,path.c_str());

		result()=temp;
	}
	else
	{
		result() = "Task Error!";
	}
	

}


void FORTE_MapAndPath::enterStateSTART(void){
  m_nECCState = scm_nStateSTART;
}

void FORTE_MapAndPath::enterStateInit(void){
  m_nECCState = scm_nStateInit;
  alg_initialize();
  sendOutputEvent( scm_nEventINITOID);
}

void FORTE_MapAndPath::enterStateMapCreation(void){
  m_nECCState = scm_nStateMapCreation;
  alg_creatMap();
  sendOutputEvent( scm_nEventmap_CNFID);
}

void FORTE_MapAndPath::enterStateInitialized(void){
  m_nECCState = scm_nStateInitialized;
}

void FORTE_MapAndPath::enterStateDeInit(void){
  m_nECCState = scm_nStateDeInit;
  alg_deInitialize();
  sendOutputEvent( scm_nEventINITOID);
}

void FORTE_MapAndPath::enterStatePathPlan(void){
  m_nECCState = scm_nStatePathPlan;
  alg_PathPlan();
  sendOutputEvent( scm_nEventPath_CNFID);
}

void FORTE_MapAndPath::executeEvent(int pa_nEIID){
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
      case scm_nStateMapCreation:
        if(1)
          enterStateInitialized();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateInitialized:
        if(scm_nEventCreateMapID == pa_nEIID)
          enterStateMapCreation();
        else
        if((scm_nEventINITID == pa_nEIID) && ((false == QI())))
          enterStateDeInit();
        else
        if(scm_nEventPathPlanID == pa_nEIID)
          enterStatePathPlan();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateDeInit:
        if(1)
          enterStateSTART();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStatePathPlan:
        if(1)
          enterStateInitialized();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      default:
      DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 5.", m_nECCState.operator TForteUInt16 ());
        m_nECCState = 0; //0 is always the initial state
        break;
    }
    pa_nEIID = cg_nInvalidEventID;  // we have to clear the event after the first check in order to ensure correct behavior
  }while(bTransitionCleared);
}


