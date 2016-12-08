
#include <stm32f10x_rcc.h>
#include <delay.h>

//中断实现滴答
// SysTick interrupt handler
void SysTick_Handler() {
	if (TimingDelay != 0) { TimingDelay--; }
}

//设置需要的滴答的个数
// Do delay for mSecs milliseconds
void Delay_ms(uint32_t mSecs) {
	SysTick_Config(SystemCoreClock / DELAY_TICK_FREQUENCY_MS);
	TimingDelay = mSecs+1;
	while (TimingDelay != 0);
}

// Do delay for nSecs microseconds
void Delay_us(uint32_t uSecs) {
	SysTick_Config(SystemCoreClock / DELAY_TICK_FREQUENCY_US);
	TimingDelay = uSecs+1;
	while (TimingDelay != 0);
}
