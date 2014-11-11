#pragma once
#include "afxwin.h"
#include "afxdtctl.h"

/**
* @class	_PDlgServiceSchedule           
* @brief    스케줄 정보를 설정하기 위한 다이얼로그입니다.
* @date           2010-09-17
* @author        이진욱(julee@pnpsecure.com)
* @par 수정정보
*                    - 2010-09-17, 이진욱 : 클래스 작성 시작
*/

// _PDlgServiceSchedule 대화 상자입니다.

class _PDlgServiceSchedule : public CDialog
{
	DECLARE_DYNAMIC(_PDlgServiceSchedule)

public:
	_PDlgServiceSchedule(CWnd* pParent, SERVICE_SCHEDULE_DATA* pSchduleData);   //< 스케줄 내용만을 보여주기 위한 생성자입
	virtual ~_PDlgServiceSchedule();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_SERVICE_SCHEDULE };

	CFont m_font;	// static 컨트롤 폰트 설정용

	HICON m_hIcon;

	CString         m_strSubject;   // Store subject editor value. UpdateData method used to Exchange value with dialog control.
	CString         m_strBody;      // Store body editor value. UpdateData method used to Exchange value with dialog control.
	COleDateTime    m_dtStartDate;  // Store StartDate editor value. UpdateData method used to Exchange value with dialog control.
	COleDateTime    m_dtStartTime;  // Store StartTime editor value. UpdateData method used to Exchange value with dialog control.
	COleDateTime    m_dtEndDate;    // Store EndDate editor value. UpdateData method used to Exchange value with dialog control.
	COleDateTime    m_dtEndTime;    // Store EndTime editor value. UpdateData method used to Exchange value with dialog control.

	SERVICE_SCHEDULE_DATA m_ScheduleData;

	CPNP_EM_MasterThread_Item *m_pMaster_thread;	// Auth 데몬통신용 Thread Pointer

	BOOL m_bEdit;
	BOOL m_bShowOnly;
	CString m_strShowOnlyText;

	CStatic m_StaticMsg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	void InitControl();
	void SetAlertData(INT nID);
	void ResetAlertData(INT nID);

	void AddEndDate_ResetTime(COleDateTime dtStartDate, COleDateTime& rdtEndDate, int nDays);
	int _AddString(CComboBox& wndCB, UINT nStrResID, DWORD_PTR dwItemData);
	int _AddLocaleString(CComboBox& wndCB, LCTYPE lcidStr, DWORD_PTR dwItemData);
	void InitDayOfWeekCBs(CComboBox& wndCB);
	void InitWhichDayCBs(CComboBox& wndCB);

	void UpdateControlsFromData();
	void SetWeekDay(INT nSelectedWeekday);
	void SetShowOnlyUI();
	void SetServiceScheduleDestText();

public:

	CStatic m_Static_ScheduleName;	
	CWDEdit m_Edit_ScheduleName;
	CStatic m_Static_JobName_Limit;		

	CStatic m_Static_BackupType;	
	CComboBox m_Combo_BackupType;

	CStatic m_Static_ScheduleType;	
	CComboBox m_Combo_ScheduleType;

	CStatic m_Static_Day_of_Month;
	CWDEdit m_Edit_Day_of_Month;
	CStatic m_Static_Day;
	CStatic m_Static_Day_Limit;

	CStatic m_Static_StartTerm;
	
	CStatic m_Static_Week_of_Month;	
	CComboBox m_Combo_Week_of_Month;
	CComboBox m_Combo_Day_of_Month;

	CDateTimeCtrl m_DateTimePicker_ScheduleDate;
	CDateTimeCtrl m_DateTimePicker_ScheduleTime;	

	CStatic m_ScheduleWeekDay;
	CButton m_Check_Sun;
	CButton m_Check_Mon;
	CButton m_Check_Tue;
	CButton m_Check_Wed;
	CButton m_Check_Thu;
	CButton m_Check_Fri;
	CButton m_Check_Sat;

	CStatic m_Static_Service_Action;	
	CComboBox m_Combo_Service_Action;

	CStatic m_Static_Service_Dest;
	CIconEdit m_IconEdit_Service_Dest;
	CButton m_Btn_Service_Dest;

	CButton m_Check_Active_Expire;
	CStatic m_Static_Time_Data;
	CStatic m_Static_DateTime_Begin;
	CStatic m_Static_DateTime_End;
	CDateTimeCtrl m_DateTimePicker_DateTime_Begin;
	CDateTimeCtrl m_DateTimePicker_DateTime_End;
	
	CStatic m_Static_AlertData;		
	CStatic m_Static_Alert;		
	CButton m_Check_Success_Alert;	
	CButton m_Check_Fail_Alert;	

	CStatic m_Static_Alert_Object_Success;
	CIconEdit m_IconEdit_Alert_Success;
	CButton m_BtnAlert_Success;

	CStatic m_Static_Alert_Object_Fail;
	CIconEdit m_IconEdit_Alert_Fail;
	CButton m_BtnAlert_Fail;

	CStatic m_Static_Comment;		// Comment
	CStatic m_Static_Comment_Limit;		// Comment
	CWDEdit m_Edit_Comment;

	CButton m_BtnOK;
	CButton c_BtnCancel;

    virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBuServiceDest();
	afx_msg void OnBnClickedBuAlertSuccess();
	afx_msg void OnBnClickedBuAlertFail();
	afx_msg void OnBnClickedCheckAlert();
	afx_msg void OnBnClickedCheckTerm();
	afx_msg void OnCbnSelchangeComboScheduleType();
	afx_msg void OnBnClickedCheckSun();
	afx_msg void OnBnClickedCheckMon();
	afx_msg void OnBnClickedCheckTue();
	afx_msg void OnBnClickedCheckWed();
	afx_msg void OnBnClickedCheckThu();
	afx_msg void OnBnClickedCheckFri();
	afx_msg void OnBnClickedCheckSat();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	void SetScheduleTypeReservation();
	void SetScheduleTypeDaily(); // 스케줄 형태(일별)
	void SetScheduleTypeWeekly(); // 스케줄 형태(주별)
	void SetScheduleTypeMonthly(); // 스케줄 형태(월별_일자기준)
	void SetScheduleTypeDayOfWeek(); // 스케줄 형태(월별_요일기준)

	void GetScheduleDayOfWeek();
	void GetBackUpMonthly_DayOfWeek();

	void MsgBox_WrongValueRange(UINT nCtrlID, int nMin, int nMax);
	SERVICE_SCHEDULE_DATA GetScheduleData() {return m_ScheduleData;}
	void SetScheduleData(SERVICE_SCHEDULE_DATA &stScheduleData) {m_ScheduleData = stScheduleData;}

protected:
	virtual void OnOK();
};
