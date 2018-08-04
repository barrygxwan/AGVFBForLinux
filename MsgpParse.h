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

#ifndef _MSGPPARSE_H_
#define _MSGPPARSE_H_

#include <basicfb.h>
#include <forte_string.h>

class FORTE_MsgpParse: public CBasicFB{
  DECLARE_FIRMWARE_FB(FORTE_MsgpParse)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_STRING &QI() {
    return *static_cast<CIEC_STRING*>(getDI(0));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_STRING &currentPosition() {
    return *static_cast<CIEC_STRING*>(getDO(0));
  };

  CIEC_STRING &lastPosition() {
    return *static_cast<CIEC_STRING*>(getDO(1));
  };

  static const TEventID scm_nEventREQID = 0;
  static const TForteInt16 scm_anEIWithIndexes[];
  static const TDataIOID scm_anEIWith[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];

  static const TEventID scm_nEventCNFID = 0;
  static const TForteInt16 scm_anEOWithIndexes[];
  static const TDataIOID scm_anEOWith[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;

   FORTE_BASIC_FB_DATA_ARRAY(1, 1, 2, 0, 0);
  void alg_parseOperation(void);
  static const TForteInt16 scm_nStateSTART = 0;
  static const TForteInt16 scm_nStatemsgParse = 1;

  void enterStateSTART(void);
  void enterStatemsgParse(void);

  virtual void executeEvent(int pa_nEIID);

public:
  FORTE_MsgpParse(CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes) : 
       CBasicFB(pa_poSrcRes, &scm_stFBInterfaceSpec, pa_nInstanceNameId,
              0, m_anFBConnData, m_anFBVarsData){
  };

  virtual ~FORTE_MsgpParse(){};

};

#endif //close the ifdef sequence from the beginning of the file

