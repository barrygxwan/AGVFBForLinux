/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: client
 *** Description: Tamplate for a simple Basic Function Block Type
 *** Version: 
 ***     0.0: 2018-01-28/4DIAC-IDE - 4DIAC-Consortium - 
 ***     1.0: 2016-05-26/AZ - fortiss GmbH - 
 *************************************************************************/

#include "client.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "client_gen.cpp"
#endif

#include <stdio.h>
#include <sys/types.h>    
#include <sys/socket.h>  
#include <arpa/inet.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#include <netinet/in.h>  
#include <errno.h>  


#include "client.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "client_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_client, g_nStringIdclient)

const CStringDictionary::TStringId FORTE_client::scm_anDataInputNames[] = {g_nStringIdIP, g_nStringIdPORT, g_nStringIdID, g_nStringIdCONNECTTIME, g_nStringIdCHECKTIME, g_nStringIdQI};

const CStringDictionary::TStringId FORTE_client::scm_anDataInputTypeIds[] = {g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdTIME, g_nStringIdTIME, g_nStringIdSTRING};

const CStringDictionary::TStringId FORTE_client::scm_anDataOutputNames[] = {g_nStringIdRESULT, g_nStringIdQO};

const CStringDictionary::TStringId FORTE_client::scm_anDataOutputTypeIds[] = {g_nStringIdSTRING, g_nStringIdSTRING};

const TForteInt16 FORTE_client::scm_anEIWithIndexes[] = {0, 6};
const TDataIOID FORTE_client::scm_anEIWith[] = {0, 1, 2, 3, 4, 255, 5, 255};
const CStringDictionary::TStringId FORTE_client::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdSEND};

const TDataIOID FORTE_client::scm_anEOWith[] = {0, 255, 1, 255};
const TForteInt16 FORTE_client::scm_anEOWithIndexes[] = {-1, 0, 2, -1};
const CStringDictionary::TStringId FORTE_client::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdSTATE, g_nStringIdRECEIVED};

const CStringDictionary::TStringId FORTE_client::scm_anInternalsNames[] = {g_nStringIdISCONNECT, g_nStringIdISNOTICE};

const CStringDictionary::TStringId FORTE_client::scm_anInternalsTypeIds[] = {g_nStringIdBOOL, g_nStringIdBOOL};

const SAdapterInstanceDef FORTE_client::scm_astAdapterInstances[] = {
{g_nStringIdATimeOut, g_nStringIdConnectTimeOut, true },
{g_nStringIdATimeOut, g_nStringIdCheckTimeOut, true }};

const SFBInterfaceSpec FORTE_client::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  3,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  6,  scm_anDataInputNames, scm_anDataInputTypeIds,
  2,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  2,scm_astAdapterInstances};


const SInternalVarsInformation FORTE_client::scm_stInternalVars = {2, scm_anInternalsNames, scm_anInternalsTypeIds};

//int cli_sockfd;/*客户端SOCKET */
//int addrlen;        
//struct sockaddr_in ser_addr,/* 服务器的地址*/  cli_addr;/* 客户端的地址*/    

//char * sendMsg = (char *)malloc(1024);
//char receiveMsg[1024];

void FORTE_client::setInitialValues(){
  ISCONNECT() = false;
  ISNOTICE() = false;
}

void FORTE_client::alg_Connect(void){
    ISCONNECT() = true;
    bool flag = true;
    char * result = (char*) malloc(128);

    char * seraddr = IP().getValue();
    int port = atoi(PORT().getValue());

    cli_sockfd=socket(AF_INET,SOCK_STREAM,0);/*创建连接的SOCKET */    
    
    if(cli_sockfd<0){/*创建失败 */   
        ISCONNECT() = false;
        bool flag = false; 
        result = strerror(errno);

        fprintf(stderr,"socker Error:%s\n",strerror(errno));    
    }    
    /* 初始化客户端地址*/    
    addrlen=sizeof(struct sockaddr_in);    
    bzero(&ser_addr,addrlen);    
    cli_addr.sin_family=AF_INET;    
    cli_addr.sin_addr.s_addr=htonl(INADDR_ANY);    
    cli_addr.sin_port=0;    
    if(bind(cli_sockfd,(struct sockaddr*)&cli_addr,addrlen)<0){    
        /*绑定失败 */   
	ISCONNECT() = false;
        bool flag = false; 
        result = strerror(errno);
 
        fprintf(stderr,"Bind Error:%s\n",strerror(errno));    
    }    
    /* 初始化服务器地址*/    
    addrlen=sizeof(struct sockaddr_in);    
    bzero(&ser_addr,addrlen);    
    ser_addr.sin_family=AF_INET;    
    ser_addr.sin_addr.s_addr=inet_addr(seraddr);    
    ser_addr.sin_port=htons(port);    
    if(connect(cli_sockfd,(struct sockaddr*)&ser_addr, addrlen)!=0)/*请求连接*/    
    {    
        /*连接失败 */    
	   ISCONNECT() = false;
        bool flag = false; 
        result = strerror(errno);

	    fprintf(stderr,"Connect Error:%s\n",seraddr); 
        fprintf(stderr,"Connect Error:%s\n",strerror(errno));    
        close(cli_sockfd);    
     

    if(flag) {
	RESULT() = "Connection Success!";
    }
    else {
	RESULT() = result;
    }
}
}

