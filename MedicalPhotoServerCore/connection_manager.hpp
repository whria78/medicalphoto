//
// connection_manager.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2007 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_CONNECTION_MANAGER_HPP
#define HTTP_CONNECTION_MANAGER_HPP
#include "../share/unicode.h"

#include <set>
#include <boost/noncopyable.hpp>
#include "connection.h"

/// Manages open connections so that they may be cleanly stopped when the server
/// needs to shut down.
class connection_manager
  : private boost::noncopyable
{
public:
  /// Add the specified connection to the manager and start it.
  virtual void start(connection_ptr c);

  /// Stop the specified connection.
  virtual void stop(connection_ptr c);

  /// Stop all connections.
  virtual void stop_all();

private:
  /// The managed connections.
//  std::set<connection_ptr> connections_;
	std::vector<connection_ptr> connections_;
};


#endif // HTTP_connection_MANAGER_HPP
