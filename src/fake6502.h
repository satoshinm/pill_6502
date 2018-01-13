// Header for declaring external interface to fake6502.c


/* Fake6502 requires you to provide two external     *
 * functions:                                        *
 *                                                   */
uint8_t read6502(uint16_t address);
void write6502(uint16_t address, uint8_t value);
/*                                                   *
 * You may optionally pass Fake6502 the pointer to a *
 * function which you want to be called after every  *
 * emulated instruction. This function should be a   *
 * void with no parameters expected to be passed to  *
 * it.                                               *
 *                                                   *
 * This can be very useful. For example, in a NES    *
 * emulator, you check the number of clock ticks     *
 * that have passed so you can know when to handle   *
 * APU events.                                       *
 *                                                   *
 * To pass Fake6502 this pointer, use the            *
 * hookexternal(void *funcptr) function provided.    *
 *                                                   *
 * To disable the hook later, pass NULL to it.       */


void reset6502();
/*   - Call this once before you begin execution.    */

void exec6502(uint32_t tickcount);
/*   - Execute 6502 code up to the next specified    *
 *     count of clock ticks.                         */

void step6502();
/*   - Execute a single instrution.                  *
 *                                                   */

void irq6502();
/*   - Trigger a hardware IRQ in the 6502 core.      */
 
void nmi6502();
/*   - Trigger an NMI in the 6502 core.              */

void hookexternal(void *funcptr);
/*   - Pass a pointer to a void function taking no   *
 *     parameters. This will cause Fake6502 to call  *
 *     that function once after each emulated        *
 *     instruction.                                  */

extern uint32_t clockticks6502;
/*   - A running total of the emulated cycle count.  */
 
extern uint32_t instructions;
/*   - A running total of the total emulated         *
 *     instruction count. This is not related to     *
 *     clock cycle timing.                           */

