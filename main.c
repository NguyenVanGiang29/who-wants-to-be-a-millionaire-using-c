#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <dos.h>
#include <windows.h>
#include <time.h>

COORD coord={0,0}; // This is for cursor position

int earnings[15]={1000,2000,4000,8000,15000,30000,40000,50000,80000,100000,200000,300000,600000,800000,1000000};
int totalEarnings, questionNumber, ULLcount=0, entry, gq=0, x, scoresorted[300];
char aName[100],usedlifeline[3];
char doGENERATEWRONG(char correct);
char doGENERATE2WRONG(char correct1,char correct2);
void doSORTARRAY(int*aNumber, int size);
char entrytemp[100], conventry[100], paris[100], optchoice;
char convscore[10][300];
char COPYRIGHT[75]={"GAME CREATED AND DESIGNED BY PAUL ELEP, WALEED OCCIDENTAL, & DAVID PASUMBAL"};

struct bank{
    char question[120];
    char choiceA[70];
    char choiceB[70];
    char choiceC[70];
    char choiceD[70];
    char answer[5];
}set[30]; //Array size for getting questions per level

struct highscore{
    int entries;
    char aName[15];
    char score[7];
}top[100],top2[100]; //Array size for high scores txt file

FILE*eBank;
FILE*mBank;
FILE*hBank;
FILE*sBank;
FILE*sBank2;

// MAIN GAME FUNCTIONS

void showHOMESCREEN(){ //Displays options (Play, HS, Exit)
    ULLcount=0;
    totalEarnings=0;
    questionNumber=0;
    usedlifeline[0]='X'; //Sets all lifelines to null
    usedlifeline[1]='X';
    usedlifeline[2]='X';
    system("COLOR f1");
    doDRAWRECTANGLE(44,9,74,13);
    gotoxy(55,10);
    printf(" WELCOME");
    gotoxy(58,11);
    printf("TO");
    gotoxy(45,12);
    printf("WHO WANTS TO BE A MILLIONAIRE");
    doDRAWRECTANGLE(48,16,70,20);
    gotoxy(53,17);
    printf("A. PLAY GAME ");
    gotoxy(50,18);
    printf("B. VIEW HIGHSCORES ");
    gotoxy(55,19);
    printf("C. EXIT");
    do{
        optchoice=(toupper(getch()));
    }while(optchoice!='A' && optchoice!='B' && optchoice!='C');
    switch (optchoice){
    case 'A': doPLAYTHEGAME();
              showLOADING(1);
              break;
    case 'B': showLOADING(1);
              showHS();
              break;
    case 'C': doCLS();
              gotoxy(((118-(46+strlen(aName)))/2),15);
              printf("Hope to see you play the game again %s, goodbye!", aName);
              gotoxy(0,30);
              exit(1);
              break;
    }
}

void doPLAYTHEGAME(){ // Activates the Game sequence
    showLOADING(1);
    doASKNAME();
    doEASYROUND();
    doMODERATEROUND();
    doHARDROUND();
    showMILLIONAIRE();

}

void doASKNAME(){ // Asks user for aName to be used throughout game
    Back:
    doCLS();
    system("COLOR B0");
    do{
        doDRAWRECTANGLE(39,13,79,18);
        gotoxy(45,14);
        printf("Okay then, what is your name?");
        gotoxy(51,17);
        printf("---------------");
        gotoxy(51,16);
        gets(aName);
        if(strlen(aName)<2 || strlen(aName)>12){
            doCLS();
            system("COLOR B4");
            system("COLOR B4");
            system("COLOR B4");
            system("COLOR B0");
            gotoxy(40,15);
            printf("Name must contain 2-12 characters only.\n");
        }
    }while(strlen(aName)<2 || strlen(aName)>12);
    doCLS();
    doDRAWRECTANGLE(33,13,83,18);
    gotoxy(((118-(35+strlen(aName)))/2),14);
    printf("So your name is %s. Is that correct?", aName);
    gotoxy(((118-(3+strlen(aName)))/2),15);
    printf("A. Yes.");
    gotoxy(((118-(8+strlen(aName)))/2),16);
    printf("B. No, change it.");
    do{
        optchoice=toupper(getch());
    }while(optchoice!='A' && optchoice!='B');
    if(optchoice=='B'){
        goto Back;
    }
    doCLS();
    doDRAWRECTANGLE(40,13,76,17);
    gotoxy(((117-(20+strlen(aName)))/2),14);
    printf("Okay %s, let us begin!", aName);
    showLOADING(1);
    gotoxy(46,16);
    printf("Press any key to continue");
    getch();
}

int doEASYROUND(){ // Gets and stores questions for Easy Round
    if((eBank = fopen("easybank.TXT", "r"))==NULL){
        showFILEERROR();
    }
    else{
        while(!feof(eBank)){
            for(x=0; x<30; x++){ // Reads the questions from file
                fgets(set[x].question, 120, eBank);
                fgets(set[x].choiceA, 70, eBank);
                fgets(set[x].choiceB, 70, eBank);
                fgets(set[x].choiceC, 70, eBank);
                fgets(set[x].choiceD, 70, eBank);
                fgets(set[x].answer, 70, eBank);
            }
        }
    }
    doSHOWQUESTIONS(1);
    fclose(eBank);
}

