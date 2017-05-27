//
//  EuclidGrid.h
//  GenTremolo
//
//  Created by Zachary Gottesman on 5/21/17.
//
//

//#ifndef EUCLIDGRID_H
//#define EUCLIDGRID_H

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <math.h>

/* Grid resolution should be every 32nd beat plus or minus the swing param. 
 * Further, the 0-chaos patterns generated by this should be 3 bars 
 * (96 beat values per array / 32 32nd-note beat values) = 3 bars.
 *
 * If any of the parameters here are marked with a comment containing "!!!", 
 * then that means the original drum code held these parameters as
 * a 3-element array - one element for each drum (kick, snare, hh). 
 * 
 * Lastly, the public / private designation of methods is still up for 
 * debate and not necessarily permanent. */

class EuclidGrid {
public:
    EuclidGrid();
    ~EuclidGrid();
    
    /* Structs */
    struct EuclidNote {
        int lengthInSamples;
        bool noteOn;
    };
    
    struct StereoEuclidNote {
        int leftLengthInSamples;
        int rightLengthInSamples;
        bool leftNoteOn;
        bool rightNoteOn;
    };
    
    /* Methods */
    int getMapX();
    int getMapY();
    int getRandomness();
    int getDensity();
    int getEuclideanLength();
    bool isOffNote();
    
    void setMapX(int x);
    void setMapY(int y);
    void setRandomness(int r);
    void setDensity(int d);
    void setEuclideanLength(int euclidLength);
    void resetToDefault();
    
    /* Pattern generation methods */
    void reset();
    bool runGrid(long playHeadLocationBy32Notes, int samplesPerQuarterNote, int noteSampleLength, EuclidNote& noteStruct);
    void evaluatePattern();                  // originally referred to as evaluateDrums
    int readPatternMap();                     // originally referred to as readDrumMap
    void output();
    
    /* ORIGINAL INTERNAL LOGIC FUNCTIONS
     
     void grids_run(t_grids *grids, long playHead);  k
     void grids_reset(t_grids *grids);               k
     void grids_evaluate_drums(t_grids *grids);      k
     t_uint8 grids_read_drum_map(t_grids *grids, t_uint8 instrument);     k
     void grids_output(t_grids *grids);  k
     
     */
    
    uint32_t* getNodeByIndex(int index); // possibly don't need this function
//    uint32_t* getBeatMap();
    
private:
    bool isOffNoteBool;
    int mapX;
    int mapY;
    int randomness;
    int density;          // !!!
    int euclideanLength;  // !!!
    
    /* Double check, but there most likely should not be any external access to these int params. */
    int patternStep;      // originally referred to as step
    int euclideanStep;    // !!!
    int perterbation;     // !!!
    int amplitude;         // !!! - originally referred to as velocity
    const int stepsPerPattern = 32;
    unsigned int state;
    
    const int defaultMapX = 64;
    const int defaultMapY = 64;
    const int defaultRandomness = 10;
    const int defaultPatternStep = 0;
    const int defaultPerterbation = 0;
    const int defaultDensity = 32;
    const int defaultEuclideanLength = 7; // !!! BD=5,SN=7,HH=11;
    const int defaultAmplitude = 0;
    const bool defaulIsOffNoteBool = false;
    
    /* Methods */
    uint32_t u32Mix(uint32_t first, uint32_t second, uint32_t maxVal);
    // u32Mix adopted from U8Mix of hardware code ( mutable-instruments.net/forum/discussion/3863/understanding-code-grids-u8mix-and-bitshift-in-pattern_generator-cc/p1 )
    
