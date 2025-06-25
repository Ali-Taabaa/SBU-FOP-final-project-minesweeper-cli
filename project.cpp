#include <iostream>
#include <cstdlib>
#include <cstring>
#include <time.h>
#include "clui.h"

#define KEY_UP_1 119
#define KEY_UP_2 87
#define KEY_DOWN_1 115
#define KEY_DOWN_2 83
#define KEY_LEFT_1 97
#define KEY_LEFT_2 65
#define KEY_RIGHT_1 100
#define KEY_RIGHT_2 68
#define SPACE 32

struct player{
    //user info
    int id;
    char* name;
    int score;
    bool player_bool;
    //saveslot info
    int size;
    char** minesweeper;
    char** minesweeper_print;
    bool save;
};

int length(char* s);
bool compare(char* s, char* t);
char** minesweeper_f(int size);
char** minesweeper_print_f(int size);
char* name_page(void);
int menu_page(void);
int difficulty_level_page(void);
void plant_mine(char** minesweeper, int size);
void print_playground(char** minesweeper_print, int size);
int game(char** minesweeper_print,char** minesweeper,int size);
void game_win(player minesweeper_player[],char** minesweeper,char** minesweeper_print,int size,int player);
void game_save(player minesweeper_player[] ,char** minesweeper , char** minesweeper_print , int size , int player);
void game_lose(char** minesweeper , char** minesweeper_print , int size);
int new_user_page(player minesweeper_player[] , int& player);
void change_name_page(player minesweeper_player[] , int& player);
void leaderboard_page(player minesweeper_player[]);

int main(){
    char** minesweeper; char** minesweeper_print;
    player* minesweeper_player = new player[10];

    for (size_t i = 0; i < 10; i++) {
        minesweeper_player[i].id = i;
        minesweeper_player[i].score = 0;
        minesweeper_player[i].player_bool = false;
        minesweeper_player[i].save = false;
    }
    minesweeper_player[0].player_bool = true;
    int option = 0 , size = 0 , result = 0 , player = 0 , saveslot_count = 0 , temp ;
    bool check = false;
    char* name = new char[50];
    char* new_name = new char[50];
    name = name_page();
    minesweeper_player[0].name = name;
    while(true){
        option = menu_page();
        if(option == 1) {
        	size = difficulty_level_page();
            minesweeper = minesweeper_f(size);
            minesweeper_print = minesweeper_print_f(size);
            plant_mine(minesweeper,size);
            print_playground(minesweeper_print,size);
            result = game(minesweeper_print,minesweeper,size);
            if(result == 1)
                game_win(minesweeper_player, minesweeper, minesweeper_print, size, player);

            else if(result == 2)
                game_save(minesweeper_player , minesweeper ,  minesweeper_print , size , player);

            else if(result == -1)
                game_lose(minesweeper , minesweeper_print , size);
        }
        else if(option == 2){
            if(minesweeper_player[player].save == false){
            	change_color_rgb(242, 10, 10);
                printf("\n You don't have any saved game.");
                reset_color();
                printf("\n Press space to continue.");
                while(true){
                    char input_2 = getch();
                    if(input_2 == SPACE)
                        break;
                }
            }
            else{
                print_playground(minesweeper_player[player].minesweeper_print,minesweeper_player[player].size);
                result = game(minesweeper_player[player].minesweeper_print,minesweeper_player[player].minesweeper,minesweeper_player[player].size);
                if(result == 1){
                    game_win(minesweeper_player, minesweeper_player[player].minesweeper, minesweeper_player[player].minesweeper_print, minesweeper_player[player].size, player);
                }
                else if(result == 2){
                    game_save(minesweeper_player , minesweeper_player[player].minesweeper ,  minesweeper_player[player].minesweeper_print , minesweeper_player[player].size , player);
            	}
                else if(result == -1){
                    game_lose(minesweeper , minesweeper_print , size);
                    minesweeper_player[player].save = false;
                }
       		}
    	}
        else if(option == 3){
                change_name_page(minesweeper_player , player);
        }
        else if(option == 4){new_user_page(minesweeper_player , player);}
        else if(option == 5){leaderboard_page(minesweeper_player);}
        else if(option == 6){quit();}

    }

    return 0;
}

