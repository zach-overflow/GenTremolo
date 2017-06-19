/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "EuclidGrid.h"
#include "DadBodLookAndFeel.h"


//==============================================================================
GenTremoloAudioProcessorEditor::GenTremoloAudioProcessorEditor (GenTremoloAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), valueTreeState(vts), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (windowWidth, windowHeight);
    setLookAndFeel(&dadBodLookAndFeel);
    
    vFontPtr = Typeface::createSystemTypefaceFor(BinaryData::VT323Regular_ttf, BinaryData::VT323Regular_ttfSize);
    
    testLabel.setText("init", dontSendNotification);
    addAndMakeVisible(&testLabel);
    
    /* ------ Automation params and components added here ------ */
    randomToggleButton.setButtonText ("Random");
    randomToggleButton.setColour(ToggleButton::ColourIds::textColourId, dadBodLookAndFeel.getSecondarySectionColour());
    addAndMakeVisible (&randomToggleButton);
    randomAttachment = new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "randomParamID", randomToggleButton);
    randomToggleButton.addListener(this);
    
    euclidToggleButton.setButtonText("Euclidean");
    euclidToggleButton.setRadioGroupId(modeRadioGroupID);
    euclidToggleButton.setColour(ToggleButton::ColourIds::textColourId, dadBodLookAndFeel.getHighlightColour());
    euclidToggleButton.setToggleState(true, dontSendNotification);
    addAndMakeVisible(&euclidToggleButton);
    euclidAttachment = new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "euclidParamID", euclidToggleButton);
    euclidToggleButton.addListener(this);
    
    standardToggleButton.setButtonText("LFO");
    standardToggleButton.setColour(ToggleButton::ColourIds::textColourId, dadBodLookAndFeel.getSecondarySectionColour());
    standardToggleButton.setRadioGroupId(modeRadioGroupID);
    addAndMakeVisible(&standardToggleButton);
    standardAttachment = new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "standardParamID", standardToggleButton);
    standardToggleButton.addListener(this);
    
    stereoToggleButton.setButtonText("Stereo");
    stereoToggleButton.setColour(ToggleButton::ColourIds::textColourId, dadBodLookAndFeel.getHighlightColour());
    addAndMakeVisible(&stereoToggleButton);
    stereoAttachment = new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "stereoParamID", stereoToggleButton);
    
    /*** Mix Slider Param ***/
    mixSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mixSlider.setRange(0.0, 10.0, 1.0);
    mixSlider.setChangeNotificationOnlyOnRelease(true);
    mixSlider.setPopupDisplayEnabled (true, this);
    mixSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(&mixSlider);
    mixLabel.setText("Mix", dontSendNotification);
    mixLabel.setJustificationType(Justification::centredBottom);
    mixLabel.setBounds(mixLabel.getX(), 18, mixLabel.getWidth(), mixLabel.getHeight());
    mixLabel.attachToComponent(&mixSlider, false);
    addAndMakeVisible(&mixLabel);
    mixAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "mixParamID", mixSlider);
    
    /*** Chaos Slider Param ***/
    // TODO look at docs for NormalisableRange.snapToLegalValue. might work for discrete chaos value fix...
    chaosSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    chaosSlider.setRange(0.0, 10.0, 1.0);
    chaosSlider.setChangeNotificationOnlyOnRelease(true);
    chaosSlider.setPopupDisplayEnabled (true, this);
    chaosSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(&chaosSlider);
    chaosLabel.setText("Chaos Amount", dontSendNotification);
    chaosLabel.setJustificationType(Justification::centredBottom);
    chaosLabel.attachToComponent(&chaosSlider, false);
    addAndMakeVisible(&chaosLabel);
    chaosAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "chaosParamID", chaosSlider);
    
    /*** Map X Slider Param ***/
    mapXSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mapXSlider.setRange(0.0, 10.0, 1.0);
    mapXSlider.setChangeNotificationOnlyOnRelease(true);
    mapXSlider.setPopupDisplayEnabled (true, this);
    mapXSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(&mapXSlider);
    mapXLabel.setText("X", dontSendNotification);
    mapXLabel.setSize(30, 20);
    mapXLabel.attachToComponent(&mapXSlider, false);
    mapXLabel.setColour(Label::ColourIds::textColourId, dadBodLookAndFeel.getHighlightColour());
    mapXLabel.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&mapXLabel);
    mapXAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "mapXParamID", mapXSlider);
    
    /*** Map Y Slider Param ***/
    mapYSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mapYSlider.setRange(0.0, 10.0, 1.0);
    mapYSlider.setChangeNotificationOnlyOnRelease(true);
    mapYSlider.setPopupDisplayEnabled (true, this);
    mapYSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(&mapYSlider);
    mapYLabel.setText("Y", dontSendNotification);
    mapYLabel.setSize(30, 20);
    mapYLabel.attachToComponent(&mapYSlider, false);
    mapYLabel.setColour(Label::ColourIds::textColourId, dadBodLookAndFeel.getHighlightColour());
    mapYLabel.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&mapYLabel);
    mapYAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "mapYParamID", mapYSlider);
    
    /*** Kick Density Slider Param ***/
    kickDensitySlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    kickDensitySlider.setRange(0.0, 127.0);
    kickDensitySlider.setPopupDisplayEnabled(true, this);
    kickDensitySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    kickDensitySlider.setColour(Slider::ColourIds::rotarySliderFillColourId, dadBodLookAndFeel.getHighlightColour());
    addAndMakeVisible(&kickDensitySlider);
    kickDensityLabel.setText("kick d", dontSendNotification);
    kickDensityLabel.setSize(30, 20);
    kickDensityLabel.attachToComponent(&kickDensitySlider, false);
    kickDensityLabel.setColour(Label::ColourIds::textColourId, dadBodLookAndFeel.getHighlightColour());
    kickDensityLabel.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&kickDensityLabel);
    kickDensityAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "kickDensityParamID", kickDensitySlider);
    
    /*** Snare Density Slider Param ***/
    snareDensitySlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    snareDensitySlider.setRange(0.0, 127.0);
    snareDensitySlider.setPopupDisplayEnabled(true, this);
    snareDensitySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    snareDensitySlider.setColour(Slider::ColourIds::rotarySliderFillColourId, dadBodLookAndFeel.getHighlightColour());
    addAndMakeVisible(&snareDensitySlider);
    snareDensityLabel.setText("snare d", dontSendNotification);
    snareDensityLabel.setSize(30, 20);
    snareDensityLabel.attachToComponent(&snareDensitySlider, false);
    snareDensityLabel.setColour(Label::ColourIds::textColourId, dadBodLookAndFeel.getHighlightColour());
    snareDensityLabel.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&snareDensityLabel);
    snareDensityAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "snareDensityParamID", snareDensitySlider);
    
    /*** HH Density Slider Param ***/
    hhDensitySlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    hhDensitySlider.setRange(0.0, 127.0);
    hhDensitySlider.setPopupDisplayEnabled(true, this);
    hhDensitySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    hhDensitySlider.setColour(Slider::ColourIds::rotarySliderFillColourId, dadBodLookAndFeel.getHighlightColour());
    addAndMakeVisible(&hhDensitySlider);
    hhDensityLabel.setText("hh d", dontSendNotification);
    hhDensityLabel.setSize(30, 20);
    hhDensityLabel.attachToComponent(&hhDensitySlider, false);
    hhDensityLabel.setColour(Label::ColourIds::textColourId, dadBodLookAndFeel.getHighlightColour());
    hhDensityLabel.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&hhDensityLabel);
    hhDensityAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "hhDensityParamID",hhDensitySlider);
    
    minBeatSlider.setSliderStyle(Slider::IncDecButtons);
    minBeatSlider.setRange(0, 4, 1);
    minBeatSlider.setValue(0);
    minBeatSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&minBeatSlider);
    minBeatSlider.addListener(this);
    minBeatLabel.setText("Min beat: 1/4", dontSendNotification);
    minBeatLabel.setJustificationType(Justification::centredBottom);
    minBeatLabel.attachToComponent(&minBeatSlider, false);
    addAndMakeVisible(&minBeatLabel);
    minBeatAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "minBeatParamID", minBeatSlider);
    
    /* non audioparameter combo boxes */
    waveformComboBox.addItem("sine", 1);
    waveformComboBox.addItem("sloped-square", 2);
    waveformComboBox.addItem("triangle", 3);
    waveformComboBox.addItem("square", 4);
    waveformComboBox.addSeparator();
    waveformComboBox.setText("sloped-square");
    addAndMakeVisible(&waveformComboBox);
    waveformComboBox.addListener(this);
    
    startTimer(300);
    
    minBeatLabel.setText("Euclid beat: " + getGridBeatString(), dontSendNotification);
    randomToggleButton.setAlpha(0.2f);
    waveformComboBox.setAlpha(0.2f);
    mapXSlider.setAlpha(1.0f);
    mapXLabel.setAlpha(1.0f);
    mapYSlider.setAlpha(1.0f);
    mapYLabel.setAlpha(1.0f);
    kickDensitySlider.setAlpha(1.0f);
    kickDensityLabel.setAlpha(1.0f);
    snareDensitySlider.setAlpha(1.0f);
    snareDensityLabel.setAlpha(1.0f);
    hhDensitySlider.setAlpha(1.0f);
    hhDensityLabel.setAlpha(1.0f);
    stereoToggleButton.setAlpha(1.0f);
    
}

