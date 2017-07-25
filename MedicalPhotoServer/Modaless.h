#pragma once

class CWnd;

template <class ModalDialog>class NonModalDialog
: public ModalDialog
{
public :
 NonModalDialog( CWnd *pParent )
 : ModalDialog( pParent ) { }

 virtual int DoModal();
 virtual void EndModalLoop( int );
protected:
 int m_nStillActive;
};

template <class ModalDialog>
inline int NonModalDialog<ModalDialog>::DoModal()
{
 MSG			l_objMessage;
 CWinThread*	l_pThread = AfxGetThread();

 ASSERT_VALID( l_pThread );

 Create( ModalDialog::IDD );
 ShowWindow( SW_SHOW );
 m_nStillActive = 1;

 //--------- Thanks to Microsoft. This block
 //--------- is from CWinThread::Run
 // from Thrdcore.cpp, with appropriate changes.
 ASSERT_VALID(this);
 // for tracking the idle time state
 BOOL l_nIdle = TRUE;
 LONG l_nIdleCount = 0;

 // acquire and dispatch messages until
 // a WM_QUIT message is received,
 // or the dialog box is closed.
 for (;;)
 {
  // phase1: check to see if we can do idle work
  while( l_nIdle && !::PeekMessage( &l_objMessage,
                                    NULL,
                                    NULL,
                                    NULL,
                                    PM_NOREMOVE ) )
  {
   // call OnIdle while in bIdle state
   if( !l_pThread->OnIdle( l_nIdleCount++ ) )
    l_nIdle = FALSE; // assume "no idle" state
  }

  // phase2: pump messages while available
  do
  {
   // Relent control back to Windows if the dialog
   // box has closed.
   if( !m_nStillActive )
    return m_nModalResult;

   if( l_objMessage.message == WM_SYSCOMMAND
   && l_objMessage.wParam == SC_CLOSE )
    OnCancel();	// Close the dialog box first.

   // pump message, but quit on WM_QUIT
   if( !l_pThread->PumpMessage() )
    return l_pThread->ExitInstance();

   // reset "no idle" state after pumping
   // "normal" message
   if( l_pThread->IsIdleMessage( &l_objMessage ) )
    l_nIdle = TRUE, l_nIdleCount = 0;
  } while( ::PeekMessage( &l_objMessage,
                          NULL,
                          NULL,
                          NULL,
                          PM_NOREMOVE ) );
 }
 ASSERT(FALSE);  // not reachable
 //---------------------
}

template <class ModalDialog>inline void
NonModalDialog<ModalDialog>::EndModalLoop(int p_nResult)
{
 m_nStillActive = 0;
 ModalDialog::EndModalLoop( p_nResult );
}