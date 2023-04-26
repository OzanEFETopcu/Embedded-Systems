#include <cstdio>
#include <chrono>
#include <thread>
#include <iostream>
using namespace std;

void print_window(int row_start, int column_start);
void print_square(int colour, int row_start, int row_end, int column_start, int column_end);
void print_row(int colour, int row, int column, int spaces);
void print_window_heading(string text, int row, int column);
string get_user_input(int row, int column);

int main() {
    // Print three terminal windows
    print_window(5, 5);
    print_window(5, 40);
    print_window(15, 25);

    // Print heading for terminal windows
    print_window_heading("Distance", 5, 7);
    print_window_heading("Compass", 5, 42);
    print_window_heading("Enter Command", 15, 27);

    get_user_input(17, 28);

    printf("\033[30;0H"); // move cursor to row and column

    cout << endl;
    return 0;
}

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
string get_user_input(int row, int column) {
    string user_input = "";
    printf("\033[30;104m"); // set text to black, blue background
    printf("\33[%i;%iH", row, column); // move cursor to row and column
    cout << ">";
    printf("\33[%i;%iH", row, column + 2); // move cursor to row and column
    cin >> user_input;

    return user_input;
}