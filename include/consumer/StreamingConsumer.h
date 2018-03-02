#ifndef OMS_STREAM_CONSUMER_H
#define OMS_STREAM_CONSUMER_H

#include <string>
#include <vector>

#include <boost/smart_ptr.hpp>

#include "KeyValue.h"
#include "ServiceLifecycle.h"
#include "MessageIterator.h"
#include "Namespace.h"

BEGIN_NAMESPACE_3(io, openmessaging, consumer)

    class StreamingConsumer : public virtual ServiceLifecycle {
    public:
        virtual ~StreamingConsumer() {

        }

        virtual boost::shared_ptr<KeyValue> properties() = 0;

        virtual std::vector<std::string> streams() = 0;

        virtual std::vector<std::string> consumers() = 0;

        virtual boost::shared_ptr<MessageIterator> current() = 0;

        virtual boost::shared_ptr<MessageIterator> begin() = 0;

        virtual boost::shared_ptr<MessageIterator> end() = 0;

        virtual boost::shared_ptr<MessageIterator> seekByTime(long timestamp) = 0;
    };

END_NAMESPACE_3(io, openmessaging, consumer)

#endif //OMS_STREAM_CONSUMER_H
