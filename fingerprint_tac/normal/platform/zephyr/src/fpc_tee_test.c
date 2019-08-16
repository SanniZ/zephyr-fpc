#define LOG_TAG "fpc_tee_test"

#include <zephyr.h>
#include <string.h>

#include "fpc_types.h"
#include "fpc_log.h"
#include "fpc_tee.h"
#include "fpc_tee_kpi.h"
#include "fpc_tee_bio.h"
#include "fpc_tee_db_blob_test.h"

#include "app_main.h"

#define print_tee_test_result(msg, rc) \
			LOGI("Test %s %s", msg, rc ? "FAIL" : "OK");

int fpc_tee_test_task(void) {
	LOG_ENTER();

    fpc_tee_t* tee = fpc_tee_init();
    //fpc_tee_bio_t* bio = fpc_tee_bio_init(tee);

	print_tee_test_result("print_build_info",
	                      fpc_tee_print_build_info(tee));
#if defined(FPC_CONFIG_TA_DB_BLOB) && defined(FPC_CONFIG_HW_AUTH)
	print_tee_test_result("db_blob",
		                  test_fpc_tee_db_blob(tee));
#endif


    //fpc_tee_bio_release(bio);
	fpc_tee_release(tee);

	return 0;
}

K_THREAD_DEFINE(fpc_tee_test, STACK_MAX_SIZE, 
	                     fpc_tee_test_task, NULL, NULL, NULL,
	                     K_PRIO_PREEMPT(11), 0, 3000);

