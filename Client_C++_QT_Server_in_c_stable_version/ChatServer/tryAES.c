#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//START OF AES_ENCRYPT

// The number of columns comprising a state in AES. This is a constant in AES. Value=4
#define Nb 4
#define MAX_CAPACITY 512
#define MAX_DIVIDE MAX_CAPACITY / 16

// The number of rounds in AES Cipher. It is simply initiated to zero. The actual value is recieved in the program.
int Nr=0;

// The number of 32 bit words in the key. It is simply initiated to zero. The actual value is recieved in the program.
int Nk=0;

// in - it is the array that holds the plain text to be encrypted.
// out - it is the array that holds the key for encryption.
// state - the array that holds the intermediate results during encryption.
unsigned char in[16], out[16], state[4][4];

// The array that stores the round keys.
unsigned char RoundKey[240];

// The Key input to the AES Program
unsigned char Key[32];

int getSBoxValueEncrypt(int num)
{
    int sbox[256] =   {
    //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, //0
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, //1
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, //2
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, //3
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, //4
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, //5
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, //6
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, //7
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, //8
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, //9
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, //A
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, //B
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, //C
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, //D
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, //E
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 }; //F
    return sbox[num];
}

// The round constant word array, Rcon[i], contains the values given by 
// x to th e power (i-1) being powers of x (x is denoted as {02}) in the field GF(28)
// Note that i starts at 1, not 0).
int RconEncrypt[255] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 
    0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 
    0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 
    0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 
    0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 
    0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 
    0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 
    0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 
    0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 
    0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 
    0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 
    0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 
    0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 
    0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 
    0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 
    0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb  };

// This function produces Nb(Nr+1) round keys. The round keys are used in each round to encrypt the states. 
void KeyExpansionEncrypt()
{
    int i,j;
    unsigned char temp[4],k;
    
    // The first round key is the key itself.
    for(i=0;i<Nk;i++)
    {
        RoundKey[i*4]=Key[i*4];
        RoundKey[i*4+1]=Key[i*4+1];
        RoundKey[i*4+2]=Key[i*4+2];
        RoundKey[i*4+3]=Key[i*4+3];
    }

    // All other round keys are found from the previous round keys.
    while (i < (Nb * (Nr+1)))
    {
                    for(j=0;j<4;j++)
                    {
                        temp[j]=RoundKey[(i-1) * 4 + j];
                    }
                    if (i % Nk == 0)
                    {
                        // This function rotates the 4 bytes in a word to the left once.
                        // [a0,a1,a2,a3] becomes [a1,a2,a3,a0]

                        // Function RotWord()
                        {
                            k = temp[0];
                            temp[0] = temp[1];
                            temp[1] = temp[2];
                            temp[2] = temp[3];
                            temp[3] = k;
                        }

                        // SubWord() is a function that takes a four-byte input word and 
                        // applies the S-box to each of the four bytes to produce an output word.

                        // Function Subword()
                        {
                            temp[0]=getSBoxValueEncrypt(temp[0]);
                            temp[1]=getSBoxValueEncrypt(temp[1]);
                            temp[2]=getSBoxValueEncrypt(temp[2]);
                            temp[3]=getSBoxValueEncrypt(temp[3]);
                        }

                        temp[0] =  temp[0] ^ RconEncrypt[i/Nk];
                    }
                    else if (Nk > 6 && i % Nk == 4)
                    {
                        // Function Subword()
                        {
                            temp[0]=getSBoxValueEncrypt(temp[0]);
                            temp[1]=getSBoxValueEncrypt(temp[1]);
                            temp[2]=getSBoxValueEncrypt(temp[2]);
                            temp[3]=getSBoxValueEncrypt(temp[3]);
                        }
                    }
                    RoundKey[i*4+0] = RoundKey[(i-Nk)*4+0] ^ temp[0];
                    RoundKey[i*4+1] = RoundKey[(i-Nk)*4+1] ^ temp[1];
                    RoundKey[i*4+2] = RoundKey[(i-Nk)*4+2] ^ temp[2];
                    RoundKey[i*4+3] = RoundKey[(i-Nk)*4+3] ^ temp[3];
                    i++;
    }
}

