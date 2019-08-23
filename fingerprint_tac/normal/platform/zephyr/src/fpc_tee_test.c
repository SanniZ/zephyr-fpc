#define LOG_TAG "fpc_tee_test"

#include <stdio.h>
#include <string.h>
#include <zephyr.h>

#include "fpc_types.h"
#include "fpc_log.h"
#include "fpc_tee.h"
#include "fpc_tee_kpi.h"
#include "fpc_tee_bio.h"
#include "fpc_tee_db_blob_test.h"

#include "fpc_service.h"

#define setup_tee_test() \
            char test_result[1024] = {0}; \
            char *result_ptr = test_result;
#define run_tee_test_case(name, rc) \
            rc ? sprintf(result_ptr, "[FAIL] %s\n", name): \
                 sprintf(result_ptr, "[ OK ] %s\n", name); \
            result_ptr = test_result + strlen(result_ptr);
#define print_tee_test_result() \
            LOGI("Test result:\n%s", test_result);

static void fpc_tee_test_task(void *p1, void *p2, void *p3) {
    LOG_ENTER();
    fpc_tee_t* tee = fpc_tee_init();
    //fpc_tee_bio_t* bio = fpc_tee_bio_init(tee);

    setup_tee_test();
    run_tee_test_case("print_build_info", fpc_tee_print_build_info(tee));
#if defined(FPC_CONFIG_TA_DB_BLOB) && defined(FPC_CONFIG_HW_AUTH)
    run_tee_test_case("db_blob", test_fpc_tee_db_blob(tee));
#endif
    print_tee_test_result();

    //fpc_tee_bio_release(bio);
    fpc_tee_release(tee);
}

static K_THREAD_STACK_DEFINE(tee_test_stack, STACK_MAX_SIZE);
static struct k_thread tee_test_thread;

void fpc_create_test_task(void) {
    k_thread_create(&tee_test_thread, tee_test_stack, STACK_MAX_SIZE,
                    fpc_tee_test_task, NULL, NULL, NULL, K_PRIO_PREEMPT(11), 0, 0);
}
//K_THREAD_DEFINE(fpc_tee_test, STACK_MAX_SIZE, 
//                fpc_tee_test_task, NULL, NULL, NULL,
//                K_PRIO_PREEMPT(11), 0, 3000);

