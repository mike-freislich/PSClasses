#pragma once
#include "LXParameterList.h"
#include "LXModuleList.h"
#include "LXControllerList.h"
#include "AUMapping.h"

void storeParameter(const char *parm) { printf("storing : %s\n", parm); }

FLASHMEM void initParameters()
{
    // master gain
    Parameters.add(ParmKeys::master_gain)->setRange(0, 1)->setValue(1.0);
    Parameters.add(ParmKeys::master_pan)->setRange(0, 1)->setValue(0.5);
    // part mixer
    Parameters.add(ParmKeys::partpan_ab)->setRange(0, 1)->setValue(0.5);
    // voice mixer
    Parameters.add(ParmKeys::voice_gain0)->setRange(0, 1)->setValue(0.8);
    Parameters.add(ParmKeys::voice_gain1)->setRange(0, 1)->setValue(0.8);
    Parameters.add(ParmKeys::voice_gain2)->setRange(0, 1)->setValue(0.8);
    Parameters.add(ParmKeys::voice_gain3)->setRange(0, 1)->setValue(0.8);
    Parameters.add(ParmKeys::voice_pan0)->setRange(0, 1)->setValue(0.5);
    Parameters.add(ParmKeys::voice_pan1)->setRange(0, 1)->setValue(0.5);
    Parameters.add(ParmKeys::voice_pan2)->setRange(0, 1)->setValue(0.5);
    Parameters.add(ParmKeys::voice_pan3)->setRange(0, 1)->setValue(0.5);
    // pitch modulator
    Parameters.add(ParmKeys::penv_amount)->setRange(0, 1)->setValue(0.5);
    Parameters.add(ParmKeys::penv_attack)->setRange(0, 10000)->setValue(5);
    Parameters.add(ParmKeys::penv_hold)->setRange(0, 10000)->setValue(0);
    Parameters.add(ParmKeys::penv_decay)->setRange(0, 10000)->setValue(120);
    Parameters.add(ParmKeys::penv_sustain)->setRange(0, 1)->setValue(1);
    Parameters.add(ParmKeys::penv_release)->setRange(0, 10000)->setValue(120);
    Parameters.add(ParmKeys::penv_invert)->setRange(0, 1)->setValue(0);
    Parameters.add(ParmKeys::plfo_amount)->setRange(0, 1)->setValue(1);
    Parameters.add(ParmKeys::plfo_freq)->setRange(0, 20000)->setValue(1);
    Parameters.add(ParmKeys::plfo_shape)->setRange(0, 11)->setValue(0);
    Parameters.add(ParmKeys::pitch_bend)->setRange(0, 16129)->setValue(8064);
    // amplitude modulator
    Parameters.add(ParmKeys::aenv_amount)->setRange(0, 1)->setValue(0.5);
    Parameters.add(ParmKeys::aenv_attack)->setRange(0, 10000)->setValue(5);
    Parameters.add(ParmKeys::aenv_hold)->setRange(0, 10000)->setValue(0);
    Parameters.add(ParmKeys::aenv_decay)->setRange(0, 10000)->setValue(120);
    Parameters.add(ParmKeys::aenv_sustain)->setRange(0, 1)->setValue(1);
    Parameters.add(ParmKeys::aenv_release)->setRange(0, 10000)->setValue(120);
    Parameters.add(ParmKeys::aenv_invert)->setRange(0, 1)->setValue(0);
    Parameters.add(ParmKeys::alfo_amount)->setRange(0, 1)->setValue(1);
    Parameters.add(ParmKeys::alfo_freq)->setRange(0, 20000)->setValue(1);
    Parameters.add(ParmKeys::alfo_shape)->setRange(0, 11)->setValue(0);
    Parameters.add(ParmKeys::amp_bend)->setRange(0, 16129)->setValue(8064);
    // frequency modulator
    Parameters.add(ParmKeys::fenv_amount)->setRange(0, 1)->setValue(0.5);
    Parameters.add(ParmKeys::fenv_attack)->setRange(0, 10000)->setValue(5);
    Parameters.add(ParmKeys::fenv_hold)->setRange(0, 10000)->setValue(0);
    Parameters.add(ParmKeys::fenv_decay)->setRange(0, 10000)->setValue(120);
    Parameters.add(ParmKeys::fenv_sustain)->setRange(0, 1)->setValue(1);
    Parameters.add(ParmKeys::fenv_release)->setRange(0, 10000)->setValue(120);
    Parameters.add(ParmKeys::fenv_invert)->setRange(0, 1)->setValue(0);
    Parameters.add(ParmKeys::flfo_amount)->setRange(0, 1)->setValue(1);
    Parameters.add(ParmKeys::flfo_freq)->setRange(0, 20000)->setValue(1);
    Parameters.add(ParmKeys::flfo_shape)->setRange(0, 11)->setValue(0);
    Parameters.add(ParmKeys::filter_bend)->setRange(0, 16129)->setValue(8064);
    // oscillators
    Parameters.add(ParmKeys::osc_a_shape);
    Parameters.add(ParmKeys::osc_a_amp)->setRange(0, 1)->setValue(1.0);
    Parameters.add(ParmKeys::osc_a_freq)->setRange(0, 20000)->setValue(1);
    Parameters.add(ParmKeys::osc_a_detune);
    Parameters.add(ParmKeys::osc_b_shape);
    Parameters.add(ParmKeys::osc_b_amp)->setRange(0, 1)->setValue(1.0);
    Parameters.add(ParmKeys::osc_b_freq)->setRange(0, 20000)->setValue(1);
    Parameters.add(ParmKeys::osc_b_detune);
    // PWM
    Parameters.add(ParmKeys::pwm_a_shape);
    Parameters.add(ParmKeys::pwm_a_freq)->setRange(0, 20000)->setValue(1);
    Parameters.add(ParmKeys::pwm_a_gain)->setRange(0, 1)->setValue(1.0);
    Parameters.add(ParmKeys::pwm_b_shape);
    Parameters.add(ParmKeys::pwm_b_freq)->setRange(0, 20000)->setValue(1);
    Parameters.add(ParmKeys::pwm_b_gain)->setRange(0, 1)->setValue(1.0);
    // XMod
    Parameters.add(ParmKeys::xmod_amount)->setRange(0, 1)->setValue(1.0);
    // RingMod
    Parameters.add(ParmKeys::ring_shape);
    Parameters.add(ParmKeys::ring_freq)->setRange(0, 20000)->setValue(1);
    ;
    Parameters.add(ParmKeys::ring_level)->setRange(0, 1)->setValue(1.0);
    // Waveshaper
    Parameters.add(ParmKeys::shaper_pregain)->setRange(0, 2)->setValue(1.0);
    Parameters.add(ParmKeys::shaper_curve);
    Parameters.add(ParmKeys::shaper_bypass);
    // filter
    Parameters.add(ParmKeys::filter_type);
    Parameters.add(ParmKeys::filter_freq)->setRange(0, 20000)->setValue(1);
    Parameters.add(ParmKeys::filter_res);
    Parameters.add(ParmKeys::filter_octaves);
    Parameters.add(ParmKeys::filter_postgain)->setRange(0, 2)->setValue(1.0);
    // noise
    Parameters.add(ParmKeys::noise_level)->setRange(0,1)->setValue(0);
    Parameters.add(ParmKeys::noise_type)->setRange(0,1)->setValue(0);

    // buttons
    Parameters.add(ParmKeys::pressedShift)->setRange(0,1)->setValue(0);
    Parameters.add(ParmKeys::pressedEnter)->setRange(0,1)->setValue(0);
    
    // SERIALIZE -----
    Parameters.serialize(&storeParameter);
}

