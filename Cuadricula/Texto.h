#pragma once
class Texto {
    static int window_width;
    static int window_height;
public:
    Texto();
    void display(void);
    void reshape(int, int);
    void printw(int, float, float, float, const char*, ...);
};