// Dlg_Time.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DBSafer_Enterprise_Manager.h"
#include "_PUserBackupWndBase.h"
#include "_PUserBackupTabFormWnd.h"
#include "_PDlgServiceSchedule.h"
#include "Dlg_Policy_Entity.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// _PDlgServiceSchedule 대화 상자입니다.

IMPLEMENT_DYNAMIC(_PDlgServiceSchedule, CDialog)
_PDlgServiceSchedule::_PDlgServiceSchedule(CWnd* pParent, SERVICE_SCHEDULE_DATA* pSchduleData)
	: CDialog(_PDlgServiceSchedule::IDD, pParent)
{
	m_pMaster_thread = NULL;

	m_pParentWnd = pParent;

	m_ScheduleData = *pSchduleData;

	m_bEdit = FALSE;

	m_strShowOnlyText = _S(IDS_MSG_CURRENT_PROGRESS_JOB);

	m_bShowOnly = FALSE;

	m_dtStartDate = COleDateTime::GetCurrentTime();
	m_dtEndDate = COleDateTime::GetCurrentTime();
}

_PDlgServiceSchedule::~_PDlgServiceSchedule()
{
	m_font.DeleteObject();
}

void _PDlgServiceSchedule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SCHEDULE_NAME, m_Static_ScheduleName);
	DDX_Control(pDX, IDC_EDIT_SCHEDULE_NAME, m_Edit_ScheduleName);
	DDX_Control(pDX, IDC_STATIC_JOB_NAME_LIMIT, m_Static_JobName_Limit);

	DDX_Control(pDX, IDC_STATIC_SCHEDULE_TYPE, m_Static_ScheduleType);
	DDX_Control(pDX, IDC_COMBO_SCHEDULE_TYPE, m_Combo_ScheduleType);

	DDX_Control(pDX, IDC_STATIC_DAY_OF_MONTH, m_Static_Day_of_Month);
	DDX_Control(pDX, IDC_EDIT_DAY_OF_MONTH, m_Edit_Day_of_Month);
	DDX_Control(pDX, IDC_STATIC_DAY, m_Static_Day);
	DDX_Control(pDX, IDC_STATIC_DAY_LIMIT, m_Static_Day_Limit);

	DDX_Control(pDX, IDC_STATIC_WEEK_OF_MONTH, m_Static_Week_of_Month);
	DDX_Control(pDX, IDC_COMBO_WEEK_OF_MONTH, m_Combo_Week_of_Month);
	DDX_Control(pDX, IDC_COMBO_DAY_OF_MONTH, m_Combo_Day_of_Month);

	DDX_Control(pDX, IDC_STATIC_START_TERM, m_Static_StartTerm);

	DDX_Control(pDX, IDC_DATETIMEPICKER_SCHEDULE_DATE, m_DateTimePicker_ScheduleDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SCHEDULE_TIME, m_DateTimePicker_ScheduleTime);

	DDX_Control(pDX, IDC_STATIC_SCHEDULE_WEEKDAY, m_ScheduleWeekDay);
	DDX_Control(pDX, IDC_CHECK_SUN, m_Check_Sun);
	DDX_Control(pDX, IDC_CHECK_MON, m_Check_Mon);
	DDX_Control(pDX, IDC_CHECK_TUE, m_Check_Tue);
	DDX_Control(pDX, IDC_CHECK_WED, m_Check_Wed);
	DDX_Control(pDX, IDC_CHECK_THU, m_Check_Thu);
	DDX_Control(pDX, IDC_CHECK_FRI, m_Check_Fri);
	DDX_Control(pDX, IDC_CHECK_SAT, m_Check_Sat);

	DDX_Control(pDX, IDC_STATIC_SERVICE_ACTION, m_Static_Service_Action);
	DDX_Control(pDX, IDC_COMBO_SERVICE_ACTION, m_Combo_Service_Action);
	DDX_Control(pDX, IDC_STATIC_SERVICE_DEST, m_Static_Service_Dest);
	DDX_Control(pDX, IDC_EDIT_SERVICE_DEST, m_IconEdit_Service_Dest);
	DDX_Control(pDX, IDC_BU_SERVICE_DEST, m_Btn_Service_Dest);

	DDX_Control(pDX, IDC_CHECK_ACTIVE_EXPIRE, m_Check_Active_Expire);
	DDX_Control(pDX, IDC_STATIC_TIME_DATA, m_Static_Time_Data);
	DDX_Control(pDX, IDC_STATIC_DATETIME_BEGIN, m_Static_DateTime_Begin);
	DDX_Control(pDX, IDC_STATIC_DATETIME_END, m_Static_DateTime_End);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BEGIN, m_DateTimePicker_DateTime_Begin);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END, m_DateTimePicker_DateTime_End);

	DDX_Control(pDX, IDC_CHECK_SUCCESS_ALARM, m_Check_Success_Alert);
	DDX_Control(pDX, IDC_CHECK_FAIL_ALARM, m_Check_Fail_Alert);
	DDX_Control(pDX, IDC_STATIC_ALARM_CONFIG, m_Static_Alert);
	DDX_Control(pDX, IDC_STATIC_ALERT, m_Static_AlertData);
	DDX_Control(pDX, IDC_STATIC_ALERT_OBJECT_SUCCESS, m_Static_Alert_Object_Success);
	DDX_Control(pDX, IDC_EDIT_ALERT_SUCCESS, m_IconEdit_Alert_Success);
	DDX_Control(pDX, IDC_BU_ALERT_SUCCESS, m_BtnAlert_Success);
	DDX_Control(pDX, IDC_STATIC_ALERT_OBJECT_FAIL, m_Static_Alert_Object_Fail);
	DDX_Control(pDX, IDC_EDIT_ALERT_FAIL, m_IconEdit_Alert_Fail);
	DDX_Control(pDX, IDC_BU_ALERT_FAIL, m_BtnAlert_Fail);

	DDX_Control(pDX, IDC_STATIC_COMMENT, m_Static_Comment);
	DDX_Control(pDX, IDC_STATIC_COMMENT_LIMIT, m_Static_Comment_Limit);
	DDX_Control(pDX, IDC_EDIT_COMMENT, m_Edit_Comment);

	DDX_Control(pDX, IDOK, m_BtnOK);
	DDX_Control(pDX, IDCANCEL, c_BtnCancel);
	DDX_Control(pDX, IDC_STATIC_MSG, m_StaticMsg);
}


BEGIN_MESSAGE_MAP(_PDlgServiceSchedule, CDialog)
	//ON_WM_CREATE()	//< 스케줄을 예약으로 변경하는 것에 대해서는 고려가 필요함
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BU_SERVICE_DEST, OnBnClickedBuServiceDest)
	ON_BN_CLICKED(IDC_BU_ALERT_SUCCESS, OnBnClickedBuAlertSuccess)
	ON_BN_CLICKED(IDC_BU_ALERT_FAIL, OnBnClickedBuAlertFail)
	ON_BN_CLICKED(IDC_CHECK_SUCCESS_ALARM, OnBnClickedCheckAlert)
	ON_BN_CLICKED(IDC_CHECK_FAIL_ALARM, OnBnClickedCheckAlert)
	ON_BN_CLICKED(IDC_CHECK_ACTIVE_EXPIRE, OnBnClickedCheckTerm)
	ON_CBN_SELCHANGE(IDC_COMBO_SCHEDULE_TYPE, OnCbnSelchangeComboScheduleType)
	ON_BN_CLICKED(IDC_CHECK_SUN, OnBnClickedCheckSun)
	ON_BN_CLICKED(IDC_CHECK_MON, OnBnClickedCheckMon)
	ON_BN_CLICKED(IDC_CHECK_TUE, OnBnClickedCheckTue)
	ON_BN_CLICKED(IDC_CHECK_WED, OnBnClickedCheckWed)
	ON_BN_CLICKED(IDC_CHECK_THU, OnBnClickedCheckThu)
	ON_BN_CLICKED(IDC_CHECK_FRI, OnBnClickedCheckFri)
	ON_BN_CLICKED(IDC_CHECK_SAT, OnBnClickedCheckSat)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