FLASHMEM void initModules()
{
    // ModulatorBanks
    Modules.add<LXEnvModulatorBank>(ModKeys::AEnvModulator)
        ->attachParameters<LXEnvModulatorBank>(
            {aenv_attack, aenv_hold, aenv_decay, aenv_sustain, aenv_release, aenv_amount, aenv_invert, amp_bend,
             alfo_amount, alfo_freq, alfo_shape})
        ->attachEnvelopes({&auENV_AMP_V1, &auENV_AMP_V2, &auENV_AMP_V3, &auENV_AMP_V4})
        ->attachAmountDC(&auDC_AMPENV)
        ->attachLFOWave(&auLFO_AMP);
    Modules.add<LXEnvModulatorBank>(ModKeys::FEnvModulator)
        ->attachParameters<LXEnvModulatorBank>(
            {fenv_attack, fenv_hold, fenv_decay, fenv_sustain, fenv_release, fenv_amount, fenv_invert, filter_bend,
             flfo_amount, flfo_freq, flfo_shape})
        ->attachEnvelopes({&auENV_FILTER_V1, &auENV_FILTER_V2, &auENV_FILTER_V3, &auENV_FILTER_V4})
        ->attachAmountDC(&auDC_FILTERENV)
        ->attachLFOWave(&auLFO_FILTER);
    Modules.add<LXEnvModulatorBank>(ModKeys::PEnvModulator)
        ->attachParameters<LXEnvModulatorBank>(
            {penv_attack, penv_hold, penv_decay, penv_sustain, penv_release, penv_amount, penv_invert, pitch_bend,
             plfo_amount, plfo_freq, plfo_shape})
        ->attachEnvelopes({&auENV_PITCH_V1, &auENV_PITCH_V2, &auENV_PITCH_V3, &auENV_PITCH_V4})
        ->attachAmountDC(&auDC_PITCHENV)
        ->attachBendDC(&auDC_PITCHBEND)
        ->attachLFOWave(&auLFO_PITCH);

    // PWM
    Modules.add<LXPulseWidthMod>(ModKeys::PulseWidthModA)
        ->attachParameters<LXPulseWidthMod>({pwm_a_freq, pwm_a_gain, pwm_a_shape})
        ->attachAmp(&auAMP_PWM_a)
        ->attachPWMWave(&auWAVE_PWM_a);
    Modules.add<LXPulseWidthMod>(ModKeys::PulseWidthModB)
        ->attachParameters<LXPulseWidthMod>({pwm_b_freq, pwm_b_gain, pwm_b_shape})
        ->attachAmp(&auAMP_PWM_b)
        ->attachPWMWave(&auWAVE_PWM_b);

    // Oscillators
    Modules.add<LXOscillator>(ModKeys::OscillatorA)
        ->attachParameters<LXOscillator>({osc_a_amp, osc_a_detune, osc_a_freq, osc_a_shape})
        ->attachAudioUnits({&auDCO_V1a, &auDCO_V2a, &auDCO_V3a, &auDCO_V4a});
    Modules.add<LXOscillator>(ModKeys::OscillatorB)
        ->attachParameters<LXOscillator>({osc_b_amp, osc_b_detune, osc_b_freq, osc_b_shape})
        ->attachAudioUnits({&auDCO_v1b, &auDCO_v2b, &auDCO_v3b, &auDCO_v4b});

    // Global modules
    Modules.add<LXCrossModulation>(ModKeys::XModulator);
    Modules.add<LXRingModulation>(ModKeys::RingMod);
    Modules.add<LXFilterBank>(ModKeys::FilterBank);
    Modules.add<LXNoiseGen>(ModKeys::NoiseGen);
    Modules.add<LXPartMixer>(ModKeys::PartMixer);
    Modules.add<LXWaveShaper>(ModKeys::Shaper);
    Modules.add<LXVoiceMixer>(ModKeys::VoiceMixer);
}


FLASHMEM void initControllers()
{
    Controllers.add<LXPotentiometer>(ContKeys::pot1)->attachParameters<LXPotentiometer>({aenv_attack, penv_attack, fenv_attack});        
    Controllers.add<LXPotentiometer>(ContKeys::pot2)->attachParameters<LXPotentiometer>({aenv_hold, penv_hold, fenv_hold});
    Controllers.add<LXPotentiometer>(ContKeys::pot3)->attachParameters<LXPotentiometer>({aenv_decay, penv_decay, fenv_decay});
    Controllers.add<LXPotentiometer>(ContKeys::pot4)->attachParameters<LXPotentiometer>({aenv_sustain, penv_sustain, fenv_sustain});
    Controllers.add<LXPotentiometer>(ContKeys::pot5)->attachParameters<LXPotentiometer>({aenv_release, penv_release, fenv_release});
    Controllers.add<LXButton>(ContKeys::btnShift)->attachParameters<LXButton>({pressedShift});
    Controllers.add<LXButton>(ContKeys::btnEnter)->attachParameters<LXButton>({pressedEnter});
    Controllers.add<LXRotary>(ContKeys::rotA);
}