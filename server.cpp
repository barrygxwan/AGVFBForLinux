/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: server
 *** Description: Tamplate for a simple Basic Function Block Type
 *** Version: 
 ***     0.0: 2018-06-06/4DIAC-IDE - 4DIAC-Consortium - 
 ***     1.0: 2016-05-26/AZ - fortiss GmbH - 
 *************************************************************************/


#include "server.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "server_gen.cpp"
#endif




DEFINE_FIRMWARE_FB(FORTE_server, g_nStringIdserver)

const CStringDictionary::TStringId FORTE_server::scm_anDataInputNames[] = {g_nStringIdQI, g_nStringIdID, g_nStringIdPort, g_nStringIdSD};

const CStringDictionary::TStringId FORTE_server::scm_anDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING};

const CStringDictionary::TStringId FORTE_server::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdRD};

const CStringDictionary::TStringId FORTE_server::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdSTRING};

const TForteInt16 FORTE_server::scm_anEIWithIndexes[] = {0, 4};
const TDataIOID FORTE_server::scm_anEIWith[] = {0, 1, 2, 255, 0, 3, 255};
const CStringDictionary::TStringId FORTE_server::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdRSP};

const TDataIOID FORTE_server::scm_anEOWith[] = {0, 1, 255, 0, 1, 2, 255};
const TForteInt16 FORTE_server::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_server::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_server::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  4,  scm_anDataInputNames, scm_anDataInputTypeIds,
  3,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};






void FORTE_server::alg_initialize(void){
	memset(&sockaddr,0,sizeof(sockaddr));
	
	
	char *ip = ID().getValue();
	int port = atoi(Port().getValue());

	//addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//ip地址
	//serverAddr.sin_port = htons(port);
	//serverAddr.sin_addr.S_un.S_addr = inet_addr(ip);

	//bind(socketSer, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	//listen(socketSer, 5);
	
		 sockaddr.sin_family = AF_INET;
	 //sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
         sockaddr.sin_addr.s_addr = inet_addr(ip);
	 sockaddr.sin_port = htons(port);
       
	 listenfd = socket(AF_INET,SOCK_STREAM,0);

	 bind(listenfd,(struct sockaddr *) &sockaddr,sizeof(sockaddr));
	 
         
	 listen(listenfd,1024);

	 
	 printf("Please wait for the client information\n");
	
	
	
	
	
	
	
	

	QO() = QI();
	STATUS() = "waiting for connect";


	 while(true)
	{
		if((connfd = accept(listenfd,(struct sockaddr*)NULL,NULL))>=0)
		 {
			printf("Socket success!");
			STATUS() = "Socket success";
			break;
		 }
	}
         
        
         flags = fcntl(connfd,F_GETFL,0);
	 fcntl(connfd,F_SETFL,flags|O_NONBLOCK);//设置为非阻塞

	

}

void FORTE_server::alg_deInitialize(void){

QO() = false;
}

void FORTE_server::alg_SendMSG(void){

	char *sendBuf = (char*)malloc(100* sizeof(char));//发送数据

	sendBuf = SD().getValue();
	send(connfd, sendBuf, strlen(sendBuf) + 1, 0);
	printf("send is OK!");
	
	SD() = "";
}

void FORTE_server::alg_RecvMSG(void){

	int ret = recv(connfd, buff, sizeof(buff), 0);
	if (ret >= 2)
	{
		buff[ret] = '\0';
		printf("%s\n", buff);
		//send(Command_Sock, buff, strlen(buff), 0);
		RD() = buff;
		sendOutputEvent(scm_nEventCNFID);
	}

}


void FORTE_server::enterStateSTART(void){
  m_nECCState = scm_nStateSTART;
}

void FORTE_server::enterStateInit(void){
  m_nECCState = scm_nStateInit;
  alg_initialize();
  sendOutputEvent( scm_nEventINITOID);
}

void FORTE_server::enterStateSend(void){
  m_nECCState = scm_nStateSend;
  alg_SendMSG();
}

void FORTE_server::enterStateInitialized(void){
  m_nECCState = scm_nStateInitialized;
}

void FORTE_server::enterStateDeInit(void){
  m_nECCState = scm_nStateDeInit;
  alg_deInitialize();
  sendOutputEvent( scm_nEventINITOID);
}

void FORTE_server::enterStateRev(void){
  m_nECCState = scm_nStateRev;
  alg_RecvMSG();
  
}

void FORTE_server::executeEvent(int pa_nEIID){
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
      case scm_nStateSend:
        if(1)
          enterStateInitialized();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateInitialized:
        if(scm_nEventRSPID == pa_nEIID)
          enterStateSend();
        else
        if((scm_nEventINITID == pa_nEIID) && ((false == QI())))
          enterStateDeInit();
        else
        if(SD() == "")
          enterStateRev();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateDeInit:
        if(1)
          enterStateSTART();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateRev:
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


