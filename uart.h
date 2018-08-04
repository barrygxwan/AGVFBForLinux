/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: uart
 *** Description: uart for RPI /dev/ttyAMA0 Parity Check: None DB: 8 stop bit 1 
 *** Version: 
 ***     0.0: 2018-03-23/4DIAC-IDE - 4DIAC-Consortium - 
 ***     1.0: 2016-05-26/AZ - fortiss GmbH - 
 *************************************************************************/

#ifndef _UART_H_
#define _UART_H_

#include <basicfb.h>
#include <forte_string.h>
#include <forte_dint.h>
#include <forte_int.h>

class FORTE_uart: public CBasicFB{
  DECLARE_FIRMWARE_FB(FORTE_uart)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_DINT &BaudRate() {
    return *static_cast<CIEC_DINT*>(getDI(0));
  };

  CIEC_INT &DataBits() {
    return *static_cast<CIEC_INT*>(getDI(1));
  };

  CIEC_INT &Stopbits() {
    return *static_cast<CIEC_INT*>(getDI(2));
  };

  CIEC_INT &Parity() {
    return *static_cast<CIEC_INT*>(getDI(3));
  };

  CIEC_STRING &sendMSG() {
    return *static_cast<CIEC_STRING*>(getDI(4));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_STRING &ConnectionState() {
    return *static_cast<CIEC_STRING*>(getDO(0));
  };

  static const TEventID scm_nEventINITID = 0;
  static const TEventID scm_nEventREQID = 1;
  static const TForteInt16 scm_anEIWithIndexes[];
  static const TDataIOID scm_anEIWith[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];

  static const TEventID scm_nEventINITOID = 0;
  static const TEventID scm_nEventCNFID = 1;
  static const TForteInt16 scm_anEOWithIndexes[];
  static const TDataIOID scm_anEOWith[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];

  static const CStringDictionary::TStringId scm_anInternalsNames[];
  static const CStringDictionary::TStringId scm_anInternalsTypeIds[];
  CIEC_INT &fd() {
    return *static_cast<CIEC_INT*>(getVarInternal(0));
  };

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;


  static const SInternalVarsInformation scm_stInternalVars;

   FORTE_BASIC_FB_DATA_ARRAY(2, 5, 1, 1, 0);

virtual void setInitialValues();
  void alg_initialize(void);
  void alg_send(void);
  static const TForteInt16 scm_nStateSTART = 0;
  static const TForteInt16 scm_nStateInit = 1;
  static const TForteInt16 scm_nStateSend = 2;
  static const TForteInt16 scm_nStateNarmal = 3;

  void enterStateSTART(void);
  void enterStateInit(void);
  void enterStateSend(void);
  void enterStateNarmal(void);

  virtual void executeEvent(int pa_nEIID);

public:
  FORTE_uart(CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes) : 
       CBasicFB(pa_poSrcRes, &scm_stFBInterfaceSpec, pa_nInstanceNameId,
           &scm_stInternalVars, m_anFBConnData, m_anFBVarsData){
  };

  virtual ~FORTE_uart(){};

};

#endif //close the ifdef sequence from the beginning of the file

