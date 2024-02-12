#pragma once

#ifdef __ARM_ARCH_7EM__
#include <Audio.h>
#else
#include "AudioStub.h"
#endif

// #include <Wire.h>
// #include <SPI.h>
// #include <SD.h>
// #include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     auDC_PITCHENV;  //xy=391.10931396484375,1512.1069087982178
AudioEffectEnvelope      auENV_PITCH_V2;      //xy=446.5279083251953,1608.6111726760864
AudioEffectEnvelope      auENV_PITCH_V1;  //xy=447.4743118286133,1573.1426811218262
AudioEffectEnvelope      auENV_PITCH_V3;      //xy=447.6390151977539,1643.0555629730225
AudioEffectEnvelope      auENV_PITCH_V4;      //xy=447.63899993896484,1677.5000367164612
AudioSynthWaveform       auWAVE_PWM_b;      //xy=588.3332824707031,2126.6665058135986
AudioSynthWaveform       auWAVE_PWM_a;      //xy=624.1669387817383,1123.9582688063383
AudioSynthWaveformDc     auDC_PITCHBEND; //xy=681.9108734130859,1639.4282474517822
AudioAmplifier           auAMP_PWM_b;           //xy=773.7500114440918,2126.250027656555
AudioAmplifier           auAMP_PWM_a;           //xy=816.2500114440918,1121.2500171661377
AudioMixer4              auMIXER_FM_v1b;   //xy=833.2679824829102,1865.166416168213
AudioMixer4              auMIXER_FM_v2b;        //xy=833.6667861938477,1931.3332862854004
AudioMixer4              auMIXER_FM_v3b;        //xy=833.6667861938477,1994.3332862854004
AudioMixer4              auMIXER_FM_v4a;        //xy=837.0715637207031,1198.0238018035889
AudioMixer4              auMIXER_FM_v4b;        //xy=833.6667861938477,2060.3332862854004
AudioMixer4              auMIXER_FM_v3a;        //xy=838.3572616577148,1262.0238094329834
AudioMixer4              auMIXER_FM_v2a;        //xy=838.3572616577148,1326.0238094329834
AudioMixer4              auMIXER_FM_v1a;   //xy=838.3870239257812,1391.856912612915
AudioSynthWaveformModulated auLFO_PITCH;   //xy=884.8395690917969,1638.4671468734741
AudioSynthWaveformModulated auDCO_V3a;   //xy=1055.6191101074219,1154.0237079188228
AudioSynthWaveformModulated auDCO_V4a;   //xy=1056.190559387207,1120.309449724853
AudioSynthWaveformModulated auDCO_V1a;       //xy=1055.9346008300781,1222.7853541895747
AudioSynthWaveformModulated auDCO_V2a;   //xy=1056.4762802124023,1188.309413485229
AudioSynthWaveformModulated auDCO_v1b;       //xy=1061.6488571166992,2021.3564805984497
AudioSynthWaveformModulated auDCO_v2b;   //xy=1064.3334503173828,2056.5236854553223
AudioSynthWaveformModulated auDCO_v3b;   //xy=1065.1906089782715,2091.5237712860107
AudioSynthWaveformModulated auDCO_v4b;  //xy=1065.6191711425781,2126.523666381836
AudioSynthWaveformDc     auDC_XMOD_a;    //xy=1126.029930114746,1618.6900062561035
AudioSynthWaveformDc     auDC_XMOD_b;    //xy=1126.6014099121094,1660.4045867919922
AudioEffectMultiply      auMULT_XMOD_v1a;  //xy=1137.2204284667969,1435.2140922546387
AudioEffectMultiply      auMULT_XMOD_v2a;      //xy=1137.6191711425781,1400.9365043640137
AudioEffectMultiply      auMULT_XMOD_v3a;      //xy=1138.2858581542969,1366.8254203796387
AudioEffectMultiply      auMULT_XMOD_v4a;      //xy=1138.6191711425781,1331.3809623718262
AudioEffectMultiply      auMULT_XMOD_v4b;      //xy=1148.0834655761719,1927.416615486145
AudioEffectMultiply      auMULT_XMOD_v3b;      //xy=1149.0834655761719,1892.416615486145
AudioEffectMultiply      auMULT_XMOD_v2b;      //xy=1151.0834655761719,1857.416615486145
AudioEffectMultiply      auMULT_XMOD_v1b;  //xy=1152.6847229003906,1822.2497453689575
AudioSynthWaveformDc     auDC_RINGMOD;   //xy=1355.9346618652344,1638.2497425079346
AudioSynthWaveform       auWAVE_RINGMOD; //xy=1447.6846618652344,1601.9997425079346
AudioMixer4              auMIXER_AM_V4a;        //xy=1456.3334503173828,1161.666591644287
AudioMixer4              auMIXER_AM_V3a;        //xy=1456.3334503173828,1225.666591644287
AudioMixer4              auMIXER_AM_V2a;        //xy=1458.3334503173828,1288.666591644287
AudioMixer4              auMIXER_AM_V1a;   //xy=1458.9347686767578,1354.4997215270996
AudioMixer4              auMIXER_AM_V1b;   //xy=1456.9346466064453,1914.4997215270996
AudioMixer4              auMIXER_AM_V4b;        //xy=1456.3334503173828,2108.666591644287
AudioMixer4              auMIXER_AM_V2b;        //xy=1457.3334503173828,1979.666591644287
AudioMixer4              auMIXER_AM_V3b;        //xy=1457.3334503173828,2044.666591644287
AudioEffectMultiply      au_MULT_ring; //xy=1568.4347877502441,1639.4997425079346
AudioEffectMultiply      auMULT_AM_POST_V4b;      //xy=1684.3334503173828,2105.666591644287
AudioEffectMultiply      auMULT_AM_POST_V4a;     //xy=1688.3334503173828,1155.666591644287
AudioEffectMultiply      auMULT_AM_POST_V1b; //xy=1686.4346466064453,1908.249355316162
AudioEffectMultiply      auMULT_AM_POST_V2b;      //xy=1686.3334503173828,1974.666591644287
AudioEffectMultiply      auMULT_AM_POST_V1a; //xy=1689.9703903198242,1347.2497549057007
AudioEffectMultiply      auMULT_AM_POST_V3b;      //xy=1687.3334503173828,2042.666591644287
AudioEffectMultiply      auMULT_AM_POST_V2a;     //xy=1691.0477294921875,1285.095127105713
AudioEffectMultiply      auMULT_AM_POST_V3a;     //xy=1692.3334503173828,1219.666591644287
AudioSynthNoiseWhite     auNOISE_WHITE;  //xy=1784.8275527954102,1532.9641704559326
AudioSynthNoisePink      auNOISE_PINK;   //xy=1791.0775527954102,1566.9641704559326
AudioMixer4              auMIXER_NOISE;         //xy=1908.5712356567383,1630.0000762939453
AudioMixer4              auMIXER_WAVE_V3a;        //xy=1958.5834732055664,1224.4166069030762
AudioMixer4              auMIXER_WAVE_V4a;        //xy=1959.8334732055664,1161.6666049957275
AudioMixer4              auMIXER_WAVE_V2a;        //xy=1959.5834732055664,1289.6666069030762
AudioMixer4              auMIXER_WAVE_V1a; //xy=1959.6846466064453,1353.999599456787
AudioMixer4              auMIXER_WAVE_V4b;        //xy=1962.8334732055664,2113.6666164398193
AudioMixer4              auMIXER_WAVE_V2b;        //xy=1963.8334732055664,1983.6666164398193
AudioMixer4              auMIXER_WAVE_V3b;        //xy=1963.8334732055664,2048.6666164398193
AudioMixer4              auMIXER_WAVE_V1b; //xy=1964.934669494629,1918.7497463226318
AudioSynthWaveformDc     auDC_FILTERENV; //xy=2183.1850204467773,1142.372631072998
AudioMixer4              auMIXER_PRESHAPE_V3;        //xy=2261.3691787719727,1706.0912818908691
AudioMixer4              auMIXER_PRESHAPE_V2;        //xy=2262.618995666504,1640.5555400848389
AudioMixer4              auMIXER_PRESHAPE_V4;        //xy=2262.440589904785,1771.627052307129
AudioMixer4              auMIXER_PRESHAPE_V1;        //xy=2263.6904678344727,1575.019863128662
AudioEffectEnvelope      auENV_FILTER_V1; //xy=2377.685043334961,1275.979835510254
AudioEffectEnvelope      auENV_FILTER_V2;      //xy=2378.393295288086,1307.0931186676025
AudioEffectEnvelope      auENV_FILTER_V3;      //xy=2379.643295288086,1339.5931177139282
AudioEffectEnvelope      auENV_FILTER_V4;      //xy=2379.643295288086,1372.0931196212769
AudioSynthWaveformModulated auLFO_FILTER;   //xy=2390.636459350586,1193.624855041504
AudioAmplifier           auAMP_SHAPER_PREAMP_V4;           //xy=2565.833541870117,2043.6805686950684
AudioAmplifier           auAMP_SHAPER_PREAMP_V3;           //xy=2569.5835456848145,1878.680564880371
AudioAmplifier           auAMP_SHAPER_PREAMP_V1; //xy=2573.160934448242,1543.995867729187
AudioMixer4              auMIXER_SHAPER_BYPASS_V4;        //xy=2572.08358001709,2122.430588722229
AudioAmplifier           auAMP_SHAPER_PREAMP_V2;           //xy=2574.583541870117,1718.6805629730225
AudioMixer4              auMIXER_SHAPER_BYPASS_V3;        //xy=2577.0835456848145,1962.4305663108826
AudioMixer4              auMIXER_SHAPER_BYPASS_V1; //xy=2578.9109420776367,1630.2458686828613
AudioMixer4              auMIXER_SHAPER_BYPASS_V2;        //xy=2578.333541870117,1801.180564880371
AudioEffectWaveshaper    auSHAPER_V2;     //xy=2579.5835494995117,1752.4305629730225
AudioEffectWaveshaper    auSHAPER_V4;     //xy=2578.333541870117,2076.1805686950684
AudioEffectWaveshaper    auSHAPER_V3;     //xy=2583.3335189819336,1913.6805477142334
AudioEffectWaveshaper    auSHAPER_V1;     //xy=2585.8332748413086,1580.0000171661377
AudioMixer4              auMIXER_FILTERMOD_V1; //xy=2653.3276290893555,1196.801248550415
AudioMixer4              auMIXER_FILTERMOD_V2;        //xy=2653.3930587768555,1260.8431224822998
AudioMixer4              auMIXER_FILTERMOD_V3;        //xy=2654.6430130004883,1324.5931072235107
AudioMixer4              auMIXER_FILTERMOD_V4;        //xy=2654.6430587768555,1392.0931224822998
AudioFilterStateVariable auFILTER_SV_V1;  //xy=2911.0178756713867,1559.7102241516113
AudioFilterStateVariable auFILTER_SV_V2;        //xy=2910.8335494995117,1748.6805629730225
AudioFilterStateVariable auFILTER_SV_V4;        //xy=2912.0835494995117,2066.1805686950684
AudioFilterStateVariable auFILTER_SV_V3;        //xy=2913.3335494995117,1904.930564880371
AudioFilterLadder        auFILTER_LADDER_V2;        //xy=2929.5835876464844,1797.4305820465088
AudioFilterLadder        auFILTER_LADDER_V1; //xy=2931.518112182617,1608.6031036376953
AudioFilterLadder        auFILTER_LADDER_V3;        //xy=2932.0835494995117,1952.4305667877197
AudioFilterLadder        auFILTER_LADDER_V4;        //xy=2932.0835494995117,2113.6805686950684
AudioSynthWaveformDc     auDC_AMPENV;    //xy=3024.2323989868164,1136.9640636444092
AudioEffectEnvelope      auENV_AMP_V2;     //xy=3205.297920227051,1306.7559089660645
AudioEffectEnvelope      auENV_AMP_V1;    //xy=3205.482250213623,1271.7140369415283
AudioEffectEnvelope      auENV_AMP_V3;     //xy=3205.297924041748,1340.5059089660645
AudioEffectEnvelope      auENV_AMP_V4;     //xy=3205.297924041748,1374.2559089660645
AudioSynthWaveformModulated auLFO_AMP;   //xy=3211.8038635253906,1202.5385704040527
AudioMixer4              auMIXER_FILTER_BLOCK_V2;         //xy=3239.583427429199,1644.930513381958
AudioMixer4              auMIXER_FILTER_BLOCK_V3;         //xy=3239.583427429199,1708.6805171966553
AudioMixer4              auMIXER_FILTER_BLOCK_V1; //xy=3240.303642272949,1581.4600524902344
AudioMixer4              auMIXER_FILTER_BLOCK_V4;         //xy=3239.583427429199,1773.6805152893066
AudioMixer4              auMIXER_FINAL_L; //xy=3323.140884399414,1986.062973022461
AudioMixer4              auMIXER_FINAL_R; //xy=3322.890914916992,2052.4520721435547
AudioMixer4              _auMIXER_AMPMOD_V1;         //xy=3489.881175994873,1209.6309070587158
AudioMixer4              _auMIXER_AMPMOD_V2;         //xy=3490.297924041748,1271.7559089660645
AudioMixer4              _auMIXER_AMPMOD_V3;         //xy=3490.297924041748,1334.2559089660645
AudioMixer4              _auMIXER_AMPMOD_V4;         //xy=3490.297924041748,1396.7559127807617
AudioAmplifier           auAMP_POST_FILTER_V3;           //xy=3509.916748046875,1696.4166259765625
AudioAmplifier           auAMP_POST_FILTER_V1;           //xy=3510.250244140625,1624.2501220703125
AudioAmplifier           auAMP_POST_FILTER_V4;           //xy=3509.916748046875,1731.5833740234375
AudioAmplifier           auAMP_POST_FILTER_V2;           //xy=3510.25,1660.2498779296875
AudioAmplifier           auAMP_MASTER_GAIN_L; //xy=3555.640739440918,1994.2296237945557
AudioAmplifier           auAMP_MASTER_GAIN_R; //xy=3555.640495300293,2034.2298679351807
AudioEffectMultiply      auMULT_AENV_POST_V3;     //xy=3784.535400390625,1696.811279296875
AudioEffectMultiply      auMULT_AENV_POST_V4;     //xy=3784.535400390625,1731.8112812042236
AudioEffectMultiply      auMULT_AENV_POST_V2; //xy=3784.969970703125,1662.7694091796875
AudioEffectMultiply      auMULT_AENV_POST_V1; //xy=3785.2197265625,1629.0194091796875
AudioAnalyzePeak         auPEAK_L;       //xy=3785.1407470703125,1948.4798622131348
AudioAnalyzePeak         auPEAK_R;       //xy=3784.8907470703125,2090.979866027832
AudioOutputUSB           auSTEREO_OUT;   //xy=3805.8907470703125,2052.729742527008
AudioMixer4              auMIXER_SCOPE;  //xy=3809.640739440918,1999.2298679351807
AudioConnection          patchCord1(auDC_PITCHENV, auENV_PITCH_V1);
AudioConnection          patchCord2(auDC_PITCHENV, auENV_PITCH_V2);
AudioConnection          patchCord3(auDC_PITCHENV, auENV_PITCH_V3);
AudioConnection          patchCord4(auDC_PITCHENV, auENV_PITCH_V4);
AudioConnection          patchCord5(auENV_PITCH_V2, 0, auMIXER_FM_v2b, 0);
AudioConnection          patchCord6(auENV_PITCH_V2, 0, auMIXER_FM_v3a, 0);
AudioConnection          patchCord7(auENV_PITCH_V1, 0, auMIXER_FM_v1b, 0);
AudioConnection          patchCord8(auENV_PITCH_V1, 0, auMIXER_FM_v4a, 0);
AudioConnection          patchCord9(auENV_PITCH_V3, 0, auMIXER_FM_v3b, 0);
AudioConnection          patchCord10(auENV_PITCH_V3, 0, auMIXER_FM_v2a, 0);
AudioConnection          patchCord11(auENV_PITCH_V4, 0, auMIXER_FM_v4b, 0);
AudioConnection          patchCord12(auENV_PITCH_V4, 0, auMIXER_FM_v1a, 0);
AudioConnection          patchCord13(auWAVE_PWM_b, auAMP_PWM_b);
AudioConnection          patchCord14(auWAVE_PWM_a, auAMP_PWM_a);
AudioConnection          patchCord15(auDC_PITCHBEND, 0, auMIXER_FM_v1a, 1);
AudioConnection          patchCord16(auDC_PITCHBEND, 0, auMIXER_FM_v1b, 1);
AudioConnection          patchCord17(auDC_PITCHBEND, 0, auMIXER_FM_v2a, 1);
AudioConnection          patchCord18(auDC_PITCHBEND, 0, auMIXER_FM_v3a, 1);
AudioConnection          patchCord19(auDC_PITCHBEND, 0, auMIXER_FM_v4a, 1);
AudioConnection          patchCord20(auDC_PITCHBEND, 0, auMIXER_FM_v2b, 1);
AudioConnection          patchCord21(auDC_PITCHBEND, 0, auMIXER_FM_v3b, 1);
AudioConnection          patchCord22(auDC_PITCHBEND, 0, auMIXER_FM_v4b, 1);
AudioConnection          patchCord23(auAMP_PWM_b, 0, auDCO_v1b, 1);
AudioConnection          patchCord24(auAMP_PWM_b, 0, auDCO_v2b, 1);
AudioConnection          patchCord25(auAMP_PWM_b, 0, auDCO_v3b, 1);
AudioConnection          patchCord26(auAMP_PWM_b, 0, auDCO_v4b, 1);
AudioConnection          patchCord27(auAMP_PWM_a, 0, auDCO_V4a, 1);
AudioConnection          patchCord28(auAMP_PWM_a, 0, auDCO_V3a, 1);
AudioConnection          patchCord29(auAMP_PWM_a, 0, auDCO_V2a, 1);
AudioConnection          patchCord30(auAMP_PWM_a, 0, auDCO_V1a, 1);
AudioConnection          patchCord31(auMIXER_FM_v1b, 0, auDCO_v1b, 0);
AudioConnection          patchCord32(auMIXER_FM_v2b, 0, auDCO_v2b, 0);
AudioConnection          patchCord33(auMIXER_FM_v3b, 0, auDCO_v3b, 0);
AudioConnection          patchCord34(auMIXER_FM_v4a, 0, auDCO_V4a, 0);
AudioConnection          patchCord35(auMIXER_FM_v4b, 0, auDCO_v4b, 0);
AudioConnection          patchCord36(auMIXER_FM_v3a, 0, auDCO_V3a, 0);
AudioConnection          patchCord37(auMIXER_FM_v2a, 0, auDCO_V2a, 0);
AudioConnection          patchCord38(auMIXER_FM_v1a, 0, auDCO_V1a, 0);
AudioConnection          patchCord39(auLFO_PITCH, 0, auMIXER_FM_v1a, 2);
AudioConnection          patchCord40(auLFO_PITCH, 0, auMIXER_FM_v1b, 2);
AudioConnection          patchCord41(auLFO_PITCH, 0, auMIXER_FM_v2a, 2);
AudioConnection          patchCord42(auLFO_PITCH, 0, auMIXER_FM_v3a, 2);
AudioConnection          patchCord43(auLFO_PITCH, 0, auMIXER_FM_v4a, 2);
AudioConnection          patchCord44(auLFO_PITCH, 0, auMIXER_FM_v2b, 2);
AudioConnection          patchCord45(auLFO_PITCH, 0, auMIXER_FM_v3b, 2);
AudioConnection          patchCord46(auLFO_PITCH, 0, auMIXER_FM_v4b, 2);
AudioConnection          patchCord47(auDCO_V3a, 0, auMULT_XMOD_v3a, 0);
AudioConnection          patchCord48(auDCO_V3a, 0, auMULT_AM_POST_V3a, 0);
AudioConnection          patchCord49(auDCO_V3a, 0, auMIXER_WAVE_V3a, 0);
AudioConnection          patchCord50(auDCO_V4a, 0, auMULT_XMOD_v4a, 0);
AudioConnection          patchCord51(auDCO_V4a, 0, auMULT_AM_POST_V4a, 0);
AudioConnection          patchCord52(auDCO_V4a, 0, auMIXER_WAVE_V4a, 0);
AudioConnection          patchCord53(auDCO_V1a, 0, auMIXER_WAVE_V1a, 0);
AudioConnection          patchCord54(auDCO_V1a, 0, auMULT_AM_POST_V1a, 0);
AudioConnection          patchCord55(auDCO_V1a, 0, auMULT_XMOD_v1a, 0);
AudioConnection          patchCord56(auDCO_V2a, 0, auMULT_XMOD_v2a, 0);
AudioConnection          patchCord57(auDCO_V2a, 0, auMULT_AM_POST_V2a, 0);
AudioConnection          patchCord58(auDCO_V2a, 0, auMIXER_WAVE_V2a, 0);
AudioConnection          patchCord59(auDCO_v1b, 0, auMIXER_WAVE_V1b, 0);
AudioConnection          patchCord60(auDCO_v1b, 0, auMULT_AM_POST_V1b, 0);
AudioConnection          patchCord61(auDCO_v1b, 0, auMULT_XMOD_v1b, 0);
AudioConnection          patchCord62(auDCO_v2b, 0, auMULT_XMOD_v2b, 0);
AudioConnection          patchCord63(auDCO_v2b, 0, auMIXER_WAVE_V2b, 0);
AudioConnection          patchCord64(auDCO_v3b, 0, auMULT_XMOD_v3b, 0);
AudioConnection          patchCord65(auDCO_v3b, 0, auMIXER_WAVE_V3b, 0);
AudioConnection          patchCord66(auDCO_v4b, 0, auMULT_XMOD_v4b, 0);
AudioConnection          patchCord67(auDCO_v4b, 0, auMIXER_WAVE_V4b, 0);
AudioConnection          patchCord68(auDC_XMOD_a, 0, auMULT_XMOD_v1a, 1);
AudioConnection          patchCord69(auDC_XMOD_a, 0, auMULT_XMOD_v2a, 1);
AudioConnection          patchCord70(auDC_XMOD_a, 0, auMULT_XMOD_v3a, 1);
AudioConnection          patchCord71(auDC_XMOD_a, 0, auMULT_XMOD_v4a, 1);
AudioConnection          patchCord72(auDC_XMOD_b, 0, auMULT_XMOD_v1b, 1);
AudioConnection          patchCord73(auDC_XMOD_b, 0, auMULT_XMOD_v2b, 1);
AudioConnection          patchCord74(auDC_XMOD_b, 0, auMULT_XMOD_v3b, 1);
AudioConnection          patchCord75(auDC_XMOD_b, 0, auMULT_XMOD_v4b, 1);
AudioConnection          patchCord76(auMULT_XMOD_v1a, 0, auMIXER_AM_V1b, 0);
AudioConnection          patchCord77(auMULT_XMOD_v2a, 0, auMIXER_AM_V2b, 0);
AudioConnection          patchCord78(auMULT_XMOD_v3a, 0, auMIXER_AM_V3b, 0);
AudioConnection          patchCord79(auMULT_XMOD_v4a, 0, auMIXER_AM_V4b, 0);
AudioConnection          patchCord80(auMULT_XMOD_v4b, 0, auMIXER_AM_V4a, 0);
AudioConnection          patchCord81(auMULT_XMOD_v3b, 0, auMIXER_AM_V3a, 0);
AudioConnection          patchCord82(auMULT_XMOD_v2b, 0, auMIXER_AM_V2a, 0);
AudioConnection          patchCord83(auMULT_XMOD_v1b, 0, auMIXER_AM_V1a, 0);
AudioConnection          patchCord84(auDC_RINGMOD, 0, au_MULT_ring, 1);
AudioConnection          patchCord85(auWAVE_RINGMOD, 0, au_MULT_ring, 0);
AudioConnection          patchCord86(auMIXER_AM_V4a, 0, auMULT_AM_POST_V4a, 1);
AudioConnection          patchCord87(auMIXER_AM_V3a, 0, auMULT_AM_POST_V3a, 1);
AudioConnection          patchCord88(auMIXER_AM_V2a, 0, auMULT_AM_POST_V2a, 1);
AudioConnection          patchCord89(auMIXER_AM_V1a, 0, auMULT_AM_POST_V1a, 1);
AudioConnection          patchCord90(auMIXER_AM_V1b, 0, auMULT_AM_POST_V1b, 1);
AudioConnection          patchCord91(auMIXER_AM_V4b, 0, auMULT_AM_POST_V4b, 1);
AudioConnection          patchCord92(auMIXER_AM_V2b, 0, auMULT_AM_POST_V2b, 1);
AudioConnection          patchCord93(auMIXER_AM_V3b, 0, auMULT_AM_POST_V3b, 1);
AudioConnection          patchCord94(au_MULT_ring, 0, auMIXER_AM_V1a, 1);
AudioConnection          patchCord95(au_MULT_ring, 0, auMIXER_AM_V1b, 1);
AudioConnection          patchCord96(au_MULT_ring, 0, auMIXER_AM_V2a, 1);
AudioConnection          patchCord97(au_MULT_ring, 0, auMIXER_AM_V3a, 1);
AudioConnection          patchCord98(au_MULT_ring, 0, auMIXER_AM_V4a, 1);
AudioConnection          patchCord99(au_MULT_ring, 0, auMIXER_AM_V2b, 1);
AudioConnection          patchCord100(au_MULT_ring, 0, auMIXER_AM_V3b, 1);
AudioConnection          patchCord101(au_MULT_ring, 0, auMIXER_AM_V4b, 1);
AudioConnection          patchCord102(auMULT_AM_POST_V4b, 0, auMIXER_WAVE_V4b, 1);
AudioConnection          patchCord103(auMULT_AM_POST_V4a, 0, auMIXER_WAVE_V4a, 1);
AudioConnection          patchCord104(auMULT_AM_POST_V1b, 0, auMIXER_WAVE_V1b, 1);
AudioConnection          patchCord105(auMULT_AM_POST_V2b, 0, auMIXER_WAVE_V2b, 1);
AudioConnection          patchCord106(auMULT_AM_POST_V1a, 0, auMIXER_WAVE_V1a, 1);
AudioConnection          patchCord107(auMULT_AM_POST_V3b, 0, auMIXER_WAVE_V3b, 1);
AudioConnection          patchCord108(auMULT_AM_POST_V2a, 0, auMIXER_WAVE_V2a, 1);
AudioConnection          patchCord109(auMULT_AM_POST_V3a, 0, auMIXER_WAVE_V3a, 1);
AudioConnection          patchCord110(auNOISE_WHITE, 0, auMIXER_NOISE, 0);
AudioConnection          patchCord111(auNOISE_PINK, 0, auMIXER_NOISE, 1);
AudioConnection          patchCord112(auMIXER_NOISE, 0, auMIXER_WAVE_V1a, 2);
AudioConnection          patchCord113(auMIXER_NOISE, 0, auMIXER_WAVE_V2a, 2);
AudioConnection          patchCord114(auMIXER_NOISE, 0, auMIXER_WAVE_V3a, 2);
AudioConnection          patchCord115(auMIXER_NOISE, 0, auMIXER_WAVE_V4a, 2);
AudioConnection          patchCord116(auMIXER_NOISE, 0, auMIXER_WAVE_V1b, 2);
AudioConnection          patchCord117(auMIXER_NOISE, 0, auMIXER_WAVE_V2b, 2);
AudioConnection          patchCord118(auMIXER_NOISE, 0, auMIXER_WAVE_V3b, 2);
AudioConnection          patchCord119(auMIXER_NOISE, 0, auMIXER_WAVE_V4b, 2);
AudioConnection          patchCord120(auMIXER_WAVE_V3a, 0, auMIXER_PRESHAPE_V3, 0);
AudioConnection          patchCord121(auMIXER_WAVE_V4a, 0, auMIXER_PRESHAPE_V4, 0);
AudioConnection          patchCord122(auMIXER_WAVE_V2a, 0, auMIXER_PRESHAPE_V2, 0);
AudioConnection          patchCord123(auMIXER_WAVE_V1a, 0, auMIXER_PRESHAPE_V1, 0);
AudioConnection          patchCord124(auMIXER_WAVE_V4b, 0, auMIXER_PRESHAPE_V4, 1);
AudioConnection          patchCord125(auMIXER_WAVE_V2b, 0, auMIXER_PRESHAPE_V2, 1);
AudioConnection          patchCord126(auMIXER_WAVE_V3b, 0, auMIXER_PRESHAPE_V3, 1);
AudioConnection          patchCord127(auMIXER_WAVE_V1b, 0, auMIXER_PRESHAPE_V1, 1);
AudioConnection          patchCord128(auDC_FILTERENV, auENV_FILTER_V1);
AudioConnection          patchCord129(auDC_FILTERENV, auENV_FILTER_V2);
AudioConnection          patchCord130(auDC_FILTERENV, auENV_FILTER_V3);
AudioConnection          patchCord131(auDC_FILTERENV, auENV_FILTER_V4);
AudioConnection          patchCord132(auMIXER_PRESHAPE_V3, auAMP_SHAPER_PREAMP_V3);
AudioConnection          patchCord133(auMIXER_PRESHAPE_V3, 0, auMIXER_SHAPER_BYPASS_V3, 0);
AudioConnection          patchCord134(auMIXER_PRESHAPE_V2, auAMP_SHAPER_PREAMP_V2);
AudioConnection          patchCord135(auMIXER_PRESHAPE_V2, 0, auMIXER_SHAPER_BYPASS_V2, 0);
AudioConnection          patchCord136(auMIXER_PRESHAPE_V4, auAMP_SHAPER_PREAMP_V4);
AudioConnection          patchCord137(auMIXER_PRESHAPE_V4, 0, auMIXER_SHAPER_BYPASS_V4, 0);
AudioConnection          patchCord138(auMIXER_PRESHAPE_V1, auAMP_SHAPER_PREAMP_V1);
AudioConnection          patchCord139(auMIXER_PRESHAPE_V1, 0, auMIXER_SHAPER_BYPASS_V1, 0);
AudioConnection          patchCord140(auENV_FILTER_V1, 0, auMIXER_FILTERMOD_V1, 0);
AudioConnection          patchCord141(auENV_FILTER_V2, 0, auMIXER_FILTERMOD_V2, 0);
AudioConnection          patchCord142(auENV_FILTER_V3, 0, auMIXER_FILTERMOD_V3, 0);
AudioConnection          patchCord143(auENV_FILTER_V4, 0, auMIXER_FILTERMOD_V4, 0);
AudioConnection          patchCord144(auLFO_FILTER, 0, auMIXER_FILTERMOD_V1, 1);
AudioConnection          patchCord145(auLFO_FILTER, 0, auMIXER_FILTERMOD_V2, 1);
AudioConnection          patchCord146(auLFO_FILTER, 0, auMIXER_FILTERMOD_V3, 1);
AudioConnection          patchCord147(auLFO_FILTER, 0, auMIXER_FILTERMOD_V4, 1);
AudioConnection          patchCord148(auAMP_SHAPER_PREAMP_V4, auSHAPER_V4);
AudioConnection          patchCord149(auAMP_SHAPER_PREAMP_V3, auSHAPER_V3);
AudioConnection          patchCord150(auAMP_SHAPER_PREAMP_V1, auSHAPER_V1);
AudioConnection          patchCord151(auMIXER_SHAPER_BYPASS_V4, 0, auFILTER_SV_V4, 0);
AudioConnection          patchCord152(auMIXER_SHAPER_BYPASS_V4, 0, auFILTER_LADDER_V4, 0);
AudioConnection          patchCord153(auAMP_SHAPER_PREAMP_V2, auSHAPER_V2);
AudioConnection          patchCord154(auMIXER_SHAPER_BYPASS_V3, 0, auFILTER_SV_V3, 0);
AudioConnection          patchCord155(auMIXER_SHAPER_BYPASS_V3, 0, auFILTER_LADDER_V3, 0);
AudioConnection          patchCord156(auMIXER_SHAPER_BYPASS_V1, 0, auFILTER_SV_V1, 0);
AudioConnection          patchCord157(auMIXER_SHAPER_BYPASS_V1, 0, auFILTER_LADDER_V1, 0);
AudioConnection          patchCord158(auMIXER_SHAPER_BYPASS_V2, 0, auFILTER_SV_V2, 0);
AudioConnection          patchCord159(auMIXER_SHAPER_BYPASS_V2, 0, auFILTER_LADDER_V2, 0);
AudioConnection          patchCord160(auSHAPER_V2, 0, auMIXER_SHAPER_BYPASS_V2, 1);
AudioConnection          patchCord161(auSHAPER_V4, 0, auMIXER_SHAPER_BYPASS_V4, 1);
AudioConnection          patchCord162(auSHAPER_V3, 0, auMIXER_SHAPER_BYPASS_V3, 1);
AudioConnection          patchCord163(auSHAPER_V1, 0, auMIXER_SHAPER_BYPASS_V1, 1);
AudioConnection          patchCord164(auMIXER_FILTERMOD_V1, 0, auFILTER_SV_V1, 1);
AudioConnection          patchCord165(auMIXER_FILTERMOD_V1, 0, auFILTER_LADDER_V1, 1);
AudioConnection          patchCord166(auMIXER_FILTERMOD_V2, 0, auFILTER_SV_V2, 1);
AudioConnection          patchCord167(auMIXER_FILTERMOD_V2, 0, auFILTER_LADDER_V2, 1);
AudioConnection          patchCord168(auMIXER_FILTERMOD_V3, 0, auFILTER_SV_V3, 1);
AudioConnection          patchCord169(auMIXER_FILTERMOD_V3, 0, auFILTER_LADDER_V3, 1);
AudioConnection          patchCord170(auMIXER_FILTERMOD_V4, 0, auFILTER_SV_V4, 1);
AudioConnection          patchCord171(auMIXER_FILTERMOD_V4, 0, auFILTER_LADDER_V4, 1);
AudioConnection          patchCord172(auFILTER_SV_V1, 0, auMIXER_FILTER_BLOCK_V1, 0);
AudioConnection          patchCord173(auFILTER_SV_V1, 1, auMIXER_FILTER_BLOCK_V1, 1);
AudioConnection          patchCord174(auFILTER_SV_V1, 2, auMIXER_FILTER_BLOCK_V1, 2);
AudioConnection          patchCord175(auFILTER_SV_V2, 0, auMIXER_FILTER_BLOCK_V2, 0);
AudioConnection          patchCord176(auFILTER_SV_V2, 1, auMIXER_FILTER_BLOCK_V2, 1);
AudioConnection          patchCord177(auFILTER_SV_V2, 2, auMIXER_FILTER_BLOCK_V2, 2);
AudioConnection          patchCord178(auFILTER_SV_V4, 0, auMIXER_FILTER_BLOCK_V4, 0);
AudioConnection          patchCord179(auFILTER_SV_V4, 1, auMIXER_FILTER_BLOCK_V4, 1);
AudioConnection          patchCord180(auFILTER_SV_V4, 2, auMIXER_FILTER_BLOCK_V4, 2);
AudioConnection          patchCord181(auFILTER_SV_V3, 0, auMIXER_FILTER_BLOCK_V3, 0);
AudioConnection          patchCord182(auFILTER_SV_V3, 1, auMIXER_FILTER_BLOCK_V3, 1);
AudioConnection          patchCord183(auFILTER_SV_V3, 2, auMIXER_FILTER_BLOCK_V3, 2);
AudioConnection          patchCord184(auFILTER_LADDER_V2, 0, auMIXER_FILTER_BLOCK_V2, 3);
AudioConnection          patchCord185(auFILTER_LADDER_V1, 0, auMIXER_FILTER_BLOCK_V1, 3);
AudioConnection          patchCord186(auFILTER_LADDER_V3, 0, auMIXER_FILTER_BLOCK_V3, 3);
AudioConnection          patchCord187(auFILTER_LADDER_V4, 0, auMIXER_FILTER_BLOCK_V4, 3);
AudioConnection          patchCord188(auDC_AMPENV, auENV_AMP_V1);
AudioConnection          patchCord189(auDC_AMPENV, auENV_AMP_V2);
AudioConnection          patchCord190(auDC_AMPENV, auENV_AMP_V3);
AudioConnection          patchCord191(auDC_AMPENV, auENV_AMP_V4);
AudioConnection          patchCord192(auENV_AMP_V2, 0, _auMIXER_AMPMOD_V2, 0);
AudioConnection          patchCord193(auENV_AMP_V1, 0, _auMIXER_AMPMOD_V1, 0);
AudioConnection          patchCord194(auENV_AMP_V3, 0, _auMIXER_AMPMOD_V3, 0);
AudioConnection          patchCord195(auENV_AMP_V4, 0, _auMIXER_AMPMOD_V4, 0);
AudioConnection          patchCord196(auLFO_AMP, 0, _auMIXER_AMPMOD_V1, 1);
AudioConnection          patchCord197(auLFO_AMP, 0, _auMIXER_AMPMOD_V2, 1);
AudioConnection          patchCord198(auLFO_AMP, 0, _auMIXER_AMPMOD_V3, 1);
AudioConnection          patchCord199(auLFO_AMP, 0, _auMIXER_AMPMOD_V4, 1);
AudioConnection          patchCord200(auMIXER_FILTER_BLOCK_V2, auAMP_POST_FILTER_V2);
AudioConnection          patchCord201(auMIXER_FILTER_BLOCK_V3, auAMP_POST_FILTER_V3);
AudioConnection          patchCord202(auMIXER_FILTER_BLOCK_V1, auAMP_POST_FILTER_V1);
AudioConnection          patchCord203(auMIXER_FILTER_BLOCK_V4, auAMP_POST_FILTER_V4);
AudioConnection          patchCord204(auMIXER_FINAL_L, auAMP_MASTER_GAIN_L);
AudioConnection          patchCord205(auMIXER_FINAL_R, auAMP_MASTER_GAIN_R);
AudioConnection          patchCord206(_auMIXER_AMPMOD_V1, 0, auMULT_AENV_POST_V1, 1);
AudioConnection          patchCord207(_auMIXER_AMPMOD_V2, 0, auMULT_AENV_POST_V2, 1);
AudioConnection          patchCord208(_auMIXER_AMPMOD_V3, 0, auMULT_AENV_POST_V3, 1);
AudioConnection          patchCord209(_auMIXER_AMPMOD_V4, 0, auMULT_AENV_POST_V4, 1);
AudioConnection          patchCord210(auAMP_POST_FILTER_V3, 0, auMULT_AENV_POST_V3, 0);
AudioConnection          patchCord211(auAMP_POST_FILTER_V1, 0, auMULT_AENV_POST_V1, 0);
AudioConnection          patchCord212(auAMP_POST_FILTER_V4, 0, auMULT_AENV_POST_V4, 0);
AudioConnection          patchCord213(auAMP_POST_FILTER_V2, 0, auMULT_AENV_POST_V2, 0);
AudioConnection          patchCord214(auAMP_MASTER_GAIN_L, auPEAK_L);
AudioConnection          patchCord215(auAMP_MASTER_GAIN_L, 0, auSTEREO_OUT, 0);
AudioConnection          patchCord216(auAMP_MASTER_GAIN_L, 0, auMIXER_SCOPE, 0);
AudioConnection          patchCord217(auAMP_MASTER_GAIN_R, 0, auSTEREO_OUT, 1);
AudioConnection          patchCord218(auAMP_MASTER_GAIN_R, auPEAK_R);
AudioConnection          patchCord219(auAMP_MASTER_GAIN_R, 0, auMIXER_SCOPE, 1);
AudioConnection          patchCord220(auMULT_AENV_POST_V3, 0, auMIXER_FINAL_L, 2);
AudioConnection          patchCord221(auMULT_AENV_POST_V3, 0, auMIXER_FINAL_R, 2);
AudioConnection          patchCord222(auMULT_AENV_POST_V4, 0, auMIXER_FINAL_R, 3);
AudioConnection          patchCord223(auMULT_AENV_POST_V4, 0, auMIXER_FINAL_L, 3);
AudioConnection          patchCord224(auMULT_AENV_POST_V2, 0, auMIXER_FINAL_L, 1);
AudioConnection          patchCord225(auMULT_AENV_POST_V2, 0, auMIXER_FINAL_R, 1);
AudioConnection          patchCord226(auMULT_AENV_POST_V1, 0, auMIXER_FINAL_L, 0);
AudioConnection          patchCord227(auMULT_AENV_POST_V1, 0, auMIXER_FINAL_R, 0);
// GUItool: end automatically generated code
