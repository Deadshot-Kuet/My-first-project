#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct user{
char username[30];
int password;
};
int signup(){
    struct user u;
    FILE *fp;
    fp=fopen("User.txt","a");
    if(fp==NULL){
        printf("Error!!!");
    }
    printf("Enter your name:\n");
    scanf("%s",u.username);
    printf("Enter your pin:\n");
    scanf("%d",&u.password);
    fprintf(fp,"%s %d\n",u.username,u.password);
    printf("\n=====Signup successful=====\n\n");
    fclose(fp);
    return 0;
}

int login(){
    char logname[30];
    int logpin;
    printf("Enter your name:\n");
    scanf("%s",logname);
    printf("Enter your pin:\n");
    scanf("%d",&logpin);
    FILE *fp;
    fp=fopen("User.txt","r");
    if(fp==NULL){
        printf("Error...");
        return 0;
    }
    int find=0;
    struct user u;
    while(fscanf(fp,"%s %d",u.username,&u.password)!=EOF){
        if(strcmp(u.username,logname)==0 && u.password==logpin){
            find=1;
            break;
        }
    }
    fclose(fp);
    return find;
}

void printboard(int mat[4][4]);
void generaterandomtwo(int mat[4][4]);
void moveleft(int mat[4][4]);
void moveright(int mat[4][4]);
void moveup(int mat[4][4]);
void movedown(int mat[4][4]);
int movechecker(int mat[4][4],char c);
int gameover(int mat[4][4]);
void scores(int ns);

int menu() {
    int choice;
    printf("\n===== MAIN MENU =====\n");
    printf("1. Start Game\n");
    printf("2. High Scores\n");
    printf("3. Quit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

void showHighScores() {
    FILE *fp = fopen("score.txt", "r");
    if (fp == NULL) {
        fp = fopen("score.txt", "w");
        fclose(fp);
        fp = fopen("score.txt", "r");
    }
    int score, rank = 1;
    printf("\n===== HIGH SCORES =====\n");
    while (fscanf(fp, "%d", &score) != EOF) {
        printf("%d. %d\n", rank, score);
        rank++;
    }
    fclose(fp);
    if (rank == 1) {
        printf("No scores yet!\n");
    }
    printf("\nPress ENTER to return to menu...");
    getchar(); getchar();
}

int main() {

    int choice;
    printf("Enter your choice:\n1.Sign Up\n2.Log in\n");
    scanf("%d",&choice);

    if(choice==1){
        signup();
        printf("Continue to log in.....\n\n");
        int success=login();
        if(success==0){
            printf("\n!!!!!Invalid Username or pin!!!!!\n");
            return 0;
        }
    }
    else if(choice==2){
        int success=login();
        if(success==0){
            printf("\n!!!!!Invalid Username or pin!!!!!\n");
            return 0;
        }
    }
    else{
        printf("Invalid error....");
        return 0;
    }

    while (1) {

        int opt = menu();

        if (opt == 1) {
            int mat[4][4] = {0};
            int moves = 0;
            char move;
            srand(time(0));
            generaterandomtwo(mat);
            generaterandomtwo(mat);
            while(1) {
                system("cls");
                printboard(mat);
                if (gameover(mat)) {
                    printf("\n===== GAME OVER =====\n");
                    break;
                }
                printf("\nMove (w/a/s/d) or q to quit: ");
                scanf(" %c", &move);
                if (move == 'q') break;
                if (movechecker(mat, move)) {
                    switch(move) {
                        case 'a': moveleft(mat); break;
                        case 'd': moveright(mat); break;
                        case 'w': moveup(mat); break;
                        case 's': movedown(mat); break;
                    }
                    generaterandomtwo(mat);
                    moves++;
                }
            }
            printf("\nTotal moves: %d\n", moves);
            scores(moves);
        }

        else if (opt == 2) {
            showHighScores();
        }

        else if (opt == 3) {
            printf("\nExiting... Goodbye!\n");
            break;
        }

        else {
            printf("\nInvalid option!\n");
        }
    }

    return 0;
}

void printboard(int mat[4][4]){
    printf("\n---------------------\n");
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            if (mat[i][j]==0) printf("|    ");
            else printf("|%4d",mat[i][j]);
        }
        printf("|\n---------------------\n");
    }
}

void generaterandomtwo(int mat[4][4]){
    int row, col;
    do {
        row = rand() % 4;
        col = rand() % 4;
    } while(mat[row][col] != 0);
    mat[row][col] = 2;
}

