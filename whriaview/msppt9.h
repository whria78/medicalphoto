// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// Collection wrapper class

class Collection : public COleDispatchDriver
{
public:
	Collection() {}		// Calls COleDispatchDriver default constructor
	Collection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Collection(const Collection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
};
/////////////////////////////////////////////////////////////////////////////
// _Application wrapper class

class _Application : public COleDispatchDriver
{
public:
	_Application() {}		// Calls COleDispatchDriver default constructor
	_Application(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Application(const _Application& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetPresentations();
	LPDISPATCH GetWindows();
	LPDISPATCH GetActiveWindow();
	LPDISPATCH GetActivePresentation();
	LPDISPATCH GetSlideShowWindows();
	LPDISPATCH GetCommandBars();
	CString GetPath();
	CString GetName();
	CString GetCaption();
	void SetCaption(LPCTSTR lpszNewValue);
	LPDISPATCH GetAssistant();
	LPDISPATCH GetFileSearch();
	LPDISPATCH GetFileFind();
	CString GetBuild();
	CString GetVersion();
	CString GetOperatingSystem();
	CString GetActivePrinter();
	long GetCreator();
	LPDISPATCH GetAddIns();
	LPDISPATCH GetVbe();
	void Help(LPCTSTR HelpFile, long ContextID);
	void Quit();
	// method 'Run' not emitted because of invalid return type or parameter type
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	long GetWindowState();
	void SetWindowState(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetActive();
	void Activate();
	LPDISPATCH GetAnswerWizard();
	LPDISPATCH GetCOMAddIns();
	CString GetProductCode();
	LPDISPATCH GetDefaultWebOptions();
	LPDISPATCH GetLanguageSettings();
	long GetShowWindowsInTaskbar();
	void SetShowWindowsInTaskbar(long nNewValue);
	long GetFeatureInstall();
	void SetFeatureInstall(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// _Global wrapper class

class _Global : public COleDispatchDriver
{
public:
	_Global() {}		// Calls COleDispatchDriver default constructor
	_Global(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Global(const _Global& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetActivePresentation();
	LPDISPATCH GetActiveWindow();
	LPDISPATCH GetAddIns();
	LPDISPATCH GetApplication();
	LPDISPATCH GetAssistant();
	LPDISPATCH GetPresentations();
	LPDISPATCH GetSlideShowWindows();
	LPDISPATCH GetWindows();
	LPDISPATCH GetCommandBars();
	LPDISPATCH GetAnswerWizard();
};
/////////////////////////////////////////////////////////////////////////////
// ColorFormat wrapper class

class ColorFormat : public COleDispatchDriver
{
public:
	ColorFormat() {}		// Calls COleDispatchDriver default constructor
	ColorFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ColorFormat(const ColorFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetRgb();
	void SetRgb(long nNewValue);
	long GetType();
	long GetSchemeColor();
	void SetSchemeColor(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// SlideShowWindow wrapper class

class SlideShowWindow : public COleDispatchDriver
{
public:
	SlideShowWindow() {}		// Calls COleDispatchDriver default constructor
	SlideShowWindow(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	SlideShowWindow(const SlideShowWindow& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetView();
	LPDISPATCH GetPresentation();
	long GetIsFullScreen();
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	long GetActive();
	void Activate();
};
/////////////////////////////////////////////////////////////////////////////
// Selection wrapper class

class Selection : public COleDispatchDriver
{
public:
	Selection() {}		// Calls COleDispatchDriver default constructor
	Selection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Selection(const Selection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	void Cut();
	void Copy();
	void Delete();
	void Unselect();
	long GetType();
	LPDISPATCH GetSlideRange();
	LPDISPATCH GetShapeRange();
	LPDISPATCH GetTextRange();
};
/////////////////////////////////////////////////////////////////////////////
// DocumentWindows wrapper class

class DocumentWindows : public COleDispatchDriver
{
public:
	DocumentWindows() {}		// Calls COleDispatchDriver default constructor
	DocumentWindows(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DocumentWindows(const DocumentWindows& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long index);
	void Arrange(long arrangeStyle);
};
/////////////////////////////////////////////////////////////////////////////
// SlideShowWindows wrapper class

class SlideShowWindows : public COleDispatchDriver
{
public:
	SlideShowWindows() {}		// Calls COleDispatchDriver default constructor
	SlideShowWindows(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	SlideShowWindows(const SlideShowWindows& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long index);
};
/////////////////////////////////////////////////////////////////////////////
// DocumentWindow wrapper class

class DocumentWindow : public COleDispatchDriver
{
public:
	DocumentWindow() {}		// Calls COleDispatchDriver default constructor
	DocumentWindow(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DocumentWindow(const DocumentWindow& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetSelection();
	LPDISPATCH GetView();
	LPDISPATCH GetPresentation();
	long GetViewType();
	void SetViewType(long nNewValue);
	long GetBlackAndWhite();
	void SetBlackAndWhite(long nNewValue);
	long GetActive();
	long GetWindowState();
	void SetWindowState(long nNewValue);
	CString GetCaption();
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	void FitToPage();
	void Activate();
	void LargeScroll(long Down, long Up, long ToRight, long ToLeft);
	void SmallScroll(long Down, long Up, long ToRight, long ToLeft);
	LPDISPATCH NewWindow();
	void Close();
	LPDISPATCH GetActivePane();
	LPDISPATCH GetPanes();
	long GetSplitVertical();
	void SetSplitVertical(long nNewValue);
	long GetSplitHorizontal();
	void SetSplitHorizontal(long nNewValue);
	LPDISPATCH RangeFromPoint(long X, long Y);
	long PointsToScreenPixelsX(float Points);
	long PointsToScreenPixelsY(float Points);
	void ScrollIntoView(float Left, float Top, float Width, float Height, long Start);
};
/////////////////////////////////////////////////////////////////////////////
// View wrapper class

class View : public COleDispatchDriver
{
public:
	View() {}		// Calls COleDispatchDriver default constructor
	View(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	View(const View& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	long GetZoom();
	void SetZoom(long nNewValue);
	void Paste();
	LPDISPATCH GetSlide();
	void SetSlide(LPDISPATCH newValue);
	void GotoSlide(long index);
	long GetDisplaySlideMiniature();
	void SetDisplaySlideMiniature(long nNewValue);
	long GetZoomToFit();
	void SetZoomToFit(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// SlideShowView wrapper class

class SlideShowView : public COleDispatchDriver
{
public:
	SlideShowView() {}		// Calls COleDispatchDriver default constructor
	SlideShowView(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	SlideShowView(const SlideShowView& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetZoom();
	LPDISPATCH GetSlide();
	long GetPointerType();
	void SetPointerType(long nNewValue);
	long GetState();
	void SetState(long nNewValue);
	long GetAcceleratorsEnabled();
	void SetAcceleratorsEnabled(long nNewValue);
	float GetPresentationElapsedTime();
	float GetSlideElapsedTime();
	void SetSlideElapsedTime(float newValue);
	LPDISPATCH GetLastSlideViewed();
	long GetAdvanceMode();
	LPDISPATCH GetPointerColor();
	long GetIsNamedShow();
	CString GetSlideShowName();
	void DrawLine(float BeginX, float BeginY, float EndX, float EndY);
	void EraseDrawing();
	void First();
	void Last();
	void Next();
	void Previous();
	void GotoSlide(long index, long ResetSlide);
	void GotoNamedShow(LPCTSTR SlideShowName);
	void EndNamedShow();
	void ResetSlideTime();
	void Exit();
	long GetCurrentShowPosition();
};
/////////////////////////////////////////////////////////////////////////////
// SlideShowSettings wrapper class

class SlideShowSettings : public COleDispatchDriver
{
public:
	SlideShowSettings() {}		// Calls COleDispatchDriver default constructor
	SlideShowSettings(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	SlideShowSettings(const SlideShowSettings& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetPointerColor();
	LPDISPATCH GetNamedSlideShows();
	long GetStartingSlide();
	void SetStartingSlide(long nNewValue);
	long GetEndingSlide();
	void SetEndingSlide(long nNewValue);
	long GetAdvanceMode();
	void SetAdvanceMode(long nNewValue);
	LPDISPATCH Run();
	long GetLoopUntilStopped();
	void SetLoopUntilStopped(long nNewValue);
	long GetShowType();
	void SetShowType(long nNewValue);
	long GetShowWithNarration();
	void SetShowWithNarration(long nNewValue);
	long GetShowWithAnimation();
	void SetShowWithAnimation(long nNewValue);
	CString GetSlideShowName();
	void SetSlideShowName(LPCTSTR lpszNewValue);
	long GetRangeType();
	void SetRangeType(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// NamedSlideShows wrapper class

class NamedSlideShows : public COleDispatchDriver
{
public:
	NamedSlideShows() {}		// Calls COleDispatchDriver default constructor
	NamedSlideShows(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	NamedSlideShows(const NamedSlideShows& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(const VARIANT& index);
	LPDISPATCH Add(LPCTSTR Name, const VARIANT& safeArrayOfSlideIDs);
};
/////////////////////////////////////////////////////////////////////////////
// NamedSlideShow wrapper class

class NamedSlideShow : public COleDispatchDriver
{
public:
	NamedSlideShow() {}		// Calls COleDispatchDriver default constructor
	NamedSlideShow(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	NamedSlideShow(const NamedSlideShow& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetName();
	void Delete();
	VARIANT GetSlideIDs();
	long GetCount();
};
/////////////////////////////////////////////////////////////////////////////
// PrintOptions wrapper class

class PrintOptions : public COleDispatchDriver
{
public:
	PrintOptions() {}		// Calls COleDispatchDriver default constructor
	PrintOptions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PrintOptions(const PrintOptions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetPrintColorType();
	void SetPrintColorType(long nNewValue);
	long GetCollate();
	void SetCollate(long nNewValue);
	long GetFitToPage();
	void SetFitToPage(long nNewValue);
	long GetFrameSlides();
	void SetFrameSlides(long nNewValue);
	long GetNumberOfCopies();
	void SetNumberOfCopies(long nNewValue);
	long GetOutputType();
	void SetOutputType(long nNewValue);
	LPDISPATCH GetParent();
	long GetPrintHiddenSlides();
	void SetPrintHiddenSlides(long nNewValue);
	long GetPrintInBackground();
	void SetPrintInBackground(long nNewValue);
	long GetRangeType();
	void SetRangeType(long nNewValue);
	LPDISPATCH GetRanges();
	long GetPrintFontsAsGraphics();
	void SetPrintFontsAsGraphics(long nNewValue);
	CString GetSlideShowName();
	void SetSlideShowName(LPCTSTR lpszNewValue);
	CString GetActivePrinter();
	void SetActivePrinter(LPCTSTR lpszNewValue);
	long GetHandoutOrder();
	void SetHandoutOrder(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PrintRanges wrapper class

class PrintRanges : public COleDispatchDriver
{
public:
	PrintRanges() {}		// Calls COleDispatchDriver default constructor
	PrintRanges(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PrintRanges(const PrintRanges& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH Add(long Start, long End);
	LPDISPATCH GetApplication();
	void ClearAll();
	LPDISPATCH Item(long index);
	LPDISPATCH GetParent();
};
/////////////////////////////////////////////////////////////////////////////
// PrintRange wrapper class

class PrintRange : public COleDispatchDriver
{
public:
	PrintRange() {}		// Calls COleDispatchDriver default constructor
	PrintRange(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PrintRange(const PrintRange& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetStart();
	long GetEnd();
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// AddIns wrapper class

class AddIns : public COleDispatchDriver
{
public:
	AddIns() {}		// Calls COleDispatchDriver default constructor
	AddIns(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AddIns(const AddIns& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(VARIANT* index);
	LPDISPATCH Add(LPCTSTR FileName);
	void Remove(VARIANT* index);
};
/////////////////////////////////////////////////////////////////////////////
// AddIn wrapper class

class AddIn : public COleDispatchDriver
{
public:
	AddIn() {}		// Calls COleDispatchDriver default constructor
	AddIn(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AddIn(const AddIn& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetFullName();
	CString GetName();
	CString GetPath();
	long GetRegistered();
	void SetRegistered(long nNewValue);
	long GetAutoLoad();
	void SetAutoLoad(long nNewValue);
	long GetLoaded();
	void SetLoaded(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// Presentations wrapper class

class Presentations : public COleDispatchDriver
{
public:
	Presentations() {}		// Calls COleDispatchDriver default constructor
	Presentations(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Presentations(const Presentations& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(const VARIANT& index);
	LPDISPATCH Add(long WithWindow);
	LPDISPATCH Open(LPCTSTR FileName, long ReadOnly, long Untitled, long WithWindow);
};
/////////////////////////////////////////////////////////////////////////////
// Hyperlinks wrapper class

class Hyperlinks : public COleDispatchDriver
{
public:
	Hyperlinks() {}		// Calls COleDispatchDriver default constructor
	Hyperlinks(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Hyperlinks(const Hyperlinks& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long index);
};
/////////////////////////////////////////////////////////////////////////////
// Hyperlink wrapper class

class Hyperlink : public COleDispatchDriver
{
public:
	Hyperlink() {}		// Calls COleDispatchDriver default constructor
	Hyperlink(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Hyperlink(const Hyperlink& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetAddress();
	void SetAddress(LPCTSTR lpszNewValue);
	CString GetSubAddress();
	void SetSubAddress(LPCTSTR lpszNewValue);
	void AddToFavorites();
	CString GetEmailSubject();
	void SetEmailSubject(LPCTSTR lpszNewValue);
	CString GetScreenTip();
	void SetScreenTip(LPCTSTR lpszNewValue);
	CString GetTextToDisplay();
	void SetTextToDisplay(LPCTSTR lpszNewValue);
	long GetShowandReturn();
	void SetShowandReturn(long nNewValue);
	void Follow();
	void CreateNewDocument(LPCTSTR FileName, long EditNow, long Overwrite);
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// PageSetup wrapper class

class PageSetup : public COleDispatchDriver
{
public:
	PageSetup() {}		// Calls COleDispatchDriver default constructor
	PageSetup(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PageSetup(const PageSetup& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetFirstSlideNumber();
	void SetFirstSlideNumber(long nNewValue);
	float GetSlideHeight();
	void SetSlideHeight(float newValue);
	float GetSlideWidth();
	void SetSlideWidth(float newValue);
	long GetSlideSize();
	void SetSlideSize(long nNewValue);
	long GetNotesOrientation();
	void SetNotesOrientation(long nNewValue);
	long GetSlideOrientation();
	void SetSlideOrientation(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// Fonts wrapper class

class Fonts : public COleDispatchDriver
{
public:
	Fonts() {}		// Calls COleDispatchDriver default constructor
	Fonts(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Fonts(const Fonts& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(const VARIANT& index);
	void Replace(LPCTSTR Original, LPCTSTR Replacement);
};
/////////////////////////////////////////////////////////////////////////////
// ExtraColors wrapper class

class ExtraColors : public COleDispatchDriver
{
public:
	ExtraColors() {}		// Calls COleDispatchDriver default constructor
	ExtraColors(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ExtraColors(const ExtraColors& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long Item(long index);
	void Add(long Type);
};
/////////////////////////////////////////////////////////////////////////////
// Slides wrapper class

class Slides : public COleDispatchDriver
{
public:
	Slides() {}		// Calls COleDispatchDriver default constructor
	Slides(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Slides(const Slides& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(const VARIANT& index);
	LPDISPATCH FindBySlideID(long SlideID);
	LPDISPATCH Add(long index, long Layout);
	long InsertFromFile(LPCTSTR FileName, long index, long SlideStart, long SlideEnd);
	LPDISPATCH Range(const VARIANT& index);
	LPDISPATCH Paste(long index);
};
/////////////////////////////////////////////////////////////////////////////
// _Slide wrapper class

class _Slide : public COleDispatchDriver
{
public:
	_Slide() {}		// Calls COleDispatchDriver default constructor
	_Slide(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Slide(const _Slide& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetShapes();
	LPDISPATCH GetHeadersFooters();
	LPDISPATCH GetSlideShowTransition();
	LPDISPATCH GetColorScheme();
	void SetColorScheme(LPDISPATCH newValue);
	LPDISPATCH GetBackground();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long GetSlideID();
	long GetPrintSteps();
	void Select();
	void Cut();
	void Copy();
	long GetLayout();
	void SetLayout(long nNewValue);
	LPDISPATCH Duplicate();
	void Delete();
	LPDISPATCH GetTags();
	long GetSlideIndex();
	long GetSlideNumber();
	long GetDisplayMasterShapes();
	void SetDisplayMasterShapes(long nNewValue);
	long GetFollowMasterBackground();
	void SetFollowMasterBackground(long nNewValue);
	LPDISPATCH GetNotesPage();
	LPDISPATCH GetMaster();
	LPDISPATCH GetHyperlinks();
	void Export(LPCTSTR FileName, LPCTSTR FilterName, long ScaleWidth, long ScaleHeight);
	LPDISPATCH GetScripts();
};
/////////////////////////////////////////////////////////////////////////////
// SlideRange wrapper class

class SlideRange : public COleDispatchDriver
{
public:
	SlideRange() {}		// Calls COleDispatchDriver default constructor
	SlideRange(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	SlideRange(const SlideRange& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetShapes();
	LPDISPATCH GetHeadersFooters();
	LPDISPATCH GetSlideShowTransition();
	LPDISPATCH GetColorScheme();
	void SetColorScheme(LPDISPATCH newValue);
	LPDISPATCH GetBackground();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long GetSlideID();
	long GetPrintSteps();
	void Select();
	void Cut();
	void Copy();
	long GetLayout();
	void SetLayout(long nNewValue);
	LPDISPATCH Duplicate();
	void Delete();
	LPDISPATCH GetTags();
	long GetSlideIndex();
	long GetSlideNumber();
	long GetDisplayMasterShapes();
	void SetDisplayMasterShapes(long nNewValue);
	long GetFollowMasterBackground();
	void SetFollowMasterBackground(long nNewValue);
	LPDISPATCH GetNotesPage();
	LPDISPATCH GetMaster();
	LPDISPATCH GetHyperlinks();
	void Export(LPCTSTR FileName, LPCTSTR FilterName, long ScaleWidth, long ScaleHeight);
	LPDISPATCH Item(const VARIANT& index);
	long GetCount();
	LPDISPATCH GetScripts();
};
/////////////////////////////////////////////////////////////////////////////
// _Master wrapper class

class _Master : public COleDispatchDriver
{
public:
	_Master() {}		// Calls COleDispatchDriver default constructor
	_Master(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Master(const _Master& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetShapes();
	LPDISPATCH GetHeadersFooters();
	LPDISPATCH GetColorScheme();
	void SetColorScheme(LPDISPATCH newValue);
	LPDISPATCH GetBackground();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	void Delete();
	float GetHeight();
	float GetWidth();
	LPDISPATCH GetTextStyles();
	LPDISPATCH GetHyperlinks();
	LPDISPATCH GetScripts();
};
/////////////////////////////////////////////////////////////////////////////
// ColorSchemes wrapper class

class ColorSchemes : public COleDispatchDriver
{
public:
	ColorSchemes() {}		// Calls COleDispatchDriver default constructor
	ColorSchemes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ColorSchemes(const ColorSchemes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long index);
	LPDISPATCH Add(LPDISPATCH Scheme);
};
/////////////////////////////////////////////////////////////////////////////
// ColorScheme wrapper class

class ColorScheme : public COleDispatchDriver
{
public:
	ColorScheme() {}		// Calls COleDispatchDriver default constructor
	ColorScheme(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ColorScheme(const ColorScheme& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Colors(long SchemeColor);
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// RGBColor wrapper class

class RGBColor : public COleDispatchDriver
{
public:
	RGBColor() {}		// Calls COleDispatchDriver default constructor
	RGBColor(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	RGBColor(const RGBColor& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetRgb();
	void SetRgb(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// SlideShowTransition wrapper class

class SlideShowTransition : public COleDispatchDriver
{
public:
	SlideShowTransition() {}		// Calls COleDispatchDriver default constructor
	SlideShowTransition(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	SlideShowTransition(const SlideShowTransition& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetAdvanceOnClick();
	void SetAdvanceOnClick(long nNewValue);
	long GetAdvanceOnTime();
	void SetAdvanceOnTime(long nNewValue);
	float GetAdvanceTime();
	void SetAdvanceTime(float newValue);
	long GetEntryEffect();
	void SetEntryEffect(long nNewValue);
	long GetHidden();
	void SetHidden(long nNewValue);
	long GetLoopSoundUntilNext();
	void SetLoopSoundUntilNext(long nNewValue);
	LPDISPATCH GetSoundEffect();
	long GetSpeed();
	void SetSpeed(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// SoundEffect wrapper class

class SoundEffect : public COleDispatchDriver
{
public:
	SoundEffect() {}		// Calls COleDispatchDriver default constructor
	SoundEffect(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	SoundEffect(const SoundEffect& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long GetType();
	void SetType(long nNewValue);
	void ImportFromFile(LPCTSTR FileName);
	void Play();
};
/////////////////////////////////////////////////////////////////////////////
// SoundFormat wrapper class

class SoundFormat : public COleDispatchDriver
{
public:
	SoundFormat() {}		// Calls COleDispatchDriver default constructor
	SoundFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	SoundFormat(const SoundFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void Play();
	void Import(LPCTSTR FileName);
	long Export(LPCTSTR FileName);
	long GetType();
	CString GetSourceFullName();
};
/////////////////////////////////////////////////////////////////////////////
// HeadersFooters wrapper class

class HeadersFooters : public COleDispatchDriver
{
public:
	HeadersFooters() {}		// Calls COleDispatchDriver default constructor
	HeadersFooters(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	HeadersFooters(const HeadersFooters& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetDateAndTime();
	LPDISPATCH GetSlideNumber();
	LPDISPATCH GetHeader();
	LPDISPATCH GetFooter();
	long GetDisplayOnTitleSlide();
	void SetDisplayOnTitleSlide(long nNewValue);
	void Clear();
};
/////////////////////////////////////////////////////////////////////////////
// Shapes wrapper class

class Shapes : public COleDispatchDriver
{
public:
	Shapes() {}		// Calls COleDispatchDriver default constructor
	Shapes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Shapes(const Shapes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& index);
	LPUNKNOWN Get_NewEnum();
	LPDISPATCH AddCallout(long Type, float Left, float Top, float Width, float Height);
	LPDISPATCH AddConnector(long Type, float BeginX, float BeginY, float EndX, float EndY);
	LPDISPATCH AddCurve(const VARIANT& SafeArrayOfPoints);
	LPDISPATCH AddLabel(long Orientation, float Left, float Top, float Width, float Height);
	LPDISPATCH AddLine(float BeginX, float BeginY, float EndX, float EndY);
	LPDISPATCH AddPicture(LPCTSTR FileName, long LinkToFile, long SaveWithDocument, float Left, float Top, float Width, float Height);
	LPDISPATCH AddPolyline(const VARIANT& SafeArrayOfPoints);
	LPDISPATCH AddShape(long Type, float Left, float Top, float Width, float Height);
	LPDISPATCH AddTextEffect(long PresetTextEffect, LPCTSTR Text, LPCTSTR FontName, float FontSize, long FontBold, long FontItalic, float Left, float Top);
	LPDISPATCH AddTextbox(long Orientation, float Left, float Top, float Width, float Height);
	LPDISPATCH BuildFreeform(long EditingType, float X1, float Y1);
	void SelectAll();
	LPDISPATCH Range(const VARIANT& index);
	long GetHasTitle();
	LPDISPATCH AddTitle();
	LPDISPATCH GetTitle();
	LPDISPATCH GetPlaceholders();
	LPDISPATCH AddOLEObject(float Left, float Top, float Width, float Height, LPCTSTR ClassName, LPCTSTR FileName, long DisplayAsIcon, LPCTSTR IconFileName, long IconIndex, LPCTSTR IconLabel, long Link);
	LPDISPATCH AddComment(float Left, float Top, float Width, float Height);
	LPDISPATCH AddPlaceholder(long Type, float Left, float Top, float Width, float Height);
	LPDISPATCH AddMediaObject(LPCTSTR FileName, float Left, float Top, float Width, float Height);
	LPDISPATCH Paste();
	LPDISPATCH AddTable(long NumRows, long NumColumns, float Left, float Top, float Width, float Height);
};
/////////////////////////////////////////////////////////////////////////////
// Placeholders wrapper class

class Placeholders : public COleDispatchDriver
{
public:
	Placeholders() {}		// Calls COleDispatchDriver default constructor
	Placeholders(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Placeholders(const Placeholders& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long index);
};
/////////////////////////////////////////////////////////////////////////////
// PlaceholderFormat wrapper class

class PlaceholderFormat : public COleDispatchDriver
{
public:
	PlaceholderFormat() {}		// Calls COleDispatchDriver default constructor
	PlaceholderFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PlaceholderFormat(const PlaceholderFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
};
/////////////////////////////////////////////////////////////////////////////
// FreeformBuilder wrapper class

class FreeformBuilder : public COleDispatchDriver
{
public:
	FreeformBuilder() {}		// Calls COleDispatchDriver default constructor
	FreeformBuilder(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FreeformBuilder(const FreeformBuilder& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void AddNodes(long SegmentType, long EditingType, float X1, float Y1, float X2, float Y2, float X3, float Y3);
	LPDISPATCH ConvertToShape();
};
/////////////////////////////////////////////////////////////////////////////
// Shape wrapper class

class Shape : public COleDispatchDriver
{
public:
	Shape() {}		// Calls COleDispatchDriver default constructor
	Shape(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Shape(const Shape& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void Apply();
	void Delete();
	void Flip(long FlipCmd);
	void IncrementLeft(float Increment);
	void IncrementRotation(float Increment);
	void IncrementTop(float Increment);
	void PickUp();
	void RerouteConnections();
	void ScaleHeight(float Factor, long RelativeToOriginalSize, long fScale);
	void ScaleWidth(float Factor, long RelativeToOriginalSize, long fScale);
	void SetShapesDefaultProperties();
	LPDISPATCH Ungroup();
	void ZOrder(long ZOrderCmd);
	LPDISPATCH GetAdjustments();
	long GetAutoShapeType();
	void SetAutoShapeType(long nNewValue);
	long GetBlackWhiteMode();
	void SetBlackWhiteMode(long nNewValue);
	LPDISPATCH GetCallout();
	long GetConnectionSiteCount();
	long GetConnector();
	LPDISPATCH GetConnectorFormat();
	LPDISPATCH GetFill();
	LPDISPATCH GetGroupItems();
	float GetHeight();
	void SetHeight(float newValue);
	long GetHorizontalFlip();
	float GetLeft();
	void SetLeft(float newValue);
	LPDISPATCH GetLine();
	long GetLockAspectRatio();
	void SetLockAspectRatio(long nNewValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	LPDISPATCH GetNodes();
	float GetRotation();
	void SetRotation(float newValue);
	LPDISPATCH GetPictureFormat();
	LPDISPATCH GetShadow();
	LPDISPATCH GetTextEffect();
	LPDISPATCH GetTextFrame();
	LPDISPATCH GetThreeD();
	float GetTop();
	void SetTop(float newValue);
	long GetType();
	long GetVerticalFlip();
	VARIANT GetVertices();
	long GetVisible();
	void SetVisible(long nNewValue);
	float GetWidth();
	void SetWidth(float newValue);
	long GetZOrderPosition();
	LPDISPATCH GetOLEFormat();
	LPDISPATCH GetLinkFormat();
	LPDISPATCH GetPlaceholderFormat();
	LPDISPATCH GetAnimationSettings();
	LPDISPATCH GetActionSettings();
	LPDISPATCH GetTags();
	void Cut();
	void Copy();
	void Select(long Replace);
	LPDISPATCH Duplicate();
	long GetMediaType();
	long GetHasTextFrame();
	LPDISPATCH GetScript();
	CString GetAlternativeText();
	void SetAlternativeText(LPCTSTR lpszNewValue);
	long GetHasTable();
	LPDISPATCH GetTable();
};
/////////////////////////////////////////////////////////////////////////////
// ShapeRange wrapper class

class ShapeRange : public COleDispatchDriver
{
public:
	ShapeRange() {}		// Calls COleDispatchDriver default constructor
	ShapeRange(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ShapeRange(const ShapeRange& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void Apply();
	void Delete();
	void Flip(long FlipCmd);
	void IncrementLeft(float Increment);
	void IncrementRotation(float Increment);
	void IncrementTop(float Increment);
	void PickUp();
	void RerouteConnections();
	void ScaleHeight(float Factor, long RelativeToOriginalSize, long fScale);
	void ScaleWidth(float Factor, long RelativeToOriginalSize, long fScale);
	void SetShapesDefaultProperties();
	LPDISPATCH Ungroup();
	void ZOrder(long ZOrderCmd);
	LPDISPATCH GetAdjustments();
	long GetAutoShapeType();
	void SetAutoShapeType(long nNewValue);
	long GetBlackWhiteMode();
	void SetBlackWhiteMode(long nNewValue);
	LPDISPATCH GetCallout();
	long GetConnectionSiteCount();
	long GetConnector();
	LPDISPATCH GetConnectorFormat();
	LPDISPATCH GetFill();
	LPDISPATCH GetGroupItems();
	float GetHeight();
	void SetHeight(float newValue);
	long GetHorizontalFlip();
	float GetLeft();
	void SetLeft(float newValue);
	LPDISPATCH GetLine();
	long GetLockAspectRatio();
	void SetLockAspectRatio(long nNewValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	LPDISPATCH GetNodes();
	float GetRotation();
	void SetRotation(float newValue);
	LPDISPATCH GetPictureFormat();
	LPDISPATCH GetShadow();
	LPDISPATCH GetTextEffect();
	LPDISPATCH GetTextFrame();
	LPDISPATCH GetThreeD();
	float GetTop();
	void SetTop(float newValue);
	long GetType();
	long GetVerticalFlip();
	VARIANT GetVertices();
	long GetVisible();
	void SetVisible(long nNewValue);
	float GetWidth();
	void SetWidth(float newValue);
	long GetZOrderPosition();
	LPDISPATCH GetOLEFormat();
	LPDISPATCH GetLinkFormat();
	LPDISPATCH GetPlaceholderFormat();
	LPDISPATCH GetAnimationSettings();
	LPDISPATCH GetActionSettings();
	LPDISPATCH GetTags();
	void Cut();
	void Copy();
	void Select(long Replace);
	LPDISPATCH Duplicate();
	long GetMediaType();
	long GetHasTextFrame();
	LPDISPATCH Item(const VARIANT& index);
	long GetCount();
	LPDISPATCH Group();
	LPDISPATCH Regroup();
	void Align(long AlignCmd, long RelativeTo);
	void Distribute(long DistributeCmd, long RelativeTo);
	LPDISPATCH GetScript();
	CString GetAlternativeText();
	void SetAlternativeText(LPCTSTR lpszNewValue);
	long GetHasTable();
	LPDISPATCH GetTable();
};
/////////////////////////////////////////////////////////////////////////////
// GroupShapes wrapper class

class GroupShapes : public COleDispatchDriver
{
public:
	GroupShapes() {}		// Calls COleDispatchDriver default constructor
	GroupShapes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	GroupShapes(const GroupShapes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& index);
	LPUNKNOWN Get_NewEnum();
};
/////////////////////////////////////////////////////////////////////////////
// Adjustments wrapper class

class Adjustments : public COleDispatchDriver
{
public:
	Adjustments() {}		// Calls COleDispatchDriver default constructor
	Adjustments(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Adjustments(const Adjustments& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	float GetItem(long index);
	void SetItem(long index, float newValue);
};
/////////////////////////////////////////////////////////////////////////////
// PictureFormat wrapper class

class PictureFormat : public COleDispatchDriver
{
public:
	PictureFormat() {}		// Calls COleDispatchDriver default constructor
	PictureFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PictureFormat(const PictureFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void IncrementBrightness(float Increment);
	void IncrementContrast(float Increment);
	float GetBrightness();
	void SetBrightness(float newValue);
	long GetColorType();
	void SetColorType(long nNewValue);
	float GetContrast();
	void SetContrast(float newValue);
	float GetCropBottom();
	void SetCropBottom(float newValue);
	float GetCropLeft();
	void SetCropLeft(float newValue);
	float GetCropRight();
	void SetCropRight(float newValue);
	float GetCropTop();
	void SetCropTop(float newValue);
	long GetTransparencyColor();
	void SetTransparencyColor(long nNewValue);
	long GetTransparentBackground();
	void SetTransparentBackground(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// FillFormat wrapper class

class FillFormat : public COleDispatchDriver
{
public:
	FillFormat() {}		// Calls COleDispatchDriver default constructor
	FillFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FillFormat(const FillFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void Background();
	void OneColorGradient(long Style, long Variant, float Degree);
	void Patterned(long Pattern);
	void PresetGradient(long Style, long Variant, long PresetGradientType);
	void PresetTextured(long PresetTexture);
	void Solid();
	void TwoColorGradient(long Style, long Variant);
	void UserPicture(LPCTSTR PictureFile);
	void UserTextured(LPCTSTR TextureFile);
	LPDISPATCH GetBackColor();
	void SetBackColor(LPDISPATCH newValue);
	LPDISPATCH GetForeColor();
	void SetForeColor(LPDISPATCH newValue);
	long GetGradientColorType();
	float GetGradientDegree();
	long GetGradientStyle();
	long GetGradientVariant();
	long GetPattern();
	long GetPresetGradientType();
	long GetPresetTexture();
	CString GetTextureName();
	long GetTextureType();
	float GetTransparency();
	void SetTransparency(float newValue);
	long GetType();
	long GetVisible();
	void SetVisible(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// LineFormat wrapper class

class LineFormat : public COleDispatchDriver
{
public:
	LineFormat() {}		// Calls COleDispatchDriver default constructor
	LineFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	LineFormat(const LineFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetBackColor();
	void SetBackColor(LPDISPATCH newValue);
	long GetBeginArrowheadLength();
	void SetBeginArrowheadLength(long nNewValue);
	long GetBeginArrowheadStyle();
	void SetBeginArrowheadStyle(long nNewValue);
	long GetBeginArrowheadWidth();
	void SetBeginArrowheadWidth(long nNewValue);
	long GetDashStyle();
	void SetDashStyle(long nNewValue);
	long GetEndArrowheadLength();
	void SetEndArrowheadLength(long nNewValue);
	long GetEndArrowheadStyle();
	void SetEndArrowheadStyle(long nNewValue);
	long GetEndArrowheadWidth();
	void SetEndArrowheadWidth(long nNewValue);
	LPDISPATCH GetForeColor();
	void SetForeColor(LPDISPATCH newValue);
	long GetPattern();
	void SetPattern(long nNewValue);
	long GetStyle();
	void SetStyle(long nNewValue);
	float GetTransparency();
	void SetTransparency(float newValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	float GetWeight();
	void SetWeight(float newValue);
};
/////////////////////////////////////////////////////////////////////////////
// ShadowFormat wrapper class

class ShadowFormat : public COleDispatchDriver
{
public:
	ShadowFormat() {}		// Calls COleDispatchDriver default constructor
	ShadowFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ShadowFormat(const ShadowFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void IncrementOffsetX(float Increment);
	void IncrementOffsetY(float Increment);
	LPDISPATCH GetForeColor();
	void SetForeColor(LPDISPATCH newValue);
	long GetObscured();
	void SetObscured(long nNewValue);
	float GetOffsetX();
	void SetOffsetX(float newValue);
	float GetOffsetY();
	void SetOffsetY(float newValue);
	float GetTransparency();
	void SetTransparency(float newValue);
	long GetType();
	void SetType(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// ConnectorFormat wrapper class

class ConnectorFormat : public COleDispatchDriver
{
public:
	ConnectorFormat() {}		// Calls COleDispatchDriver default constructor
	ConnectorFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ConnectorFormat(const ConnectorFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void BeginConnect(LPDISPATCH ConnectedShape, long ConnectionSite);
	void BeginDisconnect();
	void EndConnect(LPDISPATCH ConnectedShape, long ConnectionSite);
	void EndDisconnect();
	long GetBeginConnected();
	LPDISPATCH GetBeginConnectedShape();
	long GetBeginConnectionSite();
	long GetEndConnected();
	LPDISPATCH GetEndConnectedShape();
	long GetEndConnectionSite();
	long GetType();
	void SetType(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// TextEffectFormat wrapper class

class TextEffectFormat : public COleDispatchDriver
{
public:
	TextEffectFormat() {}		// Calls COleDispatchDriver default constructor
	TextEffectFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TextEffectFormat(const TextEffectFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void ToggleVerticalText();
	long GetAlignment();
	void SetAlignment(long nNewValue);
	long GetFontBold();
	void SetFontBold(long nNewValue);
	long GetFontItalic();
	void SetFontItalic(long nNewValue);
	CString GetFontName();
	void SetFontName(LPCTSTR lpszNewValue);
	float GetFontSize();
	void SetFontSize(float newValue);
	long GetKernedPairs();
	void SetKernedPairs(long nNewValue);
	long GetNormalizedHeight();
	void SetNormalizedHeight(long nNewValue);
	long GetPresetShape();
	void SetPresetShape(long nNewValue);
	long GetPresetTextEffect();
	void SetPresetTextEffect(long nNewValue);
	long GetRotatedChars();
	void SetRotatedChars(long nNewValue);
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	float GetTracking();
	void SetTracking(float newValue);
};
/////////////////////////////////////////////////////////////////////////////
// ThreeDFormat wrapper class

class ThreeDFormat : public COleDispatchDriver
{
public:
	ThreeDFormat() {}		// Calls COleDispatchDriver default constructor
	ThreeDFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ThreeDFormat(const ThreeDFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void IncrementRotationX(float Increment);
	void IncrementRotationY(float Increment);
	void ResetRotation();
	void SetThreeDFormat(long PresetThreeDFormat);
	void SetExtrusionDirection(long PresetExtrusionDirection);
	float GetDepth();
	void SetDepth(float newValue);
	LPDISPATCH GetExtrusionColor();
	long GetExtrusionColorType();
	void SetExtrusionColorType(long nNewValue);
	long GetPerspective();
	void SetPerspective(long nNewValue);
	long GetPresetExtrusionDirection();
	long GetPresetLightingDirection();
	void SetPresetLightingDirection(long nNewValue);
	long GetPresetLightingSoftness();
	void SetPresetLightingSoftness(long nNewValue);
	long GetPresetMaterial();
	void SetPresetMaterial(long nNewValue);
	long GetPresetThreeDFormat();
	float GetRotationX();
	void SetRotationX(float newValue);
	float GetRotationY();
	void SetRotationY(float newValue);
	long GetVisible();
	void SetVisible(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// TextFrame wrapper class

class TextFrame : public COleDispatchDriver
{
public:
	TextFrame() {}		// Calls COleDispatchDriver default constructor
	TextFrame(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TextFrame(const TextFrame& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	float GetMarginBottom();
	void SetMarginBottom(float newValue);
	float GetMarginLeft();
	void SetMarginLeft(float newValue);
	float GetMarginRight();
	void SetMarginRight(float newValue);
	float GetMarginTop();
	void SetMarginTop(float newValue);
	long GetOrientation();
	void SetOrientation(long nNewValue);
	long GetHasText();
	LPDISPATCH GetTextRange();
	LPDISPATCH GetRuler();
	long GetHorizontalAnchor();
	void SetHorizontalAnchor(long nNewValue);
	long GetVerticalAnchor();
	void SetVerticalAnchor(long nNewValue);
	long GetAutoSize();
	void SetAutoSize(long nNewValue);
	long GetWordWrap();
	void SetWordWrap(long nNewValue);
	void DeleteText();
};
/////////////////////////////////////////////////////////////////////////////
// CalloutFormat wrapper class

class CalloutFormat : public COleDispatchDriver
{
public:
	CalloutFormat() {}		// Calls COleDispatchDriver default constructor
	CalloutFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CalloutFormat(const CalloutFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void AutomaticLength();
	void CustomDrop(float Drop);
	void CustomLength(float Length);
	void PresetDrop(long DropType);
	long GetAccent();
	void SetAccent(long nNewValue);
	long GetAngle();
	void SetAngle(long nNewValue);
	long GetAutoAttach();
	void SetAutoAttach(long nNewValue);
	long GetAutoLength();
	long GetBorder();
	void SetBorder(long nNewValue);
	float GetDrop();
	long GetDropType();
	float GetGap();
	void SetGap(float newValue);
	float GetLength();
	long GetType();
	void SetType(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// ShapeNodes wrapper class

class ShapeNodes : public COleDispatchDriver
{
public:
	ShapeNodes() {}		// Calls COleDispatchDriver default constructor
	ShapeNodes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ShapeNodes(const ShapeNodes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& index);
	LPUNKNOWN Get_NewEnum();
	void Delete(long index);
	void Insert(long index, long SegmentType, long EditingType, float X1, float Y1, float X2, float Y2, float X3, float Y3);
	void SetEditingType(long index, long EditingType);
	void SetPosition(long index, float X1, float Y1);
	void SetSegmentType(long index, long SegmentType);
};
/////////////////////////////////////////////////////////////////////////////
// ShapeNode wrapper class

class ShapeNode : public COleDispatchDriver
{
public:
	ShapeNode() {}		// Calls COleDispatchDriver default constructor
	ShapeNode(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ShapeNode(const ShapeNode& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetEditingType();
	VARIANT GetPoints();
	long GetSegmentType();
};
/////////////////////////////////////////////////////////////////////////////
// OLEFormat wrapper class

class OLEFormat : public COleDispatchDriver
{
public:
	OLEFormat() {}		// Calls COleDispatchDriver default constructor
	OLEFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	OLEFormat(const OLEFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetObjectVerbs();
	LPDISPATCH GetObject();
	CString GetProgID();
	long GetFollowColors();
	void SetFollowColors(long nNewValue);
	void DoVerb(long index);
	void Activate();
};
/////////////////////////////////////////////////////////////////////////////
// LinkFormat wrapper class

class LinkFormat : public COleDispatchDriver
{
public:
	LinkFormat() {}		// Calls COleDispatchDriver default constructor
	LinkFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	LinkFormat(const LinkFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetSourceFullName();
	void SetSourceFullName(LPCTSTR lpszNewValue);
	long GetAutoUpdate();
	void SetAutoUpdate(long nNewValue);
	void Update();
};
/////////////////////////////////////////////////////////////////////////////
// ObjectVerbs wrapper class

class ObjectVerbs : public COleDispatchDriver
{
public:
	ObjectVerbs() {}		// Calls COleDispatchDriver default constructor
	ObjectVerbs(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ObjectVerbs(const ObjectVerbs& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString Item(long index);
};
/////////////////////////////////////////////////////////////////////////////
// AnimationSettings wrapper class

class AnimationSettings : public COleDispatchDriver
{
public:
	AnimationSettings() {}		// Calls COleDispatchDriver default constructor
	AnimationSettings(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AnimationSettings(const AnimationSettings& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetDimColor();
	LPDISPATCH GetSoundEffect();
	long GetEntryEffect();
	void SetEntryEffect(long nNewValue);
	long GetAfterEffect();
	void SetAfterEffect(long nNewValue);
	long GetAnimationOrder();
	void SetAnimationOrder(long nNewValue);
	long GetAdvanceMode();
	void SetAdvanceMode(long nNewValue);
	float GetAdvanceTime();
	void SetAdvanceTime(float newValue);
	LPDISPATCH GetPlaySettings();
	long GetTextLevelEffect();
	void SetTextLevelEffect(long nNewValue);
	long GetTextUnitEffect();
	void SetTextUnitEffect(long nNewValue);
	long GetAnimate();
	void SetAnimate(long nNewValue);
	long GetAnimateBackground();
	void SetAnimateBackground(long nNewValue);
	long GetAnimateTextInReverse();
	void SetAnimateTextInReverse(long nNewValue);
	long GetChartUnitEffect();
	void SetChartUnitEffect(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// ActionSettings wrapper class

class ActionSettings : public COleDispatchDriver
{
public:
	ActionSettings() {}		// Calls COleDispatchDriver default constructor
	ActionSettings(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ActionSettings(const ActionSettings& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long index);
};
/////////////////////////////////////////////////////////////////////////////
// ActionSetting wrapper class

class ActionSetting : public COleDispatchDriver
{
public:
	ActionSetting() {}		// Calls COleDispatchDriver default constructor
	ActionSetting(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ActionSetting(const ActionSetting& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetAction();
	void SetAction(long nNewValue);
	CString GetActionVerb();
	void SetActionVerb(LPCTSTR lpszNewValue);
	long GetAnimateAction();
	void SetAnimateAction(long nNewValue);
	CString GetRun();
	void SetRun(LPCTSTR lpszNewValue);
	CString GetSlideShowName();
	void SetSlideShowName(LPCTSTR lpszNewValue);
	LPDISPATCH GetHyperlink();
	LPDISPATCH GetSoundEffect();
	long GetShowandReturn();
	void SetShowandReturn(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PlaySettings wrapper class

class PlaySettings : public COleDispatchDriver
{
public:
	PlaySettings() {}		// Calls COleDispatchDriver default constructor
	PlaySettings(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PlaySettings(const PlaySettings& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetActionVerb();
	void SetActionVerb(LPCTSTR lpszNewValue);
	long GetHideWhileNotPlaying();
	void SetHideWhileNotPlaying(long nNewValue);
	long GetLoopUntilStopped();
	void SetLoopUntilStopped(long nNewValue);
	long GetPlayOnEntry();
	void SetPlayOnEntry(long nNewValue);
	long GetRewindMovie();
	void SetRewindMovie(long nNewValue);
	long GetPauseAnimation();
	void SetPauseAnimation(long nNewValue);
	long GetStopAfterSlides();
	void SetStopAfterSlides(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// TextRange wrapper class

class TextRange : public COleDispatchDriver
{
public:
	TextRange() {}		// Calls COleDispatchDriver default constructor
	TextRange(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TextRange(const TextRange& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetActionSettings();
	long GetStart();
	long GetLength();
	float GetBoundLeft();
	float GetBoundTop();
	float GetBoundWidth();
	float GetBoundHeight();
	LPDISPATCH Paragraphs(long Start, long Length);
	LPDISPATCH Sentences(long Start, long Length);
	LPDISPATCH Words(long Start, long Length);
	LPDISPATCH Characters(long Start, long Length);
	LPDISPATCH Lines(long Start, long Length);
	LPDISPATCH Runs(long Start, long Length);
	LPDISPATCH TrimText();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	LPDISPATCH InsertAfter(LPCTSTR NewText);
	LPDISPATCH InsertBefore(LPCTSTR NewText);
	LPDISPATCH InsertDateTime(long DateTimeFormat, long InsertAsField);
	LPDISPATCH InsertSlideNumber();
	LPDISPATCH InsertSymbol(LPCTSTR FontName, long CharNumber, long Unicode);
	LPDISPATCH GetFont();
	LPDISPATCH GetParagraphFormat();
	long GetIndentLevel();
	void SetIndentLevel(long nNewValue);
	void Select();
	void Cut();
	void Copy();
	void Delete();
	LPDISPATCH Paste();
	void ChangeCase(long Type);
	void AddPeriods();
	void RemovePeriods();
	LPDISPATCH Find(LPCTSTR FindWhat, long After, long MatchCase, long WholeWords);
	LPDISPATCH Replace(LPCTSTR FindWhat, LPCTSTR ReplaceWhat, long After, long MatchCase, long WholeWords);
	void RotatedBounds(float* X1, float* Y1, float* X2, float* Y2, float* X3, float* Y3, float* x4, float* y4);
	long GetLanguageID();
	void SetLanguageID(long nNewValue);
	void RtlRun();
	void LtrRun();
};
/////////////////////////////////////////////////////////////////////////////
// Ruler wrapper class

class Ruler : public COleDispatchDriver
{
public:
	Ruler() {}		// Calls COleDispatchDriver default constructor
	Ruler(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Ruler(const Ruler& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetTabStops();
	LPDISPATCH GetLevels();
};
/////////////////////////////////////////////////////////////////////////////
// RulerLevels wrapper class

class RulerLevels : public COleDispatchDriver
{
public:
	RulerLevels() {}		// Calls COleDispatchDriver default constructor
	RulerLevels(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	RulerLevels(const RulerLevels& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long index);
};
/////////////////////////////////////////////////////////////////////////////
// RulerLevel wrapper class

class RulerLevel : public COleDispatchDriver
{
public:
	RulerLevel() {}		// Calls COleDispatchDriver default constructor
	RulerLevel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	RulerLevel(const RulerLevel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	float GetFirstMargin();
	void SetFirstMargin(float newValue);
	float GetLeftMargin();
	void SetLeftMargin(float newValue);
};
/////////////////////////////////////////////////////////////////////////////
// TabStops wrapper class

class TabStops : public COleDispatchDriver
{
public:
	TabStops() {}		// Calls COleDispatchDriver default constructor
	TabStops(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TabStops(const TabStops& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long index);
	float GetDefaultSpacing();
	void SetDefaultSpacing(float newValue);
	LPDISPATCH Add(long Type, float Position);
};
/////////////////////////////////////////////////////////////////////////////
// TabStop wrapper class

class TabStop : public COleDispatchDriver
{
public:
	TabStop() {}		// Calls COleDispatchDriver default constructor
	TabStop(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TabStop(const TabStop& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	void SetType(long nNewValue);
	float GetPosition();
	void SetPosition(float newValue);
	void Clear();
};
/////////////////////////////////////////////////////////////////////////////
// Font wrapper class

class Font : public COleDispatchDriver
{
public:
	Font() {}		// Calls COleDispatchDriver default constructor
	Font(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Font(const Font& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetColor();
	long GetBold();
	void SetBold(long nNewValue);
	long GetItalic();
	void SetItalic(long nNewValue);
	long GetShadow();
	void SetShadow(long nNewValue);
	long GetEmboss();
	void SetEmboss(long nNewValue);
	long GetUnderline();
	void SetUnderline(long nNewValue);
	long GetSubscript();
	void SetSubscript(long nNewValue);
	long GetSuperscript();
	void SetSuperscript(long nNewValue);
	float GetBaselineOffset();
	void SetBaselineOffset(float newValue);
	long GetEmbedded();
	long GetEmbeddable();
	float GetSize();
	void SetSize(float newValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	CString GetNameFarEast();
	void SetNameFarEast(LPCTSTR lpszNewValue);
	CString GetNameAscii();
	void SetNameAscii(LPCTSTR lpszNewValue);
	long GetAutoRotateNumbers();
	void SetAutoRotateNumbers(long nNewValue);
	CString GetNameOther();
	void SetNameOther(LPCTSTR lpszNewValue);
	CString GetNameComplexScript();
	void SetNameComplexScript(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// ParagraphFormat wrapper class

class ParagraphFormat : public COleDispatchDriver
{
public:
	ParagraphFormat() {}		// Calls COleDispatchDriver default constructor
	ParagraphFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ParagraphFormat(const ParagraphFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetAlignment();
	void SetAlignment(long nNewValue);
	LPDISPATCH GetBullet();
	long GetLineRuleBefore();
	void SetLineRuleBefore(long nNewValue);
	long GetLineRuleAfter();
	void SetLineRuleAfter(long nNewValue);
	long GetLineRuleWithin();
	void SetLineRuleWithin(long nNewValue);
	float GetSpaceBefore();
	void SetSpaceBefore(float newValue);
	float GetSpaceAfter();
	void SetSpaceAfter(float newValue);
	float GetSpaceWithin();
	void SetSpaceWithin(float newValue);
	long GetBaseLineAlignment();
	void SetBaseLineAlignment(long nNewValue);
	long GetFarEastLineBreakControl();
	void SetFarEastLineBreakControl(long nNewValue);
	long GetWordWrap();
	void SetWordWrap(long nNewValue);
	long GetHangingPunctuation();
	void SetHangingPunctuation(long nNewValue);
	long GetTextDirection();
	void SetTextDirection(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// BulletFormat wrapper class

class BulletFormat : public COleDispatchDriver
{
public:
	BulletFormat() {}		// Calls COleDispatchDriver default constructor
	BulletFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	BulletFormat(const BulletFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetCharacter();
	void SetCharacter(long nNewValue);
	float GetRelativeSize();
	void SetRelativeSize(float newValue);
	long GetUseTextColor();
	void SetUseTextColor(long nNewValue);
	long GetUseTextFont();
	void SetUseTextFont(long nNewValue);
	LPDISPATCH GetFont();
	long GetType();
	void SetType(long nNewValue);
	long GetStyle();
	void SetStyle(long nNewValue);
	long GetStartValue();
	void SetStartValue(long nNewValue);
	void Picture(LPCTSTR Picture);
	long GetNumber();
};
/////////////////////////////////////////////////////////////////////////////
// TextStyles wrapper class

class TextStyles : public COleDispatchDriver
{
public:
	TextStyles() {}		// Calls COleDispatchDriver default constructor
	TextStyles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TextStyles(const TextStyles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long Type);
};
/////////////////////////////////////////////////////////////////////////////
// TextStyle wrapper class

class TextStyle : public COleDispatchDriver
{
public:
	TextStyle() {}		// Calls COleDispatchDriver default constructor
	TextStyle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TextStyle(const TextStyle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetRuler();
	LPDISPATCH GetTextFrame();
	LPDISPATCH GetLevels();
};
/////////////////////////////////////////////////////////////////////////////
// TextStyleLevels wrapper class

class TextStyleLevels : public COleDispatchDriver
{
public:
	TextStyleLevels() {}		// Calls COleDispatchDriver default constructor
	TextStyleLevels(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TextStyleLevels(const TextStyleLevels& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long Level);
};
/////////////////////////////////////////////////////////////////////////////
// TextStyleLevel wrapper class

class TextStyleLevel : public COleDispatchDriver
{
public:
	TextStyleLevel() {}		// Calls COleDispatchDriver default constructor
	TextStyleLevel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TextStyleLevel(const TextStyleLevel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetParagraphFormat();
	LPDISPATCH GetFont();
};
/////////////////////////////////////////////////////////////////////////////
// HeaderFooter wrapper class

class HeaderFooter : public COleDispatchDriver
{
public:
	HeaderFooter() {}		// Calls COleDispatchDriver default constructor
	HeaderFooter(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	HeaderFooter(const HeaderFooter& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetVisible();
	void SetVisible(long nNewValue);
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	long GetUseFormat();
	void SetUseFormat(long nNewValue);
	long GetFormat();
	void SetFormat(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// _Presentation wrapper class

class _Presentation : public COleDispatchDriver
{
public:
	_Presentation() {}		// Calls COleDispatchDriver default constructor
	_Presentation(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Presentation(const _Presentation& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetSlideMaster();
	LPDISPATCH GetTitleMaster();
	long GetHasTitleMaster();
	LPDISPATCH AddTitleMaster();
	void ApplyTemplate(LPCTSTR FileName);
	CString GetTemplateName();
	LPDISPATCH GetNotesMaster();
	LPDISPATCH GetHandoutMaster();
	LPDISPATCH GetSlides();
	LPDISPATCH GetPageSetup();
	LPDISPATCH GetColorSchemes();
	LPDISPATCH GetExtraColors();
	LPDISPATCH GetSlideShowSettings();
	LPDISPATCH GetFonts();
	LPDISPATCH GetWindows();
	LPDISPATCH GetTags();
	LPDISPATCH GetDefaultShape();
	LPDISPATCH GetBuiltInDocumentProperties();
	LPDISPATCH GetCustomDocumentProperties();
	LPDISPATCH GetVBProject();
	long GetReadOnly();
	CString GetFullName();
	CString GetName();
	CString GetPath();
	long GetSaved();
	void SetSaved(long nNewValue);
	long GetLayoutDirection();
	void SetLayoutDirection(long nNewValue);
	LPDISPATCH NewWindow();
	void FollowHyperlink(LPCTSTR Address, LPCTSTR SubAddress, BOOL NewWindow, BOOL AddHistory, LPCTSTR ExtraInfo, long Method, LPCTSTR HeaderInfo);
	void AddToFavorites();
	LPDISPATCH GetPrintOptions();
	void PrintOut(long From, long To, LPCTSTR PrintToFile, long Copies, long Collate);
	void Save();
	void SaveAs(LPCTSTR FileName, long FileFormat, long EmbedTrueTypeFonts);
	void SaveCopyAs(LPCTSTR FileName, long FileFormat, long EmbedTrueTypeFonts);
	void Export(LPCTSTR Path, LPCTSTR FilterName, long ScaleWidth, long ScaleHeight);
	void Close();
	LPDISPATCH GetContainer();
	long GetDisplayComments();
	void SetDisplayComments(long nNewValue);
	long GetFarEastLineBreakLevel();
	void SetFarEastLineBreakLevel(long nNewValue);
	CString GetNoLineBreakBefore();
	void SetNoLineBreakBefore(LPCTSTR lpszNewValue);
	CString GetNoLineBreakAfter();
	void SetNoLineBreakAfter(LPCTSTR lpszNewValue);
	void UpdateLinks();
	LPDISPATCH GetSlideShowWindow();
	long GetFarEastLineBreakLanguage();
	void SetFarEastLineBreakLanguage(long nNewValue);
	void WebPagePreview();
	long GetDefaultLanguageID();
	void SetDefaultLanguageID(long nNewValue);
	LPDISPATCH GetCommandBars();
	LPDISPATCH GetPublishObjects();
	LPDISPATCH GetWebOptions();
	LPDISPATCH GetHTMLProject();
	void ReloadAs(long cp);
	long GetEnvelopeVisible();
	void SetEnvelopeVisible(long nNewValue);
	long GetVBASigned();
};
/////////////////////////////////////////////////////////////////////////////
// PPDialogs wrapper class

class PPDialogs : public COleDispatchDriver
{
public:
	PPDialogs() {}		// Calls COleDispatchDriver default constructor
	PPDialogs(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPDialogs(const PPDialogs& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH Item(const VARIANT& index);
	LPDISPATCH AddDialog(float Left, float Top, float Width, float Height, long Modal, LPUNKNOWN ParentWindow, long Position, long DisplayHelp);
	LPDISPATCH AddTabDialog(float Left, float Top, float Width, float Height, long Modal, LPUNKNOWN ParentWindow, long Position, long DisplayHelp);
	LPDISPATCH LoadDialog(LPCTSTR resourceDLL, long nResID, long bModal, LPUNKNOWN ParentWindow, long Position);
	LPDISPATCH AddAlert();
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long RunCharacterAlert(LPCTSTR Text, long Type, long icon, LPUNKNOWN ParentWindow);
};
/////////////////////////////////////////////////////////////////////////////
// PPAlert wrapper class

class PPAlert : public COleDispatchDriver
{
public:
	PPAlert() {}		// Calls COleDispatchDriver default constructor
	PPAlert(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPAlert(const PPAlert& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	void Run(LPCTSTR Title, long Type, LPCTSTR Text, LPCTSTR leftBtn, LPCTSTR middleBtn, LPCTSTR rightBtn);
	long GetPressedButton();
	CString GetOnButton();
	void SetOnButton(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPDialog wrapper class

class PPDialog : public COleDispatchDriver
{
public:
	PPDialog() {}		// Calls COleDispatchDriver default constructor
	PPDialog(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPDialog(const PPDialog& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetStyle();
	long GetMode();
	void SetMode(long nNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	long GetHideOnIdle();
	void SetHideOnIdle(long nNewValue);
	CString GetResourceDLL();
	void SetResourceDLL(LPCTSTR lpszNewValue);
	CString GetCaption();
	void SetCaption(LPCTSTR lpszNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	float GetClientLeft();
	float GetClientTop();
	float GetClientWidth();
	float GetClientHeight();
	long GetVisible();
	void SetVisible(long nNewValue);
	LPDISPATCH GetControls();
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	LPDISPATCH GetSheets();
	LPDISPATCH GetTabControl();
	long GetDelayTime();
	void SetDelayTime(long nNewValue);
	long SaveDialog(LPCTSTR FileName);
	void Terminate();
	CString GetOnTerminate();
	void SetOnTerminate(LPCTSTR lpszNewValue);
	CString GetOnIdle();
	void SetOnIdle(LPCTSTR lpszNewValue);
	CString GetOnMouseDown();
	void SetOnMouseDown(LPCTSTR lpszNewValue);
	CString GetOnMouseUp();
	void SetOnMouseUp(LPCTSTR lpszNewValue);
	CString GetOnKeyPressed();
	void SetOnKeyPressed(LPCTSTR lpszNewValue);
	CString GetOnTimer();
	void SetOnTimer(LPCTSTR lpszNewValue);
	CString GetOnActivate();
	void SetOnActivate(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPTabSheet wrapper class

class PPTabSheet : public COleDispatchDriver
{
public:
	PPTabSheet() {}		// Calls COleDispatchDriver default constructor
	PPTabSheet(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPTabSheet(const PPTabSheet& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	void Select();
	float GetClientLeft();
	float GetClientTop();
	float GetClientWidth();
	float GetClientHeight();
	LPDISPATCH GetControls();
	LPDISPATCH GetTags();
	CString GetOnActivate();
	void SetOnActivate(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPControls wrapper class

class PPControls : public COleDispatchDriver
{
public:
	PPControls() {}		// Calls COleDispatchDriver default constructor
	PPControls(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPControls(const PPControls& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH Item(const VARIANT& index);
	LPDISPATCH AddPushButton(float Left, float Top, float Width, float Height);
	LPDISPATCH AddToggleButton(float Left, float Top, float Width, float Height);
	LPDISPATCH AddBitmapButton(float Left, float Top, float Width, float Height);
	LPDISPATCH AddListBox(float Left, float Top, float Width, float Height);
	LPDISPATCH AddCheckBox(float Left, float Top, float Width, float Height);
	LPDISPATCH AddRadioCluster(float Left, float Top, float Width, float Height);
	LPDISPATCH AddStaticText(float Left, float Top, float Width, float Height);
	LPDISPATCH AddEditText(float Left, float Top, float Width, float Height, const VARIANT& VerticalScrollBar);
	LPDISPATCH AddIcon(float Left, float Top, float Width, float Height);
	LPDISPATCH AddBitmap(float Left, float Top, float Width, float Height);
	LPDISPATCH AddSpinner(float Left, float Top, float Width, float Height);
	LPDISPATCH AddScrollBar(long Style, float Left, float Top, float Width, float Height);
	LPDISPATCH AddGroupBox(float Left, float Top, float Width, float Height);
	LPDISPATCH AddDropDown(float Left, float Top, float Width, float Height);
	LPDISPATCH AddDropDownEdit(float Left, float Top, float Width, float Height);
	LPDISPATCH AddMiniature(float Left, float Top, float Width, float Height);
	LPDISPATCH AddFrame(float Left, float Top, float Width, float Height);
	long GetVisible();
	void SetVisible(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPTabSheets wrapper class

class PPTabSheets : public COleDispatchDriver
{
public:
	PPTabSheets() {}		// Calls COleDispatchDriver default constructor
	PPTabSheets(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPTabSheets(const PPTabSheets& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH Item(const VARIANT& index);
	LPDISPATCH Add(LPCTSTR Name);
	LPDISPATCH GetActiveSheet();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPControl wrapper class

class PPControl : public COleDispatchDriver
{
public:
	PPControl() {}		// Calls COleDispatchDriver default constructor
	PPControl(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPControl(const PPControl& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetFocus();
	void SetFocus(long nNewValue);
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	CString GetOnSetFocus();
	void SetOnSetFocus(LPCTSTR lpszNewValue);
	CString GetOnKillFocus();
	void SetOnKillFocus(LPCTSTR lpszNewValue);
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPPushButton wrapper class

class PPPushButton : public COleDispatchDriver
{
public:
	PPPushButton() {}		// Calls COleDispatchDriver default constructor
	PPPushButton(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPPushButton(const PPPushButton& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetFocus();
	void SetFocus(long nNewValue);
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	CString GetOnSetFocus();
	void SetOnSetFocus(LPCTSTR lpszNewValue);
	CString GetOnKillFocus();
	void SetOnKillFocus(LPCTSTR lpszNewValue);
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	void Click();
	long GetIsDefault();
	void SetIsDefault(long nNewValue);
	long GetIsEscape();
	void SetIsEscape(long nNewValue);
	CString GetOnPressed();
	void SetOnPressed(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPToggleButton wrapper class

class PPToggleButton : public COleDispatchDriver
{
public:
	PPToggleButton() {}		// Calls COleDispatchDriver default constructor
	PPToggleButton(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPToggleButton(const PPToggleButton& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetFocus();
	void SetFocus(long nNewValue);
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	CString GetOnSetFocus();
	void SetOnSetFocus(LPCTSTR lpszNewValue);
	CString GetOnKillFocus();
	void SetOnKillFocus(LPCTSTR lpszNewValue);
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long GetState();
	void SetState(long nNewValue);
	long GetResourceID();
	void SetResourceID(long nNewValue);
	void Click();
	CString GetOnClick();
	void SetOnClick(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPBitmapButton wrapper class

class PPBitmapButton : public COleDispatchDriver
{
public:
	PPBitmapButton() {}		// Calls COleDispatchDriver default constructor
	PPBitmapButton(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPBitmapButton(const PPBitmapButton& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetFocus();
	void SetFocus(long nNewValue);
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	CString GetOnSetFocus();
	void SetOnSetFocus(LPCTSTR lpszNewValue);
	CString GetOnKillFocus();
	void SetOnKillFocus(LPCTSTR lpszNewValue);
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	void Click();
	long GetResourceID();
	void SetResourceID(long nNewValue);
	CString GetOnPressed();
	void SetOnPressed(LPCTSTR lpszNewValue);
	long GetIsDefault();
	void SetIsDefault(long nNewValue);
	long GetIsEscape();
	void SetIsEscape(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPListBox wrapper class

class PPListBox : public COleDispatchDriver
{
public:
	PPListBox() {}		// Calls COleDispatchDriver default constructor
	PPListBox(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPListBox(const PPListBox& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetFocus();
	void SetFocus(long nNewValue);
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	CString GetOnSetFocus();
	void SetOnSetFocus(LPCTSTR lpszNewValue);
	CString GetOnKillFocus();
	void SetOnKillFocus(LPCTSTR lpszNewValue);
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	LPDISPATCH GetStrings();
	long GetSelectionStyle();
	void SetSelectionStyle(long nNewValue);
	void SetTabStops(const VARIANT& safeArrayTabStops);
	long GetFocusItem();
	void SetFocusItem(long nNewValue);
	long GetTopItem();
	CString GetOnSelectionChange();
	void SetOnSelectionChange(LPCTSTR lpszNewValue);
	CString GetOnDoubleClick();
	void SetOnDoubleClick(LPCTSTR lpszNewValue);
	long GetIsSelected(long index);
	void SetIsSelected(long index, long nNewValue);
	void Abbreviate(long Style);
	long GetIsAbbreviated();
};
/////////////////////////////////////////////////////////////////////////////
// PPStrings wrapper class

class PPStrings : public COleDispatchDriver
{
public:
	PPStrings() {}		// Calls COleDispatchDriver default constructor
	PPStrings(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPStrings(const PPStrings& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	CString Item(long index);
	CString Add(LPCTSTR String);
	void Insert(LPCTSTR String, long Position);
	void Delete(long index);
};
/////////////////////////////////////////////////////////////////////////////
// PPCheckBox wrapper class

class PPCheckBox : public COleDispatchDriver
{
public:
	PPCheckBox() {}		// Calls COleDispatchDriver default constructor
	PPCheckBox(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPCheckBox(const PPCheckBox& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetFocus();
	void SetFocus(long nNewValue);
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	CString GetOnSetFocus();
	void SetOnSetFocus(LPCTSTR lpszNewValue);
	CString GetOnKillFocus();
	void SetOnKillFocus(LPCTSTR lpszNewValue);
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long GetState();
	void SetState(long nNewValue);
	void Click();
	CString GetOnClick();
	void SetOnClick(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPRadioCluster wrapper class

class PPRadioCluster : public COleDispatchDriver
{
public:
	PPRadioCluster() {}		// Calls COleDispatchDriver default constructor
	PPRadioCluster(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPRadioCluster(const PPRadioCluster& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetFocus();
	void SetFocus(long nNewValue);
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	CString GetOnSetFocus();
	void SetOnSetFocus(LPCTSTR lpszNewValue);
	CString GetOnKillFocus();
	void SetOnKillFocus(LPCTSTR lpszNewValue);
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	LPDISPATCH Item(const VARIANT& index);
	LPDISPATCH Add(float Left, float Top, float Width, float Height);
	long GetCount();
	LPDISPATCH GetSelected();
	CString GetOnClick();
	void SetOnClick(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPStaticText wrapper class

class PPStaticText : public COleDispatchDriver
{
public:
	PPStaticText() {}		// Calls COleDispatchDriver default constructor
	PPStaticText(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPStaticText(const PPStaticText& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetFocus();
	void SetFocus(long nNewValue);
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	CString GetOnSetFocus();
	void SetOnSetFocus(LPCTSTR lpszNewValue);
	CString GetOnKillFocus();
	void SetOnKillFocus(LPCTSTR lpszNewValue);
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long GetUseForegroundColor();
	void SetUseForegroundColor(long nNewValue);
	long GetUseBackgroundColor();
	void SetUseBackgroundColor(long nNewValue);
	long GetForegroundColor();
	void SetForegroundColor(long nNewValue);
	long GetBackgroundColor();
	void SetBackgroundColor(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPEditText wrapper class

class PPEditText : public COleDispatchDriver
{
public:
	PPEditText() {}		// Calls COleDispatchDriver default constructor
	PPEditText(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPEditText(const PPEditText& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetFocus();
	void SetFocus(long nNewValue);
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	CString GetOnSetFocus();
	void SetOnSetFocus(LPCTSTR lpszNewValue);
	CString GetOnKillFocus();
	void SetOnKillFocus(LPCTSTR lpszNewValue);
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long GetMultiLine();
	void SetMultiLine(long nNewValue);
	long GetVerticalScrollBar();
	void SetVerticalScrollBar(long nNewValue);
	long GetWordWrap();
	void SetWordWrap(long nNewValue);
	long GetReadOnly();
	void SetReadOnly(long nNewValue);
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	long GetMaxLength();
	void SetMaxLength(long nNewValue);
	CString GetOnAChange();
	void SetOnAChange(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPIcon wrapper class

class PPIcon : public COleDispatchDriver
{
public:
	PPIcon() {}		// Calls COleDispatchDriver default constructor
	PPIcon(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPIcon(const PPIcon& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetFocus();
	void SetFocus(long nNewValue);
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	CString GetOnSetFocus();
	void SetOnSetFocus(LPCTSTR lpszNewValue);
	CString GetOnKillFocus();
	void SetOnKillFocus(LPCTSTR lpszNewValue);
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long GetResourceID();
	void SetResourceID(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPBitmap wrapper class

class PPBitmap : public COleDispatchDriver
{
public:
	PPBitmap() {}		// Calls COleDispatchDriver default constructor
	PPBitmap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPBitmap(const PPBitmap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetFocus();
	void SetFocus(long nNewValue);
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	CString GetOnSetFocus();
	void SetOnSetFocus(LPCTSTR lpszNewValue);
	CString GetOnKillFocus();
	void SetOnKillFocus(LPCTSTR lpszNewValue);
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long GetResourceID();
	void SetResourceID(long nNewValue);
	CString GetOnClick();
	void SetOnClick(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPSpinner wrapper class

class PPSpinner : public COleDispatchDriver
{
public:
	PPSpinner() {}		// Calls COleDispatchDriver default constructor
	PPSpinner(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPSpinner(const PPSpinner& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetFocus();
	void SetFocus(long nNewValue);
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	CString GetOnSetFocus();
	void SetOnSetFocus(LPCTSTR lpszNewValue);
	CString GetOnKillFocus();
	void SetOnKillFocus(LPCTSTR lpszNewValue);
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long GetMinimum();
	void SetMinimum(long nNewValue);
	long GetMaximum();
	void SetMaximum(long nNewValue);
	long GetIncrement();
	void SetIncrement(long nNewValue);
	long GetPageChange();
	void SetPageChange(long nNewValue);
	long GetCurrentValue();
	void SetCurrentValue(long nNewValue);
	CString GetOnAChange();
	void SetOnAChange(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPScrollBar wrapper class

class PPScrollBar : public COleDispatchDriver
{
public:
	PPScrollBar() {}		// Calls COleDispatchDriver default constructor
	PPScrollBar(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPScrollBar(const PPScrollBar& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetFocus();
	void SetFocus(long nNewValue);
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	CString GetOnSetFocus();
	void SetOnSetFocus(LPCTSTR lpszNewValue);
	CString GetOnKillFocus();
	void SetOnKillFocus(LPCTSTR lpszNewValue);
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long GetMinimum();
	void SetMinimum(long nNewValue);
	long GetMaximum();
	void SetMaximum(long nNewValue);
	long GetIncrement();
	void SetIncrement(long nNewValue);
	long GetPageChange();
	void SetPageChange(long nNewValue);
	long GetCurrentValue();
	void SetCurrentValue(long nNewValue);
	CString GetOnScroll();
	void SetOnScroll(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPGroupBox wrapper class

class PPGroupBox : public COleDispatchDriver
{
public:
	PPGroupBox() {}		// Calls COleDispatchDriver default constructor
	PPGroupBox(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPGroupBox(const PPGroupBox& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetFocus();
	void SetFocus(long nNewValue);
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	CString GetOnSetFocus();
	void SetOnSetFocus(LPCTSTR lpszNewValue);
	CString GetOnKillFocus();
	void SetOnKillFocus(LPCTSTR lpszNewValue);
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPFrame wrapper class

class PPFrame : public COleDispatchDriver
{
public:
	PPFrame() {}		// Calls COleDispatchDriver default constructor
	PPFrame(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPFrame(const PPFrame& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetFocus();
	void SetFocus(long nNewValue);
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	CString GetOnSetFocus();
	void SetOnSetFocus(LPCTSTR lpszNewValue);
	CString GetOnKillFocus();
	void SetOnKillFocus(LPCTSTR lpszNewValue);
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPTabControl wrapper class

class PPTabControl : public COleDispatchDriver
{
public:
	PPTabControl() {}		// Calls COleDispatchDriver default constructor
	PPTabControl(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPTabControl(const PPTabControl& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetFocus();
	void SetFocus(long nNewValue);
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	CString GetOnSetFocus();
	void SetOnSetFocus(LPCTSTR lpszNewValue);
	CString GetOnKillFocus();
	void SetOnKillFocus(LPCTSTR lpszNewValue);
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPDropDown wrapper class

class PPDropDown : public COleDispatchDriver
{
public:
	PPDropDown() {}		// Calls COleDispatchDriver default constructor
	PPDropDown(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPDropDown(const PPDropDown& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetFocus();
	void SetFocus(long nNewValue);
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	CString GetOnSetFocus();
	void SetOnSetFocus(LPCTSTR lpszNewValue);
	CString GetOnKillFocus();
	void SetOnKillFocus(LPCTSTR lpszNewValue);
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	LPDISPATCH GetStrings();
	long GetFocusItem();
	void SetFocusItem(long nNewValue);
	CString GetOnSelectionChange();
	void SetOnSelectionChange(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPDropDownEdit wrapper class

class PPDropDownEdit : public COleDispatchDriver
{
public:
	PPDropDownEdit() {}		// Calls COleDispatchDriver default constructor
	PPDropDownEdit(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPDropDownEdit(const PPDropDownEdit& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetFocus();
	void SetFocus(long nNewValue);
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	CString GetOnSetFocus();
	void SetOnSetFocus(LPCTSTR lpszNewValue);
	CString GetOnKillFocus();
	void SetOnKillFocus(LPCTSTR lpszNewValue);
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	LPDISPATCH GetStrings();
	long GetFocusItem();
	void SetFocusItem(long nNewValue);
	CString GetOnSelectionChange();
	void SetOnSelectionChange(LPCTSTR lpszNewValue);
	CString GetOnEdit();
	void SetOnEdit(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPSlideMiniature wrapper class

class PPSlideMiniature : public COleDispatchDriver
{
public:
	PPSlideMiniature() {}		// Calls COleDispatchDriver default constructor
	PPSlideMiniature(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPSlideMiniature(const PPSlideMiniature& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetFocus();
	void SetFocus(long nNewValue);
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	CString GetOnSetFocus();
	void SetOnSetFocus(LPCTSTR lpszNewValue);
	CString GetOnKillFocus();
	void SetOnKillFocus(LPCTSTR lpszNewValue);
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	void SetImage(LPDISPATCH Slide);
	long GetSelected();
	void SetSelected(long nNewValue);
	CString GetOnClick();
	void SetOnClick(LPCTSTR lpszNewValue);
	CString GetOnDoubleClick();
	void SetOnDoubleClick(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// PPRadioButton wrapper class

class PPRadioButton : public COleDispatchDriver
{
public:
	PPRadioButton() {}		// Calls COleDispatchDriver default constructor
	PPRadioButton(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PPRadioButton(const PPRadioButton& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	long GetFocus();
	void SetFocus(long nNewValue);
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	long GetHelpId();
	void SetHelpId(long nNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	CString GetOnSetFocus();
	void SetOnSetFocus(LPCTSTR lpszNewValue);
	CString GetOnKillFocus();
	void SetOnKillFocus(LPCTSTR lpszNewValue);
	LPDISPATCH GetTags();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long GetState();
	void SetState(long nNewValue);
	void Click();
	void DoubleClick();
	CString GetOnClick();
	void SetOnClick(LPCTSTR lpszNewValue);
	CString GetOnDoubleClick();
	void SetOnDoubleClick(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// Tags wrapper class

class Tags : public COleDispatchDriver
{
public:
	Tags() {}		// Calls COleDispatchDriver default constructor
	Tags(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Tags(const Tags& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString Item(LPCTSTR Name);
	void Add(LPCTSTR Name, LPCTSTR Value);
	void Delete(LPCTSTR Name);
	CString Name(long index);
	CString Value(long index);
};
/////////////////////////////////////////////////////////////////////////////
// FileDialogFileList wrapper class

class FileDialogFileList : public COleDispatchDriver
{
public:
	FileDialogFileList() {}		// Calls COleDispatchDriver default constructor
	FileDialogFileList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FileDialogFileList(const FileDialogFileList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString Item(long index);
	CString DisplayName(long index);
};
/////////////////////////////////////////////////////////////////////////////
// FileDialogExtension wrapper class

class FileDialogExtension : public COleDispatchDriver
{
public:
	FileDialogExtension() {}		// Calls COleDispatchDriver default constructor
	FileDialogExtension(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FileDialogExtension(const FileDialogExtension& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetExtensions();
	void SetExtensions(LPCTSTR lpszNewValue);
	CString GetDescription();
	void SetDescription(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// FileDialogExtensionList wrapper class

class FileDialogExtensionList : public COleDispatchDriver
{
public:
	FileDialogExtensionList() {}		// Calls COleDispatchDriver default constructor
	FileDialogExtensionList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FileDialogExtensionList(const FileDialogExtensionList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long index);
	LPDISPATCH Add(LPCTSTR Extension, LPCTSTR Description);
};
/////////////////////////////////////////////////////////////////////////////
// FileDialog wrapper class

class FileDialog : public COleDispatchDriver
{
public:
	FileDialog() {}		// Calls COleDispatchDriver default constructor
	FileDialog(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FileDialog(const FileDialog& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetExtensions();
	CString GetDefaultDirectoryRegKey();
	void SetDefaultDirectoryRegKey(LPCTSTR lpszNewValue);
	CString GetDialogTitle();
	void SetDialogTitle(LPCTSTR lpszNewValue);
	CString GetActionButtonName();
	void SetActionButtonName(LPCTSTR lpszNewValue);
	long GetIsMultiSelect();
	void SetIsMultiSelect(long nNewValue);
	long GetIsPrintEnabled();
	void SetIsPrintEnabled(long nNewValue);
	long GetIsReadOnlyEnabled();
	void SetIsReadOnlyEnabled(long nNewValue);
	long GetDirectoriesOnly();
	void SetDirectoriesOnly(long nNewValue);
	long GetInitialView();
	void SetInitialView(long nNewValue);
	void Launch(LPUNKNOWN pUnk);
	CString GetOnAction();
	void SetOnAction(LPCTSTR lpszNewValue);
	LPDISPATCH GetFiles();
	long GetUseODMADlgs();
	void SetUseODMADlgs(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// OCXExtender wrapper class

class OCXExtender : public COleDispatchDriver
{
public:
	OCXExtender() {}		// Calls COleDispatchDriver default constructor
	OCXExtender(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	OCXExtender(const OCXExtender& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	long GetZOrderPosition();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// Table wrapper class

class Table : public COleDispatchDriver
{
public:
	Table() {}		// Calls COleDispatchDriver default constructor
	Table(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Table(const Table& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetColumns();
	LPDISPATCH GetRows();
	LPDISPATCH Cell(long Row, long Column);
	long GetTableDirection();
	void SetTableDirection(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// Columns wrapper class

class Columns : public COleDispatchDriver
{
public:
	Columns() {}		// Calls COleDispatchDriver default constructor
	Columns(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Columns(const Columns& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long index);
	LPDISPATCH Add(long BeforeColumn);
};
/////////////////////////////////////////////////////////////////////////////
// Column wrapper class

class Column : public COleDispatchDriver
{
public:
	Column() {}		// Calls COleDispatchDriver default constructor
	Column(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Column(const Column& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetCells();
	void Select();
	void Delete();
	float GetWidth();
	void SetWidth(float newValue);
};
/////////////////////////////////////////////////////////////////////////////
// Rows wrapper class

class Rows : public COleDispatchDriver
{
public:
	Rows() {}		// Calls COleDispatchDriver default constructor
	Rows(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Rows(const Rows& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long index);
	LPDISPATCH Add(long BeforeRow);
};
/////////////////////////////////////////////////////////////////////////////
// Row wrapper class

class Row : public COleDispatchDriver
{
public:
	Row() {}		// Calls COleDispatchDriver default constructor
	Row(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Row(const Row& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetCells();
	void Select();
	void Delete();
	float GetHeight();
	void SetHeight(float newValue);
};
/////////////////////////////////////////////////////////////////////////////
// CellRange wrapper class

class CellRange : public COleDispatchDriver
{
public:
	CellRange() {}		// Calls COleDispatchDriver default constructor
	CellRange(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CellRange(const CellRange& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long index);
	LPDISPATCH GetBorders();
};
/////////////////////////////////////////////////////////////////////////////
// Cell wrapper class

class Cell : public COleDispatchDriver
{
public:
	Cell() {}		// Calls COleDispatchDriver default constructor
	Cell(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Cell(const Cell& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetShape();
	LPDISPATCH GetBorders();
	void Merge(LPDISPATCH MergeTo);
	void Split(long NumRows, long NumColumns);
	void Select();
	BOOL GetSelected();
};
/////////////////////////////////////////////////////////////////////////////
// Borders wrapper class

class Borders : public COleDispatchDriver
{
public:
	Borders() {}		// Calls COleDispatchDriver default constructor
	Borders(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Borders(const Borders& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long BorderType);
};
/////////////////////////////////////////////////////////////////////////////
// Panes wrapper class

class Panes : public COleDispatchDriver
{
public:
	Panes() {}		// Calls COleDispatchDriver default constructor
	Panes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Panes(const Panes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH Item(long index);
	LPDISPATCH GetParent();
};
/////////////////////////////////////////////////////////////////////////////
// Pane wrapper class

class Pane : public COleDispatchDriver
{
public:
	Pane() {}		// Calls COleDispatchDriver default constructor
	Pane(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Pane(const Pane& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParent();
	void Activate();
	long GetActive();
	LPDISPATCH GetApplication();
	long GetViewType();
};
/////////////////////////////////////////////////////////////////////////////
// DefaultWebOptions wrapper class

class DefaultWebOptions : public COleDispatchDriver
{
public:
	DefaultWebOptions() {}		// Calls COleDispatchDriver default constructor
	DefaultWebOptions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DefaultWebOptions(const DefaultWebOptions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetIncludeNavigation();
	void SetIncludeNavigation(long nNewValue);
	long GetFrameColors();
	void SetFrameColors(long nNewValue);
	long GetResizeGraphics();
	void SetResizeGraphics(long nNewValue);
	long GetShowSlideAnimation();
	void SetShowSlideAnimation(long nNewValue);
	long GetOrganizeInFolder();
	void SetOrganizeInFolder(long nNewValue);
	long GetUseLongFileNames();
	void SetUseLongFileNames(long nNewValue);
	long GetRelyOnVML();
	void SetRelyOnVML(long nNewValue);
	long GetAllowPNG();
	void SetAllowPNG(long nNewValue);
	long GetScreenSize();
	void SetScreenSize(long nNewValue);
	long GetEncoding();
	void SetEncoding(long nNewValue);
	long GetUpdateLinksOnSave();
	void SetUpdateLinksOnSave(long nNewValue);
	long GetCheckIfOfficeIsHTMLEditor();
	void SetCheckIfOfficeIsHTMLEditor(long nNewValue);
	long GetAlwaysSaveInDefaultEncoding();
	void SetAlwaysSaveInDefaultEncoding(long nNewValue);
	LPDISPATCH GetFonts();
	CString GetFolderSuffix();
};
/////////////////////////////////////////////////////////////////////////////
// WebOptions wrapper class

class WebOptions : public COleDispatchDriver
{
public:
	WebOptions() {}		// Calls COleDispatchDriver default constructor
	WebOptions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	WebOptions(const WebOptions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetIncludeNavigation();
	void SetIncludeNavigation(long nNewValue);
	long GetFrameColors();
	void SetFrameColors(long nNewValue);
	long GetResizeGraphics();
	void SetResizeGraphics(long nNewValue);
	long GetShowSlideAnimation();
	void SetShowSlideAnimation(long nNewValue);
	long GetOrganizeInFolder();
	void SetOrganizeInFolder(long nNewValue);
	long GetUseLongFileNames();
	void SetUseLongFileNames(long nNewValue);
	long GetRelyOnVML();
	void SetRelyOnVML(long nNewValue);
	long GetAllowPNG();
	void SetAllowPNG(long nNewValue);
	long GetScreenSize();
	void SetScreenSize(long nNewValue);
	long GetEncoding();
	void SetEncoding(long nNewValue);
	CString GetFolderSuffix();
	void UseDefaultFolderSuffix();
};
/////////////////////////////////////////////////////////////////////////////
// PublishObjects wrapper class

class PublishObjects : public COleDispatchDriver
{
public:
	PublishObjects() {}		// Calls COleDispatchDriver default constructor
	PublishObjects(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PublishObjects(const PublishObjects& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long index);
};
/////////////////////////////////////////////////////////////////////////////
// PublishObject wrapper class

class PublishObject : public COleDispatchDriver
{
public:
	PublishObject() {}		// Calls COleDispatchDriver default constructor
	PublishObject(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PublishObject(const PublishObject& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetHTMLVersion();
	void SetHTMLVersion(long nNewValue);
	long GetSourceType();
	void SetSourceType(long nNewValue);
	long GetRangeStart();
	void SetRangeStart(long nNewValue);
	long GetRangeEnd();
	void SetRangeEnd(long nNewValue);
	CString GetSlideShowName();
	void SetSlideShowName(LPCTSTR lpszNewValue);
	long GetSpeakerNotes();
	void SetSpeakerNotes(long nNewValue);
	CString GetFileName();
	void SetFileName(LPCTSTR lpszNewValue);
	void Publish();
};
/////////////////////////////////////////////////////////////////////////////
// Marker wrapper class

class Marker : public COleDispatchDriver
{
public:
	Marker() {}		// Calls COleDispatchDriver default constructor
	Marker(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Marker(const Marker& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetMarkerType();
	void SetMarkerType(long nNewValue);
	long GetTime();
};
