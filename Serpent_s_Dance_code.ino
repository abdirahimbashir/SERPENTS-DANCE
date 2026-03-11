#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// TFT Display pins
#define TFT_CS   10
#define TFT_DC   9
#define TFT_RST  8

// Your buzzer and buttons
#define BUZZER_PIN 3
#define BTN_LEFT 2
#define BTN_RIGHT 6

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// ================ COMPLETE NOTE DEFINITIONS ================
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define REST 0

// ================ ORIGINAL "SERPENT'S DANCE" MELODY ================
// Created exclusively for your snake game!

int serpentMelody[] = {
  // === INTRO (Mysterious opening - snake appears) ===
  NOTE_E4, NOTE_G4, NOTE_B4, NOTE_E5,  // Rising serpent
  NOTE_D5, NOTE_B4, NOTE_G4, NOTE_E4,  // Falling back
  NOTE_FS4, NOTE_A4, NOTE_CS5, NOTE_FS5,  // Quick coil
  NOTE_E5, REST, NOTE_DS5, NOTE_E5,  // Strike and pause
  
  // === VERSE 1 (The hunt - searching for food) ===
  NOTE_E5, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_B4, NOTE_D5,
  NOTE_C5, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_FS5, NOTE_E5,
  NOTE_D5, NOTE_B4, NOTE_G4, NOTE_B4, NOTE_D5, NOTE_E5, NOTE_G5, NOTE_FS5,
  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_G5, NOTE_E5, REST,
  
  // === CHORUS (Victory - when eating food) ===
  NOTE_G5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_D5,
  NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_FS5, NOTE_E5,
  NOTE_G5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_G4, REST,
  
  // === VERSE 2 (Faster - more intense) ===
  NOTE_E5, NOTE_FS5, NOTE_G5, NOTE_FS5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4,
  NOTE_G4, NOTE_B4, NOTE_D5, NOTE_E5, NOTE_FS5, NOTE_G5, NOTE_A5, NOTE_G5,
  NOTE_E5, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_G5,
  NOTE_FS5, NOTE_E5, NOTE_FS5, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_A4, REST,
  
  // === CHORUS 2 (Even more victorious) ===
  NOTE_G5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_D5,
  NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6, NOTE_B5,
  NOTE_A5, NOTE_G5, NOTE_FS5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, REST,
  
  // === OUTRO (The serpent rests) ===
  NOTE_E4, NOTE_G4, NOTE_B4, NOTE_E5,  // Slow descent
  NOTE_D5, NOTE_B4, NOTE_G4, NOTE_E4,
  NOTE_C5, NOTE_A4, NOTE_FS4, NOTE_D4,
  NOTE_E4, NOTE_G4, NOTE_B4, NOTE_E4, REST
};

int serpentDurations[] = {
  // INTRO - slower, mysterious
  400, 400, 400, 600,
  400, 400, 400, 600,
  300, 300, 300, 600,
  400, 200, 200, 800,
  
  // VERSE 1 - moderate speed
  300, 300, 200, 200, 200, 200, 300, 300,
  300, 200, 200, 300, 200, 200, 300, 300,
  200, 200, 200, 200, 200, 200, 300, 200,
  300, 200, 200, 200, 200, 300, 400, 200,
  
  // CHORUS - bright and energetic
  200, 200, 200, 200, 200, 200, 200, 300,
  200, 200, 200, 200, 200, 200, 200, 300,
  200, 200, 200, 200, 200, 200, 200, 300,
  300, 200, 200, 200, 400, 200, 400, 200,
  
  // VERSE 2 - faster, more intense
  200, 200, 200, 200, 200, 200, 200, 200,
  200, 200, 200, 200, 200, 200, 200, 300,
  150, 150, 150, 150, 150, 150, 150, 300,
  150, 150, 150, 150, 150, 150, 400, 200,
  
  // CHORUS 2 - triumphant
  150, 150, 150, 150, 150, 150, 150, 200,
  150, 150, 150, 150, 150, 150, 150, 200,
  150, 150, 150, 150, 150, 150, 150, 300,
  150, 150, 150, 150, 150, 150, 600, 200,
  
  // OUTRO - slowing down
  400, 400, 400, 600,
  400, 400, 400, 600,
  400, 400, 400, 600,
  300, 300, 300, 800, 200
};

int serpentNoteCount = sizeof(serpentMelody) / sizeof(serpentMelody[0]);

// Game constants
#define GRID_SIZE 8
#define CELL_SIZE 16
#define MAX_SNAKE 64

// Direction constants
#define DIR_UP 0
#define DIR_RIGHT 1
#define DIR_DOWN 2
#define DIR_LEFT 3

