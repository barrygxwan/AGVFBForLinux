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

#ifndef _AGVEVALUATE_H_
#define _AGVEVALUATE_H_

#include <basicfb.h>
#include <forte_bool.h>
#include <forte_string.h>
#include <forte_dint.h>


class FORTE_AGVEvaluate: public CBasicFB{
  DECLARE_FIRMWARE_FB(FORTE_AGVEvaluate)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_STRING &currentPosition() {
    return *static_cast<CIEC_STRING*>(getDI(0));
  };

  CIEC_STRING &BeginEndPosition() {
    return *static_cast<CIEC_STRING*>(getDI(1));
  };

  CIEC_STRING &LengthAndWeight() {
    return *static_cast<CIEC_STRING*>(getDI(2));
  };

  CIEC_BOOL &state() {
    return *static_cast<CIEC_BOOL*>(getDI(3));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_STRING &value() {
    return *static_cast<CIEC_STRING*>(getDO(0));
  };

  static const TEventID scm_nEventREQID = 0;
  static const TEventID scm_nEventCurrentStateID = 1;
  static const TForteInt16 scm_anEIWithIndexes[];
  static const TDataIOID scm_anEIWith[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];

  static const TEventID scm_nEventCNFID = 0;
  static const TForteInt16 scm_anEOWithIndexes[];
  static const TDataIOID scm_anEOWith[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];

  static const CStringDictionary::TStringId scm_anInternalsNames[];
  static const CStringDictionary::TStringId scm_anInternalsTypeIds[];
  CIEC_DINT &currentTime() {
    return *static_cast<CIEC_DINT*>(getVarInternal(0));
  };

  CIEC_DINT &LastTime() {
    return *static_cast<CIEC_DINT*>(getVarInternal(1));
  };

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;


  static const SInternalVarsInformation scm_stInternalVars;

   FORTE_BASIC_FB_DATA_ARRAY(1, 4, 1, 2, 0);
  void alg_stateTran(void);
  void alg_calculateValue(void);
  static const TForteInt16 scm_nStateSTART = 0;
  static const TForteInt16 scm_nStateState = 1;
  static const TForteInt16 scm_nStatevalueCalculation = 2;

  void enterStateSTART(void);
  void enterStateState(void);
  void enterStatevalueCalculation(void);

  virtual void executeEvent(int pa_nEIID);

public:
  FORTE_AGVEvaluate(CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes) : 
       CBasicFB(pa_poSrcRes, &scm_stFBInterfaceSpec, pa_nInstanceNameId,
           &scm_stInternalVars, m_anFBConnData, m_anFBVarsData){
  };

  virtual ~FORTE_AGVEvaluate(){};

};


#endif //close the ifdef sequence from the beginning of the file

