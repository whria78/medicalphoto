// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "msppt9.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// Collection properties

/////////////////////////////////////////////////////////////////////////////
// Collection operations

long Collection::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _Application properties

/////////////////////////////////////////////////////////////////////////////
// _Application operations

LPDISPATCH _Application::GetPresentations()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetWindows()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetActiveWindow()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetActivePresentation()
{
	LPDISPATCH result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetSlideShowWindows()
{
	LPDISPATCH result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetCommandBars()
{
	LPDISPATCH result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Application::GetPath()
{
	CString result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Application::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Application::GetCaption()
{
	CString result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Application::SetCaption(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH _Application::GetAssistant()
{
	LPDISPATCH result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetFileSearch()
{
	LPDISPATCH result;
	InvokeHelper(0x7db, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetFileFind()
{
	LPDISPATCH result;
	InvokeHelper(0x7dc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Application::GetBuild()
{
	CString result;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Application::GetVersion()
{
	CString result;
	InvokeHelper(0x7de, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Application::GetOperatingSystem()
{
	CString result;
	InvokeHelper(0x7df, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Application::GetActivePrinter()
{
	CString result;
	InvokeHelper(0x7e0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long _Application::GetCreator()
{
	long result;
	InvokeHelper(0x7e1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetAddIns()
{
	LPDISPATCH result;
	InvokeHelper(0x7e2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetVbe()
{
	LPDISPATCH result;
	InvokeHelper(0x7e3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Application::Help(LPCTSTR HelpFile, long ContextID)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x7e4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HelpFile, ContextID);
}

void _Application::Quit()
{
	InvokeHelper(0x7e5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

float _Application::GetLeft()
{
	float result;
	InvokeHelper(0x7e9, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void _Application::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7e9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float _Application::GetTop()
{
	float result;
	InvokeHelper(0x7ea, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void _Application::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7ea, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float _Application::GetWidth()
{
	float result;
	InvokeHelper(0x7eb, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void _Application::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float _Application::GetHeight()
{
	float result;
	InvokeHelper(0x7ec, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void _Application::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long _Application::GetWindowState()
{
	long result;
	InvokeHelper(0x7ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Application::SetWindowState(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Application::GetVisible()
{
	long result;
	InvokeHelper(0x7ee, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Application::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Application::GetActive()
{
	long result;
	InvokeHelper(0x7f0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Application::Activate()
{
	InvokeHelper(0x7f1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _Application::GetAnswerWizard()
{
	LPDISPATCH result;
	InvokeHelper(0x7f2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetCOMAddIns()
{
	LPDISPATCH result;
	InvokeHelper(0x7f3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Application::GetProductCode()
{
	CString result;
	InvokeHelper(0x7f4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetDefaultWebOptions()
{
	LPDISPATCH result;
	InvokeHelper(0x7f5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetLanguageSettings()
{
	LPDISPATCH result;
	InvokeHelper(0x7f6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Application::GetShowWindowsInTaskbar()
{
	long result;
	InvokeHelper(0x7f8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Application::SetShowWindowsInTaskbar(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Application::GetFeatureInstall()
{
	long result;
	InvokeHelper(0x7fa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Application::SetFeatureInstall(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7fa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// _Global properties

/////////////////////////////////////////////////////////////////////////////
// _Global operations

LPDISPATCH _Global::GetActivePresentation()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Global::GetActiveWindow()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Global::GetAddIns()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Global::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Global::GetAssistant()
{
	LPDISPATCH result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Global::GetPresentations()
{
	LPDISPATCH result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Global::GetSlideShowWindows()
{
	LPDISPATCH result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Global::GetWindows()
{
	LPDISPATCH result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Global::GetCommandBars()
{
	LPDISPATCH result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Global::GetAnswerWizard()
{
	LPDISPATCH result;
	InvokeHelper(0x7db, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ColorFormat properties

/////////////////////////////////////////////////////////////////////////////
// ColorFormat operations

LPDISPATCH ColorFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ColorFormat::GetCreator()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ColorFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ColorFormat::GetRgb()
{
	long result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ColorFormat::SetRgb(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ColorFormat::GetType()
{
	long result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ColorFormat::GetSchemeColor()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ColorFormat::SetSchemeColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// SlideShowWindow properties

/////////////////////////////////////////////////////////////////////////////
// SlideShowWindow operations

LPDISPATCH SlideShowWindow::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideShowWindow::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideShowWindow::GetView()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideShowWindow::GetPresentation()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long SlideShowWindow::GetIsFullScreen()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

float SlideShowWindow::GetLeft()
{
	float result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void SlideShowWindow::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float SlideShowWindow::GetTop()
{
	float result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void SlideShowWindow::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float SlideShowWindow::GetWidth()
{
	float result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void SlideShowWindow::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float SlideShowWindow::GetHeight()
{
	float result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void SlideShowWindow::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long SlideShowWindow::GetActive()
{
	long result;
	InvokeHelper(0x7db, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideShowWindow::Activate()
{
	InvokeHelper(0x7dc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Selection properties

/////////////////////////////////////////////////////////////////////////////
// Selection operations

LPDISPATCH Selection::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Selection::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Selection::Cut()
{
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::Copy()
{
	InvokeHelper(0x7d4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::Delete()
{
	InvokeHelper(0x7d5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::Unselect()
{
	InvokeHelper(0x7d6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long Selection::GetType()
{
	long result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Selection::GetSlideRange()
{
	LPDISPATCH result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Selection::GetShapeRange()
{
	LPDISPATCH result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Selection::GetTextRange()
{
	LPDISPATCH result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DocumentWindows properties

/////////////////////////////////////////////////////////////////////////////
// DocumentWindows operations

long DocumentWindows::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH DocumentWindows::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DocumentWindows::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DocumentWindows::Item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

void DocumentWindows::Arrange(long arrangeStyle)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 arrangeStyle);
}


/////////////////////////////////////////////////////////////////////////////
// SlideShowWindows properties

/////////////////////////////////////////////////////////////////////////////
// SlideShowWindows operations

long SlideShowWindows::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideShowWindows::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideShowWindows::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideShowWindows::Item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DocumentWindow properties

/////////////////////////////////////////////////////////////////////////////
// DocumentWindow operations

LPDISPATCH DocumentWindow::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DocumentWindow::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DocumentWindow::GetSelection()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DocumentWindow::GetView()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DocumentWindow::GetPresentation()
{
	LPDISPATCH result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long DocumentWindow::GetViewType()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void DocumentWindow::SetViewType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long DocumentWindow::GetBlackAndWhite()
{
	long result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void DocumentWindow::SetBlackAndWhite(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long DocumentWindow::GetActive()
{
	long result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long DocumentWindow::GetWindowState()
{
	long result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void DocumentWindow::SetWindowState(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString DocumentWindow::GetCaption()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

float DocumentWindow::GetLeft()
{
	float result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void DocumentWindow::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7da, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float DocumentWindow::GetTop()
{
	float result;
	InvokeHelper(0x7db, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void DocumentWindow::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7db, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float DocumentWindow::GetWidth()
{
	float result;
	InvokeHelper(0x7dc, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void DocumentWindow::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7dc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float DocumentWindow::GetHeight()
{
	float result;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void DocumentWindow::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void DocumentWindow::FitToPage()
{
	InvokeHelper(0x7de, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void DocumentWindow::Activate()
{
	InvokeHelper(0x7df, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void DocumentWindow::LargeScroll(long Down, long Up, long ToRight, long ToLeft)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x7e0, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Down, Up, ToRight, ToLeft);
}

void DocumentWindow::SmallScroll(long Down, long Up, long ToRight, long ToLeft)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x7e1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Down, Up, ToRight, ToLeft);
}

LPDISPATCH DocumentWindow::NewWindow()
{
	LPDISPATCH result;
	InvokeHelper(0x7e2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void DocumentWindow::Close()
{
	InvokeHelper(0x7e3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH DocumentWindow::GetActivePane()
{
	LPDISPATCH result;
	InvokeHelper(0x7e5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DocumentWindow::GetPanes()
{
	LPDISPATCH result;
	InvokeHelper(0x7e6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long DocumentWindow::GetSplitVertical()
{
	long result;
	InvokeHelper(0x7e7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void DocumentWindow::SetSplitVertical(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7e7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long DocumentWindow::GetSplitHorizontal()
{
	long result;
	InvokeHelper(0x7e8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void DocumentWindow::SetSplitHorizontal(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7e8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH DocumentWindow::RangeFromPoint(long X, long Y)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7e9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		X, Y);
	return result;
}

long DocumentWindow::PointsToScreenPixelsX(float Points)
{
	long result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7ea, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		Points);
	return result;
}

long DocumentWindow::PointsToScreenPixelsY(float Points)
{
	long result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7eb, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		Points);
	return result;
}

void DocumentWindow::ScrollIntoView(float Left, float Top, float Width, float Height, long Start)
{
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_I4;
	InvokeHelper(0x7ec, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Left, Top, Width, Height, Start);
}


/////////////////////////////////////////////////////////////////////////////
// View properties

/////////////////////////////////////////////////////////////////////////////
// View operations

LPDISPATCH View::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH View::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long View::GetType()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long View::GetZoom()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void View::SetZoom(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void View::Paste()
{
	InvokeHelper(0x7d5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH View::GetSlide()
{
	LPDISPATCH result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void View::SetSlide(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void View::GotoSlide(long index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 index);
}

long View::GetDisplaySlideMiniature()
{
	long result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void View::SetDisplaySlideMiniature(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long View::GetZoomToFit()
{
	long result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void View::SetZoomToFit(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// SlideShowView properties

/////////////////////////////////////////////////////////////////////////////
// SlideShowView operations

LPDISPATCH SlideShowView::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideShowView::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long SlideShowView::GetZoom()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideShowView::GetSlide()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long SlideShowView::GetPointerType()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideShowView::SetPointerType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long SlideShowView::GetState()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideShowView::SetState(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long SlideShowView::GetAcceleratorsEnabled()
{
	long result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideShowView::SetAcceleratorsEnabled(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float SlideShowView::GetPresentationElapsedTime()
{
	float result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

float SlideShowView::GetSlideElapsedTime()
{
	float result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void SlideShowView::SetSlideElapsedTime(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH SlideShowView::GetLastSlideViewed()
{
	LPDISPATCH result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long SlideShowView::GetAdvanceMode()
{
	long result;
	InvokeHelper(0x7db, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideShowView::GetPointerColor()
{
	LPDISPATCH result;
	InvokeHelper(0x7dc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long SlideShowView::GetIsNamedShow()
{
	long result;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString SlideShowView::GetSlideShowName()
{
	CString result;
	InvokeHelper(0x7de, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void SlideShowView::DrawLine(float BeginX, float BeginY, float EndX, float EndY)
{
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7df, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 BeginX, BeginY, EndX, EndY);
}

void SlideShowView::EraseDrawing()
{
	InvokeHelper(0x7e0, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void SlideShowView::First()
{
	InvokeHelper(0x7e1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void SlideShowView::Last()
{
	InvokeHelper(0x7e2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void SlideShowView::Next()
{
	InvokeHelper(0x7e3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void SlideShowView::Previous()
{
	InvokeHelper(0x7e4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void SlideShowView::GotoSlide(long index, long ResetSlide)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7e5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 index, ResetSlide);
}

void SlideShowView::GotoNamedShow(LPCTSTR SlideShowName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7e6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SlideShowName);
}

void SlideShowView::EndNamedShow()
{
	InvokeHelper(0x7e7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void SlideShowView::ResetSlideTime()
{
	InvokeHelper(0x7e8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void SlideShowView::Exit()
{
	InvokeHelper(0x7e9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long SlideShowView::GetCurrentShowPosition()
{
	long result;
	InvokeHelper(0x7eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// SlideShowSettings properties

/////////////////////////////////////////////////////////////////////////////
// SlideShowSettings operations

LPDISPATCH SlideShowSettings::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideShowSettings::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideShowSettings::GetPointerColor()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideShowSettings::GetNamedSlideShows()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long SlideShowSettings::GetStartingSlide()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideShowSettings::SetStartingSlide(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long SlideShowSettings::GetEndingSlide()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideShowSettings::SetEndingSlide(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long SlideShowSettings::GetAdvanceMode()
{
	long result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideShowSettings::SetAdvanceMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH SlideShowSettings::Run()
{
	LPDISPATCH result;
	InvokeHelper(0x7d8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long SlideShowSettings::GetLoopUntilStopped()
{
	long result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideShowSettings::SetLoopUntilStopped(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long SlideShowSettings::GetShowType()
{
	long result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideShowSettings::SetShowType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7da, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long SlideShowSettings::GetShowWithNarration()
{
	long result;
	InvokeHelper(0x7db, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideShowSettings::SetShowWithNarration(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7db, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long SlideShowSettings::GetShowWithAnimation()
{
	long result;
	InvokeHelper(0x7dc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideShowSettings::SetShowWithAnimation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7dc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString SlideShowSettings::GetSlideShowName()
{
	CString result;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void SlideShowSettings::SetSlideShowName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long SlideShowSettings::GetRangeType()
{
	long result;
	InvokeHelper(0x7de, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideShowSettings::SetRangeType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7de, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// NamedSlideShows properties

/////////////////////////////////////////////////////////////////////////////
// NamedSlideShows operations

long NamedSlideShows::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH NamedSlideShows::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH NamedSlideShows::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH NamedSlideShows::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

LPDISPATCH NamedSlideShows::Add(LPCTSTR Name, const VARIANT& safeArrayOfSlideIDs)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name, &safeArrayOfSlideIDs);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// NamedSlideShow properties

/////////////////////////////////////////////////////////////////////////////
// NamedSlideShow operations

LPDISPATCH NamedSlideShow::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH NamedSlideShow::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString NamedSlideShow::GetName()
{
	CString result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void NamedSlideShow::Delete()
{
	InvokeHelper(0x7d4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

VARIANT NamedSlideShow::GetSlideIDs()
{
	VARIANT result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

long NamedSlideShow::GetCount()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// PrintOptions properties

/////////////////////////////////////////////////////////////////////////////
// PrintOptions operations

LPDISPATCH PrintOptions::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PrintOptions::GetPrintColorType()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PrintOptions::SetPrintColorType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PrintOptions::GetCollate()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PrintOptions::SetCollate(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PrintOptions::GetFitToPage()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PrintOptions::SetFitToPage(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PrintOptions::GetFrameSlides()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PrintOptions::SetFrameSlides(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PrintOptions::GetNumberOfCopies()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PrintOptions::SetNumberOfCopies(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PrintOptions::GetOutputType()
{
	long result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PrintOptions::SetOutputType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH PrintOptions::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PrintOptions::GetPrintHiddenSlides()
{
	long result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PrintOptions::SetPrintHiddenSlides(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PrintOptions::GetPrintInBackground()
{
	long result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PrintOptions::SetPrintInBackground(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7da, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PrintOptions::GetRangeType()
{
	long result;
	InvokeHelper(0x7db, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PrintOptions::SetRangeType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7db, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH PrintOptions::GetRanges()
{
	LPDISPATCH result;
	InvokeHelper(0x7dc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PrintOptions::GetPrintFontsAsGraphics()
{
	long result;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PrintOptions::SetPrintFontsAsGraphics(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PrintOptions::GetSlideShowName()
{
	CString result;
	InvokeHelper(0x7de, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PrintOptions::SetSlideShowName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7de, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PrintOptions::GetActivePrinter()
{
	CString result;
	InvokeHelper(0x7df, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PrintOptions::SetActivePrinter(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7df, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PrintOptions::GetHandoutOrder()
{
	long result;
	InvokeHelper(0x7e0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PrintOptions::SetHandoutOrder(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7e0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PrintRanges properties

/////////////////////////////////////////////////////////////////////////////
// PrintRanges operations

long PrintRanges::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH PrintRanges::Add(long Start, long End)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7d1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Start, End);
	return result;
}

LPDISPATCH PrintRanges::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void PrintRanges::ClearAll()
{
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH PrintRanges::Item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

LPDISPATCH PrintRanges::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// PrintRange properties

/////////////////////////////////////////////////////////////////////////////
// PrintRange operations

LPDISPATCH PrintRange::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PrintRange::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PrintRange::GetStart()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long PrintRange::GetEnd()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PrintRange::Delete()
{
	InvokeHelper(0x7d5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// AddIns properties

/////////////////////////////////////////////////////////////////////////////
// AddIns operations

long AddIns::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH AddIns::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH AddIns::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH AddIns::Item(VARIANT* index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

LPDISPATCH AddIns::Add(LPCTSTR FileName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		FileName);
	return result;
}

void AddIns::Remove(VARIANT* index)
{
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x7d4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 index);
}


/////////////////////////////////////////////////////////////////////////////
// AddIn properties

/////////////////////////////////////////////////////////////////////////////
// AddIn operations

LPDISPATCH AddIn::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH AddIn::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString AddIn::GetFullName()
{
	CString result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString AddIn::GetName()
{
	CString result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString AddIn::GetPath()
{
	CString result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long AddIn::GetRegistered()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void AddIn::SetRegistered(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long AddIn::GetAutoLoad()
{
	long result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void AddIn::SetAutoLoad(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long AddIn::GetLoaded()
{
	long result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void AddIn::SetLoaded(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// Presentations properties

/////////////////////////////////////////////////////////////////////////////
// Presentations operations

long Presentations::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Presentations::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Presentations::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Presentations::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

LPDISPATCH Presentations::Add(long WithWindow)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		WithWindow);
	return result;
}

LPDISPATCH Presentations::Open(LPCTSTR FileName, long ReadOnly, long Untitled, long WithWindow)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x7d4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		FileName, ReadOnly, Untitled, WithWindow);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Hyperlinks properties

/////////////////////////////////////////////////////////////////////////////
// Hyperlinks operations

long Hyperlinks::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Hyperlinks::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Hyperlinks::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Hyperlinks::Item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Hyperlink properties

/////////////////////////////////////////////////////////////////////////////
// Hyperlink operations

LPDISPATCH Hyperlink::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Hyperlink::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Hyperlink::GetType()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString Hyperlink::GetAddress()
{
	CString result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Hyperlink::SetAddress(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString Hyperlink::GetSubAddress()
{
	CString result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Hyperlink::SetSubAddress(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void Hyperlink::AddToFavorites()
{
	InvokeHelper(0x7d6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString Hyperlink::GetEmailSubject()
{
	CString result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Hyperlink::SetEmailSubject(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString Hyperlink::GetScreenTip()
{
	CString result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Hyperlink::SetScreenTip(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString Hyperlink::GetTextToDisplay()
{
	CString result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Hyperlink::SetTextToDisplay(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long Hyperlink::GetShowandReturn()
{
	long result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Hyperlink::SetShowandReturn(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7da, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void Hyperlink::Follow()
{
	InvokeHelper(0x7db, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Hyperlink::CreateNewDocument(LPCTSTR FileName, long EditNow, long Overwrite)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4;
	InvokeHelper(0x7dc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName, EditNow, Overwrite);
}

void Hyperlink::Delete()
{
	InvokeHelper(0x7dd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// PageSetup properties

/////////////////////////////////////////////////////////////////////////////
// PageSetup operations

LPDISPATCH PageSetup::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PageSetup::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PageSetup::GetFirstSlideNumber()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PageSetup::SetFirstSlideNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PageSetup::GetSlideHeight()
{
	float result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PageSetup::SetSlideHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PageSetup::GetSlideWidth()
{
	float result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PageSetup::SetSlideWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long PageSetup::GetSlideSize()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PageSetup::SetSlideSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PageSetup::GetNotesOrientation()
{
	long result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PageSetup::SetNotesOrientation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PageSetup::GetSlideOrientation()
{
	long result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PageSetup::SetSlideOrientation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// Fonts properties

/////////////////////////////////////////////////////////////////////////////
// Fonts operations

long Fonts::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Fonts::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Fonts::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Fonts::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

void Fonts::Replace(LPCTSTR Original, LPCTSTR Replacement)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Original, Replacement);
}


/////////////////////////////////////////////////////////////////////////////
// ExtraColors properties

/////////////////////////////////////////////////////////////////////////////
// ExtraColors operations

long ExtraColors::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ExtraColors::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ExtraColors::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ExtraColors::Item(long index)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		index);
	return result;
}

void ExtraColors::Add(long Type)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Type);
}


/////////////////////////////////////////////////////////////////////////////
// Slides properties

/////////////////////////////////////////////////////////////////////////////
// Slides operations

long Slides::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Slides::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Slides::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Slides::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

LPDISPATCH Slides::FindBySlideID(long SlideID)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		SlideID);
	return result;
}

LPDISPATCH Slides::Add(long index, long Layout)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7d4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index, Layout);
	return result;
}

long Slides::InsertFromFile(LPCTSTR FileName, long index, long SlideStart, long SlideEnd)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x7d5, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		FileName, index, SlideStart, SlideEnd);
	return result;
}

LPDISPATCH Slides::Range(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x7d6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

LPDISPATCH Slides::Paste(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _Slide properties

/////////////////////////////////////////////////////////////////////////////
// _Slide operations

LPDISPATCH _Slide::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Slide::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Slide::GetShapes()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Slide::GetHeadersFooters()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Slide::GetSlideShowTransition()
{
	LPDISPATCH result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Slide::GetColorScheme()
{
	LPDISPATCH result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Slide::SetColorScheme(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH _Slide::GetBackground()
{
	LPDISPATCH result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Slide::GetName()
{
	CString result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Slide::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _Slide::GetSlideID()
{
	long result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _Slide::GetPrintSteps()
{
	long result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Slide::Select()
{
	InvokeHelper(0x7db, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Slide::Cut()
{
	InvokeHelper(0x7dc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Slide::Copy()
{
	InvokeHelper(0x7dd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long _Slide::GetLayout()
{
	long result;
	InvokeHelper(0x7de, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Slide::SetLayout(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7de, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH _Slide::Duplicate()
{
	LPDISPATCH result;
	InvokeHelper(0x7df, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Slide::Delete()
{
	InvokeHelper(0x7e0, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _Slide::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x7e1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Slide::GetSlideIndex()
{
	long result;
	InvokeHelper(0x7e2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _Slide::GetSlideNumber()
{
	long result;
	InvokeHelper(0x7e3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _Slide::GetDisplayMasterShapes()
{
	long result;
	InvokeHelper(0x7e4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Slide::SetDisplayMasterShapes(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7e4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Slide::GetFollowMasterBackground()
{
	long result;
	InvokeHelper(0x7e5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Slide::SetFollowMasterBackground(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7e5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH _Slide::GetNotesPage()
{
	LPDISPATCH result;
	InvokeHelper(0x7e6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Slide::GetMaster()
{
	LPDISPATCH result;
	InvokeHelper(0x7e7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Slide::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x7e8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Slide::Export(LPCTSTR FileName, LPCTSTR FilterName, long ScaleWidth, long ScaleHeight)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_I4 VTS_I4;
	InvokeHelper(0x7e9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName, FilterName, ScaleWidth, ScaleHeight);
}

LPDISPATCH _Slide::GetScripts()
{
	LPDISPATCH result;
	InvokeHelper(0x7ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// SlideRange properties

/////////////////////////////////////////////////////////////////////////////
// SlideRange operations

LPDISPATCH SlideRange::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideRange::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideRange::GetShapes()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideRange::GetHeadersFooters()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideRange::GetSlideShowTransition()
{
	LPDISPATCH result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideRange::GetColorScheme()
{
	LPDISPATCH result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void SlideRange::SetColorScheme(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH SlideRange::GetBackground()
{
	LPDISPATCH result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString SlideRange::GetName()
{
	CString result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void SlideRange::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long SlideRange::GetSlideID()
{
	long result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long SlideRange::GetPrintSteps()
{
	long result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideRange::Select()
{
	InvokeHelper(0x7db, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void SlideRange::Cut()
{
	InvokeHelper(0x7dc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void SlideRange::Copy()
{
	InvokeHelper(0x7dd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long SlideRange::GetLayout()
{
	long result;
	InvokeHelper(0x7de, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideRange::SetLayout(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7de, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH SlideRange::Duplicate()
{
	LPDISPATCH result;
	InvokeHelper(0x7df, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void SlideRange::Delete()
{
	InvokeHelper(0x7e0, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH SlideRange::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x7e1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long SlideRange::GetSlideIndex()
{
	long result;
	InvokeHelper(0x7e2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long SlideRange::GetSlideNumber()
{
	long result;
	InvokeHelper(0x7e3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long SlideRange::GetDisplayMasterShapes()
{
	long result;
	InvokeHelper(0x7e4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideRange::SetDisplayMasterShapes(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7e4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long SlideRange::GetFollowMasterBackground()
{
	long result;
	InvokeHelper(0x7e5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideRange::SetFollowMasterBackground(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7e5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH SlideRange::GetNotesPage()
{
	LPDISPATCH result;
	InvokeHelper(0x7e6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideRange::GetMaster()
{
	LPDISPATCH result;
	InvokeHelper(0x7e7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideRange::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x7e8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void SlideRange::Export(LPCTSTR FileName, LPCTSTR FilterName, long ScaleWidth, long ScaleHeight)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_I4 VTS_I4;
	InvokeHelper(0x7e9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName, FilterName, ScaleWidth, ScaleHeight);
}

LPDISPATCH SlideRange::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

long SlideRange::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideRange::GetScripts()
{
	LPDISPATCH result;
	InvokeHelper(0x7ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _Master properties

/////////////////////////////////////////////////////////////////////////////
// _Master operations

LPDISPATCH _Master::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Master::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Master::GetShapes()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Master::GetHeadersFooters()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Master::GetColorScheme()
{
	LPDISPATCH result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Master::SetColorScheme(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH _Master::GetBackground()
{
	LPDISPATCH result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Master::GetName()
{
	CString result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Master::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void _Master::Delete()
{
	InvokeHelper(0x7d8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

float _Master::GetHeight()
{
	float result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

float _Master::GetWidth()
{
	float result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Master::GetTextStyles()
{
	LPDISPATCH result;
	InvokeHelper(0x7db, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Master::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x7dc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Master::GetScripts()
{
	LPDISPATCH result;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ColorSchemes properties

/////////////////////////////////////////////////////////////////////////////
// ColorSchemes operations

long ColorSchemes::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ColorSchemes::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ColorSchemes::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ColorSchemes::Item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

LPDISPATCH ColorSchemes::Add(LPDISPATCH Scheme)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Scheme);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ColorScheme properties

/////////////////////////////////////////////////////////////////////////////
// ColorScheme operations

long ColorScheme::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ColorScheme::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ColorScheme::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ColorScheme::Colors(long SchemeColor)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		SchemeColor);
	return result;
}

void ColorScheme::Delete()
{
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// RGBColor properties

/////////////////////////////////////////////////////////////////////////////
// RGBColor operations

LPDISPATCH RGBColor::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH RGBColor::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long RGBColor::GetRgb()
{
	long result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void RGBColor::SetRgb(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// SlideShowTransition properties

/////////////////////////////////////////////////////////////////////////////
// SlideShowTransition operations

LPDISPATCH SlideShowTransition::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH SlideShowTransition::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long SlideShowTransition::GetAdvanceOnClick()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideShowTransition::SetAdvanceOnClick(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long SlideShowTransition::GetAdvanceOnTime()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideShowTransition::SetAdvanceOnTime(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float SlideShowTransition::GetAdvanceTime()
{
	float result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void SlideShowTransition::SetAdvanceTime(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long SlideShowTransition::GetEntryEffect()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideShowTransition::SetEntryEffect(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long SlideShowTransition::GetHidden()
{
	long result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideShowTransition::SetHidden(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long SlideShowTransition::GetLoopSoundUntilNext()
{
	long result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideShowTransition::SetLoopSoundUntilNext(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH SlideShowTransition::GetSoundEffect()
{
	LPDISPATCH result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long SlideShowTransition::GetSpeed()
{
	long result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SlideShowTransition::SetSpeed(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7da, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// SoundEffect properties

/////////////////////////////////////////////////////////////////////////////
// SoundEffect operations

LPDISPATCH SoundEffect::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH SoundEffect::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString SoundEffect::GetName()
{
	CString result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void SoundEffect::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long SoundEffect::GetType()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void SoundEffect::SetType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void SoundEffect::ImportFromFile(LPCTSTR FileName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName);
}

void SoundEffect::Play()
{
	InvokeHelper(0x7d6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// SoundFormat properties

/////////////////////////////////////////////////////////////////////////////
// SoundFormat operations

void SoundFormat::Play()
{
	InvokeHelper(0x7d0, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void SoundFormat::Import(LPCTSTR FileName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName);
}

long SoundFormat::Export(LPCTSTR FileName)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d2, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		FileName);
	return result;
}

long SoundFormat::GetType()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString SoundFormat::GetSourceFullName()
{
	CString result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// HeadersFooters properties

/////////////////////////////////////////////////////////////////////////////
// HeadersFooters operations

LPDISPATCH HeadersFooters::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH HeadersFooters::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH HeadersFooters::GetDateAndTime()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH HeadersFooters::GetSlideNumber()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH HeadersFooters::GetHeader()
{
	LPDISPATCH result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH HeadersFooters::GetFooter()
{
	LPDISPATCH result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long HeadersFooters::GetDisplayOnTitleSlide()
{
	long result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void HeadersFooters::SetDisplayOnTitleSlide(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void HeadersFooters::Clear()
{
	InvokeHelper(0x7d8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Shapes properties

/////////////////////////////////////////////////////////////////////////////
// Shapes operations

LPDISPATCH Shapes::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Shapes::GetCreator()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shapes::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Shapes::GetCount()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shapes::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

LPUNKNOWN Shapes::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shapes::AddCallout(long Type, float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Type, Left, Top, Width, Height);
	return result;
}

LPDISPATCH Shapes::AddConnector(long Type, float BeginX, float BeginY, float EndX, float EndY)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Type, BeginX, BeginY, EndX, EndY);
	return result;
}

LPDISPATCH Shapes::AddCurve(const VARIANT& SafeArrayOfPoints)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&SafeArrayOfPoints);
	return result;
}

LPDISPATCH Shapes::AddLabel(long Orientation, float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Orientation, Left, Top, Width, Height);
	return result;
}

LPDISPATCH Shapes::AddLine(float BeginX, float BeginY, float EndX, float EndY)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		BeginX, BeginY, EndX, EndY);
	return result;
}

LPDISPATCH Shapes::AddPicture(LPCTSTR FileName, long LinkToFile, long SaveWithDocument, float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		FileName, LinkToFile, SaveWithDocument, Left, Top, Width, Height);
	return result;
}

LPDISPATCH Shapes::AddPolyline(const VARIANT& SafeArrayOfPoints)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&SafeArrayOfPoints);
	return result;
}

LPDISPATCH Shapes::AddShape(long Type, float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Type, Left, Top, Width, Height);
	return result;
}

LPDISPATCH Shapes::AddTextEffect(long PresetTextEffect, LPCTSTR Text, LPCTSTR FontName, float FontSize, long FontBold, long FontItalic, float Left, float Top)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_R4 VTS_I4 VTS_I4 VTS_R4 VTS_R4;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		PresetTextEffect, Text, FontName, FontSize, FontBold, FontItalic, Left, Top);
	return result;
}

LPDISPATCH Shapes::AddTextbox(long Orientation, float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Orientation, Left, Top, Width, Height);
	return result;
}

LPDISPATCH Shapes::BuildFreeform(long EditingType, float X1, float Y1)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_R4 VTS_R4;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		EditingType, X1, Y1);
	return result;
}

void Shapes::SelectAll()
{
	InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Shapes::Range(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

long Shapes::GetHasTitle()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shapes::AddTitle()
{
	LPDISPATCH result;
	InvokeHelper(0x7d5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shapes::GetTitle()
{
	LPDISPATCH result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shapes::GetPlaceholders()
{
	LPDISPATCH result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shapes::AddOLEObject(float Left, float Top, float Width, float Height, LPCTSTR ClassName, LPCTSTR FileName, long DisplayAsIcon, LPCTSTR IconFileName, long IconIndex, LPCTSTR IconLabel, long Link)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_I4;
	InvokeHelper(0x7d8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height, ClassName, FileName, DisplayAsIcon, IconFileName, IconIndex, IconLabel, Link);
	return result;
}

LPDISPATCH Shapes::AddComment(float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7d9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height);
	return result;
}

LPDISPATCH Shapes::AddPlaceholder(long Type, float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7da, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Type, Left, Top, Width, Height);
	return result;
}

LPDISPATCH Shapes::AddMediaObject(LPCTSTR FileName, float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7db, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		FileName, Left, Top, Width, Height);
	return result;
}

LPDISPATCH Shapes::Paste()
{
	LPDISPATCH result;
	InvokeHelper(0x7dc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shapes::AddTable(long NumRows, long NumColumns, float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7dd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		NumRows, NumColumns, Left, Top, Width, Height);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Placeholders properties

/////////////////////////////////////////////////////////////////////////////
// Placeholders operations

long Placeholders::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Placeholders::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Placeholders::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Placeholders::Item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// PlaceholderFormat properties

/////////////////////////////////////////////////////////////////////////////
// PlaceholderFormat operations

LPDISPATCH PlaceholderFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PlaceholderFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PlaceholderFormat::GetType()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// FreeformBuilder properties

/////////////////////////////////////////////////////////////////////////////
// FreeformBuilder operations

LPDISPATCH FreeformBuilder::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long FreeformBuilder::GetCreator()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH FreeformBuilder::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void FreeformBuilder::AddNodes(long SegmentType, long EditingType, float X1, float Y1, float X2, float Y2, float X3, float Y3)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SegmentType, EditingType, X1, Y1, X2, Y2, X3, Y3);
}

LPDISPATCH FreeformBuilder::ConvertToShape()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Shape properties

/////////////////////////////////////////////////////////////////////////////
// Shape operations

LPDISPATCH Shape::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Shape::GetCreator()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Shape::Apply()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Shape::Delete()
{
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Shape::Flip(long FlipCmd)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FlipCmd);
}

void Shape::IncrementLeft(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

void Shape::IncrementRotation(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

void Shape::IncrementTop(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

void Shape::PickUp()
{
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Shape::RerouteConnections()
{
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Shape::ScaleHeight(float Factor, long RelativeToOriginalSize, long fScale)
{
	static BYTE parms[] =
		VTS_R4 VTS_I4 VTS_I4;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Factor, RelativeToOriginalSize, fScale);
}

void Shape::ScaleWidth(float Factor, long RelativeToOriginalSize, long fScale)
{
	static BYTE parms[] =
		VTS_R4 VTS_I4 VTS_I4;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Factor, RelativeToOriginalSize, fScale);
}

void Shape::SetShapesDefaultProperties()
{
	InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Shape::Ungroup()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Shape::ZOrder(long ZOrderCmd)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ZOrderCmd);
}

LPDISPATCH Shape::GetAdjustments()
{
	LPDISPATCH result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Shape::GetAutoShapeType()
{
	long result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Shape::SetAutoShapeType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Shape::GetBlackWhiteMode()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Shape::SetBlackWhiteMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH Shape::GetCallout()
{
	LPDISPATCH result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Shape::GetConnectionSiteCount()
{
	long result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Shape::GetConnector()
{
	long result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetConnectorFormat()
{
	LPDISPATCH result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetFill()
{
	LPDISPATCH result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetGroupItems()
{
	LPDISPATCH result;
	InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

float Shape::GetHeight()
{
	float result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void Shape::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long Shape::GetHorizontalFlip()
{
	long result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

float Shape::GetLeft()
{
	float result;
	InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void Shape::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH Shape::GetLine()
{
	LPDISPATCH result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Shape::GetLockAspectRatio()
{
	long result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Shape::SetLockAspectRatio(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x71, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString Shape::GetName()
{
	CString result;
	InvokeHelper(0x73, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Shape::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x73, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH Shape::GetNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x74, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

float Shape::GetRotation()
{
	float result;
	InvokeHelper(0x75, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void Shape::SetRotation(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x75, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH Shape::GetPictureFormat()
{
	LPDISPATCH result;
	InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetShadow()
{
	LPDISPATCH result;
	InvokeHelper(0x77, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetTextEffect()
{
	LPDISPATCH result;
	InvokeHelper(0x78, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetTextFrame()
{
	LPDISPATCH result;
	InvokeHelper(0x79, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetThreeD()
{
	LPDISPATCH result;
	InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

float Shape::GetTop()
{
	float result;
	InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void Shape::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long Shape::GetType()
{
	long result;
	InvokeHelper(0x7c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Shape::GetVerticalFlip()
{
	long result;
	InvokeHelper(0x7d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT Shape::GetVertices()
{
	VARIANT result;
	InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

long Shape::GetVisible()
{
	long result;
	InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Shape::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float Shape::GetWidth()
{
	float result;
	InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void Shape::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x80, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long Shape::GetZOrderPosition()
{
	long result;
	InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetOLEFormat()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetLinkFormat()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetPlaceholderFormat()
{
	LPDISPATCH result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetAnimationSettings()
{
	LPDISPATCH result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetActionSettings()
{
	LPDISPATCH result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Shape::Cut()
{
	InvokeHelper(0x7d9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Shape::Copy()
{
	InvokeHelper(0x7da, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Shape::Select(long Replace)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7db, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Replace);
}

LPDISPATCH Shape::Duplicate()
{
	LPDISPATCH result;
	InvokeHelper(0x7dc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Shape::GetMediaType()
{
	long result;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Shape::GetHasTextFrame()
{
	long result;
	InvokeHelper(0x7de, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetScript()
{
	LPDISPATCH result;
	InvokeHelper(0x82, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString Shape::GetAlternativeText()
{
	CString result;
	InvokeHelper(0x83, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Shape::SetAlternativeText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x83, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long Shape::GetHasTable()
{
	long result;
	InvokeHelper(0x7e0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetTable()
{
	LPDISPATCH result;
	InvokeHelper(0x7e1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ShapeRange properties

/////////////////////////////////////////////////////////////////////////////
// ShapeRange operations

LPDISPATCH ShapeRange::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ShapeRange::GetCreator()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void ShapeRange::Apply()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ShapeRange::Delete()
{
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ShapeRange::Flip(long FlipCmd)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FlipCmd);
}

void ShapeRange::IncrementLeft(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

void ShapeRange::IncrementRotation(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

void ShapeRange::IncrementTop(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

void ShapeRange::PickUp()
{
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ShapeRange::RerouteConnections()
{
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ShapeRange::ScaleHeight(float Factor, long RelativeToOriginalSize, long fScale)
{
	static BYTE parms[] =
		VTS_R4 VTS_I4 VTS_I4;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Factor, RelativeToOriginalSize, fScale);
}

void ShapeRange::ScaleWidth(float Factor, long RelativeToOriginalSize, long fScale)
{
	static BYTE parms[] =
		VTS_R4 VTS_I4 VTS_I4;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Factor, RelativeToOriginalSize, fScale);
}

void ShapeRange::SetShapesDefaultProperties()
{
	InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH ShapeRange::Ungroup()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void ShapeRange::ZOrder(long ZOrderCmd)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ZOrderCmd);
}

LPDISPATCH ShapeRange::GetAdjustments()
{
	LPDISPATCH result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ShapeRange::GetAutoShapeType()
{
	long result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetAutoShapeType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ShapeRange::GetBlackWhiteMode()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetBlackWhiteMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH ShapeRange::GetCallout()
{
	LPDISPATCH result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ShapeRange::GetConnectionSiteCount()
{
	long result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ShapeRange::GetConnector()
{
	long result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetConnectorFormat()
{
	LPDISPATCH result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetFill()
{
	LPDISPATCH result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetGroupItems()
{
	LPDISPATCH result;
	InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

float ShapeRange::GetHeight()
{
	float result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long ShapeRange::GetHorizontalFlip()
{
	long result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

float ShapeRange::GetLeft()
{
	float result;
	InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH ShapeRange::GetLine()
{
	LPDISPATCH result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ShapeRange::GetLockAspectRatio()
{
	long result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetLockAspectRatio(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x71, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString ShapeRange::GetName()
{
	CString result;
	InvokeHelper(0x73, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x73, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH ShapeRange::GetNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x74, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

float ShapeRange::GetRotation()
{
	float result;
	InvokeHelper(0x75, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetRotation(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x75, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH ShapeRange::GetPictureFormat()
{
	LPDISPATCH result;
	InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetShadow()
{
	LPDISPATCH result;
	InvokeHelper(0x77, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetTextEffect()
{
	LPDISPATCH result;
	InvokeHelper(0x78, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetTextFrame()
{
	LPDISPATCH result;
	InvokeHelper(0x79, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetThreeD()
{
	LPDISPATCH result;
	InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

float ShapeRange::GetTop()
{
	float result;
	InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long ShapeRange::GetType()
{
	long result;
	InvokeHelper(0x7c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ShapeRange::GetVerticalFlip()
{
	long result;
	InvokeHelper(0x7d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT ShapeRange::GetVertices()
{
	VARIANT result;
	InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

long ShapeRange::GetVisible()
{
	long result;
	InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float ShapeRange::GetWidth()
{
	float result;
	InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x80, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long ShapeRange::GetZOrderPosition()
{
	long result;
	InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetOLEFormat()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetLinkFormat()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetPlaceholderFormat()
{
	LPDISPATCH result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetAnimationSettings()
{
	LPDISPATCH result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetActionSettings()
{
	LPDISPATCH result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void ShapeRange::Cut()
{
	InvokeHelper(0x7d9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ShapeRange::Copy()
{
	InvokeHelper(0x7da, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ShapeRange::Select(long Replace)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7db, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Replace);
}

LPDISPATCH ShapeRange::Duplicate()
{
	LPDISPATCH result;
	InvokeHelper(0x7dc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ShapeRange::GetMediaType()
{
	long result;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ShapeRange::GetHasTextFrame()
{
	long result;
	InvokeHelper(0x7de, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

long ShapeRange::GetCount()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::Group()
{
	LPDISPATCH result;
	InvokeHelper(0x7e0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::Regroup()
{
	LPDISPATCH result;
	InvokeHelper(0x7e1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void ShapeRange::Align(long AlignCmd, long RelativeTo)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7e2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AlignCmd, RelativeTo);
}

void ShapeRange::Distribute(long DistributeCmd, long RelativeTo)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7e3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DistributeCmd, RelativeTo);
}

LPDISPATCH ShapeRange::GetScript()
{
	LPDISPATCH result;
	InvokeHelper(0x82, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString ShapeRange::GetAlternativeText()
{
	CString result;
	InvokeHelper(0x83, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetAlternativeText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x83, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long ShapeRange::GetHasTable()
{
	long result;
	InvokeHelper(0x7e5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetTable()
{
	LPDISPATCH result;
	InvokeHelper(0x7e6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// GroupShapes properties

/////////////////////////////////////////////////////////////////////////////
// GroupShapes operations

LPDISPATCH GroupShapes::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long GroupShapes::GetCreator()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH GroupShapes::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long GroupShapes::GetCount()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH GroupShapes::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

LPUNKNOWN GroupShapes::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Adjustments properties

/////////////////////////////////////////////////////////////////////////////
// Adjustments operations

LPDISPATCH Adjustments::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Adjustments::GetCreator()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Adjustments::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Adjustments::GetCount()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

float Adjustments::GetItem(long index)
{
	float result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		index);
	return result;
}

void Adjustments::SetItem(long index, float newValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_R4;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 index, newValue);
}


/////////////////////////////////////////////////////////////////////////////
// PictureFormat properties

/////////////////////////////////////////////////////////////////////////////
// PictureFormat operations

LPDISPATCH PictureFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PictureFormat::GetCreator()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH PictureFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void PictureFormat::IncrementBrightness(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

void PictureFormat::IncrementContrast(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

float PictureFormat::GetBrightness()
{
	float result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PictureFormat::SetBrightness(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long PictureFormat::GetColorType()
{
	long result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PictureFormat::SetColorType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PictureFormat::GetContrast()
{
	float result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PictureFormat::SetContrast(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PictureFormat::GetCropBottom()
{
	float result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PictureFormat::SetCropBottom(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PictureFormat::GetCropLeft()
{
	float result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PictureFormat::SetCropLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PictureFormat::GetCropRight()
{
	float result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PictureFormat::SetCropRight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PictureFormat::GetCropTop()
{
	float result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PictureFormat::SetCropTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long PictureFormat::GetTransparencyColor()
{
	long result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PictureFormat::SetTransparencyColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PictureFormat::GetTransparentBackground()
{
	long result;
	InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PictureFormat::SetTransparentBackground(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// FillFormat properties

/////////////////////////////////////////////////////////////////////////////
// FillFormat operations

LPDISPATCH FillFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long FillFormat::GetCreator()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH FillFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void FillFormat::Background()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void FillFormat::OneColorGradient(long Style, long Variant, float Degree)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_R4;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Style, Variant, Degree);
}

void FillFormat::Patterned(long Pattern)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Pattern);
}

void FillFormat::PresetGradient(long Style, long Variant, long PresetGradientType)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Style, Variant, PresetGradientType);
}

void FillFormat::PresetTextured(long PresetTexture)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 PresetTexture);
}

void FillFormat::Solid()
{
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void FillFormat::TwoColorGradient(long Style, long Variant)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Style, Variant);
}

void FillFormat::UserPicture(LPCTSTR PictureFile)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 PictureFile);
}

void FillFormat::UserTextured(LPCTSTR TextureFile)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 TextureFile);
}

LPDISPATCH FillFormat::GetBackColor()
{
	LPDISPATCH result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void FillFormat::SetBackColor(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH FillFormat::GetForeColor()
{
	LPDISPATCH result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void FillFormat::SetForeColor(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long FillFormat::GetGradientColorType()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

float FillFormat::GetGradientDegree()
{
	float result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

long FillFormat::GetGradientStyle()
{
	long result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long FillFormat::GetGradientVariant()
{
	long result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long FillFormat::GetPattern()
{
	long result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long FillFormat::GetPresetGradientType()
{
	long result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long FillFormat::GetPresetTexture()
{
	long result;
	InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString FillFormat::GetTextureName()
{
	CString result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long FillFormat::GetTextureType()
{
	long result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

float FillFormat::GetTransparency()
{
	float result;
	InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void FillFormat::SetTransparency(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long FillFormat::GetType()
{
	long result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long FillFormat::GetVisible()
{
	long result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void FillFormat::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x71, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// LineFormat properties

/////////////////////////////////////////////////////////////////////////////
// LineFormat operations

LPDISPATCH LineFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long LineFormat::GetCreator()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH LineFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH LineFormat::GetBackColor()
{
	LPDISPATCH result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void LineFormat::SetBackColor(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long LineFormat::GetBeginArrowheadLength()
{
	long result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetBeginArrowheadLength(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long LineFormat::GetBeginArrowheadStyle()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetBeginArrowheadStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long LineFormat::GetBeginArrowheadWidth()
{
	long result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetBeginArrowheadWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long LineFormat::GetDashStyle()
{
	long result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetDashStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long LineFormat::GetEndArrowheadLength()
{
	long result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetEndArrowheadLength(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long LineFormat::GetEndArrowheadStyle()
{
	long result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetEndArrowheadStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long LineFormat::GetEndArrowheadWidth()
{
	long result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetEndArrowheadWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH LineFormat::GetForeColor()
{
	LPDISPATCH result;
	InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void LineFormat::SetForeColor(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x6c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long LineFormat::GetPattern()
{
	long result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetPattern(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long LineFormat::GetStyle()
{
	long result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float LineFormat::GetTransparency()
{
	float result;
	InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetTransparency(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long LineFormat::GetVisible()
{
	long result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x70, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float LineFormat::GetWeight()
{
	float result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetWeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x71, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}


/////////////////////////////////////////////////////////////////////////////
// ShadowFormat properties

/////////////////////////////////////////////////////////////////////////////
// ShadowFormat operations

LPDISPATCH ShadowFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ShadowFormat::GetCreator()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShadowFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void ShadowFormat::IncrementOffsetX(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

void ShadowFormat::IncrementOffsetY(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

LPDISPATCH ShadowFormat::GetForeColor()
{
	LPDISPATCH result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void ShadowFormat::SetForeColor(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long ShadowFormat::GetObscured()
{
	long result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ShadowFormat::SetObscured(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float ShadowFormat::GetOffsetX()
{
	float result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ShadowFormat::SetOffsetX(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float ShadowFormat::GetOffsetY()
{
	float result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ShadowFormat::SetOffsetY(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float ShadowFormat::GetTransparency()
{
	float result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ShadowFormat::SetTransparency(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long ShadowFormat::GetType()
{
	long result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ShadowFormat::SetType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ShadowFormat::GetVisible()
{
	long result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ShadowFormat::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// ConnectorFormat properties

/////////////////////////////////////////////////////////////////////////////
// ConnectorFormat operations

LPDISPATCH ConnectorFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ConnectorFormat::GetCreator()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ConnectorFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void ConnectorFormat::BeginConnect(LPDISPATCH ConnectedShape, long ConnectionSite)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ConnectedShape, ConnectionSite);
}

void ConnectorFormat::BeginDisconnect()
{
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ConnectorFormat::EndConnect(LPDISPATCH ConnectedShape, long ConnectionSite)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ConnectedShape, ConnectionSite);
}

void ConnectorFormat::EndDisconnect()
{
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long ConnectorFormat::GetBeginConnected()
{
	long result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ConnectorFormat::GetBeginConnectedShape()
{
	LPDISPATCH result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ConnectorFormat::GetBeginConnectionSite()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ConnectorFormat::GetEndConnected()
{
	long result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ConnectorFormat::GetEndConnectedShape()
{
	LPDISPATCH result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ConnectorFormat::GetEndConnectionSite()
{
	long result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ConnectorFormat::GetType()
{
	long result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ConnectorFormat::SetType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// TextEffectFormat properties

/////////////////////////////////////////////////////////////////////////////
// TextEffectFormat operations

LPDISPATCH TextEffectFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long TextEffectFormat::GetCreator()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextEffectFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::ToggleVerticalText()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long TextEffectFormat::GetAlignment()
{
	long result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetAlignment(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long TextEffectFormat::GetFontBold()
{
	long result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetFontBold(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long TextEffectFormat::GetFontItalic()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetFontItalic(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString TextEffectFormat::GetFontName()
{
	CString result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetFontName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

float TextEffectFormat::GetFontSize()
{
	float result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetFontSize(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long TextEffectFormat::GetKernedPairs()
{
	long result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetKernedPairs(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long TextEffectFormat::GetNormalizedHeight()
{
	long result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetNormalizedHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long TextEffectFormat::GetPresetShape()
{
	long result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetPresetShape(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long TextEffectFormat::GetPresetTextEffect()
{
	long result;
	InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetPresetTextEffect(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long TextEffectFormat::GetRotatedChars()
{
	long result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetRotatedChars(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString TextEffectFormat::GetText()
{
	CString result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

float TextEffectFormat::GetTracking()
{
	float result;
	InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetTracking(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}


/////////////////////////////////////////////////////////////////////////////
// ThreeDFormat properties

/////////////////////////////////////////////////////////////////////////////
// ThreeDFormat operations

LPDISPATCH ThreeDFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ThreeDFormat::GetCreator()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ThreeDFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void ThreeDFormat::IncrementRotationX(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

void ThreeDFormat::IncrementRotationY(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

void ThreeDFormat::ResetRotation()
{
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ThreeDFormat::SetThreeDFormat(long PresetThreeDFormat)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 PresetThreeDFormat);
}

void ThreeDFormat::SetExtrusionDirection(long PresetExtrusionDirection)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 PresetExtrusionDirection);
}

float ThreeDFormat::GetDepth()
{
	float result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ThreeDFormat::SetDepth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH ThreeDFormat::GetExtrusionColor()
{
	LPDISPATCH result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ThreeDFormat::GetExtrusionColorType()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ThreeDFormat::SetExtrusionColorType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ThreeDFormat::GetPerspective()
{
	long result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ThreeDFormat::SetPerspective(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ThreeDFormat::GetPresetExtrusionDirection()
{
	long result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ThreeDFormat::GetPresetLightingDirection()
{
	long result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ThreeDFormat::SetPresetLightingDirection(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ThreeDFormat::GetPresetLightingSoftness()
{
	long result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ThreeDFormat::SetPresetLightingSoftness(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ThreeDFormat::GetPresetMaterial()
{
	long result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ThreeDFormat::SetPresetMaterial(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ThreeDFormat::GetPresetThreeDFormat()
{
	long result;
	InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

float ThreeDFormat::GetRotationX()
{
	float result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ThreeDFormat::SetRotationX(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float ThreeDFormat::GetRotationY()
{
	float result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ThreeDFormat::SetRotationY(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long ThreeDFormat::GetVisible()
{
	long result;
	InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ThreeDFormat::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// TextFrame properties

/////////////////////////////////////////////////////////////////////////////
// TextFrame operations

LPDISPATCH TextFrame::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long TextFrame::GetCreator()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextFrame::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

float TextFrame::GetMarginBottom()
{
	float result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void TextFrame::SetMarginBottom(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float TextFrame::GetMarginLeft()
{
	float result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void TextFrame::SetMarginLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float TextFrame::GetMarginRight()
{
	float result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void TextFrame::SetMarginRight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float TextFrame::GetMarginTop()
{
	float result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void TextFrame::SetMarginTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long TextFrame::GetOrientation()
{
	long result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextFrame::SetOrientation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long TextFrame::GetHasText()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextFrame::GetTextRange()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextFrame::GetRuler()
{
	LPDISPATCH result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long TextFrame::GetHorizontalAnchor()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextFrame::SetHorizontalAnchor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long TextFrame::GetVerticalAnchor()
{
	long result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextFrame::SetVerticalAnchor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long TextFrame::GetAutoSize()
{
	long result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextFrame::SetAutoSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long TextFrame::GetWordWrap()
{
	long result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextFrame::SetWordWrap(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void TextFrame::DeleteText()
{
	InvokeHelper(0x7da, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CalloutFormat properties

/////////////////////////////////////////////////////////////////////////////
// CalloutFormat operations

LPDISPATCH CalloutFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long CalloutFormat::GetCreator()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH CalloutFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void CalloutFormat::AutomaticLength()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CalloutFormat::CustomDrop(float Drop)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Drop);
}

void CalloutFormat::CustomLength(float Length)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Length);
}

void CalloutFormat::PresetDrop(long DropType)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DropType);
}

long CalloutFormat::GetAccent()
{
	long result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CalloutFormat::SetAccent(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CalloutFormat::GetAngle()
{
	long result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CalloutFormat::SetAngle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CalloutFormat::GetAutoAttach()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CalloutFormat::SetAutoAttach(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CalloutFormat::GetAutoLength()
{
	long result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CalloutFormat::GetBorder()
{
	long result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CalloutFormat::SetBorder(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float CalloutFormat::GetDrop()
{
	float result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

long CalloutFormat::GetDropType()
{
	long result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

float CalloutFormat::GetGap()
{
	float result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CalloutFormat::SetGap(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float CalloutFormat::GetLength()
{
	float result;
	InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

long CalloutFormat::GetType()
{
	long result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CalloutFormat::SetType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// ShapeNodes properties

/////////////////////////////////////////////////////////////////////////////
// ShapeNodes operations

LPDISPATCH ShapeNodes::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ShapeNodes::GetCreator()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeNodes::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ShapeNodes::GetCount()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeNodes::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

LPUNKNOWN ShapeNodes::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

void ShapeNodes::Delete(long index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 index);
}

void ShapeNodes::Insert(long index, long SegmentType, long EditingType, float X1, float Y1, float X2, float Y2, float X3, float Y3)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 index, SegmentType, EditingType, X1, Y1, X2, Y2, X3, Y3);
}

void ShapeNodes::SetEditingType(long index, long EditingType)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 index, EditingType);
}

void ShapeNodes::SetPosition(long index, float X1, float Y1)
{
	static BYTE parms[] =
		VTS_I4 VTS_R4 VTS_R4;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 index, X1, Y1);
}

void ShapeNodes::SetSegmentType(long index, long SegmentType)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 index, SegmentType);
}


/////////////////////////////////////////////////////////////////////////////
// ShapeNode properties

/////////////////////////////////////////////////////////////////////////////
// ShapeNode operations

LPDISPATCH ShapeNode::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ShapeNode::GetCreator()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeNode::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ShapeNode::GetEditingType()
{
	long result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT ShapeNode::GetPoints()
{
	VARIANT result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

long ShapeNode::GetSegmentType()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// OLEFormat properties

/////////////////////////////////////////////////////////////////////////////
// OLEFormat operations

LPDISPATCH OLEFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH OLEFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH OLEFormat::GetObjectVerbs()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH OLEFormat::GetObject()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString OLEFormat::GetProgID()
{
	CString result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long OLEFormat::GetFollowColors()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void OLEFormat::SetFollowColors(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void OLEFormat::DoVerb(long index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 index);
}

void OLEFormat::Activate()
{
	InvokeHelper(0x7d8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// LinkFormat properties

/////////////////////////////////////////////////////////////////////////////
// LinkFormat operations

LPDISPATCH LinkFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH LinkFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString LinkFormat::GetSourceFullName()
{
	CString result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void LinkFormat::SetSourceFullName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long LinkFormat::GetAutoUpdate()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LinkFormat::SetAutoUpdate(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void LinkFormat::Update()
{
	InvokeHelper(0x7d5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// ObjectVerbs properties

/////////////////////////////////////////////////////////////////////////////
// ObjectVerbs operations

long ObjectVerbs::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ObjectVerbs::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ObjectVerbs::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString ObjectVerbs::Item(long index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// AnimationSettings properties

/////////////////////////////////////////////////////////////////////////////
// AnimationSettings operations

LPDISPATCH AnimationSettings::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH AnimationSettings::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH AnimationSettings::GetDimColor()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH AnimationSettings::GetSoundEffect()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long AnimationSettings::GetEntryEffect()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void AnimationSettings::SetEntryEffect(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long AnimationSettings::GetAfterEffect()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void AnimationSettings::SetAfterEffect(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long AnimationSettings::GetAnimationOrder()
{
	long result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void AnimationSettings::SetAnimationOrder(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long AnimationSettings::GetAdvanceMode()
{
	long result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void AnimationSettings::SetAdvanceMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float AnimationSettings::GetAdvanceTime()
{
	float result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void AnimationSettings::SetAdvanceTime(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH AnimationSettings::GetPlaySettings()
{
	LPDISPATCH result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long AnimationSettings::GetTextLevelEffect()
{
	long result;
	InvokeHelper(0x7db, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void AnimationSettings::SetTextLevelEffect(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7db, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long AnimationSettings::GetTextUnitEffect()
{
	long result;
	InvokeHelper(0x7dc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void AnimationSettings::SetTextUnitEffect(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7dc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long AnimationSettings::GetAnimate()
{
	long result;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void AnimationSettings::SetAnimate(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long AnimationSettings::GetAnimateBackground()
{
	long result;
	InvokeHelper(0x7de, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void AnimationSettings::SetAnimateBackground(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7de, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long AnimationSettings::GetAnimateTextInReverse()
{
	long result;
	InvokeHelper(0x7df, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void AnimationSettings::SetAnimateTextInReverse(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7df, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long AnimationSettings::GetChartUnitEffect()
{
	long result;
	InvokeHelper(0x7e0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void AnimationSettings::SetChartUnitEffect(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7e0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// ActionSettings properties

/////////////////////////////////////////////////////////////////////////////
// ActionSettings operations

long ActionSettings::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ActionSettings::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ActionSettings::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ActionSettings::Item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ActionSetting properties

/////////////////////////////////////////////////////////////////////////////
// ActionSetting operations

LPDISPATCH ActionSetting::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ActionSetting::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ActionSetting::GetAction()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ActionSetting::SetAction(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString ActionSetting::GetActionVerb()
{
	CString result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void ActionSetting::SetActionVerb(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long ActionSetting::GetAnimateAction()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ActionSetting::SetAnimateAction(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString ActionSetting::GetRun()
{
	CString result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void ActionSetting::SetRun(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString ActionSetting::GetSlideShowName()
{
	CString result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void ActionSetting::SetSlideShowName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH ActionSetting::GetHyperlink()
{
	LPDISPATCH result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ActionSetting::GetSoundEffect()
{
	LPDISPATCH result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ActionSetting::GetShowandReturn()
{
	long result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ActionSetting::SetShowandReturn(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7da, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PlaySettings properties

/////////////////////////////////////////////////////////////////////////////
// PlaySettings operations

LPDISPATCH PlaySettings::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PlaySettings::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PlaySettings::GetActionVerb()
{
	CString result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PlaySettings::SetActionVerb(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PlaySettings::GetHideWhileNotPlaying()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PlaySettings::SetHideWhileNotPlaying(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PlaySettings::GetLoopUntilStopped()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PlaySettings::SetLoopUntilStopped(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PlaySettings::GetPlayOnEntry()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PlaySettings::SetPlayOnEntry(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PlaySettings::GetRewindMovie()
{
	long result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PlaySettings::SetRewindMovie(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PlaySettings::GetPauseAnimation()
{
	long result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PlaySettings::SetPauseAnimation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PlaySettings::GetStopAfterSlides()
{
	long result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PlaySettings::SetStopAfterSlides(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// TextRange properties

/////////////////////////////////////////////////////////////////////////////
// TextRange operations

long TextRange::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextRange::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextRange::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextRange::GetActionSettings()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long TextRange::GetStart()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long TextRange::GetLength()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

float TextRange::GetBoundLeft()
{
	float result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

float TextRange::GetBoundTop()
{
	float result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

float TextRange::GetBoundWidth()
{
	float result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

float TextRange::GetBoundHeight()
{
	float result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextRange::Paragraphs(long Start, long Length)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7da, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Start, Length);
	return result;
}

LPDISPATCH TextRange::Sentences(long Start, long Length)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7db, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Start, Length);
	return result;
}

LPDISPATCH TextRange::Words(long Start, long Length)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7dc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Start, Length);
	return result;
}

LPDISPATCH TextRange::Characters(long Start, long Length)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7dd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Start, Length);
	return result;
}

LPDISPATCH TextRange::Lines(long Start, long Length)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7de, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Start, Length);
	return result;
}

LPDISPATCH TextRange::Runs(long Start, long Length)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7df, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Start, Length);
	return result;
}

LPDISPATCH TextRange::TrimText()
{
	LPDISPATCH result;
	InvokeHelper(0x7e0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString TextRange::GetText()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void TextRange::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH TextRange::InsertAfter(LPCTSTR NewText)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7e1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		NewText);
	return result;
}

LPDISPATCH TextRange::InsertBefore(LPCTSTR NewText)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7e2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		NewText);
	return result;
}

LPDISPATCH TextRange::InsertDateTime(long DateTimeFormat, long InsertAsField)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7e3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		DateTimeFormat, InsertAsField);
	return result;
}

LPDISPATCH TextRange::InsertSlideNumber()
{
	LPDISPATCH result;
	InvokeHelper(0x7e4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextRange::InsertSymbol(LPCTSTR FontName, long CharNumber, long Unicode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4;
	InvokeHelper(0x7e5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		FontName, CharNumber, Unicode);
	return result;
}

LPDISPATCH TextRange::GetFont()
{
	LPDISPATCH result;
	InvokeHelper(0x7e6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextRange::GetParagraphFormat()
{
	LPDISPATCH result;
	InvokeHelper(0x7e7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long TextRange::GetIndentLevel()
{
	long result;
	InvokeHelper(0x7e8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextRange::SetIndentLevel(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7e8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void TextRange::Select()
{
	InvokeHelper(0x7e9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void TextRange::Cut()
{
	InvokeHelper(0x7ea, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void TextRange::Copy()
{
	InvokeHelper(0x7eb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void TextRange::Delete()
{
	InvokeHelper(0x7ec, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH TextRange::Paste()
{
	LPDISPATCH result;
	InvokeHelper(0x7ed, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void TextRange::ChangeCase(long Type)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7ee, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Type);
}

void TextRange::AddPeriods()
{
	InvokeHelper(0x7ef, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void TextRange::RemovePeriods()
{
	InvokeHelper(0x7f0, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH TextRange::Find(LPCTSTR FindWhat, long After, long MatchCase, long WholeWords)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x7f1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		FindWhat, After, MatchCase, WholeWords);
	return result;
}

LPDISPATCH TextRange::Replace(LPCTSTR FindWhat, LPCTSTR ReplaceWhat, long After, long MatchCase, long WholeWords)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x7f2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		FindWhat, ReplaceWhat, After, MatchCase, WholeWords);
	return result;
}

void TextRange::RotatedBounds(float* X1, float* Y1, float* X2, float* Y2, float* X3, float* Y3, float* x4, float* y4)
{
	static BYTE parms[] =
		VTS_PR4 VTS_PR4 VTS_PR4 VTS_PR4 VTS_PR4 VTS_PR4 VTS_PR4 VTS_PR4;
	InvokeHelper(0x7f3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 X1, Y1, X2, Y2, X3, Y3, x4, y4);
}

long TextRange::GetLanguageID()
{
	long result;
	InvokeHelper(0x7f4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextRange::SetLanguageID(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7f4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void TextRange::RtlRun()
{
	InvokeHelper(0x7f5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void TextRange::LtrRun()
{
	InvokeHelper(0x7f6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Ruler properties

/////////////////////////////////////////////////////////////////////////////
// Ruler operations

LPDISPATCH Ruler::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Ruler::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Ruler::GetTabStops()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Ruler::GetLevels()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// RulerLevels properties

/////////////////////////////////////////////////////////////////////////////
// RulerLevels operations

long RulerLevels::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH RulerLevels::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH RulerLevels::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH RulerLevels::Item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// RulerLevel properties

/////////////////////////////////////////////////////////////////////////////
// RulerLevel operations

LPDISPATCH RulerLevel::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH RulerLevel::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

float RulerLevel::GetFirstMargin()
{
	float result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void RulerLevel::SetFirstMargin(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float RulerLevel::GetLeftMargin()
{
	float result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void RulerLevel::SetLeftMargin(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}


/////////////////////////////////////////////////////////////////////////////
// TabStops properties

/////////////////////////////////////////////////////////////////////////////
// TabStops operations

long TabStops::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH TabStops::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH TabStops::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH TabStops::Item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

float TabStops::GetDefaultSpacing()
{
	float result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void TabStops::SetDefaultSpacing(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH TabStops::Add(long Type, float Position)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_R4;
	InvokeHelper(0x7d4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Type, Position);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// TabStop properties

/////////////////////////////////////////////////////////////////////////////
// TabStop operations

LPDISPATCH TabStop::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH TabStop::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long TabStop::GetType()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TabStop::SetType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float TabStop::GetPosition()
{
	float result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void TabStop::SetPosition(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void TabStop::Clear()
{
	InvokeHelper(0x7d5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Font properties

/////////////////////////////////////////////////////////////////////////////
// Font operations

LPDISPATCH Font::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Font::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Font::GetColor()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Font::GetBold()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Font::SetBold(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Font::GetItalic()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Font::SetItalic(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Font::GetShadow()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Font::SetShadow(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Font::GetEmboss()
{
	long result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Font::SetEmboss(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Font::GetUnderline()
{
	long result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Font::SetUnderline(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Font::GetSubscript()
{
	long result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Font::SetSubscript(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Font::GetSuperscript()
{
	long result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Font::SetSuperscript(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7da, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float Font::GetBaselineOffset()
{
	float result;
	InvokeHelper(0x7db, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void Font::SetBaselineOffset(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7db, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long Font::GetEmbedded()
{
	long result;
	InvokeHelper(0x7dc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Font::GetEmbeddable()
{
	long result;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

float Font::GetSize()
{
	float result;
	InvokeHelper(0x7de, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void Font::SetSize(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7de, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString Font::GetName()
{
	CString result;
	InvokeHelper(0x7df, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Font::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7df, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString Font::GetNameFarEast()
{
	CString result;
	InvokeHelper(0x7e0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Font::SetNameFarEast(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7e0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString Font::GetNameAscii()
{
	CString result;
	InvokeHelper(0x7e1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Font::SetNameAscii(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7e1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long Font::GetAutoRotateNumbers()
{
	long result;
	InvokeHelper(0x7e2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Font::SetAutoRotateNumbers(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7e2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString Font::GetNameOther()
{
	CString result;
	InvokeHelper(0x7e3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Font::SetNameOther(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7e3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString Font::GetNameComplexScript()
{
	CString result;
	InvokeHelper(0x7e4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Font::SetNameComplexScript(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7e4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// ParagraphFormat properties

/////////////////////////////////////////////////////////////////////////////
// ParagraphFormat operations

LPDISPATCH ParagraphFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ParagraphFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ParagraphFormat::GetAlignment()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ParagraphFormat::SetAlignment(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH ParagraphFormat::GetBullet()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ParagraphFormat::GetLineRuleBefore()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ParagraphFormat::SetLineRuleBefore(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ParagraphFormat::GetLineRuleAfter()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ParagraphFormat::SetLineRuleAfter(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ParagraphFormat::GetLineRuleWithin()
{
	long result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ParagraphFormat::SetLineRuleWithin(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float ParagraphFormat::GetSpaceBefore()
{
	float result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ParagraphFormat::SetSpaceBefore(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float ParagraphFormat::GetSpaceAfter()
{
	float result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ParagraphFormat::SetSpaceAfter(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float ParagraphFormat::GetSpaceWithin()
{
	float result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ParagraphFormat::SetSpaceWithin(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7da, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long ParagraphFormat::GetBaseLineAlignment()
{
	long result;
	InvokeHelper(0x7db, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ParagraphFormat::SetBaseLineAlignment(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7db, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ParagraphFormat::GetFarEastLineBreakControl()
{
	long result;
	InvokeHelper(0x7dc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ParagraphFormat::SetFarEastLineBreakControl(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7dc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ParagraphFormat::GetWordWrap()
{
	long result;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ParagraphFormat::SetWordWrap(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ParagraphFormat::GetHangingPunctuation()
{
	long result;
	InvokeHelper(0x7de, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ParagraphFormat::SetHangingPunctuation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7de, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ParagraphFormat::GetTextDirection()
{
	long result;
	InvokeHelper(0x7df, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ParagraphFormat::SetTextDirection(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7df, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// BulletFormat properties

/////////////////////////////////////////////////////////////////////////////
// BulletFormat operations

LPDISPATCH BulletFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH BulletFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long BulletFormat::GetCharacter()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void BulletFormat::SetCharacter(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float BulletFormat::GetRelativeSize()
{
	float result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void BulletFormat::SetRelativeSize(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long BulletFormat::GetUseTextColor()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void BulletFormat::SetUseTextColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long BulletFormat::GetUseTextFont()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void BulletFormat::SetUseTextFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH BulletFormat::GetFont()
{
	LPDISPATCH result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long BulletFormat::GetType()
{
	long result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void BulletFormat::SetType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long BulletFormat::GetStyle()
{
	long result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void BulletFormat::SetStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long BulletFormat::GetStartValue()
{
	long result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void BulletFormat::SetStartValue(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7da, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void BulletFormat::Picture(LPCTSTR Picture)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7db, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Picture);
}

long BulletFormat::GetNumber()
{
	long result;
	InvokeHelper(0x7dc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// TextStyles properties

/////////////////////////////////////////////////////////////////////////////
// TextStyles operations

long TextStyles::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextStyles::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextStyles::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextStyles::Item(long Type)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Type);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// TextStyle properties

/////////////////////////////////////////////////////////////////////////////
// TextStyle operations

LPDISPATCH TextStyle::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextStyle::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextStyle::GetRuler()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextStyle::GetTextFrame()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextStyle::GetLevels()
{
	LPDISPATCH result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// TextStyleLevels properties

/////////////////////////////////////////////////////////////////////////////
// TextStyleLevels operations

long TextStyleLevels::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextStyleLevels::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextStyleLevels::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextStyleLevels::Item(long Level)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Level);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// TextStyleLevel properties

/////////////////////////////////////////////////////////////////////////////
// TextStyleLevel operations

LPDISPATCH TextStyleLevel::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextStyleLevel::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextStyleLevel::GetParagraphFormat()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextStyleLevel::GetFont()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// HeaderFooter properties

/////////////////////////////////////////////////////////////////////////////
// HeaderFooter operations

LPDISPATCH HeaderFooter::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH HeaderFooter::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long HeaderFooter::GetVisible()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void HeaderFooter::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString HeaderFooter::GetText()
{
	CString result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void HeaderFooter::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long HeaderFooter::GetUseFormat()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void HeaderFooter::SetUseFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long HeaderFooter::GetFormat()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void HeaderFooter::SetFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// _Presentation properties

/////////////////////////////////////////////////////////////////////////////
// _Presentation operations

LPDISPATCH _Presentation::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::GetSlideMaster()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::GetTitleMaster()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Presentation::GetHasTitleMaster()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::AddTitleMaster()
{
	LPDISPATCH result;
	InvokeHelper(0x7d6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Presentation::ApplyTemplate(LPCTSTR FileName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName);
}

CString _Presentation::GetTemplateName()
{
	CString result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::GetNotesMaster()
{
	LPDISPATCH result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::GetHandoutMaster()
{
	LPDISPATCH result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::GetSlides()
{
	LPDISPATCH result;
	InvokeHelper(0x7db, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::GetPageSetup()
{
	LPDISPATCH result;
	InvokeHelper(0x7dc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::GetColorSchemes()
{
	LPDISPATCH result;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::GetExtraColors()
{
	LPDISPATCH result;
	InvokeHelper(0x7de, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::GetSlideShowSettings()
{
	LPDISPATCH result;
	InvokeHelper(0x7df, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::GetFonts()
{
	LPDISPATCH result;
	InvokeHelper(0x7e0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::GetWindows()
{
	LPDISPATCH result;
	InvokeHelper(0x7e1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x7e2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::GetDefaultShape()
{
	LPDISPATCH result;
	InvokeHelper(0x7e3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::GetBuiltInDocumentProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x7e4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::GetCustomDocumentProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x7e5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::GetVBProject()
{
	LPDISPATCH result;
	InvokeHelper(0x7e6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Presentation::GetReadOnly()
{
	long result;
	InvokeHelper(0x7e7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _Presentation::GetFullName()
{
	CString result;
	InvokeHelper(0x7e8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Presentation::GetName()
{
	CString result;
	InvokeHelper(0x7e9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Presentation::GetPath()
{
	CString result;
	InvokeHelper(0x7ea, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long _Presentation::GetSaved()
{
	long result;
	InvokeHelper(0x7eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Presentation::SetSaved(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Presentation::GetLayoutDirection()
{
	long result;
	InvokeHelper(0x7ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Presentation::SetLayoutDirection(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH _Presentation::NewWindow()
{
	LPDISPATCH result;
	InvokeHelper(0x7ed, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Presentation::FollowHyperlink(LPCTSTR Address, LPCTSTR SubAddress, BOOL NewWindow, BOOL AddHistory, LPCTSTR ExtraInfo, long Method, LPCTSTR HeaderInfo)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BOOL VTS_BOOL VTS_BSTR VTS_I4 VTS_BSTR;
	InvokeHelper(0x7ee, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Address, SubAddress, NewWindow, AddHistory, ExtraInfo, Method, HeaderInfo);
}

void _Presentation::AddToFavorites()
{
	InvokeHelper(0x7ef, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _Presentation::GetPrintOptions()
{
	LPDISPATCH result;
	InvokeHelper(0x7f1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Presentation::PrintOut(long From, long To, LPCTSTR PrintToFile, long Copies, long Collate)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR VTS_I4 VTS_I4;
	InvokeHelper(0x7f2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 From, To, PrintToFile, Copies, Collate);
}

void _Presentation::Save()
{
	InvokeHelper(0x7f3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Presentation::SaveAs(LPCTSTR FileName, long FileFormat, long EmbedTrueTypeFonts)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4;
	InvokeHelper(0x7f4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName, FileFormat, EmbedTrueTypeFonts);
}

void _Presentation::SaveCopyAs(LPCTSTR FileName, long FileFormat, long EmbedTrueTypeFonts)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4;
	InvokeHelper(0x7f5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName, FileFormat, EmbedTrueTypeFonts);
}

void _Presentation::Export(LPCTSTR Path, LPCTSTR FilterName, long ScaleWidth, long ScaleHeight)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_I4 VTS_I4;
	InvokeHelper(0x7f6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Path, FilterName, ScaleWidth, ScaleHeight);
}

void _Presentation::Close()
{
	InvokeHelper(0x7f7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _Presentation::GetContainer()
{
	LPDISPATCH result;
	InvokeHelper(0x7f9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Presentation::GetDisplayComments()
{
	long result;
	InvokeHelper(0x7fa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Presentation::SetDisplayComments(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7fa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Presentation::GetFarEastLineBreakLevel()
{
	long result;
	InvokeHelper(0x7fb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Presentation::SetFarEastLineBreakLevel(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7fb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _Presentation::GetNoLineBreakBefore()
{
	CString result;
	InvokeHelper(0x7fc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Presentation::SetNoLineBreakBefore(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7fc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _Presentation::GetNoLineBreakAfter()
{
	CString result;
	InvokeHelper(0x7fd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Presentation::SetNoLineBreakAfter(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7fd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void _Presentation::UpdateLinks()
{
	InvokeHelper(0x7fe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _Presentation::GetSlideShowWindow()
{
	LPDISPATCH result;
	InvokeHelper(0x7ff, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Presentation::GetFarEastLineBreakLanguage()
{
	long result;
	InvokeHelper(0x800, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Presentation::SetFarEastLineBreakLanguage(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x800, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void _Presentation::WebPagePreview()
{
	InvokeHelper(0x801, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long _Presentation::GetDefaultLanguageID()
{
	long result;
	InvokeHelper(0x802, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Presentation::SetDefaultLanguageID(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x802, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH _Presentation::GetCommandBars()
{
	LPDISPATCH result;
	InvokeHelper(0x803, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::GetPublishObjects()
{
	LPDISPATCH result;
	InvokeHelper(0x804, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::GetWebOptions()
{
	LPDISPATCH result;
	InvokeHelper(0x805, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Presentation::GetHTMLProject()
{
	LPDISPATCH result;
	InvokeHelper(0x806, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Presentation::ReloadAs(long cp)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x807, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 cp);
}

long _Presentation::GetEnvelopeVisible()
{
	long result;
	InvokeHelper(0x809, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Presentation::SetEnvelopeVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x809, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Presentation::GetVBASigned()
{
	long result;
	InvokeHelper(0x80b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// PPDialogs properties

/////////////////////////////////////////////////////////////////////////////
// PPDialogs operations

long PPDialogs::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPDialogs::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPDialogs::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

LPDISPATCH PPDialogs::AddDialog(float Left, float Top, float Width, float Height, long Modal, LPUNKNOWN ParentWindow, long Position, long DisplayHelp)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_I4 VTS_UNKNOWN VTS_I4 VTS_I4;
	InvokeHelper(0x7d2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height, Modal, ParentWindow, Position, DisplayHelp);
	return result;
}

LPDISPATCH PPDialogs::AddTabDialog(float Left, float Top, float Width, float Height, long Modal, LPUNKNOWN ParentWindow, long Position, long DisplayHelp)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_I4 VTS_UNKNOWN VTS_I4 VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height, Modal, ParentWindow, Position, DisplayHelp);
	return result;
}

LPDISPATCH PPDialogs::LoadDialog(LPCTSTR resourceDLL, long nResID, long bModal, LPUNKNOWN ParentWindow, long Position)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_UNKNOWN VTS_I4;
	InvokeHelper(0x7d4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		resourceDLL, nResID, bModal, ParentWindow, Position);
	return result;
}

LPDISPATCH PPDialogs::AddAlert()
{
	LPDISPATCH result;
	InvokeHelper(0x7d5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPDialogs::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPDialogs::GetName()
{
	CString result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDialogs::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPDialogs::RunCharacterAlert(LPCTSTR Text, long Type, long icon, LPUNKNOWN ParentWindow)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_UNKNOWN;
	InvokeHelper(0x7d8, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		Text, Type, icon, ParentWindow);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// PPAlert properties

/////////////////////////////////////////////////////////////////////////////
// PPAlert operations

LPDISPATCH PPAlert::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPAlert::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void PPAlert::Run(LPCTSTR Title, long Type, LPCTSTR Text, LPCTSTR leftBtn, LPCTSTR middleBtn, LPCTSTR rightBtn)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Title, Type, Text, leftBtn, middleBtn, rightBtn);
}

long PPAlert::GetPressedButton()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString PPAlert::GetOnButton()
{
	CString result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPAlert::SetOnButton(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPDialog properties

/////////////////////////////////////////////////////////////////////////////
// PPDialog operations

LPDISPATCH PPDialog::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPDialog::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPDialog::GetStyle()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long PPDialog::GetMode()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPDialog::SetMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPDialog::GetHelpId()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPDialog::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPDialog::GetHideOnIdle()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPDialog::SetHideOnIdle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPDialog::GetResourceDLL()
{
	CString result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDialog::SetResourceDLL(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPDialog::GetCaption()
{
	CString result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDialog::SetCaption(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

float PPDialog::GetLeft()
{
	float result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPDialog::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPDialog::GetTop()
{
	float result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPDialog::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7da, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPDialog::GetWidth()
{
	float result;
	InvokeHelper(0x7db, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPDialog::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7db, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPDialog::GetHeight()
{
	float result;
	InvokeHelper(0x7dc, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPDialog::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7dc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPDialog::GetClientLeft()
{
	float result;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

float PPDialog::GetClientTop()
{
	float result;
	InvokeHelper(0x7de, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

float PPDialog::GetClientWidth()
{
	float result;
	InvokeHelper(0x7df, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

float PPDialog::GetClientHeight()
{
	float result;
	InvokeHelper(0x7e0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

long PPDialog::GetVisible()
{
	long result;
	InvokeHelper(0x7e1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPDialog::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7e1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH PPDialog::GetControls()
{
	LPDISPATCH result;
	InvokeHelper(0x7e2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPDialog::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x7e3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPDialog::GetName()
{
	CString result;
	InvokeHelper(0x7e4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDialog::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7e4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPDialog::GetSheets()
{
	LPDISPATCH result;
	InvokeHelper(0x7e5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPDialog::GetTabControl()
{
	LPDISPATCH result;
	InvokeHelper(0x7e6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPDialog::GetDelayTime()
{
	long result;
	InvokeHelper(0x7e7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPDialog::SetDelayTime(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7e7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPDialog::SaveDialog(LPCTSTR FileName)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7e8, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		FileName);
	return result;
}

void PPDialog::Terminate()
{
	InvokeHelper(0x7e9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString PPDialog::GetOnTerminate()
{
	CString result;
	InvokeHelper(0x7eb, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDialog::SetOnTerminate(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPDialog::GetOnIdle()
{
	CString result;
	InvokeHelper(0x7ec, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDialog::SetOnIdle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPDialog::GetOnMouseDown()
{
	CString result;
	InvokeHelper(0x7ed, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDialog::SetOnMouseDown(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPDialog::GetOnMouseUp()
{
	CString result;
	InvokeHelper(0x7ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDialog::SetOnMouseUp(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPDialog::GetOnKeyPressed()
{
	CString result;
	InvokeHelper(0x7ef, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDialog::SetOnKeyPressed(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPDialog::GetOnTimer()
{
	CString result;
	InvokeHelper(0x7f0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDialog::SetOnTimer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPDialog::GetOnActivate()
{
	CString result;
	InvokeHelper(0x7f1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDialog::SetOnActivate(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPTabSheet properties

/////////////////////////////////////////////////////////////////////////////
// PPTabSheet operations

LPDISPATCH PPTabSheet::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPTabSheet::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPTabSheet::GetName()
{
	CString result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPTabSheet::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void PPTabSheet::Select()
{
	InvokeHelper(0x7d4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

float PPTabSheet::GetClientLeft()
{
	float result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

float PPTabSheet::GetClientTop()
{
	float result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

float PPTabSheet::GetClientWidth()
{
	float result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

float PPTabSheet::GetClientHeight()
{
	float result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPTabSheet::GetControls()
{
	LPDISPATCH result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPTabSheet::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPTabSheet::GetOnActivate()
{
	CString result;
	InvokeHelper(0x7db, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPTabSheet::SetOnActivate(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7db, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPControls properties

/////////////////////////////////////////////////////////////////////////////
// PPControls operations

long PPControls::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPControls::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPControls::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

LPDISPATCH PPControls::AddPushButton(float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7d2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height);
	return result;
}

LPDISPATCH PPControls::AddToggleButton(float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height);
	return result;
}

LPDISPATCH PPControls::AddBitmapButton(float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7d4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height);
	return result;
}

LPDISPATCH PPControls::AddListBox(float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7d5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height);
	return result;
}

LPDISPATCH PPControls::AddCheckBox(float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7d6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height);
	return result;
}

LPDISPATCH PPControls::AddRadioCluster(float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7d7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height);
	return result;
}

LPDISPATCH PPControls::AddStaticText(float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7d8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height);
	return result;
}

LPDISPATCH PPControls::AddEditText(float Left, float Top, float Width, float Height, const VARIANT& VerticalScrollBar)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_VARIANT;
	InvokeHelper(0x7d9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height, &VerticalScrollBar);
	return result;
}

LPDISPATCH PPControls::AddIcon(float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7da, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height);
	return result;
}

LPDISPATCH PPControls::AddBitmap(float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7db, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height);
	return result;
}

LPDISPATCH PPControls::AddSpinner(float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7dc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height);
	return result;
}

LPDISPATCH PPControls::AddScrollBar(long Style, float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7dd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Style, Left, Top, Width, Height);
	return result;
}

LPDISPATCH PPControls::AddGroupBox(float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7de, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height);
	return result;
}

LPDISPATCH PPControls::AddDropDown(float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7df, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height);
	return result;
}

LPDISPATCH PPControls::AddDropDownEdit(float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7e0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height);
	return result;
}

LPDISPATCH PPControls::AddMiniature(float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7e1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height);
	return result;
}

LPDISPATCH PPControls::AddFrame(float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7e2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height);
	return result;
}

long PPControls::GetVisible()
{
	long result;
	InvokeHelper(0x7e3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPControls::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7e3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPTabSheets properties

/////////////////////////////////////////////////////////////////////////////
// PPTabSheets operations

long PPTabSheets::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPTabSheets::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

LPDISPATCH PPTabSheets::Add(LPCTSTR Name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name);
	return result;
}

LPDISPATCH PPTabSheets::GetActiveSheet()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPTabSheets::GetName()
{
	CString result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPTabSheets::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPControl properties

/////////////////////////////////////////////////////////////////////////////
// PPControl operations

LPDISPATCH PPControl::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPControl::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPControl::GetEnable()
{
	long result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPControl::SetEnable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPControl::GetVisible()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPControl::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPControl::GetFocus()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPControl::SetFocus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPControl::GetLabel()
{
	CString result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPControl::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPControl::GetHelpId()
{
	long result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPControl::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PPControl::GetLeft()
{
	float result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPControl::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPControl::GetTop()
{
	float result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPControl::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPControl::GetWidth()
{
	float result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPControl::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPControl::GetHeight()
{
	float result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPControl::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString PPControl::GetOnSetFocus()
{
	CString result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPControl::SetOnSetFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPControl::GetOnKillFocus()
{
	CString result;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPControl::SetOnKillFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPControl::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPControl::GetName()
{
	CString result;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPControl::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPPushButton properties

/////////////////////////////////////////////////////////////////////////////
// PPPushButton operations

LPDISPATCH PPPushButton::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPPushButton::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPPushButton::GetEnable()
{
	long result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPPushButton::SetEnable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPPushButton::GetVisible()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPPushButton::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPPushButton::GetFocus()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPPushButton::SetFocus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPPushButton::GetLabel()
{
	CString result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPPushButton::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPPushButton::GetHelpId()
{
	long result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPPushButton::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PPPushButton::GetLeft()
{
	float result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPPushButton::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPPushButton::GetTop()
{
	float result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPPushButton::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPPushButton::GetWidth()
{
	float result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPPushButton::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPPushButton::GetHeight()
{
	float result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPPushButton::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString PPPushButton::GetOnSetFocus()
{
	CString result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPPushButton::SetOnSetFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPPushButton::GetOnKillFocus()
{
	CString result;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPPushButton::SetOnKillFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPPushButton::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPPushButton::GetName()
{
	CString result;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPPushButton::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void PPPushButton::Click()
{
	InvokeHelper(0x7d1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long PPPushButton::GetIsDefault()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPPushButton::SetIsDefault(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPPushButton::GetIsEscape()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPPushButton::SetIsEscape(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPPushButton::GetOnPressed()
{
	CString result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPPushButton::SetOnPressed(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPToggleButton properties

/////////////////////////////////////////////////////////////////////////////
// PPToggleButton operations

LPDISPATCH PPToggleButton::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPToggleButton::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPToggleButton::GetEnable()
{
	long result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPToggleButton::SetEnable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPToggleButton::GetVisible()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPToggleButton::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPToggleButton::GetFocus()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPToggleButton::SetFocus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPToggleButton::GetLabel()
{
	CString result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPToggleButton::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPToggleButton::GetHelpId()
{
	long result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPToggleButton::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PPToggleButton::GetLeft()
{
	float result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPToggleButton::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPToggleButton::GetTop()
{
	float result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPToggleButton::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPToggleButton::GetWidth()
{
	float result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPToggleButton::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPToggleButton::GetHeight()
{
	float result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPToggleButton::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString PPToggleButton::GetOnSetFocus()
{
	CString result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPToggleButton::SetOnSetFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPToggleButton::GetOnKillFocus()
{
	CString result;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPToggleButton::SetOnKillFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPToggleButton::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPToggleButton::GetName()
{
	CString result;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPToggleButton::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPToggleButton::GetState()
{
	long result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPToggleButton::SetState(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPToggleButton::GetResourceID()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPToggleButton::SetResourceID(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void PPToggleButton::Click()
{
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString PPToggleButton::GetOnClick()
{
	CString result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPToggleButton::SetOnClick(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPBitmapButton properties

/////////////////////////////////////////////////////////////////////////////
// PPBitmapButton operations

LPDISPATCH PPBitmapButton::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPBitmapButton::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPBitmapButton::GetEnable()
{
	long result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPBitmapButton::SetEnable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPBitmapButton::GetVisible()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPBitmapButton::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPBitmapButton::GetFocus()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPBitmapButton::SetFocus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPBitmapButton::GetLabel()
{
	CString result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPBitmapButton::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPBitmapButton::GetHelpId()
{
	long result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPBitmapButton::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PPBitmapButton::GetLeft()
{
	float result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPBitmapButton::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPBitmapButton::GetTop()
{
	float result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPBitmapButton::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPBitmapButton::GetWidth()
{
	float result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPBitmapButton::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPBitmapButton::GetHeight()
{
	float result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPBitmapButton::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString PPBitmapButton::GetOnSetFocus()
{
	CString result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPBitmapButton::SetOnSetFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPBitmapButton::GetOnKillFocus()
{
	CString result;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPBitmapButton::SetOnKillFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPBitmapButton::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPBitmapButton::GetName()
{
	CString result;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPBitmapButton::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void PPBitmapButton::Click()
{
	InvokeHelper(0x7d1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long PPBitmapButton::GetResourceID()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPBitmapButton::SetResourceID(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPBitmapButton::GetOnPressed()
{
	CString result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPBitmapButton::SetOnPressed(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPBitmapButton::GetIsDefault()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPBitmapButton::SetIsDefault(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPBitmapButton::GetIsEscape()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPBitmapButton::SetIsEscape(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPListBox properties

/////////////////////////////////////////////////////////////////////////////
// PPListBox operations

LPDISPATCH PPListBox::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPListBox::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPListBox::GetEnable()
{
	long result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPListBox::SetEnable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPListBox::GetVisible()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPListBox::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPListBox::GetFocus()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPListBox::SetFocus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPListBox::GetLabel()
{
	CString result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPListBox::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPListBox::GetHelpId()
{
	long result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPListBox::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PPListBox::GetLeft()
{
	float result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPListBox::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPListBox::GetTop()
{
	float result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPListBox::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPListBox::GetWidth()
{
	float result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPListBox::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPListBox::GetHeight()
{
	float result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPListBox::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString PPListBox::GetOnSetFocus()
{
	CString result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPListBox::SetOnSetFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPListBox::GetOnKillFocus()
{
	CString result;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPListBox::SetOnKillFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPListBox::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPListBox::GetName()
{
	CString result;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPListBox::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPListBox::GetStrings()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPListBox::GetSelectionStyle()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPListBox::SetSelectionStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void PPListBox::SetTabStops(const VARIANT& safeArrayTabStops)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &safeArrayTabStops);
}

long PPListBox::GetFocusItem()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPListBox::SetFocusItem(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPListBox::GetTopItem()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString PPListBox::GetOnSelectionChange()
{
	CString result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPListBox::SetOnSelectionChange(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPListBox::GetOnDoubleClick()
{
	CString result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPListBox::SetOnDoubleClick(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPListBox::GetIsSelected(long index)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3e7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		index);
	return result;
}

void PPListBox::SetIsSelected(long index, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x3e7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 index, nNewValue);
}

void PPListBox::Abbreviate(long Style)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Style);
}

long PPListBox::GetIsAbbreviated()
{
	long result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// PPStrings properties

/////////////////////////////////////////////////////////////////////////////
// PPStrings operations

long PPStrings::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString PPStrings::Item(long index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		index);
	return result;
}

CString PPStrings::Add(LPCTSTR String)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d1, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		String);
	return result;
}

void PPStrings::Insert(LPCTSTR String, long Position)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x7d2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 String, Position);
}

void PPStrings::Delete(long index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 index);
}


/////////////////////////////////////////////////////////////////////////////
// PPCheckBox properties

/////////////////////////////////////////////////////////////////////////////
// PPCheckBox operations

LPDISPATCH PPCheckBox::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPCheckBox::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPCheckBox::GetEnable()
{
	long result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPCheckBox::SetEnable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPCheckBox::GetVisible()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPCheckBox::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPCheckBox::GetFocus()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPCheckBox::SetFocus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPCheckBox::GetLabel()
{
	CString result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPCheckBox::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPCheckBox::GetHelpId()
{
	long result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPCheckBox::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PPCheckBox::GetLeft()
{
	float result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPCheckBox::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPCheckBox::GetTop()
{
	float result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPCheckBox::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPCheckBox::GetWidth()
{
	float result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPCheckBox::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPCheckBox::GetHeight()
{
	float result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPCheckBox::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString PPCheckBox::GetOnSetFocus()
{
	CString result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPCheckBox::SetOnSetFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPCheckBox::GetOnKillFocus()
{
	CString result;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPCheckBox::SetOnKillFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPCheckBox::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPCheckBox::GetName()
{
	CString result;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPCheckBox::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPCheckBox::GetState()
{
	long result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPCheckBox::SetState(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void PPCheckBox::Click()
{
	InvokeHelper(0x7d2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString PPCheckBox::GetOnClick()
{
	CString result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPCheckBox::SetOnClick(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPRadioCluster properties

/////////////////////////////////////////////////////////////////////////////
// PPRadioCluster operations

LPDISPATCH PPRadioCluster::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPRadioCluster::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPRadioCluster::GetEnable()
{
	long result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPRadioCluster::SetEnable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPRadioCluster::GetVisible()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPRadioCluster::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPRadioCluster::GetFocus()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPRadioCluster::SetFocus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPRadioCluster::GetLabel()
{
	CString result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPRadioCluster::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPRadioCluster::GetHelpId()
{
	long result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPRadioCluster::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PPRadioCluster::GetLeft()
{
	float result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPRadioCluster::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPRadioCluster::GetTop()
{
	float result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPRadioCluster::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPRadioCluster::GetWidth()
{
	float result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPRadioCluster::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPRadioCluster::GetHeight()
{
	float result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPRadioCluster::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString PPRadioCluster::GetOnSetFocus()
{
	CString result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPRadioCluster::SetOnSetFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPRadioCluster::GetOnKillFocus()
{
	CString result;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPRadioCluster::SetOnKillFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPRadioCluster::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPRadioCluster::GetName()
{
	CString result;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPRadioCluster::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPRadioCluster::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

LPDISPATCH PPRadioCluster::Add(float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x7d1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Left, Top, Width, Height);
	return result;
}

long PPRadioCluster::GetCount()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPRadioCluster::GetSelected()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPRadioCluster::GetOnClick()
{
	CString result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPRadioCluster::SetOnClick(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPStaticText properties

/////////////////////////////////////////////////////////////////////////////
// PPStaticText operations

LPDISPATCH PPStaticText::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPStaticText::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPStaticText::GetEnable()
{
	long result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPStaticText::SetEnable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPStaticText::GetVisible()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPStaticText::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPStaticText::GetFocus()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPStaticText::SetFocus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPStaticText::GetLabel()
{
	CString result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPStaticText::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPStaticText::GetHelpId()
{
	long result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPStaticText::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PPStaticText::GetLeft()
{
	float result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPStaticText::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPStaticText::GetTop()
{
	float result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPStaticText::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPStaticText::GetWidth()
{
	float result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPStaticText::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPStaticText::GetHeight()
{
	float result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPStaticText::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString PPStaticText::GetOnSetFocus()
{
	CString result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPStaticText::SetOnSetFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPStaticText::GetOnKillFocus()
{
	CString result;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPStaticText::SetOnKillFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPStaticText::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPStaticText::GetName()
{
	CString result;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPStaticText::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPStaticText::GetUseForegroundColor()
{
	long result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPStaticText::SetUseForegroundColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPStaticText::GetUseBackgroundColor()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPStaticText::SetUseBackgroundColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPStaticText::GetForegroundColor()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPStaticText::SetForegroundColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPStaticText::GetBackgroundColor()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPStaticText::SetBackgroundColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPEditText properties

/////////////////////////////////////////////////////////////////////////////
// PPEditText operations

LPDISPATCH PPEditText::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPEditText::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPEditText::GetEnable()
{
	long result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPEditText::SetEnable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPEditText::GetVisible()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPEditText::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPEditText::GetFocus()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPEditText::SetFocus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPEditText::GetLabel()
{
	CString result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPEditText::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPEditText::GetHelpId()
{
	long result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPEditText::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PPEditText::GetLeft()
{
	float result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPEditText::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPEditText::GetTop()
{
	float result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPEditText::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPEditText::GetWidth()
{
	float result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPEditText::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPEditText::GetHeight()
{
	float result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPEditText::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString PPEditText::GetOnSetFocus()
{
	CString result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPEditText::SetOnSetFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPEditText::GetOnKillFocus()
{
	CString result;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPEditText::SetOnKillFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPEditText::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPEditText::GetName()
{
	CString result;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPEditText::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPEditText::GetMultiLine()
{
	long result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPEditText::SetMultiLine(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPEditText::GetVerticalScrollBar()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPEditText::SetVerticalScrollBar(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPEditText::GetWordWrap()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPEditText::SetWordWrap(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPEditText::GetReadOnly()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPEditText::SetReadOnly(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPEditText::GetText()
{
	CString result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPEditText::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPEditText::GetMaxLength()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPEditText::SetMaxLength(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPEditText::GetOnAChange()
{
	CString result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPEditText::SetOnAChange(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPIcon properties

/////////////////////////////////////////////////////////////////////////////
// PPIcon operations

LPDISPATCH PPIcon::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPIcon::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPIcon::GetEnable()
{
	long result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPIcon::SetEnable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPIcon::GetVisible()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPIcon::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPIcon::GetFocus()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPIcon::SetFocus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPIcon::GetLabel()
{
	CString result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPIcon::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPIcon::GetHelpId()
{
	long result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPIcon::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PPIcon::GetLeft()
{
	float result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPIcon::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPIcon::GetTop()
{
	float result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPIcon::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPIcon::GetWidth()
{
	float result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPIcon::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPIcon::GetHeight()
{
	float result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPIcon::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString PPIcon::GetOnSetFocus()
{
	CString result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPIcon::SetOnSetFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPIcon::GetOnKillFocus()
{
	CString result;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPIcon::SetOnKillFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPIcon::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPIcon::GetName()
{
	CString result;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPIcon::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPIcon::GetResourceID()
{
	long result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPIcon::SetResourceID(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPBitmap properties

/////////////////////////////////////////////////////////////////////////////
// PPBitmap operations

LPDISPATCH PPBitmap::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPBitmap::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPBitmap::GetEnable()
{
	long result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPBitmap::SetEnable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPBitmap::GetVisible()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPBitmap::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPBitmap::GetFocus()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPBitmap::SetFocus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPBitmap::GetLabel()
{
	CString result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPBitmap::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPBitmap::GetHelpId()
{
	long result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPBitmap::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PPBitmap::GetLeft()
{
	float result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPBitmap::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPBitmap::GetTop()
{
	float result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPBitmap::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPBitmap::GetWidth()
{
	float result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPBitmap::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPBitmap::GetHeight()
{
	float result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPBitmap::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString PPBitmap::GetOnSetFocus()
{
	CString result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPBitmap::SetOnSetFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPBitmap::GetOnKillFocus()
{
	CString result;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPBitmap::SetOnKillFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPBitmap::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPBitmap::GetName()
{
	CString result;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPBitmap::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPBitmap::GetResourceID()
{
	long result;
	InvokeHelper(0x7d0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPBitmap::SetResourceID(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPBitmap::GetOnClick()
{
	CString result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPBitmap::SetOnClick(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPSpinner properties

/////////////////////////////////////////////////////////////////////////////
// PPSpinner operations

LPDISPATCH PPSpinner::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPSpinner::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPSpinner::GetEnable()
{
	long result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPSpinner::SetEnable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPSpinner::GetVisible()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPSpinner::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPSpinner::GetFocus()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPSpinner::SetFocus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPSpinner::GetLabel()
{
	CString result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPSpinner::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPSpinner::GetHelpId()
{
	long result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPSpinner::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PPSpinner::GetLeft()
{
	float result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPSpinner::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPSpinner::GetTop()
{
	float result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPSpinner::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPSpinner::GetWidth()
{
	float result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPSpinner::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPSpinner::GetHeight()
{
	float result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPSpinner::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString PPSpinner::GetOnSetFocus()
{
	CString result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPSpinner::SetOnSetFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPSpinner::GetOnKillFocus()
{
	CString result;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPSpinner::SetOnKillFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPSpinner::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPSpinner::GetName()
{
	CString result;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPSpinner::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPSpinner::GetMinimum()
{
	long result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPSpinner::SetMinimum(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPSpinner::GetMaximum()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPSpinner::SetMaximum(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPSpinner::GetIncrement()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPSpinner::SetIncrement(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPSpinner::GetPageChange()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPSpinner::SetPageChange(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPSpinner::GetCurrentValue()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPSpinner::SetCurrentValue(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPSpinner::GetOnAChange()
{
	CString result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPSpinner::SetOnAChange(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPScrollBar properties

/////////////////////////////////////////////////////////////////////////////
// PPScrollBar operations

LPDISPATCH PPScrollBar::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPScrollBar::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPScrollBar::GetEnable()
{
	long result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPScrollBar::SetEnable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPScrollBar::GetVisible()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPScrollBar::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPScrollBar::GetFocus()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPScrollBar::SetFocus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPScrollBar::GetLabel()
{
	CString result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPScrollBar::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPScrollBar::GetHelpId()
{
	long result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPScrollBar::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PPScrollBar::GetLeft()
{
	float result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPScrollBar::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPScrollBar::GetTop()
{
	float result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPScrollBar::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPScrollBar::GetWidth()
{
	float result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPScrollBar::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPScrollBar::GetHeight()
{
	float result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPScrollBar::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString PPScrollBar::GetOnSetFocus()
{
	CString result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPScrollBar::SetOnSetFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPScrollBar::GetOnKillFocus()
{
	CString result;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPScrollBar::SetOnKillFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPScrollBar::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPScrollBar::GetName()
{
	CString result;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPScrollBar::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPScrollBar::GetMinimum()
{
	long result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPScrollBar::SetMinimum(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPScrollBar::GetMaximum()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPScrollBar::SetMaximum(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPScrollBar::GetIncrement()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPScrollBar::SetIncrement(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPScrollBar::GetPageChange()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPScrollBar::SetPageChange(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPScrollBar::GetCurrentValue()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPScrollBar::SetCurrentValue(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPScrollBar::GetOnScroll()
{
	CString result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPScrollBar::SetOnScroll(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPGroupBox properties

/////////////////////////////////////////////////////////////////////////////
// PPGroupBox operations

LPDISPATCH PPGroupBox::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPGroupBox::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPGroupBox::GetEnable()
{
	long result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPGroupBox::SetEnable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPGroupBox::GetVisible()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPGroupBox::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPGroupBox::GetFocus()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPGroupBox::SetFocus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPGroupBox::GetLabel()
{
	CString result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPGroupBox::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPGroupBox::GetHelpId()
{
	long result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPGroupBox::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PPGroupBox::GetLeft()
{
	float result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPGroupBox::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPGroupBox::GetTop()
{
	float result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPGroupBox::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPGroupBox::GetWidth()
{
	float result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPGroupBox::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPGroupBox::GetHeight()
{
	float result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPGroupBox::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString PPGroupBox::GetOnSetFocus()
{
	CString result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPGroupBox::SetOnSetFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPGroupBox::GetOnKillFocus()
{
	CString result;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPGroupBox::SetOnKillFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPGroupBox::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPGroupBox::GetName()
{
	CString result;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPGroupBox::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPFrame properties

/////////////////////////////////////////////////////////////////////////////
// PPFrame operations

LPDISPATCH PPFrame::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPFrame::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPFrame::GetEnable()
{
	long result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPFrame::SetEnable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPFrame::GetVisible()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPFrame::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPFrame::GetFocus()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPFrame::SetFocus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPFrame::GetLabel()
{
	CString result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPFrame::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPFrame::GetHelpId()
{
	long result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPFrame::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PPFrame::GetLeft()
{
	float result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPFrame::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPFrame::GetTop()
{
	float result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPFrame::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPFrame::GetWidth()
{
	float result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPFrame::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPFrame::GetHeight()
{
	float result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPFrame::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString PPFrame::GetOnSetFocus()
{
	CString result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPFrame::SetOnSetFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPFrame::GetOnKillFocus()
{
	CString result;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPFrame::SetOnKillFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPFrame::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPFrame::GetName()
{
	CString result;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPFrame::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPTabControl properties

/////////////////////////////////////////////////////////////////////////////
// PPTabControl operations

LPDISPATCH PPTabControl::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPTabControl::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPTabControl::GetEnable()
{
	long result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPTabControl::SetEnable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPTabControl::GetVisible()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPTabControl::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPTabControl::GetFocus()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPTabControl::SetFocus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPTabControl::GetLabel()
{
	CString result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPTabControl::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPTabControl::GetHelpId()
{
	long result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPTabControl::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PPTabControl::GetLeft()
{
	float result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPTabControl::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPTabControl::GetTop()
{
	float result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPTabControl::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPTabControl::GetWidth()
{
	float result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPTabControl::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPTabControl::GetHeight()
{
	float result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPTabControl::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString PPTabControl::GetOnSetFocus()
{
	CString result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPTabControl::SetOnSetFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPTabControl::GetOnKillFocus()
{
	CString result;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPTabControl::SetOnKillFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPTabControl::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPTabControl::GetName()
{
	CString result;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPTabControl::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPDropDown properties

/////////////////////////////////////////////////////////////////////////////
// PPDropDown operations

LPDISPATCH PPDropDown::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPDropDown::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPDropDown::GetEnable()
{
	long result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPDropDown::SetEnable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPDropDown::GetVisible()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPDropDown::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPDropDown::GetFocus()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPDropDown::SetFocus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPDropDown::GetLabel()
{
	CString result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDropDown::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPDropDown::GetHelpId()
{
	long result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPDropDown::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PPDropDown::GetLeft()
{
	float result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPDropDown::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPDropDown::GetTop()
{
	float result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPDropDown::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPDropDown::GetWidth()
{
	float result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPDropDown::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPDropDown::GetHeight()
{
	float result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPDropDown::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString PPDropDown::GetOnSetFocus()
{
	CString result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDropDown::SetOnSetFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPDropDown::GetOnKillFocus()
{
	CString result;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDropDown::SetOnKillFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPDropDown::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPDropDown::GetName()
{
	CString result;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDropDown::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPDropDown::GetStrings()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPDropDown::GetFocusItem()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPDropDown::SetFocusItem(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPDropDown::GetOnSelectionChange()
{
	CString result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDropDown::SetOnSelectionChange(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPDropDownEdit properties

/////////////////////////////////////////////////////////////////////////////
// PPDropDownEdit operations

LPDISPATCH PPDropDownEdit::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPDropDownEdit::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPDropDownEdit::GetEnable()
{
	long result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPDropDownEdit::SetEnable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPDropDownEdit::GetVisible()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPDropDownEdit::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPDropDownEdit::GetFocus()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPDropDownEdit::SetFocus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPDropDownEdit::GetLabel()
{
	CString result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDropDownEdit::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPDropDownEdit::GetHelpId()
{
	long result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPDropDownEdit::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PPDropDownEdit::GetLeft()
{
	float result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPDropDownEdit::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPDropDownEdit::GetTop()
{
	float result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPDropDownEdit::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPDropDownEdit::GetWidth()
{
	float result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPDropDownEdit::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPDropDownEdit::GetHeight()
{
	float result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPDropDownEdit::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString PPDropDownEdit::GetOnSetFocus()
{
	CString result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDropDownEdit::SetOnSetFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPDropDownEdit::GetOnKillFocus()
{
	CString result;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDropDownEdit::SetOnKillFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPDropDownEdit::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPDropDownEdit::GetName()
{
	CString result;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDropDownEdit::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPDropDownEdit::GetStrings()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPDropDownEdit::GetFocusItem()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPDropDownEdit::SetFocusItem(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPDropDownEdit::GetOnSelectionChange()
{
	CString result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDropDownEdit::SetOnSelectionChange(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPDropDownEdit::GetOnEdit()
{
	CString result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPDropDownEdit::SetOnEdit(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPSlideMiniature properties

/////////////////////////////////////////////////////////////////////////////
// PPSlideMiniature operations

LPDISPATCH PPSlideMiniature::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPSlideMiniature::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPSlideMiniature::GetEnable()
{
	long result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPSlideMiniature::SetEnable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPSlideMiniature::GetVisible()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPSlideMiniature::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPSlideMiniature::GetFocus()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPSlideMiniature::SetFocus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPSlideMiniature::GetLabel()
{
	CString result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPSlideMiniature::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPSlideMiniature::GetHelpId()
{
	long result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPSlideMiniature::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PPSlideMiniature::GetLeft()
{
	float result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPSlideMiniature::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPSlideMiniature::GetTop()
{
	float result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPSlideMiniature::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPSlideMiniature::GetWidth()
{
	float result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPSlideMiniature::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPSlideMiniature::GetHeight()
{
	float result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPSlideMiniature::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString PPSlideMiniature::GetOnSetFocus()
{
	CString result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPSlideMiniature::SetOnSetFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPSlideMiniature::GetOnKillFocus()
{
	CString result;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPSlideMiniature::SetOnKillFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPSlideMiniature::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPSlideMiniature::GetName()
{
	CString result;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPSlideMiniature::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void PPSlideMiniature::SetImage(LPDISPATCH Slide)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x7d1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Slide);
}

long PPSlideMiniature::GetSelected()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPSlideMiniature::SetSelected(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPSlideMiniature::GetOnClick()
{
	CString result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPSlideMiniature::SetOnClick(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPSlideMiniature::GetOnDoubleClick()
{
	CString result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPSlideMiniature::SetOnDoubleClick(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// PPRadioButton properties

/////////////////////////////////////////////////////////////////////////////
// PPRadioButton operations

LPDISPATCH PPRadioButton::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PPRadioButton::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PPRadioButton::GetEnable()
{
	long result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPRadioButton::SetEnable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPRadioButton::GetVisible()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPRadioButton::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PPRadioButton::GetFocus()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPRadioButton::SetFocus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PPRadioButton::GetLabel()
{
	CString result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPRadioButton::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPRadioButton::GetHelpId()
{
	long result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPRadioButton::SetHelpId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PPRadioButton::GetLeft()
{
	float result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPRadioButton::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPRadioButton::GetTop()
{
	float result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPRadioButton::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPRadioButton::GetWidth()
{
	float result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPRadioButton::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PPRadioButton::GetHeight()
{
	float result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PPRadioButton::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString PPRadioButton::GetOnSetFocus()
{
	CString result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPRadioButton::SetOnSetFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPRadioButton::GetOnKillFocus()
{
	CString result;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPRadioButton::SetOnKillFocus(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH PPRadioButton::GetTags()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString PPRadioButton::GetName()
{
	CString result;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPRadioButton::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PPRadioButton::GetState()
{
	long result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PPRadioButton::SetState(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void PPRadioButton::Click()
{
	InvokeHelper(0x7d2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void PPRadioButton::DoubleClick()
{
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString PPRadioButton::GetOnClick()
{
	CString result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPRadioButton::SetOnClick(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString PPRadioButton::GetOnDoubleClick()
{
	CString result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PPRadioButton::SetOnDoubleClick(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// Tags properties

/////////////////////////////////////////////////////////////////////////////
// Tags operations

long Tags::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Tags::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Tags::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString Tags::Item(LPCTSTR Name)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Name);
	return result;
}

void Tags::Add(LPCTSTR Name, LPCTSTR Value)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name, Value);
}

void Tags::Delete(LPCTSTR Name)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name);
}

CString Tags::Name(long index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d7, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		index);
	return result;
}

CString Tags::Value(long index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d8, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// FileDialogFileList properties

/////////////////////////////////////////////////////////////////////////////
// FileDialogFileList operations

long FileDialogFileList::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH FileDialogFileList::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH FileDialogFileList::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString FileDialogFileList::Item(long index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		index);
	return result;
}

CString FileDialogFileList::DisplayName(long index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// FileDialogExtension properties

/////////////////////////////////////////////////////////////////////////////
// FileDialogExtension operations

LPDISPATCH FileDialogExtension::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH FileDialogExtension::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString FileDialogExtension::GetExtensions()
{
	CString result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FileDialogExtension::SetExtensions(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString FileDialogExtension::GetDescription()
{
	CString result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FileDialogExtension::SetDescription(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// FileDialogExtensionList properties

/////////////////////////////////////////////////////////////////////////////
// FileDialogExtensionList operations

long FileDialogExtensionList::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH FileDialogExtensionList::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH FileDialogExtensionList::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH FileDialogExtensionList::Item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

LPDISPATCH FileDialogExtensionList::Add(LPCTSTR Extension, LPCTSTR Description)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Extension, Description);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// FileDialog properties

/////////////////////////////////////////////////////////////////////////////
// FileDialog operations

LPDISPATCH FileDialog::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH FileDialog::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH FileDialog::GetExtensions()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString FileDialog::GetDefaultDirectoryRegKey()
{
	CString result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FileDialog::SetDefaultDirectoryRegKey(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString FileDialog::GetDialogTitle()
{
	CString result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FileDialog::SetDialogTitle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString FileDialog::GetActionButtonName()
{
	CString result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FileDialog::SetActionButtonName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long FileDialog::GetIsMultiSelect()
{
	long result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void FileDialog::SetIsMultiSelect(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long FileDialog::GetIsPrintEnabled()
{
	long result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void FileDialog::SetIsPrintEnabled(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long FileDialog::GetIsReadOnlyEnabled()
{
	long result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void FileDialog::SetIsReadOnlyEnabled(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long FileDialog::GetDirectoriesOnly()
{
	long result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void FileDialog::SetDirectoriesOnly(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7da, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long FileDialog::GetInitialView()
{
	long result;
	InvokeHelper(0x7db, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void FileDialog::SetInitialView(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7db, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void FileDialog::Launch(LPUNKNOWN pUnk)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x7dc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pUnk);
}

CString FileDialog::GetOnAction()
{
	CString result;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FileDialog::SetOnAction(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH FileDialog::GetFiles()
{
	LPDISPATCH result;
	InvokeHelper(0x7de, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long FileDialog::GetUseODMADlgs()
{
	long result;
	InvokeHelper(0x7df, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void FileDialog::SetUseODMADlgs(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7df, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// OCXExtender properties

/////////////////////////////////////////////////////////////////////////////
// OCXExtender operations

BOOL OCXExtender::GetVisible()
{
	BOOL result;
	InvokeHelper(0x80010007, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void OCXExtender::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x80010007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

float OCXExtender::GetLeft()
{
	float result;
	InvokeHelper(0x80010003, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void OCXExtender::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x80010003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float OCXExtender::GetTop()
{
	float result;
	InvokeHelper(0x80010004, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void OCXExtender::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x80010004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float OCXExtender::GetHeight()
{
	float result;
	InvokeHelper(0x80010005, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void OCXExtender::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x80010005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float OCXExtender::GetWidth()
{
	float result;
	InvokeHelper(0x80010006, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void OCXExtender::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x80010006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long OCXExtender::GetZOrderPosition()
{
	long result;
	InvokeHelper(0x800100e6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString OCXExtender::GetName()
{
	CString result;
	InvokeHelper(0x80010000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void OCXExtender::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x80010000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// Table properties

/////////////////////////////////////////////////////////////////////////////
// Table operations

LPDISPATCH Table::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Table::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Table::GetColumns()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Table::GetRows()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Table::Cell(long Row, long Column)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7d5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Row, Column);
	return result;
}

long Table::GetTableDirection()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Table::SetTableDirection(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// Columns properties

/////////////////////////////////////////////////////////////////////////////
// Columns operations

long Columns::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Columns::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Columns::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Columns::Item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

LPDISPATCH Columns::Add(long BeforeColumn)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		BeforeColumn);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Column properties

/////////////////////////////////////////////////////////////////////////////
// Column operations

LPDISPATCH Column::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Column::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Column::GetCells()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Column::Select()
{
	InvokeHelper(0x7d4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Column::Delete()
{
	InvokeHelper(0x7d5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

float Column::GetWidth()
{
	float result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void Column::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}


/////////////////////////////////////////////////////////////////////////////
// Rows properties

/////////////////////////////////////////////////////////////////////////////
// Rows operations

long Rows::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Rows::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Rows::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Rows::Item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

LPDISPATCH Rows::Add(long BeforeRow)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		BeforeRow);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Row properties

/////////////////////////////////////////////////////////////////////////////
// Row operations

LPDISPATCH Row::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Row::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Row::GetCells()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Row::Select()
{
	InvokeHelper(0x7d4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Row::Delete()
{
	InvokeHelper(0x7d5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

float Row::GetHeight()
{
	float result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void Row::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}


/////////////////////////////////////////////////////////////////////////////
// CellRange properties

/////////////////////////////////////////////////////////////////////////////
// CellRange operations

long CellRange::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH CellRange::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH CellRange::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH CellRange::Item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

LPDISPATCH CellRange::GetBorders()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Cell properties

/////////////////////////////////////////////////////////////////////////////
// Cell operations

LPDISPATCH Cell::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Cell::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Cell::GetShape()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Cell::GetBorders()
{
	LPDISPATCH result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Cell::Merge(LPDISPATCH MergeTo)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x7d5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MergeTo);
}

void Cell::Split(long NumRows, long NumColumns)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 NumRows, NumColumns);
}

void Cell::Select()
{
	InvokeHelper(0x7d7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL Cell::GetSelected()
{
	BOOL result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Borders properties

/////////////////////////////////////////////////////////////////////////////
// Borders operations

long Borders::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Borders::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Borders::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Borders::Item(long BorderType)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		BorderType);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Panes properties

/////////////////////////////////////////////////////////////////////////////
// Panes operations

long Panes::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Panes::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Panes::Item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

LPDISPATCH Panes::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Pane properties

/////////////////////////////////////////////////////////////////////////////
// Pane operations

LPDISPATCH Pane::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Pane::Activate()
{
	InvokeHelper(0x7d1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long Pane::GetActive()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Pane::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Pane::GetViewType()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DefaultWebOptions properties

/////////////////////////////////////////////////////////////////////////////
// DefaultWebOptions operations

long DefaultWebOptions::GetIncludeNavigation()
{
	long result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void DefaultWebOptions::SetIncludeNavigation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long DefaultWebOptions::GetFrameColors()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void DefaultWebOptions::SetFrameColors(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long DefaultWebOptions::GetResizeGraphics()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void DefaultWebOptions::SetResizeGraphics(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long DefaultWebOptions::GetShowSlideAnimation()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void DefaultWebOptions::SetShowSlideAnimation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long DefaultWebOptions::GetOrganizeInFolder()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void DefaultWebOptions::SetOrganizeInFolder(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long DefaultWebOptions::GetUseLongFileNames()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void DefaultWebOptions::SetUseLongFileNames(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long DefaultWebOptions::GetRelyOnVML()
{
	long result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void DefaultWebOptions::SetRelyOnVML(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long DefaultWebOptions::GetAllowPNG()
{
	long result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void DefaultWebOptions::SetAllowPNG(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long DefaultWebOptions::GetScreenSize()
{
	long result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void DefaultWebOptions::SetScreenSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long DefaultWebOptions::GetEncoding()
{
	long result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void DefaultWebOptions::SetEncoding(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7da, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long DefaultWebOptions::GetUpdateLinksOnSave()
{
	long result;
	InvokeHelper(0x7db, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void DefaultWebOptions::SetUpdateLinksOnSave(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7db, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long DefaultWebOptions::GetCheckIfOfficeIsHTMLEditor()
{
	long result;
	InvokeHelper(0x7dc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void DefaultWebOptions::SetCheckIfOfficeIsHTMLEditor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7dc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long DefaultWebOptions::GetAlwaysSaveInDefaultEncoding()
{
	long result;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void DefaultWebOptions::SetAlwaysSaveInDefaultEncoding(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7dd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH DefaultWebOptions::GetFonts()
{
	LPDISPATCH result;
	InvokeHelper(0x7de, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString DefaultWebOptions::GetFolderSuffix()
{
	CString result;
	InvokeHelper(0x7df, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// WebOptions properties

/////////////////////////////////////////////////////////////////////////////
// WebOptions operations

long WebOptions::GetIncludeNavigation()
{
	long result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void WebOptions::SetIncludeNavigation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long WebOptions::GetFrameColors()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void WebOptions::SetFrameColors(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long WebOptions::GetResizeGraphics()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void WebOptions::SetResizeGraphics(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long WebOptions::GetShowSlideAnimation()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void WebOptions::SetShowSlideAnimation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long WebOptions::GetOrganizeInFolder()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void WebOptions::SetOrganizeInFolder(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long WebOptions::GetUseLongFileNames()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void WebOptions::SetUseLongFileNames(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long WebOptions::GetRelyOnVML()
{
	long result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void WebOptions::SetRelyOnVML(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long WebOptions::GetAllowPNG()
{
	long result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void WebOptions::SetAllowPNG(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long WebOptions::GetScreenSize()
{
	long result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void WebOptions::SetScreenSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long WebOptions::GetEncoding()
{
	long result;
	InvokeHelper(0x7da, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void WebOptions::SetEncoding(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7da, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString WebOptions::GetFolderSuffix()
{
	CString result;
	InvokeHelper(0x7db, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void WebOptions::UseDefaultFolderSuffix()
{
	InvokeHelper(0x7dc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// PublishObjects properties

/////////////////////////////////////////////////////////////////////////////
// PublishObjects operations

long PublishObjects::GetCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH PublishObjects::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PublishObjects::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PublishObjects::Item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// PublishObject properties

/////////////////////////////////////////////////////////////////////////////
// PublishObject operations

LPDISPATCH PublishObject::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PublishObject::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PublishObject::GetHTMLVersion()
{
	long result;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PublishObject::SetHTMLVersion(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PublishObject::GetSourceType()
{
	long result;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PublishObject::SetSourceType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PublishObject::GetRangeStart()
{
	long result;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PublishObject::SetRangeStart(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PublishObject::GetRangeEnd()
{
	long result;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PublishObject::SetRangeEnd(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PublishObject::GetSlideShowName()
{
	CString result;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PublishObject::SetSlideShowName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long PublishObject::GetSpeakerNotes()
{
	long result;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PublishObject::SetSpeakerNotes(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString PublishObject::GetFileName()
{
	CString result;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void PublishObject::SetFileName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void PublishObject::Publish()
{
	InvokeHelper(0x7da, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Marker properties

/////////////////////////////////////////////////////////////////////////////
// Marker operations

long Marker::GetMarkerType()
{
	long result;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Marker::SetMarkerType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Marker::GetTime()
{
	long result;
	InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}