// Game states
enum GameState {
  MENU,
  PLAYING,
  GAME_OVER,
  HIGH_SCORE
};

// Snake segment structure
struct Point {
  int x;
  int y;
};

// Game variables
GameState gameState = MENU;
Point snake[MAX_SNAKE];
int snakeLength = 3;
int currentDir = DIR_RIGHT;
int nextDir = DIR_RIGHT;
Point food;
int score = 0;
int highScore = 0;
unsigned long lastMoveTime = 0;
int moveDelay = 300;

// Music variables
int currentNote = 0;
unsigned long lastNoteTime = 0;
bool musicPlaying = false;

// Button debouncing
unsigned long lastButtonTime = 0;
const int debounceDelay = 200;

// Sound effects
int eatMelody[] = {NOTE_C5, NOTE_E5, NOTE_G5};
int eatDurations[] = {100, 100, 200};
int gameOverMelody[] = {NOTE_C4, NOTE_G3, NOTE_E3, NOTE_C3};
int gameOverDurations[] = {300, 300, 300, 600};
int menuMelody[] = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_E4, NOTE_C4};
int menuDurations[] = {200, 200, 200, 400, 200, 200, 400};

void setup() {
  Serial.begin(9600);
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);
  
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextWrap(false);
  tft.setRotation(0);
  
  loadHighScore();
  showSplashScreen();
  playMelody(menuMelody, menuDurations, 7);
  delay(2000);
  
  showMenu();
}

void loop() {
  switch(gameState) {
    case MENU:
      handleMenu();
      break;
    case PLAYING:
      handleGameplay();
      break;
    case GAME_OVER:
      handleGameOver();
      break;
    case HIGH_SCORE:
      showHighScore();
      break;
  }
}

// ================ MUSIC FUNCTIONS ================

int getCurrentTempo() {
  // Music speeds up as snake grows longer!
  int baseTempo = 300;
  int speedBonus = snakeLength * 8;
  return max(150, baseTempo - speedBonus);
}

void playBackgroundMusic() {
  if (gameState != PLAYING) {
    musicPlaying = false;
    noTone(BUZZER_PIN);
    return;
  }
  
  musicPlaying = true;
  int currentTempo = getCurrentTempo();
  
  if (millis() - lastNoteTime > serpentDurations[currentNote]) {
    // Move to next note
    currentNote = (currentNote + 1) % serpentNoteCount;
    
    if (serpentMelody[currentNote] > 0) {
      tone(BUZZER_PIN, serpentMelody[currentNote], serpentDurations[currentNote]);
    } else {
      noTone(BUZZER_PIN);
    }
    
    lastNoteTime = millis();
  }
}

void playMelody(int melody[], int durations[], int length) {
  for (int i = 0; i < length; i++) {
    tone(BUZZER_PIN, melody[i], durations[i]);
    delay(durations[i] + 30);
  }
  noTone(BUZZER_PIN);
}

void playSound(int freq, int duration) {
  tone(BUZZER_PIN, freq, duration);
}

// ================ MENU FUNCTIONS ================

void showMenu() {
  tft.fillScreen(ST7735_BLACK);
  
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(2);
  tft.setCursor(15, 30);
  tft.println("SNAKE");
  
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(10, 60);
  tft.println("Serpent's Dance");
  
  tft.setCursor(10, 80);
  tft.println("Press LEFT to");
  tft.setCursor(10, 95);
  tft.println("start game");
  
  tft.setCursor(10, 115);
  tft.print("High Score: ");
  tft.print(highScore);
  
  // Draw a simple snake
  tft.fillRect(90, 60, 8, 8, ST7735_GREEN);
  tft.fillRect(75, 60, 8, 8, ST7735_GREEN);
  tft.fillRect(60, 60, 8, 8, ST7735_GREEN);
  tft.fillRect(45, 60, 8, 8, ST7735_RED);
}

void handleMenu() {
  if (digitalRead(BTN_LEFT) == LOW && millis() - lastButtonTime > debounceDelay) {
    playSound(NOTE_C5, 100);
    lastButtonTime = millis();
    startNewGame();
    gameState = PLAYING;
    currentNote = 0;
    lastNoteTime = millis();
  }
  
  if (digitalRead(BTN_RIGHT) == LOW && millis() - lastButtonTime > debounceDelay) {
    playSound(NOTE_G4, 100);
    lastButtonTime = millis();
    gameState = HIGH_SCORE;
  }
}

