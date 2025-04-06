#include <grpcpp/grpcpp.h>
#include "service.grpc.pb.h"
#include <iostream>
#include <memory>

void SayHello() {
    std::string target_str = "localhost:50051";
    Greeter::Stub stub(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));

    HelloRequest request;
    request.set_name("World");

    HelloReply reply;

    grpc::ClientContext context;
    grpc::Status status = stub.SayHello(&context, request, &reply);

    if (status.ok()) {
        std::cout << "Greeter received: " << reply.message() << std::endl;
    } else {
        std::cout << "RPC failed" << std::endl;
    }
}


int main() {
    SayHello();

    return 0;
}