int doMODERATEROUND(){ // Gets and stores questions for Moderate Round
    if((mBank = fopen("moderatebank.TXT", "r"))==NULL){
        showFILEERROR();
    }
    else{
        while(!feof(mBank)){
            for(x=0; x<30; x++){ // Reads the questions from file
                fgets(set[x].question, 120, mBank);
                fgets(set[x].choiceA, 70, mBank);
                fgets(set[x].choiceB, 70, mBank);
                fgets(set[x].choiceC, 70, mBank);
                fgets(set[x].choiceD, 70, mBank);
                fgets(set[x].answer, 70, mBank);
            }
        }
    }
    doSHOWQUESTIONS(2);
    fclose(mBank);
}

void doHARDROUND(){ // Gets and stores questions for Hard Round
    if((hBank = fopen("hardbank.TXT", "r"))==NULL){
        showFILEERROR();
    }else{
        while(!feof(hBank)){
            for(x=0; x<30; x++){ // Reads the questions from file
                fgets(set[x].question, 120, hBank);
                fgets(set[x].choiceA, 70, hBank);
                fgets(set[x].choiceB, 70, hBank);
                fgets(set[x].choiceC, 70, hBank);
                fgets(set[x].choiceD, 70, hBank);
                fgets(set[x].answer, 70, hBank);
            }
        }
    }
    doSHOWQUESTIONS(3);
    fclose(hBank);
}

void doSHOWQUESTIONS(int level){ // Function for displaying questions from level and options for bef. and aft. questions
    int  questionCount, usedQuestion[5]={-1,-1,-1,-1,-1}, uq=0;
    // questionCount-Total number of questions per level, usedQuestion-Array for questions used at most once
    // gq-getting questions from bank(0-29), uq-to assign question to usedQuestion, x-counter for reading bank

    doCLS();
    srand(time(NULL));
    for(questionCount=0; questionCount<5; questionCount++){
        questionNumber++;
        do{
            gq=(rand()%30); // Generates a number until 30(array 29)

        }while(gq==usedQuestion[0] || gq==usedQuestion[1] || gq==usedQuestion[2] || gq==usedQuestion[3] || gq==usedQuestion[4]);
        usedQuestion[uq]=gq;
        if(questionNumber!=1){ // Ensures the code inside does not print when in Q1
            doDRAWRECTANGLE(44,12,72,17);
            gotoxy(((118-(5+strlen(aName)))/2),13);
            printf("So, %s,", aName);
            gotoxy(46,14);
            printf("Do you want to continue?");
            gotoxy(52,15);
            printf("(A) Continue.");
            gotoxy(((117-(19+getDIGITSEARNINGS(totalEarnings)))/2),16);
            printf("(B) Walk away with %d.",totalEarnings);
            do{
                optchoice=toupper(getch());
            }while(optchoice!='A' && optchoice!='B');
        }
        if(optchoice=='B'){
            doCLS();
            system("COLOR F1");
            doDRAWRECTANGLE(23,13,95,17);
            gotoxy(((118-(21+strlen(aName)+getDIGITSEARNINGS(totalEarnings)))/2),14);
            printf("%s, Your earnings are: %d", aName, totalEarnings);
            gotoxy(((118-(54+strlen(aName)))/2),15);
            printf("Thank you for playing WHO WANTS TO BE A MILLIONAIRE?, %s!!", aName); // 56+15=71, m36
            gotoxy(42,16);
            printf("Hope to play with you again soon!");
            doHIGHSCOREENTRY(aName, totalEarnings);
            gotoxy(0,60);
            exit(1);
            break;
        }else{
        system("COLOR F2");
        doCLS();
        if(questionNumber!=1){
            gotoxy(1,1);
            printf("Alright %s, onto the next question!\n", aName);
        }
        doDRAWRECTANGLE(51,3,67,5); // border for question number
        doDRAWRECTANGLE(1,6,117,8); // border for question
        doDRAWRECTANGLE(15,9,104,17); // Initial border for choices
        doDRAWRECTANGLE(16,10,55,12); // border for A
        doDRAWRECTANGLE(16,14,55,16); // border for B
        doDRAWRECTANGLE(64,10,103,12); // border for C
        doDRAWRECTANGLE(64,14,103,16);  // border for D
        gotoxy(55,4);
        printf("Question %d\n", questionNumber);
        gotoxy(((121-strlen(set[gq].question))/2),7);
        printf("%s",set[gq].question);
        gotoxy(17,11);
        printf("%s",set[gq].choiceA);
        gotoxy(17,15);
        printf("%s",set[gq].choiceB);
        gotoxy(65,11);
        printf("%s",set[gq].choiceC);
        gotoxy(65,15);
        printf("%s",set[gq].choiceD);
        afterQ:
        gotoxy(35,19);
        printf("\t%s, do you want to...", aName);
        gotoxy(30,21);
        printf("\t(A) Pick an answer from the choices");
        if(questionNumber!=15){
        gotoxy(30,23);
        printf("\t(B) Use a life line.");
        }
        if(ULLcount!=3){
            printf("(Lifelines left :%d)", 3-ULLcount);
        }else{
            printf("(No lifelines left.)");
        }
        if(questionNumber!=1){
            if(questionNumber==15){
            gotoxy(30,23);
            printf("\t(C) Or walk away with 1/2 of the earnings.");
            }else{
            gotoxy(30,25);
            printf("\t(C) Or walk away with 1/2 of the earnings.");
            }
            do{
                gotoxy(33,27);
                optchoice=toupper(getchar());
            }while(optchoice!='A' && optchoice!='B' && optchoice!='C');
            goto Forward;
        }else if(questionNumber==15){
            do{
                gotoxy(33,27);
                optchoice=toupper(getchar());
            }while(optchoice!='A' && optchoice!='C');
        }else
        do{
            gotoxy(33,27);
            optchoice=toupper(getchar());
        }while(optchoice!='A' && optchoice!='B');

        Forward:
        doSHOWQAGAIN();
        if(usedlifeline[0]=='A' && usedlifeline[1]=='B' && usedlifeline[2]=='C' && optchoice=='B'){
            system("COLOR 74");
            system("COLOR 74");
            system("COLOR 74");
            system("COLOR F2");
            gotoxy(42,24);
            printf("You already used all your lifelines\n"); // 35, m17
            goto afterQ;
        }
        switch(optchoice){
            case 'A':break;
            case 'B':system("COLOR 7C");
                     doLIFELINE(*set[gq].answer,gq);
                     break;
            case 'C':system("COLOR F1");
                     doCLS();
                     gotoxy(24,9);
                     printf("Alright, you've chosen to walk away with 1/2 of your current earnings.");
                     gotoxy(39,10);
                     printf("The correct answer is ");
                     switch(*set[gq].answer){
                        case'A':printf("%s\n\n", set[gq].choiceA);
                                break;
                        case'B':printf("%s\n\n", set[gq].choiceB);
                                break;
                        case'C':printf("%s\n\n", set[gq].choiceC);
                                break;
                        case'D':printf("%s\n\n", set[gq].choiceD);
                                break;
                     }
                     gotoxy(((118-(19+getDIGITSEARNINGS(totalEarnings)))/2),12);
                     printf("Your earnings are: %d", totalEarnings=totalEarnings/2);
                     gotoxy(((118-(54+strlen(aName)))/2),15);
                     printf("Thank you for playing WHO WANTS TO BE A MILLIONAIRE?, %s!!", aName);
                     gotoxy(42,16);
                     printf("Hope to play with you again soon!", aName);
                     doHIGHSCOREENTRY(aName, totalEarnings);
                     exit(1);
        }
        doGETANSWER(gq, level, *set[gq].answer);
        uq++;
        }
    }
}

