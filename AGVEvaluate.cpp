/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: AGVEvaluate
 *** Description: Tamplate for a simple Basic Function Block Type
 *** Version: 
 ***     0.0: 2018-03-27/4DIAC-IDE - 4DIAC-Consortium - 
 ***     1.0: 2016-05-26/AZ - fortiss GmbH - 
 *************************************************************************/

#include "AGVEvaluate.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "AGVEvaluate_gen.cpp"
#endif
#include"Dijkstra.h"


#include <stdio.h>  
#include <cmath>   
#include <string.h>  
#include <algorithm>  

#include "stdlib.h"
#include <time.h> 
DEFINE_FIRMWARE_FB(FORTE_AGVEvaluate, g_nStringIdAGVEvaluate)

const CStringDictionary::TStringId FORTE_AGVEvaluate::scm_anDataInputNames[] = {g_nStringIdcurrentPosition, g_nStringIdBeginEndPosition, g_nStringIdLengthAndWeight, g_nStringIdstate};

const CStringDictionary::TStringId FORTE_AGVEvaluate::scm_anDataInputTypeIds[] = {g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdBOOL};

const CStringDictionary::TStringId FORTE_AGVEvaluate::scm_anDataOutputNames[] = {g_nStringIdvalue};

const CStringDictionary::TStringId FORTE_AGVEvaluate::scm_anDataOutputTypeIds[] = {g_nStringIdSTRING};

const TForteInt16 FORTE_AGVEvaluate::scm_anEIWithIndexes[] = {0, 4};
const TDataIOID FORTE_AGVEvaluate::scm_anEIWith[] = {0, 1, 2, 255, 3, 255};
const CStringDictionary::TStringId FORTE_AGVEvaluate::scm_anEventInputNames[] = {g_nStringIdREQ, g_nStringIdCurrentState};

const TDataIOID FORTE_AGVEvaluate::scm_anEOWith[] = {0, 255};
const TForteInt16 FORTE_AGVEvaluate::scm_anEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_AGVEvaluate::scm_anEventOutputNames[] = {g_nStringIdCNF};

const CStringDictionary::TStringId FORTE_AGVEvaluate::scm_anInternalsNames[] = {g_nStringIdcurrentTime, g_nStringIdLastTime};

const CStringDictionary::TStringId FORTE_AGVEvaluate::scm_anInternalsTypeIds[] = {g_nStringIdDINT, g_nStringIdDINT};

const SFBInterfaceSpec FORTE_AGVEvaluate::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  1,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  4,  scm_anDataInputNames, scm_anDataInputTypeIds,
  1,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


const SInternalVarsInformation FORTE_AGVEvaluate::scm_stInternalVars = {2, scm_anInternalsNames, scm_anInternalsTypeIds};



void FORTE_AGVEvaluate::alg_stateTran(void){
	if (state() == true) {//system busy
		currentTime() = 0;
		LastTime() = 0;
	}
	else {
		LastTime() = clock();
	}

}

void FORTE_AGVEvaluate::alg_calculateValue(void){
	ArrayGraph *myGraph1;
	/*char *currentPositionr = currentPosition().getValue();*/
	int position = atoi(currentPosition().getValue());
	int m;
	int n;

	char* recvMsg = LengthAndWeight().getValue();

	char temp1[5];
	char temp2[5];
	int i = 0, j = 0;
	/*while (*recvMsg && *recvMsg++ != '_');
	while (*recvMsg && *recvMsg != '_') temp1[i++] = *recvMsg++;
	*recvMsg++;
	while (*recvMsg && *recvMsg != '+') temp2[j++] = *recvMsg++;*/

	do { temp1[i++] = *recvMsg; } while (*recvMsg && *recvMsg++ != '_');
	while (*recvMsg) temp2[j++] = *recvMsg++;

	temp1[i] = '\0';
	temp2[j] = '\0';

	m = atoi(temp1);
	n = atoi(temp2);
	//printf("m=%d,n=%d\n",m,n);
	int begin;
	int end;

	char* recvMsg2 = BeginEndPosition().getValue();
	char temp3[5];
	char temp4[5];
	i = 0;
	j = 0;
	do { temp3[i++] = *recvMsg2; } while (*recvMsg2 && *recvMsg2++ != '_');
	while (*recvMsg2) temp4[j++] = *recvMsg2++;

	temp3[i] = '\0';
	temp4[j] = '\0';

	begin = atoi(temp3);
	end = atoi(temp4);

	myGraph1 = new ArrayGraph(m, n);
	map<int, Tpoint> AGVmap;
	AGVmap = myGraph1->getvertexMap();


	char str_int[80];
	char str_double[30];
	int x1, x2, x3, y1, y2, y3;
	int  mahattanDistance1, mahattanDistance2, mahattanDistanceTotal;
	double WaitTime;

	if (state() == true) {//system busy
		value() = "busy";
	}
	else {

		currentTime() = clock();
		WaitTime = currentTime() - LastTime();

		x1 = AGVmap[position].getX();
		y1 = AGVmap[position].getY();
		//printf("x1 = : %d\n", x1);
		//printf("y1 = : %d\n", y1);

		x2 = AGVmap[begin].getX();
		y2 = AGVmap[begin].getY();
		//printf("x2 = : %d\n", x2);
		//printf("y2 = : %d\n", y2);

		x3 = AGVmap[end].getX();
		y3 = AGVmap[end].getY();
		//printf("x3 = : %d\n", x3);
		//printf("y3 = : %d\n", y3);


		mahattanDistance1 = abs(x1 - x2) + abs(y1 - y2);
		//printf("Current position to targetbegin Position:mahattanDistance = %d \n", mahattanDistance1);
		mahattanDistance2 = abs(x2 - x3) + abs(y2 - y3);
		//printf("Targetbegin Position to TargetEnd Position:mahattanDistance = %d \n", mahattanDistance2);

		mahattanDistanceTotal = mahattanDistance1 + mahattanDistance2;
		sprintf(str_int, "%d", mahattanDistanceTotal);
		//itoa(mahattanDistanceTotal, str_int, 10);
		gcvt(WaitTime / 1000, 5, str_double);
		strcat(str_int, "+");
		strcat(str_int, str_double);
		value() = str_int;
		//printf("The value is : %s \n", str_int);



	}
}


void FORTE_AGVEvaluate::enterStateSTART(void){
  m_nECCState = scm_nStateSTART;
}

void FORTE_AGVEvaluate::enterStateState(void){
  m_nECCState = scm_nStateState;
  alg_stateTran();
}

void FORTE_AGVEvaluate::enterStatevalueCalculation(void){
  m_nECCState = scm_nStatevalueCalculation;
  alg_calculateValue();
  sendOutputEvent( scm_nEventCNFID);
}

void FORTE_AGVEvaluate::executeEvent(int pa_nEIID){
  bool bTransitionCleared;
  do{
    bTransitionCleared = true;
    switch(m_nECCState){
      case scm_nStateSTART:
        if(scm_nEventCurrentStateID == pa_nEIID)
          enterStateState();
        else
        if(scm_nEventREQID == pa_nEIID)
          enterStatevalueCalculation();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateState:
        if(1)
          enterStateSTART();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStatevalueCalculation:
        if(1)
          enterStateSTART();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      default:
      DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 2.", m_nECCState.operator TForteUInt16 ());
        m_nECCState = 0; //0 is always the initial state
        break;
    }
    pa_nEIID = cg_nInvalidEventID;  // we have to clear the event after the first check in order to ensure correct behavior
  }while(bTransitionCleared);
}


