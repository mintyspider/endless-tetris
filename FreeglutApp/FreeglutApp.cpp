// tetris.cpp - вечный тетрис
#include <iostream>
#include <vector>
#include <ctime>
#include "GLUT/include/GL/glut.h"

const int windowWidth = 400;    // Ширина окна
const int windowHeight = 800;   // Высота окна
const int fieldWidth = 10;      // Ширина игрового поля
const int fieldHeight = 20;     // Высота игрового поля
const int blockSize = 40;       // Размер блока

bool gameStarted = false;        // Флаг, указывающий, начата ли игра
bool gameOver = false;           // Флаг, указывающий, завершилась ли игра

enum TetrominoType { I, O, T, S, Z, J, L }; // Перечисление для типов фигур

const float colors[7][3] = {
    {0.0f, 1.0f, 1.0f},  // I - голубой
    {1.0f, 1.0f, 0.0f},  // O - желтый
    {0.5f, 0.0f, 0.5f},  // T - фиолетовый
    {0.0f, 1.0f, 0.0f},  // S - зеленый
    {1.0f, 0.0f, 0.0f},  // Z - красный
    {0.0f, 0.0f, 1.0f},  // J - синий
    {1.0f, 0.5f, 0.0f}   // L - оранжевый
};

struct Block {
    int x, y;
};

class Tetris {
public:
    Tetris() : grid(fieldWidth, std::vector<int>(fieldHeight, 0)) { // Инициализация игрового поля
        srand(time(0)); // Инициализация генератора случайных чисел
        spawnBlock();    // Генерация первого блока
    }

    // Функция для отрисовки игрового поля
    void drawField() {
        for (int i = 0; i < fieldWidth; ++i) {
            for (int j = 0; j < fieldHeight; ++j) {
                if (grid[i][j] == 1) { // Если ячейка заполнена
                    glColor3f(0.7f, 0.7f, 0.7f); // Серый цвет блока
                    drawBlock(i, j); // Отрисовка блока
                }
            }
        }
    }

    // Функция для отрисовки отдельного блока
    void drawBlock(int x, int y) {
        glBegin(GL_QUADS); // Начало отрисовки квадрата
        glVertex2f(x * blockSize, y * blockSize); // Левый нижний угол
        glVertex2f(x * blockSize + blockSize, y * blockSize); // Правый нижний угол
        glVertex2f(x * blockSize + blockSize, y * blockSize + blockSize); // Правый верхний угол
        glVertex2f(x * blockSize, y * blockSize + blockSize); // Левый верхний угол
        glEnd(); // Завершение отрисовки квадрата
    }

    // Функция для генерации нового блока
    void spawnBlock() {
        currentBlockType = static_cast<TetrominoType>(rand() % 7); // Случайный выбор типа блока
        currentColor = colors[currentBlockType];                   // Устанавливаем цвет текущего блока
        switch (currentBlockType) {                               // Координаты блоков для каждого типа
        case I: currentBlocks = { {3, fieldHeight - 1}, {4, fieldHeight - 1}, {5, fieldHeight - 1}, {6, fieldHeight - 1} }; break;
        case O: currentBlocks = { {4, fieldHeight - 1}, {5, fieldHeight - 1}, {4, fieldHeight - 2}, {5, fieldHeight - 2} }; break;
        case T: currentBlocks = { {4, fieldHeight - 1}, {3, fieldHeight - 1}, {5, fieldHeight - 1}, {4, fieldHeight - 2} }; break;
        case S: currentBlocks = { {4, fieldHeight - 1}, {5, fieldHeight - 1}, {3, fieldHeight - 2}, {4, fieldHeight - 2} }; break;
        case Z: currentBlocks = { {3, fieldHeight - 1}, {4, fieldHeight - 1}, {4, fieldHeight - 2}, {5, fieldHeight - 2} }; break;
        case J: currentBlocks = { {4, fieldHeight - 1}, {3, fieldHeight - 1}, {5, fieldHeight - 1}, {3, fieldHeight - 2} }; break;
        case L: currentBlocks = { {3, fieldHeight - 1}, {4, fieldHeight - 1}, {5, fieldHeight - 1}, {5, fieldHeight - 2} }; break;
        }
    }

