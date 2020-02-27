#include <iostream>
#include <memory>
#include <thread>

#include "MessageQueue.h"

int main() {
    std::string queue_name = "/test";
    auto queue = std::make_shared<MessageQueue>(queue_name);

    std::this_thread::sleep_for(std::chrono::seconds(10));

    std::cout << "sending data..." << std::endl;
    queue->send_data("this is a test message");

    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "getting data..." << std::endl;
    auto data = queue->get_data();
    std::cout << "got data " << data << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(10));

    return 0;
}
