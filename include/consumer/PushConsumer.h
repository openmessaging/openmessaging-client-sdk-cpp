#ifndef OMS_PUSH_CONSUMER_H
#define OMS_PUSH_CONSUMER_H

#include <string>

#include <boost/shared_ptr.hpp>

#include "ServiceLifecycle.h"
#include "PushConsumerInterceptor.h"
#include "MessageListener.h"
#include "Namespace.h"
#include "OMS.h"

BEGIN_NAMESPACE_3(io, openmessaging, consumer)

        class PushConsumer : public virtual ServiceLifecycle {
        public:
            virtual ~PushConsumer() {

            }

            virtual boost::shared_ptr<KeyValue> properties() = 0;

            virtual void resume() = 0;

            virtual void suspend() = 0;

            virtual bool isSuspended() = 0;

            virtual PushConsumer &attachQueue(const std::string &queueName,
                                              const boost::shared_ptr<MessageListener> &listener,
                                              const boost::shared_ptr<KeyValue> &properties = kv_nullptr) = 0;

            virtual PushConsumer &detachQueue(const std::string &queueName) = 0;

            virtual void addInterceptor(const boost::shared_ptr<PushConsumerInterceptor> &interceptor) = 0;

            virtual void removeInterceptor(const boost::shared_ptr<PushConsumerInterceptor> &interceptor) = 0;
        };

END_NAMESPACE_3(io, openmessaging, consumer)

#endif //OMS_PUSH_CONSUMER_H
