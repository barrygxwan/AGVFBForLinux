/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: TaskManager
 *** Description: Tamplate for a simple Basic Function Block Type
 *** Version: 
 ***     0.0: 2018-07-05/4DIAC-IDE - 4DIAC-Consortium - 
 ***     1.0: 2016-05-26/AZ - fortiss GmbH - 
 *************************************************************************/

#include "TaskManager.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "TaskManager_gen.cpp"
#endif
#include"stdio.h"

DEFINE_FIRMWARE_FB(FORTE_TaskManager, g_nStringIdTaskManager)

const CStringDictionary::TStringId FORTE_TaskManager::scm_anDataInputNames[] = {g_nStringIdQI, g_nStringIdPosition, g_nStringIdTaskMSG};

const CStringDictionary::TStringId FORTE_TaskManager::scm_anDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdSTRING};

const CStringDictionary::TStringId FORTE_TaskManager::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdPath, g_nStringIdFinish};

const CStringDictionary::TStringId FORTE_TaskManager::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdSTRING};

const TForteInt16 FORTE_TaskManager::scm_anEIWithIndexes[] = {0, 2, 4, -1};
const TDataIOID FORTE_TaskManager::scm_anEIWith[] = {0, 255, 1, 255, 0, 2, 1, 255};
const CStringDictionary::TStringId FORTE_TaskManager::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdCurrentPosition, g_nStringIdTaskRecv, g_nStringIdTaskDone};

const TDataIOID FORTE_TaskManager::scm_anEOWith[] = {0, 255, 0, 1, 255, 2, 255};
const TForteInt16 FORTE_TaskManager::scm_anEOWithIndexes[] = {0, 2, 5, -1};
const CStringDictionary::TStringId FORTE_TaskManager::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF, g_nStringIdTaskFinish};

const CStringDictionary::TStringId FORTE_TaskManager::scm_anInternalsNames[] = {g_nStringIdTaskCount, g_nStringIdPath1, g_nStringIdPaht2};

const CStringDictionary::TStringId FORTE_TaskManager::scm_anInternalsTypeIds[] = {g_nStringIdINT, g_nStringIdSTRING, g_nStringIdSTRING};

const SFBInterfaceSpec FORTE_TaskManager::scm_stFBInterfaceSpec = {
  4,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  3,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  3,  scm_anDataInputNames, scm_anDataInputTypeIds,
  3,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


const SInternalVarsInformation FORTE_TaskManager::scm_stInternalVars = {3, scm_anInternalsNames, scm_anInternalsTypeIds};


void FORTE_TaskManager::setInitialValues(){
  TaskCount() = 0;
}

void FORTE_TaskManager::alg_initialize(void){

QO() = QI();
}

void FORTE_TaskManager::alg_deInitialize(void){

QO() = false;
}

void FORTE_TaskManager::alg_PathRebuild(void){
	char *currentPosition= Position().getValue();
	char *task = TaskMSG().getValue();
	Path2() = TaskMSG();
	char temp[10];
	int tempIndex = 0;
	//判断位置是否有效
	if (strcmp(currentPosition,"a")==0)
	{
		printf("The Position is invalid!");
	}
	else
	{

		while (*currentPosition)
		{
			temp[tempIndex++] = *currentPosition++;
		}
		temp[tempIndex++] = '_';
		while (*task&&*task != '_')
		{
			temp[tempIndex++] = *task++;
		}
		temp[tempIndex] = '\0';
		Path1() = temp;
		Path() = Path1();
	}

	TaskCount() = 0;
	}






void FORTE_TaskManager::alg_Path2MSG(void) {
	Path() = Path2();
	TaskCount() = 1;
}

void FORTE_TaskManager::alg_TaskReallyDone(void){


	Finish() = "Task is finised";
	TaskCount() = 0;
}

void FORTE_TaskManager::alg_positionUpdate(void){

}


void FORTE_TaskManager::enterStateSTART(void){
  m_nECCState = scm_nStateSTART;
}

void FORTE_TaskManager::enterStateInit(void){
  m_nECCState = scm_nStateInit;
  alg_initialize();
  sendOutputEvent( scm_nEventINITOID);
}

void FORTE_TaskManager::enterStateTaskRearrangement(void){
  m_nECCState = scm_nStateTaskRearrangement;
  alg_PathRebuild();
  sendOutputEvent( scm_nEventCNFID);
}

void FORTE_TaskManager::enterStateInitialized(void){
  m_nECCState = scm_nStateInitialized;
}

void FORTE_TaskManager::enterStateDeInit(void){
  m_nECCState = scm_nStateDeInit;
  alg_deInitialize();
  sendOutputEvent( scm_nEventINITOID);
}

void FORTE_TaskManager::enterStateTaskPhaseOne(void){
  m_nECCState = scm_nStateTaskPhaseOne;
  alg_Path2MSG();
  sendOutputEvent( scm_nEventCNFID);
}

void FORTE_TaskManager::enterStateTaskFinish(void){
  m_nECCState = scm_nStateTaskFinish;
  alg_TaskReallyDone();
  sendOutputEvent( scm_nEventTaskFinishID);
}

void FORTE_TaskManager::enterStatePositionState(void){
  m_nECCState = scm_nStatePositionState;
  alg_positionUpdate();
}

void FORTE_TaskManager::executeEvent(int pa_nEIID){
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
      case scm_nStateTaskRearrangement:
        if(1)
          enterStateInitialized();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateInitialized:
        if(scm_nEventTaskRecvID == pa_nEIID)
          enterStateTaskRearrangement();
        else
        if((scm_nEventINITID == pa_nEIID) && ((false == QI())))
          enterStateDeInit();
        else
        if((scm_nEventTaskDoneID == pa_nEIID) && ((TaskCount() == 0)))
          enterStateTaskPhaseOne();
        else
        if((scm_nEventTaskDoneID == pa_nEIID) && ((TaskCount() == 1)))
          enterStateTaskFinish();
        else
        if(scm_nEventCurrentPositionID == pa_nEIID)
          enterStatePositionState();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateDeInit:
        if(1)
          enterStateSTART();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateTaskPhaseOne:
        if(1)
          enterStateInitialized();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateTaskFinish:
        if(1)
          enterStateInitialized();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStatePositionState:
        if(1)
          enterStateInitialized();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      default:
      DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 7.", m_nECCState.operator TForteUInt16 ());
        m_nECCState = 0; //0 is always the initial state
        break;
    }
    pa_nEIID = cg_nInvalidEventID;  // we have to clear the event after the first check in order to ensure correct behavior
  }while(bTransitionCleared);
}