GenTremoloAudioProcessorEditor::~GenTremoloAudioProcessorEditor()
{
}

//==============================================================================
void GenTremoloAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour(getLookAndFeel().findColour(Label::ColourIds::textColourId));
    g.setFont(dadBodLookAndFeel.getTitleTypefacePtr());
    g.setFont(dadBodLookAndFeel.getTitleFontSize());
    g.drawFittedText ("Gen Tremolo 0.0.1", getLocalBounds(), Justification::topLeft, 1);
    g.drawRoundedRectangle(4.0f, topBoxTop, (float)getWidth()-8.0f, 107.0f, cornerSize, dadBodLookAndFeel.smallLineWidth);
    
    g.setColour(dadBodLookAndFeel.getTestGridColour());
    
    /* the drawn lines here is purely for testing alignment and should be removed for public releases. */
    for (int i = 1; i < 6; i++) {
        g.drawLine(((float)getWidth())/6.0f*((float) i), 1.0f, ((float)getWidth())/6.0f*((float) i), 399.0f);
    }
    g.drawLine(4.0f, ((float)getHeight())/2.0f, ((float)getWidth())-4.0f, ((float)getHeight())/2.0f); // for alignment testing
    g.drawLine(4.0f, ((float)getHeight())/6.0f*5.0f, ((float)getWidth())-4.0f, ((float)getHeight())/6.0f*5.0f); // for alignment testing
    /* end test line drawing */
    
    g.setColour(dadBodLookAndFeel.getHighlightColour());

    /* draw euclid box */
    g.drawRoundedRectangle(4.0f, (float)topBoxBottom, (float)getWidth() - 8.0f, 129.0f, cornerSize, dadBodLookAndFeel.smallLineWidth);
    g.setColour(dadBodLookAndFeel.getSecondarySectionColour());
    
    /* draw LFO box */
    g.drawRoundedRectangle(4.0f, (float)euclidBoxBottom, (float)getWidth() - 8.0f, 129.0f, cornerSize, dadBodLookAndFeel.smallLineWidth);
    float lineWidth = (float)getWidth() - 1.0f;

    g.setColour(dadBodLookAndFeel.getOpaqueStringColour());
    g.drawRect(1.0f, (float)titleBoxBottom, lineWidth, 1.0f); // title divider line
    g.drawRect(1.0f, (float)topBoxBottom, lineWidth, 1.0f);   // top box divider line
    g.drawRect(1.0f, (float)euclidBoxBottom, lineWidth, 1.0f); // euclid box divider line
}

