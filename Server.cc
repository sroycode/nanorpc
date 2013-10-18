/**
* @project nanorpc
* @file Server.cc
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
* Server Implementation
*
*/
#include <google/protobuf/descriptor.h>
#include <google/protobuf/stubs/common.h>
#include <city.h>
#include "Server.hh"
#include <iostream>

nrpc::Server::Server(const std::string url, size_t io_threads) :
	sock(AF_SP, NN_REP),
	url_(url),
	io_threads_(io_threads_)
{
	sock.bind(url_.c_str());
}

nrpc::Server::~Server()
{
	RpcMethodMap::iterator iter;
	for (iter = rpc_method_map_.begin(); iter != rpc_method_map_.end();) {
		RpcMethod *rpc_method = iter->second;
		++iter;
		delete rpc_method;
	}
	sock.shutdown (0);
}

void nrpc::Server::RegisterService(google::protobuf::Service *service)
{
	const google::protobuf::ServiceDescriptor *descriptor = service->GetDescriptor();
	for (int i = 0; i < descriptor->method_count(); ++i) {
		const google::protobuf::MethodDescriptor *method = descriptor->method(i);
		const google::protobuf::Message *request = &service->GetRequestPrototype(method);
		const google::protobuf::Message *response = &service->GetResponsePrototype(method);
		RpcMethod *rpc_method = new RpcMethod(service, request, response, method);
		std::string methodname=std::string(method->full_name());
		uint64_t hash = ::CityHash64(methodname.c_str(),methodname.length());
		rpc_method_map_[hash] = rpc_method;
	}
}

void nrpc::Server::Start()
{
	uint64_t opcode = 0;
	while (1) {
		char* buf=NULL;
		int bytes = sock.recv(&buf, NN_MSG, 0);
		if (bytes<=0) continue;
std::cerr << bytes << std::endl;
		memcpy((char*)(&opcode), buf, sizeof(opcode));
		// opcode = ntohl(opcode);
std::cerr << opcode << std::endl;
			RpcMethodMap::const_iterator iter = rpc_method_map_.find(opcode);
			if (iter == rpc_method_map_.end()) {
				continue;
			}
		RpcMethod *rpc_method = iter->second;
		const google::protobuf::MethodDescriptor *method = rpc_method->method_;
		google::protobuf::Message *request = rpc_method->request_->New();
		google::protobuf::Message *response = rpc_method->response_->New();
		request->ParseFromString(buf + sizeof(opcode));
		nn::freemsg(buf);
		rpc_method->service_->CallMethod(method,NULL,request, response, NULL);
		size_t msg_len = response->ByteSize();
		buf = (char*)nn::allocmsg(msg_len,0);
		response->SerializeToArray(buf,msg_len);
		sock.send(buf,msg_len,0);
		delete request;
		delete response;
		nn::freemsg(buf);
	}
}
