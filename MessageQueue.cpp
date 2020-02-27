#include "MessageQueue.h"

#include <cstring>

MessageQueue::MessageQueue(std::string qname)
:queue_name(std::move(qname))
{
    queueId = std::shared_ptr<mqd_t>(new mqd_t(-1), [this](const mqd_t *q){
        mq_close(*q);
        mq_unlink(queue_name.c_str());
    });

    *queueId = mq_open(queue_name.c_str(), O_CREAT|O_RDWR, 0664, nullptr);
    int err = errno;
    if(err) throw std::runtime_error("MessageQueue::{ctor}(" + queue_name + ") " + strerror(err));
}

void MessageQueue::send_data(const char *data, size_t size, unsigned int prio)
{
    mq_send(*queueId, data, size, prio);
    int err = errno;
    if(err) throw std::runtime_error(std::string{"MessageQueue::send_data(...) "} + strerror(err));
}

void MessageQueue::send_data(const std::string &data, unsigned int prio)
{
    send_data(data.c_str(), (size_t)data.length(), prio);
}

std::string MessageQueue::get_data()
{
    struct mq_attr attrs = {0, 0, 0, 0};
    mq_getattr(*queueId, &attrs);
    char *buf = new char[attrs.mq_msgsize];
    mq_receive(*queueId, buf, attrs.mq_msgsize, nullptr);
    int err = errno;
    if(err) throw std::runtime_error(std::string{"MessageQueue::get_data() "} + strerror(err));
    return std::move(std::string{buf});
}
