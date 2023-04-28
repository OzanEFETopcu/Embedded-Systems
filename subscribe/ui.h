#ifndef TERMINAL_UI_H
#define TERMINAL_UI_H

#include <string>

void print_window(int row_start, int column_start);
void print_square(int colour, int row_start, int row_end, int column_start, int column_end);
void print_row(int colour, int row, int column, int spaces);
void print_window_heading(std::string text, int row, int column);
std::string get_user_input(int row, int column);

#endif // TERMINAL_UI_H