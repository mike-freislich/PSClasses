#pragma once

#include <vector>
#include "PSKeys.h"
#include "PSParameterManager.h"
#include "AudioMockObjects.h"
#include "config.h"

typedef std::vector<PSParameter *> GlobalParameterList;

AudioEffectEnvelope AU_Aenv_a;
AudioEffectEnvelope AU_Aenv_b;
AudioEffectEnvelope AU_Penv_a;
AudioEffectEnvelope AU_Penv_b;
AudioEffectEnvelope AU_Fenv_a;
AudioEffectEnvelope AU_Fenv_b;
AudioAmplifier AU_amp_mainL;
AudioAmplifier AU_amp_mainR;
AudioMixer4 AU_mixer_output;

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
   attachAudioFunc(PARM_AENVa_ATTACK   , &AU_Aenv_a,        &AudioEffectEnvelope::attack);
   attachAudioFunc(PARM_AENVa_HOLD     , &AU_Aenv_a,        &AudioEffectEnvelope::hold);
   attachAudioFunc(PARM_AENVa_DECAY    , &AU_Aenv_a,        &AudioEffectEnvelope::decay);
   attachAudioFunc(PARM_AENVa_SUSTAIN  , &AU_Aenv_a,        &AudioEffectEnvelope::sustain);
   attachAudioFunc(PARM_AENVa_RELEASE  , &AU_Aenv_a,        &AudioEffectEnvelope::release);
   attachAudioFunc(PARM_AENVa_AMOUNT   , &AU_mixer_output,  &AudioMixer4::gain, 1);

   attachAudioFunc(PARM_AENVb_ATTACK   , &AU_Aenv_b,        &AudioEffectEnvelope::attack);
   attachAudioFunc(PARM_AENVb_HOLD     , &AU_Aenv_b,        &AudioEffectEnvelope::hold);
   attachAudioFunc(PARM_AENVb_DECAY    , &AU_Aenv_b,        &AudioEffectEnvelope::decay);
   attachAudioFunc(PARM_AENVb_SUSTAIN  , &AU_Aenv_b,        &AudioEffectEnvelope::sustain);
   attachAudioFunc(PARM_AENVb_RELEASE  , &AU_Aenv_b,        &AudioEffectEnvelope::release);
   attachAudioFunc(PARM_AENVb_AMOUNT   , &AU_mixer_output,  &AudioMixer4::gain, 2);
}

void testParameters()
{
   PSConfig config;
   config.loadConfig("config.json");
   config.applyConfig();
   connectParameterTargets();


   Parameters[PARM_AENVa_ATTACK]->setValue(9);
   Parameters[PARM_AENVa_AMOUNT]->setValue(85);
   Parameters[PARM_AENVa_DECAY]->setValue(200);
   Parameters[PARM_AENVa_AMOUNT]->setValue(99);
}
