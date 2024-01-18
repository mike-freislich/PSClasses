// #include "Audio.h"
// #include <Wire.h>
// #include <SPI.h>
// #include <SD.h>
// #include <SerialFlash.h>

// GUItool: begin automatically generated code 2024.01.18

AudioSynthWaveformDc     voicePENVdc;    //xy=90,650
AudioSynthWaveformDc     voiceFENVdc;    //xy=138.99999237060547,540.1111259460449
AudioEffectEnvelope      osc2PENV;       //xy=161.77777099609375,713.5555572509766
AudioEffectEnvelope      osc1PENV;       //xy=162.66666412353516,592.9999771118164
AudioSynthWaveformDc     pitchBendDC;            //xy=283,824
AudioEffectEnvelope      filter2env;     //xy=323,1378
AudioEffectEnvelope      filter1env;     //xy=434,321
AudioMixer4              osc2FMmixer;    //xy=493,1059
AudioSynthWaveformModulated waveformRight;  //xy=493,1119
AudioSynthWaveformModulated waveformLeft;   //xy=497,564
AudioMixer4              osc1FMmixer;    //xy=497,622
AudioSynthWaveformDc     osc1XMODamt;    //xy=529,393
AudioEffectMultiply      multiplyOsc1XMOD; //xy=538,430
AudioSynthWaveformDc     osc2XMODamt;    //xy=537,1257
AudioEffectMultiply      multiplyOsc2XMOD; //xy=549,1212
AudioSynthWaveformDc     voiceRINGamt;   //xy=562,827
AudioMixer4              osc2AMmixer;    //xy=748,987
AudioMixer4              osc1AMmixer;    //xy=755,682
AudioEffectMultiply      osc2AMpost;     //xy=804,1072
AudioEffectMultiply      osc1AMpost;     //xy=833,596
AudioSynthWaveform       voiceRingModwave; //xy=858,826
AudioEffectMultiply      multiplyOsc1Ring; //xy=863,777
AudioEffectMultiply      mulitplyOsc2Ring; //xy=863,879
AudioMixer4              osc1waveMixer;  //xy=1056,554
AudioMixer4              osc2waveMixer;  //xy=1068,1098
AudioSynthNoiseWhite     noise1;         //xy=1117,813
AudioSynthNoisePink      pink1;          //xy=1117,848
AudioMixer4              filter2modMixer; //xy=1223,1294
AudioAmplifier           waveshapePreAmp2; //xy=1310.5555114746094,1130.6666202545166
AudioEffectWaveshaper    waveshape2;     //xy=1313.5555114746094,1093.6666202545166
AudioAmplifier           waveshapePreAmp1; //xy=1327.2222213745117,530.1110916137695
AudioMixer4              osc2ShaperBypassMixer;         //xy=1325.4443054199219,1031.9999523162842
AudioSynthWaveformDc     voiceAENVdc;    //xy=1328,839
AudioMixer4              osc1ShaperBypassMixer;         //xy=1341.666748046875,634.1110687255859
AudioEffectWaveshaper    waveshape1;     //xy=1353.2222213745117,567.1110916137695
AudioMixer4              filter1modMixer; //xy=1431,440
AudioEffectEnvelope      AENV1;          //xy=1481,800
AudioEffectEnvelope      AENV2;          //xy=1486,885
AudioEffectMultiply      AENV1post;      //xy=1599,729
AudioEffectMultiply      AENV2post;      //xy=1600,948
AudioFilterStateVariable filter1;        //xy=1628,514
AudioFilterLadder        ladder1;        //xy=1630.8888854980469,564.1111125946045
AudioFilterStateVariable filter2;        //xy=1639.0000228881836,1181.8888511657715
AudioFilterLadder        ladder2;        //xy=1640.0000228881836,1125.8888511657715
AudioMixer4              filter1blockMixer; //xy=1808,529
AudioMixer4              filter2blockMixer; //xy=1824.0000228881836,1170.8888511657715
AudioMixer4              voiceMainLeftmixer; //xy=1968,815
AudioMixer4              voiceMainRightmixer; //xy=1968,879
AudioAmplifier           voiceGainLeft;  //xy=2153.888946533203,744.2222146987915
AudioAmplifier           voiceGainRight; //xy=2153.6665954589844,961.8889036178589
AudioAnalyzePeak         peakRight;      //xy=2209.6665954589844,1007.8889036178589
AudioAnalyzePeak         peakLeft;       //xy=2221.888946533203,691.2222146987915
AudioOutputUSB           stereoOut;      //xy=2307.9997940063477,887.2221927642822
AudioMixer4              oscilloscopeMixer; //xy=2329.7775802612305,833.6665840148926
AudioConnection          patchCord1(voicePENVdc, osc1PENV);
AudioConnection          patchCord2(voicePENVdc, osc2PENV);
AudioConnection          patchCord3(voiceFENVdc, filter1env);
AudioConnection          patchCord4(voiceFENVdc, filter2env);
AudioConnection          patchCord5(osc2PENV, 0, osc2FMmixer, 0);
AudioConnection          patchCord6(osc1PENV, 0, osc1FMmixer, 0);
AudioConnection          patchCord7(pitchBendDC, 0, osc1FMmixer, 1);
AudioConnection          patchCord8(pitchBendDC, 0, osc2FMmixer, 1);
AudioConnection          patchCord9(filter2env, 0, filter2modMixer, 0);
AudioConnection          patchCord10(filter1env, 0, filter1modMixer, 0);
AudioConnection          patchCord11(osc2FMmixer, 0, waveformRight, 0);
AudioConnection          patchCord12(waveformRight, 0, osc2waveMixer, 0);
AudioConnection          patchCord13(waveformRight, 0, osc2AMpost, 0);
AudioConnection          patchCord14(waveformRight, 0, multiplyOsc2XMOD, 0);
AudioConnection          patchCord15(waveformLeft, 0, osc1waveMixer, 0);
AudioConnection          patchCord16(waveformLeft, 0, osc1AMpost, 0);
AudioConnection          patchCord17(waveformLeft, 0, multiplyOsc1XMOD, 0);
AudioConnection          patchCord18(osc1FMmixer, 0, waveformLeft, 0);
AudioConnection          patchCord19(osc1XMODamt, 0, multiplyOsc1XMOD, 1);
AudioConnection          patchCord20(multiplyOsc1XMOD, 0, osc2AMmixer, 0);
AudioConnection          patchCord21(osc2XMODamt, 0, multiplyOsc2XMOD, 1);
AudioConnection          patchCord22(multiplyOsc2XMOD, 0, osc1AMmixer, 0);
AudioConnection          patchCord23(voiceRINGamt, 0, multiplyOsc1Ring, 1);
AudioConnection          patchCord24(voiceRINGamt, 0, mulitplyOsc2Ring, 1);
AudioConnection          patchCord25(osc2AMmixer, 0, osc2AMpost, 1);
AudioConnection          patchCord26(osc1AMmixer, 0, osc1AMpost, 1);
AudioConnection          patchCord27(osc2AMpost, 0, osc2waveMixer, 1);
AudioConnection          patchCord28(osc1AMpost, 0, osc1waveMixer, 1);
AudioConnection          patchCord29(voiceRingModwave, 0, multiplyOsc1Ring, 0);
AudioConnection          patchCord30(voiceRingModwave, 0, mulitplyOsc2Ring, 0);
AudioConnection          patchCord31(multiplyOsc1Ring, 0, osc1AMmixer, 1);
AudioConnection          patchCord32(mulitplyOsc2Ring, 0, osc2AMmixer, 1);
AudioConnection          patchCord33(osc1waveMixer, waveshapePreAmp1);
AudioConnection          patchCord34(osc1waveMixer, 0, osc1ShaperBypassMixer, 0);
AudioConnection          patchCord35(osc2waveMixer, waveshapePreAmp2);
AudioConnection          patchCord36(osc2waveMixer, 0, osc2ShaperBypassMixer, 0);
AudioConnection          patchCord37(noise1, 0, osc1waveMixer, 2);
AudioConnection          patchCord38(noise1, 0, osc2waveMixer, 2);
AudioConnection          patchCord39(pink1, 0, osc1waveMixer, 3);
AudioConnection          patchCord40(pink1, 0, osc2waveMixer, 3);
AudioConnection          patchCord41(filter2modMixer, 0, ladder2, 1);
AudioConnection          patchCord42(filter2modMixer, 0, filter2, 1);
AudioConnection          patchCord43(waveshapePreAmp2, waveshape2);
AudioConnection          patchCord44(waveshape2, 0, osc2ShaperBypassMixer, 1);
AudioConnection          patchCord45(waveshapePreAmp1, waveshape1);
AudioConnection          patchCord46(osc2ShaperBypassMixer, 0, ladder2, 0);
AudioConnection          patchCord47(osc2ShaperBypassMixer, 0, filter2, 0);
AudioConnection          patchCord48(voiceAENVdc, AENV1);
AudioConnection          patchCord49(voiceAENVdc, AENV2);
AudioConnection          patchCord50(osc1ShaperBypassMixer, 0, filter1, 0);
AudioConnection          patchCord51(osc1ShaperBypassMixer, 0, ladder1, 0);
AudioConnection          patchCord52(waveshape1, 0, osc1ShaperBypassMixer, 1);
AudioConnection          patchCord53(filter1modMixer, 0, filter1, 1);
AudioConnection          patchCord54(filter1modMixer, 0, ladder1, 1);
AudioConnection          patchCord55(AENV1, 0, AENV1post, 1);
AudioConnection          patchCord56(AENV2, 0, AENV2post, 1);
AudioConnection          patchCord57(AENV1post, 0, voiceMainLeftmixer, 0);
AudioConnection          patchCord58(AENV2post, 0, voiceMainRightmixer, 0);
AudioConnection          patchCord59(filter1, 0, filter1blockMixer, 0);
AudioConnection          patchCord60(filter1, 1, filter1blockMixer, 1);
AudioConnection          patchCord61(filter1, 2, filter1blockMixer, 2);
AudioConnection          patchCord62(ladder1, 0, filter1blockMixer, 3);
AudioConnection          patchCord63(filter2, 0, filter2blockMixer, 0);
AudioConnection          patchCord64(filter2, 1, filter2blockMixer, 1);
AudioConnection          patchCord65(filter2, 2, filter2blockMixer, 2);
AudioConnection          patchCord66(ladder2, 0, filter2blockMixer, 3);
AudioConnection          patchCord67(filter1blockMixer, 0, AENV1post, 0);
AudioConnection          patchCord68(filter2blockMixer, 0, AENV2post, 0);
AudioConnection          patchCord69(voiceMainLeftmixer, voiceGainLeft);
AudioConnection          patchCord70(voiceMainRightmixer, voiceGainRight);
AudioConnection          patchCord71(voiceGainLeft, peakLeft);
AudioConnection          patchCord72(voiceGainLeft, 0, stereoOut, 0);
AudioConnection          patchCord73(voiceGainLeft, 0, oscilloscopeMixer, 0);
AudioConnection          patchCord74(voiceGainRight, 0, stereoOut, 1);
AudioConnection          patchCord75(voiceGainRight, peakRight);
AudioConnection          patchCord76(voiceGainRight, 0, oscilloscopeMixer, 1);
// GUItool: end automatically generated code