int _PDlgServiceSchedule::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

// _PDlgServiceSchedule 메시지 처리기입니다.

BOOL _PDlgServiceSchedule::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_pMaster_thread = &((CDBSafer_Enterprise_ManagerApp*)AfxGetApp())->m_SessionManager.m_Master_Session;

	InitControl();	//< UI 컨트롤 초기화 함수

	SetScheduleTypeReservation();	//< 기본 예약 상태로 설정
	
	if(FALSE != m_bEdit)	UpdateControlsFromData();	//< 에디트일 경우 에디트 내용 적용

	OnBnClickedCheckTerm();	//< 스케줄 이벤트 객체의 유효기간 설정 컨트롤의 UI 설정

	OnBnClickedCheckAlert();	//< Alert의 컨트롤의 UI 설정

	if(FALSE != m_bShowOnly)	SetShowOnlyUI();	//< 읽기 형태의 UI 출력	- 현재 사용 안됨

	return TRUE;  
}

void _PDlgServiceSchedule::InitControl()
{
	m_Edit_Comment.SetExclusion(EDIT_EXCLUSION_CHAR2);	// 입력제한 문자 설정

	if(MAKELANGID(LANG_JAPANESE, SUBLANG_DEFAULT) == ::GetUserDefaultLangID())
	{
		m_font.CreateFont(11, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, 0, SHIFTJIS_CHARSET, 0, CLIP_CHARACTER_PRECIS, 0, VARIABLE_PITCH | FF_ROMAN, "MS Shell Dlg");
	}
	else
	{
		m_font.CreateFont(11, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, 0, HANGUL_CHARSET, 0, CLIP_CHARACTER_PRECIS, 0, VARIABLE_PITCH | FF_ROMAN, "MS Shell Dlg");
	}

	m_Static_JobName_Limit.SetFont(&m_font);
	m_Static_Comment_Limit.SetFont(&m_font);
	m_Static_Day_Limit.SetFont(&m_font);

	m_Edit_Comment.SetLimitStr(127);
	m_Edit_Comment.SetMessageCaption(_S(IDS_STR_COMMENT/*설명*/));

	m_IconEdit_Service_Dest.HideEditCaret();
	m_IconEdit_Alert_Success.HideEditCaret();
	m_IconEdit_Alert_Fail.HideEditCaret();

	m_Edit_ScheduleName.SetExclusion(EDIT_EXCLUSION_CHAR);	// 입력제한 문자 설정
	m_Edit_ScheduleName.SetLimitStr(254);

	m_DateTimePicker_ScheduleTime.SetFormat(_T("HH:mm:00"));

	//스케줄의 특성상 Date만 사용하기로 한다.
	/*m_DateTimePicker_DateTime_Begin.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));
	m_DateTimePicker_DateTime_End.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));*/

	//일자 입력 1 ~ 31일만 입력 받음
	m_Edit_Day_of_Month.SetLimitDigit_Min(1);
	m_Edit_Day_of_Month.SetLimitDigit(31);

	m_Combo_ScheduleType.AddString(_S(IDS_STR_RESERVATION));
	m_Combo_ScheduleType.AddString(_S(IDS_SCHEDULE_TYPE_DAILY));
	m_Combo_ScheduleType.AddString(_S(IDS_SCHEDULE_TYPE_WEEKLY));
	m_Combo_ScheduleType.AddString(_S(IDS_SCHEDULE_TYPE_MONTHLY));
	m_Combo_ScheduleType.AddString(_S(IDS_SCHEDULE_TYPE_MONTHLY_DAY_OF_WEEK));

	m_Combo_Service_Action.AddString(_S(IDS_TMP_SERVICE_START));
	m_Combo_Service_Action.AddString(_S(IDS_TMP_SERVICE_STOP));
	m_Combo_Service_Action.SetCurSel(0);
	
	InitWhichDayCBs(m_Combo_Week_of_Month);
	InitDayOfWeekCBs(m_Combo_Day_of_Month);
	
	m_IconEdit_Service_Dest.ResetIcon();
	m_IconEdit_Alert_Success.ResetIcon();
	m_IconEdit_Alert_Fail.ResetIcon();

	INT nSelectedWeekday = NewBackupUtil::GetDayOfWeek(m_dtStartDate);
	SetWeekDay(nSelectedWeekday);
	m_Combo_Day_of_Month.SetCurSel(nSelectedWeekday);
	m_Combo_Week_of_Month.SetCurSel(NewBackupUtil::GetWeekcountOfMonth(m_dtStartDate, (INT)m_Combo_Day_of_Month.GetItemData(m_Combo_Day_of_Month.GetCurSel())));
	m_Edit_Day_of_Month.SetWindowText(::INT2CString(m_dtStartDate.GetDay()));
	m_Combo_ScheduleType.SetCurSel(emComboScheduleTypeDaily);
	m_Combo_Week_of_Month.SetCurSel(emFirstWeek);
}

void _PDlgServiceSchedule::OnBnClickedOk()
{
	OnOK();
}