void doGETANSWER(int gq, int level, char correct){ // Function for getting answer from user. From SHOWQUESTIONS
        char answer;
        int choice;
            ifB:
            gotoxy(30,22);
            printf("Okay, what is your answer %s? ", aName); // 27+15=42, m21
        do{
            answer=toupper(getch());
        }while(answer!='A' && answer!='B' && answer!='C' && answer!='D');
            if(level==2 || level==3){
                gotoxy(28,22);
                printf("Your answer is %c, Do you want to continue?", answer);
                gotoxy(30,23);
                printf("A. Yes");
                gotoxy(30,24);
                printf("B. No");
                do{
                    choice=toupper(getch());
                }while(choice!='A' && choice!='B');
                if(choice=='B'){
                    doSHOWQAGAIN();
                    goto ifB;
                }
                if(choice=='A'){
                    if(answer==correct){
                        system("COLOR 2F");
                        doCLS();
                        gotoxy(((118-(18+strlen(aName)))/2),6);
                        printf("You got it right %s!", aName); //18+15=33, m17
                        totalEarnings=earnings[questionNumber-1];
                    }else{
                        doSHOWWRONG();
                    }
                }
            }
            if(answer==correct){
                system("COLOR 2F");
                doCLS();
                gotoxy(((118-(18+strlen(aName)))/2),6);
                printf("You got it right %s!", aName);
                totalEarnings=earnings[questionNumber-1];
            }else{
                doSHOWWRONG();
            }
}





// LIFELINE FUNCTIONS

void doLIFELINE(char correct, int gq){ // Displays options for Lifeline
    char LLChoice;
    gotoxy(35,19);
    printf("Choose a lifeline\n");
    if(usedlifeline[0]!='A'){
        gotoxy(35,20);
        printf("A. Call a friend\n");
    }
    if(usedlifeline[1]!='B'){
        gotoxy(35,21);
        printf("B. Ask the audience\n");
    }
    if(usedlifeline[2]!='C'){
        gotoxy(35,22);
        printf("C. 50/50\n");
    }

    do{
        LLChoice=toupper(getch());
    }while((LLChoice!='A' && LLChoice!='B' && LLChoice!='C') || LLChoice==usedlifeline[0] || LLChoice==usedlifeline[1] || LLChoice==usedlifeline[2]);
    switch(LLChoice){
        case'A':showCALLAFRIEND(correct);
                usedlifeline[0]='A';
                ULLcount++;
                break;
        case'B':showASKTHEAUDIENCE(correct);
                usedlifeline[1]='B';
                ULLcount++;
                break;
        case'C':showFIFTYFIFTY(correct, gq);
                usedlifeline[2]='C';
                ULLcount++;
                break;
    }
}