void GenTremoloAudioProcessorEditor::comboBoxChanged(ComboBox* comboBox) {
    if (comboBox == &waveformComboBox) {
        switch (comboBox->getSelectedId()) {
            case 1:
                processor.trem_waveform_indicator = GenTremoloAudioProcessor::kWaveformSine;
                break;
            case 2:
                processor.trem_waveform_indicator = GenTremoloAudioProcessor::kWaveformSquareSlopedEdges;
                break;
            case 3:
                processor.trem_waveform_indicator = GenTremoloAudioProcessor::kWaveformTriangle;
                break;
            case 4:
                processor.trem_waveform_indicator = GenTremoloAudioProcessor::kWaveformSquare;
                break;
            default:
                processor.trem_waveform_indicator = GenTremoloAudioProcessor::kWaveformSine;
                break;
        }
    }
}

void GenTremoloAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    if (slider == &minBeatSlider) {
        if (randomToggleButton.getToggleState() || standardToggleButton.getToggleState())
            minBeatLabel.setText("Min beat: " + getMinBeatString(), dontSendNotification);
        if (euclidToggleButton.getToggleState())
            minBeatLabel.setText("Euclid beat: " + getGridBeatString(), dontSendNotification);
    }
}

String GenTremoloAudioProcessorEditor::getMinBeatString() {
    switch ((int)minBeatSlider.getValue()) {
        case 0:
            return "1/64th";
        case 1:
            return "1/32nd";
        case 2:
            return "1/16th";
        case 3:
            return "1/8th";
        case 4:
            return "1/4th";
        default:
            return "n/a";
    }
}


// TODO deal with the fact that the min beat slider has two choices for 1/4th... 64th beat doesn't work because its too small for euclidgrid resolution.
String GenTremoloAudioProcessorEditor::getGridBeatString() {
    switch ((int)minBeatSlider.getValue()) {
        case 0:
            return "1/32nd";
        case 1:
            return "1/16th";
        case 2:
            return "1/8th";
        case 3:
            return "1/4th";
        case 4:
            return "1/2";
        default:
            return "n/a";
    }
}

