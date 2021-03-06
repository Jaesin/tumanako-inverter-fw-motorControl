#include "fu.h"

uint32_t MotorVoltage::boost;
u32fp MotorVoltage::fac;
uint32_t MotorVoltage::maxAmp;
u32fp MotorVoltage::endFrq;
u32fp MotorVoltage::minFrq;


/** Set 0 Hz boost to overcome winding resistance */
void MotorVoltage::SetBoost(uint32_t boost /**< amplitude in digit */)
{
   MotorVoltage::boost = boost;
   CalcFac();
}

/** Set frequency where the full amplitude is to be provided */
void MotorVoltage::SetWeakeningFrq(u32fp frq)
{
   endFrq = frq;
   CalcFac();
}

/** Get amplitude for a given frequency */
uint32_t MotorVoltage::GetAmp(u32fp frq)
{
   return MotorVoltage::GetAmpPerc(frq, 100);
}

/** Get amplitude for given frequency multiplied with given percantage */
uint32_t MotorVoltage::GetAmpPerc(u32fp frq, uint32_t perc)
{
   uint32_t amp = (perc * (FP_TOINT(FP_MUL(fac, frq)) + boost)) / 100;
   if (frq < minFrq)
   {
      amp = 0;
   }
   if (amp > maxAmp)
   {
      amp = maxAmp;
   }
   return amp;
}

void MotorVoltage::SetMaxAmp(uint32_t maxAmp)
{
   MotorVoltage::maxAmp = maxAmp;
   CalcFac();
}

void MotorVoltage::SetMinFrq(u32fp frq)
{
   minFrq = frq;
}

/** Calculate slope of u/f */
void MotorVoltage::CalcFac()
{
   fac = FP_DIV(FP_FROMINT(maxAmp - boost), endFrq);
}