// This function adds the round key to state.
// The round key is added to the state by an XOR function.
void AddRoundKeyEncrypt(int round) 
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            state[j][i] ^= RoundKey[round * Nb * 4 + i * Nb + j];
        }
    }
}

// The SubBytes Function Substitutes the values in the
// state matrix with values in an S-box.
void SubBytesEncrypt()
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            state[i][j] = getSBoxValueEncrypt(state[i][j]);

        }
    }
}

// The ShiftRows() function shifts the rows in the state to the left.
// Each row is shifted with different offset.
// Offset = Row number. So the first row is not shifted.
void ShiftRowsEncrypt()
{
    unsigned char temp;

    // Rotate first row 1 columns to left   
    temp=state[1][0];
    state[1][0]=state[1][1];
    state[1][1]=state[1][2];
    state[1][2]=state[1][3];
    state[1][3]=temp;

    // Rotate second row 2 columns to left  
    temp=state[2][0];
    state[2][0]=state[2][2];
    state[2][2]=temp;

    temp=state[2][1];
    state[2][1]=state[2][3];
    state[2][3]=temp;

    // Rotate third row 3 columns to left
    temp=state[3][0];
    state[3][0]=state[3][3];
    state[3][3]=state[3][2];
    state[3][2]=state[3][1];
    state[3][1]=temp;
}

// xtime is a macro that finds the product of {02} and the argument to xtime modulo {1b}  
#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))

// MixColumns function mixes the columns of the state matrix
void MixColumnsEncrypt()
{
    int i;
    unsigned char Tmp,Tm,t;
    for(i=0;i<4;i++)
    {   
        t=state[0][i];
        Tmp = state[0][i] ^ state[1][i] ^ state[2][i] ^ state[3][i] ;
        Tm = state[0][i] ^ state[1][i] ; Tm = xtime(Tm); state[0][i] ^= Tm ^ Tmp ;
        Tm = state[1][i] ^ state[2][i] ; Tm = xtime(Tm); state[1][i] ^= Tm ^ Tmp ;
        Tm = state[2][i] ^ state[3][i] ; Tm = xtime(Tm); state[2][i] ^= Tm ^ Tmp ;
        Tm = state[3][i] ^ t ; Tm = xtime(Tm); state[3][i] ^= Tm ^ Tmp ;
    }
}

// Cipher is the main function that encrypts the PlainText.
void Cipher()
{
    int i,j,round=0;

    //Copy the input PlainText to state array.
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            state[j][i] = in[i*4 + j];
        }
    }

    // Add the First round key to the state before starting the rounds.
    AddRoundKeyEncrypt(0); 
    
    // There will be Nr rounds.
    // The first Nr-1 rounds are identical.
    // These Nr-1 rounds are executed in the loop below.
    for(round=1;round<Nr;round++)
    {
        SubBytesEncrypt();
        ShiftRowsEncrypt();
        MixColumnsEncrypt();
        AddRoundKeyEncrypt(round);
    }
    
    // The last round is given below.
    // The MixColumns function is not here in the last round.
    SubBytesEncrypt();
    ShiftRowsEncrypt();
    AddRoundKeyEncrypt(Nr);

    // The encryption process is over.
    // Copy the state array to output array.
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            out[i*4+j]=state[j][i];
        }
    }
}

//END OF AES_ENCRYPT

//START OF AES_DECRYPT

int getSBoxInvert(int num)
{
int rsbox[256] =
{ 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb
, 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb
, 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e
, 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25
, 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92
, 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84
, 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06
, 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b
, 0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73
, 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e
, 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b
, 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4
, 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f
, 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef
, 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61
, 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };

return rsbox[num];
}

int getSBoxValueDecrypt(int num)
{
    int sbox[256] =   {
    //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };
    return sbox[num];
}

// The round constant word array, Rcon[i], contains the values given by 
// x to th e power (i-1) being powers of x (x is denoted as {02}) in the field GF(2^8)
// Note that i starts at 1, not 0).
int RconDecrypt[255] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 
    0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 
    0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 
    0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 
    0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 
    0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 
    0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 
    0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 
    0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 
    0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 
    0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 
    0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 
    0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 
    0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 
    0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 
    0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb  };

