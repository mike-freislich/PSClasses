#pragma once
#include "Module.h"
#include "AUMapping.h"

#define PARAMS_FILTERBLOCK PARM_FILTER_RES, PARM_FILTER_FREQ, PARM_FILTER_OCTAVES, PARM_FILTER_TYPE, PARM_FILTER_POSTGAIN

namespace PS
{
    enum FilterType
    {
        filterLowPass = 0,
        filterBandPass = 1,
        filterHighPass = 2,
        filterLadder = 3
    };

    struct ModuleFilterBlockParameters
    {
        std::string resonance, frequency, octaves, filterType, postGain;
        ModuleFilterBlockParameters(
            const std::string &resonance,
            const std::string &frequency,
            const std::string &octaves,
            const std::string &filterType,
            const std::string &postGain)
            : resonance(resonance), frequency(frequency), octaves(octaves), filterType(filterType), postGain(postGain) {}
    };

    class ModuleFilterBlock : public Module
    {
    public:
        ModuleFilterBlock()
        {
            typeName = "ModuleFilterBlock";
            _mixers = {&auMIXER_FILTER_BLOCK_V1, &auMIXER_FILTER_BLOCK_V2, &auMIXER_FILTER_BLOCK_V3, &auMIXER_FILTER_BLOCK_V4};
            _postAmps = {&auAMP_POST_FILTER_V1, &auAMP_POST_FILTER_V2, &auAMP_POST_FILTER_V3, &auAMP_POST_FILTER_V4};
            _svfilters = {&auFILTER_SV_V1, &auFILTER_SV_V2, &auFILTER_SV_V3, &auFILTER_SV_V4};
            _ladderFilters = {&auFILTER_LADDER_V1, &auFILTER_LADDER_V2, &auFILTER_LADDER_V3, &auFILTER_LADDER_V4};
        }
        ~ModuleFilterBlock() {
            _postAmps.clear();
            _ladderFilters.clear();
            _svfilters.clear();
            _mixers.clear();
        }

        static ModuleFilterBlock *create(const char *key, const char *displayName, const ModuleFilterBlockParameters &p)
        {
            ModuleFilterBlock *newMod = Module::create<ModuleFilterBlock>(key, displayName);
            newMod->addParameters(p);
            return newMod;
        }

        ObjectType getType() override { return ObjectType::TModuleFilterBlock; }

        void addParameters(const ModuleFilterBlockParameters &p)
        {
            _postGain = addParameter(Parameters[p.postGain]);
            _resonance = addParameter(Parameters[p.resonance]);
            _freq = addParameter(Parameters[p.frequency]);
            _octaves = addParameter(Parameters[p.octaves]);
            _filterType = addParameter(Parameters[p.filterType]);
        }

        bool update() override
        {
            bool result;

            if (_postGain->changed(true))
            {
                for (auto amp : _postAmps)
                    amp->gain(_postGain->getValue());
                result = true;
            }

            if (_resonance->changed(true))
            {
                float q = _resonance->getValue();
                for (auto svf : _svfilters)
                    svf->resonance(q);
                for (auto ladder : _ladderFilters)
                    ladder->resonance(q);
                result = true;
            }

            if (_freq->changed(true))
            {
                float f = _freq->getValue();
                for (auto svf : _svfilters)
                    svf->frequency(f);
                for (auto ladder : _ladderFilters)
                    ladder->frequency(f);
            }

            if (_octaves->changed(true))
            {
                float o = _octaves->getValue();
                for (auto svf : _svfilters)
                    svf->octaveControl(o);
                for (auto ladder : _ladderFilters)
                    ladder->octaveControl(o);
            }

            if (_filterType->changed(true))
            {
                uint8_t t = _filterType->getValue();                
                for (auto mixer:  _mixers)
                {
                    for (uint8_t c = 0; c < 4; c ++)
                    {
                        if (c == t)
                            mixer->gain(c, 1);
                        else
                            mixer->gain(c, 0);
                    }
                }                
            }

            return result;
        }
    protected:
        Parameter *_postGain, *_resonance, *_freq, *_octaves, *_filterType;
        std::vector<AudioAmplifier *> _postAmps;
        std::vector<AudioFilterStateVariable *> _svfilters;
        std::vector<AudioFilterLadder *> _ladderFilters;
        std::vector<AudioMixer4 *> _mixers;
    };
}