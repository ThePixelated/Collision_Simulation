#include <iostream>
#include <Windows.h>
#include <conio.h>

struct Ball {
    int x_coor;
    int y_coor;
    int ballSpeed;
    bool x_borderHit;
    bool y_borderHit;

    int styleBall;
};

// void EraseDrawBall(Ball &ball_data) {
// 	COORD coor;
//     coor.X = ball_data.x_coor + ball_data.ballSpeed;
// 	coor.Y = ball_data.y_coor + ball_data.ballSpeed;

// 	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coor);
//     std::cout << char(219);

// 	coor.X = ball_data.x_coor;
// 	coor.Y = ball_data.y_coor;

// 	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coor);
//     std::cout << ' ';
// }

void EraseBall(Ball ball_data) {
    COORD coor;
    coor.X = ball_data.x_coor;
	coor.Y = ball_data.y_coor;

	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coor);
    std::cout << ' ';

    // Sleep(100);
}

void RenderBall(Ball ball_data, int index) {    // Remove int index later !!!!!!
    COORD coor;
    coor.X = ball_data.x_coor;
	coor.Y = ball_data.y_coor;

	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coor);
    // if (index % 2 == 0) std::cout << char(219);
    // else std::cout << char(176);

    std::cout << char(ball_data.styleBall);     // Remove this also !!!!!!!!!

    // Sleep(100);
}

void BorderCollision(Ball* ball_data, int widthScreen, int heightScreen, int size) {
    // Border Collision Check
    // ----------------------
    for (int i = 0; i < size; i++) {
        if (ball_data[i].x_coor <= 0) {
            ball_data[i].x_borderHit = true;
        } else if (ball_data[i].x_coor >= widthScreen - 1) {
            ball_data[i].x_borderHit = false;
        }

        if (ball_data[i].y_coor <= 0) {
            ball_data[i].y_borderHit = true;
        } else if (ball_data[i].y_coor >= heightScreen) {
            ball_data[i].y_borderHit = false;
        }
    }
}

/*void BallCollision(Ball* ball_data, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; i++) {
            if (ball_data[i].x_coor <= 0) {
                ball_data[i].x_borderHit = true;
            } else if (ball_data[i].x_coor >= widthScreen - 1) {
                ball_data[i].x_borderHit = false;
            }

            if (ball_data[i].y_coor <= 0) {
                ball_data[i].y_borderHit = true;
            } else if (ball_data[i].y_coor >= heightScreen) {
                ball_data[i].y_borderHit = false;
        }
        }
    }
}*/

void BallMovement(Ball* ball_data, int size) {
    // Ball Movement
    // -------------
    for (int i = 0; i < size; i++) {
        EraseBall(ball_data[i]);

        if (ball_data[i].x_borderHit) ball_data[i].x_coor += ball_data[i].ballSpeed;
        else ball_data[i].x_coor -= ball_data[i].ballSpeed;

        if (ball_data[i].y_borderHit) ball_data[i].y_coor += ball_data[i].ballSpeed;
        else ball_data[i].y_coor -= ball_data[i].ballSpeed;

        RenderBall(ball_data[i], i);
    }
}

void corner_coorBuff(int ScreenWidth, int ScreenHeight) {
    COORD corner_coor;
    corner_coor.X = ScreenWidth;
    corner_coor.Y = ScreenHeight;

    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), corner_coor);
}

int main() {
    int width = 119;
    int height = 29;

    int size;
    std::cin >> size;
    Ball ball[size];

    for (int i = 0; i < size; i++) {
        std::cin >> ball[i].x_coor >> ball[i].y_coor >> ball[i].ballSpeed >> ball[i].x_borderHit >> ball[i].y_borderHit;
        ball[i].styleBall = i + 65;
        // ball[i].x_coor = width / 2;
        // ball[i].y_coor = height / 2;
        // ball[i].ballSpeed = 1;

        // ball[i].x_borderHit;
        // ball[i].y_borderHit;
    }

    while (true) {
        BorderCollision(ball, width, height, size);
        // BallCollision
        BallMovement(ball, size);
        
        // EraseDrawBall(ball);

        corner_coorBuff(width, height);
        Sleep(25);
    }

    _getch();

    return 0;
}