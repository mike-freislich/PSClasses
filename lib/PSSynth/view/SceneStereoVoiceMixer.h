#pragma once
#include "Scene.h"
#include "PSMStereoVoiceMixer.h"

namespace ps
{
    class SceneStereoVoiceMixer : public Scene
    {
    public:
        SceneStereoVoiceMixer() : Scene()
        {
            typeName = "SceneStereoVoiceMixer";
            addModule(Modules[MOD_MIXER_MAIN]);
        }
        ~SceneStereoVoiceMixer() override {}

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
                }
            }
        }
    };

}