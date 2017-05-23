/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "EuclidGrid.h"


//==============================================================================
GenTremoloAudioProcessor::GenTremoloAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
parameters(*this, nullptr) // TODO point to and set up an undomanager
{
    /* Set default values: */
    trem_beat_indicator = k4th;
    trem_frequency = 2.0;
    trem_depth = 1.0;
    trem_waveform_indicator = kWaveformSquareSlopedEdges; //kWaveformSine;
    trem_lfo_phase = 0.0;
    sample_frequency = 1.0/44100.0;
    isRandom = false;
    minBeat = k64th;
    maxBeat = k2;
    blockCounter = 1;
    sampleCounter = 0;
    
    globalNumSamplesPassed = 0;
    
    
    /* initialize and add the parameters */
    
    // TODO use the value to text function to set the label to either on or off for automation
    parameters.createAndAddParameter("randomParamID", "Random", String(),
                                     NormalisableRange<float> (0.0f, 1.0f, 1.0f), 0.0f,
                                     [](float value)
                                     {
                                         // value to text function
                                         return value < 0.5 ? "Random Off" : "Random On";
                                     },
                                     [](const String& text)
                                     {
                                         // text to value function
                                         if (text == "Random Off")    return 0.0f;
                                         if (text == "Random On")  return 1.0f;
                                         return 0.0f;
                                     });   // text to value function
    parameters.createAndAddParameter("chaosParamID", "Chaos", String(), NormalisableRange<float> (0.0f, 1.0f), 0.5f, nullptr, nullptr);
    // TODO use the value to text function to set the min beat label
    parameters.createAndAddParameter("minBeatParamID", "Min beat", String(), NormalisableRange<float> (0.0f, 4.0f, 1.0f), 0.0f, nullptr, nullptr);
    
    
    parameters.state = ValueTree (Identifier ("APVTSGenTremolo"));
    
    
    /* EuclidGrid setup */  // TODO integrate user parameters here!
//    EuclidGrid* euclidGrid = new EuclidGrid();
    euclidGrid = new EuclidGrid();
    isEuclid = false;
    euclidNoteAmplitude = 0.0f;
    volumeRampMultiplier = euclidNoteAmplitude;
    euclidLinearSmoothedValue.reset((double)sample_frequency, ((double)declickRampLengthInMs)/1000.0);
    lastPptPosition = -1;
    pptPosition = 0; // position relative to 32nd notes
}

GenTremoloAudioProcessor::~GenTremoloAudioProcessor()
{
    // TODO make sure that we don't need to delete the EuclidGrid object explicitly.
}

//==============================================================================
const String GenTremoloAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GenTremoloAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GenTremoloAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double GenTremoloAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GenTremoloAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GenTremoloAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GenTremoloAudioProcessor::setCurrentProgram (int index)
{
}

const String GenTremoloAudioProcessor::getProgramName (int index)
{
    return {};
}

void GenTremoloAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void GenTremoloAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void GenTremoloAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GenTremoloAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

// Function for calculating LFO waveforms. Phase runs from 0-1, output is scaled
// from 0 to 1 (note: not -1 to 1 as would be typical of sine).
float GenTremoloAudioProcessor::lfo(float phase, int waveform)
{
    switch(waveform)
    {
    case kWaveformTriangle:
        if(phase < 0.25f)
            return 0.5f + 2.0f*phase;
        else if(phase < 0.75f)
            return 1.0f - 2.0f*(phase - 0.25f);
        else
            return 2.0f*(phase-0.75f);
    case kWaveformSquare:
        if(phase < 0.5f)
            return 1.0f;
        else
            return 0.0f;
    case kWaveformSquareSlopedEdges:
        if(phase < 0.48f)
            return 1.0f;
        else if(phase < 0.5f)
            return 1.0f - 50.0f*(phase - 0.48f);
        else if(phase < 0.98f)
            return 0.0f;
        else
            return 50.0f*(phase - 0.98f);
    case kWaveformSine:
    default:
        return 0.5f + 0.5f*sinf(2.0 * M_PI * phase);
    }
}