int movechecker(int mat[4][4], char c){
    int i,j;
    if(c=='a'){
        for(i=0;i<4;i++){
            for(j=1;j<4;j++){
                if(mat[i][j]!=0){
                    if(mat[i][j-1]==0 || mat[i][j-1]==mat[i][j]) return 1;
                }
            }
        }
    }
    else if(c=='d'){
        for(i=0;i<4;i++){
            for(j=2;j>=0;j--){
                if(mat[i][j]!=0){
                    if(mat[i][j+1]==0 || mat[i][j+1]==mat[i][j]) return 1;
                }
            }
        }
    }
    else if(c=='w'){
        for(j=0;j<4;j++){
            for(i=1;i<4;i++){
                if(mat[i][j]!=0){
                    if(mat[i-1][j]==0 || mat[i-1][j]==mat[i][j]) return 1;
                }
            }
        }
    }
    else if(c=='s'){
        for(j=0;j<4;j++){
            for(i=2;i>=0;i--){
                if(mat[i][j]!=0){
                    if(mat[i+1][j]==0 || mat[i+1][j]==mat[i][j]) return 1;
                }
            }
        }
    }
    return 0;
}

void moveleft(int mat[4][4]){
    for(int i=0;i<4;i++){
        for(int k=0;k<3;k++){
            for(int j=0;j<3;j++){
                if(mat[i][j]==0){
                    mat[i][j]=mat[i][j+1]; mat[i][j+1]=0;
                }
            }
        }
        for(int j=0;j<3;j++){
            if(mat[i][j]==mat[i][j+1] && mat[i][j]!=0){
                mat[i][j]*=2; mat[i][j+1]=0;
            }
        }
        for(int k=0;k<3;k++){
            for(int j=0;j<3;j++){
                if(mat[i][j]==0){
                    mat[i][j]=mat[i][j+1]; mat[i][j+1]=0;
                }
            }
        }
    }
}

void moveright(int mat[4][4]){
    for(int i=0;i<4;i++){
        for(int k=0;k<3;k++){
            for(int j=3;j>0;j--){
                if(mat[i][j]==0){ mat[i][j]=mat[i][j-1]; mat[i][j-1]=0; }
            }
        }
        for(int j=3;j>0;j--){
            if(mat[i][j]==mat[i][j-1] && mat[i][j]!=0){ mat[i][j]*=2; mat[i][j-1]=0; }
        }
        for(int k=0;k<3;k++){
            for(int j=3;j>0;j--){
                if(mat[i][j]==0){ mat[i][j]=mat[i][j-1]; mat[i][j-1]=0; }
            }
        }
    }
}

void moveup(int mat[4][4]){
    for(int j=0;j<4;j++){
        for(int k=0;k<3;k++){
            for(int i=0;i<3;i++){
                if(mat[i][j]==0){ mat[i][j]=mat[i+1][j]; mat[i+1][j]=0; }
            }
        }
        for(int i=0;i<3;i++){
            if(mat[i][j]==mat[i+1][j] && mat[i][j]!=0){ mat[i][j]*=2; mat[i+1][j]=0; }
        }
        for(int k=0;k<3;k++){
            for(int i=0;i<3;i++){
                if(mat[i][j]==0){ mat[i][j]=mat[i+1][j]; mat[i+1][j]=0; }
            }
        }
    }
}

void movedown(int mat[4][4]){
    for(int j=0;j<4;j++){
        for(int k=0;k<3;k++){
            for(int i=3;i>0;i--){ if(mat[i][j]==0){ mat[i][j]=mat[i-1][j]; mat[i-1][j]=0; }}
        }
        for(int i=3;i>0;i--){ if(mat[i][j]==mat[i-1][j] && mat[i][j]!=0){ mat[i][j]*=2; mat[i-1][j]=0; }}
        for(int k=0;k<3;k++){
            for(int i=3;i>0;i--){ if(mat[i][j]==0){ mat[i][j]=mat[i-1][j]; mat[i-1][j]=0; }}
        }
    }
}

int gameover(int mat[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (mat[i][j] == 0) return 0;
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (mat[i][j] == mat[i][j+1])
                return 0;
        }
    }
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            if (mat[i][j] == mat[i+1][j])
                return 0;
        }
    }
    return 1;
}

void scores(int ns){
    FILE *fp;
    fp=fopen("score.txt","r");
    if (fp == NULL) {
        fp = fopen("score.txt", "w");
        fclose(fp);
        fp = fopen("score.txt", "r");
    }
    int n=0; char c;
    while(fscanf(fp,"%c",&c)!=EOF){
        if(c=='\n') n++;
    } n++;
    rewind(fp);
    int *hi = malloc(n * sizeof(int));
    if(hi == NULL){
        return;
    }
    hi[n-1] = ns;
    for(int i=0;i<n-1;i++){
        fscanf(fp,"%d",&hi[i]);
    }
    fclose(fp);
    fp=fopen("score.txt","w");
    int i,j,temp;
    for(i=0;i<n-1;i++){
        for(j=0;j<n-1;j++){
            if(hi[j]<hi[j+1]){
                temp=hi[j];
                hi[j]=hi[j+1];
                hi[j+1]=temp;
            }
        }
    }
    for(i=0;i<n;i++){
        fprintf(fp,"%d\n",hi[i]);
    }
    fclose(fp);
    free(hi);
}
