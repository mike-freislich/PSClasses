#pragma once
#include <vector>
#include "PSKeys.h"
#include "PSParameterManager.h"
#include "AudioStub.h"
#include "AUMapping.h"
#include "config.h"

template <typename T>
void attachAudioFunc(const char *parmKey, T *audioUnit, void (T::*func)(float))
{
   if (PSParameter *p = Parameters[parmKey])
   {
      auto f = mapValueFunc(audioUnit, func);
      p->setAudioUnitHandle(f);
   }
}

template <typename T>
void attachAudioFunc(const char *parmKey, T *audioUnit, void (T::*func)(unsigned int, float), uint8_t channel)
{
   if (PSParameter *p = Parameters[parmKey])
   {
      auto f = mapValueFunc(audioUnit, func);
      p->setAudioUnitHandle(f, channel);
   }
}




void connectParameterTargets()
{
   //attachAudioFunc(PARM_AENV_AMOUNT, &auDC_AMPENV, &AudioSynthWaveformDc::amplitude);

   //attachAudioFunc(PARM_AENV_ATTACK, &auENV_AMP_V1, &AudioEffectEnvelope::attack);
   //attachAudioFunc(PARM_AENV_HOLD, &auENV_AMP_V1, &AudioEffectEnvelope::hold);
   //attachAudioFunc(PARM_AENV_DECAY, &auENV_AMP_V1, &AudioEffectEnvelope::decay);
   //attachAudioFunc(PARM_AENV_SUSTAIN, &auENV_AMP_V1, &AudioEffectEnvelope::sustain);
   //attachAudioFunc(PARM_AENV_RELEASE, &auENV_AMP_V1, &AudioEffectEnvelope::release);

   //attachAudioFunc(PARM_AENV_ATTACK, &auENV_AMP_V1, &AudioEffectEnvelope::attack);
   //attachAudioFunc(PARM_AENV_HOLD, &auENV_AMP_V1, &AudioEffectEnvelope::hold);
   //attachAudioFunc(PARM_AENV_DECAY, &auENV_AMP_V1, &AudioEffectEnvelope::decay);
   //attachAudioFunc(PARM_AENV_SUSTAIN, &auENV_AMP_V1, &AudioEffectEnvelope::sustain);
   //attachAudioFunc(PARM_AENV_RELEASE, &auENV_AMP_V1, &AudioEffectEnvelope::release);

   //attachAudioFunc(PARM_MASTER_GAIN_A, &auAMP_MASTER_GAIN_L, &AudioAmplifier::gain);
   //attachAudioFunc(PARM_MASTER_GAIN_B, &auAMP_MASTER_GAIN_L, &AudioAmplifier::gain);
}

// void testParameters()
// {
//    PSConfig config;
//    config.loadConfig("config.json");
//    config.applyConfig();
//    connectParameterTargets();

//    Parameters[PARM_AENV_ATTACK]->setValue(9);
//    Parameters[PARM_AENV_AMOUNT]->setValue(85);
//    Parameters[PARM_AENV_DECAY]->setValue(200);
//    Parameters[PARM_AENV_AMOUNT]->setValue(99);

//    Parameters[PARM_MASTER_GAIN_A]->setValue(50);
//    Parameters[PARM_MASTER_GAIN_B]->setValue(75);
// }
