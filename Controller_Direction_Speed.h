/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: Controller_Direction_Speed
 *** Description: Tamplate for a simple Basic Function Block Type
 *** Version: 
 ***     0.0: 2018-07-24/4DIAC-IDE - 4DIAC-Consortium - 
 ***     1.0: 2016-05-26/AZ - fortiss GmbH - 
 *************************************************************************/

#ifndef _CONTROLLER_DIRECTION_SPEED_H_
#define _CONTROLLER_DIRECTION_SPEED_H_

#include <basicfb.h>
#include <forte_bool.h>
#include <forte_string.h>
#include <string.h>
#include <vector> 
class MyVehicle
{
public:
	MyVehicle();
	~MyVehicle();
	int direction;//1->Y+;2->Y-;3->X+;4->X-.


};

MyVehicle::MyVehicle()
{
}

MyVehicle::~MyVehicle()
{
}


#endif //close the ifdef sequence from the beginning of the file


class FORTE_Controller_Direction_Speed : public CBasicFB {
	DECLARE_FIRMWARE_FB(FORTE_Controller_Direction_Speed)

private:
	static const CStringDictionary::TStringId scm_anDataInputNames[];
	static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
	CIEC_BOOL &QI() {
		return *static_cast<CIEC_BOOL*>(getDI(0));
	};

	CIEC_STRING &pathMSG() {
		return *static_cast<CIEC_STRING*>(getDI(1));
	};

	CIEC_STRING &my_position_x_y() {
		return *static_cast<CIEC_STRING*>(getDI(2));
	};

	CIEC_STRING &target_positon_y() {
		return *static_cast<CIEC_STRING*>(getDI(3));
	};

	CIEC_STRING &my_positionLable() {
		return *static_cast<CIEC_STRING*>(getDI(4));
	};

	CIEC_STRING &ArbitrationCMD() {
		return *static_cast<CIEC_STRING*>(getDI(5));
	};

	CIEC_INT &distance() {
		return *static_cast<CIEC_INT*>(getDI(6));
	};

	static const CStringDictionary::TStringId scm_anDataOutputNames[];
	static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
	CIEC_BOOL &QO() {
		return *static_cast<CIEC_BOOL*>(getDO(0));
	};

	CIEC_BOOL &state() {
		return *static_cast<CIEC_BOOL*>(getDO(1));
	};

	CIEC_STRING &commandOutput() {
		return *static_cast<CIEC_STRING*>(getDO(2));
	};

	static const TEventID scm_nEventINITID = 0;
	static const TEventID scm_nEventPATHID = 1;
	static const TEventID scm_nEventPOSITIONID = 2;
	static const TEventID scm_nEventARBITRATIONID = 3;
	static const TForteInt16 scm_anEIWithIndexes[];
	static const TDataIOID scm_anEIWith[];
	static const CStringDictionary::TStringId scm_anEventInputNames[];

	static const TEventID scm_nEventINITOID = 0;
	static const TEventID scm_nEventCNFID = 1;
	static const TEventID scm_nEventVEHICLESTATEID = 2;
	static const TForteInt16 scm_anEOWithIndexes[];
	static const TDataIOID scm_anEOWith[];
	static const CStringDictionary::TStringId scm_anEventOutputNames[];

	static const CStringDictionary::TStringId scm_anInternalsNames[];
	static const CStringDictionary::TStringId scm_anInternalsTypeIds[];
	CIEC_BOOL &ArbitrateCommand() {
		return *static_cast<CIEC_BOOL*>(getVarInternal(0));
	};

	CIEC_STRING &Direction() {
		return *static_cast<CIEC_STRING*>(getVarInternal(1));
	};

	static const SFBInterfaceSpec scm_stFBInterfaceSpec;


	static const SInternalVarsInformation scm_stInternalVars;

	FORTE_BASIC_FB_DATA_ARRAY(3, 7, 3, 2, 0);

	virtual void setInitialValues();
	void alg_initialize(void);
	void alg_deInitialize(void);
	void alg_PathMSGParse(void);
	void alg_Arbitrate(void);
	void alg_realTimeControl(void);
	static const TForteInt16 scm_nStateSTART = 0;
	static const TForteInt16 scm_nStateInit = 1;
	static const TForteInt16 scm_nStateInitialized = 2;
	static const TForteInt16 scm_nStateDeInit = 3;
	static const TForteInt16 scm_nStatePathParse = 4;
	static const TForteInt16 scm_nStateArbitrateControl = 5;
	static const TForteInt16 scm_nStatePositionRealTimeControl = 6;

	void enterStateSTART(void);
	void enterStateInit(void);
	void enterStateInitialized(void);
	void enterStateDeInit(void);
	void enterStatePathParse(void);
	void enterStateArbitrateControl(void);
	void enterStatePositionRealTimeControl(void);

	virtual void executeEvent(int pa_nEIID);
	std::vector<char*> Node;
	int* g_path;
	int release;
	MyVehicle myAgv = MyVehicle();
    int *pq;
public:
	FORTE_Controller_Direction_Speed(CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes) :
		CBasicFB(pa_poSrcRes, &scm_stFBInterfaceSpec, pa_nInstanceNameId,
			&scm_stInternalVars, m_anFBConnData, m_anFBVarsData) {
	};

	virtual ~FORTE_Controller_Direction_Speed() {};

};

