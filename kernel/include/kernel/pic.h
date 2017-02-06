#ifndef _KERNEL_PIC_H
#define _KERNEL_PIC_H

#define PIC_MASTER    0x20    /* IO base address for master PIC */
#define PIC_SLAVE    0xA0    /* IO base address for slave PIC */
#define PIC_MASTER_COMMAND  PIC_MASTER
#define PIC_MASTER_DATA (PIC_MASTER+1)
#define PIC_MASTER_IRQ_ENTRIES 8
#define PIC_SLAVE_COMMAND  PIC_SLAVE
#define PIC_SLAVE_DATA (PIC_SLAVE+1)
#define PIC_SLAVE_IRQ_ENTRIES 8
#define PIC_IRQ_ENTRIES (PIC_MASTER_IRQ_ENTRIES + PIC_SLAVE_IRQ_ENTRIES)

#define PIC_EOI 0x20

#define ICW1_ICW4 0x01    //ICW4 (not) needed
#define ICW1_SINGLE 0x02    // Single (cascade) mode
#define ICW1_INTERVAL4  0x04    // Call address interval 4 (8)
#define ICW1_LEVEL  0x08    // Level triggered (edge) mode
#define ICW1_INIT 0x10    // Initialization - required!
 
#define ICW4_8086 0x01    // 8086/88 (MCS-80/85) mode
#define ICW4_AUTO 0x02    // Auto (normal) EOI
#define ICW4_BUF_SLAVE  0x08    // Buffered mode/slave
#define ICW4_BUF_MASTER 0x0C    // Buffered mode/master
#define ICW4_SFNM 0x10    // Special fully nested (not)

#endif /* _KERNEL_PIC_H */