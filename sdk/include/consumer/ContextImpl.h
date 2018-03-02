#ifndef OMS_CONTEXT_IMPL_H
#define OMS_CONTEXT_IMPL_H

#include "Namespace.h"
#include "consumer/Context.h"
#include "core.h"

BEGIN_NAMESPACE_3(io, openmessaging, consumer)
    class ContextImpl : public Context {
    public:

        ContextImpl(jobject proxy);

        virtual boost::shared_ptr<KeyValue> properties();

        virtual void ack(boost::shared_ptr<KeyValue> props);

    private:
        jobject _proxy;
        jclass classContext;
        jmethodID midProperties;
        jmethodID midAck;
        jmethodID midAck2;

    };
END_NAMESPACE_3(io, openmessaging, consumer)

#endif //OMS_CONTEXT_IMPL_H