void showCALLAFRIEND(char correct){ // Part of LL
    doSHOWQAGAIN();
    int typefriend;
    typefriend=(rand()%3)+1;
    switch(typefriend){
        case 1: showWISEFRIEND(correct);
                break;
        case 2: showUNSUREFRIEND(correct);
                break;
        case 3: showARROGANTFRIEND(correct);
                break;
    }
}

void showASKTHEAUDIENCE(char correct){ // Part of LL
    doSHOWQAGAIN();
    srand(time(NULL));
    int audiencePct[3];
    int probability;
    int a,b,c,d;
    probability=(rand()%100)+1;
    do{
        audiencePct[0]=(rand()%100)+1;
        audiencePct[1]=(rand()%100)+1;
        audiencePct[2]=(rand()%100)+1;
        audiencePct[3]=(rand()%100)+1;
    }while(audiencePct[0]+audiencePct[1]+audiencePct[2]+audiencePct[3]!=100);
    if(probability<=60){
        doSORTARRAY(audiencePct,4);
        switch(correct){
        case'A':gotoxy(70,21);
                printf("%d%% of the audience thinks the answer is A\n", audiencePct[0]);
                gotoxy(70,22);
                printf("%d%% of the audience thinks the answer is B\n", audiencePct[a=doGEN1RANDOMINT()]);
                gotoxy(70,23);
                printf("%d%% of the audience thinks the answer is C\n", audiencePct[doGEN2RANDOMINT(a)]);
                gotoxy(70,24);
                printf("%d%% of the audience thinks the answer is D\n", audiencePct[doGEN3RANDOMINT(a,doGEN2RANDOMINT(a,audiencePct))]);
                break;
        case'B':gotoxy(70,21);
                printf("%d%% of the audience thinks the answer is A\n", audiencePct[a=doGEN1RANDOMINT()]);
                gotoxy(70,22);
                printf("%d%% of the audience thinks the answer is B\n", audiencePct[0]);
                gotoxy(70,23);
                printf("%d%% of the audience thinks the answer is C\n", audiencePct[doGEN2RANDOMINT(a)]);
                gotoxy(70,24);
                printf("%d%% of the audience thinks the answer is D\n", audiencePct[doGEN3RANDOMINT(a,doGEN2RANDOMINT(a))]);
                break;
        case'C':gotoxy(70,21);
                a=doGEN1RANDOMINT();
                printf("%d%% of the audience thinks the answer is A\n", audiencePct[a]);
                gotoxy(70,22);
                printf("%d%% of the audience thinks the answer is B\n", audiencePct[doGEN2RANDOMINT(a)]);
                gotoxy(70,23);
                printf("%d%% of the audience thinks the answer is C\n", audiencePct[0]);
                gotoxy(70,24);
                printf("%d%% of the audience thinks the answer is D\n", audiencePct[doGEN3RANDOMINT(a,doGEN2RANDOMINT(a))]);
                break;
        case'D':gotoxy(70,21);
                a=doGEN1RANDOMINT();
                printf("%d%% of the audience thinks the answer is A\n", audiencePct[a]);
                gotoxy(70,22);
                printf("%d%% of the audience thinks the answer is B\n", audiencePct[doGEN2RANDOMINT(a)]);
                gotoxy(70,23);
                printf("%d%% of the audience thinks the answer is C\n", audiencePct[doGEN3RANDOMINT(a,doGEN2RANDOMINT(a))]);
                gotoxy(70,24);
                printf("%d%% of the audience thinks the answer is D\n", audiencePct[0]);
                break;
        }

    }else{
        gotoxy(70,21);
        printf("%d%% of the audience thinks the answer is A\n", audiencePct[0]);
        gotoxy(70,22);
        printf("%d%% of the audience thinks the answer is B\n", audiencePct[1]);
        gotoxy(70,23);
        printf("%d%% of the audience thinks the answer is C\n", audiencePct[2]);
        gotoxy(70,24);
        printf("%d%% of the audience thinks the answer is D\n", audiencePct[3]);
    }
}

void showFIFTYFIFTY(char correct,int gq){ // Part of LL
    doCLS();
    doDRAWRECTANGLE(51,3,67,5); // border for question number
    doDRAWRECTANGLE(1,6,117,8); // border for question
    doDRAWRECTANGLE(15,9,104,17); // Initial border for choices
    doDRAWRECTANGLE(16,10,55,12); // border for A
    doDRAWRECTANGLE(16,14,55,16); // border for B
    doDRAWRECTANGLE(64,10,103,12); // border for C
    doDRAWRECTANGLE(64,14,103,16);  // border for D
    gotoxy(55,4);
    printf("Question %d\n", questionNumber);
    gotoxy(((120-strlen(set[gq].question))/2),7);
    printf("%s",set[gq].question);
    char removedchoice[1];
    removedchoice[0]=doGENERATEWRONG(correct);
    removedchoice[1]=doGENERATE2WRONG(correct,removedchoice[0]);
    if(removedchoice[0]!='A' && removedchoice[1]!='A'){
        gotoxy(18,11);
        printf("%s", set[gq].choiceA);
    }
    if(removedchoice[0]!='B' && removedchoice[1]!='B'){
        gotoxy(18,15);
        printf("%s", set[gq].choiceB);
    }
    if(removedchoice[0]!='C' && removedchoice[1]!='C'){
        gotoxy(66,11);
        printf("%s", set[gq].choiceC);
    }
    if(removedchoice[0]!='D' && removedchoice[1]!='D'){
        gotoxy(66,15);
        printf("%s", set[gq].choiceD);
    }
}