BOOL _PDlgServiceSchedule::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN)
		{
			HWND hwnd;

			hwnd = GetDlgItem(IDC_EDIT_COMMENT)->m_hWnd;

			if(pMsg->hwnd == hwnd)
				return CDialog::PreTranslateMessage(pMsg);
		}
	}

	if(pMsg->message == WM_LBUTTONDBLCLK)
	{
		if(pMsg->hwnd == GetDlgItem(IDC_EDIT_ALERT_SUCCESS)->m_hWnd)
		{
			OnBnClickedBuAlertSuccess();
			return TRUE;
		}

		if(pMsg->hwnd == GetDlgItem(IDC_EDIT_ALERT_FAIL)->m_hWnd)
		{
			OnBnClickedBuAlertFail();
			return TRUE;
		}

		if(pMsg->hwnd == GetDlgItem(IDC_EDIT_SERVICE_DEST)->m_hWnd)
		{
			OnBnClickedBuServiceDest();
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

HBRUSH _PDlgServiceSchedule::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(nCtlColor == CTLCOLOR_STATIC)
	{
		if( IDC_STATIC_COMMENT_LIMIT == pWnd->GetDlgCtrlID())
			pDC->SetTextColor(RGB(100,100,100));

		if(IDC_EDIT_ALERT_SUCCESS == pWnd->GetDlgCtrlID())
		{
			if(m_Check_Success_Alert.GetCheck())
			{
				pDC->SetBkColor(RGB(255,255,255));
				return(HBRUSH)GetStockObject(WHITE_BRUSH);
			}
		}
		if(IDC_EDIT_ALERT_FAIL == pWnd->GetDlgCtrlID())
		{
			if(m_Check_Fail_Alert.GetCheck())
			{
				pDC->SetBkColor(RGB(255,255,255));
				return(HBRUSH)GetStockObject(WHITE_BRUSH);
			}
		}
		if(IDC_EDIT_SERVICE_DEST == pWnd->GetDlgCtrlID())
		{
			if(m_ScheduleData.dest_descript.length() > 0)
			{
				pDC->SetBkColor(RGB(255,255,255));
				return(HBRUSH)GetStockObject(WHITE_BRUSH);
			}
		}

		if( IDC_STATIC_MSG == pWnd->GetDlgCtrlID())
			pDC->SetTextColor(RGB(225, 0, 0));
	}

	return hbr;
}

void _PDlgServiceSchedule::SetShowOnlyUI()
{
	m_Edit_ScheduleName.SetReadOnly(TRUE);

	m_Combo_ScheduleType.EnableWindow(FALSE);

	m_Edit_Day_of_Month.SetReadOnly(TRUE);

	m_Combo_Week_of_Month.EnableWindow(FALSE);
	m_Combo_Day_of_Month.EnableWindow(FALSE);

	m_DateTimePicker_ScheduleDate.EnableWindow(FALSE);
	m_DateTimePicker_ScheduleTime.EnableWindow(FALSE);

	m_Check_Sun.EnableWindow(FALSE);
	m_Check_Mon.EnableWindow(FALSE);
	m_Check_Tue.EnableWindow(FALSE);
	m_Check_Wed.EnableWindow(FALSE);
	m_Check_Thu.EnableWindow(FALSE);
	m_Check_Fri.EnableWindow(FALSE);
	m_Check_Sat.EnableWindow(FALSE);

	m_Combo_Service_Action.EnableWindow(FALSE);

	m_Check_Active_Expire.EnableWindow(FALSE);
	m_DateTimePicker_DateTime_Begin.EnableWindow(FALSE);
	m_DateTimePicker_DateTime_End.EnableWindow(FALSE);

	m_Check_Success_Alert.EnableWindow(FALSE);	
	m_Check_Fail_Alert.EnableWindow(FALSE);	

	m_IconEdit_Alert_Success.EnableWindow(FALSE);
	m_BtnAlert_Success.EnableWindow(FALSE);

	m_IconEdit_Service_Dest.EnableWindow(FALSE);
	m_Btn_Service_Dest.EnableWindow(FALSE);

	m_IconEdit_Alert_Fail.EnableWindow(FALSE);
	m_BtnAlert_Fail.EnableWindow(FALSE);

	m_Edit_Comment.SetReadOnly(TRUE);

	m_BtnOK.EnableWindow(FALSE);
	m_BtnOK.ShowWindow(FALSE);

	c_BtnCancel.SetWindowText(_S(IDS_STR_OK));

	m_StaticMsg.SetWindowText(m_strShowOnlyText);

	SetWindowText(_S(IDS_SCHEDULE_DETAIL)/*"스케줄 상세"*/);
}

/**
 * @brief
 *	스케줄의 설정 및 칼렌더 컨트롤에 설정된 이벤트를 넘김
 *
 * @param [in] 
 *
 * @return 
 *
 * @par 수정정보
 *	- 2010-01-03, 이진욱 : 함수정의
 */
void _PDlgServiceSchedule::OnOK()
{
	int nDayInterval = 1;
	int nMonthInterval = 1;
	int nWeeklyInterval = 1;
	int nMonthDate = 0;

	CString strActivate(_T("")), strExpire(_T("")), strDay(_T(""));

	//< 스케줄 명 얻기
	m_Edit_ScheduleName.GetWindowText(m_strSubject);
	if(m_strSubject.GetLength() <= 0)
	{
		MessageBox(_S(IDS_MSG_SCHEDULE_NAME),_S(IDS_MSG_CAPTION_SCHEDULE_ADD),MB_ICONINFORMATION);
		m_Edit_ScheduleName.SetFocus();
		return;
	}

	if(m_ScheduleData.dest_descript.length() <= 0)
	{
		MessageBox(_S(IDS_MSG_SCHEDULE_DEST_SERVICE_NONE),_S(IDS_MSG_CAPTION_SCHEDULE_ADD),MB_ICONINFORMATION);
		OnBnClickedBuServiceDest();
		return;
	}

	//< Date 입력이 정상적인지 확인한다.
	if(m_Check_Active_Expire.GetCheck())
	{
		COleDateTime dtStartDate;  
		COleDateTime dtEndDate;  

		m_DateTimePicker_DateTime_Begin.GetTime(dtStartDate);
		m_DateTimePicker_DateTime_End.GetTime(dtEndDate);

		if (dtEndDate < dtStartDate)
		{
			MessageBox(_S(IDS_MSG_WRONG_ACTIVATE_DURATION),_S(IDS_MSG_CAPTION_SCHEDULE_ADD),MB_ICONINFORMATION);
			return;
		}

		/*if(FALSE == m_bEdit)
		{
			CString strStartDate(""),strStartTime(""), strStartDateTime(_T(""));
			COleDateTime dtReserve;

			m_DateTimePicker_DateTime_Begin.GetWindowText(strStartDate);
			m_DateTimePicker_ScheduleTime.GetWindowText(strStartTime);
			strStartDateTime.Format(_T("%s %s"), strStartDate, strStartTime);

			dtReserve.ParseDateTime(strStartDateTime.GetBuffer(0));
			if(dtReserve < COleDateTime::GetCurrentTime())
			{
				MessageBox(_S(IDS_MSG_DATE_ILLEGALITY_ACTIVATE), _S(IDS_MSG_CAPTION_SCHEDULE_ADD),MB_ICONINFORMATION);
				m_DateTimePicker_DateTime_Begin.SetFocus();
				return;
			}
		}*/
	}

	STRCPY(m_ScheduleData.name,(const char*)m_strSubject);

	m_Edit_Comment.GetWindowText(m_strBody);
	STRCPY(m_ScheduleData.comment,(const char*)m_strBody);

	if(FALSE == m_bEdit)	
		m_ScheduleData.enabled = TRUE;	 // 사용

	//< 스케줄 형태
	if(0 == m_Combo_Service_Action.GetCurSel())
		m_ScheduleData.service_action = SERVICE_SCHEDULE_DATA::emServiceActionStart;	//전일
	else
		m_ScheduleData.service_action = SERVICE_SCHEDULE_DATA::emServiceActionStop;	//전일

	if(m_Check_Active_Expire.GetCheck())
	{
		//패턴등록을 위한 날짜 지정
		m_DateTimePicker_DateTime_Begin.GetTime(m_dtStartDate);
		m_DateTimePicker_DateTime_End.GetTime(m_dtEndDate);

		m_DateTimePicker_DateTime_Begin.GetWindowText(strActivate);
		m_DateTimePicker_DateTime_End.GetWindowText(strExpire);
		
		//< (2011. 06. 08) Activate, Expire는 항상 '00:00:00'에서 시작하여 '23:59:59'로 끝나도록 요청하여 수정함
		strActivate.AppendFormat(_T(" 00:00:00"));	
		strExpire.AppendFormat(_T(" 23:59:59"));

		STRCPY(m_ScheduleData.activate,(const char*)strActivate);
		STRCPY(m_ScheduleData.expire,(const char*)strExpire);
	}
	else
	{
		memset(m_ScheduleData.activate, 0x00, sizeof(m_ScheduleData.activate));
		memset(m_ScheduleData.expire, 0x00, sizeof(m_ScheduleData.expire));
	}

	// 스케줄의 동작 시간을 설정
	COleDateTime dtStartTime;
	m_DateTimePicker_ScheduleTime.GetTime(dtStartTime);
	dtStartTime = CXTPCalendarUtils::ResetDate(dtStartTime);
	dtStartTime.SetTime(dtStartTime.GetHour(), dtStartTime.GetMinute(), 0);
	STRCPY(m_ScheduleData.res_time, util::FormatTimeOnly(dtStartTime).GetBuffer(0));

	memset(m_ScheduleData.res_date, 0x00, sizeof(m_ScheduleData.res_date));	//<날자 초기화
	switch (m_Combo_ScheduleType.GetCurSel())
	{
	case SERVICE_SCHEDULE_DATA::emServiceScheduleReservation:
		{
			m_ScheduleData.type = SERVICE_SCHEDULE_DATA::emServiceScheduleReservation;
			COleDateTime dtStartDate, dtTmpDate;
			m_DateTimePicker_ScheduleDate.GetTime(dtStartDate);
			
			dtTmpDate = COleDateTime::GetCurrentTime();
			dtTmpDate = CXTPCalendarUtils::ResetTime(dtTmpDate);
			
			if(dtStartDate < dtTmpDate)
			{
				MessageBox(_S(IDS_MSG_CONFIRM_SCHEDULE_START), _S(IDS_MSG_CAPTION_SCHEDULE_ADD),MB_ICONINFORMATION);
				m_DateTimePicker_DateTime_Begin.SetFocus();
				return;
			}
			
			dtStartDate = CXTPCalendarUtils::ResetTime(dtStartDate);
			STRCPY(m_ScheduleData.res_date, util::FormatDateOnly(dtStartDate).GetBuffer(0));
		}
		break;
	case SERVICE_SCHEDULE_DATA::emServiceScheduleDaily:
		m_ScheduleData.type = SERVICE_SCHEDULE_DATA::emServiceScheduleDaily;	
		break;
	case SERVICE_SCHEDULE_DATA::emServiceScheduleWeekly:
		m_ScheduleData.type = SERVICE_SCHEDULE_DATA::emServiceScheduleWeekly;	
		GetScheduleDayOfWeek();
		if(0 == m_ScheduleData.basic_wday)
		{
			MessageBox(_S(IDS_MSG_NO_WEEKDAY),_S(IDS_MSG_CAPTION_SCHEDULE_ADD),MB_ICONINFORMATION);
			return;
		}
		break;
	case SERVICE_SCHEDULE_DATA::emServiceScheduleMonthly:

		m_Edit_Day_of_Month.GetWindowText(strDay);
		nMonthDate = (int)atoi(strDay);
		if (nMonthDate < 1 || nMonthDate > 31)
		{
			MsgBox_WrongValueRange(XTP_IDC_EDIT_MONTH_DATE, 1, 31);
			return;
		}

		m_ScheduleData.type = SERVICE_SCHEDULE_DATA::emServiceScheduleMonthly;	

		m_ScheduleData.basic_date = nMonthDate;
		break;
	case SERVICE_SCHEDULE_DATA::emServiceScheduleDayOfWeek:

		m_ScheduleData.type = SERVICE_SCHEDULE_DATA::emServiceScheduleDayOfWeek;	

		GetBackUpMonthly_DayOfWeek();
		break;
	}

	if(m_Check_Success_Alert.GetCheck())
	{
		if(_tcslen(m_ScheduleData.alert_success) <= 0)
		{
			MessageBox(_S(IDS_MSG_CONFIRM_EVENT_ALERT_OBJECT)/*"경고 객체가 설정되지 않았습니다. 경고 객체를 확인하여 주십시오"*/,_S(IDS_MSG_CAPTION_SCHEDULE_ADD),MB_ICONINFORMATION);
			return;
		}
	}

	if(m_Check_Fail_Alert.GetCheck())
	{
		if(_tcslen(m_ScheduleData.alert_fail) <= 0)
		{
			MessageBox(_S(IDS_MSG_CONFIRM_EVENT_ALERT_OBJECT)/*"경고 객체가 설정되지 않았습니다. 경고 객체를 확인하여 주십시오"*/,_S(IDS_MSG_CAPTION_SCHEDULE_ADD),MB_ICONINFORMATION);
			return;
		}
	}

	UpdateData(TRUE);

	CDialog::OnOK();
}

void _PDlgServiceSchedule::OnBnClickedBuServiceDest()
{
	CDlg_Policy_Entity oEntityDlg(this);
	oEntityDlg.SetEntityType(POLICY_ENTITY_SCHEDULE_SERVICE);
	oEntityDlg.SetScheduleDest(m_ScheduleData.dest_type, m_ScheduleData.dest_descript);

	if(oEntityDlg.DoModal() == IDOK)
	{
		oEntityDlg.GetScheduleDest(m_ScheduleData.dest_type, m_ScheduleData.dest_descript);
		m_ScheduleData.dest_descript_service_list = oEntityDlg.GetScheduleDestServiceList();

		SetServiceScheduleDestText();
	}

	UpdateData(FALSE);
}

void _PDlgServiceSchedule::SetServiceScheduleDestText()
{
	switch(m_ScheduleData.dest_type)
	{
	case SERVICE_SCHEDULE_DATA::emServiceObject:
		m_IconEdit_Service_Dest.ResetIcon();
		m_IconEdit_Service_Dest.SetWindowText(m_ScheduleData.dest_descript_service_list.c_str());
		break;
	case SERVICE_SCHEDULE_DATA::emServiceGroup:
		{
			const GROUP_DATA* pGroupData = m_pMaster_thread->GetService_Group_From_Idx(_ttoi(m_ScheduleData.dest_descript.c_str()));
			if(pGroupData)
			{
				m_IconEdit_Service_Dest.ResetIcon();
				m_IconEdit_Service_Dest.SetIcon(IDI_GROUP);
				m_IconEdit_Service_Dest.SetWindowText(pGroupData->group_name);
			}
		}
		break;				
	case SERVICE_SCHEDULE_DATA::emServiceType:
		m_IconEdit_Service_Dest.ResetIcon();
		m_IconEdit_Service_Dest.SetIcon(IDI_SERVICE);
		m_IconEdit_Service_Dest.SetWindowText(_S(IDS_STR_ALL_SERVICE_TYPE , ServiceType2Str(_ttoi(m_ScheduleData.dest_descript.c_str()), 0).GetBuffer(0)));
		break;
	default:
		m_IconEdit_Service_Dest.ResetIcon();
		m_IconEdit_Service_Dest.SetWindowText(_T(""));
		break;
	}
}

void _PDlgServiceSchedule::OnBnClickedBuAlertSuccess()
{
	SetAlertData(IDC_BU_ALERT_SUCCESS);
}

void _PDlgServiceSchedule::OnBnClickedBuAlertFail()
{
	SetAlertData(IDC_BU_ALERT_FAIL);
}

void _PDlgServiceSchedule::SetAlertData(INT nID)
{
	CDlg_Policy_Entity oEntityDlg(this);
	oEntityDlg.SetEntityType(POLICY_ENTITY_ALERT);

	if(IDC_BU_ALERT_SUCCESS == nID)
	{
		if(m_ScheduleData.alert_success[0] != '\0')
		{
			oEntityDlg.SetAlertObject(m_ScheduleData.alert_success);
		}

		if(oEntityDlg.DoModal() == IDOK)
		{
			INT nObjectIndex = 0;
			INT nGroupIndex = 0;
			CString strAlertName;
			CString strAlertGroupName;

			oEntityDlg.GetAlertObject(nObjectIndex, strAlertName, nGroupIndex, strAlertGroupName);

			if(strAlertName.GetLength() > 0)
			{
				m_ScheduleData.alert_object_index_success = nObjectIndex;
				m_ScheduleData.alert_group_index_success = 0;
				STRCPY(m_ScheduleData.alert_success, (const char*)strAlertName);

				CString str = m_ScheduleData.alert_success;

				m_IconEdit_Alert_Success.SetWindowText(str);
				m_IconEdit_Alert_Success.ResetIcon();		// 그룹아이콘을 제거합니다.
			}
			else if(strAlertGroupName.GetLength() > 0)
			{
				m_ScheduleData.alert_object_index_success = 0;
				m_ScheduleData.alert_group_index_success = nGroupIndex;
				STRCPY(m_ScheduleData.alert_success, (const char*)strAlertGroupName);

				CString str = m_ScheduleData.alert_success;

				m_IconEdit_Alert_Success.SetIcon(IDI_GROUP);		// 아이콘을 설정합니다.
				m_IconEdit_Alert_Success.SetWindowText(str);
			}
			else
			{
				ResetAlertData(IDC_BU_ALERT_SUCCESS);		// Alert객체 데이터 초기화
			}
		}
	}
	else if(IDC_BU_ALERT_FAIL == nID)
	{
		if(m_ScheduleData.alert_fail[0] != '\0')
		{
			oEntityDlg.SetAlertObject(m_ScheduleData.alert_fail);
		}

		if(oEntityDlg.DoModal() == IDOK)
		{
			INT nObjectIndex = 0;
			INT nGroupIndex = 0;
			CString strAlertName;
			CString strAlertGroupName;

			oEntityDlg.GetAlertObject(nObjectIndex, strAlertName, nGroupIndex, strAlertGroupName);

			if(strAlertName.GetLength() > 0)
			{
				m_ScheduleData.alert_object_index_fail = nObjectIndex;
				m_ScheduleData.alert_group_index_fail = 0;
				STRCPY(m_ScheduleData.alert_fail, (const char*)strAlertName);

				CString str = m_ScheduleData.alert_fail;

				m_IconEdit_Alert_Fail.SetWindowText(str);
				m_IconEdit_Alert_Fail.ResetIcon();		// 그룹아이콘을 제거합니다.
			}
			else if(strAlertGroupName.GetLength() > 0)
			{
				m_ScheduleData.alert_object_index_fail = 0;
				m_ScheduleData.alert_group_index_fail = nGroupIndex;
				STRCPY(m_ScheduleData.alert_fail, (const char*)strAlertGroupName);

				CString str = m_ScheduleData.alert_fail;

				m_IconEdit_Alert_Fail.SetIcon(IDI_GROUP);		// 아이콘을 설정합니다.
				m_IconEdit_Alert_Fail.SetWindowText(str);
			}
			else
			{
				ResetAlertData(IDC_BU_ALERT_FAIL);		// Alert객체 데이터 초기화
			}
		}
	}
}	

void _PDlgServiceSchedule::ResetAlertData(INT nID)		// Alert객체 데이터 초기화
{
	if(IDC_BU_ALERT_SUCCESS == nID)
	{
		m_ScheduleData.alert_object_index_success = 0;
		m_ScheduleData.alert_group_index_success = 0;
		memset(m_ScheduleData.alert_success, 0x00, sizeof(m_ScheduleData.alert_success));
		m_IconEdit_Alert_Success.SetWindowText("");
		m_IconEdit_Alert_Success.ResetIcon();		// 그룹아이콘을 제거합니다.
	}
	else if(IDC_BU_ALERT_FAIL == nID)
	{
		m_ScheduleData.alert_object_index_fail = 0;
		m_ScheduleData.alert_group_index_fail = 0;
		memset(m_ScheduleData.alert_fail, 0x00, sizeof(m_ScheduleData.alert_fail));
		m_IconEdit_Alert_Fail.SetWindowText("");
		m_IconEdit_Alert_Fail.ResetIcon();		// 그룹아이콘을 제거합니다.
	}

}

void _PDlgServiceSchedule::OnBnClickedCheckAlert()
{
	if(!m_Check_Success_Alert.GetCheck())
	{
		m_IconEdit_Alert_Success.EnableWindow(FALSE);
		m_BtnAlert_Success.EnableWindow(FALSE);
		ResetAlertData(IDC_BU_ALERT_SUCCESS);
	}
	else
	{
		m_IconEdit_Alert_Success.EnableWindow(TRUE);
		m_BtnAlert_Success.EnableWindow(TRUE);
	}

	if(!m_Check_Fail_Alert.GetCheck())
	{
		m_IconEdit_Alert_Fail.EnableWindow(FALSE);
		m_BtnAlert_Fail.EnableWindow(FALSE);
		ResetAlertData(IDC_BU_ALERT_FAIL);
	}
	else
	{
		m_IconEdit_Alert_Fail.EnableWindow(TRUE);
		m_BtnAlert_Fail.EnableWindow(TRUE);
	}
}

void _PDlgServiceSchedule::OnBnClickedCheckTerm()
{
	if(m_Check_Active_Expire.GetCheck())
	{
		m_DateTimePicker_DateTime_Begin.EnableWindow(TRUE);
		m_DateTimePicker_DateTime_End.EnableWindow(TRUE);
	}
	else
	{
		m_DateTimePicker_DateTime_Begin.EnableWindow(FALSE);
		m_DateTimePicker_DateTime_End.EnableWindow(FALSE);
	}
}

void _PDlgServiceSchedule::OnCbnSelchangeComboScheduleType()
{
	int iSchedule_type;
	
	iSchedule_type = m_Combo_ScheduleType.GetCurSel();
	
	switch (iSchedule_type)
	{
	case SERVICE_SCHEDULE_DATA::emServiceScheduleReservation:
		SetScheduleTypeReservation();
		break;
	case SERVICE_SCHEDULE_DATA::emServiceScheduleDaily:
		SetScheduleTypeDaily();
		break;
	case SERVICE_SCHEDULE_DATA::emServiceScheduleWeekly:
		SetScheduleTypeWeekly();
		break;
	case SERVICE_SCHEDULE_DATA::emServiceScheduleMonthly:
		SetScheduleTypeMonthly();
		break;
	case SERVICE_SCHEDULE_DATA::emServiceScheduleDayOfWeek:
		SetScheduleTypeDayOfWeek();
		break;
	default:
		break;
	}
}
void _PDlgServiceSchedule::SetScheduleTypeReservation()
{
	m_DateTimePicker_ScheduleDate.ShowWindow(SW_SHOW);

	m_Static_Week_of_Month.ShowWindow(SW_HIDE);
	m_Static_Day.ShowWindow(SW_HIDE);
	m_Edit_Day_of_Month.ShowWindow(SW_HIDE);
	m_Static_Day_Limit.ShowWindow(SW_HIDE);

	m_Static_Day_of_Month.ShowWindow(SW_HIDE);
	m_Combo_Week_of_Month.ShowWindow(SW_HIDE);
	m_Combo_Day_of_Month.ShowWindow(SW_HIDE);

	m_Static_StartTerm.ShowWindow(SW_HIDE);

	m_ScheduleWeekDay.ShowWindow(SW_HIDE);
	m_Check_Sun.ShowWindow(SW_HIDE);
	m_Check_Mon.ShowWindow(SW_HIDE);
	m_Check_Tue.ShowWindow(SW_HIDE);
	m_Check_Wed.ShowWindow(SW_HIDE);
	m_Check_Thu.ShowWindow(SW_HIDE);
	m_Check_Fri.ShowWindow(SW_HIDE);
	m_Check_Sat.ShowWindow(SW_HIDE);
}

void _PDlgServiceSchedule::SetScheduleTypeDaily()
{
	m_DateTimePicker_ScheduleDate.ShowWindow(SW_HIDE);

	m_Static_Week_of_Month.ShowWindow(SW_HIDE);
	m_Static_Day.ShowWindow(SW_HIDE);
	m_Edit_Day_of_Month.ShowWindow(SW_HIDE);
	m_Static_Day_Limit.ShowWindow(SW_HIDE);

	m_Static_Day_of_Month.ShowWindow(SW_HIDE);
	m_Combo_Week_of_Month.ShowWindow(SW_HIDE);
	m_Combo_Day_of_Month.ShowWindow(SW_HIDE);

	m_Static_StartTerm.ShowWindow(SW_SHOW);
	
	m_ScheduleWeekDay.ShowWindow(SW_HIDE);
	m_Check_Sun.ShowWindow(SW_HIDE);
	m_Check_Mon.ShowWindow(SW_HIDE);
	m_Check_Tue.ShowWindow(SW_HIDE);
	m_Check_Wed.ShowWindow(SW_HIDE);
	m_Check_Thu.ShowWindow(SW_HIDE);
	m_Check_Fri.ShowWindow(SW_HIDE);
	m_Check_Sat.ShowWindow(SW_HIDE);
}

void _PDlgServiceSchedule::SetScheduleTypeWeekly()
{
	m_DateTimePicker_ScheduleDate.ShowWindow(SW_HIDE);

	m_Static_Week_of_Month.ShowWindow(SW_HIDE);
	m_Static_Day.ShowWindow(SW_HIDE);
	m_Edit_Day_of_Month.ShowWindow(SW_HIDE);
	m_Static_Day_Limit.ShowWindow(SW_HIDE);

	m_Static_Day_of_Month.ShowWindow(SW_HIDE);
	m_Combo_Week_of_Month.ShowWindow(SW_HIDE);
	m_Combo_Day_of_Month.ShowWindow(SW_HIDE);

	m_Static_StartTerm.ShowWindow(SW_SHOW);

	m_ScheduleWeekDay.ShowWindow(SW_SHOW);
	m_Check_Sun.ShowWindow(SW_SHOW);
	m_Check_Mon.ShowWindow(SW_SHOW);
	m_Check_Tue.ShowWindow(SW_SHOW);
	m_Check_Wed.ShowWindow(SW_SHOW);
	m_Check_Thu.ShowWindow(SW_SHOW);
	m_Check_Fri.ShowWindow(SW_SHOW);
	m_Check_Sat.ShowWindow(SW_SHOW);
}

void _PDlgServiceSchedule::SetScheduleTypeMonthly()
{
	m_DateTimePicker_ScheduleDate.ShowWindow(SW_HIDE);

	m_Static_Week_of_Month.ShowWindow(SW_HIDE);
	m_Static_Day.ShowWindow(SW_SHOW);
	m_Edit_Day_of_Month.ShowWindow(SW_SHOW);
	m_Static_Day_Limit.ShowWindow(SW_SHOW);

	m_Static_Day_of_Month.ShowWindow(SW_SHOW);
	m_Combo_Week_of_Month.ShowWindow(SW_HIDE);
	m_Combo_Day_of_Month.ShowWindow(SW_HIDE);

	m_Static_StartTerm.ShowWindow(SW_SHOW);

	m_ScheduleWeekDay.ShowWindow(SW_HIDE);
	m_Check_Sun.ShowWindow(SW_HIDE);
	m_Check_Mon.ShowWindow(SW_HIDE);
	m_Check_Tue.ShowWindow(SW_HIDE);
	m_Check_Wed.ShowWindow(SW_HIDE);
	m_Check_Thu.ShowWindow(SW_HIDE);
	m_Check_Fri.ShowWindow(SW_HIDE);
	m_Check_Sat.ShowWindow(SW_HIDE);
}

void _PDlgServiceSchedule::SetScheduleTypeDayOfWeek()
{
	m_DateTimePicker_ScheduleDate.ShowWindow(SW_HIDE);

	m_Static_Week_of_Month.ShowWindow(SW_HIDE);
	m_Static_Day.ShowWindow(SW_HIDE);
	m_Edit_Day_of_Month.ShowWindow(SW_HIDE);
	m_Static_Day_Limit.ShowWindow(SW_HIDE);

	m_Static_Day_of_Month.ShowWindow(SW_SHOW);
	m_Combo_Week_of_Month.ShowWindow(SW_SHOW);
	m_Combo_Day_of_Month.ShowWindow(SW_SHOW);

	m_Static_StartTerm.ShowWindow(SW_HIDE);

	m_ScheduleWeekDay.ShowWindow(SW_HIDE);
	m_Check_Sun.ShowWindow(SW_HIDE);
	m_Check_Mon.ShowWindow(SW_HIDE);
	m_Check_Tue.ShowWindow(SW_HIDE);
	m_Check_Wed.ShowWindow(SW_HIDE);
	m_Check_Thu.ShowWindow(SW_HIDE);
	m_Check_Fri.ShowWindow(SW_HIDE);
	m_Check_Sat.ShowWindow(SW_HIDE);
}

void _PDlgServiceSchedule::OnBnClickedCheckSun()
{
}

void _PDlgServiceSchedule::OnBnClickedCheckMon()
{
}

void _PDlgServiceSchedule::OnBnClickedCheckTue()
{
}

void _PDlgServiceSchedule::OnBnClickedCheckWed()
{
}

void _PDlgServiceSchedule::OnBnClickedCheckThu()
{
}

void _PDlgServiceSchedule::OnBnClickedCheckFri()
{
}

void _PDlgServiceSchedule::OnBnClickedCheckSat()
{
}

void _PDlgServiceSchedule::GetScheduleDayOfWeek()
{
	m_ScheduleData.basic_wday = 0;

	if(m_Check_Sun.GetCheck())
		m_ScheduleData.basic_wday |= xtpCalendarDaySunday;
	if(m_Check_Mon.GetCheck())
		m_ScheduleData.basic_wday |= xtpCalendarDayMonday;
	if(m_Check_Tue.GetCheck())
		m_ScheduleData.basic_wday |= xtpCalendarDayTuesday;
	if(m_Check_Wed.GetCheck())
		m_ScheduleData.basic_wday |= xtpCalendarDayWednesday;
	if(m_Check_Thu.GetCheck())
		m_ScheduleData.basic_wday |= xtpCalendarDayThursday;
	if(m_Check_Fri.GetCheck())
		m_ScheduleData.basic_wday |= xtpCalendarDayFriday;
	if(m_Check_Sat.GetCheck())
		m_ScheduleData.basic_wday |= xtpCalendarDaySaturday;
}

void _PDlgServiceSchedule::GetBackUpMonthly_DayOfWeek()
{
	if(emSun == m_Combo_Day_of_Month.GetCurSel())
		m_ScheduleData.basic_wday = xtpCalendarDaySunday;
	else if(emMon == m_Combo_Day_of_Month.GetCurSel())
		m_ScheduleData.basic_wday = xtpCalendarDayMonday;
	else if(emTue == m_Combo_Day_of_Month.GetCurSel())
		m_ScheduleData.basic_wday = xtpCalendarDayTuesday;
	else if(emWed == m_Combo_Day_of_Month.GetCurSel())
		m_ScheduleData.basic_wday = xtpCalendarDayWednesday;
	else if(emThu == m_Combo_Day_of_Month.GetCurSel())
		m_ScheduleData.basic_wday = xtpCalendarDayThursday;
	else if(emFri == m_Combo_Day_of_Month.GetCurSel())
		m_ScheduleData.basic_wday = xtpCalendarDayFriday;
	else if(emSat == m_Combo_Day_of_Month.GetCurSel())
		m_ScheduleData.basic_wday = xtpCalendarDaySaturday;


	if (emFirstWeek == m_Combo_Week_of_Month.GetCurSel())
		m_ScheduleData.basic_week = xtpCalendarWeekFirst;
	else if (emSecondWeek == m_Combo_Week_of_Month.GetCurSel())
		m_ScheduleData.basic_week = xtpCalendarWeekSecond;
	else if (emThirdWeek == m_Combo_Week_of_Month.GetCurSel())
		m_ScheduleData.basic_week = xtpCalendarWeekThird;
	else if (emFourthWeek == m_Combo_Week_of_Month.GetCurSel())
		m_ScheduleData.basic_week = xtpCalendarWeekFourth;
	else if (emLastWeek == m_Combo_Week_of_Month.GetCurSel())
		m_ScheduleData.basic_week = xtpCalendarWeekLast;
}

void _PDlgServiceSchedule::AddEndDate_ResetTime(COleDateTime dtStartDate, COleDateTime& rdtEndDate, int nDays)
{
	COleDateTimeSpan spDiff = CXTPCalendarUtils::ResetTime(rdtEndDate) -
		CXTPCalendarUtils::ResetTime(dtStartDate);
	if (nDays > 0 || nDays < 0 && (DWORD)(double)spDiff >= (DWORD)(-1 * nDays) )
	{
		rdtEndDate = CXTPCalendarUtils::ResetTime(rdtEndDate) + COleDateTimeSpan(nDays,0,0,0);
	}
}

/**
 * @brief
 *	작업 데이터를 통해 값을 통해 실제 스케줄 값을 설정한다.
 *
 * @param [in] 
 *
 * @return 
 *
 * @par 수정정보
 *	- 2010-06-23, 이진욱 : 함수정의
 */
void _PDlgServiceSchedule::UpdateControlsFromData()
{
	if((_tcslen(m_ScheduleData.activate) <= 0) || 0 == _tcscmp(m_ScheduleData.activate, __NULL_DATETIME_STRING)) 
	{
		m_dtStartDate = COleDateTime::GetCurrentTime();
		m_dtStartDate = CXTPCalendarUtils::ResetTime(m_dtStartDate);
	}
	else
	{
		m_dtStartDate.ParseDateTime(m_ScheduleData.activate, VAR_DATEVALUEONLY);
	}

	if((_tcslen(m_ScheduleData.expire) <= 0) || 0 == _tcscmp(m_ScheduleData.expire, __NULL_DATETIME_STRING))
	{
		m_Check_Active_Expire.SetCheck(FALSE);
		m_dtEndDate = COleDateTime::GetCurrentTime();
		m_dtEndDate = CXTPCalendarUtils::ResetTime(m_dtEndDate);
	}
	else
	{
		m_Check_Active_Expire.SetCheck(TRUE);
		m_dtEndDate.ParseDateTime(m_ScheduleData.expire, VAR_DATEVALUEONLY);
	}

	m_DateTimePicker_DateTime_Begin.SetTime(m_dtStartDate);
	m_DateTimePicker_DateTime_End.SetTime(m_dtEndDate);

	//< 동작 시간 설정
	COleDateTime dtTmpEndDate;
	dtTmpEndDate.ParseDateTime(m_ScheduleData.res_time, VAR_TIMEVALUEONLY);
	m_DateTimePicker_ScheduleTime.SetTime(dtTmpEndDate);

	INT nSelectedWeekday = NewBackupUtil::GetDayOfWeek(m_dtStartDate);
	SetWeekDay(nSelectedWeekday);
		
	// 스케줄 패턴에 따라 스케줄 타잎값을 지정한다.
	switch (m_ScheduleData.type)
	{
	case SERVICE_SCHEDULE_DATA::emServiceScheduleReservation:
		m_Combo_ScheduleType.SetCurSel(SERVICE_SCHEDULE_DATA::emServiceScheduleReservation);
		dtTmpEndDate.ParseDateTime(m_ScheduleData.res_date, VAR_DATEVALUEONLY);
		m_DateTimePicker_ScheduleDate.SetTime(dtTmpEndDate);
		break;
	case SERVICE_SCHEDULE_DATA::emServiceScheduleDaily:
		m_Combo_ScheduleType.SetCurSel(SERVICE_SCHEDULE_DATA::emServiceScheduleDaily);
		break;
	case SERVICE_SCHEDULE_DATA::emServiceScheduleWeekly:
		m_Combo_ScheduleType.SetCurSel(SERVICE_SCHEDULE_DATA::emServiceScheduleWeekly);

		if (xtpCalendarDayMonday == ( m_ScheduleData.basic_wday & xtpCalendarDayMonday))
			m_Check_Mon.SetCheck(TRUE);
		else
			m_Check_Mon.SetCheck(FALSE);

		if (xtpCalendarDayTuesday == ( m_ScheduleData.basic_wday & xtpCalendarDayTuesday))
			m_Check_Tue.SetCheck(TRUE);
		else
			m_Check_Tue.SetCheck(FALSE);

		if (xtpCalendarDayWednesday == ( m_ScheduleData.basic_wday & xtpCalendarDayWednesday))
			m_Check_Wed.SetCheck(TRUE);
		else
			m_Check_Wed.SetCheck(FALSE);

		if (xtpCalendarDayThursday == ( m_ScheduleData.basic_wday & xtpCalendarDayThursday))
			m_Check_Thu.SetCheck(TRUE);
		else
			m_Check_Thu.SetCheck(FALSE);

		if (xtpCalendarDayFriday == ( m_ScheduleData.basic_wday & xtpCalendarDayFriday))
			m_Check_Fri.SetCheck(TRUE);
		else
			m_Check_Fri.SetCheck(FALSE);

		if (xtpCalendarDaySaturday == ( m_ScheduleData.basic_wday & xtpCalendarDaySaturday))
			m_Check_Sat.SetCheck(TRUE);
		else
			m_Check_Sat.SetCheck(FALSE);

		if (xtpCalendarDaySunday == ( m_ScheduleData.basic_wday & xtpCalendarDaySunday))
			m_Check_Sun.SetCheck(TRUE);
		else
			m_Check_Sun.SetCheck(FALSE);
		break;
	case SERVICE_SCHEDULE_DATA::emServiceScheduleMonthly:
		m_Combo_ScheduleType.SetCurSel(SERVICE_SCHEDULE_DATA::emServiceScheduleMonthly);
		m_Edit_Day_of_Month.SetWindowText(::INT2CString(m_ScheduleData.basic_date));
		break;
	case SERVICE_SCHEDULE_DATA::emServiceScheduleDayOfWeek:
		m_Combo_ScheduleType.SetCurSel(SERVICE_SCHEDULE_DATA::emServiceScheduleDayOfWeek);
		if(xtpCalendarDaySunday == m_ScheduleData.basic_wday)
			m_Combo_Day_of_Month.SetCurSel(emSun);
		else if(xtpCalendarDayMonday == m_ScheduleData.basic_wday)
			m_Combo_Day_of_Month.SetCurSel(emMon);
		else if(xtpCalendarDayTuesday == m_ScheduleData.basic_wday)
			m_Combo_Day_of_Month.SetCurSel(emTue);
		else if(xtpCalendarDayWednesday == m_ScheduleData.basic_wday)
			m_Combo_Day_of_Month.SetCurSel(emWed);
		else if(xtpCalendarDayThursday == m_ScheduleData.basic_wday)
			m_Combo_Day_of_Month.SetCurSel(emThu);
		else if(xtpCalendarDayFriday == m_ScheduleData.basic_wday)
			m_Combo_Day_of_Month.SetCurSel(emFri);
		else if(xtpCalendarDaySaturday == m_ScheduleData.basic_wday)
			m_Combo_Day_of_Month.SetCurSel(emSat);

		if (xtpCalendarWeekFirst == m_ScheduleData.basic_week)
			m_Combo_Week_of_Month.SetCurSel(emFirstWeek);
		else if (xtpCalendarWeekSecond == m_ScheduleData.basic_week)
			m_Combo_Week_of_Month.SetCurSel(emSecondWeek);
		else if (xtpCalendarWeekThird == m_ScheduleData.basic_week)
			m_Combo_Week_of_Month.SetCurSel(emThirdWeek);
		else if (xtpCalendarWeekFourth == m_ScheduleData.basic_week)
			m_Combo_Week_of_Month.SetCurSel(emFourthWeek);
		else if (xtpCalendarWeekLast == m_ScheduleData.basic_week)
			m_Combo_Week_of_Month.SetCurSel(emLastWeek);
		break;
	default:
		return;
	}

	switch(m_ScheduleData.service_action)
	{
		case SERVICE_SCHEDULE_DATA::emServiceActionStart:
			m_Combo_Service_Action.SetCurSel(0);
			break;
		case SERVICE_SCHEDULE_DATA::emServiceActionStop:
			m_Combo_Service_Action.SetCurSel(1);
			break;
		default:
			break;
	}

	SetServiceScheduleDestText();	//< 대상 서비스 표시

	//< 스케줄 타잎에 따른 콤보 UI의 Refresh
	OnCbnSelchangeComboScheduleType();

	if(m_ScheduleData.alert_success[0] != '\0')				//< Alert 정보 설정
	{
		CString str;
		str.Format("%s", m_ScheduleData.alert_success);

		m_IconEdit_Alert_Success.SetIcon(IDI_GROUP);		//< 아이콘을 설정합니다.
		m_IconEdit_Alert_Success.SetWindowText(str);

		m_Check_Success_Alert.SetCheck(TRUE);
	}

	if(m_ScheduleData.alert_fail[0] != '\0')				//< Alert 정보 설정
	{
		CString str;
		str.Format("%s", m_ScheduleData.alert_fail);

		m_IconEdit_Alert_Fail.SetIcon(IDI_GROUP);		//< 아이콘을 설정합니다.
		m_IconEdit_Alert_Fail.SetWindowText(str);

		m_Check_Fail_Alert.SetCheck(TRUE);
	}

	m_Edit_ScheduleName.SetWindowText(m_ScheduleData.name);
	m_Edit_Comment.SetWindowText(m_ScheduleData.comment);

	UpdateData(FALSE);
}

void _PDlgServiceSchedule::MsgBox_WrongValueRange(UINT nCtrlID, int nMin, int nMax)
{
	if (GetDlgItem(nCtrlID))
		GetDlgItem(nCtrlID)->SetFocus();

	CString strFormat = CXTPCalendarUtils::LoadString(XTP_IDS_CALENDAR_WRONG_VALUE_RANGE);
	CString strMsg, strVal1, strVal2;
	strVal1.Format(_T("%d"), nMin);
	strVal2.Format(_T("%d"), nMax);

	strMsg.Format(strFormat, (LPCTSTR)strVal1, (LPCTSTR)strVal2);

	AfxMessageBox(strMsg);
}

int _PDlgServiceSchedule::_AddString(CComboBox& wndCB, UINT nStrResID, DWORD_PTR dwItemData)
{
	int nIndex = wndCB.AddString(CXTPCalendarUtils::LoadString(nStrResID));
	wndCB.SetItemData(nIndex, dwItemData);
	return nIndex;
}

int _PDlgServiceSchedule::_AddLocaleString(CComboBox& wndCB, LCTYPE lcidStr, DWORD_PTR dwItemData)
{
	int nIndex = wndCB.AddString(CXTPCalendarUtils::GetLocaleString(lcidStr, 255));
	wndCB.SetItemData(nIndex, dwItemData);
	return nIndex;
}

void _PDlgServiceSchedule::InitDayOfWeekCBs(CComboBox& wndCB)
{
	_AddLocaleString(wndCB, LOCALE_SDAYNAME1, xtpCalendarDayMonday);
	_AddLocaleString(wndCB, LOCALE_SDAYNAME2, xtpCalendarDayTuesday);
	_AddLocaleString(wndCB, LOCALE_SDAYNAME3, xtpCalendarDayWednesday);
	_AddLocaleString(wndCB, LOCALE_SDAYNAME4, xtpCalendarDayThursday);
	_AddLocaleString(wndCB, LOCALE_SDAYNAME5, xtpCalendarDayFriday);
	_AddLocaleString(wndCB, LOCALE_SDAYNAME6, xtpCalendarDaySaturday);
	_AddLocaleString(wndCB, LOCALE_SDAYNAME7, xtpCalendarDaySunday);

	wndCB.SetCurSel(0);
}

void _PDlgServiceSchedule::InitWhichDayCBs(CComboBox& wndCB)
{
	_AddString(wndCB, IDS_SCHEDULE_FIRST_WEEK,   xtpCalendarWeekFirst);
	_AddString(wndCB, IDS_SCHEDULE_SECOND_WEEK,  xtpCalendarWeekSecond);
	_AddString(wndCB, IDS_SCHEDULE_THIRD_WEEK,   xtpCalendarWeekThird);
	_AddString(wndCB, IDS_SCHEDULE_FOURTH_WEEK,  xtpCalendarWeekFourth);
	_AddString(wndCB, IDS_SCHEDULE_LAST_WEEK,    xtpCalendarWeekLast);

	wndCB.SetCurSel(0);
}

void _PDlgServiceSchedule::SetWeekDay(INT nSelectedWeekday)
{
	switch(nSelectedWeekday)
	{
	case emSun:
		m_Check_Sun.SetCheck(TRUE);
		break;
	case emMon:
		m_Check_Mon.SetCheck(TRUE);
		break;
	case emTue:
		m_Check_Tue.SetCheck(TRUE);
		break;
	case emWed:
		m_Check_Wed.SetCheck(TRUE);
		break;
	case emThu:
		m_Check_Thu.SetCheck(TRUE);
		break;
	case emFri:
		m_Check_Fri.SetCheck(TRUE);
		break;
	case emSat:
		m_Check_Sat.SetCheck(TRUE);
		break;
	default:
		TRACE("\n_PDlgServiceSchedule::SetWeekDay() - Wrong nSelectedWeekday");
		break;
	}
}