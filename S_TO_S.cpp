/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: S_TO_S
 *** Description: Tamplate for a simple Basic Function Block Type
 *** Version: 
 ***     0.0: 2018-07-30/4DIAC-IDE - 4DIAC-Consortium - 
 ***     1.0: 2016-05-26/AZ - fortiss GmbH - 
 *************************************************************************/

#include "S_TO_S.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "S_TO_S_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_S_TO_S, g_nStringIdS_TO_S)

const CStringDictionary::TStringId FORTE_S_TO_S::scm_anDataInputNames[] = {g_nStringIdQI};

const CStringDictionary::TStringId FORTE_S_TO_S::scm_anDataInputTypeIds[] = {g_nStringIdSTRING};

const CStringDictionary::TStringId FORTE_S_TO_S::scm_anDataOutputNames[] = {g_nStringIdQO};

const CStringDictionary::TStringId FORTE_S_TO_S::scm_anDataOutputTypeIds[] = {g_nStringIdSTRING};

const TForteInt16 FORTE_S_TO_S::scm_anEIWithIndexes[] = {0};
const TDataIOID FORTE_S_TO_S::scm_anEIWith[] = {0, 255};
const CStringDictionary::TStringId FORTE_S_TO_S::scm_anEventInputNames[] = {g_nStringIdREQ};

const TDataIOID FORTE_S_TO_S::scm_anEOWith[] = {0, 255};
const TForteInt16 FORTE_S_TO_S::scm_anEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_S_TO_S::scm_anEventOutputNames[] = {g_nStringIdCNF};

const SFBInterfaceSpec FORTE_S_TO_S::scm_stFBInterfaceSpec = {
  1,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  1,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  1,  scm_anDataInputNames, scm_anDataInputTypeIds,
  1,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};

void FORTE_S_TO_S::alg_initialize(void){

QO() = "";
}

void FORTE_S_TO_S::alg_normalOperation(void){
QO() = QI();




}


void FORTE_S_TO_S::enterStateSTART(void){
  m_nECCState = scm_nStateSTART;
}

void FORTE_S_TO_S::enterStateNormalOp(void){
  m_nECCState = scm_nStateNormalOp;
  alg_normalOperation();
  sendOutputEvent( scm_nEventCNFID);
  alg_initialize();
}

void FORTE_S_TO_S::executeEvent(int pa_nEIID){
  bool bTransitionCleared;
  do{
    bTransitionCleared = true;
    switch(m_nECCState){
      case scm_nStateSTART:
        if(scm_nEventREQID == pa_nEIID)
          enterStateNormalOp();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateNormalOp:
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