void showWISEFRIEND(char correct){ // Part of CaF
    doSHOWQAGAIN();
    showCALLING();
    srand(time(NULL));
    int probability;
    probability=(rand()%10)+1;
    if(probability==10){     // 10% mali
        gotoxy(30,20);
        printf("WISE FRIEND: I think the correct answer is %c",doGENERATEWRONG(correct));    // wrong answer
    }else{                   //90%
        gotoxy(30,20);
        printf("WISE FRIEND: I think the correct answer is %c",correct);
    }
}

void showUNSUREFRIEND(char correct){ // Part of CaF
    doSHOWQAGAIN();
    showCALLING();
    srand(time(NULL));
    int probability;
    probability=(rand()%10)+1;
    if(probability<=5){     //50%
        gotoxy(30,20);
        printf("UNSURE FRIEND: Um, I'm not sure, but I think the correct answer is %c",doGENERATEWRONG(correct)); // wrong answer
    }else{
        gotoxy(30,20);            //50%
        printf("UNSURE FRIEND: Um, I'm not sure, but I think the correct answer is %c",correct);
    }
}

void showARROGANTFRIEND(char correct){ // Part of CaF
    doSHOWQAGAIN();
    showCALLING();
    srand(time(NULL));
    int probability;
    probability=(rand()%10)+1;
    if(probability<=7){     // 70% mali
        gotoxy(30,20);
        printf("ARROGANT FRIEND: Ugh, It's %c",doGENERATEWRONG(correct)); // wrong answer
    }else{                  // 30 % tama
        gotoxy(30,20);
        printf("ARROGANT FRIEND: Ugh, It's %c",correct);
    }
}

char doGENERATEWRONG(char correct){   // Generates a wrong answer
    srand(time(NULL));
    int correctanswer;
    char wronganswer;
    int whichwrong;
    switch(correct){
        case 'A': correctanswer=1;
                  break;
        case 'B': correctanswer=2;
                  break;
        case 'C': correctanswer=3;
                  break;
        case 'D': correctanswer=4;
                  break;
    }
    do{
        whichwrong=(rand()%4)+1;
    }while(whichwrong==correctanswer); //randomize ng wrong answer
    switch(whichwrong){
        case 1: wronganswer='A';
                break;
        case 2: wronganswer='B';
                break;
        case 3: wronganswer='C';
                break;
        case 4: wronganswer='D';
                break;
    }
    return wronganswer;
}

char doGENERATE2WRONG(char correct1,char correct2){ // Generates 2nd wrong answer. For 50/50 Function
    srand(time(NULL));
    int correctanswer1,correctanswer2;
    char wronganswer;
    int whichwrong;
    switch(correct1){
        case 'A': correctanswer1=1;
                  break;
        case 'B': correctanswer1=2;
                  break;
        case 'C': correctanswer1=3;
                  break;
        case 'D': correctanswer1=4;
                  break;
    }
    switch(correct2){
        case 'A': correctanswer2=1;
                  break;
        case 'B': correctanswer2=2;
                  break;
        case 'C': correctanswer2=3;
                  break;
        case 'D': correctanswer2=4;
                  break;
    }
    do{
        whichwrong=(rand()%4)+1;
    }while(whichwrong==correctanswer1 || whichwrong==correctanswer2); //randomize ng wrong answer
    switch(whichwrong){
        case 1: wronganswer='A';
                break;
        case 2: wronganswer='B';
                break;
        case 3: wronganswer='C';
                break;
        case 4: wronganswer='D';
                break;
    }
    return wronganswer;
}

int doGEN1RANDOMINT(){
    int randomint;
    srand(time(NULL));
    do{
        randomint=(rand()%4);
    }while(randomint==0);
    return randomint;
}

int doGEN2RANDOMINT(int a){
    int randomint;
    srand(time(NULL));
    do{
        randomint=(rand()%4);
    }while(randomint==a || randomint==0);
    return randomint;
}

int doGEN3RANDOMINT(int a,int b){
    int randomint;
    srand(time(NULL));
    do{
        randomint=(rand()%4);
    }while(randomint==0 || randomint==a || randomint==b);
    return randomint;
}



// HIGH SCORE FUNCTIONS

void doSORTARRAY(int*aNumber, int size){
    int i,j, temp;
    for(i=0; i<size; i++){
        for(j=i+1; j<size; j++){
            if(aNumber[i]<aNumber[j]){
                temp=aNumber[i];
                aNumber[i]=aNumber[j];
                aNumber[j]=temp;
            }
        }
    }
}