// This function produces Nb(Nr+1) round keys. The round keys are used in each round to decrypt the states. 
void KeyExpansionDecrypt()
{
    int i,j;
    unsigned char temp[4],k;
    
    // The first round key is the key itself.
    for(i=0;i<Nk;i++)
    {
        RoundKey[i*4]=Key[i*4];
        RoundKey[i*4+1]=Key[i*4+1];
        RoundKey[i*4+2]=Key[i*4+2];
        RoundKey[i*4+3]=Key[i*4+3];
    }

    // All other round keys are found from the previous round keys.
    while (i < (Nb * (Nr+1)))
    {
        for(j=0;j<4;j++)
        {
            temp[j]=RoundKey[(i-1) * 4 + j];
        }
        if (i % Nk == 0)
        {
            // This function rotates the 4 bytes in a word to the left once.
            // [a0,a1,a2,a3] becomes [a1,a2,a3,a0]

            // Function RotWord()
            {
                k = temp[0];
                temp[0] = temp[1];
                temp[1] = temp[2];
                temp[2] = temp[3];
                temp[3] = k;
            }

            // SubWord() is a function that takes a four-byte input word and 
            // applies the S-box to each of the four bytes to produce an output word.

            // Function Subword()
            {
                temp[0]=getSBoxValueDecrypt(temp[0]);
                temp[1]=getSBoxValueDecrypt(temp[1]);
                temp[2]=getSBoxValueDecrypt(temp[2]);
                temp[3]=getSBoxValueDecrypt(temp[3]);
            }

            temp[0] =  temp[0] ^ RconDecrypt[i/Nk];
        }
        else if (Nk > 6 && i % Nk == 4)
        {
            // Function Subword()
            {
                temp[0]=getSBoxValueDecrypt(temp[0]);
                temp[1]=getSBoxValueDecrypt(temp[1]);
                temp[2]=getSBoxValueDecrypt(temp[2]);
                temp[3]=getSBoxValueDecrypt(temp[3]);
            }
        }
        RoundKey[i*4+0] = RoundKey[(i-Nk)*4+0] ^ temp[0];
        RoundKey[i*4+1] = RoundKey[(i-Nk)*4+1] ^ temp[1];
        RoundKey[i*4+2] = RoundKey[(i-Nk)*4+2] ^ temp[2];
        RoundKey[i*4+3] = RoundKey[(i-Nk)*4+3] ^ temp[3];
        i++;
    }
}

// This function adds the round key to state.
// The round key is added to the state by an XOR function.
void AddRoundKeyDecrypt(int round) 
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            state[j][i] ^= RoundKey[round * Nb * 4 + i * Nb + j];
        }
    }
}

// The SubBytes Function Substitutes the values in the
// state matrix with values in an S-box.
void InvSubBytes()
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            state[i][j] = getSBoxInvert(state[i][j]);

        }
    }
}

// The ShiftRows() function shifts the rows in the state to the left.
// Each row is shifted with different offset.
// Offset = Row number. So the first row is not shifted.
void InvShiftRows()
{
    unsigned char temp;

    // Rotate first row 1 columns to right  
    temp=state[1][3];
    state[1][3]=state[1][2];
    state[1][2]=state[1][1];
    state[1][1]=state[1][0];
    state[1][0]=temp;

    // Rotate second row 2 columns to right 
    temp=state[2][0];
    state[2][0]=state[2][2];
    state[2][2]=temp;

    temp=state[2][1];
    state[2][1]=state[2][3];
    state[2][3]=temp;

    // Rotate third row 3 columns to right
    temp=state[3][0];
    state[3][0]=state[3][1];
    state[3][1]=state[3][2];
    state[3][2]=state[3][3];
    state[3][3]=temp;
}

// Multiplty is a macro used to multiply numbers in the field GF(2^8)
#define Multiply(x,y) (((y & 1) * x) ^ ((y>>1 & 1) * xtime(x)) ^ ((y>>2 & 1) * xtime(xtime(x))) ^ ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^ ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))

