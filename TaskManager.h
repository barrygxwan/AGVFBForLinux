/*************************************************************************
*** FORTE Library Element
***
*** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
***
*** Name: TaskManager
*** Description: Tamplate for a simple Basic Function Block Type
*** Version:
***     0.0: 2018-07-05/4DIAC-IDE - 4DIAC-Consortium -
***     1.0: 2016-05-26/AZ - fortiss GmbH -
*************************************************************************/

#ifndef _TASKMANAGER_H_
#define _TASKMANAGER_H_

#include <basicfb.h>
#include <forte_bool.h>
#include <forte_string.h>
#include <forte_int.h>

class FORTE_TaskManager : public CBasicFB {
	DECLARE_FIRMWARE_FB(FORTE_TaskManager)

private:
	static const CStringDictionary::TStringId scm_anDataInputNames[];
	static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
	CIEC_BOOL &QI() {
		return *static_cast<CIEC_BOOL*>(getDI(0));
	};

	CIEC_STRING &Position() {
		return *static_cast<CIEC_STRING*>(getDI(1));
	};

	CIEC_STRING &TaskMSG() {
		return *static_cast<CIEC_STRING*>(getDI(2));
	};

	static const CStringDictionary::TStringId scm_anDataOutputNames[];
	static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
	CIEC_BOOL &QO() {
		return *static_cast<CIEC_BOOL*>(getDO(0));
	};

	CIEC_STRING &Path() {
		return *static_cast<CIEC_STRING*>(getDO(1));
	};

	CIEC_STRING &Finish() {
		return *static_cast<CIEC_STRING*>(getDO(2));
	};

	static const TEventID scm_nEventINITID = 0;
	static const TEventID scm_nEventCurrentPositionID = 1;
	static const TEventID scm_nEventTaskRecvID = 2;
	static const TEventID scm_nEventTaskDoneID = 3;
	static const TForteInt16 scm_anEIWithIndexes[];
	static const TDataIOID scm_anEIWith[];
	static const CStringDictionary::TStringId scm_anEventInputNames[];

	static const TEventID scm_nEventINITOID = 0;
	static const TEventID scm_nEventCNFID = 1;
	static const TEventID scm_nEventTaskFinishID = 2;
	static const TForteInt16 scm_anEOWithIndexes[];
	static const TDataIOID scm_anEOWith[];
	static const CStringDictionary::TStringId scm_anEventOutputNames[];

	static const CStringDictionary::TStringId scm_anInternalsNames[];
	static const CStringDictionary::TStringId scm_anInternalsTypeIds[];
	CIEC_INT &TaskCount() {
		return *static_cast<CIEC_INT*>(getVarInternal(0));
	};

	CIEC_STRING &Path1() {
		return *static_cast<CIEC_STRING*>(getVarInternal(1));
	};

	CIEC_STRING &Path2() {
		return *static_cast<CIEC_STRING*>(getVarInternal(2));
	};

	static const SFBInterfaceSpec scm_stFBInterfaceSpec;


	static const SInternalVarsInformation scm_stInternalVars;

	FORTE_BASIC_FB_DATA_ARRAY(3, 3, 3, 3, 0);

	virtual void setInitialValues();
	void alg_initialize(void);
	void alg_deInitialize(void);
	void alg_PathRebuild(void);
	void alg_Path2MSG(void);
	void alg_TaskReallyDone(void);
	void alg_positionUpdate(void);
	static const TForteInt16 scm_nStateSTART = 0;
	static const TForteInt16 scm_nStateInit = 1;
	static const TForteInt16 scm_nStateTaskRearrangement = 2;
	static const TForteInt16 scm_nStateInitialized = 3;
	static const TForteInt16 scm_nStateDeInit = 4;
	static const TForteInt16 scm_nStateTaskPhaseOne = 5;
	static const TForteInt16 scm_nStateTaskFinish = 6;
	static const TForteInt16 scm_nStatePositionState = 7;

	void enterStateSTART(void);
	void enterStateInit(void);
	void enterStateTaskRearrangement(void);
	void enterStateInitialized(void);
	void enterStateDeInit(void);
	void enterStateTaskPhaseOne(void);
	void enterStateTaskFinish(void);
	void enterStatePositionState(void);

	virtual void executeEvent(int pa_nEIID);

public:
	FORTE_TaskManager(CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes) :
		CBasicFB(pa_poSrcRes, &scm_stFBInterfaceSpec, pa_nInstanceNameId,
			&scm_stInternalVars, m_anFBConnData, m_anFBVarsData) {
	};

	virtual ~FORTE_TaskManager() {};

};

#endif //close the ifdef sequence from the beginning of the file