    // Функция для отрисовки текущего блока
    void drawCurrentBlock() {
        glColor3f(currentColor[0], currentColor[1], currentColor[2]); // Устанавливаем цвет блока
        for (const auto& block : currentBlocks) drawBlock(block.x, block.y); // Отрисовываем каждый блок
    }

    void rotateBlock() {
        if (currentBlockType == O) return; // Квадратный блок не поворачивается
        Block pivot = currentBlocks[0]; // Вращаем вокруг первого блока
        std::vector<Block> rotatedBlocks = currentBlocks; // Копия текущих блоков для вращения

        for (auto& block : rotatedBlocks) { // Применение вращения
            int dx = block.x - pivot.x;
            int dy = block.y - pivot.y;
            block.x = pivot.x - dy; // Новый X
            block.y = pivot.y + dx; // Новый Y
        }

        if (canMove(rotatedBlocks)) currentBlocks = rotatedBlocks; // Если можно, то обновляем
    }

    void moveBlockDown() {
        if (canMove(0, -1)) {
            for (auto& block : currentBlocks) block.y--; // Двигаем вниз
        }
        else {
            placeBlock(); // Если нельзя, помещаем блок
            checkLines(); // Проверяем линии
            spawnBlock(); // Генерируем новый блок
            if (!canMove(currentBlocks)) { // Проверка на завершение игры
                gameOver = true; // Установка флага завершения игры
                std::cout << "Game Over!" << std::endl; // Сообщение о завершении игры
            }
        }
    }
    // Функция для движения блока влево
    void moveBlockLeft() { if (canMove(-1, 0)) for (auto& block : currentBlocks) block.x--; }

    // Функция для движения блока вправо
    void moveBlockRight() { if (canMove(1, 0)) for (auto& block : currentBlocks) block.x++; }

    // Проверка возможности движения на dx, dy
    bool canMove(int dx, int dy) {
        std::vector<Block> movedBlocks = currentBlocks; // Копия текущих блоков
        for (auto& block : movedBlocks) {
            block.x += dx; // Движение по X
            block.y += dy; // Движение по Y
        }
        return canMove(movedBlocks); // Проверяем возможность движения
    }

    // Проверка, можно ли переместить указанные блоки
    bool canMove(const std::vector<Block>& blocks) {
        for (const auto& block : blocks) {
            if (block.x < 0 || block.x >= fieldWidth || block.y < 0 || grid[block.x][block.y] == 1)
                return false; // Проверяем границы и заполненность
        }
        return true;
    }

    // Размещение блока на поле
    void placeBlock() {
        for (const auto& block : currentBlocks) grid[block.x][block.y] = 1; // Заполняем игровое поле
    }

    // Проверка и удаление полных линий
    void checkLines() {
        for (int j = 0; j < fieldHeight; ++j) {
            bool lineFull = true;
            for (int i = 0; i < fieldWidth; ++i) {
                if (grid[i][j] == 0) {
                    lineFull = false; // Проверяем заполненность линии
                    break;
                }
            }
            if (lineFull) {
                for (int k = j; k < fieldHeight - 1; ++k)
                    for (int i = 0; i < fieldWidth; ++i)
                        grid[i][k] = grid[i][k + 1]; // Удаляем линию
                for (int i = 0; i < fieldWidth; ++i)
                    grid[i][fieldHeight - 1] = 0; // Очищаем верхнюю линию
            }
        }
    }

private:
    std::vector<std::vector<int>> grid; // Игровое поле
    TetrominoType currentBlockType; // Тип текущего блока
    std::vector<Block> currentBlocks; // Текущие блоки
    const float* currentColor; // Цвет текущего блока
};

Tetris tetris;