    /* pattern arrays */
    uint32_t node_0[96]  = {
        255,      0,      0,      0,      0,      0,    145,      0,
        0,      0,      0,      0,    218,      0,      0,      0,
        72,      0,     36,      0,    182,      0,      0,      0,
        109,      0,      0,      0,     72,      0,      0,      0,
        36,      0,    109,      0,      0,      0,      8,      0,
        255,      0,      0,      0,      0,      0,     72,      0,
        0,      0,    182,      0,      0,      0,     36,      0,
        218,      0,      0,      0,    145,      0,      0,      0,
        170,      0,    113,      0,    255,      0,     56,      0,
        170,      0,    141,      0,    198,      0,     56,      0,
        170,      0,    113,      0,    226,      0,     28,      0,
        170,      0,    113,      0,    198,      0,     85,      0,
    };
    uint32_t node_1[96]  = {
        229,      0,     25,      0,    102,      0,     25,      0,
        204,      0,     25,      0,     76,      0,      8,      0,
        255,      0,      8,      0,     51,      0,     25,      0,
        178,      0,     25,      0,    153,      0,    127,      0,
        28,      0,    198,      0,     56,      0,     56,      0,
        226,      0,     28,      0,    141,      0,     28,      0,
        28,      0,    170,      0,     28,      0,     28,      0,
        255,      0,    113,      0,     85,      0,     85,      0,
        159,      0,    159,      0,    255,      0,     63,      0,
        159,      0,    159,      0,    191,      0,     31,      0,
        159,      0,    127,      0,    255,      0,     31,      0,
        159,      0,    127,      0,    223,      0,     95,      0,
    };

    uint32_t node_2[96]  = {
        255,      0,      0,      0,    127,      0,      0,      0,
        0,      0,    102,      0,      0,      0,    229,      0,
        0,      0,    178,      0,    204,      0,      0,      0,
        76,      0,     51,      0,    153,      0,     25,      0,
        0,      0,    127,      0,      0,      0,      0,      0,
        255,      0,    191,      0,     31,      0,     63,      0,
        0,      0,     95,      0,      0,      0,      0,      0,
        223,      0,      0,      0,     31,      0,    159,      0,
        255,      0,     85,      0,    148,      0,     85,      0,
        127,      0,     85,      0,    106,      0,     63,      0,
        212,      0,    170,      0,    191,      0,    170,      0,
        85,      0,     42,      0,    233,      0,     21,      0,
    };

    uint32_t node_3[96]  = {
        255,      0,    212,      0,     63,      0,      0,      0,
        106,      0,    148,      0,     85,      0,    127,      0,
        191,      0,     21,      0,    233,      0,      0,      0,
        21,      0,    170,      0,      0,      0,     42,      0,
        0,      0,      0,      0,    141,      0,    113,      0,
        255,      0,    198,      0,      0,      0,     56,      0,
        0,      0,     85,      0,     56,      0,     28,      0,
        226,      0,     28,      0,    170,      0,     56,      0,
        255,      0,    231,      0,    255,      0,    208,      0,
        139,      0,     92,      0,    115,      0,     92,      0,
        185,      0,     69,      0,     46,      0,     46,      0,
        162,      0,     23,      0,    208,      0,     46,      0,
    };

    uint32_t node_4[96]  = {
        255,      0,     31,      0,     63,      0,     63,      0,
        127,      0,     95,      0,    191,      0,     63,      0,
        223,      0,     31,      0,    159,      0,     63,      0,
        31,      0,     63,      0,     95,      0,     31,      0,
        8,      0,      0,      0,     95,      0,     63,      0,
        255,      0,      0,      0,    127,      0,      0,      0,
        8,      0,      0,      0,    159,      0,     63,      0,
        255,      0,    223,      0,    191,      0,     31,      0,
        76,      0,     25,      0,    255,      0,    127,      0,
        153,      0,     51,      0,    204,      0,    102,      0,
        76,      0,     51,      0,    229,      0,    127,      0,
        153,      0,     51,      0,    178,      0,    102,      0,
    };

    uint32_t node_5[96]  = {
        255,      0,     51,      0,     25,      0,     76,      0,
        0,      0,      0,      0,    102,      0,      0,      0,
        204,      0,    229,      0,      0,      0,    178,      0,
        0,      0,    153,      0,    127,      0,      8,      0,
        178,      0,    127,      0,    153,      0,    204,      0,
        255,      0,      0,      0,     25,      0,     76,      0,
        102,      0,     51,      0,      0,      0,      0,      0,
        229,      0,     25,      0,     25,      0,    204,      0,
        178,      0,    102,      0,    255,      0,     76,      0,
        127,      0,     76,      0,    229,      0,     76,      0,
        153,      0,    102,      0,    255,      0,     25,      0,
        127,      0,     51,      0,    204,      0,     51,      0,
    };

