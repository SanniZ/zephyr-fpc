/*
 * Copyright (c) 2015 Fingerprint Cards AB <tech@fingerprints.com>
 *
 * All rights are reserved.
 * Proprietary and confidential.
 * Unauthorized copying of this file, via any medium is strictly prohibited.
 * Any use is subject to an appropriate license granted by Fingerprint Cards AB.
 */

#ifndef FPC_IRQ_DEVICE_H
#define FPC_IRQ_DEVICE_H

typedef struct fpc_irq fpc_irq_t;

void fpc_irq_release(fpc_irq_t* device);
fpc_irq_t* fpc_irq_init();

int fpc_irq_set_cancel(fpc_irq_t* device);
int fpc_irq_clear_cancel(fpc_irq_t* device);
int fpc_irq_wait(fpc_irq_t* device, int irq_value);
int fpc_irq_status(fpc_irq_t* device);
int fpc_irq_wakeup_enable(fpc_irq_t* device);
int fpc_irq_wakeup_disable(fpc_irq_t* device);

#endif // FPC_REE_DEVICE_H
