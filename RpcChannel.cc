/**
* @project nanorpc
* @file RpcChannel.cc
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
* Channel Implementation for client
*
*/
#include <google/protobuf/descriptor.h>
#include "RpcChannel.hh"
#include <city.h>
#include <iostream>

nrpc::RpcChannel::RpcChannel(const char* url) :
	sock(AF_SP, NN_REQ),
	sockid(sock.connect(url))
{
}

nrpc::RpcChannel::~RpcChannel()
{
	Close();
}

void nrpc::RpcChannel::CallMethod(const google::protobuf::MethodDescriptor* method,
                                  google::protobuf::RpcController* controller,
                                  const google::protobuf::Message* request,
                                  google::protobuf::Message* response,
                                  google::protobuf::Closure* done)
{
	std::string methodname=std::string(method->full_name());
	uint64_t opcode = ::CityHash64(methodname.c_str(),methodname.length());
	size_t msg_len = request->ByteSize() + sizeof(opcode);
	char* buf=NULL;
	buf = (char*)nn::allocmsg(msg_len,0);
	memcpy(buf, &opcode, sizeof(opcode));
	request->SerializeToArray(buf + sizeof(opcode), request->ByteSize());
	sock.send(buf,msg_len,0);
	nn::freemsg(buf);
	sock.recv(&buf, NN_MSG, 0);
	response->ParseFromString(buf);
	nn::freemsg(buf);
}

void nrpc::RpcChannel::Close()
{
	if (sockid>0) {
		sock.shutdown (0);
		sockid=0;
	}
}
