/*
HOW TO INSTALL:
sudo apt-get install libncurses-dev
sudo apt-get install libncurses5

G++ flag: -lncurses
*/

#include <ncurses.h>
#include <string>
#include <vector>

void draw_frame(int start_row, int start_col, int end_row, int end_col)
{
    // Draw top border
    mvprintw(start_row, start_col, "+");
    for (int i = start_col + 1; i < end_col; i++)
        addch('-');
    addch('+');

    // Draw side borders
    for (int i = start_row + 1; i < end_row; i++)
    {
        mvprintw(i, start_col, "|");
        mvprintw(i, end_col, "|");
    }

    // Draw bottom border
    mvprintw(end_row, start_col, "+");
    for (int i = start_col + 1; i < end_col; i++)
        addch('-');
    addch('+');
}

void print_row(int row, int col, const std::vector<std::string> &data)
{
    // Print data in row
    for (const auto &cell : data)
    {
        mvprintw(row, col, "%s", cell.c_str());
        col += cell.size() + 2; // Add padding between cells
    }
}

void table_display(const std::vector<std::vector<std::string>> &table_data)
{
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    // Define table data
    // std::vector<std::vector<std::string>> table_data = {
    //     {"Name", "Age", "Gender"},
    //     {"John", "25", "Male"},
    //     {"Jane", "30", "Female"},
    //     {"Bob", "40", "Male"}};

    // Set table dimensions and position
    int table_height = table_data.size() + 2; // Add padding for frame
    int table_width = 0;
    for (const auto &row : table_data)
        table_width = std::max(table_width, static_cast<int>(row.size() * 12)); // Add padding for cell content
    int table_start_row = (LINES - table_height) / 2;
    int table_start_col = (COLS - table_width) / 2;

    // Draw table frame
    draw_frame(table_start_row, table_start_col, table_start_row + table_height - 1, table_start_col + table_width - 1);

    // Print table headers
    print_row(table_start_row + 1, table_start_col + 1, table_data[0]);

    // Print table data
    for (int i = 1; i < table_data.size(); i++)
        print_row(table_start_row + i + 1, table_start_col + 1, table_data[i]);

    // Refresh screen and wait for user input
    refresh();
    getch();

    // End ncurses
    endwin();
}

/*
USAGE:

int main()
{
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    // Define table data
    std::vector<std::vector<std::string>> table_data = {
        {"Name", "Age", "Gender"},
        {"John", "25", "Male"},
        {"Jane", "30", "Female"},
        {"Bob", "40", "Male"}
    };

    // Set table dimensions and position
    int table_height = table_data.size() + 2; // Add padding for frame
    int table_width = 0;
    for (const auto& row : table_data)
        table_width = std::max(table_width, static_cast<int>(row.size() * 12)); // Add padding for cell content
    int table_start_row = (LINES - table_height) / 2;
    int table_start_col = (COLS - table_width) / 2;

    // Draw table frame
    draw_frame(table_start_row, table_start_col, table_start_row + table_height - 1, table_start_col + table_width - 1);

    // Print table headers
    print_row(table_start_row + 1, table_start_col + 1, table_data[0]);

    // Print table data
    for (int i = 1; i < table_data.size(); i++)
        print_row(table_start_row + i + 1, table_start_col + 1, table_data[i]);

    // Refresh screen and wait for user input
    refresh();
    getch();

    // End ncurses
    endwin();

    return 0;
}

*/