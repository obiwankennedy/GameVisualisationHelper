#version 440

layout(location = 0) in vec2 texCoord;
layout(location = 1) in vec2 fragCoord;
layout(location = 0) out vec4 fragColor;

layout(std140, binding = 0) uniform buf {
    mat4 qt_Matrix;
    float qt_Opacity;
    float brightnessContrastBrightness;
    float brightnessContrastContrast;
    float blurMultiplier;
    float fastBlurAmount;
};

layout(binding = 1) uniform sampler2D iSource;

layout(binding = 2) uniform sampler2D iSourceBlur1;
layout(binding = 3) uniform sampler2D iSourceBlur2;
layout(binding = 4) uniform sampler2D iSourceBlur3;
layout(binding = 5) uniform sampler2D iSourceBlur4;
layout(binding = 6) uniform sampler2D iSourceBlur5;

#define BLUR_HELPER_MAX_LEVEL 64

layout(location = 2) in vec4 blurWeight1;
layout(location = 3) in vec2 blurWeight2;

void main() {
    fragColor = texture(iSource, texCoord);
    {
        vec4 blurredColor = texture(iSource, texCoord) * blurWeight1[0];
        blurredColor += texture(iSourceBlur1, texCoord) * blurWeight1[1];
    #if (BLUR_HELPER_MAX_LEVEL > 2)
        blurredColor += texture(iSourceBlur2, texCoord) * blurWeight1[2];
    #endif
    #if (BLUR_HELPER_MAX_LEVEL > 8)
        blurredColor += texture(iSourceBlur3, texCoord) * blurWeight1[3];
    #endif
    #if (BLUR_HELPER_MAX_LEVEL > 16)
        blurredColor += texture(iSourceBlur4, texCoord) * blurWeight2[0];
    #endif
    #if (BLUR_HELPER_MAX_LEVEL > 32)
        blurredColor += texture(iSourceBlur5, texCoord) * blurWeight2[1];
    #endif
    
        fragColor = blurredColor;
    }
    {
        fragColor.rgb /= max(1.0/256.0, fragColor.a);
        float c = 1.0 + brightnessContrastContrast;
        float contrastGainFactor = 1.0 + c * c * c * c * step(0.0, brightnessContrastContrast);
        fragColor.rgb = ((fragColor.rgb - 0.5) * (contrastGainFactor * brightnessContrastContrast + 1.0)) + 0.5;
        fragColor.rgb = mix(fragColor.rgb, vec3(step(0.0, brightnessContrastBrightness)), abs(brightnessContrastBrightness));
        fragColor = vec4(fragColor.rgb * fragColor.a, fragColor.a);
    }
    fragColor = fragColor * qt_Opacity;
}