int length(char* s) {
    int index = 0;
    while (s[index] != '\0')
        index++;
    return index;
    }
bool compare(char* s, char* t) {
    int len1 = length(s);
    int len2 = length(t);
    if (len1 != len2)
        return false;
    for (int i = 0; i < len1; ++i)
        if (s[i] != t[i])
            return false;
    return true;
}
char** minesweeper_f(int size){
    char** minesweeper = new char*[size];
    for (size_t i = 0; i < size; i++)
        minesweeper[i] = new char[size];
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++)
            minesweeper[i][j] = '0';
    return minesweeper;
}
char** minesweeper_print_f(int size){
    char** minesweeper_print = new char*[size];
    for (size_t i = 0; i < size; i++)
        minesweeper_print[i] = new char[size];
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++)
            minesweeper_print[i][j] = 'X';
    return minesweeper_print;
}
char* name_page(void){
    clear_screen();
    char* name = new char[50];
    std::cout << "\n Enter Your Name : ";
    std::cin.getline(name,50);
    return name;
}
int menu_page(void){
    clear_screen();
    printf("\n 1.New Game\n");
    printf(" 2.Load Game\n");
    printf(" 3.Change Name\n");
    printf(" 4.New User\n");
    printf(" 5.Leaderboard\n");
    printf(" 6.Quit\n\n");
    printf(" Select an option: ");
    int input;
    while(true){
        std::cin >> input;
       	if(input==1) {clear_screen(); return 1;}
    	else if(input==2) {clear_screen(); return 2;}
    	else if(input==3) {clear_screen(); return 3;}
        else if(input==4) {clear_screen(); return 4;}
        else if(input==5) {clear_screen(); return 5;}
        else if(input==6) {clear_screen(); return 6;}
        else {printf(" Try again.\n Select an option: ");}
        }
}
int difficulty_level_page(void){
    printf("\n 1.Easy\n");
    printf(" 2.Normal\n");
    printf(" 3.Hard\n");
    printf(" 4.Optional Difficulty\n\n");
    printf(" Select an option: ");
    int input , input_optional;
    while(true){
        std::cin >> input;
        switch(input){
            case 1 : clear_screen(); return 5;
            case 2 : clear_screen(); return 12;
            case 3 : clear_screen(); return 20;
            case 4 :
                printf(" Enter the optional size: ");
                std::cin >> input_optional;
                while (true) {
                    if(input_optional > 20 || input_optional < 5){
                    	change_color_rgb(242, 10, 10);
                        printf(" The size should be less than 20 and more than 5." );
                        reset_color();
                        printf("\n Enter the optional size: ");
                        std::cin >> input_optional;
                    }
                    else{
                        clear_screen();
                        return input_optional;
                    }
                }
            default : printf(" Try again.\n Select an option: "); break;
        }
    }
}
void plant_mine(char** minesweeper, int size){
    //mines :
    srand(time(0));
    int mine_counter;
    switch(size){
        case 5 : mine_counter = 4; break;
        case 12 : mine_counter = 28; break;
        case 20 : mine_counter = 96; break;
        default : mine_counter = (size*size)/10*2;
    }
    int i_mine , j_mine;
    while(mine_counter > 0){
        i_mine = rand()%size;
        j_mine = rand()%size;
        while(true){
            if(minesweeper[i_mine][j_mine] != 'B'){
                minesweeper[i_mine][j_mine] = 'B';
                mine_counter--;
                break;
            }
            else{
                i_mine = rand()%size;
                j_mine= rand()%size;
            }
        }
    }

    //numbers :
    for (int i = 0; i < size; i++){ //check neighbor cells of ech cell
        for (int j = 0; j < size; j++){
            if(minesweeper[i][j] == 'B')
                continue;
            else{
                for(int a = i-1; a < i+2; a++){
                    for(int b = j-1; b < j+2; b++){
                        if(a<0 || a>=size || b<0 || b>=size || (a==i && b==j)){
                            continue;
                        }
                        else{
                            if(minesweeper[a][b] == 'B')
                                minesweeper[i][j] += 1;
                        }
                    }
                }
            }
        }
    }
}
void print_playground(char** minesweeper_print, int size){
    int line_row = 0, line_col = 0;
    for(int i = 0; i < size+1 ; i++){
    	for(int j = 0; j < size+1 ; j++){
            //first row : number of lines
    		if(line_row==0){
    			if(line_col==0){//first row and first column
    				printf("%3c", ' ');
    				line_col++;
    			}
    			else{
                    change_color_rgb(31, 209, 132);
                    if(line_col < 10)
    				    printf("%3c", line_col + '0');
                    else
                        printf("%3c", line_col + 'A' - 10);
                    reset_color();
    				line_col++;
    			}
    		}
            //first column : number of lines
            else if(line_col==0 && line_row!=0){
                change_color_rgb(31, 209, 132);
                if(line_row < 10)
                    printf("%3c", line_row + '0');
                else
                    printf("%3c", line_row + 'A' - 10);
                reset_color();
                line_col++;
            }
            //other cells
            else if(line_col!=0 && line_row!=0){
            	if(minesweeper_print[i-1][j-1]=='F'){ //color of flag cell
            		change_color_rgb(42, 245, 15);
            		printf("%3c", minesweeper_print[i-1][j-1]);
            		reset_color();
    			}
    			else if(minesweeper_print[i-1][j-1]=='B'){ //color of mine cell
    				change_color_rgb(245, 45, 15);
    				printf("%3c", minesweeper_print[i-1][j-1]);
    				reset_color();
    			}
                else{
    				if(minesweeper_print[i-1][j-1]=='0'){ //null cell
    					minesweeper_print[i-1][j-1]=' ';
    				}
                    if(minesweeper_print[i-1][j-1]!='X'){
                        change_color_rgb(223, 230, 46);
    					printf("%3c", minesweeper_print[i-1][j-1]);
    					reset_color();
                    }
                    else
    				    printf("%3c", minesweeper_print[i-1][j-1]);
    			}
                line_col++;
            }
    	}
        printf("\n");
    	line_col=0;
    	line_row++;
    }
}
int game(char** minesweeper_print,char** minesweeper,int size){
    const int first_row = 2;
    const int first_col = 6;
    const int last_row = first_row + size - 1;
    const int last_col = 3*(size+1);

    cursor_to_pos(first_row,first_col);
    int x , y; int flag_count;
    int leftover_cells = 0; 
    switch(size){
        case 5 : flag_count = 4; break;
        case 12 : flag_count = 28; break;
        case 20 : flag_count = 96; break;
        default : flag_count = (size*size)/10*2;
    }
    for(int i = 0; i < size; i++){
    	for(int j = 0; j < size; j++){
    		if(minesweeper_print[i][j] == 'F')
    			flag_count--;
    		if(minesweeper_print[i][j] == 'X')
    			leftover_cells++;
		}
	}
    leftover_cells = leftover_cells - flag_count;
    char input;
    while(true){
    	if(leftover_cells == 0) {
            clear_screen();
            play_beep();
            print_playground(minesweeper,size);
            printf("\n You Won! :)\n");
            printf("\n Press space to continue.\n" );
            while(true){
                input = getch();
                if(input==SPACE)
                    return 1; //1 ==> win
            }
        }
    	input = getch();
    	if(input == KEY_UP_1 || input == KEY_UP_2){
            if(get_cursor_x() != first_row) {cursor_up(1);}
        }

    	else if(input == KEY_DOWN_1 || input == KEY_DOWN_2){
            if(get_cursor_x() != last_row) {cursor_down(1);}
        }

    	else if(input == KEY_LEFT_1 || input == KEY_LEFT_2){
            if(get_cursor_y() != first_col) {cursor_backward(3);}
        }

    	else if(input == KEY_RIGHT_1 || input == KEY_RIGHT_2){
            if(get_cursor_y() != last_col) {cursor_forward(3);}
        }

        else if(input == 'Q' || input == 'q') {return -2;}

        else if(input == 'O' || input == 'o') {
            clear_screen();
            printf("\n Press space to save the game.");
            printf("\n Press Q to quit.");
            while(true){
                char input = getch();
                if(input == SPACE)
                    return 2;
                else if(input == 'Q' || input == 'q')
                    return -2;
            }
        }

        else if(input == 'F' || input == 'f') {
    		y = get_cursor_y(); x = get_cursor_x();
    		if(minesweeper_print[x-2][(y/3)-2] == 'F'){
    			minesweeper_print[x-2][(y/3)-2] = 'X';
    			flag_count++;
    		}
    		else{
    			if(flag_count==0) {play_beep();}
    			else if(minesweeper_print[x-2][(y/3)-2] != 'X') {play_beep();}
    			else{
    				minesweeper_print[x-2][(y/3)-2] = 'F';
    				flag_count--;
    			}
    	    }
    		clear_screen();
    		print_playground(minesweeper_print,size);
    		cursor_to_pos(x,y);
    	}

        else if(input == SPACE){
    			y = get_cursor_y();
    			x = get_cursor_x();
    			if(minesweeper_print[x-2][(y/3)-2] == 'F'){
    				play_beep();
    			}
    			else if(minesweeper_print[x-2][(y/3)-2] != 'X'){
    				play_beep();
    			}
    			else if(minesweeper[x-2][(y/3)-2] == 'B'){ //select a cell wich contains mine
    				clear_screen();
    				play_beep();
    				print_playground(minesweeper,size);
                    printf("\n Game Over! \n");
    				printf("\n Press space to continue.\n" );
                    while(true){
                        input = getch();
                        if(input==SPACE)
                            return -1; //-1 ==> lose
                    }
    			}
    			else{
                    if(minesweeper[x-2][(y/3)-2] == '0'){
                		minesweeper_print[x-2][(y/3)-2] = ' ';
    				}
    				else{
                        minesweeper_print[x-2][(y/3)-2] = minesweeper[x-2][(y/3)-2];

                    }
                    leftover_cells--;
                }
            	for (size_t a = 0; a < 4; a++) {
                    for (size_t i = 0; i < size; i++) {
                        for (size_t j = 0; j < size-1; j++) {
                            if (minesweeper_print[i][j] == ' ') {
                            	if(minesweeper_print[i][j+1] == ' ')
                            		continue;
                                if(minesweeper[i][j+1] == '0' && minesweeper_print[i][j+1] != 'F'){
                                    minesweeper_print[i][j+1] = ' ';
                                    leftover_cells--;
                                }
                                else if(minesweeper[i][j+1] == 'B')
                                    continue;
                                else if(minesweeper_print[i][j+1] == 'X'){
                                    minesweeper_print[i][j+1] = minesweeper[i][j+1];
                                    leftover_cells--;
                                    continue;
                                }
                            }
                        }
                    }
    				for (size_t i = 0; i < size; i++) {
                        for (size_t j = size-1; j > 0; j--) {
                            if (minesweeper_print[i][j] == ' ') {
                            	if(minesweeper_print[i][j-1] == ' ')
                            		continue;
                                if(minesweeper[i][j-1] == '0' && minesweeper_print[i][j-1] != 'F'){
                                    minesweeper_print[i][j-1] = ' ';
                                    leftover_cells--;
                                }
                                else if(minesweeper[i][j-1] == 'B')
                                    continue;
                                else if(minesweeper_print[i][j-1] == 'X'){
                                    minesweeper_print[i][j-1] = minesweeper[i][j-1];
                                    leftover_cells--;
                                    continue;
                                }
                            }
                        }
                    }
                    for (size_t j = 0; j < size; j++) {
                        for (size_t i = 0; i < size-1; i++) {
                            if (minesweeper_print[i][j] == ' ') {
                            	if(minesweeper_print[i+1][j] == ' ')
                            		continue;
                                if(minesweeper[i+1][j] == '0' && minesweeper_print[i+1][j] != 'F'){
                                    minesweeper_print[i+1][j] = ' ';
                                    leftover_cells--;
                                }
                                else if(minesweeper[i+1][j] == 'B')
                                    continue;
                                else if(minesweeper_print[i+1][j] == 'X'){
                                    minesweeper_print[i+1][j] = minesweeper[i+1][j];
                                    leftover_cells--;
                                    continue;
                                }
                            }
                        }
                    }
                    for (size_t j = 0; j < size; j++) {
                        for (size_t i = size-1; i > 0; i--) {
                            if (minesweeper_print[i][j] == ' ') {
                            	if(minesweeper_print[i-1][j] == ' ')
                            		continue;
                                if(minesweeper[i-1][j] == '0' && minesweeper_print[i-1][j] != 'F'){
                                    minesweeper_print[i-1][j] = ' ';
                                    leftover_cells--;
                                }
                                else if(minesweeper[i-1][j] == 'B')
                                    continue;
                                else if(minesweeper_print[i-1][j] == 'X'){
                                    minesweeper_print[i-1][j] = minesweeper[i-1][j];
                                    leftover_cells--;
                                    continue;
                                }
                            }
                        }
                    }
                }
                for (size_t i = 0; i < size; i++) {
                    for (size_t j = 0; j < size; j++) {
                        if(minesweeper_print[i][j] == ' '){
                            if(j!=0 && i!=0 && minesweeper[i-1][j-1]!='0' && minesweeper_print[i-1][j-1]=='X'){
                                minesweeper_print[i-1][j-1] = minesweeper[i-1][j-1];
                                leftover_cells--;
                            }
                            if(j!=size-1 && i!=size-1 && minesweeper[i+1][j+1]!='0' && minesweeper_print[i+1][j+1]=='X'){
                                minesweeper_print[i+1][j+1] = minesweeper[i+1][j+1];
                                leftover_cells--;
                            }
                            if(i!=0 && j!=size-1 && minesweeper[i-1][j+1]!='0' && minesweeper_print[i-1][j+1]=='X'){
                                minesweeper_print[i-1][j+1] = minesweeper[i-1][j+1];
                                leftover_cells--;
                            }
                            if(j!=0 && i!=size-1 && minesweeper[i+1][j-1]!='0' && minesweeper_print[i+1][j-1]=='X'){
                                minesweeper_print[i+1][j-1] = minesweeper[i+1][j-1];
                                leftover_cells--;
                            }
                        }
                    }
                }
				clear_screen();
				print_playground(minesweeper_print,size);
				cursor_to_pos(x,y);
    			}
    		}
	}
