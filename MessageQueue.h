#ifndef POSIX_QUEUES_MESSAGEQUEUE_H
#define POSIX_QUEUES_MESSAGEQUEUE_H

#include <memory>
#include <mqueue.h>

class MessageQueue{
public:
    explicit MessageQueue(std::string qname);

    void send_data(const char* data, size_t size, unsigned int prio = 1);

    void send_data(const std::string& data, unsigned int prio = 1);

    std::string get_data();

    void get_data_loop(const std::function<bool(const char* data, size_t len)>& callback);

private:
    std::shared_ptr<mqd_t> queueId;
    std::string queue_name;
};
#endif //POSIX_QUEUES_MESSAGEQUEUE_H
