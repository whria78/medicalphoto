#pragma once

#include "../share/cmycout.h"
#include "../share/config.h"

class SendMsgCout
	:
	public CMyCout
{
public:
	SendMsgCout(HWND hwnd,_tostream& os)
		: CMyCout(os)
		, m_hwnd(hwnd)
	{
	}

	void WriteString(const tstring& str)
	{
#ifdef _WIN32
		HWND hwnd = ::FindWindow(_T("MedicalPhotoServer"), NULL);
		if (hwnd!=NULL)
		{
			log_struct log_struct_;
			log_struct_.iFlag=iSetFlag;
			log_struct_.stDetail=MCodeChanger::_CCU(str);

			std::ostringstream archive_stream_out;
			boost::archive::text_oarchive archive_out(archive_stream_out);

//			archive_out << log_struct_;
			serialout(archive_out,log_struct_);

			std::string steamout_=archive_stream_out.str();
			COPYDATASTRUCT cds;
			cds.dwData=WM_COPYDATA_LOG;
			cds.cbData=steamout_.length();
			cds.lpData=(void*)steamout_.c_str();

			::SendMessage(hwnd,WM_COPYDATA,(WPARAM)m_hwnd,(LPARAM)&cds);

/*
			std::ostringstream archive_stream_out;
			boost::archive::text_oarchive archive_out(archive_stream_out);

			archive_out 
				<< MCodeChanger::_CCU(str);

			std::string steamout_=archive_stream_out.str();
			COPYDATASTRUCT cds;
			cds.dwData=WM_COPYDATA_LOG;
			cds.cbData=steamout_.length();
			cds.lpData=(void*)steamout_.c_str();

			SendMessage(hwnd,WM_COPYDATA,(WPARAM)m_hwnd,(LPARAM)&cds);*/
		}
#endif
		CMyCout::WriteString(str);
	}
private:
	template <typename T>
	void serialout(boost::archive::text_oarchive& archive_out,const T& t)
	{
		archive_out << t;
	}
	HWND m_hwnd;
};