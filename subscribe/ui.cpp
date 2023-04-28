#include <cstdio>
#include <chrono>
#include <thread>
#include <iostream>
#include "ui.h"
using namespace std;

void print_window(int row_start, int column_start);
void print_square(int colour, int row_start, int row_end, int column_start, int column_end);
void print_row(int colour, int row, int column, int spaces);
void print_window_heading(string text, int row, int column);
string get_user_input(int row, int column);

// Print command window with header, border and inner square
void print_window(int row_start, int column_start) {
    // Green header
    print_square(102, row_start, row_start+5, column_start, column_start+30);
    // Yellow borders (background square)
    print_square(103, row_start+1, row_start+6, column_start, column_start+30);
    // Blue inner sqare
    print_square(104, row_start+2, row_start+5, column_start+2,
                 column_start+28);
    fflush(stdout);
}

void print_square(int colour, int row_start, int row_end, int column_start,
                  int column_end) {
    int width = column_end - column_start;
    int height = row_end - row_start;

    for (int i = 0; i < height; i++) {
        print_row(colour, (row_start + i), column_start, width);
    }
}

// Print row with specific background colour
void print_row(int colour, int row, int column, int spaces) {
    printf("\33[%i;%iH", row, column); // move cursor to row and column
    printf("\033[%im", colour); // set background colour
    for (int i = 0; i < spaces; i++) {
        printf(" ");
    }
}

// Print heading for window
void print_window_heading(string text, int row, int column) {
    printf("\33[%i;%iH", row, column); // move cursor to row and column
    printf("\033[30;102m"); // set text to black, green background
    cout << text;
}

// Get user input
std::string get_user_input(int row, int column) {
    std::string user_input = "";
    printf("\033[30;104m"); // set text to black, blue background
    printf("\33[%i;%iH", row, column); // move cursor to row and column
    cout << ">";
    printf("\33[%i;%iH", row, column + 2); // move cursor to row and column
    cin >> user_input;

    return user_input;
}