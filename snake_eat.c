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



int snakeX[SNAKE_MAX_LENGTH] = {5, 4, 3, 2, 1}; //Ϊ�˱����߳�������ʱ��ν��Ԫ���ƶ�������ʦ�������˳�����ˡ�0��Ԫ����ͷ��
int snakeY[SNAKE_MAX_LENGTH] = {1, 1, 1, 1, 1};
int snakeLength = 5;
int  play = 1; //b��ʶ�Ƿ�Game over



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

	while(play){ //play�����ж��Ƿ�Game Over�����ܱ�left��right��up��down�ĸ��������ı�

		ch = getchar(); //��ʹ�ûس��Ͷ�ȡ�ַ������ڲ���ϵͳ����Ȼ������΢���ṩ��ͷ�ļ����Ǿ�ÿ�ζ��س��¡��㲻��Ϊʲô�������ֹ�����

		//The C library itself deals with files, and doesn't concern itself with how data gets into the input file.

		//Therefore, there's no way in the language itself to get keys as they are pressed; instead, this is platform-specific.

		//Since you haven't specified OS or compiler, we can't look it up for you.

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
			default: //ƥ�䵽���������ַ�����Ҫ����������
				break;
		}
	}
	printf("\nGame over!\n");
}
void left(){

	int i;

	if(map[snakeY[0]][snakeX[0] - 1] == SNAKE_BODY ||

	   map[snakeY[0]][snakeX[0] - 1] == WALL_CELL){

		play = 0; //��ͷ���������ǽ��ʱ��������Ϸ

		return;

	} else{

		int put_money_flag = 0; //����put_money����Ӧ���������ƶ�֮��ִ�У�����ʳ����ж��������ƶ�֮ǰ������������һ��flag
		if(map[snakeY[0]][snakeX[0] - 1] == SNAKE_FOOD){
			put_money_flag = 1;
			if(snakeLength != SNAKE_MAX_LENGTH)
				snakeLength++;
		} else
			map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = BLANK_CELL;
			//������������ڣ�����Ե���ʳ���ԭ���������һ�ڴ������µ�һ�ڣ�ͼ���Ͽ������������һ��û�б仯��
			//����û�гԵ�ʳ���ͼ���ϵ���β��Ҫ�ƶ�����˽�ԭ��β����λ����Ϊ�ո�
		for(i = snakeLength - 1; i > 0; i--){
			snakeX[i] = snakeX[i - 1]; //ÿһ�ڵ�λ�ñ�Ϊǰһ�ڵ�ԭλ��
			snakeY[i] = snakeY[i - 1];
		}
		map[snakeY[0]][snakeX[0]] = SNAKE_BODY; //ԭ��ͷλ�ñ�Ϊ����
		snakeX[0]--;
		map[snakeY[0]][snakeX[0]] = SNAKE_HEAD; //��ͷ����λ����H������
		if(put_money_flag)
			put_money(); //�����ƶ���ȫ���غ󣬲�����ʳ��
	}
	output();
}

//��ʵҲ���Է�Ϊ�����������������������ʳ�������ж����
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
