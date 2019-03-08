/*
  This code is copyright 2019 Jonathan Thomson, jethomson.wordpress.com

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose and without fee is hereby
  granted, provided that the above copyright notice appear in all
  copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#include "ReAnimator_demo.h"
#include "ReAnimator.h"

#define LEDS_DATA_PIN 2
#define LED_STRIP_MILLIAMPS 100

CRGB leds[NUM_LEDS];

uint8_t gdynamic_hue = 0;
uint8_t gstatic_hue = HUE_ALIEN_GREEN;
uint8_t grandom_hue = 0;

ReAnimator GlowSerum(leds, &gdynamic_hue, LED_STRIP_MILLIAMPS);

void setup() {

    // for the ADMP401 microphone wire the AREF pin to 3.3V pin
    // and tell the uc we're using an analog reference
    //analogReference(EXTERNAL);

    Serial.begin(57600);

    FastLED.setMaxPowerInVoltsAndMilliamps(LED_STRIP_VOLTAGE, LED_STRIP_MILLIAMPS);
    FastLED.setCorrection(TypicalSMD5050);
    FastLED.addLeds<WS2812B, LEDS_DATA_PIN, GRB>(leds, NUM_LEDS);

    random16_set_seed(analogRead(A0));

    GlowSerum.set_pattern(ORBIT);
    GlowSerum.set_overlay(NO_OVERLAY, false);
    GlowSerum.set_overlay(NO_OVERLAY, true);

    GlowSerum.set_autocycle_interval(10000);
    GlowSerum.set_autocycle_enabled(false);
    GlowSerum.set_flipflop_interval(6000);
    GlowSerum.set_flipflop_enabled(false);

    FastLED.clear();
    FastLED.show();
}


void loop() {
    static bool go = false;

    const uint8_t PATTERNS_NUM = 34;
    const Pattern patterns[PATTERNS_NUM] = {ORBIT, THEATER_CHASE, RUNNING_LIGHTS,
                                            SHOOTING_STAR, CYLON, JUGGLE, MITOSIS,
                                            BUBBLES, SPARKLE, MATRIX, WEAVE, STARSHIP_RACE,
                                            PAC_MAN, BALLS,
                                            HALLOWEEN_FADE, HALLOWEEN_ORBIT,
                                            DYNAMIC_RAINBOW,
                                            SOLID, SOLID, SOLID, SOLID, DYNAMIC_RAINBOW,
                                            ORBIT, THEATER_CHASE, RUNNING_LIGHTS,
                                            SHOOTING_STAR,
                                            SOUND_BLOCKS, SOUND_BLOCKS, SOUND_RIBBONS, SOUND_RIBBONS,
                                            SOUND_ORBIT, SOUND_ORBIT, SOUND_RIPPLE, SOUND_RIPPLE};

    const Overlay overlays[PATTERNS_NUM] = {NO_OVERLAY, NO_OVERLAY, NO_OVERLAY,
                                            NO_OVERLAY, NO_OVERLAY, NO_OVERLAY, NO_OVERLAY,
                                            NO_OVERLAY, NO_OVERLAY, NO_OVERLAY, NO_OVERLAY, NO_OVERLAY,
                                            NO_OVERLAY, NO_OVERLAY,
                                            NO_OVERLAY, NO_OVERLAY,
                                            NO_OVERLAY,
                                            GLITTER, BREATHING, CONFETTI, FLICKER, FROZEN_DECAY,
                                            NO_OVERLAY, NO_OVERLAY, NO_OVERLAY,
                                            NO_OVERLAY,
                                            NO_OVERLAY, NO_OVERLAY, NO_OVERLAY, NO_OVERLAY,
                                            NO_OVERLAY, NO_OVERLAY, NO_OVERLAY, NO_OVERLAY};

    static uint8_t poi = 0;

    EVERY_N_MILLISECONDS(19200) {
        poi = (poi+1) % PATTERNS_NUM;
        GlowSerum.set_pattern(patterns[poi]);
        GlowSerum.set_overlay(overlays[poi], false);

        if (poi >= 22 && poi <= 25) {
            GlowSerum.set_flipflop_enabled(true);
        }
        else {
            GlowSerum.set_flipflop_enabled(false);
        }
    }

    EVERY_N_MILLISECONDS(100) { gdynamic_hue+=3; grandom_hue = random8(); }

    GlowSerum.reanimate();
    FastLED.show(); // only want to use one controller so management of brightness and power usage is more easy
}






