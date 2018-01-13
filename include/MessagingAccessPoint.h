#ifndef MESSAGINGACCESSPOINT_H
#define MESSAGINGACCESSPOINT_H

#include <string>
#include <boost/shared_ptr.hpp>

#include "ServiceLifecycle.h"
#include "KeyValue.h"
#include "producer.h"
#include "consumer.h"
#include "ResourceManager.h"
#include "observer.h"

namespace io {

namespace openmessaging {

extern boost::shared_ptr<KeyValue> kv_nullptr;

class MessagingAccessPoint : public virtual ServiceLifecycle {
public:
    virtual ~MessagingAccessPoint() {

    }

    virtual boost::shared_ptr<KeyValue> properties();

    virtual std::string implVersion() = 0;

    virtual boost::shared_ptr<producer::Producer> createProducer(boost::shared_ptr<KeyValue> properties = kv_nullptr) = 0;

    virtual boost::shared_ptr<consumer::PushConsumer> createPushConsumer(boost::shared_ptr<KeyValue> properties = kv_nullptr) = 0;

    virtual boost::shared_ptr<consumer::PullConsumer> createPullConsumer(const std::string &queueName, boost::shared_ptr<KeyValue> properties = kv_nullptr) = 0;

    virtual boost::shared_ptr<consumer::StreamingConsumer> createStreamingConsumer(const std::string &queueName,
                                                                         boost::shared_ptr<KeyValue> properites = kv_nullptr) = 0;

    virtual boost::shared_ptr<ResourceManager> getResourceManager() = 0;

    virtual void addObserver(boost::shared_ptr<observer::Observer> observer) = 0;
};

}

}

#endif // MESSAGINGACCESSPOINT_H
