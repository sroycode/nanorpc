/**
* @project nanorpc
* @file Server.hh
* @author  S Roychowdhury <sroycode AT gmail DOT com>
* @version 1.0
*
* @section LICENSE
*
* Copyright (c) 2013 S Roychowdhury
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the "Software"), to deal in
* the Software without restriction, including without limitation the rights to
* use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
* the Software, and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
* FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
* IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
* @section DESCRIPTION
*
* Server Headers
*
*/
#ifndef _NRPC_SERVER_HH_
#define _NRPC_SERVER_HH_

#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>
#include "nn.hpp"

#include <map>
#include <string>


#include "RpcMethod.hpp"

namespace nrpc {

class Server {

public:
	Server(const std::string url, size_t io_threads);
	~Server();
	void Start();
	void RegisterService(google::protobuf::Service *service);

private:
	nn::socket sock;
	const std::string url_;
	const size_t io_threads_;
	typedef std::map<uint64_t,RpcMethod*> RpcMethodMap;
	RpcMethodMap rpc_method_map_;
};
};
#endif