    uint32_t node_6[96]  = {
        255,      0,      0,      0,    223,      0,      0,      0,
        31,      0,      8,      0,    127,      0,      0,      0,
        95,      0,      0,      0,    159,      0,      0,      0,
        95,      0,     63,      0,    191,      0,      0,      0,
        51,      0,    204,      0,      0,      0,    102,      0,
        255,      0,    127,      0,      8,      0,    178,      0,
        25,      0,    229,      0,      0,      0,     76,      0,
        204,      0,    153,      0,     51,      0,     25,      0,
        255,      0,    226,      0,    255,      0,    255,      0,
        198,      0,     28,      0,    141,      0,     56,      0,
        170,      0,     56,      0,     85,      0,     28,      0,
        170,      0,     28,      0,    113,      0,     56,      0,
    };

    uint32_t node_7[96]  = {
        223,      0,      0,      0,     63,      0,      0,      0,
        95,      0,      0,      0,    223,      0,     31,      0,
        255,      0,      0,      0,    159,      0,      0,      0,
        127,      0,     31,      0,    191,      0,     31,      0,
        0,      0,      0,      0,    109,      0,      0,      0,
        218,      0,      0,      0,    182,      0,     72,      0,
        8,      0,     36,      0,    145,      0,     36,      0,
        255,      0,      8,      0,    182,      0,     72,      0,
        255,      0,     72,      0,    218,      0,     36,      0,
        218,      0,      0,      0,    145,      0,      0,      0,
        255,      0,     36,      0,    182,      0,     36,      0,
        182,      0,      0,      0,    109,      0,      0,      0,
    };

    uint32_t node_8[96]  = {
        255,      0,      0,      0,    218,      0,      0,      0,
        36,      0,      0,      0,    218,      0,      0,      0,
        182,      0,    109,      0,    255,      0,      0,      0,
        0,      0,      0,      0,    145,      0,     72,      0,
        159,      0,      0,      0,     31,      0,    127,      0,
        255,      0,     31,      0,      0,      0,     95,      0,
        8,      0,      0,      0,    191,      0,     31,      0,
        255,      0,     31,      0,    223,      0,     63,      0,
        255,      0,     31,      0,     63,      0,     31,      0,
        95,      0,     31,      0,     63,      0,    127,      0,
        159,      0,     31,      0,     63,      0,     31,      0,
        223,      0,    223,      0,    191,      0,    191,      0,
    };

    uint32_t node_9[96]  = {
        226,      0,     28,      0,     28,      0,    141,      0,
        8,      0,      8,      0,    255,      0,      8,      0,
        113,      0,     28,      0,    198,      0,     85,      0,
        56,      0,    198,      0,    170,      0,     28,      0,
        8,      0,     95,      0,      8,      0,      8,      0,
        255,      0,     63,      0,     31,      0,    223,      0,
        8,      0,     31,      0,    191,      0,      8,      0,
        255,      0,    127,      0,    127,      0,    159,      0,
        115,      0,     46,      0,    255,      0,    185,      0,
        139,      0,     23,      0,    208,      0,    115,      0,
        231,      0,     69,      0,    255,      0,    162,      0,
        139,      0,    115,      0,    231,      0,     92,      0,
    };

    uint32_t node_10[96]  = {
        145,      0,      0,      0,      0,      0,    109,      0,
        0,      0,      0,      0,    255,      0,    109,      0,
        72,      0,    218,      0,      0,      0,      0,      0,
        36,      0,      0,      0,    182,      0,      0,      0,
        0,      0,    127,      0,    159,      0,    127,      0,
        159,      0,    191,      0,    223,      0,     63,      0,
        255,      0,     95,      0,     31,      0,     95,      0,
        31,      0,      8,      0,     63,      0,      8,      0,
        255,      0,      0,      0,    145,      0,      0,      0,
        182,      0,    109,      0,    109,      0,    109,      0,
        218,      0,      0,      0,     72,      0,      0,      0,
        182,      0,     72,      0,    182,      0,     36,      0,
    };

    uint32_t node_11[96]  = {
        255,      0,      0,      0,      0,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,      0,
        255,      0,      0,      0,    218,      0,     72,     36,
        0,      0,    182,      0,      0,      0,    145,    109,
        0,      0,    127,      0,      0,      0,     42,      0,
        212,      0,      0,    212,      0,      0,    212,      0,
        0,      0,      0,      0,     42,      0,      0,      0,
        255,      0,      0,      0,    170,    170,    127,     85,
        145,      0,    109,    109,    218,    109,     72,      0,
        145,      0,     72,      0,    218,      0,    109,      0,
        182,      0,    109,      0,    255,      0,     72,      0,
        182,    109,     36,    109,    255,    109,    109,      0,
    };

