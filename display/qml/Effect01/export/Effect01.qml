// Created with Qt Quick Effect Maker (version 0.43), Fri May 19 05:42:54 2023

import QtQuick

Item {
    id: rootItem

    // This is the main source for the effect
    property Item source: null

    // This property defines how much the source brightness is increased or decreased.
    //
    // The value ranges from -1.0 to 1.0. By default, the property is set to 0.0 (no change).
    property real brightnessContrastBrightness: 0.561287
    // This property defines how much the source contrast is increased or decreased. The decrease of the contrast is linear, but the increase is applied with a non-linear curve to allow very high contrast adjustment at the high end of the value range.
    //
    // The value ranges from -1.0 to 1.0. By default, the property is set to 0.0 (no change).
    property real brightnessContrastContrast: 0.927249
    // This property defines a multiplier for extending the blur radius.
    //
    // The value ranges from 0.0 (not multiplied) to inf. By default, the property is set to 0.0. Incresing the multiplier extends the blur radius, but decreases the blur quality. This is more performant option for a bigger blur radius than BLUR_HELPER_MAX_LEVEL as it doesn't increase the amount of texture lookups.
    //
    // Note: This affects to both blur and shadow effects.
    property real blurMultiplier: 1.486
    // This value defines the softness of the shadow. A larger value causes the edges of the shadow to appear more blurry.
    property real fastBlurAmount: 0.544753

    BlurHelper {
        id: blurHelper
        anchors.fill: parent
        property int blurMax: 64
        property real blurMultiplier: rootItem.blurMultiplier
    }
    ShaderEffect {
        readonly property alias iSource: rootItem.source
        readonly property alias iSourceBlur1: blurHelper.blurSrc1
        readonly property alias iSourceBlur2: blurHelper.blurSrc2
        readonly property alias iSourceBlur3: blurHelper.blurSrc3
        readonly property alias iSourceBlur4: blurHelper.blurSrc4
        readonly property alias iSourceBlur5: blurHelper.blurSrc5
        readonly property alias brightnessContrastBrightness: rootItem.brightnessContrastBrightness
        readonly property alias brightnessContrastContrast: rootItem.brightnessContrastContrast
        readonly property alias blurMultiplier: rootItem.blurMultiplier
        readonly property alias fastBlurAmount: rootItem.fastBlurAmount

        vertexShader: 'effect01.vert.qsb'
        fragmentShader: 'effect01.frag.qsb'
        anchors.fill: parent
    }
}