void startNewGame() {
  snakeLength = 3;
  snake[0] = {4, 4};
  snake[1] = {3, 4};
  snake[2] = {2, 4};
  currentDir = DIR_RIGHT;
  nextDir = DIR_RIGHT;
  score = 0;
  moveDelay = 300;
  
  generateFood();
  tft.fillScreen(ST7735_BLACK);
  drawGrid();
}

// ================ GAMEPLAY FUNCTIONS ================

void handleGameplay() {
  // Play background music - speeds up as snake grows!
  playBackgroundMusic();
  
  handleInput();
  
  if (millis() - lastMoveTime > moveDelay) {
    if (!isOpposite(nextDir, currentDir)) {
      currentDir = nextDir;
    }
    
    moveSnake();
    
    if (checkCollisions()) {
      gameOver();
      return;
    }
    
    checkFood();
    drawGame();
    lastMoveTime = millis();
  }
}

void handleInput() {
  if (millis() - lastButtonTime < debounceDelay) return;
  
  bool leftPressed = (digitalRead(BTN_LEFT) == LOW);
  bool rightPressed = (digitalRead(BTN_RIGHT) == LOW);
  
  if (leftPressed || rightPressed) {
    if (leftPressed) {
      nextDir = (currentDir + 3) % 4;
    } else if (rightPressed) {
      nextDir = (currentDir + 1) % 4;
    }
    
    lastButtonTime = millis();
  }
}

void moveSnake() {
  for (int i = snakeLength - 1; i > 0; i--) {
    snake[i] = snake[i - 1];
  }
  
  switch(currentDir) {
    case DIR_UP:    snake[0].y--; break;
    case DIR_RIGHT: snake[0].x++; break;
    case DIR_DOWN:  snake[0].y++; break;
    case DIR_LEFT:  snake[0].x--; break;
  }
  
  // Wrap around edges
  if (snake[0].x < 0) snake[0].x = GRID_SIZE - 1;
  if (snake[0].x >= GRID_SIZE) snake[0].x = 0;
  if (snake[0].y < 0) snake[0].y = GRID_SIZE - 1;
  if (snake[0].y >= GRID_SIZE) snake[0].y = 0;
}

bool checkCollisions() {
  for (int i = 1; i < snakeLength; i++) {
    if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
      return true;
    }
  }
  return false;
}

void checkFood() {
  if (snake[0].x == food.x && snake[0].y == food.y) {
    snakeLength++;
    score += 10;
    
    if (moveDelay > 100) {
      moveDelay -= 15;
    }
    
    // Pause background music briefly for eat sound
    noTone(BUZZER_PIN);
    playMelody(eatMelody, eatDurations, 3);
    // Resume music from where it left off
    lastNoteTime = millis();
    
    generateFood();
    
    if (score > highScore) {
      highScore = score;
    }
  }
}

void generateFood() {
  bool validPosition;
  int attempts = 0;
  
  do {
    validPosition = true;
    food.x = random(0, GRID_SIZE);
    food.y = random(0, GRID_SIZE);
    
    for (int i = 0; i < snakeLength; i++) {
      if (snake[i].x == food.x && snake[i].y == food.y) {
        validPosition = false;
        break;
      }
    }
    
    attempts++;
    if (attempts > 100) {
      victory();
      return;
    }
  } while (!validPosition);
}

void drawGame() {
  tft.fillRect(0, 0, 128, 128, ST7735_BLACK);
  drawGrid();
  
  // Draw snake
  for (int i = 0; i < snakeLength; i++) {
    int x = snake[i].x * CELL_SIZE;
    int y = snake[i].y * CELL_SIZE;
    
    if (i == 0) {
      // Head
      tft.fillRect(x + 2, y + 2, CELL_SIZE - 4, CELL_SIZE - 4, ST7735_GREEN);
      // Eyes
      if (currentDir == DIR_UP || currentDir == DIR_DOWN) {
        tft.fillRect(x + 4, y + 4, 2, 2, ST7735_WHITE);
        tft.fillRect(x + 10, y + 4, 2, 2, ST7735_WHITE);
      } else {
        tft.fillRect(x + 4, y + 8, 2, 2, ST7735_WHITE);
        tft.fillRect(x + 10, y + 8, 2, 2, ST7735_WHITE);
      }
    } else {
      // Body
      tft.fillRect(x + 2, y + 2, CELL_SIZE - 4, CELL_SIZE - 4, ST7735_BLUE);
    }
  }
  
  // Draw food (blinking)
  if ((millis() / 300) % 2 == 0) {
    int fx = food.x * CELL_SIZE;
    int fy = food.y * CELL_SIZE;
    tft.fillCircle(fx + 8, fy + 8, 6, ST7735_RED);
  }
  
  drawHUD();
}

void drawGrid() {
  tft.drawRect(0, 0, 128, 128, ST7735_WHITE);
}

