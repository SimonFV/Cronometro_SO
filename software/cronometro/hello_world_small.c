#include "sys/alt_irq.h"

#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"

#include "system.h"

static unsigned leds = 0;

static void timer_irs(void *context)
{
	(void)context;

	leds = leds << 1 | (IORD_ALTERA_AVALON_PIO_DATA(PIO_SWITCH_0_BASE) & 1);
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_LEDS_0_BASE, leds);
}

int main()
{ 
	alt_ic_isr_register(
			TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID,
			TIMER_0_IRQ,
			timer_irs,
			NULL,
			NULL
	);

	IOWR_ALTERA_AVALON_TIMER_CONTROL(
			TIMER_0_BASE,
			ALTERA_AVALON_TIMER_CONTROL_ITO_MSK
			| ALTERA_AVALON_TIMER_CONTROL_CONT_MSK
	);


	/* Event loop never exits. */
	while (1);

	return 0;
}