    uint32_t node_12[96]  = {
        255,      0,      0,      0,    255,      0,    191,      0,
        0,      0,      0,      0,     95,      0,     63,      0,
        31,      0,      0,      0,    223,      0,    223,      0,
        0,      0,      8,      0,    159,      0,    127,      0,
        0,      0,     85,      0,     56,      0,     28,      0,
        255,      0,     28,      0,      0,      0,    226,      0,
        0,      0,    170,      0,     56,      0,    113,      0,
        198,      0,      0,      0,    113,      0,    141,      0,
        255,      0,     42,      0,    233,      0,     63,      0,
        212,      0,     85,      0,    191,      0,    106,      0,
        191,      0,     21,      0,    170,      0,      8,      0,
        170,      0,    127,      0,    148,      0,    148,      0,
    };

    uint32_t node_13[96]  = {
        255,      0,      0,      0,      0,      0,     63,      0,
        191,      0,     95,      0,     31,      0,    223,      0,
        255,      0,     63,      0,     95,      0,     63,      0,
        159,      0,      0,      0,      0,      0,    127,      0,
        72,      0,      0,      0,      0,      0,      0,      0,
        255,      0,      0,      0,      0,      0,      0,      0,
        72,      0,     72,      0,     36,      0,      8,      0,
        218,      0,    182,      0,    145,      0,    109,      0,
        255,      0,    162,      0,    231,      0,    162,      0,
        231,      0,    115,      0,    208,      0,    139,      0,
        185,      0,     92,      0,    185,      0,     46,      0,
        162,      0,     69,      0,    162,      0,     23,      0,
    };

    uint32_t node_14[96]  = {
        255,      0,      0,      0,     51,      0,      0,      0,
        0,      0,      0,      0,    102,      0,      0,      0,
        204,      0,      0,      0,    153,      0,      0,      0,
        0,      0,      0,      0,     51,      0,      0,      0,
        0,      0,      0,      0,      8,      0,     36,      0,
        255,      0,      0,      0,    182,      0,      8,      0,
        0,      0,      0,      0,     72,      0,    109,      0,
        145,      0,      0,      0,    255,      0,    218,      0,
        212,      0,      8,      0,    170,      0,      0,      0,
        127,      0,      0,      0,     85,      0,      8,      0,
        255,      0,      8,      0,    170,      0,      0,      0,
        127,      0,      0,      0,     42,      0,      8,      0,
    };

    uint32_t node_15[96]  = {
        255,      0,      0,      0,      0,      0,      0,      0,
        36,      0,      0,      0,    182,      0,      0,      0,
        218,      0,      0,      0,      0,      0,      0,      0,
        72,      0,      0,      0,    145,      0,    109,      0,
        36,      0,     36,      0,      0,      0,      0,      0,
        255,      0,      0,      0,    182,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,    109,
        218,      0,      0,      0,    145,      0,     72,     72,
        255,      0,     28,      0,    226,      0,     56,      0,
        198,      0,      0,      0,      0,      0,     28,     28,
        170,      0,      0,      0,    141,      0,      0,      0,
        113,      0,      0,      0,     85,     85,     85,     85,
    };

    uint32_t node_16[96]  = {
        255,      0,      0,      0,      0,      0,     95,      0,
        0,      0,    127,      0,      0,      0,      0,      0,
        223,      0,     95,      0,     63,      0,     31,      0,
        191,      0,      0,      0,    159,      0,      0,      0,
        0,      0,     31,      0,    255,      0,      0,      0,
        0,      0,     95,      0,    223,      0,      0,      0,
        0,      0,     63,      0,    191,      0,      0,      0,
        0,      0,      0,      0,    159,      0,    127,      0,
        141,      0,     28,      0,     28,      0,     28,      0,
        113,      0,      8,      0,      8,      0,      8,      0,
        255,      0,      0,      0,    226,      0,      0,      0,
        198,      0,     56,      0,    170,      0,     85,      0,
    };

