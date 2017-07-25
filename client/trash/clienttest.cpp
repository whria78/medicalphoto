#include "stdafx.h"

#include "whriaclient.h"
#include "../share/config.h"
#include "../datatype/datatype.h"
#include <boost/serialization/vector.hpp>


template <typename T>
void serial_out(boost::archive::text_oarchive& archive,const T& t)
{
	archive << t;
}

int main(int argc, char* argv[])
{
	config config_;
	config_.BackUpInterval=111;
	config_.save();
	
	CWhriaClient c;

	c.connect("localhost","9999");
	dx_list dx_list;
	c.getdx("aa",dx_list);

	command cmd_;
	cmd_.order_code=LOGIN;



  return 0;
}
