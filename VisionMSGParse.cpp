/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: VisionMSGParse
 *** Description: Tamplate for a simple Basic Function Block Type
 *** Version: 
 ***     0.0: 2018-07-25/4DIAC-IDE - 4DIAC-Consortium - 
 ***     1.0: 2016-05-26/AZ - fortiss GmbH - 
 *************************************************************************/
#include <stdio.h>
#include "VisionMSGParse.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "VisionMSGParse_gen.cpp"
#endif


DEFINE_FIRMWARE_FB(FORTE_VisionMSGParse, g_nStringIdVisionMSGParse)

const CStringDictionary::TStringId FORTE_VisionMSGParse::scm_anDataInputNames[] = { g_nStringIdMassageIn };

const CStringDictionary::TStringId FORTE_VisionMSGParse::scm_anDataInputTypeIds[] = { g_nStringIdSTRING };

const CStringDictionary::TStringId FORTE_VisionMSGParse::scm_anDataOutputNames[] = { g_nStringIdpositionLabel, g_nStringIdposition_x, g_nStringIdposition_y, g_nStringIdposition_x_y };

const CStringDictionary::TStringId FORTE_VisionMSGParse::scm_anDataOutputTypeIds[] = { g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING };

const TForteInt16 FORTE_VisionMSGParse::scm_anEIWithIndexes[] = { 0 };
const TDataIOID FORTE_VisionMSGParse::scm_anEIWith[] = { 0, 255 };
const CStringDictionary::TStringId FORTE_VisionMSGParse::scm_anEventInputNames[] = { g_nStringIdREQ };

const TDataIOID FORTE_VisionMSGParse::scm_anEOWith[] = { 0, 1, 2, 3, 255 };
const TForteInt16 FORTE_VisionMSGParse::scm_anEOWithIndexes[] = { 0, -1 };
const CStringDictionary::TStringId FORTE_VisionMSGParse::scm_anEventOutputNames[] = { g_nStringIdCNF };

const CStringDictionary::TStringId FORTE_VisionMSGParse::scm_anInternalsNames[] = { g_nStringIdlastPositionLabel };

const CStringDictionary::TStringId FORTE_VisionMSGParse::scm_anInternalsTypeIds[] = { g_nStringIdSTRING };

const SFBInterfaceSpec FORTE_VisionMSGParse::scm_stFBInterfaceSpec = {
	1,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
	1,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  1,  scm_anDataInputNames, scm_anDataInputTypeIds,
	4,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
	0, 0
};


const SInternalVarsInformation FORTE_VisionMSGParse::scm_stInternalVars = { 1, scm_anInternalsNames, scm_anInternalsTypeIds };

void FORTE_VisionMSGParse::alg_normalOperation(void){
	char* recvMsg = MassageIn().getValue();
	char Head[6];
	char Vehicle[8];
	char P_x[10];
	char P_y[10];
	char End[5];
	char P_x_y[50];
	int index = 0;
	int i = 0;
	bool isComplete = false;

	//Head+Vehicle_Px_Py+End
	//检查报文完整性
	while (*recvMsg&&*recvMsg != '+')//TM
	{
		if (index > 6)
		{
			//printf("报文不完整");
			isComplete = false;
			break;
		}
		else
		{
			Head[index++] = *recvMsg++;
		}

	}
	Head[index] = '\0';
	*recvMsg++;

	index = 0;
	while ((strcmp(Head, "Head") == 0) && *recvMsg&&*recvMsg != '_')//TM
	{
		if (index >8)
		{
			// printf("报文不完整");
			isComplete = false;
			break;
		}
		else
		{
			Vehicle[index++] = *recvMsg++;
		}

	}
	Vehicle[index] = '\0';
	*recvMsg++;
	index = 0;
	while ((strcmp(Head, "Head") == 0) && *recvMsg&&*recvMsg != '_')//TM
	{
		if (index >10)
		{
			// printf("报文不完整");
			isComplete = false;
			break;
		}
		else
		{
			P_x[index++] = *recvMsg++;
		}

	}
	P_x[index] = '\0';
	*recvMsg++;
	index = 0;
	while ((strcmp(Head, "Head") == 0) && *recvMsg&&*recvMsg != '+')//TM
	{
		if (index >10)
		{
			// printf("报文不完整");
			isComplete = false;
			break;
		}
		else
		{
			P_y[index++] = *recvMsg++;
		}

	}
	P_y[index] = '\0';
	*recvMsg++;



	index = 0;
	while ((strcmp(Head, "Head") == 0) && *recvMsg)//END判断
	{

		if (index >= 4)
		{
			// printf("报文不完整");
			isComplete = false;
			break;
		}
		else
		{
			End[index++] = *recvMsg++;
		}

	}
	End[index] = '\0';
	index = 0;
	if ((strcmp(Head, "Head") == 0) && (strcmp(End, "End") == 0))
	{
		// printf("报文完整\n");
		isComplete = true;
	}
	if (isComplete)
	{
		position_x() = P_x;
		position_y() = P_y;
		strcpy(P_x_y, P_x);
		strcat(P_x_y,"_");
		strcat(P_x_y, P_y);
		position_x_y() = P_x_y;
		//label处理判断
		char str_label[30];
         printf("current position:%s \n",P_x_y);
		
		for (int j = 0; j < 64; j++)
		{
			if ((atoi(P_x) - X[j])*(atoi(P_x) - X[j]) + (atoi(P_y) - Y[j])*(atoi(P_y) - Y[j]) <= Radius*Radius)
			{
			    //itoa(j, str_label, 10);
				sprintf(str_label,"%d",j);
				positionLabel() = str_label;

				/*if (lastPositionLabel()!= positionLabel())
				{
                 

				}
				  lastPositionLabel() = str_label;
*/
				
				break;
			}
		}


	}
	else
	{
		//printf("报文不完整或错误：请检查报文格式\n");
	}


}


void FORTE_VisionMSGParse::enterStateSTART(void){
  m_nECCState = scm_nStateSTART;
}

void FORTE_VisionMSGParse::enterStateNormalOp(void){
  m_nECCState = scm_nStateNormalOp;
  alg_normalOperation();
  sendOutputEvent( scm_nEventCNFID);
}

void FORTE_VisionMSGParse::executeEvent(int pa_nEIID){
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