    uint32_t node_17[96]  = {
        255,      0,      0,      0,      8,      0,      0,      0,
        182,      0,      0,      0,     72,      0,      0,      0,
        218,      0,      0,      0,     36,      0,      0,      0,
        145,      0,      0,      0,    109,      0,      0,      0,
        0,      0,     51,     25,     76,     25,     25,      0,
        153,      0,      0,      0,    127,    102,    178,      0,
        204,      0,      0,      0,      0,      0,    255,      0,
        0,      0,    102,      0,    229,      0,     76,      0,
        113,      0,      0,      0,    141,      0,     85,      0,
        0,      0,      0,      0,    170,      0,      0,      0,
        56,     28,    255,      0,      0,      0,      0,      0,
        198,      0,      0,      0,    226,      0,      0,      0,
    };

    uint32_t node_18[96]  = {
        255,      0,      8,      0,     28,      0,     28,      0,
        198,      0,     56,      0,     56,      0,     85,      0,
        255,      0,     85,      0,    113,      0,    113,      0,
        226,      0,    141,      0,    170,      0,    141,      0,
        0,      0,      0,      0,      0,      0,      0,      0,
        255,      0,      0,      0,    127,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,      0,
        63,      0,      0,      0,    191,      0,      0,      0,
        255,      0,      0,      0,    255,      0,    127,      0,
        0,      0,     85,      0,      0,      0,    212,      0,
        0,      0,    212,      0,     42,      0,    170,      0,
        0,      0,    127,      0,      0,      0,      0,      0,
    };

    uint32_t node_19[96]  = {
        255,      0,      0,      0,      0,      0,    218,      0,
        182,      0,      0,      0,      0,      0,    145,      0,
        145,      0,     36,      0,      0,      0,    109,      0,
        109,      0,      0,      0,     72,      0,     36,      0,
        0,      0,      0,      0,    109,      0,      8,      0,
        72,      0,      0,      0,    255,      0,    182,      0,
        0,      0,      0,      0,    145,      0,      8,      0,
        36,      0,      8,      0,    218,      0,    182,      0,
        255,      0,      0,      0,      0,      0,    226,      0,
        85,      0,      0,      0,    141,      0,      0,      0,
        0,      0,      0,      0,    170,      0,     56,      0,
        198,      0,      0,      0,    113,      0,     28,      0,
    };

    uint32_t node_20[96]  = {
        255,      0,      0,      0,    113,      0,      0,      0,
        198,      0,     56,      0,     85,      0,     28,      0,
        255,      0,      0,      0,    226,      0,      0,      0,
        170,      0,      0,      0,    141,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,      0,
        255,      0,    145,      0,    109,      0,    218,      0,
        36,      0,    182,      0,     72,      0,     72,      0,
        255,      0,      0,      0,      0,      0,    109,      0,
        36,      0,     36,      0,    145,      0,      0,      0,
        72,      0,     72,      0,    182,      0,      0,      0,
        72,      0,     72,      0,    218,      0,      0,      0,
        109,      0,    109,      0,    255,      0,      0,      0,
    };

    uint32_t node_21[96]  = {
        255,      0,      0,      0,    218,      0,      0,      0,
        145,      0,      0,      0,     36,      0,      0,      0,
        218,      0,      0,      0,     36,      0,      0,      0,
        182,      0,     72,      0,      0,      0,    109,      0,
        0,      0,      0,      0,      8,      0,      0,      0,
        255,      0,     85,      0,    212,      0,     42,      0,
        0,      0,      0,      0,      8,      0,      0,      0,
        85,      0,    170,      0,    127,      0,     42,      0,
        109,      0,    109,      0,    255,      0,      0,      0,
        72,      0,     72,      0,    218,      0,      0,      0,
        145,      0,    182,      0,    255,      0,      0,      0,
        36,      0,     36,      0,    218,      0,      8,      0,
    };

    uint32_t node_22[96]  = {
        255,      0,      0,      0,     42,      0,      0,      0,
        212,      0,      0,      0,      8,      0,    212,      0,
        170,      0,      0,      0,     85,      0,      0,      0,
        212,      0,      8,      0,    127,      0,      8,      0,
        255,      0,     85,      0,      0,      0,      0,      0,
        226,      0,     85,      0,      0,      0,    198,      0,
        0,      0,    141,      0,     56,      0,      0,      0,
        170,      0,     28,      0,      0,      0,    113,      0,
        113,      0,     56,      0,    255,      0,      0,      0,
        85,      0,     56,      0,    226,      0,      0,      0,
        0,      0,    170,      0,      0,      0,    141,      0,
        28,      0,     28,      0,    198,      0,     28,      0,
    };