// MixColumns function mixes the columns of the state matrix.
// The method used to multiply may be difficult to understand for the inexperienced.
// Please use the references to gain more information.
void InvMixColumns()
{
    int i;
    unsigned char a,b,c,d;
    for(i=0;i<4;i++)
    {   
    
        a = state[0][i];
        b = state[1][i];
        c = state[2][i];
        d = state[3][i];

        
        state[0][i] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d) ^ Multiply(d, 0x09);
        state[1][i] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b) ^ Multiply(d, 0x0d);
        state[2][i] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e) ^ Multiply(d, 0x0b);
        state[3][i] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09) ^ Multiply(d, 0x0e);
    }
}

// InvCipher is the main function that decrypts the CipherText.
void InvCipher()
{
    int i,j,round=0;

    //Copy the input CipherText to state array.
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            state[j][i] = in[i*4 + j];
        }
    }

    // Add the First round key to the state before starting the rounds.
    AddRoundKeyDecrypt(Nr); 

    // There will be Nr rounds.
    // The first Nr-1 rounds are identical.
    // These Nr-1 rounds are executed in the loop below.
    for(round=Nr-1;round>0;round--)
    {
        InvShiftRows();
        InvSubBytes();
        AddRoundKeyDecrypt(round);
        InvMixColumns();
    }
    
    // The last round is given below.
    // The MixColumns function is not here in the last round.
    InvShiftRows();
    InvSubBytes();
    AddRoundKeyDecrypt(0);

    // The decryption process is over.
    // Copy the state array to output array.
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            out[i*4+j]=state[j][i];
        }
    }
}

//END OF AES_DECRYPT

char hexDigit(unsigned n)
{
    if (n < 10) {
        return n + '0';
    } else {
        return (n - 10) + 'A';
    }
}

void charToHex(char c, char hex[2])
{
    hex[0] = hexDigit(c / 0x10);
    hex[1] = hexDigit(c % 0x10);
    //hex[2] = '\0';
}

char hexToAscii(char first, char second)
{
    char hex[5], *stop;
    hex[0] = '0';
    hex[1] = 'x';
    hex[2] = first;
    hex[3] = second;
    hex[4] = 0;
    return strtol(hex, &stop, 16);
}

void uncharToChar(char *dst, unsigned char *src,size_t src_len)
{
        while (src_len--)
            dst += sprintf(dst,"%02x",*src++);
        *dst = '\0';
}

void convertToReal(char *dest, char *source)
{
    int i;
    int count = 0;
    for(i = 0; i < strlen(source)/2; i++)
    {
        if(source[count] == '0' && source[count+1] == '0')
        {
            dest[i] = 0;
        }
        else
        {
            dest[i] = hexToAscii(source[count], source[count+1]);
        }
  
        count += 2;
    }
}


void containHex(char dest[MAX_CAPACITY][1], char *source)
{
    int i;
    int count = 0;
    for(i = 0; i < strlen(source)/2; i++)
    {
        dest[i][0] = hexToAscii(source[count], source[count+1]);
        count += 2;
    }
}


void xor_str(char *A, char *B, char *res) {
    int i = 0;
    int j;
    int a, b, x;

    /*
    if(strlen(A) < strlen(B))
    {
        for(j = strlen(A) - 1; j < strlen(B); j++)
        {
            A[j] = '0';
            printf("A\n");
        }
    }
    else
    if(strlen(A) > strlen(B))
    {
        for(j = strlen(B) - 1; j < strlen(A); j++)
        {
            B[j] = '0';
            printf("B\n");
        }
    }
    */

    while (A[i] != 0) {//kalau belum null
        if (A[i] >= '0' && A[i] <= '9') {
            a = A[i] - '0';
        }
        else if (A[i] >= 'a' && A[i] <= 'z'){
            a = A[i] - 'a' + 10;
        }
        if (B[i] >= '0' && B[i] <= '9') {
            b = B[i] - '0';
        }
        else if (B[i] >= 'a' && B[i] <= 'z'){
            b = B[i] - 'a' + 10;
        }
        x = a ^ b;
        if (x < 10) {
            res[i] = '0' + x;
        }
        else {
            res[i] = 'a' + x - 10;
        }
        i++;
    }
    res[i] = 0;
}



