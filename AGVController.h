/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: AGVController
 *** Description: Tamplate for a simple Basic Function Block Type
 *** Version: 
 ***     0.0: 2018-06-08/4DIAC-IDE - 4DIAC-Consortium - 
 ***     1.0: 2016-05-26/AZ - fortiss GmbH - 
 *************************************************************************/

#ifndef _AGVCONTROLLER_H_
#define _AGVCONTROLLER_H_

#include <basicfb.h>
#include <forte_bool.h>
#include <forte_string.h>

#include <string.h>
#include <vector> 

class FORTE_AGVController: public CBasicFB{
  DECLARE_FIRMWARE_FB(FORTE_AGVController)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_BOOL &QI() {
    return *static_cast<CIEC_BOOL*>(getDI(0));
  };

  CIEC_STRING &PathMSG() {
    return *static_cast<CIEC_STRING*>(getDI(1));
  };

  CIEC_STRING &CurrentPosition() {
    return *static_cast<CIEC_STRING*>(getDI(2));
  };

  CIEC_STRING &LastPosition() {
    return *static_cast<CIEC_STRING*>(getDI(3));
  };

  CIEC_STRING &ArbitrateCOMD() {
    return *static_cast<CIEC_STRING*>(getDI(4));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_BOOL &QO() {
    return *static_cast<CIEC_BOOL*>(getDO(0));
  };

  CIEC_BOOL &State() {
    return *static_cast<CIEC_BOOL*>(getDO(1));
  };

  CIEC_STRING &commandToAGV() {
    return *static_cast<CIEC_STRING*>(getDO(2));
  };

  static const TEventID scm_nEventINITID = 0;
  static const TEventID scm_nEventPATHRecvID = 1;
  static const TEventID scm_nEventPositionRecvID = 2;
  static const TEventID scm_nEventArbitrationID = 3;
  static const TForteInt16 scm_anEIWithIndexes[];
  static const TDataIOID scm_anEIWith[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];

  static const TEventID scm_nEventINITOID = 0;
  static const TEventID scm_nEventCNFID = 1;
  static const TEventID scm_nEventTaskDoneID = 2;
  static const TForteInt16 scm_anEOWithIndexes[];
  static const TDataIOID scm_anEOWith[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];

  static const CStringDictionary::TStringId scm_anInternalsNames[];
  static const CStringDictionary::TStringId scm_anInternalsTypeIds[];
  CIEC_BOOL &ArbitrateCommand() {
    return *static_cast<CIEC_BOOL*>(getVarInternal(0));
  };

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;


  static const SInternalVarsInformation scm_stInternalVars;

   FORTE_BASIC_FB_DATA_ARRAY(3, 5, 3, 1, 0);

virtual void setInitialValues();
  void alg_initialize(void);
  void alg_deInitialize(void);
  void alg_PathMSGParse(void);
  void alg_Arbitrate(void);
  void alg_mainControl(void);
  static const TForteInt16 scm_nStateSTART = 0;
  static const TForteInt16 scm_nStateInit = 1;
  static const TForteInt16 scm_nStatePathParse = 2;
  static const TForteInt16 scm_nStateInitialized = 3;
  static const TForteInt16 scm_nStateDeInit = 4;
  static const TForteInt16 scm_nStatearbitrateControl = 5;
  static const TForteInt16 scm_nStatePositionControl = 6;

  void enterStateSTART(void);
  void enterStateInit(void);
  void enterStatePathParse(void);
  void enterStateInitialized(void);
  void enterStateDeInit(void);
  void enterStatearbitrateControl(void);
  void enterStatePositionControl(void);

  virtual void executeEvent(int pa_nEIID);
  std::vector<char*> Node;
  int* g_path;

public:
  FORTE_AGVController(CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes) : 
       CBasicFB(pa_poSrcRes, &scm_stFBInterfaceSpec, pa_nInstanceNameId,
           &scm_stInternalVars, m_anFBConnData, m_anFBVarsData){
  };

  virtual ~FORTE_AGVController(){};

  //std::vector<char*> Node;
  //std::vector<std::string> Node;

};

class MyAGV
{
public:
	MyAGV();
	~MyAGV();
	int direction;//1->Y+;2->Y-;3->X+;4->X-.
    

};

MyAGV::MyAGV()
{
}

MyAGV::~MyAGV()
{
}

#endif //close the ifdef sequence from the beginning of the file

