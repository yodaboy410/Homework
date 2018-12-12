# **设计一只智能贪吃蛇**
## 前言
![](1.png)
上篇关于贪吃蛇的游戏是自己操作那么这次就讲一讲如何让他成为一支人性化的小蛇把！
首先要从tyy程式中实行kbhit代入已经完成的贪吃蛇游戏代码。

## 游戏设计

以下是实行kbhit的代码。然后按照备注把自己的贪吃蛇代码放入其中。
```
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>

static struct termios ori_attr, cur_attr;

static __inline 
int tty_reset(void)
{
        if (tcsetattr(STDIN_FILENO, TCSANOW, &ori_attr) != 0)
                return -1;

        return 0;
}


static __inline
int tty_set(void)
{
        
        if ( tcgetattr(STDIN_FILENO, &ori_attr) )
                return -1;
        
        memcpy(&cur_attr, &ori_attr, sizeof(cur_attr) );
        cur_attr.c_lflag &= ~ICANON;
//        cur_attr.c_lflag |= ECHO;
        cur_attr.c_lflag &= ~ECHO;
        cur_attr.c_cc[VMIN] = 1;
        cur_attr.c_cc[VTIME] = 0;

        if (tcsetattr(STDIN_FILENO, TCSANOW, &cur_attr) != 0)
                return -1;

        return 0;
}

static __inline
int kbhit(void) 
{
                   
        fd_set rfds;
        struct timeval tv;
        int retval;

        /* Watch stdin (fd 0) to see when it has input. */
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        /* Wait up to five seconds. */
        tv.tv_sec  = 0;
        tv.tv_usec = 0;

        retval = select(1, &rfds, NULL, NULL, &tv);
        /* Don't rely on the value of tv now! */

        if (retval == -1) {
                perror("select()");
                return 0;
        } else if (retval)
                return 1;
        /* FD_ISSET(0, &rfds) will be true. */
        else
                return 0;
        return 0;
}

//将你的 snake 代码放在这里

int main()
{
        int tty_set_flag;
        tty_set_flag = tty_set();

        //将你的 snake 代码放在这里

        printf("pressed `q` to quit!\n");
        while(1) {

                if( kbhit() ) {
                        const int key = getchar();
                        printf("%c pressed\n", key);
                        if(key == 'q')
                                break;
                } else {
                        fprintf(stderr, "<no key detected>\n");
                }
        }

        if(tty_set_flag == 0) 
                tty_reset();
        return 0;
}
```
在//处key上下列的代码
```
#include<stdio.h>
#include<stdlib.h>
#include<time.h>



#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'


void put_money();
void output();
void left();
void right();
void up();
void down();

char map[12][13] = {

	"************",

	"*XXXXH     *",

	"*          *",

	"*          *",

	"*          *",

	"*          *",

	"*          *",

	"*          *",

	"*          *",

	"*          *",

	"*          *",

	"************"

};



int snakeX[SNAKE_MAX_LENGTH] = {5, 4, 3, 2, 1}; 
int snakeY[SNAKE_MAX_LENGTH] = {1, 1, 1, 1, 1};
int snakeLength = 5;
int  play = 1; 

void output(){
	printf("\n");
	int i; 
	for(i = 0; i < 12; i++){
	printf("\t%s\n", map[i]);
	}

}



void put_money(){

	int row, column;

	do{

		srand(time(NULL));

		row = 1 + rand() % 11;

		srand(time(NULL));

		column = 1 + rand() % 11;

	} while(map[row][column] != BLANK_CELL);

	map[row][column] = SNAKE_FOOD;

}



int main(){

	char ch;

	put_money();

	output();

	while(play){ 

		ch = getchar(); 

		switch(ch){

			case 'A':
			case 'a':{
				left();
				break;
			}
			case 'D':
			case 'd':{
				right();
				break;
			}
			case 'W':
			case 'w':{
				up();
				break;
			}
			case 'S':
			case 's':{
				down();
				break;
			}
			default: 
				break;
		}
	}
	printf("\nGame over!\n");
}
void left(){

	int i;

	if(map[snakeY[0]][snakeX[0] - 1] == SNAKE_BODY ||

	   map[snakeY[0]][snakeX[0] - 1] == WALL_CELL){

		play = 0; 
		return;

	} else{

		int put_money_flag = 0; 
		if(map[snakeY[0]][snakeX[0] - 1] == SNAKE_FOOD){
			put_money_flag = 1;
			if(snakeLength != SNAKE_MAX_LENGTH)
				snakeLength++;
		} else
			map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = BLANK_CELL;
		for(i = snakeLength - 1; i > 0; i--){
			snakeX[i] = snakeX[i - 1]; 
			snakeY[i] = snakeY[i - 1];
		}
		map[snakeY[0]][snakeX[0]] = SNAKE_BODY;
		snakeX[0]--;
		map[snakeY[0]][snakeX[0]] = SNAKE_HEAD; 
		if(put_money_flag)
			put_money(); 
	}
	output();
}

void right(){ 
	int i;
	if(map[snakeY[0]][snakeX[0] + 1] == SNAKE_BODY ||
	   map[snakeY[0]][snakeX[0] + 1] == WALL_CELL){
		play = 0;
		return;
	} else{
		int put_money_flag = 0;
		if(map[snakeY[0]][snakeX[0] + 1] == SNAKE_FOOD){
			put_money_flag = 1;
			if(snakeLength != SNAKE_MAX_LENGTH)
				snakeLength++;
		} else
			map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = BLANK_CELL;
		for(i = snakeLength - 1; i > 0; i--){
			snakeX[i] = snakeX[i - 1];
			snakeY[i] = snakeY[i - 1];
		}
		map[snakeY[0]][snakeX[0]] = SNAKE_BODY;
		snakeX[0]++;
		map[snakeY[0]][snakeX[0]] = SNAKE_HEAD;
		if(put_money_flag)
			put_money();
	}
	output();
} 
void up(){
	int i;
	if(map[snakeY[0] - 1][snakeX[0]] == SNAKE_BODY ||
	   map[snakeY[0] - 1][snakeX[0]] == WALL_CELL){
		play = 0;
		return;
	} else{
		int put_money_flag = 0;
		if(map[snakeY[0] - 1][snakeX[0]] == SNAKE_FOOD){
			put_money_flag = 1;
			if(snakeLength != SNAKE_MAX_LENGTH)
			snakeLength++;
		} else
			map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = BLANK_CELL;
		for(i = snakeLength - 1; i > 0; i--){
			snakeX[i] = snakeX[i - 1];
			snakeY[i] = snakeY[i - 1];
		}
		map[snakeY[0]][snakeX[0]] = SNAKE_BODY;
		snakeY[0]--;
		map[snakeY[0]][snakeX[0]] = SNAKE_HEAD;
		if(put_money_flag)
			put_money();
	}
	output();
}
void down(){
	int i;
	if(map[snakeY[0] + 1][snakeX[0]] == SNAKE_BODY ||
	   map[snakeY[0] + 1][snakeX[0]] == WALL_CELL){
		play = 0;
		return;
	} else{
		int put_money_flag = 0;
		if(map[snakeY[0] + 1][snakeX[0]] == SNAKE_FOOD){
			put_money_flag = 1;
			if(snakeLength != SNAKE_MAX_LENGTH)
				snakeLength++;
		} else
			map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = BLANK_CELL;

		for(i = snakeLength - 1; i > 0; i--){
			snakeX[i] = snakeX[i - 1];
			snakeY[i] = snakeY[i - 1];
		}
		map[snakeY[0]][snakeX[0]] = SNAKE_BODY;
		snakeY[0]++;
		map[snakeY[0]][snakeX[0]] = SNAKE_HEAD;
		if(put_money_flag)
			put_money();
	}
output();
}
```

## 总结
利用c语言做出一个游戏，真的好难好难。虽然贪吃蛇看着简单，但其中要做的东西有很多！称赞所有大佬。