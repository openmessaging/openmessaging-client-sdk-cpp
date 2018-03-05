#ifndef OMS_BASE_TEST_H
#define OMS_BASE_TEST_H

#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <gtest/gtest.h>
#include "Namespace.h"
#include "CurrentEnv.h"
#include "core.h"
#include <cstdlib>

BEGIN_NAMESPACE_2(io, openmessaging)

    class BaseTest : public ::testing::Test {
    public:
        void SetUp() {
            const char *rocketmq_home = "ROCKETMQ_HOME=/Users/lizhanhui/work/apache_rocketmq/distribution/target/apache-rocketmq";
            const char *namesrv_addr = "NAMESRV_ADDR=localhost:9876";

            putenv(const_cast<char *>(rocketmq_home));
            putenv(const_cast<char *>(namesrv_addr));

            Initialize();

            static bool started = false;
            if (started) {
                return;
            }

            CurrentEnv context;

            const char* klassNameSrvStartup = "org/apache/rocketmq/namesrv/NamesrvStartup";
            classNamesrvStartup = context.findClass(klassNameSrvStartup);
            const char* sigCreateNamesrvController = "([Ljava/lang/String;)Lorg/apache/rocketmq/namesrv/NamesrvController;";
            midCreateNamesrvController = context.getMethodId(classNamesrvStartup, "createController", sigCreateNamesrvController, true);

            const char* sigStartNamesrv = "(Lorg/apache/rocketmq/namesrv/NamesrvController;)Lorg/apache/rocketmq/namesrv/NamesrvController;";
            midStartNamesrv = context.getMethodId(classNamesrvStartup, "start", sigStartNamesrv, true);

            const char* sigShutdownNamesrv = "(Lorg/apache/rocketmq/namesrv/NamesrvController;)V";
            midShutdownNamesrv = context.getMethodId(classNamesrvStartup, "shutdown", sigShutdownNamesrv, true);

            const char *klassBrokerStartup = "org/apache/rocketmq/broker/BrokerStartup";
            classBrokerStartup = context.findClass(klassBrokerStartup);

            const char* sigCreateBrokerController = "([Ljava/lang/String;)Lorg/apache/rocketmq/broker/BrokerController;";

            midCreateBrokerController = context.getMethodId(classBrokerStartup, "createBrokerController", sigCreateBrokerController, true);

            const char* sigStartBroker = "(Lorg/apache/rocketmq/broker/BrokerController;)Lorg/apache/rocketmq/broker/BrokerController;";
            midStartBroker = context.getMethodId(classBrokerStartup, "start", sigStartBroker, true);

            const char* sigShutdownBroker = "(Lorg/apache/rocketmq/broker/BrokerController;)V";
            midShutdownBroker = context.getMethodId(classBrokerStartup, "shutdown", sigShutdownBroker, true);


            jclass classString = context.findClass("java/lang/String");
            jobjectArray args = context.env->NewObjectArray(1,
                                                            classString,
                                                            context.newStringUTF(""));

            namesrvController = context.callStaticObjectMethod(classNamesrvStartup, midCreateNamesrvController, args);
            context.callStaticObjectMethod(classNamesrvStartup, midStartNamesrv, namesrvController);

            brokerController = context.callStaticObjectMethod(classBrokerStartup, midCreateBrokerController, args);
            context.callStaticObjectMethod(classBrokerStartup, midStartBroker, brokerController);

            started = true;
        }

        void TearDown() {
            CurrentEnv context;

            context.callStaticVoidMethod(classBrokerStartup, midShutdownBroker, brokerController);
            context.callStaticVoidMethod(classNamesrvStartup, midShutdownNamesrv, namesrvController);
            context.deleteRef(brokerController);
            context.deleteRef(namesrvController);
            context.deleteRef(classBrokerStartup);
            context.deleteRef(classNamesrvStartup);

            std::cout << "RocketMQ server cluster tears down OK" << std::endl;
        }

    protected:
        jclass classNamesrvStartup;
        jmethodID midCreateNamesrvController;
        jmethodID midStartNamesrv;
        jmethodID midShutdownNamesrv;
        jobject namesrvController;

        jclass classBrokerStartup;
        jmethodID  midCreateBrokerController;
        jmethodID  midStartBroker;
        jmethodID  midShutdownBroker;
        jobject brokerController;
    };

END_NAMESPACE_2(io, openmessaging)
#endif //OMS_BASE_TEST_H