    uint32_t node_23[96]  = {
        255,      0,      0,      0,    229,      0,      0,      0,
        204,      0,    204,      0,      0,      0,     76,      0,
        178,      0,    153,      0,     51,      0,    178,      0,
        178,      0,    127,      0,    102,     51,     51,     25,
        0,      0,      0,      0,      0,      0,      0,     31,
        0,      0,      0,      0,    255,      0,      0,     31,
        0,      0,      8,      0,      0,      0,    191,    159,
        127,     95,     95,      0,    223,      0,     63,      0,
        255,      0,    255,      0,    204,    204,    204,    204,
        0,      0,     51,     51,     51,     51,      0,      0,
        204,      0,    204,      0,    153,    153,    153,    153,
        153,      0,      0,      0,    102,    102,    102,    102,
    };

    uint32_t node_24[96]  = {
        170,      0,      0,      0,      0,    255,      0,      0,
        198,      0,      0,      0,      0,     28,      0,      0,
        141,      0,      0,      0,      0,    226,      0,      0,
        56,      0,      0,    113,      0,     85,      0,      0,
        255,      0,      0,      0,      0,    113,      0,      0,
        85,      0,      0,      0,      0,    226,      0,      0,
        141,      0,      0,      8,      0,    170,     56,     56,
        198,      0,      0,     56,      0,    141,     28,      0,
        255,      0,      0,      0,      0,    191,      0,      0,
        159,      0,      0,      0,      0,    223,      0,      0,
        95,      0,      0,      0,      0,     63,      0,      0,
        127,      0,      0,      0,      0,     31,      0,      0,
    };

    uint32_t* beat_map[5][5] = {  // originally referred to as drum_map
        { node_10, node_8, node_0, node_9, node_11 },
        { node_15, node_7, node_13, node_12, node_6 },
        { node_18, node_14, node_4, node_5, node_3 },
        { node_23, node_16, node_21, node_1, node_2 },
        { node_24, node_19, node_17, node_20, node_22 },
    };

