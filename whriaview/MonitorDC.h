#pragma once

class CMonitor;

// CMonitorDC command target

class CMonitorDC : public CDC
{
public:
	CMonitorDC( CMonitor* pMonitor );
	virtual ~CMonitorDC();
};


