/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: MsgpParse
 *** Description: Tamplate for a simple Basic Function Block Type
 *** Version: 
 ***     0.0: 2018-05-31/4DIAC-IDE - 4DIAC-Consortium - 
 ***     1.0: 2016-05-26/AZ - fortiss GmbH - 
 *************************************************************************/
#include <stdio.h>
#include "MsgpParse.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "MsgpParse_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_MsgpParse, g_nStringIdMsgpParse)

const CStringDictionary::TStringId FORTE_MsgpParse::scm_anDataInputNames[] = {g_nStringIdQI};

const CStringDictionary::TStringId FORTE_MsgpParse::scm_anDataInputTypeIds[] = {g_nStringIdSTRING};

const CStringDictionary::TStringId FORTE_MsgpParse::scm_anDataOutputNames[] = {g_nStringIdcurrentPosition, g_nStringIdlastPosition};

const CStringDictionary::TStringId FORTE_MsgpParse::scm_anDataOutputTypeIds[] = {g_nStringIdSTRING, g_nStringIdSTRING};

const TForteInt16 FORTE_MsgpParse::scm_anEIWithIndexes[] = {0};
const TDataIOID FORTE_MsgpParse::scm_anEIWith[] = {0, 255};
const CStringDictionary::TStringId FORTE_MsgpParse::scm_anEventInputNames[] = {g_nStringIdREQ};

const TDataIOID FORTE_MsgpParse::scm_anEOWith[] = {0, 1, 255};
const TForteInt16 FORTE_MsgpParse::scm_anEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_MsgpParse::scm_anEventOutputNames[] = {g_nStringIdCNF};

const SFBInterfaceSpec FORTE_MsgpParse::scm_stFBInterfaceSpec = {
  1,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  1,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  1,  scm_anDataInputNames, scm_anDataInputTypeIds,
  2,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};

void FORTE_MsgpParse::alg_parseOperation(void){
 char* recvMsg =QI().getValue();
 char VP[4];
 char currentP[10];
 char LastP[10];
 char End[5];
 int i = 0, VPindex = 0, currentPindex = 0, LastPindex = 0, Endindex = 0;
 bool isComplete = false;

 //VP + P_LastP +End
 //检查报文完整性
 while (*recvMsg&&*recvMsg != '+')//TM
 {
	 if (VPindex >= 4)
	 {
		 printf("报文不完整");
		 isComplete = false;
		 break;
	 }
	 else
	 {
		 VP[VPindex++] = *recvMsg++;
	 }

 }
 VP[VPindex] = '\0';
 *recvMsg++;

 while ((strcmp(VP, "VP") == 0)&&*recvMsg&&*recvMsg != '_')//TM
 {
	 if (currentPindex >= 10)
	 {
		// printf("报文不完整");
		 isComplete = false;
		 break;
	 }
	 else
	 {
		 currentP[currentPindex++] = *recvMsg++;
	 }

 }
		currentP[currentPindex] = '\0';
		 *recvMsg++;

		 while ((strcmp(VP, "VP") == 0)&&*recvMsg&&*recvMsg != '+')//TM
		 {
			 if (LastPindex >= 10)
			 {
				// printf("报文不完整");
				 isComplete = false;
				 break;
			 }
			 else
			 {
				 LastP[LastPindex++] = *recvMsg++;
			 }

		 }
		 LastP[LastPindex] = '\0';
		 *recvMsg++;

		 while ((strcmp(VP, "VP") == 0) && *recvMsg)//END判断
		 {

			 if (Endindex >= 4)
			 {
				// printf("报文不完整");
				 isComplete = false;
				 break;
			 }
			 else
			 {
				 End[Endindex++] = *recvMsg++;
			 }

		 }
		 End[Endindex] = '\0';

		 if ((strcmp(VP, "VP") == 0) && (strcmp(End, "End") == 0))
		 {
			// printf("报文完整\n");
			 isComplete = true;
		 }
		 if (isComplete)
		 {
			 currentPosition() = currentP;
			 lastPosition() = LastP;
		 }
		 else
		 {
			 printf("报文不完整或错误：请检查报文格式\n");
		 }








}


void FORTE_MsgpParse::enterStateSTART(void){
  m_nECCState = scm_nStateSTART;
}

void FORTE_MsgpParse::enterStatemsgParse(void){
  m_nECCState = scm_nStatemsgParse;
  alg_parseOperation();
  sendOutputEvent( scm_nEventCNFID);
}

void FORTE_MsgpParse::executeEvent(int pa_nEIID){
  bool bTransitionCleared;
  do{
    bTransitionCleared = true;
    switch(m_nECCState){
      case scm_nStateSTART:
        if(scm_nEventREQID == pa_nEIID)
          enterStatemsgParse();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStatemsgParse:
        if(1)
          enterStateSTART();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      default:
      DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 1.", m_nECCState.operator TForteUInt16 ());
        m_nECCState = 0; //0 is always the initial state
        break;
    }
    pa_nEIID = cg_nInvalidEventID;  // we have to clear the event after the first check in order to ensure correct behavior
  }while(bTransitionCleared);
}


