/**
* @project nanorpc
* @file RpcMethod.hpp
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
* RpcMethod: definition of PB Rpc Method
*
*/
#ifndef _NRPC_RPCMETHOD_HPP_
#define _NRPC_RPCMETHOD_HPP_

#include <google/protobuf/service.h>
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/stubs/common.h>

namespace nrpc {
struct RpcMethod {
public:
	RpcMethod(google::protobuf::Service *service,
	          const google::protobuf::Message *request,
	          const google::protobuf::Message *response,
	          const google::protobuf::MethodDescriptor *method)
		: service_(service),
		  request_(request),
		  response_(response),
		  method_(method) {
	}

	google::protobuf::Service *service_;
	const google::protobuf::Message *request_;
	const google::protobuf::Message *response_;
	const google::protobuf::MethodDescriptor *method_;
};

} // namespace

#endif
