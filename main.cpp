#include "SSDL.h"
#include <vector>
#include <string>
#include <stdlib.h>

const bool _DEBUG = false;

const std::vector<std::vector<int>> SIMPSON_LOCATION = {
    {239, 71, 38, 117},
    {303, 113, 33, 80},
    {120, 77, 40, 106},
    {256, 129, 35, 61},
    {146, 67, 38, 112},
    {182, 95, 48, 89},
    {273, 52, 27, 48},
    {303, 68, 25, 54},
    {24, 83, 49, 94},
    {433, 79, 17, 87},
    {437, 143, 67, 36},
    {12, 49, 33, 54},
};
const std::vector<std::string> SIMPSONS = {
    "Homer",
    "Bart",
    "Krusty",
    "Lisa",
    "Apu",
    "Moe",
    "Marge",
    "Flanders",
    "Chief Wiggum",
    "Smithers",
    "Milhouse",
    "Ralph Wiggum",
};

enum
{
    PICTURE_WIDTH = 553,
    PICTURE_HEIGHT = 187,
};

void run_builder(void)
{
    int cur = 0;
    while (true)
    {
        int height = PICTURE_HEIGHT;
        SSDL_SetCursor(cur, PICTURE_HEIGHT);

        std::vector<int> location = {0, 0, 0, 0};

        SSDL_WaitMouse();
        int x = SSDL_GetMouseX(), y = SSDL_GetMouseY();
        location[0] = x;
        location[1] = y;

        SSDL_WaitMouse();
        x = SSDL_GetMouseX(), y = SSDL_GetMouseY();
        location[2] = x - location[0];
        location[3] = y - location[1];

        for (auto i : location)
        {
            SSDL_SetCursor(cur, height);
            sout << i;
            height += 20;
        }
        cur += 40;
    }
}

void flash_box(int left, int top, int width, int height)
{
    std::vector<SSDL_Color> flash_colors = {
        RED,
        WHITE,
    };
    for (int i = 0; i < 4; i++)
    {
        SSDL_Color color = flash_colors.at(i % 2);
        SSDL_SetRenderDrawColor(color);
        SSDL_RenderDrawRect(left, top, width, height);
        SSDL_Delay(250);
    }
}

void run_game(void)
{
    srand(time(NULL));
    int total_simpsons = SIMPSONS.size();
    int random = rand() % total_simpsons;

    std::string simpson = SIMPSONS.at(random);
    std::vector<int> location = SIMPSON_LOCATION.at(random);

    int left = location[0];
    int top = location[1];
    int width = location[2];
    int height = location[3];

    SSDL_SetCursor(20, PICTURE_HEIGHT + 50);
    sout << "Where is " << simpson << "? Click to win.";

    SSDL_WaitMouse();

    int x = SSDL_GetMouseX(), y = SSDL_GetMouseY();
    bool is_x_in_range = (left < x && x < left + width);
    bool is_y_in_range = (top < y && y < top + height);

    SSDL_SetCursor(20, PICTURE_HEIGHT + 70);
    if (is_x_in_range && is_y_in_range)
    {
        SSDL_SetRenderDrawColor(GREEN);
        sout << "You win!";
    }
    else
    {
        SSDL_SetRenderDrawColor(RED);
        sout << "You lose.";
        flash_box(left, top, width, height);
    }

    SSDL_WaitKey();
}

int main(int argc, char **argv)
{

    const SSDL_Image BACKGROUND = SSDL_LoadImage("media/simpsons.png");

    SSDL_SetWindowTitle("Find the Simpsons");

    SSDL_SetWindowSize(PICTURE_WIDTH, PICTURE_HEIGHT + 100);

    SSDL_RenderImage(BACKGROUND, 10, 10);

    if (_DEBUG)
    {
        run_builder();
    }
    else
    {
        run_game();
    }
}