void FORTE_client::alg_Send(void){
    //fprintf(stderr,"%s\n", "ready to send");
    sendMsg = QI().getValue();
    fprintf(stderr,"%s\n", sendMsg);
    send(cli_sockfd, sendMsg, strlen(sendMsg),MSG_DONTWAIT);/*发送数据*/
    //fprintf(stderr,"%s\n", "sended");

   QI() = "";
}

void FORTE_client::alg_Receive(void){
    //fprintf(stderr,"%s\n", "ready to receive");

    ISNOTICE() = false;

    memset(receiveMsg, 0, sizeof(receiveMsg));
    recv(cli_sockfd, receiveMsg, 1024,MSG_DONTWAIT);

    //fprintf(stderr,"%s\n", receiveMsg);

    if(receiveMsg != "" && receiveMsg[0] != '\0') {
	//fprintf(stderr,"%s\n", "notice");
	ISNOTICE() = true;
	QO() = receiveMsg;
    }

    //sleep(1);
}

void FORTE_client::alg_Sleep(void){
    sleep(3);
}

void FORTE_client::alg_SendID(void){
    sendMsg = ID().getValue();
	fprintf(stderr,"%s\n", sendMsg);
    send(cli_sockfd, sendMsg, strlen(sendMsg),MSG_DONTWAIT);/*发送数据*/
}


void FORTE_client::alg_SetConnectTimeOut(void){
ConnectTimeOut().DT() = CONNECTTIME();
}

void FORTE_client::alg_SetCheckTimeOut(void){
CheckTimeOut().DT() = CHECKTIME();
}


void FORTE_client::enterStateSTART(void){
  m_nECCState = scm_nStateSTART;
}

void FORTE_client::enterStateInit(void){
  m_nECCState = scm_nStateInit;
}

void FORTE_client::enterStateIdle(void){
  m_nECCState = scm_nStateIdle;
}

void FORTE_client::enterStateSend(void){
  m_nECCState = scm_nStateSend;
  alg_Send();
}

void FORTE_client::enterStateReceive(void){
  m_nECCState = scm_nStateReceive;
  alg_Receive();
}

void FORTE_client::enterStateSuccess(void){
  m_nECCState = scm_nStateSuccess;
  sendOutputEvent( scm_nEventINITOID);
}

void FORTE_client::enterStateConnecting(void){
  m_nECCState = scm_nStateConnecting;
  alg_Connect();
  sendOutputEvent( scm_nEventSTATEID);
}

void FORTE_client::enterStatePending(void){
  m_nECCState = scm_nStatePending;
  alg_SetCheckTimeOut();
  sendAdapterEvent(scm_nCheckTimeOutAdpNum, FORTE_ATimeOut::scm_nEventSTARTID);
}

void FORTE_client::enterStateNotice(void){
  m_nECCState = scm_nStateNotice;
  sendOutputEvent( scm_nEventRECEIVEDID);
}

void FORTE_client::enterStateFail(void){
  m_nECCState = scm_nStateFail;
  alg_SetConnectTimeOut();
  sendAdapterEvent(scm_nConnectTimeOutAdpNum, FORTE_ATimeOut::scm_nEventSTARTID);
}

void FORTE_client::enterStateIdentify(void){
  m_nECCState = scm_nStateIdentify;
  alg_SendID();
}

void FORTE_client::enterStateJudging(void){
  m_nECCState = scm_nStateJudging;
  alg_SetCheckTimeOut();
  sendAdapterEvent(scm_nCheckTimeOutAdpNum, FORTE_ATimeOut::scm_nEventSTARTID);
}

void FORTE_client::executeEvent(int pa_nEIID){
  bool bTransitionCleared;
  do{
    bTransitionCleared = true;
    switch(m_nECCState){
      case scm_nStateSTART:
        if(scm_nEventINITID == pa_nEIID)
          enterStateInit();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateInit:
        if(1)
          enterStateConnecting();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateIdle:
        if(QI() == "")
          enterStateReceive();
        else
         if(!((QI() == "")))
          enterStateJudging();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateSend:
        if(1)
          enterStateIdle();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateReceive:
        if(1)
          enterStatePending();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateSuccess:
        if(1)
          enterStateIdentify();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateConnecting:
        if(ISCONNECT() == true)
          enterStateSuccess();
        else
        if(ISCONNECT() == false)
          enterStateFail();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStatePending:
        if((CheckTimeOut().TimeOut() == pa_nEIID) && ((ISNOTICE() == true)))
          enterStateNotice();
        else
        if((CheckTimeOut().TimeOut() == pa_nEIID) && ((ISNOTICE() == false)))
          enterStateIdle();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateNotice:
        if(1)
          enterStateIdle();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateFail:
        if(ConnectTimeOut().TimeOut() == pa_nEIID)
          enterStateConnecting();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateIdentify:
        if(1)
          enterStateIdle();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateJudging:
        if(CheckTimeOut().TimeOut() == pa_nEIID)
          enterStateSend();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      default:
      DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 11.", m_nECCState.operator TForteUInt16 ());
        m_nECCState = 0; //0 is always the initial state
        break;
    }
    pa_nEIID = cg_nInvalidEventID;  // we have to clear the event after the first check in order to ensure correct behavior
  }while(bTransitionCleared);
}