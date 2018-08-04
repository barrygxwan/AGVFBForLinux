/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: TaskCenterMSGParse
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     0.0: 2018-06-21/4DIAC-IDE - 4DIAC-Consortium - 
 *************************************************************************/

#include "TaskCenterMSGParse.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "TaskCenterMSGParse_gen.cpp"
#endif
#include <stdio.h>

DEFINE_FIRMWARE_FB(FORTE_TaskCenterMSGParse, g_nStringIdTaskCenterMSGParse)

const CStringDictionary::TStringId FORTE_TaskCenterMSGParse::scm_anDataInputNames[] = { g_nStringIdQI, g_nStringIdPARAMS };

const CStringDictionary::TStringId FORTE_TaskCenterMSGParse::scm_anDataInputTypeIds[] = { g_nStringIdBOOL, g_nStringIdSTRING };

const CStringDictionary::TStringId FORTE_TaskCenterMSGParse::scm_anDataOutputNames[] = { g_nStringIdQO, g_nStringIdTaskNum, g_nStringIdmapMSG, g_nStringIdTaskMSG };

const CStringDictionary::TStringId FORTE_TaskCenterMSGParse::scm_anDataOutputTypeIds[] = { g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING };

const TForteInt16 FORTE_TaskCenterMSGParse::scm_anEIWithIndexes[] = { 0, 3 };
const TDataIOID FORTE_TaskCenterMSGParse::scm_anEIWith[] = { 0, 1, 255, 0, 1, 255 };
const CStringDictionary::TStringId FORTE_TaskCenterMSGParse::scm_anEventInputNames[] = { g_nStringIdINIT, g_nStringIdREQ };

const TDataIOID FORTE_TaskCenterMSGParse::scm_anEOWith[] = { 0, 255, 0, 3, 1, 2, 255, 3, 1, 255, 0, 2, 255 };
const TForteInt16 FORTE_TaskCenterMSGParse::scm_anEOWithIndexes[] = { 0, 2, 7, 10, -1 };
const CStringDictionary::TStringId FORTE_TaskCenterMSGParse::scm_anEventOutputNames[] = { g_nStringIdINITO, g_nStringIdEvaluate, g_nStringIdTask, g_nStringIdMAP };

const SFBInterfaceSpec FORTE_TaskCenterMSGParse::scm_stFBInterfaceSpec = {
	2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
	4,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  2,  scm_anDataInputNames, scm_anDataInputTypeIds,
	4,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
	0, 0
};



void FORTE_TaskCenterMSGParse::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventINITID:
	{
		QO() = QI();
		sendOutputEvent(scm_nEventINITOID);
	}
      break;
    case scm_nEventREQID:
	{
		if (true == QI())
		{
			char* recvMsg = PARAMS().getValue();
			char TM[4];
			char object[10];
			char taskNum[10];
			char taskMsg[20];
			char End[5];
			int i = 0, TMindex = 0, objectindex = 0, taskNumindex = 0,taskMsgindex = 0, Endindex = 0;
			bool isComplete = false;
			//TM + MAP +  map_Length_Weight +End
			//检查报文完整性
			while (*recvMsg&&*recvMsg != '+')//TM
			{
				if (TMindex >= 4)
				{
					//printf("报文不完整");
					isComplete = false;
					break;
				}
				else
				{
					TM[TMindex++] = *recvMsg++;
				}

			}
			TM[TMindex] = '\0';
			*recvMsg++;
			while ((strcmp(TM, "TM") == 0) && *recvMsg && *recvMsg != '+')//对象判断
			{

				if (objectindex >= 10)
				{
					//printf("报文不完整");
					isComplete = false;
					break;
				}
				else
				{
					object[objectindex++] = *recvMsg++;
				}

			}
			object[objectindex] = '\0';
			*recvMsg++;

			while ((strcmp(TM, "TM") == 0) && *recvMsg && *recvMsg != '+')//对象判断
			{

				if (taskNumindex >= 10)
				{
					//printf("报文不完整");
					isComplete = false;
					break;
				}
				else
				{
					taskNum[taskNumindex++] = *recvMsg++;
				}

			}
			taskNum[taskNumindex] = '\0';
			*recvMsg++;


			while ((strcmp(TM, "TM") == 0) && *recvMsg && *recvMsg++ != '_');
			while ((strcmp(TM, "TM") == 0) && *recvMsg && *recvMsg!= '+')//对象判断
			{

				if (taskMsgindex >= 10)
				{
					//printf("报文不完整");
					isComplete = false;
					break;
				}
				else
				{
					taskMsg[taskMsgindex++] = *recvMsg++;
				}

			}
			taskMsg[taskMsgindex] = '\0';
			*recvMsg++;






			while ((strcmp(TM, "TM") == 0) && *recvMsg)//END判断
			{

				if (Endindex >= 4)
				{
					//printf("报文不完整");
					isComplete = false;
					break;
				}
				else
				{
					End[Endindex++] = *recvMsg++;
				}

			}
			End[Endindex] = '\0';

			if ((strcmp(TM, "TM") == 0) && (strcmp(End, "End") == 0))
			{
				printf("报文完整");
				isComplete = true;
			}
			if (isComplete)
			{


				if ((strcmp(object, "VVVV") == 0))
				{


					TaskNum() = taskNum;
					TaskMSG() = taskMsg;
					sendOutputEvent(scm_nEventEvaluateID);
				}
				else if ((strcmp(object, "MAP") == 0))
				{
					TaskNum() = taskNum;
					mapMSG() = taskMsg;
					sendOutputEvent(scm_nEventMAPID);

				}
				else
				{
					TaskNum() = taskNum;
					TaskMSG() = taskMsg;
					sendOutputEvent(scm_nEventTaskID);
				}
			}
			else
			{
				printf("报文不完整或错误：请检查报文格式\n");
			}
		}

	}
      break;
  }
}



