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
	
struct AdditionalCoor{
	int x_coor;
	int y_coor;
};

struct Block {
	int xBarCoor;   // Center Point of X
	int yBarCoor;   // Center Point of Y
	
	AdditionalCoor top_bar;     // Mid Point of top left and top right
	AdditionalCoor bottom_bar;  // Mid Point of bottom left and bottom right
	AdditionalCoor left_bar;    // Mid Point of top left and bottom left
	AdditionalCoor right_bar;   // Mid Point of top right and bottom right
	AdditionalCoor center_bar;  // The Center of the block
	
	AdditionalCoor topLeft_bar;
	AdditionalCoor topRight_bar;
	AdditionalCoor bottomLeft_bar;
	AdditionalCoor bottomRight_bar;
};

Block* _BarInnit(int X_axis = -1, int Y_axis = -1, int WidthBlock = 1, int HeightBlock = 5, int BlockRotation = 0, int ManyBlocks = 1, int ScrnWidth = 119, int ScrnHeight = 119) {
	Block* bars = new Block[size];
	
	if (X_axis == -1) X_axis = (ScrnWidth / 2) + 1;
	if (Y_axis == -1) y_axis = ScrnHeight / 2;
	
	for (int i = 0; i < ManyBlock; i++) {
		bar.xBarCoor = X_axis;
		bar.yBarCoor = Y_axis;
		
		bar.top_bar.x_coor = bar.xBarCoor;
		bar.bottom_bar.x_coor = bar.xBarCoor;
		
		bar.top_bar.y_coor = bar.yBarCoor - ManyBlock;
		bar.bottom_bar.y_coor = bar.yBarCoor + ManyBlock;
	}
	
	return bars;
}

void EraseBall(Ball* ball_data, int size) {
    COORD coor;
    for (int i = 0; i < size; i++) {
        coor.X = ball_data[i].x_coor;
		coor.Y = ball_data[i].y_coor;
	
		SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coor);
	    std::cout << ' ';
	}
    // Sleep(100);
}

void RenderBall(Ball* ball_data, int size) {
    COORD coor;
    for (int i = 0; i < size; i++) {
        coor.X = ball_data[i].x_coor;
		coor.Y = ball_data[i].y_coor;
	
		SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coor);
	    std::cout << char(219);
	}
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

void BallCollisionBar(Ball* ball_data, Block bar, int size) {
	for (int i = 0; i < size; i++) {
		// X AXIS CHECK
		// ------------
		// Left Side Bar Collision
		if (ball_data[i].x_borderHit && (ball_data[i].x_coor >= bar.xBarCoor && ball_data[i].x_coor <= bar.xBarCoor) && (ball_data[i].y_coor >= bar.top_bar.y_coor && ball_data[i].y_coor <= bar.bottom_bar.y_coor) ) {
			ball_data[i].x_coor -= 1;
			ball_data[i].x_borderHit = false;
		}
		
		// Right Side Bar Collision
		else if (!ball_data[i].x_borderHit && (ball_data[i].x_coor <= bar.xBarCoor && ball_data[i].x_coor >= bar.xBarCoor) && (ball_data[i].y_coor >= bar.top_bar.y_coor && ball_data[i].y_coor <= bar.bottom_bar.y_coor) ) {
			ball_data[i].x_coor += 1;
			ball_data[i].x_borderHit = true;
		}
		
		// Y AXIS CHECK
		// ------------
		// Top Side Bar Collision
		
		// Bottom Side Bar Collision
	}
}

void BallMovement(Ball* ball_data, int size) {
    // Ball Movement
    // -------------
    for (int i = 0; i < size; i++) {
//        EraseBall(ball_data[i]);

        if (ball_data[i].x_borderHit) ball_data[i].x_coor += ball_data[i].ballSpeed;
        else ball_data[i].x_coor -= ball_data[i].ballSpeed;

//        if (ball_data[i].y_borderHit) ball_data[i].y_coor += ball_data[i].ballSpeed;
//        else ball_data[i].y_coor -= ball_data[i].ballSpeed;

//        RenderBall(ball_data[i]);
    }
}

void RenderBlock(Block bar) {
    COORD coor;
    
    for (int i = bar.top_bar.y_coor; i <= bar.top_bar.y_coor - (bar.top_bar.y_coor - bar.bottom_bar.y_coor); i++) {
    	coor.X = bar.xBarCoor;
		coor.Y = i;
	
		SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coor);
		std::cout << char(219);
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
	
	Block bar;

//	_barInnit();
	
	int size;
    std::cin >> size;
    Ball ball[size];

    for (int i = 0; i < size; i++) {
        std::cin >> ball[i].x_coor >> ball[i].y_coor >> ball[i].ballSpeed >> ball[i].x_borderHit >> ball[i].y_borderHit;
    }
    
	RenderBlock(bar);

	while (true) {
		BorderCollision(ball, width, height, size);
        BallCollisionBar(ball, bar, size);
        
		EraseBall(ball, size);
		BallMovement(ball, size);
        RenderBall(ball, size);
		
		corner_coorBuff(119, 29);
		Sleep(25);
	}
	
	
	getch();
	
	return 0;
}
