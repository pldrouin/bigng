#include "adc.h"

void initadc(void)
{
  ADC_MUX_SELECT_REG = _BV(ADC_REFERENCE_SELECT_BIT_0);
  //ADC_CTRL_STATUS_REG = _BV(ADC_START_CONVERSION) | _BV(ENABLE_ADC) | _BV(ENABLE_ADC_AUTO_TRIGGER) | _BV(ADC_INTERRUPT_ENABLE);
  ADC_CTRL_STATUS_REG = _BV(ADC_START_CONVERSION) | _BV(ENABLE_ADC) | _BV(ENABLE_ADC_AUTO_TRIGGER) | _BV(ADC_INTERRUPT_ENABLE) | _BV(ADC_PRESCALE_BIT_2) | _BV(ADC_PRESCALE_BIT_1) | _BV(ADC_PRESCALE_BIT_0);
}

// Called when ADC conversion completes
ISR(ADC_INTR_FUNC)
{
  uint8_t adc_channel = ADC_MUX_SELECT_REG & 7U;
  ADC_MUX_SELECT_REG = (ADC_MUX_SELECT_REG & ~7U) | (adc_channel+1)%8; 
  uint16_t value = ADC_DATA_LOW_REG | (((uint16_t)ADC_DATA_HIGH_REG)<<8);
}
