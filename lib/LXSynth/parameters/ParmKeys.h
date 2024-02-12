#pragma once

enum ParmKeys
{
    penv_amount = 100,
    penv_attack = 101,
    penv_hold = 102,
    penv_decay = 103,
    penv_sustain = 104,
    penv_release = 105,
    penv_invert = 106,

    plfo_shape = 110,
    plfo_freq = 111,
    plfo_amount = 112,
    pitch_bend = 120,

    aenv_amount = 200,
    aenv_attack = 201,
    aenv_hold = 202,
    aenv_decay = 203,
    aenv_sustain = 204,
    aenv_release = 205,
    aenv_invert = 206,
    

    alfo_shape = 210,
    alfo_freq = 211,
    alfo_amount = 212,
    amp_bend = 220,

    fenv_amount = 300,
    fenv_attack = 301,
    fenv_hold = 302,
    fenv_decay = 303,
    fenv_sustain = 304,
    fenv_release = 305,
    fenv_invert = 306,

    flfo_shape = 310,
    flfo_freq = 311,
    flfo_amount = 312,  
    filter_bend = 320,

    pwm_a_shape = 400,
    pwm_a_freq = 401,
    pwm_a_gain = 402,
    pwm_b_shape = 410,
    pwm_b_freq = 411,
    pwm_b_gain = 412,

    osc_a_amp = 500,
    osc_a_freq = 501,
    osc_a_shape = 502,
    osc_a_detune = 503,
    osc_b_amp = 520,
    osc_b_freq = 521,
    osc_b_shape = 522,
    osc_b_detune = 523,

    xmod_amount = 540,

    ring_level = 550,
    ring_freq = 551,
    ring_shape = 552,

    noise_level = 560,
    noise_type = 561,

    partpan_ab = 570,
    
    shaper_pregain = 600,
    shaper_curve = 601,
    shaper_bypass = 602,

    filter_res = 610,
    filter_freq = 611,
    filter_octaves = 612,
    filter_type = 613,
    filter_postgain = 614,

    voice_gain0 = 650,
    voice_gain1 = 651,
    voice_gain2 = 652,
    voice_gain3 = 653,
    voice_pan0 = 660,
    voice_pan1 = 661,
    voice_pan2 = 662,
    voice_pan3 = 663,

    master_gain = 700,
    master_pan = 701,

    pressedShift = 800,
    pressedEnter = 810
};

FLASHMEM const char * parmKey_cstr(ParmKeys key)
{
    switch (key)
    {
    case penv_amount: return "penv_amount"; 
    case penv_attack: return "penv_attack";
    case penv_hold : return "penv_hold";
    case penv_decay: return "penv_decay";
    case penv_sustain: return "penv_sustain";
    case penv_release: return "penv_release";
    case penv_invert: return "penv_invert";

    case plfo_shape: return "plfo_shape";
    case plfo_freq: return "plfo_freq";
    case plfo_amount: return "plfo_amount";
    case pitch_bend: return "pitch_bend";

    case aenv_amount: return "aenv_amount";
    case aenv_attack: return "aenv_attack";
    case aenv_hold: return "aenv_hold";
    case aenv_decay: return "aenv_decay";
    case aenv_sustain: return "aenv_sustain";
    case aenv_release: return "aenv_release";
    case aenv_invert: return "aenv_invert";
    

    case alfo_shape : return "alfo_shape";
    case alfo_freq : return "alfo_freq";
    case alfo_amount : return "alfo_amount";
    case amp_bend : return "amp_bend";

    case fenv_amount : return "fenv_amount";
    case fenv_attack : return "fenv_attack";
    case fenv_hold : return "fenv_hold";
    case fenv_decay : return "fenv_decay";
    case fenv_sustain : return "fenv_sustain";
    case fenv_release : return "fenv_release";
    case fenv_invert : return "fenv_invert";

    case flfo_shape : return "flfo_shape";
    case flfo_freq : return "flfo_freq";
    case flfo_amount : return "flfo_amount";
    case filter_bend : return "filter_bend";

    case pwm_a_shape : return "pwm_a_shape";
    case pwm_a_freq : return "pwm_a_freq";
    case pwm_a_gain : return "pwm_a_gain";
    case pwm_b_shape : return "pwm_b_shape";
    case pwm_b_freq : return "pwm_b_freq";
    case pwm_b_gain : return "pwm_b_gain";

    case osc_a_amp : return "osc_a_amp";
    case osc_a_freq : return "osc_a_freq";
    case osc_a_shape : return "osc_a_shape";
    case osc_a_detune : return "osc_a_detune";
    case osc_b_amp : return "osc_b_amp";
    case osc_b_freq : return "osc_b_freq";
    case osc_b_shape : return "osc_b_shape";
    case osc_b_detune : return "osc_b_detune";

    case xmod_amount : return "xmod_amount";

    case ring_level : return "ring_level";
    case ring_freq : return "ring_freq";
    case ring_shape : return "ring_shape";

    case noise_level : return "noise_level";
    case noise_type : return "noise_type";

    case partpan_ab : return "partpan_ab";
    
    case shaper_pregain : return "shaper_pregain";
    case shaper_curve : return "shaper_curve";
    case shaper_bypass : return "shaper_bypass";

    case filter_res : return "filter_res";
    case filter_freq : return "filter_freq";
    case filter_octaves : return "filter_octaves";
    case filter_type : return "filter_type";
    case filter_postgain : return "filter_postgain";

    case voice_gain0 : return "voice_gain0";
    case voice_gain1 : return "voice_gain1";
    case voice_gain2 : return "voice_gain2";
    case voice_gain3 : return "voice_gain3";
    case voice_pan0 : return "voice_pan0";
    case voice_pan1 : return "voice_pan1";
    case voice_pan2 : return "voice_pan2";
    case voice_pan3 : return "voice_pan3";

    case master_gain : return "master_gain";
    case master_pan : return "master_pan";
    case pressedShift : return "pressedShift";
    case pressedEnter : return "pressedEnter";
    default: return "unknown";
    }
}