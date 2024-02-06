#pragma once
#include "PSScene.h"
#include "PSMStereoVoiceMixer.h"

class PSSceneStereoVoiceMixer : public PSScene
{
public:
    PSSceneStereoVoiceMixer() : PSScene()
    {
        typeName = "PSSceneStereoVoiceMixer";
        addModule(Modules[MOD_MIXER_MAIN]);
    }
    ~PSSceneStereoVoiceMixer() override {}

    void drawModules() override
    {
        for (auto &module : _modules.getData())
        {
            if (PSMStereoVoiceMixer *mixer = dynamic_cast<PSMStereoVoiceMixer *>(module.second))
            {
                for (uint8_t voice = 0; voice < VOICES; voice++)
                {
                    float left, right;
                    float gain = mixer->getVoiceGain(voice);
                    float pan = mixer->getVoicePan(voice);
                    mixer->getStereoGainLR(gain, pan, left, right);
                    printf("Voice %d : (GAIN %3d) (PAN %3d) (L %3d) (R %3d)\n",
                           voice, (int)(100 * gain), (int)(100 * pan), (int)(100 * left), (int)(100 * right));
                }
                // printf("Envelope [%s] : (atk %7.2f)  (hld %7.2f)  (dec %7.2f)  (sus %2.2f)  (rel %7.2f)  (amt %2.2f) (lfo-s %2.0f) (lfo-lvl %2.2f) (lfo-freq %2.2f) \n",
                //        e->displayName.c_str(),
                //        e->getAttack(), e->getHold(), e->getDecay(), e->getSustain(), e->getRelease(), e->getAmount() * e->invertMultiplier(), e->getLFOShape(), e->getLFOAmplitude(), e->getLFOFreq());
            }
        }
    }
};