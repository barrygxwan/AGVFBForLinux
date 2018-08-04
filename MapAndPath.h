/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: MapAndPath
 *** Description: Tamplate for a simple Basic Function Block Type
 *** Version: 
 ***     0.0: 2018-06-04/4DIAC-IDE - 4DIAC-Consortium - 
 ***     1.0: 2016-05-26/AZ - fortiss GmbH - 
 *************************************************************************/

#ifndef _MAPANDPATH_H_
#define _MAPANDPATH_H_

#include <basicfb.h>
#include <forte_bool.h>
#include <forte_string.h>
#include <forte_int.h>

class FORTE_MapAndPath: public CBasicFB{
  DECLARE_FIRMWARE_FB(FORTE_MapAndPath)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_BOOL &QI() {
    return *static_cast<CIEC_BOOL*>(getDI(0));
  };

  CIEC_STRING &LengthAndWeight() {
    return *static_cast<CIEC_STRING*>(getDI(1));
  };

  CIEC_INT &AlgorithmSelection() {
    return *static_cast<CIEC_INT*>(getDI(2));
  };

  CIEC_STRING &BeginEndPosition() {
    return *static_cast<CIEC_STRING*>(getDI(3));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_BOOL &QO() {
    return *static_cast<CIEC_BOOL*>(getDO(0));
  };

  CIEC_STRING &State() {
    return *static_cast<CIEC_STRING*>(getDO(1));
  };

  CIEC_STRING &result() {
    return *static_cast<CIEC_STRING*>(getDO(2));
  };

  static const TEventID scm_nEventINITID = 0;
  static const TEventID scm_nEventCreateMapID = 1;
  static const TEventID scm_nEventPathPlanID = 2;
  static const TForteInt16 scm_anEIWithIndexes[];
  static const TDataIOID scm_anEIWith[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];

  static const TEventID scm_nEventINITOID = 0;
  static const TEventID scm_nEventmap_CNFID = 1;
  static const TEventID scm_nEventPath_CNFID = 2;
  static const TForteInt16 scm_anEOWithIndexes[];
  static const TDataIOID scm_anEOWith[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];

  static const CStringDictionary::TStringId scm_anInternalsNames[];
  static const CStringDictionary::TStringId scm_anInternalsTypeIds[];
  CIEC_INT &maxNum() {
    return *static_cast<CIEC_INT*>(getVarInternal(0));
  };

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;


  static const SInternalVarsInformation scm_stInternalVars;

   FORTE_BASIC_FB_DATA_ARRAY(3, 4, 3, 1, 0);
  void alg_initialize(void);
  void alg_deInitialize(void);
  void alg_creatMap(void);
  void alg_PathPlan(void);
  static const TForteInt16 scm_nStateSTART = 0;
  static const TForteInt16 scm_nStateInit = 1;
  static const TForteInt16 scm_nStateMapCreation = 2;
  static const TForteInt16 scm_nStateInitialized = 3;
  static const TForteInt16 scm_nStateDeInit = 4;
  static const TForteInt16 scm_nStatePathPlan = 5;

  void enterStateSTART(void);
  void enterStateInit(void);
  void enterStateMapCreation(void);
  void enterStateInitialized(void);
  void enterStateDeInit(void);
  void enterStatePathPlan(void);

  virtual void executeEvent(int pa_nEIID);

public:
  FORTE_MapAndPath(CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes) : 
       CBasicFB(pa_poSrcRes, &scm_stFBInterfaceSpec, pa_nInstanceNameId,
           &scm_stInternalVars, m_anFBConnData, m_anFBVarsData){
  };

  virtual ~FORTE_MapAndPath(){};

};

#endif //close the ifdef sequence from the beginning of the file

