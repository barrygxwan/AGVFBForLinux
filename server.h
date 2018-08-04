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

#ifndef _SERVER_H_
#define _SERVER_H_

#include <basicfb.h>
#include <forte_bool.h>
#include <forte_string.h>

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#define MAXLINE 1024


class FORTE_server: public CBasicFB{
  DECLARE_FIRMWARE_FB(FORTE_server)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_BOOL &QI() {
    return *static_cast<CIEC_BOOL*>(getDI(0));
  };

  CIEC_STRING &ID() {
    return *static_cast<CIEC_STRING*>(getDI(1));
  };

  CIEC_STRING &Port() {
    return *static_cast<CIEC_STRING*>(getDI(2));
  };

  CIEC_STRING &SD() {
    return *static_cast<CIEC_STRING*>(getDI(3));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_BOOL &QO() {
    return *static_cast<CIEC_BOOL*>(getDO(0));
  };

  CIEC_STRING &STATUS() {
    return *static_cast<CIEC_STRING*>(getDO(1));
  };

  CIEC_STRING &RD() {
    return *static_cast<CIEC_STRING*>(getDO(2));
  };

  static const TEventID scm_nEventINITID = 0;
  static const TEventID scm_nEventRSPID = 1;
  static const TForteInt16 scm_anEIWithIndexes[];
  static const TDataIOID scm_anEIWith[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];

  static const TEventID scm_nEventINITOID = 0;
  static const TEventID scm_nEventCNFID = 1;
  static const TForteInt16 scm_anEOWithIndexes[];
  static const TDataIOID scm_anEOWith[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;

   FORTE_BASIC_FB_DATA_ARRAY(2, 4, 3, 0, 0);
  void alg_initialize(void);
  void alg_deInitialize(void);
  void alg_SendMSG(void);
  void alg_RecvMSG(void);
  static const TForteInt16 scm_nStateSTART = 0;
  static const TForteInt16 scm_nStateInit = 1;
  static const TForteInt16 scm_nStateSend = 2;
  static const TForteInt16 scm_nStateInitialized = 3;
  static const TForteInt16 scm_nStateDeInit = 4;
  static const TForteInt16 scm_nStateRev = 5;

  void enterStateSTART(void);
  void enterStateInit(void);
  void enterStateSend(void);
  void enterStateInitialized(void);
  void enterStateDeInit(void);
  void enterStateRev(void);

  virtual void executeEvent(int pa_nEIID);

public:
  FORTE_server(CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes) : 
       CBasicFB(pa_poSrcRes, &scm_stFBInterfaceSpec, pa_nInstanceNameId,
              0, m_anFBConnData, m_anFBVarsData){
  };
  
  
	 int listenfd,connfd,flags;
	 struct sockaddr_in sockaddr;
	 char buff[MAXLINE];
	 int n;
	 int count =0;

  virtual ~FORTE_server(){};

};

#endif //close the ifdef sequence from the beginning of the file

