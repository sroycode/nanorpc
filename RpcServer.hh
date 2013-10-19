/**
* @project nanorpc
* @file RpcServer.hh
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
* RpcServer Headers
*
*/
#ifndef _NRPC_SERVER_HH_
#define _NRPC_SERVER_HH_

#include <string>
#include <map>
#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>
#include "nn.hpp"

#include "RpcMethod.hpp"

namespace nrpc {

class RpcServer {
	typedef std::map<uint64_t,RpcMethod*> RpcMethodMap;
public:
	RpcServer(const char* url);
	~RpcServer();
	// add more endpoints
	void EndPoint(const char* url);
	// start 
	void Start();
	// register a service
	void RegisterService(google::protobuf::Service *service);
	// remove all services
	void RemoveService();
	// close
	void Close();

private:
	nn::socket sock;
	int sockid;
	RpcMethodMap rpc_method_map_;
};
}
#endif