int GenTremoloAudioProcessor::getSamplesPerQuarterNote(double bpm) {
    double sampleRate = GenTremoloAudioProcessor::getSampleRate();
    if (bpm <= 0) {
        return (int)round(60.0*sampleRate/120.0);
    }
    return (int)round(60.0*sampleRate/bpm);
}

int GenTremoloAudioProcessor::getSamplesPerBeat(int beatIndicator, double bpm) {
    double sampleRate = GenTremoloAudioProcessor::getSampleRate();
    if (bpm <= 0)
        return (int)round(60.0*sampleRate/120.0);
    int quarterNoteSampleLength = (int)round(60.0*sampleRate/bpm);
    switch (beatIndicator) {
        case k4th:
            return quarterNoteSampleLength;
        case k8th:
            return quarterNoteSampleLength/2;
        case k16th:
            return quarterNoteSampleLength/4;
        case k32nd:
            return quarterNoteSampleLength/8;
        case k64th:
            return quarterNoteSampleLength/16;
        default:
            return quarterNoteSampleLength;
    }
}

/* returns the scale of our interval size that we pass before randomly assigning a new trem frequency*/
int GenTremoloAudioProcessor::scaleChaosParameterToInt() {
    const int chaosLevel = (const int)round(*parameters.getRawParameterValue("chaosParamID") * 10.0f);
    if (chaosLevel == 10) {
        return 1;
    }
    if (chaosLevel == 0) {
        return 10;
    }
    return 10 - chaosLevel;
}

void GenTremoloAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    
    int randVal = 1;  // TODO make randVal remember its state
    const int chaosIntervalSize = scaleChaosParameterToInt();
    isRandom = *parameters.getRawParameterValue("randomParamID") < 0.5f ? false : true;
