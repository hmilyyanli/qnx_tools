#ifndef TEST_INTERFACES__MTA_CONFIG__H
#define TEST_INTERFACES__MTA_CONFIG__H

#ifdef __cplusplus
extern "C" {
#endif

#define PRODUCER_CONSUMER_IPC "nvscisync_c_0"
#define PRODUCER_MTA_IPC "nvscisync_b_0"
#define CONSUMER_IPC "nvscisync_c_1"
#define MTA_IPC "nvscisync_b_1"

#define SAMPLES_COUNT    10u
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // TEST_INTERFACES__MTA_INTERFACE__H
