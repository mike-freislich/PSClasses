#pragma once
// #include "AudioShard.h"
#include "AudioMockObjects.h"
// #include <Wire.h>
// #include <SPI.h>
// #include <SD.h>
// #include <SerialFlash.h>

// GUItool: begin automatically generated code 2024.01.18
AudioSynthWaveformModulated auWAVE_a;   // xy=497,564
AudioSynthWaveformModulated auWAVE_b;   // xy=493,1119
AudioSynthWaveformDc auDC_PITCHENV;     // xy=90,650
AudioEffectEnvelope auENV_PITCH_a;      // xy=162.66666412353516,592.9999771118164
AudioEffectEnvelope auENV_PITCH_b;      // xy=161.77777099609375,713.5555572509766
AudioSynthWaveformDc auDC_FILTERENV;    // xy=138.99999237060547,540.1111259460449
AudioEffectEnvelope auENV_FILTER_a;     // xy=434,321
AudioEffectEnvelope auENV_FILTER_b;     // xy=323,1378
AudioSynthWaveformDc auDC_AMPENV;       // xy=1328,839
AudioEffectEnvelope auENV_AMP_a;        // xy=1481,800
AudioEffectEnvelope auENV_AMP_b;        // xy=1486,885
AudioMixer4 auMIXER_FM_a;               // xy=497,622
AudioMixer4 auMIXER_FM_b;               // xy=493,1059
AudioSynthWaveformDc auDC_PITCHBEND;    // xy=283,824
AudioEffectMultiply auMULT_XMOD_a;      // xy=538,430
AudioEffectMultiply auMULT_XMOD_b;      // xy=549,1212
AudioSynthWaveformDc auDC_XMOD_a;       // xy=529,393
AudioSynthWaveformDc auDC_XMOD_b;       // xy=537,1257
AudioMixer4 auMIXER_AM_a;               // xy=755,682
AudioMixer4 auMIXER_AM_b;               // xy=748,987
AudioEffectMultiply auMULT_AM_POST_a;   // xy=833,596
AudioEffectMultiply auMULT_AM_POST_b;   // xy=804,1072
AudioSynthWaveformDc auDC_RINGMOD;      // xy=562,827
AudioSynthWaveform auWAVE_RINGMOD;      // xy=858,826
AudioEffectMultiply au_MULT_ring_a;     // xy=863,777
AudioEffectMultiply au_MULT_ring_b;     // xy=863,879
AudioMixer4 auMIXER_WAVE_a;             // xy=1056,554
AudioMixer4 auMIXER_WAVE_b;             // xy=1068,1098
AudioSynthNoiseWhite auNOISE_WHITE;     // xy=1117,813
AudioSynthNoisePink auNOISE_PINK;       // xy=1117,848
AudioMixer4 auMIXER_FILTERMOD_a;        // xy=1431,440
AudioMixer4 auMIXER_FILTERMOD_b;        // xy=1223,1294
AudioEffectWaveshaper auSHAPER_a;       // xy=1353.2222213745117,567.1110916137695
AudioAmplifier auAMP_SHAPER_PREAMP_a;   // xy=1327.2222213745117,530.1110916137695
AudioMixer4 auMIXER_SHAPER_BYPASS_a;    // xy=1341.666748046875,634.1110687255859
AudioEffectWaveshaper auSHAPER_b;       // xy=1313.5555114746094,1093.6666202545166
AudioAmplifier auAMP_SHAPER_PREAMP_b;   // xy=1310.5555114746094,1130.6666202545166
AudioMixer4 auMIXER_SHAPER_BYPASS_b;    // xy=1325.4443054199219,1031.9999523162842
AudioEffectMultiply auMULT_AENV_POST_a; // xy=1599,729
AudioEffectMultiply auMULT_AENV_POST_b; // xy=1600,948
AudioFilterStateVariable auFILTER_SV_a; // xy=1628,514
AudioFilterLadder auFILTER_LADDER_a;    // xy=1630.8888854980469,564.1111125946045
AudioFilterStateVariable auFILTER_SV_b; // xy=1639.0000228881836,1181.8888511657715
AudioFilterLadder auFILTER_LADDER_b;    // xy=1640.0000228881836,1125.8888511657715
AudioMixer4 auMIXER_FILTER_BLOCK_a;     // xy=1808,529
AudioMixer4 auMIXER_FILTER_BLOCK_b;     // xy=1824.0000228881836,1170.8888511657715
AudioMixer4 auMIXER_MAIN_a;             // xy=1968,815
AudioMixer4 auMIXER_MAIN_b;             // xy=1968,879
AudioAmplifier auAMP_WAVEGAIN_a;        // xy=2153.888946533203,744.2222146987915
AudioAmplifier auAMP_WAVEGAIN_b;        // xy=2153.6665954589844,961.8889036178589
AudioAnalyzePeak auPEAK_a;              // xy=2221.888946533203,691.2222146987915
AudioAnalyzePeak auPEAK_b;              // xy=2209.6665954589844,1007.8889036178589
AudioOutputUSB auSTEREO_OUT;            // xy=2307.9997940063477,887.2221927642822
AudioMixer4 auMIXER_SCOPE;              // xy=2329.7775802612305,833.6665840148926
AudioConnection patchCord1(auDC_PITCHENV, auENV_PITCH_a);
AudioConnection patchCord2(auDC_PITCHENV, auENV_PITCH_b);
AudioConnection patchCord3(auDC_FILTERENV, auENV_FILTER_a);
AudioConnection patchCord4(auDC_FILTERENV, auENV_FILTER_b);
AudioConnection patchCord5(auENV_PITCH_b, 0, auMIXER_FM_b, 0);
AudioConnection patchCord6(auENV_PITCH_a, 0, auMIXER_FM_a, 0);
AudioConnection patchCord7(auDC_PITCHBEND, 0, auMIXER_FM_a, 1);
AudioConnection patchCord8(auDC_PITCHBEND, 0, auMIXER_FM_b, 1);
AudioConnection patchCord9(auENV_FILTER_b, 0, auMIXER_FILTERMOD_b, 0);
AudioConnection patchCord10(auENV_FILTER_a, 0, auMIXER_FILTERMOD_a, 0);
AudioConnection patchCord11(auMIXER_FM_b, 0, auWAVE_b, 0);
AudioConnection patchCord12(auWAVE_b, 0, auMIXER_WAVE_b, 0);
AudioConnection patchCord13(auWAVE_b, 0, auMULT_AM_POST_b, 0);
AudioConnection patchCord14(auWAVE_b, 0, auMULT_XMOD_b, 0);
AudioConnection patchCord15(auWAVE_a, 0, auMIXER_WAVE_a, 0);
AudioConnection patchCord16(auWAVE_a, 0, auMULT_AM_POST_a, 0);
AudioConnection patchCord17(auWAVE_a, 0, auMULT_XMOD_a, 0);
AudioConnection patchCord18(auMIXER_FM_a, 0, auWAVE_a, 0);
AudioConnection patchCord19(auDC_XMOD_a, 0, auMULT_XMOD_a, 1);
AudioConnection patchCord20(auMULT_XMOD_a, 0, auMIXER_AM_b, 0);
AudioConnection patchCord21(auDC_XMOD_b, 0, auMULT_XMOD_b, 1);
AudioConnection patchCord22(auMULT_XMOD_b, 0, auMIXER_AM_a, 0);
AudioConnection patchCord23(auDC_RINGMOD, 0, au_MULT_ring_a, 1);
AudioConnection patchCord24(auDC_RINGMOD, 0, au_MULT_ring_b, 1);
AudioConnection patchCord25(auMIXER_AM_b, 0, auMULT_AM_POST_b, 1);
AudioConnection patchCord26(auMIXER_AM_a, 0, auMULT_AM_POST_a, 1);
AudioConnection patchCord27(auMULT_AM_POST_b, 0, auMIXER_WAVE_b, 1);
AudioConnection patchCord28(auMULT_AM_POST_a, 0, auMIXER_WAVE_a, 1);
AudioConnection patchCord29(auWAVE_RINGMOD, 0, au_MULT_ring_a, 0);
AudioConnection patchCord30(auWAVE_RINGMOD, 0, au_MULT_ring_b, 0);
AudioConnection patchCord31(au_MULT_ring_a, 0, auMIXER_AM_a, 1);
AudioConnection patchCord32(au_MULT_ring_b, 0, auMIXER_AM_b, 1);
AudioConnection patchCord33(auMIXER_WAVE_a, auAMP_SHAPER_PREAMP_a);
AudioConnection patchCord34(auMIXER_WAVE_a, 0, auMIXER_SHAPER_BYPASS_a, 0);
AudioConnection patchCord35(auMIXER_WAVE_b, auAMP_SHAPER_PREAMP_b);
AudioConnection patchCord36(auMIXER_WAVE_b, 0, auMIXER_SHAPER_BYPASS_b, 0);
AudioConnection patchCord37(auNOISE_WHITE, 0, auMIXER_WAVE_a, 2);
AudioConnection patchCord38(auNOISE_WHITE, 0, auMIXER_WAVE_b, 2);
AudioConnection patchCord39(auNOISE_PINK, 0, auMIXER_WAVE_a, 3);
AudioConnection patchCord40(auNOISE_PINK, 0, auMIXER_WAVE_b, 3);
AudioConnection patchCord41(auMIXER_FILTERMOD_b, 0, auFILTER_LADDER_b, 1);
AudioConnection patchCord42(auMIXER_FILTERMOD_b, 0, auFILTER_SV_b, 1);
AudioConnection patchCord43(auAMP_SHAPER_PREAMP_b, auSHAPER_b);
AudioConnection patchCord44(auSHAPER_b, 0, auMIXER_SHAPER_BYPASS_b, 1);
AudioConnection patchCord45(auAMP_SHAPER_PREAMP_a, auSHAPER_a);
AudioConnection patchCord46(auMIXER_SHAPER_BYPASS_b, 0, auFILTER_LADDER_b, 0);
AudioConnection patchCord47(auMIXER_SHAPER_BYPASS_b, 0, auFILTER_SV_b, 0);
AudioConnection patchCord48(auDC_AMPENV, auENV_AMP_a);
AudioConnection patchCord49(auDC_AMPENV, auENV_AMP_b);
AudioConnection patchCord50(auMIXER_SHAPER_BYPASS_a, 0, auFILTER_SV_a, 0);
AudioConnection patchCord51(auMIXER_SHAPER_BYPASS_a, 0, auFILTER_LADDER_a, 0);
AudioConnection patchCord52(auSHAPER_a, 0, auMIXER_SHAPER_BYPASS_a, 1);
AudioConnection patchCord53(auMIXER_FILTERMOD_a, 0, auFILTER_SV_a, 1);
AudioConnection patchCord54(auMIXER_FILTERMOD_a, 0, auFILTER_LADDER_a, 1);
AudioConnection patchCord55(auENV_AMP_a, 0, auMULT_AENV_POST_a, 1);
AudioConnection patchCord56(auENV_AMP_b, 0, auMULT_AENV_POST_b, 1);
AudioConnection patchCord57(auMULT_AENV_POST_a, 0, auMIXER_MAIN_a, 0);
AudioConnection patchCord58(auMULT_AENV_POST_b, 0, auMIXER_MAIN_b, 0);
AudioConnection patchCord59(auFILTER_SV_a, 0, auMIXER_FILTER_BLOCK_a, 0);
AudioConnection patchCord60(auFILTER_SV_a, 1, auMIXER_FILTER_BLOCK_a, 1);
AudioConnection patchCord61(auFILTER_SV_a, 2, auMIXER_FILTER_BLOCK_a, 2);
AudioConnection patchCord62(auFILTER_LADDER_a, 0, auMIXER_FILTER_BLOCK_a, 3);
AudioConnection patchCord63(auFILTER_SV_b, 0, auMIXER_FILTER_BLOCK_b, 0);
AudioConnection patchCord64(auFILTER_SV_b, 1, auMIXER_FILTER_BLOCK_b, 1);
AudioConnection patchCord65(auFILTER_SV_b, 2, auMIXER_FILTER_BLOCK_b, 2);
AudioConnection patchCord66(auFILTER_LADDER_b, 0, auMIXER_FILTER_BLOCK_b, 3);
AudioConnection patchCord67(auMIXER_FILTER_BLOCK_a, 0, auMULT_AENV_POST_a, 0);
AudioConnection patchCord68(auMIXER_FILTER_BLOCK_b, 0, auMULT_AENV_POST_b, 0);
AudioConnection patchCord69(auMIXER_MAIN_a, auAMP_WAVEGAIN_a);
AudioConnection patchCord70(auMIXER_MAIN_b, auAMP_WAVEGAIN_b);
AudioConnection patchCord71(auAMP_WAVEGAIN_a, auPEAK_a);
AudioConnection patchCord72(auAMP_WAVEGAIN_a, 0, auSTEREO_OUT, 0);
AudioConnection patchCord73(auAMP_WAVEGAIN_a, 0, auMIXER_SCOPE, 0);
AudioConnection patchCord74(auAMP_WAVEGAIN_b, 0, auSTEREO_OUT, 1);
AudioConnection patchCord75(auAMP_WAVEGAIN_b, auPEAK_b);
AudioConnection patchCord76(auAMP_WAVEGAIN_b, 0, auMIXER_SCOPE, 1);
// GUItool: end automatically generated code