    uint32_t grids_res_euclidean[1024]  = {
        0,      0,      0,      0,      0,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,      0,
        1,      1,      1,      1,      1,      1,      1,      1,
        1,      1,      1,      1,      1,      1,      1,      1,
        
        0,      0,      0,      0,      0,      0,      0,      0,
        1,      1,      1,      1,      1,      1,      1,      1,
        1,      1,      1,      1,      1,      1,      1,      1,
        3,      3,      3,      3,      3,      3,      3,      3,
        
        0,      0,      0,      0,      0,      0,      1,      1,
        1,      1,      1,      1,      1,      1,      1,      1,
        5,      5,      5,      5,      5,      5,      5,      5,
        5,      5,      7,      7,      7,      7,      7,      7,
        
        0,      0,      0,      0,      1,      1,      1,      1,
        1,      1,      1,      1,      5,      5,      5,      5,
        5,      5,      5,      5,     13,     13,     13,     13,
        13,     13,     13,     13,     15,     15,     15,     15,
        
        
        0,      0,      0,      0,      1,      1,      1,      1,
        1,      1,      9,      9,      9,      9,      9,      9,
        13,     13,     13,     13,     13,     13,     29,     29,
        29,     29,     29,     29,     31,     31,     31,     31,
        
        0,      0,      0,      1,      1,      1,      1,      1,
        9,      9,      9,      9,      9,     21,     21,     21,
        21,     21,     21,     45,     45,     45,     45,     45,
        61,     61,     61,     61,     61,     63,     63,     63,
        
        0,      0,      0,      1,      1,      1,      1,     17,
        17,     17,     17,     17,     41,     41,     41,     41,
        45,     45,     45,     45,     93,     93,     93,     93,
        93,    125,    125,    125,    125,    127,    127,    127,
        
        0,      0,      1,      1,      1,      1,     17,     17,
        17,     17,     41,     41,     41,     41,     85,     85,
        85,     85,    173,    173,    173,    173,    221,    221,
        221,    221,    253,    253,    253,    253,    255,    255,
        
        
        0,      0,      1,      1,      1,      1,     33,     33,
        33,     73,     73,     73,     73,    169,    169,    169,
        173,    173,    173,    365,    365,    365,    365,    445,
        445,    445,    509,    509,    509,    509,    511,    511,
        
        0,      0,      1,      1,      1,     33,     33,     33,
        145,    145,    145,    297,    297,    297,    341,    341,
        341,    341,    429,    429,    429,    733,    733,    733,
        957,    957,    957,   1021,   1021,   1021,   1023,   1023,
        
        0,      0,      1,      1,      1,     65,     65,     65,
        145,    145,    297,    297,    297,    681,    681,    681,
        685,    685,    685,   1453,   1453,   1453,   1757,   1757,
        1917,   1917,   1917,   2045,   2045,   2045,   2047,   2047,
        
        0,      0,      1,      1,     65,     65,     65,    273,
        273,    273,    585,    585,   1193,   1193,   1193,   1365,
        1365,   1709,   1709,   1709,   2925,   2925,   3549,   3549,
        3549,   3965,   3965,   3965,   4093,   4093,   4095,   4095,
        
        
        0,      0,      1,      1,    129,    129,    545,    545,
        545,   1169,   1169,   2345,   2345,   2345,   2729,   2729,
        2733,   2733,   3501,   3501,   3501,   5853,   5853,   7101,
        7101,   7101,   7933,   7933,   8189,   8189,   8191,   8191,
        
        0,      0,      1,      1,    129,    129,    545,    545,
        2193,   2193,   2345,   2345,   2345,   5289,   5289,   5461,
        5461,   5805,   5805,  11693,  11693,  11693,  11997,  11997,
        15293,  15293,  16125,  16125,  16381,  16381,  16383,  16383,
        
        0,      0,      1,      1,    257,    257,   1057,   1057,
        2193,   2193,   4681,   4681,   9513,   9513,  10921,  10921,
        10925,  10925,  13741,  13741,  23405,  23405,  28381,  28381,
        30653,  30653,  32253,  32253,  32765,  32765,  32767,  32767,
        
        0,      1,      1,    257,    257,   2113,   2113,   4369,
        4369,   9361,   9361,  10537,  10537,  21161,  21161,  21845,
        21845,  23213,  23213,  44461,  44461,  46813,  46813,  56797,
        56797,  61309,  61309,  65021,  65021,  65533,  65533,  65535,
        
        
        0,      1,      1,    513,    513,   2113,   2113,   8737,
        8737,  17553,  17553,  18729,  38057,  38057,  43689,  43689,
        43693,  43693,  54957,  54957,  93613,  95965,  95965, 113597,
        113597, 126845, 126845, 130045, 130045, 131069, 131069, 131071,
        
        0,      1,      1,    513,    513,   4161,   4161,  16929,
        34961,  34961,  37449,  37449,  76073,  86697,  86697,  87381,
        87381,  88749,  88749, 109997, 187245, 187245, 192221, 192221,
        228285, 253821, 253821, 261117, 261117, 262141, 262141, 262143,
        
        0,      1,      1,   1025,   1025,   8321,  16929,  16929,
        34961,  74897,  74897,  84265,  84265, 169129, 174761, 174761,
        174765, 174765, 186029, 355757, 355757, 374493, 374493, 454365,
        490429, 490429, 507645, 522237, 522237, 524285, 524285, 524287,
        
        0,      1,      1,   1025,   8321,   8321,  33825,  69905,
        69905, 148625, 148625, 149801, 304425, 304425, 346793, 349525,
        349525, 354989, 439725, 439725, 748973, 751325, 751325, 908765,
        908765, 980925, 1031933, 1031933, 1046525, 1048573, 1048573, 1048575,
        
        
        0,      1,      1,   2049,  16513,  16513,  67649, 139809,
        139809, 280721, 299593, 299593, 338217, 677033, 677033, 699049,
        699053, 743085, 743085, 1420717, 1497965, 1497965, 1535709, 1817533,
        1817533, 1961853, 2064125, 2064125, 2093053, 2097149, 2097149, 2097151,
        
        0,      1,      1,   2049,  33025, 133185, 133185, 270881,
        297105, 297105, 599185, 608553, 1217705, 1217705, 1395369, 1398101,
        1398101, 1403565, 1758893, 1758893, 2977197, 2995933, 3600093, 3600093,
        3652541, 3927933, 3927933, 4128253, 4190205, 4194301, 4194301, 4194303,
        
        0,      1,      1,   4097,  33025, 133185, 133185, 541217,
        559249, 1189009, 1189009, 1198377, 2435369, 2708137, 2708137, 2796201,
        2796205, 2972333, 2972333, 3517869, 5991853, 6010589, 6010589, 7270109,
        7306173, 8122237, 8122237, 8322557, 8380413, 8388605, 8388605, 8388607,
        
        0,      1,   4097,   4097,  65793, 266305, 541217, 541217,
        1118481, 2245777, 2396745, 2697513, 2697513, 4887721, 5581481, 5592405,
        5592405, 5614253, 7001773, 11382189, 11382189, 11983725, 12285661, 14540253,
        15694781, 15694781, 16244605, 16645629, 16769021, 16769021, 16777213, 16777215,
        
        
        0,      1,   8193,   8193, 131585, 532609, 1082401, 2236961,
        2236961, 4491409, 4793489, 4868393, 9741609, 9741609, 11096745, 11184809,
        11184813, 11360941, 14071213, 14071213, 23817645, 23967453, 24571613, 29080509,
        29080509, 31389629, 32489213, 33291261, 33538045, 33538045, 33554429, 33554431,
        
        0,      1,   8193, 131585, 131585, 1056897, 2164801, 4465185,
        4753553, 9577617, 9577617, 9586985, 19212585, 21664937, 22358697, 22369621,
        22369621, 22391469, 23778989, 28683693, 47934893, 47953629, 47953629, 57601757,
        58178493, 62779261, 64995069, 66845693, 66845693, 67092477, 67108861, 67108863,
        
        0,      1,  16385, 262657, 262657, 1056897, 4261953, 8667681,
        8947857, 19022993, 19173961, 21580073, 21580073, 38966441, 44389033, 44739241,
        44739245, 45439661, 56284845, 91057581, 91057581, 95869805, 96171741, 116322013,
        116882365, 125693821, 132103933, 133692413, 133692413, 134184957, 134217725, 134217727,
        
        0,      1,  16385, 525313, 2113665, 8521793, 8521793, 8929825,
        17895697, 35932305, 38347921, 38422825, 77932841, 86660265, 89434793, 89478485,
        89478485, 89565869, 95114925, 112569773, 191589805, 191739613, 196570845, 232644061,
        250575805, 251391869, 251391869, 264208125, 267384829, 268402685, 268435453, 268435455,
        
        
        0,      1,  32769, 525313, 4227329, 8521793, 17318433, 35791393,
        35791393, 38045841, 76620945, 76695849, 86321449, 156406953, 177556137, 178956969,
        178956973, 181758637, 224057005, 364228013, 383479213, 383629021, 460779229, 465288125,
        465288125, 502234045, 519827325, 528416253, 535820285, 536805373, 536870909, 536870911,
        
        0,      1,  32769, 1049601, 8421633, 17043521, 34636833, 71442977,
        71862417, 152192145, 153391689, 155797801, 311731497, 346641065, 357870249, 357913941,
        357913941, 358001325, 380459693, 450278829, 762146221, 766958445, 769357533, 930016989,
        930855869, 1004468157, 1039654781, 1056898557, 1071642621, 1073676285, 1073741821, 1073741823,
        
        0,      1,  65537, 2099201, 8421633, 34087041, 69273665, 138682913,
        143165585, 287458449, 306783377, 307382569, 614803753, 625644713, 714427049, 715827881,
        715827885, 718629549, 896194221, 917876141, 1532718509, 1533916893, 1572566749, 1861152477,
        1870117821, 2008936317, 2079309565, 2130640381, 2143285245, 2147352573, 2147483645, 2147483647,
        
        0,      1,  65537, 2099201, 16843009, 67641473, 138479681, 277365281,
        286331153, 574916753, 613491857, 613566761, 690563369, 1246925993, 1386828457, 1431481001,
        1432005293, 1521310381, 1801115309, 2913840557, 3067833773, 3067983581, 3145133789, 3722304989,
        3740236733, 4018007933, 4159684349, 4261281277, 4290768893, 4294836221, 4294967293, 4294967295
    };

};