void drawHUD() {
  tft.fillRect(0, 130, 128, 30, ST7735_BLACK);
  
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  
  tft.setCursor(5, 135);
  tft.print("Score:");
  tft.print(score);
  
  tft.setCursor(5, 145);
  tft.print("Best:");
  tft.print(highScore);
  
  // Show music info
  tft.setCursor(65, 135);
  tft.setTextColor(ST7735_MAGENTA);
  tft.print("♪ SERPENT ♪");
  
  // Show tempo indicator
  tft.setCursor(70, 145);
  tft.setTextColor(ST7735_CYAN);
  int tempo = map(snakeLength, 3, 20, 1, 9);
  tft.print("Speed:");
  tft.print(tempo);
}

bool isOpposite(int dir1, int dir2) {
  return (dir1 == DIR_UP && dir2 == DIR_DOWN) ||
         (dir1 == DIR_DOWN && dir2 == DIR_UP) ||
         (dir1 == DIR_LEFT && dir2 == DIR_RIGHT) ||
         (dir1 == DIR_RIGHT && dir2 == DIR_LEFT);
}

// ================ GAME OVER FUNCTIONS ================

void gameOver() {
  gameState = GAME_OVER;
  
  // Stop background music
  musicPlaying = false;
  noTone(BUZZER_PIN);
  
  playMelody(gameOverMelody, gameOverDurations, 4);
  
  for (int i = 0; i < 3; i++) {
    tft.fillScreen(ST7735_RED);
    delay(150);
    tft.fillScreen(ST7735_BLACK);
    delay(150);
  }
}

void victory() {
  // Stop background music
  musicPlaying = false;
  noTone(BUZZER_PIN);
  
  playMelody(menuMelody, menuDurations, 7);
  
  for (int i = 0; i < 5; i++) {
    tft.fillScreen(ST7735_GREEN);
    delay(200);
    tft.fillScreen(ST7735_BLACK);
    delay(200);
  }
  
  gameState = GAME_OVER;
}

void handleGameOver() {
  tft.fillScreen(ST7735_BLACK);
  
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(2);
  tft.setCursor(20, 40);
  tft.println("GAME");
  tft.setCursor(20, 60);
  tft.println("OVER");
  
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(10, 90);
  tft.print("Score: ");
  tft.print(score);
  
  tft.setCursor(10, 105);
  tft.print("Best: ");
  tft.print(highScore);
  
  tft.setCursor(10, 125);
  tft.setTextColor(ST7735_CYAN);
  tft.println("Press LEFT to play");
  
  if (digitalRead(BTN_LEFT) == LOW && millis() - lastButtonTime > debounceDelay) {
    playSound(NOTE_C5, 100);
    lastButtonTime = millis();
    gameState = MENU;
    showMenu();
  }
}

void showHighScore() {
  tft.fillScreen(ST7735_BLACK);
  
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(2);
  tft.setCursor(10, 40);
  tft.println("HIGH");
  tft.setCursor(10, 60);
  tft.println("SCORE");
  
  tft.setTextSize(3);
  tft.setTextColor(ST7735_GREEN);
  tft.setCursor(40, 90);
  tft.print(highScore);
  
  tft.setTextSize(1);
  tft.setTextColor(ST7735_CYAN);
  tft.setCursor(10, 130);
  tft.println("Press RIGHT");
  tft.setCursor(15, 145);
  tft.println("for menu");
  
  if (digitalRead(BTN_RIGHT) == LOW && millis() - lastButtonTime > debounceDelay) {
    playSound(NOTE_C5, 100);
    lastButtonTime = millis();
    gameState = MENU;
    showMenu();
  }
}

// ================ UTILITY FUNCTIONS ================

void showSplashScreen() {
  tft.fillScreen(ST7735_BLACK);
  
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(2);
  tft.setCursor(15, 30);
  tft.println("SNAKE");
  
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(10, 60);
  tft.println("Original Soundtrack");
  
  tft.setCursor(15, 75);
  tft.setTextColor(ST7735_MAGENTA);
  tft.println("\"Serpent's");
  tft.setCursor(25, 90);
  tft.println("Dance\"");
  
  tft.setTextColor(ST7735_CYAN);
  tft.setCursor(10, 115);
  tft.println("Music speeds up");
  tft.setCursor(15, 130);
  tft.println("as you grow!");
  
  // Snake animation
  for (int i = 0; i < 5; i++) {
    tft.fillRect(40 + i*10, 145, 8, 8, ST7735_GREEN);
    delay(100);
  }
}

void loadHighScore() {
  highScore = 0;  // Start at 0
}
