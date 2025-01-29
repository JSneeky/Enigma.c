#include <stdio.h>
#include <string.h>

//Standard Input: A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
//Plugboard:      O G V D Z Q B P L X K I N M A H F R T S U C W J Y E
//Rotor I:        E K M F L G D Q V Z N T O W Y H X U S P A I B R C J
//Rotor II:       A J D K S I R U X B L H W T M C Q G Z N P Y F V O E
//Rotor III:      B D F H J L C P R T X V Z N Y E I W G A K M U S Q O

//Reflector B:    AY BR CU DH EQ FS GL IP JX KN MO TZ VW 

//Plugboard -> Rotors -> Reflector -> Rotors -> Plugboard

char reflector(char ref) {
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    char output[] = "yruhqsldpxngokmiebfzcwvjat";
    for (int i = 0; i < 26; i++) {
        if (alphabet[i] == ref) return output[i];
        else; 
    } 
    return '/';
}

char rotor(char r, char rotor1[], char rotor2[]) {
    for (int i = 0; i < 26; i++) {
        if (rotor1[i] == r) return rotor2[i];
        else; 
    } 
    return '/';
}

void rotate(char rotor[]) {
    char store = rotor[25];
    char rotorStore[27];
    strcpy(rotorStore, rotor);
    for (int i = 0; i < 25; i++) {
        rotor[i + 1] = rotorStore[i];
    }
    rotor[0] = store;
}

char plugboard(char pb) {
    char input[] = "aobgqfstjxzehpilmncvdkruwy";
    char output[] = "oagbfqtsxjezphlinmvcdkruwy";
    for (int i = 0; i < 26; i++) {
        if (input[i] == pb) return output[i];
        else;
    }
    return '/';
}

void components(char input[], char rotor1[], char rotor2[], char rotor3[], char encrypt[], int i) {
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
    if (i % 26 == 0) rotate(rotor2);
    if (i % 676 == 0) rotate(rotor3);
    encrypt[i] = pb;
}

void controller(char input[], char rotor1[], char rotor2[], char rotor3[]) {
    int length = strlen(input);
    char encrypt[length + 1];
    for (int i = 0; i < length; i++) {
        if (input[i] == ' ') encrypt[i] = ' ';
        else {
            components(input, rotor1, rotor2, rotor3, encrypt, i);
        }
    }
    encrypt[length] = '\0';
    printf("Encryption Complete!!\n%s\n", encrypt);
}

int main(int n, char *args[n]) {
    char rotor1[27];
    char rotor2[27];
    char rotor3[27];
    strcpy(rotor1, "ekmflgdqvzntowyhxuspaibrcj");
    strcpy(rotor2, "ajdksiruxblhwtmcqgznpyfvoe");
    strcpy(rotor3, "bdfhjlcprtxvznyeiwgakmusqo");
    controller(args[1], rotor1, rotor2, rotor3);
    return 0;
}