// Демонстрация стартового экрана
void displayStartScreen() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Заголовок "Welcome to Tetris!"
    glRasterPos2f(80, 600);
    const char* title = "Welcome to my endless Tetris!";
    for (const char* c = title; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    glRasterPos2f(85, 570);
    const char* author = "Made by mintyspider with <3";
    for (const char* c = author; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    // Инструкция по началу игры
    glRasterPos2f(85, 540);
    const char* startInstruction = "Press Enter to start the game!";
    for (const char* c = startInstruction; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    glRasterPos2f(85, 510);
    const char* endInstruction = "Press Esc to exit the game!";
    for (const char* c = endInstruction; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    // Инструкция по управлению
    glRasterPos2f(60, 400);
    const char* controlsTitle = "Controls:";
    for (const char* c = controlsTitle; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    // Управление
    glRasterPos2f(70, 350);
    const char* moveLeft = "Left Arrow - Move Left";
    for (const char* c = moveLeft; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    glRasterPos2f(70, 320);
    const char* moveRight = "Right Arrow - Move Right";
    for (const char* c = moveRight; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    glRasterPos2f(70, 290);
    const char* moveDown = "Down Arrow - Move Down Faster";
    for (const char* c = moveDown; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    glRasterPos2f(70, 260);
    const char* rotateInstruction = "Up Arrow - Rotate";
    for (const char* c = rotateInstruction; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    glFlush();
}

// Отрисовка сцены
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Очистка экрана
    if (gameStarted && !gameOver) {
        tetris.drawField(); // Отрисовка игрового поля
        tetris.drawCurrentBlock(); // Отрисовка текущего блока
    }
    else if (!gameStarted) {
        displayStartScreen(); // Демонстрация стартового экрана
    }
    else if (gameOver) { // Показ уведомления о завершении игры
        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos2f(90, 400);
        const char* gameOverMessage = "Game Over!";
        for (const char* c = gameOverMessage; *c != '\0'; c++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
    glFlush();
}

// Таймер для управления падением блока
void timer(int value) {
    if (gameStarted && !gameOver) {
        tetris.moveBlockDown(); // Опускание блока
        glutPostRedisplay(); // Обновление окна
    }
    glutTimerFunc(1000, timer, 0); // Перезапуск таймера через 1000 мс
}

// Обработка нажатий клавиш
void keyboard(unsigned char key, int x, int y) {
    if (key == 13) { // Запуск игры
        gameStarted = true;
        glutTimerFunc(1000, timer, 0);
    }
    else if (key == 27) { // Если нажата клавиша Esc
        glutDestroyWindow(glutGetWindow()); // Закрыть текущее окно
        exit(0);
    }
    glutPostRedisplay(); // Обновление окна
}

// Обработка нажатий клавиш во время игры
void keyboardSpecial(int key, int x, int y) {
    if (gameStarted && !gameOver) {
        switch (key) {
        case GLUT_KEY_LEFT: tetris.moveBlockLeft(); break; // Влево
        case GLUT_KEY_RIGHT: tetris.moveBlockRight(); break; // Вправо
        case GLUT_KEY_DOWN: tetris.moveBlockDown(); break; // Вниз
        case GLUT_KEY_UP: tetris.rotateBlock(); break; // Поворот
        }
        glutPostRedisplay(); // Обновление окна
    }
}

// Инициализация игры
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Установка цвета фона
    glMatrixMode(GL_PROJECTION);            // Установка режима матрицы проекции
    glLoadIdentity();                       // Сброс матрицы
    glOrtho(0, windowWidth, 0, windowHeight, -1, 1); // Установка ортографической проекции
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Инициализация GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Установка режима отображения
    glutInitWindowSize(windowWidth, windowHeight); // Установка размера окна
    glutCreateWindow("Endless Tetris"); // Создание окна
    initGL(); // Инициализация игры
    glutDisplayFunc(display); // Установка функции отображения
    glutKeyboardFunc(keyboard); // Установка функции обработки клавиш
    glutSpecialFunc(keyboardSpecial); // Обработка игровых клавиш
    glutMainLoop(); // Запуск главного цикла обработки
    return 0;
}