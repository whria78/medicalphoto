// MonitorDC.cpp : implementation file
//

#include "stdafx.h"
#include "MonitorDC.h"
#include "MultiMonitor.h"

// CMonitorDC

CMonitorDC::CMonitorDC( CMonitor* pMonitor )
{
	ASSERT( pMonitor );
	ASSERT( pMonitor->IsMonitor() );

	VERIFY( Attach( pMonitor->CreateDC() ) );
}

CMonitorDC::~CMonitorDC()
{
	VERIFY( DeleteDC() );
}


// CMonitorDC member functions
