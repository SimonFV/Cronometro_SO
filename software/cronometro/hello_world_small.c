#include "sys/alt_irq.h"

#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"
#include "alt_types.h"

#include "system.h"

static unsigned int segments7_0 = 0;
static unsigned int segments7_1 = 0;
static unsigned int segments7_2 = 0;
static unsigned int segments7_3 = 0;
static unsigned int segments7_4 = 0;
static unsigned int segments7_5 = 0;

static unsigned int milliseconds = 0;
static unsigned int seconds = 0;
static unsigned int minutes = 0;

void io_button_isr(void * context);
void io_button_setup();
volatile int edge_val;

volatile int running = 0;

/**
 * @brief Responsible for handling the timer counter and timer interrupts with its modes
 *
 * @param context
 */
static void timer_irs(void *context)
{
	//Standby and start condition, depending on whether the button is pressed or not.
	if (running == 0)
	{
		IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);
		return;
	}

	(void)context;

	milliseconds++;

	//Reads the mode from the switches: milliseconds, seconds or mixed
	unsigned int mode = IORD_ALTERA_AVALON_PIO_DATA(PIO_SWITCH_0_BASE);

	//milliseconds
	if (mode == 0)
	{
		segments7_0 = milliseconds % 10;
		segments7_1 = (milliseconds / 10) % 10;
		segments7_2 = (milliseconds / 100) % 10;
		segments7_3 = (milliseconds / 1000) % 10;
		segments7_4 = (milliseconds / 10000) % 10;
		segments7_5 = (milliseconds / 100000) % 10;
	}
	//seconds
	else if (mode == 1)
	{
		seconds = milliseconds/1000;

		segments7_0 = seconds % 10;
		segments7_1 = (seconds / 10) % 10;
		segments7_2 = (seconds / 100) % 10;
		segments7_3 = (seconds / 1000) % 10;
		segments7_4 = (seconds / 10000) % 10;
		segments7_5 = (seconds / 100000) % 10;
	}
	//mixed
	else if (mode == 2)
	{
		minutes = milliseconds/60000;
		seconds = (milliseconds/1000) % 60;

		segments7_0 = (milliseconds/10) % 10;
		segments7_1 = (milliseconds/100) % 10;
		segments7_2 = seconds % 10;
		segments7_3 = (seconds/10) % 10;
		segments7_4 = minutes % 10;
		segments7_5 = (minutes/10) % 10;
	}
	else
	{
		segments7_0 = 127;
		segments7_1 = 127;
		segments7_2 = 127;
		segments7_3 = 127;
		segments7_4 = 127;
		segments7_5 = 127;
	}

	//Sets the value to be decoded to show in the display.
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_7SEGMENTS_0_BASE, segments7_0);
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_7SEGMENTS_1_BASE, segments7_1);
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_7SEGMENTS_2_BASE, segments7_2);
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_7SEGMENTS_3_BASE, segments7_3);
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_7SEGMENTS_4_BASE, segments7_4);
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_7SEGMENTS_5_BASE, segments7_5);

	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);
}

/**
 * @brief Configure the necessary for button interruptions
 *
 */
void io_button_setup(void){
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_BUTTON_0_BASE, 0x01);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_BUTTON_0_BASE, 0x00);
	void * edge_val_ptr;
	edge_val_ptr = (void *) &edge_val;
	alt_ic_isr_register(PIO_BUTTON_0_IRQ_INTERRUPT_CONTROLLER_ID,
						PIO_BUTTON_0_IRQ,
						io_button_isr,
						edge_val_ptr,
						0x00);
}

/**
 * @brief Handles button interrupts and resets its state
 *
 * @param context
 */
void io_button_isr(void * context){
	volatile int * edge_ptr;
	edge_ptr = (volatile int *) context;
	*edge_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIO_BUTTON_0_BASE);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_BUTTON_0_BASE, 0);
}

/**
 * @brief Main function in charge of calling and executing the complete program
 *
 * @return int
 */
int main()
{
	//Initialize all IOs
	alt_ic_isr_register(
		TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID,
		TIMER_0_IRQ,
		timer_irs,
		NULL,
		NULL);

	IOWR_ALTERA_AVALON_TIMER_CONTROL(
		TIMER_0_BASE,
		ALTERA_AVALON_TIMER_CONTROL_ITO_MSK | ALTERA_AVALON_TIMER_CONTROL_CONT_MSK);

	io_button_setup();

	/* Event loop never exits. */
	while (1){
		if(edge_val & 0x01){
			edge_val = 0;
			if (running == 0)
				running = 1;
			else
				running = 0;
		}
	}

	return 0;
}
