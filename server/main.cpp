#include <iostream>
#include <memory>
#include <thread>
#include <unistd.h>
#include <csignal>

#include <MessageQueue.h>

int main() {
    std::string queue_name = "/test";
    auto queue = std::make_shared<MessageQueue>(queue_name);

    for(int i = 0; i < 1000; ++i){
        std::string message = "this message with " + std::to_string(i);
        queue->send_data(message);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    std::cout << "child process finished" << std::endl;

    return 0;
}
