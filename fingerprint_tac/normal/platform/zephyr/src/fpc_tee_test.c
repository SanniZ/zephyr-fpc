#define LOG_TAG "fpc_tee_test"

#include <zephyr.h>
#include <string.h>
#include <stdio.h>

#include "fpc_types.h"
#include "fpc_log.h"
#include "fpc_tee.h"
#include "fpc_tee_kpi.h"
#include "fpc_tee_bio.h"
#include "fpc_tee_db_blob_test.h"

#include "app_main.h"


#define create_tee_test() \
            char test_result[1024] = {0}; \
            char *result_ptr = test_result; \
            char temp_buf[32]
#define run_tee_test_case(name, rc) \
            memset(temp_buf, 0, sizeof(temp_buf)); \
            sprintf(temp_buf, "Run %16s test %s\n", name, rc ? "FAIL": "OK"); \
            memcpy(result_ptr, temp_buf, strlen(temp_buf)); \
            result_ptr += strlen(temp_buf)
#define print_tee_test_result() \
            LOGI("Run test result:\n%s", test_result)

int fpc_tee_test_task(void) {
    LOG_ENTER();

    fpc_tee_t* tee = fpc_tee_init();
    //fpc_tee_bio_t* bio = fpc_tee_bio_init(tee);

    create_tee_test();
    run_tee_test_case("print_build_info", fpc_tee_print_build_info(tee));
#if defined(FPC_CONFIG_TA_DB_BLOB) && defined(FPC_CONFIG_HW_AUTH)
    run_tee_test_case("db_blob", test_fpc_tee_db_blob(tee));
#endif
    print_tee_test_result();

    //fpc_tee_bio_release(bio);
    fpc_tee_release(tee);

    return 0;
}

K_THREAD_DEFINE(fpc_tee_test, STACK_MAX_SIZE, 
	                     fpc_tee_test_task, NULL, NULL, NULL,
	                     K_PRIO_PREEMPT(11), 0, 3000);

