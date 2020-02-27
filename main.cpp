#include <iostream>
#include <memory>
#include <thread>
#include <unistd.h>
#include <csignal>

#include "MessageQueue.h"

void child_payload(const std::shared_ptr<MessageQueue>& queue)
{
    queue->get_data_loop([](const char *data, size_t len)-> bool{
        std::cout << "chile get message: " << std::string{data} << std::endl;
        return true;
    });

    std::cout << "child process finished" << std::endl;
}

void parent_payload(const std::shared_ptr<MessageQueue>& queue, pid_t child_pid)
{
    for(int i = 0; i < 10; ++i){
        std::string message = "this message with " + std::to_string(i);
        queue->send_data(message);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    kill(child_pid, SIGINT);
    std::cout << "kill sended" << std::endl;
}

int main() {
    std::string queue_name = "/test";
    auto queue = std::make_shared<MessageQueue>(queue_name);

    pid_t c_pid = fork();

    if(c_pid){
        parent_payload(queue, c_pid);
    }else{
        child_payload(queue);
    }

    return 0;
}
