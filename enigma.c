#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EXIT_CODE 1
#define ALPHA 26
#define LAST 25
#define ROTORLEN 27

void error() {
    fprintf(stderr, "Input error.");
    exit(EXIT_CODE);
}

//Standard Input: A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
//Plugboard:      O G V D Z Q B P L X K I N M A H F R T S U C W J Y E
//Rotor I:        E K M F L G D Q V Z N T O W Y H X U S P A I B R C J
//Rotor II:       A J D K S I R U X B L H W T M C Q G Z N P Y F V O E
//Rotor III:      B D F H J L C P R T X V Z N Y E I W G A K M U S Q O

//Reflector B:    AY BR CU DH EQ FS GL IP JX KN MO TZ VW 

//Plugboard -> Rotors -> Reflector -> Rotors -> Plugboard


//Controls the functionality of the reflector. Alphabet is arranged into 13 pairs. 
//Takes an input character and swaps it for its corresponding character
char reflector(char ref) {
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    char output[] = "yruhqsldpxngokmiebfzcwvjat";
    for (int i = 0; i < ALPHA; i++) {
        if (alphabet[i] == ref) return output[i];
        else; 
    } 
    return '/';
}

//Controls the functionality of the rotors. Scans rotor1 for the position of the 
//input, r, and then outputs the character in that position in rotor 2.
char rotor(char r, char rotor1[], char rotor2[]) {
    for (int i = 0; i < ALPHA; i++) {
        if (rotor1[i] == r) return rotor2[i];
        else; 
    } 
    return '/';
}

//Rotates the input rotor by shifting all elements along by one.
//Takes place on every key press for rotor I, every 26 key presses for rotor II 
//and every 676 key presses for rotor III. Assuming that the notches are at the starting position.
//This mimics the mechanical rotation of the rotors within the machine. 
void rotate(char rotor[]) {
    char store = rotor[LAST];
    char rotorStore[ROTORLEN];
    strcpy(rotorStore, rotor);
    for (int i = 0; i < LAST; i++) {
        rotor[i + 1] = rotorStore[i];
    }
    rotor[0] = store;
}

//Controls the functionality of the plugboard. 10 pairs of letters are connected for encryption.
//The remaining 6 letters are connected to themselves
char plugboard(char pb) {
    char input[] = "aobgqfstjxzehpilmncvdkruwy";
    char output[] = "oagbfqtsxjezphlinmvcdkruwy";
    for (int i = 0; i < ALPHA; i++) {
        if (input[i] == pb) return output[i];
        else;
    }
    return '/';
}

//Passes the input to each component to mimic the physical connections of the engima machine
void components(char input[], char rotor1[], char rotor2[], char rotor3[], char encrypt[], int count1, int count2, int i) {
    char pb = plugboard(input[i]);
    char r1 = rotor(pb, rotor1, rotor1);
    char r2 = rotor(r1, rotor1, rotor2);
    char r3 = rotor(r2, rotor2, rotor3);
    char rf = reflector(r3);
    char r4 = rotor(rf, rotor3, rotor3);
    char r5 = rotor(r4, rotor3, rotor2);
    char r6 = rotor(r5, rotor2, rotor1);
    pb = plugboard(r6);
    rotate(rotor1);
    if (count1 % ALPHA == 0) rotate(rotor2);
    if (count2 % ALPHA == 0) rotate(rotor3);
    encrypt[i] = pb;
}

//Passes the individual characters of the input to the components function one by one
void controller(char input[], char rotor1[], char rotor2[], char rotor3[], int count1, int count2) {
    int length = strlen(input);
    char encrypt[length + 1];
    for (int i = 0; i < length; i++) {
        if (input[i] == ' ') encrypt[i] = ' ';
        else {
            components(input, rotor1, rotor2, rotor3, encrypt, count1, count2, i);
            count1++;
            if (count1 % ALPHA == 0) count2++;
        }
    }
    encrypt[length] = '\0';
    printf("Encryption Complete!!\n%s\n", encrypt);
}

//Controls the starting position of the rotors. Set to 0 by default.
void startingPos(char rotor1[], char rotor2[], char rotor3[], int pos1, int pos2, int pos3) {
    for (int i = 0; i < pos1; i++) {
        rotate(rotor1);
    }
    for (int i = 0; i < pos2; i++) {
        rotate(rotor2);
    }
    for (int i = 0; i < pos3; i++) {
        rotate(rotor3);
    }
}

//Instanciates the rotors and positions them according to the starting positions given
void rotorCreate(char input[], int pos1, int pos2, int pos3, int count1, int count2) {
    char rotor1[ROTORLEN];
    char rotor2[ROTORLEN];
    char rotor3[ROTORLEN];
    strcpy(rotor1, "ekmflgdqvzntowyhxuspaibrcj");
    strcpy(rotor2, "ajdksiruxblhwtmcqgznpyfvoe");
    strcpy(rotor3, "bdfhjlcprtxvznyeiwgakmusqo");
    startingPos(rotor1, rotor2, rotor3, pos1, pos2, pos3);
    controller(input, rotor1, rotor2, rotor3, count1, count2);
}

void lower(char input[]) {
    int length = strlen(input);
    for (int i = 0; i < length; i++) {
        input[i] = tolower(input[i]);
    }
}

//All rotors have a starting position of 0.
int main(int n, char *args[n]) {
    if (n == 2) {
        //Edit these variables to change the starting positions of the rotors
        //pos1, pos2 and pos3 change the starting position of the rotors
        //count1 and count2 change the position of the notches in rotors I & II
        int pos1 = 0;
        int pos2 = 0;
        int pos3 = 0;
        int count1 = 1;
        int count2 = 1;
        lower(args[1]);
        rotorCreate(args[1], pos1, pos2, pos3, count1, count2);
        return 0;
    }
    else error();
}
