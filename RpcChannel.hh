/**
* @project nanorpc
* @file RpcChannel.hh
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
* RpcChannel Headers for client
*
*/
#ifndef _NRPC_CHANNEL_HH_
#define _NRPC_CHANNEL_HH_
#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>
#include "nn.hpp"
#include <google/protobuf/service.h>
#include <google/protobuf/message.h>
#include <string>

namespace nrpc {
class RpcChannel : public google::protobuf::RpcChannel {
public:
	RpcChannel(const std::string url);
	virtual ~RpcChannel();
	virtual void CallMethod(const google::protobuf::MethodDescriptor* method,
	                        google::protobuf::RpcController* controller,
	                        const google::protobuf::Message* request,
	                        google::protobuf::Message* response,
	                        google::protobuf::Closure* done);

	void Close();
private:
	const std::string url_;
	nn::socket sock;
};
}
#endif
