/**
* @project nanorpc
* @file EchoServer.cc
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
* example: echo server
*
*/
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <iostream>
#include "RpcServer.hh"
#include "echo.pb.h"
#include "EchoEndpoint.hh"

class EchoServiceImpl : public echo::EchoService {
public:
	EchoServiceImpl() {};

	virtual void Echo1(::google::protobuf::RpcController* controller,
	                   const ::echo::EchoRequest* request,
	                   ::echo::EchoResponse* response,
	                   ::google::protobuf::Closure* done) {
		std::cerr << "Received1: " << request->message().c_str() << std::endl;
		response->set_response(std::string("You sent1: ") + request->message());
		if (done) {
			done->Run();
		}
	}
	virtual void Echo2(::google::protobuf::RpcController* controller,
	                   const ::echo::EchoRequest* request,
	                   ::echo::EchoResponse* response,
	                   ::google::protobuf::Closure* done) {
		std::cerr << "Received2: " << request->message().c_str() << std::endl;
		response->set_response(std::string("You sent2: ") + request->message());
		if (done) {
			done->Run();
		}
	}
};

void OnExit(int sig)
{
	std::cerr << "Exiting on ^C " << sig << std::endl;
}

int main(int argc, char *argv[])
{
	signal(SIGINT, OnExit);
	try {
		nrpc::RpcServer rpc_server(ECHO_ENDPOINT_PORT);
		::google::protobuf::Service *service = new EchoServiceImpl();
		rpc_server.RegisterService(service);
		rpc_server.Start();
	} catch (nn::exception& e) {
		std::cerr << "NN EXCEPTION : " << e.what() << std::endl;
	} catch (std::exception& e) {
		std::cerr << "STD EXCEPTION : " << e.what() << std::endl;
	} catch (...) {
		std::cerr << " UNTRAPPED EXCEPTION " << std::endl;
	}
	return 0;
}