void game_win(player minesweeper_player[],char** minesweeper,char** minesweeper_print,int size,int player){
    minesweeper_player[player].score += size;
    for (size_t i = 0; i < size; i++) {
        delete[] minesweeper[i];
    }
    delete[] minesweeper;
    for (size_t i = 0; i < size; i++) {
        delete[] minesweeper_print[i];
    }
    delete[] minesweeper_print;
    }
void game_save(player minesweeper_player[] ,char** minesweeper , char** minesweeper_print , int size , int player){

        minesweeper_player[player].minesweeper = minesweeper;
        minesweeper_player[player].minesweeper_print = minesweeper_print;
        minesweeper_player[player].size = size;
        minesweeper_player[player].save = true;
}
void game_lose(char** minesweeper , char** minesweeper_print , int size){
    for (size_t i = 0; i < size; i++) {
        delete[] minesweeper[i];
    }
    delete[] minesweeper;
    for (size_t i = 0; i < size; i++) {
        delete[] minesweeper_print[i];
    }
    delete[] minesweeper_print;
    }
int new_user_page(player minesweeper_player[] , int& player){
    if(minesweeper_player[9].player_bool==true){
        clear_screen();
        change_color_rgb(242, 10, 10);
        printf("\n New user can not be added.\n");
        reset_color();
        printf("\n Press space to continue.\n");
        while(true){
            char input = getch();
            if(input == SPACE)
                return 0;
        }
    }
    bool check = false;
    int i = 0;
    char* name = new char[50];
    std::cin.ignore();
    name = name_page();
    	while(true){
        while(minesweeper_player[i].player_bool == true){
        	if(compare(minesweeper_player[i].name,name) == true){
        		check = true;
        		break;
    		}
        	i++;
    	}
        if(check == true){
        	change_color_rgb(242, 10, 10);
            printf("\n This username is not available.");
            reset_color();
            printf("\n Enter another username: ");
            //std::cin.ignore();
            std::cin.getline(name,30);
            check = false;
        }
        else{
            for (size_t i = 0; i < 10; i++) {
                if(minesweeper_player[i].player_bool==false){
                    player = i;
                    minesweeper_player[i].name = name;
                    minesweeper_player[i].player_bool = true;
                    return 0;
                }
            }
        }
    }
}
void change_name_page(player minesweeper_player[] , int& player){
    char* new_name = new char[50];
    clear_screen();
    printf("\n Enter your new name: ");
    std::cin.ignore();
    std::cin.getline(new_name,50);
    bool check = false;
    int i = 0;
    	while(true){
        while(minesweeper_player[i].player_bool == true){
        	if(compare(minesweeper_player[i].name,new_name) == true && player!=i){
        		check = true;
        		break;
    		}
        	i++;
    	}
        if(check == true){
        	change_color_rgb(242, 10, 10);
            printf("\n This username is already in use.");
            reset_color();
            printf("\n Press space to continue with this username.\n" );
            printf(" Press C to change the username.\n" );
            while(true){
                char input_1 = getch();
                if(input_1 == SPACE){
                    player = i;
                    return;
                }
                else if(input_1 == 'c' || input_1 == 'C'){
                    break;
                }
            }
            printf("\n Enter another username: ");
            //std::cin.ignore();
            std::cin.getline(new_name,50);
            check = false;
        }
        else{
            minesweeper_player[player].name = new_name;
            break;
        }
    }
    	printf(" Press spase to continue.");
    	while(true){
        	char input_2 = getch();
        	if(input_2 == SPACE)
        	    break;
    	}

}
void leaderboard_page(player minesweeper_player[]){
    clear_screen();
    int temp_score , temp_id;
    char* temp_name = new char[50];
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9-i; j++)
            if (minesweeper_player[j + 1].score > minesweeper_player[j].score){
                temp_score = minesweeper_player[j + 1].score;
                minesweeper_player[j + 1].score = minesweeper_player[j].score;
                minesweeper_player[j].score = temp_score;

                temp_name = minesweeper_player[j + 1].name;
                minesweeper_player[j + 1].name = minesweeper_player[j].name;
                minesweeper_player[j].name = temp_name;

                temp_id = minesweeper_player[j + 1].id;
                minesweeper_player[j + 1].id = minesweeper_player[j].id;
                minesweeper_player[j].id = temp_id;
            }
    std::cout << std::endl;
    for (int j = 0; j < 5; j++) {
        if(minesweeper_player[j].player_bool == false)
            break;
        else{
            change_color_rgb(7, 229, 245);
            std::cout << " " << j+1 << " " ;
            reset_color();
            printf("%s : %d\n",minesweeper_player[j].name,minesweeper_player[j].score);
        }
    }
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9-i; j++)
            if (minesweeper_player[j + 1].id < minesweeper_player[j].id){
                temp_id = minesweeper_player[j + 1].id;
                minesweeper_player[j + 1].score = minesweeper_player[j].id;
                minesweeper_player[j].id = temp_id;

                temp_score = minesweeper_player[j + 1].score;
                minesweeper_player[j + 1].score = minesweeper_player[j].score;
                minesweeper_player[j].score = temp_score;

                temp_name = minesweeper_player[j + 1].name;
                minesweeper_player[j + 1].name = minesweeper_player[j].name;
                minesweeper_player[j].name = temp_name;

            }
    std::cout << "\n Press space to continue.";
    while(true){
    	char input = getch();
    	if(input == SPACE)
    		break;
    }
}