void doHIGHSCOREENTRY(char *aName,int score){ //Function for high score entry attempt
    char convscore[100];
    char playagain;
    entry++;
    sprintf(convscore, "%d", score);
    sprintf(conventry, "%d", entry);
    if((sBank = fopen("scoresbank.TXT", "a"))==NULL){
        printf("Sorry, %s. The file could not be read.\n", aName);
    }
        fprintf(sBank, "%s", conventry);
        fprintf(sBank, "\n");
        fprintf(sBank, "%s", aName);
        fprintf(sBank, "\n");
        fprintf(sBank, "%s", convscore);
        fprintf(sBank, "\n");
        fclose(sBank);
        printSORTED();
        if(totalEarnings!=1000000){
            gotoxy(45,18);
            printf("Press anything to continue....");
            getch();
            doCLS();
            system("COLOR F1");
            doDRAWRECTANGLE(44,14,72,18);
            gotoxy(45,15);
            printf("Do you want to play again?\n");
            gotoxy(45,16);
            printf("A. Yes\n");
            gotoxy(45,17);
            printf("B. No");
            do{
                playagain=toupper(getch());
            }while(playagain!='A' && playagain!='B');
            if(playagain=='A'){
                doCLS();
                printSORTED();
                showHOMESCREEN();
            }else{
                gotoxy(0,31);
                printSORTED();
                exit(1);
            }
        }
}

void showHS(){
    doCLS();
    int i=0,j,x,y;
    int temp1,temp2;
    int score[300];
    char choice;
    system("COLOR F6");
    if((sBank = fopen("scoresbank.TXT", "r"))==NULL){
        showFILEERROR();
    }
    while(!feof(sBank)){
        fgets(paris,100,sBank);
        fgets(top[i].entries,300, sBank);
        fgets(top[i].aName, 100, sBank);
        fgets(top[i].score, 100, sBank);
        i++;
}

    for(j=0; j<300; j++){
        score[j]=atoi(top[j].score);
    }

    gotoxy(53,4);
    printf("HIGH SCORES");
    for(i=0; i<10; i++){
        if(strlen(top[i].aName)>1){
            gotoxy(48,i+6);
            printf("%d\t\t%s\n", score[i],top[i].aName);
        }
    }
    gotoxy(48,i+8);
    printf("A. Home\t\tB. Exit");
    do{
        choice=(toupper(getch()));
    }while(choice!='A' && choice!='B');
    switch (choice){
    case 'A': doCLS();
              showHOMESCREEN();
              break;
    case 'B': doCLS();
              gotoxy(((117-(46+strlen(aName)))/2), 15);
              printf("Hope to see you play the game again %s, goodbye!\n", aName);
              gotoxy(0,31);
              exit(1);
              break;
    }
}

void doSORTHS2(int*aNumber, int size){
    int i,j, temp;
    char temp1[100];
    for(i=0; i<size; i++){
        for(j=i+1; j<size; j++){
            if(aNumber[i]<aNumber[j]){
                strcpy(temp1, top2[i].aName);
                strcpy(top2[i].aName,top2[j].aName);
                strcpy(top2[j].aName,temp1);
                temp=aNumber[i];
                aNumber[i]=aNumber[j];
                aNumber[j]=temp;
            }
        }
    }
}

void doREADENTRYCOUNT(){
    int i;
    if((sBank = fopen("scoresbank.TXT", "r"))==NULL){
        printf("Sorry, %s. The file could not be read.\n", aName);
    }
    else{
    while(!feof(sBank)){
        for(i=0; i<300; i++){

            fgets(entrytemp,100,sBank);
            entry=atoi(entrytemp);
            fgets(top[i].aName, 100, sBank);
            fgets(top[i].score, 100, sBank);

        }
    }
    entry=atoi(entrytemp);
    }
}

void doSHOWWRONG(){ // Displays wrong answer screen
    system("COLOR 4F");
    doCLS();
    gotoxy(25,13);
    printf("Aw, you've chosen the wrong answer! The correct answer was "); // 60, m30even
    switch(*set[gq].answer){
        case'A':printf("%s\n", set[gq].choiceA);
            break;
        case'B':printf("%s\n", set[gq].choiceB);
            break;
        case'C':printf("%s\n", set[gq].choiceC);
            break;
        case'D':printf("%s\n", set[gq].choiceD);
            break;
    }
    totalEarnings=totalEarnings/4;
    gotoxy(((118-(21+strlen(aName)+getDIGITSEARNINGS(totalEarnings)))/2),14);
    printf("%s, Your earnings are: %d", aName, totalEarnings);
    gotoxy(((118-(54+strlen(aName)))/2),15);
    printf("Thank you for playing WHO WANTS TO BE A MILLIONAIRE?, %s!!", aName);
    gotoxy(42,16);
    printf("Hope to play with you again soon!");
    doHIGHSCOREENTRY(aName, totalEarnings);
    exit(1);
}

void readHS(){
    int i=0,j;

    if((sBank2 = fopen("scoresbank.TXT", "r"))==NULL){
        showFILEERROR();
    }
    while(!feof(sBank2)){
        fgets(paris,100,sBank2);
        fgets(top2[i].entries,300, sBank2);
        fgets(top2[i].aName, 100, sBank2);
        fgets(top2[i].score, 100, sBank2);
        i++;
    }
    for(j=0; j<300; j++){
        scoresorted[j]=atoi(top2[j].score);
    }
    doSORTHS2(scoresorted,300);
    fclose(sBank2);
}

