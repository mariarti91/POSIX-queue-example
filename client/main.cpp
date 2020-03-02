#include <iostream>
#include <memory>
#include <unistd.h>

#include <MessageQueue.h>

int main() {
    std::string queue_name = "/test";
    auto queue = std::make_shared<MessageQueue>(queue_name);

    int count = 0;

    queue->get_data_loop([&count](const char *data, size_t len)-> bool{
        std::cout << "parent get message: " << std::string{data} << std::endl;
        return ++count < 10;
    });

    return 0;
}