char *xor(char *source1, int src_sz, char *source2) {

    int i, j = 0;
    int k_len = strlen(source2);
    char *result = calloc(src_sz+1, sizeof(char));

    for (i = 0; i < src_sz; i++) {
        result[i] = source1[i] ^ source2[j];
        j++;
        j = j > k_len ? 0 : j;
        //printf("perulangan -> %d\nlength -> %d\nkarakter -> %c\n", i, src_sz, result[i]);
    }
    return result;
}

void char2hex(char* A, char *Hex) {
    int i=0;
    int j=0;
    int t;
    char temp[32];

    while(A[i] != '\0') {

        printf("%d %lu\n", i, strlen(A));
        
        t = A[i] >> 4;
        if (t < 10) {
            temp[j] = '0' + t;
        }
        else {
            temp[j] = 'a' + t - 10;
        }
        j++;
        t = A[i] % 16;
        if (t < 10) {
            temp[j] = '0' + t;
        }
        else {
            temp[j] = 'a' + t - 10;
        }
        j++;
        i++;
    }

    for(i = 0; i < (int)strlen(A)*2; i++)
    {
        Hex[i] = temp[i];
    } 

    //printf("%s\n", Hex);
}
/*
char* stringToHex(char* input, int size)
{
    static const char* const lut = "0123456789abcdef";
    size_t len = size*2;

    //printf("this-> %d\n", size);

    char output[100];
    int count = 0;

    for (size_t i = 0; i < size; i++)
    {
        const unsigned char c = input[i];
        output[count] = lut[c >> 4];
        count++;
        output[count] = lut[c & 15];
        count++;
    }
    //printf("this-> %s\n", output);
    return output;
}
*/
//done

void divideAscii(char dest[MAX_CAPACITY][17], char *source)
{
    int i, j, part;
    part = (strlen(source) - 1) / 16;
    //printf("part : %d\nlength : %d\n", part, strlen(source));
    for(i = 0; i <= part; i++)
    {
        memset(&dest[i][0], 0, sizeof(dest[i]));
        for(j = i * 16; j < ((i+1) * 16); j++)
        {
            if(j >= strlen(source))
            {
                dest[i][j] = '\0';
                break;
            }
            dest[i][j%16] = source[j];
            //printf("karakter : %c\n", source[j]);
            //printf("%d -> %d\n", j, strlen(dest[i]));

        }
    }
    //printf("%d\n", strlen(dest[0]));
}