//    sample_frequency = GenTremoloAudioProcessor::getSampleRate(); // this is not working. Get sample freq from host
//    euclidLinearSmoothedValue.reset(sample_frequency, ((float)declickRampLengthInMs)/1000.0);
    const int totalNumInputChannels  = GenTremoloAudioProcessor::getTotalNumInputChannels();
    const int totalNumOutputChannels = GenTremoloAudioProcessor::getTotalNumOutputChannels();
    const int numSamples = buffer.getNumSamples();
    AudioPlayHead* const playHead = getPlayHead();
    AudioPlayHead::CurrentPositionInfo result = {};
    EuclidGrid::EuclidNote noteStruct = {};
    
    /* get DAW's bpm and beat grid info (only up to date at the start of every call to processBlock) */
    double bpm = 120.0;
    if (playHead != nullptr) {
        if (GenTremoloAudioProcessor::getPlayHead()->getCurrentPosition(result)) {
            bpm = result.bpm;
            globalNumSamplesPassed = (long)result.timeInSamples;
            pptPosition = 8*(long)round(result.ppqPosition);
            lastPptPosition = pptPosition;
        }
    }
    int samplesPerBeatIndicator = getSamplesPerBeat(trem_beat_indicator, bpm);
    int samplesPerQuarterNote = getSamplesPerQuarterNote(bpm);
    long samplesPer32ndNote = 8*(long)samplesPerQuarterNote;
    float temp_trem_lfo_phase_copy;
    float* channelDataLeft = buffer.getWritePointer(0);
    float* channelDataRight = buffer.getWritePointer(1);
    temp_trem_lfo_phase_copy = trem_lfo_phase;
    
    /* iterate through and process samples in block */
    for (int i = 0; i < numSamples; i++) {
        
        const float inLeft = channelDataLeft[i];
        const float inRight = channelDataRight[i];
        
        /* Random Tremolo Preparation */
        if (!isEuclid && isRandom && (sampleCounter % samplesPerBeatIndicator*chaosIntervalSize) == 0) {
            trem_frequency = next_trem_frequency;
            randVal = rand() + 1;
            trem_beat_indicator = BeatIndicators(randVal % 5);
            next_trem_frequency = getUpdatedTremFrequency(bpm);
            sampleCounter = 0;
        }
        
        /* Euclidean Tremolo preparation - update pptPosition and lastPptPosition */
        if ((globalNumSamplesPassed%samplesPer32ndNote == 0)) {
            lastPptPosition = pptPosition;
            pptPosition++;
        }
        
        /* Euclidean Tremolo */
        if (isEuclid) { // TODO make sure that we are not doing multiple grid runs while one grid note plays
            if ( (pptPosition != lastPptPosition) && euclidGrid->runGrid(pptPosition, samplesPerQuarterNote, noteStruct) ) {
                euclidNoteAmplitude = noteStruct.isMuted ? 0.0f : 1.0f;
                euclidLinearSmoothedValue.setValue(euclidNoteAmplitude);
            }
            if (euclidLinearSmoothedValue.isSmoothing()) {
                volumeRampMultiplier = euclidLinearSmoothedValue.getNextValue();
                channelDataLeft[i] = inLeft*volumeRampMultiplier;
                channelDataRight[i] = inRight*volumeRampMultiplier;
            } else {
                channelDataLeft[i] = inLeft*euclidNoteAmplitude;
                channelDataRight[i] = inRight*euclidNoteAmplitude;
            }
        }
        
        /* Non Euclidean Tremolo */
        if (!isEuclid) { // non euclidean logic
            channelDataLeft[i] = inLeft * (1.0f - trem_depth*lfo(temp_trem_lfo_phase_copy, trem_waveform_indicator));
            channelDataRight[i] = inRight * (1.0f - trem_depth*lfo(temp_trem_lfo_phase_copy, trem_waveform_indicator));
        }
        
        /* Update the carrier and LFO phases, keeping them in the range 0-1 */
        temp_trem_lfo_phase_copy += trem_frequency*sample_frequency;
        if(temp_trem_lfo_phase_copy >= 1.0)
            temp_trem_lfo_phase_copy -= 1.0;
        
        /* Increment sample counters */
        sampleCounter++;
        globalNumSamplesPassed++;
    }
    
    /* Having made a local copy of the state variables for each channel, now transfer the result
     * back to the main state variable so they will be preserved for the next call of processBlock() */
    
    trem_lfo_phase = temp_trem_lfo_phase_copy;
    
    /* In case we have more outputs than inputs, we'll clear any output
     * channels that didn't contain input data, (because these aren't
     * guaranteed to be empty - they may contain garbage). */
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

float GenTremoloAudioProcessor::getUpdatedTremFrequency(double bpm) {
    switch (trem_beat_indicator) {
        case k2:
            return bpm / 120.0;
        case k4th:
            return bpm / 60.0;
        case k8th:
            return bpm / 30.0;
        case k16th:
            return bpm / 15.0;
        case k32nd:
            return bpm / 7.5;
        case k64th:
            return bpm / 3.75;
        default:
            return bpm / 60.0;
    }
}

//==============================================================================
bool GenTremoloAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* GenTremoloAudioProcessor::createEditor()
{
    return new GenTremoloAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void GenTremoloAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    /* You should use this method to store your parameters in the memory block.
     * You could do that either as raw data, or use the XML or ValueTree classes
     * as intermediaries to make it easy to save and load complex data. */
    
    ScopedPointer<XmlElement> xml (parameters.state.createXml());
    copyXmlToBinary (*xml, destData);
}

void GenTremoloAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /* You should use this method to restore your parameters from this memory block,
     * whose contents will have been created by the getStateInformation() call. */
    
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState != nullptr) {
        if (xmlState->hasTagName (parameters.state.getType())) {
            parameters.state = ValueTree::fromXml (*xmlState);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GenTremoloAudioProcessor();
}