void printSORTED(){
    readHS();
    int i=0,j,k,l=0;
    itoa(scoresorted[0], convscore[0], 10);
    itoa(scoresorted[1], convscore[1], 10);
    itoa(scoresorted[2], convscore[2], 10);
    itoa(scoresorted[3], convscore[3], 10);
    itoa(scoresorted[4], convscore[4], 10);
    itoa(scoresorted[5], convscore[5], 10);
    itoa(scoresorted[6], convscore[6], 10);
    itoa(scoresorted[7], convscore[7], 10);
    itoa(scoresorted[8], convscore[8], 10);
    itoa(scoresorted[9], convscore[9], 10);
    writeHS();
}

void writeHS(){
    int i;
    if((sBank2 = fopen("scoresbank.TXT", "w+"))==NULL){
        printf("Sorry, %s. The file could not be read.\n", aName);
    }else
    for(i=0; i<entry&&i<10; i++){
        fprintf(sBank2, "%d", i+1);
        fprintf(sBank2, "\n");
        fprintf(sBank2, "%s", top2[i].aName);
        fprintf(sBank2, "%s", convscore[i]);
        fprintf(sBank2, "\n");
    }
    fclose(sBank2);
}



// DISPLAY FUNCTIONS

void doSHOWQAGAIN(){ // Displays question format again for changes in action area
        doCLS();
        doDRAWRECTANGLE(51,3,67,5); // border for question number
        doDRAWRECTANGLE(1,6,117,8); // border for question
        doDRAWRECTANGLE(15,9,104,17); // Initial border for choices
        doDRAWRECTANGLE(16,10,55,12); // border for A
        doDRAWRECTANGLE(16,14,55,16); // border for B
        doDRAWRECTANGLE(64,10,103,12); // border for C
        doDRAWRECTANGLE(64,14,103,16);  // border for D
        gotoxy(55,4);
        printf("Question %d\n", questionNumber);
        gotoxy(((121-strlen(set[gq].question))/2),7);
        printf("%s",set[gq].question);
        gotoxy(18,11);
        printf("%s",set[gq].choiceA);
        gotoxy(18,15);
        printf("%s",set[gq].choiceB);
        gotoxy(66,11);
        printf("%s",set[gq].choiceC);
        gotoxy(66,15);
        printf("%s",set[gq].choiceD);
}

void showMILLIONAIRE(){
    char choice='X';
    int i;
    doCLS();
    gotoxy(((118-(9+strlen(aName)))/2),7);
    printf("You won %s!", aName);
    gotoxy(43,9);
    printf("Congratulations Mr. Millionaire!");
    gotoxy(35,10);
    printf("Thank you for playing WHO WANTS TO BE A MILLIONAIRE?\n");
    gotoxy(41,12);
    printf("A. Home     B. Play Again     C. Exit");
    totalEarnings=earnings[questionNumber-1]; //millionaire
    doHIGHSCOREENTRY(aName, totalEarnings);
    system("COLOR 7E");
    doDELAY(700);
    system("COLOR AE");
    doDELAY(700);
    system("COLOR 9E");
    doDELAY(700);
    system("COLOR DE");
    doDELAY(700);
    system("COLOR 7E");
    questionNumber=0;
    do{
        choice=(toupper(getch()));
    }while(choice!='A' && choice!='B' && choice!='C');
    switch (choice){
    case 'A': doCLS();
              showHOMESCREEN();
              break;
    case 'B': doCLS();
              doPLAYTHEGAME();
              break;
    case 'C': doCLS();
              gotoxy(((117-(46+strlen(aName)))/2), 15);
              printf("Hope to see you play the game again %s, goodbye!", aName);
              exit(1);
              break;


    }
}

void showFILEERROR(){ // Displays file error screen
    doCLS();
    system("COLOR 40");
    gotoxy(((118-(36+strlen(aName)))/2),15);
    printf("Sorry, %s. The file could not be read.\n", aName);
    gotoxy(0,31);
    exit(1);
}



// DESIGN AND ANIMATION FUNCTIONS

void doDRAWRECTANGLE(int x1, int y1, int x2, int y2){ // Function format for borders
    int i, j;
    gotoxy(x1,y1);
    printf("%c",254);
    for(i = x1; i < x2; i++){
        gotoxy(i+1, y1);
        printf("%c",254);
    }
    gotoxy(x2,y1);
    printf("%c",254);
    for(i = y1; i < y2; i++){
        gotoxy(x2, i+1);
        printf("%c",254);
    }
    gotoxy(x2, y2);
    printf("%c",254);
    for(i = x2; i > x1; i--){
        gotoxy(i-1,y2);
        printf("%c",254);
    }
    gotoxy(x1,y2);
    printf("%c",254);
    for(i = y2; i > y1+1; i--){
        gotoxy(x1,i-1);
        printf("%c",254);
    }
    gotoxy(x1,y2+1);
}

void doCLS(){ // Resets what's being shown in the display
    system("cls");
    doDRAWRECTANGLE(0,0,118,30);
}