int main()
{
    char ascii[MAX_CAPACITY];
    char convert[MAX_CAPACITY] = "";
    char deconvert[MAX_CAPACITY] = "";
    char real[MAX_CAPACITY] = "";
    int b, i, blocksIV, blocksAscii;

    /*
    while(Nr!=128 && Nr!=192 && Nr!=256)
    {
        printf("Enter the length of Key(128, 192 or 256 only): ");
        scanf("%d", &Nr);
    }
    */
    // Calculate Nk and Nr from the recieved value.
    int AES_MODE = 128;
    Nk = AES_MODE / 32;
    Nr = Nk + 6;
    
    printf("NK = %d, NR = %d\n", Nk, Nr);

    char IV[MAX_CAPACITY] = "0123456789abcdef";


    // The array tempkey stores the key.
    unsigned char tempkey[32] = {0x00  ,0x01  ,0x02  ,0x03  ,0x04  ,0x05  ,0x06  ,0x07  ,0x08  ,0x09  ,0x0a  ,0x0b  ,0x0c  ,0x0d  ,0x0e  ,0x0f};
    //unsigned char temp2[32]= {0x00  ,0x11  ,0x22  ,0x33  ,0x44  ,0x55  ,0x66  ,0x77  ,0x88  ,0x99  ,0xaa  ,0xbb  ,0xcc  ,0xdd  ,0xee  ,0xff};
    
    // Copy the Key and PlainText
    for(i=0;i<Nk*4;i++)
    {
        Key[i]=tempkey[i];
        //in[i]=temp2[i];
    }


    printf("Masukkan plaintext : ");
    //getchar();
    gets(ascii);

    blocksAscii = ((strlen(ascii) - 1) / 16);

    char partAscii[MAX_CAPACITY][17];
    divideAscii(partAscii, ascii);

    char hasilxorencrypt[MAX_CAPACITY][33];
    char hasilxordecrypt[MAX_CAPACITY][33];

    for (int ba = 0; ba <= blocksAscii; ba++)
    {
        if(ba == 0)
        {
            blocksIV = ((strlen(IV) - 1) / 16);
            //printf("jumlah : %d\n", blocksIV);
        }
        else
        {
            blocksIV = ((strlen(convert) - 1) / 16);
        }

        for(b = 0; b <= blocksIV; b++)
        {
            for(i=0;i<Nb*4;i++)
            {
                if(ba == 0)
                {
                    if((i + (b * 16) < strlen(IV)))
                    {
                        in[i] = (unsigned char)IV[ (i + (b * 16) ) ];
                    }
                    else
                    {
                        in[i] = 0x00;
                    }
                }
                else
                {
                    if((i + (b * 16) < strlen(convert)))
                    {
                        in[i] = (unsigned char)convert[ (i + (b * 16) ) ];
                    }
                    else
                    {
                        in[i] = 0x00;
                    }
                }
            }

            printf("\n");

            printf("hexadecimal in in: ");

            for(i=0;i<Nb*4;i++)
            {
                printf("%02x ", in[i]);
            }
            printf("\n");

            // The KeyExpansion routine must be called before encryption.
            KeyExpansionEncrypt();

            // The next function call encrypts the PlainText with the Key using AES algorithm.
            Cipher();

            // Output the encrypted text.
            printf("\nText after encryption:\n");

            printf("Encryption : ");

            for(i=0;i<Nb*4;i++)
            {
                printf("%02x ", out[i]);
            }
            printf("\n\n");

            char tempconvert[16];
            uncharToChar(tempconvert, out, sizeof(out));

            memset(&convert[0], 0, sizeof(convert));
            strcat(convert, tempconvert);

            memset(&in[0], 0, sizeof(in));
            memset(&out[0], 0, sizeof(out));
        }

        char plainInHex[33];
        char xorResult[MAX_CAPACITY];
        char convSelected[MAX_CAPACITY];

        memset(&convSelected[0], 0, sizeof(convSelected));
        strncpy(convSelected, convert, strlen(partAscii[ba])*2);
        char2hex(partAscii[ba], plainInHex);
        xor_str(plainInHex, convSelected, xorResult);
                
        strcpy(hasilxorencrypt[ba], xorResult);
        
        printf("panjang convert %lu -> %s\n", strlen(convert), convert);
        printf("partAscii -> %s\npanjang partAscii -> %lu\nkali 2 -> %lu\n", partAscii[ba], strlen(partAscii[ba]), strlen(partAscii[ba])*2);
        printf("panjang hexaAscii %lu -> %s\n", strlen(plainInHex), plainInHex);
        printf("panjang convertSelected %lu -> %s\n", strlen(convSelected), convSelected);
        printf("panjang hasilxorencrypt %lu -> %s\n", strlen(hasilxorencrypt[ba]), hasilxorencrypt[ba]);
        
        char tempConvResult[MAX_CAPACITY];
        convertToReal(tempConvResult, convSelected);
        memset(&convert[0], 0, sizeof(convert));
        strcpy(convert, tempConvResult);
        memset(&plainInHex[0], 0, sizeof(plainInHex));
        memset(&xorResult[0], 0, sizeof(xorResult));
    }

    //Decryption 

    for (int ba = 0; ba <= blocksAscii; ba++)
    {
        if(ba == 0)
        {
            blocksIV = ((strlen(IV) - 1) / 16);
            //printf("jumlah : %d\n", blocks);
        }
        else
        {
            blocksIV = ((strlen(convert) - 1) / 16);
        }

        for(b = 0; b <= blocksIV; b++)
        {
            for(i=0;i<Nb*4;i++)
            {
                if(ba == 0)
                {
                    if((i + (b * 16) < strlen(IV)))
                    {
                        in[i] = (unsigned char)IV[ (i + (b * 16) ) ];
                    }
                    else
                    {
                        in[i] = 0x00;
                    }
                }
                else
                {
                    if((i + (b * 16) < strlen(convert)))
                    {
                        in[i] = (unsigned char)convert[ (i + (b * 16) ) ];
                    }
                    else
                    {
                        in[i] = 0x00;
                    }
                }
            }

            printf("\n");

            printf("hexadecimal in in: ");

            for(i=0;i<Nb*4;i++)
            {
                printf("%02x ", in[i]);
            }
            printf("\n");

            // The KeyExpansion routine must be called before encryption.
            KeyExpansionEncrypt();

            // The next function call encrypts the PlainText with the Key using AES algorithm.
            Cipher();

            // Output the encrypted text.
            printf("\nText after encryption:\n");

            printf("Encryption : ");

            for(i=0;i<Nb*4;i++)
            {
                printf("%02x ", out[i]);
            }
            printf("\n\n");

            char tempconvert[16];
            uncharToChar(tempconvert, out, sizeof(out));

            memset(&convert[0], 0, sizeof(convert));
            strcat(convert, tempconvert);

            memset(&in[0], 0, sizeof(in));
            memset(&out[0], 0, sizeof(out));
        }

        char tempRes[MAX_CAPACITY];
        char convSelected2[MAX_CAPACITY];

        memset(&convSelected2[0], 0, sizeof(convSelected2));
        strncpy(convSelected2, convert, strlen(hasilxorencrypt[ba]));
        xor_str(hasilxorencrypt[ba], convSelected2, tempRes);

        strcpy(hasilxordecrypt[ba], tempRes);
        printf("Encrypted message dengan panjang %lu -> %s\n", strlen(hasilxorencrypt[ba]), hasilxorencrypt[ba]);
        printf("panjang convertSelected2 %lu -> %s\n", strlen(convSelected2), convSelected2);
        printf("hasil xor ke %d -> %s\n", ba, hasilxordecrypt[ba]);

        char tempConvResult[MAX_CAPACITY];
        convertToReal(tempConvResult, convSelected2);
        memset(&convert[0], 0, sizeof(convert));
        strcpy(convert, tempConvResult);
        memset(&tempRes[0], 0, sizeof(tempRes));
        
        convertToReal(real, hasilxordecrypt[ba]);
        printf("Plaintext that has been decrypted : ");
        puts(real);
        memset(&real[0], 0, sizeof(real));
        
    }

    /*
    char convertToAscii[MAX_CAPACITY][1];
    containHex(convertToAscii, convert);

    printf("contain hex -> ");
    for(i = 0; i < strlen(convert); i++)
    {
        printf("no %d -> %02x ", i, convertToAscii[i][0]);
        printf("\n");
    }
    printf("\n");
    

    char bug;
    if(blocks > 0)
    {
        bug = convertToAscii[16][0];
        //printf("bug -> %02x\n", bug);
    }

    for(b = 0; b <= blocks; b++)
    {
        for(i=0;i<Nb*4;i++)
        {
            if((i + (b * 16) < strlen(convert)))
            {
                if((i + (b * 16)) == 16)
                {
                    in[i] = (unsigned char) bug;
                    //printf("bug %d -> %02x ", (i + (b * 16)), bug);
                }
                else
                {
                    in[i] = (unsigned char)convertToAscii[ (i + (b * 16) ) ][0];
                    //printf("no %d -> %02x ", (i + (b * 16)), convertToAscii[ (i + (b * 16) ) ][0]);
                }
            }
            else
            {
                in[i] = 0x00;
            }
        }

        printf("\nhexadecimal in in: ");

        for(i=0;i<Nb*4;i++)
        {
            printf("%02x ", in[i]);
        }
        printf("\n");

        KeyExpansionDecrypt();

        InvCipher();

        printf("\nText after decryption:\n");

        printf("Decryption : ");

        for(i=0;i<Nb*4;i++)
        {
            printf("%02x ", out[i]);
        }
        printf("\n\n");

        char tempdeconvert[16];
        uncharToChar(tempdeconvert, out, sizeof(out));

        strcat(deconvert, tempdeconvert);

        memset(&in[0], 0, sizeof(in));
        memset(&out[0], 0, sizeof(out));
    }

    convertToReal(real, deconvert);
    printf("Plaintext that has been decrypted : ");
    puts(real);
    */
   
    return 0;
}