void GenTremoloAudioProcessorEditor::buttonClicked(Button* button) {
    if (button == &randomToggleButton || button == &standardToggleButton) {
        minBeatLabel.setText("Min beat: " + getMinBeatString(), dontSendNotification);
        randomToggleButton.setAlpha(1.0f);
        waveformComboBox.setAlpha(1.0f);
        mapXSlider.setAlpha(0.2f);
        mapXLabel.setAlpha(0.2f);
        mapYSlider.setAlpha(0.2f);
        mapYLabel.setAlpha(0.2f);
        kickDensitySlider.setAlpha(0.2f);
        kickDensityLabel.setAlpha(0.2f);
        snareDensitySlider.setAlpha(0.2f);
        snareDensityLabel.setAlpha(0.2f);
        hhDensitySlider.setAlpha(0.2f);
        hhDensityLabel.setAlpha(0.2f);
        stereoToggleButton.setAlpha(0.2f);
    }
    if (button == &euclidToggleButton) {
        minBeatLabel.setText("Euclid beat: " + getGridBeatString(), dontSendNotification);
        randomToggleButton.setAlpha(0.2f);
        waveformComboBox.setAlpha(0.2f);
        mapXSlider.setAlpha(1.0f);
        mapXLabel.setAlpha(1.0f);
        mapYSlider.setAlpha(1.0f);
        mapYLabel.setAlpha(1.0f);
        kickDensitySlider.setAlpha(1.0f);
        kickDensityLabel.setAlpha(1.0f);
        snareDensitySlider.setAlpha(1.0f);
        snareDensityLabel.setAlpha(1.0f);
        hhDensitySlider.setAlpha(1.0f);
        hhDensityLabel.setAlpha(1.0f);
        stereoToggleButton.setAlpha(1.0f);
    }
}

/* For testing purposes */
void GenTremoloAudioProcessorEditor::timerCallback() {
//    if (processor.isEuclid) {
//        String labelText = String("b ") + String(processor.euclidBeatDivisor) + String(" s ") + String(processor.euclidStep);
//        testLabel.setText(labelText, dontSendNotification);
//    } else {
//        testLabel.setText("off", dontSendNotification);
//    }
    testLabel.setText("n: " + String(vFontPtr->getName()), dontSendNotification);
}

void GenTremoloAudioProcessorEditor::resized() {
    /* This is generally where you'll want to lay out the positions of any
     * subcomponents in your editor.. */
    
    /*** Top Box ***/
    chaosSlider.setBounds(chaosSliderX, chaosSliderY - chaosSliderDiameter/6 + 4, chaosSliderDiameter, chaosSliderDiameter);
    mixSlider.setBounds(mixSliderX - chaosSliderDiameter/2, chaosSliderY - chaosSliderDiameter/6 + 4, chaosSliderDiameter, chaosSliderDiameter);
    
    /*** Euclid Box ***/
    euclidToggleButton.setBounds(euclidToggleX, euclidToggleY - toggleHeight - 2, getWidth()/6, toggleHeight);
    stereoToggleButton.setBounds(euclidToggleButton.getX(), euclidToggleButton.getY() + toggleHeight + 4, euclidToggleButton.getWidth(), euclidToggleButton.getHeight());
    kickDensitySlider.setBounds(firstEuclidKnobX, euclidKnobY, euclidKnobDiameter, euclidKnobDiameter);
    snareDensitySlider.setBounds(kickDensitySlider.getX() + knobXOffset, euclidKnobY, euclidKnobDiameter, euclidKnobDiameter);
    hhDensitySlider.setBounds(snareDensitySlider.getX() + knobXOffset, euclidKnobY, euclidKnobDiameter, euclidKnobDiameter);
    mapXSlider.setBounds(hhDensitySlider.getX() + knobXOffset, euclidKnobY, euclidKnobDiameter, euclidKnobDiameter);
    mapYSlider.setBounds(mapXSlider.getX() + knobXOffset, euclidKnobY, euclidKnobDiameter, euclidKnobDiameter);
    
    /*** LFO Box ***/
    waveformComboBox.setBounds(waveformX, lfoBoxY - getHeight()/14, getWidth()/4, getHeight()/7);
    // euclidLabel is just for testing
    testLabel.setBounds(waveformComboBox.getX(), waveformComboBox.getY() - waveformComboBox.getHeight()/2 - 7, waveformComboBox.getWidth(), waveformComboBox.getHeight());
    
    standardToggleButton.setBounds(euclidToggleX, standardToggleY - toggleHeight - 2, getWidth()/5, toggleHeight);
    randomToggleButton.setBounds(euclidToggleX, standardToggleButton.getY() + toggleHeight + 4, getWidth()/5, toggleHeight);
    
    minBeatLabel.setBounds(getWidth()/2 - 70, lfoBoxY - 10, 140, 20);
    minBeatSlider.setBounds(getWidth()/2 - minBeatSliderWidth/2, lfoBoxY - minBeatSliderHeight/2, minBeatSliderWidth, minBeatSliderHeight);

    
    // TODO smarter or automatic resizing. Like example from Juce audio parameter tutorial
    
}