int showLOADING(int max){ // Loading Animation
    int i;
    for(i=0; i<max; i++){
        gotoxy(100,29);
        printf("LOADING");
        doDELAY(250);
        printf("%c%c", 177, 177);
        doDELAY(250);
        printf("%c%c", 177, 177);
        doDELAY(250);
        printf("%c%c", 177, 177);
        doDELAY(250);
        printf("%c%c", 177, 177);
        doDELAY(250);
        gotoxy(100,29);
        printf("               ");
    }
}

void showCALLING(){ // Calling Animation
    int i;
    for(i=0; i<3; i++){
        gotoxy(30,18);
        printf("Calling");
        doDELAY(250);
        printf(".");
        doDELAY(250);
        printf(".");
        doDELAY(250);
        printf(".");
        doDELAY(250);
        gotoxy(30,18);
        printf("          ");
    }
}

void doSHOWTITLE(){ // Function for start screen
    gotoxy(15,1);
    printf("@   ,@   .@ @:   @.  :@@@@+     @   ,@   .@   @@    @@   ': ''@+'' @@'@    ;''@''; .@@@@@\n");
    gotoxy(15,2);
    printf("@,  @@.  @, @:   @.  @    @`    @,  @@.  @,   @#,   @;@  ':   @.   @          @    @    @;\n");
    gotoxy(15,3);
    printf(",@  @,@  @  @:   @. #'    '@    ,@  @,@  @   +. @   @ @  ':   @.   @`         @   ,@    .@\n");
    gotoxy(15,4);
    printf(" @  @ @  @  @@@@@@. @.    .@     @  @ @  @   @  @   @ .@ ':   @.   .@@        @   ''     @\n");
    gotoxy(15,5);
    printf(" @ :: @ :;  @:   @. @,    ,@     @ :: @ :;  `@  ';  @  @.':   @.     ,@.      @   '+     @\n");
    gotoxy(15,6);
    printf(" ';@  ';@   @:   @. '#    @;     ';@  ';@   @@@@@@  @   @':   @.      ,@      @   .@    ;@\n");
    gotoxy(15,7);
    printf("  @@   @@   @:   @.  @`  ,@       @@   @@   @    @  @   @@:   @.  .   #'      @    @:  `@\n");
    gotoxy(15,8);
    printf("  @@   @@   @:   @.  `@@@@        @@   @@  ,@    '# @    @:   @.   @@@#       @     @@@@`\n");
    gotoxy(15,12);
    printf("\n");
    gotoxy(15,10);

    printf("                                  @@@;   @@@@@      `@\n");
    gotoxy(15,11);
    printf("                                  @  #@  @          @#,\n");
    gotoxy(15,12);
    printf("                                  @   @  @          @ @\n");
    gotoxy(15,13);
    printf("                                  @  #;  @         :; @\n");
    gotoxy(15,14);
    printf("                                  @@@@#  @@@@      @  ;'\n");
    gotoxy(15,15);
    printf("                                  @   @  @         @'''@\n");
    gotoxy(15,16);
    printf("                                  @   @. @        ';   @\n");
    gotoxy(15,17);
    printf("                                  @  ,@  @        @    ;#\n");
    gotoxy(15,18);
    printf("                                  @@@'   @@@@@    @     @\n");
    gotoxy(15,19);
    printf("\n");
    gotoxy(15,20);
    printf("          @@`    :@.  @  @     @    @.   @@@@   '@    @    @#    @  @@@@,  @@@@@\n");
    gotoxy(15,21);
    printf("          @,@    @@.  @  @     @    @.  @.  ,@  ';@   @   ,;@    @  @   @  @\n");
    gotoxy(15,22);
    printf("          @.@   `@@.  @  @     @    @. #+    @: ':@.  @   @ @`   @  @   @  @\n");
    gotoxy(15,23);
    printf("          @.+;  @ @.  @  @     @    @. @`    ;@ ': @  @   @ `@   @  @   @  @@@@@\n");
    gotoxy(15,24);
    printf("          @. @  @ @.  @  @     @    @. @     :@ ': @; @  ;,  @   @  @'#@   @\n");
    gotoxy(15,25);
    printf("          @. @`#, @.  @  @     @    @. @:    @; ':  @ @  @@@@@,  @  @   @  @\n");
    gotoxy(15,26);
    printf("          @. .@@  @.  @  @     @    @. ,@    @  ':  '#@  @   `@  @  @   @  @\n");
    gotoxy(15,27);
    printf("          @.  @#  @.  @  @@@@` @@@@ @.  #@@@@.  ':   @@ #:    @  @  @   @  @@@@@\n\n\n");
    gotoxy(((120-strlen(COPYRIGHT))/2),29);
    printf("%s\n", COPYRIGHT);

}



// MISCELLANEOUS

int getDIGITSEARNINGS(int n) { // For calculating digits  for digits 4+ for printing
    if (n <= 8000) return 4;
    if (n <= 80000) return 5;
    if (n <= 800000) return 6;
    if (n == 1000000) return 7;
}

void doDELAY(unsigned int mseconds){
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void gotoxy(int x,int y){   // This is for cursor position
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}



// MAIN

void main(){
    doREADENTRYCOUNT(); // Initiates player number in scores log
    system("COLOR f1");
    doCLS();
    doSHOWTITLE();
    showLOADING(3);
    doCLS();
    showHOMESCREEN();
}


