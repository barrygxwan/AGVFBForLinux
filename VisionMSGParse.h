/*************************************************************************
*** FORTE Library Element
***
*** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
***
*** Name: VisionMSGParse
*** Description: Tamplate for a simple Basic Function Block Type
*** Version:
***     0.0: 2018-07-25/4DIAC-IDE - 4DIAC-Consortium -
***     1.0: 2016-05-26/AZ - fortiss GmbH -
*************************************************************************/

#ifndef _VISIONMSGPARSE_H_
#define _VISIONMSGPARSE_H_

#include <basicfb.h>
#include <forte_string.h>
#define Radius 10
static int X[64] = { 34, 85, 137,189,240,292,343,395,
                     34, 85, 137,188,240,292,343,394,
					 34, 86, 137,188,240,292,343,394,
					 34, 85, 137,189,239,291,343,393,
					 34, 85, 137,188,239,292,342,393,
					 34, 85, 137,188,240,292,342,393,
					 34, 85, 136,188,239,291,342,393,
					 34, 85, 137,188,239,291,342,393, };
static int Y[64] = { 394,394,394,394,394,394,394,394,
                     343,343,343,343,343,343,341,341,
                     291,290,290,290,290,290,290,290,
                     239,239,238,239,238,238,238,237,
                     187,188,187,188,187,188,187,187,
                     136,136,136,136,136,135,136,135,
                     85, 84, 85, 85, 85, 85, 84, 84,
                     34, 34, 33, 33, 33, 34, 34, 33 };


class FORTE_VisionMSGParse : public CBasicFB {
	DECLARE_FIRMWARE_FB(FORTE_VisionMSGParse)

private:
	static const CStringDictionary::TStringId scm_anDataInputNames[];
	static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
	CIEC_STRING &MassageIn() {
		return *static_cast<CIEC_STRING*>(getDI(0));
	};

	static const CStringDictionary::TStringId scm_anDataOutputNames[];
	static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
	CIEC_STRING &positionLabel() {
		return *static_cast<CIEC_STRING*>(getDO(0));
	};

	CIEC_STRING &position_x() {
		return *static_cast<CIEC_STRING*>(getDO(1));
	};

	CIEC_STRING &position_y() {
		return *static_cast<CIEC_STRING*>(getDO(2));
	};

	CIEC_STRING &position_x_y() {
		return *static_cast<CIEC_STRING*>(getDO(3));
	};

	static const TEventID scm_nEventREQID = 0;
	static const TForteInt16 scm_anEIWithIndexes[];
	static const TDataIOID scm_anEIWith[];
	static const CStringDictionary::TStringId scm_anEventInputNames[];

	static const TEventID scm_nEventCNFID = 0;
	static const TForteInt16 scm_anEOWithIndexes[];
	static const TDataIOID scm_anEOWith[];
	static const CStringDictionary::TStringId scm_anEventOutputNames[];

	static const CStringDictionary::TStringId scm_anInternalsNames[];
	static const CStringDictionary::TStringId scm_anInternalsTypeIds[];
	CIEC_STRING &lastPositionLabel() {
		return *static_cast<CIEC_STRING*>(getVarInternal(0));
	};

	static const SFBInterfaceSpec scm_stFBInterfaceSpec;


	static const SInternalVarsInformation scm_stInternalVars;

	FORTE_BASIC_FB_DATA_ARRAY(1, 1, 4, 1, 0);
	void alg_normalOperation(void);
	static const TForteInt16 scm_nStateSTART = 0;
	static const TForteInt16 scm_nStateNormalOp = 1;

	void enterStateSTART(void);
	void enterStateNormalOp(void);

	virtual void executeEvent(int pa_nEIID);

public:
	FORTE_VisionMSGParse(CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes) :
		CBasicFB(pa_poSrcRes, &scm_stFBInterfaceSpec, pa_nInstanceNameId,
			&scm_stInternalVars, m_anFBConnData, m_anFBVarsData) {
	};

	virtual ~FORTE_VisionMSGParse() {};

};

#endif //close the ifdef sequence from the beginning of the file

