#include <iostream>
#include <mqueue.h>
#include <memory>
#include <thread>
#include <cstring>
#include <utility>

class MessageQueue{
public:
    explicit MessageQueue(std::string qname)
    :queue_name(std::move(qname))
    {
        queueId = std::shared_ptr<mqd_t>(new mqd_t(-1), [this](mqd_t *q){
            mq_close(*q);
            mq_unlink(queue_name.c_str());
        });

        *queueId = mq_open(queue_name.c_str(), O_CREAT|O_RDWR, 0664, nullptr);
        int err = errno;
        if(err) throw std::runtime_error("MessageQueue::{ctor}(" + queue_name + ") " + strerror(err));
    }

    void send_data(const char* data, size_t size, unsigned int prio = 1){
        mq_send(*queueId, data, size, prio);
        int err = errno;
        if(err) throw std::runtime_error(std::string{"MessageQueue::send_data(...) "} + strerror(err));
    }

    void send_data(const std::string& data, unsigned int prio = 1){
        send_data(data.c_str(), (size_t)data.length(), prio);
    }

    std::string get_data(){
        struct mq_attr attrs = {0, 0, 0, 0};
        mq_getattr(*queueId, &attrs);
        char *buf = new char[attrs.mq_msgsize];
        mq_receive(*queueId, buf, attrs.mq_msgsize, nullptr);
        int err = errno;
        if(err) throw std::runtime_error(std::string{"MessageQueue::get_data() "} + strerror(err));
        return std::move(std::string{buf});
    }

private:
    std::shared_ptr<mqd_t> queueId;
    std::string queue_name;
};

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
