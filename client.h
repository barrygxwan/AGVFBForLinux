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

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <basicfb.h>
#include <forte_bool.h>
#include <forte_string.h>
#include <forte_time.h>
#include "ATimeOut.h"


#include <stdio.h>
#include <sys/types.h>    
#include <sys/socket.h>  
#include <arpa/inet.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#include <netinet/in.h>  
#include <errno.h> 
class FORTE_client: public CBasicFB{
  DECLARE_FIRMWARE_FB(FORTE_client)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_STRING &IP() {
    return *static_cast<CIEC_STRING*>(getDI(0));
  };

  CIEC_STRING &PORT() {
    return *static_cast<CIEC_STRING*>(getDI(1));
  };

  CIEC_STRING &ID() {
    return *static_cast<CIEC_STRING*>(getDI(2));
  };

  CIEC_TIME &CONNECTTIME() {
    return *static_cast<CIEC_TIME*>(getDI(3));
  };

  CIEC_TIME &CHECKTIME() {
    return *static_cast<CIEC_TIME*>(getDI(4));
  };

  CIEC_STRING &QI() {
    return *static_cast<CIEC_STRING*>(getDI(5));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_STRING &RESULT() {
    return *static_cast<CIEC_STRING*>(getDO(0));
  };

  CIEC_STRING &QO() {
    return *static_cast<CIEC_STRING*>(getDO(1));
  };

  static const TEventID scm_nEventINITID = 0;
  static const TEventID scm_nEventSENDID = 1;
  static const TForteInt16 scm_anEIWithIndexes[];
  static const TDataIOID scm_anEIWith[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];

  static const TEventID scm_nEventINITOID = 0;
  static const TEventID scm_nEventSTATEID = 1;
  static const TEventID scm_nEventRECEIVEDID = 2;
  static const TForteInt16 scm_anEOWithIndexes[];
  static const TDataIOID scm_anEOWith[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];

  static const CStringDictionary::TStringId scm_anInternalsNames[];
  static const CStringDictionary::TStringId scm_anInternalsTypeIds[];
  CIEC_BOOL &ISCONNECT() {
    return *static_cast<CIEC_BOOL*>(getVarInternal(0));
  };

  CIEC_BOOL &ISNOTICE() {
    return *static_cast<CIEC_BOOL*>(getVarInternal(1));
  };

  static const SAdapterInstanceDef scm_astAdapterInstances[];

  FORTE_ATimeOut& ConnectTimeOut() {
    return (*static_cast<FORTE_ATimeOut*>(m_apoAdapters[0]));
  };
  static const int scm_nConnectTimeOutAdpNum = 0;
  FORTE_ATimeOut& CheckTimeOut() {
    return (*static_cast<FORTE_ATimeOut*>(m_apoAdapters[1]));
  };
  static const int scm_nCheckTimeOutAdpNum = 1;
  static const SFBInterfaceSpec scm_stFBInterfaceSpec;


  static const SInternalVarsInformation scm_stInternalVars;

   FORTE_BASIC_FB_DATA_ARRAY(3, 6, 2, 2, 2);

virtual void setInitialValues();
  void alg_Connect(void);
  void alg_Send(void);
  void alg_Receive(void);
  void alg_SendID(void);
  void alg_SetConnectTimeOut(void);
  void alg_SetCheckTimeOut(void);
  static const TForteInt16 scm_nStateSTART = 0;
  static const TForteInt16 scm_nStateInit = 1;
  static const TForteInt16 scm_nStateIdle = 2;
  static const TForteInt16 scm_nStateSend = 3;
  static const TForteInt16 scm_nStateReceive = 4;
  static const TForteInt16 scm_nStateSuccess = 5;
  static const TForteInt16 scm_nStateConnecting = 6;
  static const TForteInt16 scm_nStatePending = 7;
  static const TForteInt16 scm_nStateNotice = 8;
  static const TForteInt16 scm_nStateFail = 9;
  static const TForteInt16 scm_nStateIdentify = 10;
  static const TForteInt16 scm_nStateJudging = 11;

  void enterStateSTART(void);
  void enterStateInit(void);
  void enterStateIdle(void);
  void enterStateSend(void);
  void enterStateReceive(void);
  void enterStateSuccess(void);
  void enterStateConnecting(void);
  void enterStatePending(void);
  void enterStateNotice(void);
  void enterStateFail(void);
  void enterStateIdentify(void);
  void enterStateJudging(void);
  void alg_Sleep(void);
  virtual void executeEvent(int pa_nEIID);

public:
  FORTE_client(CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes) : 
       CBasicFB(pa_poSrcRes, &scm_stFBInterfaceSpec, pa_nInstanceNameId,
           &scm_stInternalVars, m_anFBConnData, m_anFBVarsData){
  };
int cli_sockfd;/*客户端SOCKET */
int addrlen;        
struct sockaddr_in ser_addr,/* 服务器的地址*/  cli_addr;/* 客户端的地址*/    

char * sendMsg = (char *)malloc(1024);
char receiveMsg[1024];
  virtual ~FORTE_client(){};

};

#endif //close the ifdef sequence from the beginning of the file

