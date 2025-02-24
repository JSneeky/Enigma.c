The file enigma.c is an implementation of an Engima Machine in C. The program will encrypt any message passed to it using the I, II and III rotors, the B reflector and a randomly chosen plugboard configuration. The encryption implemented by each component is shown at the top of the file.

Input:
./enigma "INPUT"

Important Information:
> The INPUT can contain spaces.
> The machine can also decrypt any messages that have been encrypted with the same settings.
> The rotors I, II, III and reflector B are the actual rotors and reflectors that would have been used during the Second World War. The program can be reconfigured to use different rotor configurations.
> The plugboard settings that are set by default have been chosen at random and can be changed by editing the input and output strings within the plugboard function. 
> The starting positions of the rotors can be changed by editing the pos1, pos2 and pos3 values within the main to reflect the starting position.
