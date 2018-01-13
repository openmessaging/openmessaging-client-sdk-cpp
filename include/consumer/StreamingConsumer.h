#ifndef OMS_STREAMCONSUMER_H
#define OMS_STREAMCONSUMER_H

#include <string>
#include <vector>

#include "KeyValue.h"
#include "ServiceLifecycle.h"
#include "MessageIterator.h"

namespace io {
    namespace openmessaging {

        namespace consumer {
            class StreamingConsumer : public virtual ServiceLifecycle {
            public:
                virtual ~StreamingConsumer() {

                }

                virtual boost::shared_ptr<KeyValue> properties() = 0;

                virtual std::vector<std::string> streams() = 0;

                virtual std::vector<std::string> consumers() = 0;

                virtual MessageIterator current() = 0;

                virtual MessageIterator begin() = 0;

                virtual MessageIterator end() = 0;

                virtual MessageIterator seekByTime(long timestamp) = 0;
            };

        }

    }
}

#endif //OMS_STREAMCONSUMER_H
