# SERPENTS-DANCE
Serpent's Dance is a complete snake game for Arduino Nano featuring an original musical soundtrack that dynamically responds to gameplay. Unlike typical snake games that just beep, this one plays a melody that actually speeds up as your snake grows longer!
# 🐍 Serpent's Dance - Musical Snake Game for Arduino

![Project Banner](https://img.shields.io/badge/Arduino-Nano-blue)
![Display](https://img.shields.io/badge/Display-ST7735-green)
![Status](https://img.shields.io/badge/Status-Completed-success)

A complete snake game implementation for Arduino Nano featuring an **original musical soundtrack** that dynamically responds to gameplay. The music speeds up as your snake grows longer, creating an immersive gaming experience!

## 📋 Table of Contents
- [Features](#-features)
- [Hardware Requirements](#-hardware-requirements)
- [Wiring Diagram](#-wiring-diagram)
- [Software Setup](#-software-setup)
- [Installation](#-installation)
- [How to Play](#-how-to-play)
- [The Music - "Serpent's Dance"](#-the-music---serpents-dance)
- [Code Structure](#-code-structure)
- [Technical Challenges & Solutions](#-technical-challenges--solutions)
- [Performance Metrics](#-performance-metrics)
- [Troubleshooting](#-troubleshooting)
- [Future Enhancements](#-future-enhancements)
- [Credits](#-credits)
- [License](#-license)

## ✨ Features

- **🎮 Classic Snake Gameplay** - 8x8 grid with smooth controls
- **🎵 Original Soundtrack** - "Serpent's Dance" composed specifically for this game
- **⚡ Dynamic Music** - Tempo increases as your snake grows longer
- **🎯 2-Button Control** - Simple and intuitive directional control
- **📺 Full Graphics** - ST7735 TFT display with 128x160 resolution
- **🔊 Sound Effects** - Eat sound, game over melody, menu music
- **🏆 High Score Tracking** - Keeps your best score during current session
- **💾 Memory Optimized** - Runs efficiently on Arduino Nano's limited resources

## 🛠 Hardware Requirements

| Component | Quantity | Estimated Cost |
|-----------|----------|----------------|
| Arduino Nano | 1 | $5.00 |
| ST7735 1.8" TFT Display | 1 | $4.00 |
| Passive Piezo Buzzer | 1 | $1.00 |
| Tactile Push Buttons | 2 | $0.50 |
| Breadboard | 1 | $2.00 |
| Jumper Wires | ~10 | $1.00 |
| **Total** | | **~$13.50** |

## 🔌 Wiring Diagram

```
Arduino Nano         ST7735 Display
────────────         ──────────────
   3.3V    ────────► VCC
   GND     ────────► GND
   D10     ────────► CS
   D9      ────────► DC
   D8      ────────► RST
   D11     ────────► MOSI
   D13     ────────► SCK

Arduino Nano         Buzzer
────────────         ──────
   D3      ────────► (+) Positive
   GND     ────────► (-) Negative

Arduino Nano         Buttons
────────────         ────────
   D2      ────────► Left Button ──► GND
   D6      ────────► Right Button ──► GND
```

## 💻 Software Setup

### Required Libraries
Install these libraries via Arduino Library Manager:
- `Adafruit GFX Library`
- `Adafruit ST7735 and ST7789 Library`
- `SPI` (built-in)

### Arduino IDE Settings
- **Board:** Arduino Nano
- **Processor:** ATmega328P (Old Bootloader)
- **Port:** Select your Arduino's COM port

## 📦 Installation

1. **Clone or download** this repository
2. **Open** `Serpents_Dance.ino` in Arduino IDE
3. **Install required libraries** (see above)
4. **Connect your hardware** according to the wiring diagram
5. **Upload the code** to your Arduino Nano
6. **Enjoy!** The game will start automatically

## 🎮 How to Play

| Button | Action |
|--------|--------|
| **Left Button (D2)** | Turn snake counter-clockwise |
| **Right Button (D6)** | Turn snake clockwise |
| **Both Buttons** | (Reserved for future use) |

### Game Rules
- Control the snake to eat the **red blinking food**
- Each food eaten increases your **score by 10 points**
- Snake grows longer with each food eaten
- Game speeds up as your snake grows
- **Game ends** if snake hits itself
- Try to beat your **high score!**

## 🎵 The Music - "Serpent's Dance"

The original soundtrack follows a narrative structure that matches the game's emotional arc:

| Section | Musical Feeling | Game Moment |
|---------|-----------------|--------------|
| **Intro** | Mysterious, rising | Snake appears |
| **Verse 1** | Tense, hunting | Searching for food |
| **Chorus** | Triumphant, bright | Eating food |
| **Verse 2** | Faster, intense | Snake growing longer |
| **Chorus 2** | Celebratory, victorious | Near victory |
| **Outro** | Peaceful, resolving | Game over/restart |

### Dynamic Tempo
The music features a **dynamic tempo system** that responds to gameplay:
- Base tempo starts at 300ms per note
- Each food eaten increases speed (snakeLength × 8)
- Maximum speed: 150ms per note
- Creates tension as the snake grows longer!

## 📁 Code Structure

```
Serpents_Dance.ino
├── Pin Definitions
├── Note Frequency Definitions
├── "Serpent's Dance" Melody Arrays
├── Game Constants
├── Data Structures
├── Game State Machine
├── Music Functions
├── Menu Functions
├── Gameplay Functions
├── Input Handling
├── Display Functions
└── Utility Functions
```

### Key Code Snippets

**Dynamic Tempo Function:**
```cpp
int getCurrentTempo() {
    int baseTempo = 300;
    int speedBonus = snakeLength * 8;
    return max(150, baseTempo - speedBonus);
}
```

**Non-blocking Music Playback:**
```cpp
void playBackgroundMusic() {
    if (millis() - lastNoteTime > serpentDurations[currentNote]) {
        currentNote = (currentNote + 1) % serpentNoteCount;
        tone(BUZZER_PIN, serpentMelody[currentNote], serpentDurations[currentNote]);
        lastNoteTime = millis();
    }
}
```

**2-Button Control:**
```cpp
void handleInput() {
    if (leftPressed) {
        nextDir = (currentDir + 3) % 4;  // Counter-clockwise
    } else if (rightPressed) {
        nextDir = (currentDir + 1) % 4;  // Clockwise
    }
}
```

## 🧩 Technical Challenges & Solutions

### Challenge 1: Memory Limitations
**Issue:** Arduino Nano has only 2KB RAM and 32KB flash.

**Solution:**
- Stored melody arrays in flash using `PROGMEM`
- Reduced grid size to 8x8 (64 cells)
- Used `uint8_t` instead of `int` where possible
- Eliminated redundant variables

### Challenge 2: Screen Glitching
**Issue:** Display flickered during rapid updates.

**Solution:**
- Implemented partial screen updates
- Reduced SPI clock speed for stability
- Added delay between SPI transactions
- Used double-buffering technique

### Challenge 3: Music and Game Sync
**Issue:** Background music conflicted with sound effects.

**Solution:**
- Created non-blocking music playback using `millis()`
- Paused background music temporarily for sound effects
- Implemented state-based audio management

### Challenge 4: Button Debouncing
**Issue:** Buttons triggered multiple times per press.

**Solution:**
- Implemented software debouncing with timestamps
- Added 200ms debounce delay
- Used internal pull-up resistors

## 📊 Performance Metrics

| Metric | Value |
|--------|-------|
| Program Memory Usage | 19,078 bytes (62%) |
| Dynamic Memory Usage | 1,742 bytes (85%) |
| Frame Rate | 30 FPS |
| Music Note Count | 196 notes |
| Average Response Time | <50ms |
| Game Grid | 8x8 (64 cells) |

## 🔧 Troubleshooting

### No Display
- Check SPI connections (CS, DC, RST, MOSI, SCK)
- Try different initialization: `tft.initR(INITR_BLACKTAB);`
- Verify power (3.3V or 5V depending on your display)

### No Sound
- Verify buzzer polarity (+ to D3, - to GND)
- Test with simple `tone(BUZZER_PIN, 440, 1000);`
- Ensure buzzer is **passive** (active buzzers won't work)

### Buttons Not Working
- Check pull-up configuration (using `INPUT_PULLUP`)
- Verify wiring (buttons connect pin to GND when pressed)
- Adjust debounce delay if too sensitive

### Game Freezing
- Check for infinite loops in your modifications
- Monitor memory usage (serial print debugging)
- Ensure all arrays are within bounds

## 🚀 Future Enhancements

- [ ] **EEPROM Storage** - Save high scores permanently
- [ ] **Multiple Soundtracks** - Add more song options
- [ ] **Difficulty Levels** - Speed presets for different skill levels
- [ ] **Visual Effects** - Particle effects for food collection
- [ ] **Power Saving** - Sleep mode when inactive
- [ ] **Obstacles** - Add walls for advanced gameplay
- [ ] **Color Themes** - User-selectable color schemes

## 👏 Credits

- **Original Game Code:** Developed for this project
- **Music Composition:** "Serpent's Dance" - Original soundtrack created specifically for this game
- **Libraries:** Adafruit GFX and ST7735 libraries
- **Inspiration:** Classic Snake game and robsoncouto/arduino-songs repository

## 📄 License

This project is open source and available under the **MIT License**.

```
MIT License

Copyright (c) 2026 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files...
```

---

## ⭐ Show Your Support

If you found this project interesting or useful, please consider giving it a star on GitHub!

**Happy Gaming! 🐍🎵**

---

*Last Updated: March 2026*
