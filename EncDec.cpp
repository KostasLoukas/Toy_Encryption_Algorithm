#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(void)
{


	//unsigned char sbox[16] = { '6', '4','c','5','0','7','2','e','1','f','3','d','8','a','9','b'};
	unsigned char key[5][4];	//setting hex values for key
	key[0][0] = 'a';	//a
	key[0][1] = '1';	//1
	key[0][2] = 'e';	//e
	key[0][3] = '9';	//9

	int i = 0, j = 0, k = 0;
	long l = 0, max = 0;
	char ans;
	int ans2;


	srand(time(NULL));
	


	//Creating the round keys and printing them on the screen
	//Every char is 1 byte!
	//key[0][1,2,3,4] = "a1e9"
	//Key Generation
	unsigned char leftpart1, rightpart1, leftpart2, rightpart2, leftpart3, rightpart3, leftpart4, rightpart4;

	for (i = 1; i < 4; i++)
	{
		//cutting the first and last four bits of the first character
		leftpart1 = key[i - 1][0] & 0xF0;
		leftpart1 = leftpart1 >> 4;
		rightpart1 = key[i - 1][0] & 0x0F;

		//cutting the first and last four bits of the second character
		leftpart2 = key[i - 1][1] & 0xF0;
		leftpart2 = leftpart2 >> 4;
		rightpart2 = key[i - 1][1] & 0x0F;

		//cutting the first and last four bits of the third character
		leftpart3 = key[i - 1][2] & 0xF0;
		leftpart3 = leftpart3 >> 4;
		rightpart3 = key[i - 1][2] & 0x0F;

		//cutting the first and last four bits of the fourth character
		leftpart4 = key[i - 1][3] & 0xF0;
		leftpart4 = leftpart4 >> 4;
		rightpart4 = key[i - 1][3] & 0x0F;


		//we do the appropriate shifts
		leftpart1 = leftpart1 << 2;
		rightpart1 = rightpart1 << 2;

		leftpart2 = leftpart2 << 2;
		rightpart2 = rightpart2 << 2;

		leftpart3 = leftpart3 << 2;
		rightpart3 = rightpart3 << 2;

		leftpart4 = leftpart4 << 2;
		rightpart4 = rightpart4 << 2;


		//we do the relocation
		unsigned char tmp = rightpart1;
		rightpart1 = leftpart2;
		leftpart2 = tmp;

		tmp = rightpart3;
		rightpart3 = leftpart4;
		leftpart4 = tmp;

		//we save the new key
		leftpart1 = leftpart1 << 4;
		key[i][0] = leftpart1 | rightpart1;

		leftpart2 = leftpart2 << 4;
		key[i][1] = leftpart2 | rightpart2;

		leftpart3 = leftpart3 << 4;
		key[i][2] = leftpart3 | rightpart3;

		leftpart4 = leftpart4 << 4;
		key[i][3] = leftpart4 | rightpart4;

	}


	//cutting the first and last four bits of the first character
	leftpart1 = key[3][0] & 0xF0;
	leftpart1 = leftpart1 >> 4;
	rightpart1 = key[3][0] & 0x0F;

	//cutting the first and last four bits of the second character
	leftpart2 = key[3][1] & 0xF0;
	leftpart2 = leftpart2 >> 4;
	rightpart2 = key[3][1] & 0x0F;

	//cutting the first and last four bits of the third character
	leftpart3 = key[3][2] & 0xF0;
	leftpart3 = leftpart3 >> 4;
	rightpart3 = key[3][2] & 0x0F;

	//cutting the first and last four bits of the fourth character
	leftpart4 = key[3][3] & 0xF0;
	leftpart4 = leftpart4 >> 4;
	rightpart4 = key[3][3] & 0x0F;


	//we do the appropriate shifts
	leftpart1 = leftpart1 << 2;
	rightpart1 = rightpart1 << 2;

	leftpart2 = leftpart2 << 2;
	rightpart2 = rightpart2 << 2;

	leftpart3 = leftpart3 << 2;
	rightpart3 = rightpart3 << 2;

	leftpart4 = leftpart4 << 2;
	rightpart4 = rightpart4 << 2;


	//we save the new key
	leftpart1 = leftpart1 << 4;
	key[4][0] = leftpart1 | rightpart1;

	leftpart2 = leftpart2 << 4;
	key[4][1] = leftpart2 | rightpart2;

	leftpart3 = leftpart3 << 4;
	key[4][2] = leftpart3 | rightpart3;

	leftpart4 = leftpart4 << 4;
	key[4][3] = leftpart4 | rightpart4;



	//We print the keys
	for (i = 0; i < 5; i++)
	{
		printf("Key%d: ", i);
		for (j = 0; j < 4; j++)
		{
			printf("%c", key[i][j]);
		}
		printf("\n");
	}


	unsigned char in[5]; //our message to be encrypted (separated in four characters) (+1 in size for the null character)
	unsigned char out[5]; //output of encryption/input of decryption (+1 in size for the null character)
	in[4] = '\0';
	out[4] = '\0';

	unsigned char leftpart[4]; //left four bits of each character
	unsigned char rightpart[4]; //right four bits of each character
	unsigned char leftpartbits[4][4];
	unsigned char rightpartbits[4][4];


	printf("Do you want to run the single message Encryption-Decryption or the multiple messages one? (insert '1' for single and '2' for multiple)\n");
	scanf("%d", &ans2);
	

	
	if (ans2 == 1)
	{
		max = 1;
		in[0] = 'f'; //can be customized
		in[1] = 'a';
		in[2] = 'd';
		in[3] = '3';
	}
	else if (ans2 == 2)
	{
		max = 67108864 * 2.5;  //almost 1.000.000.000 bytes for that number of loops
	}
	else
	{
		printf("INVALID ANSWER!\n");
		return 1;
	}
	


	


	printf("Encrypting and Decrypting all generated messages. Please wait...\n");


	double time_spent = 0.0;
	clock_t begin = clock();

	
	for (l = 0 ; l < max ; l++)
	{
		
		if (max != 1)  //generating the message (only capital letters are generated here for all the messages)
		{
			in[0] = (char)(65 + rand() % 26);
			in[1] = (char)(65 + rand() % 26);
			in[2] = (char)(65 + rand() % 26);
			in[3] = (char)(65 + rand() % 26);

		}

		/*
		//We print the input
		printf("Encryption input message: ");
		for (i = 0 ; i<4 ; i++)
		{
			printf("%c", in[i]);
		}
		printf("\n");
		*/
		
		
		//Encrypting

		//We do the XOR
		out[0] = in[0] ^ key[0][0];
		out[1] = in[1] ^ key[0][1];
		out[2] = in[2] ^ key[0][2];
		out[3] = in[3] ^ key[0][3];

		for (k = 0; k < 3; k++)
		{


			//cutting the first and last four bits of the first character
			leftpart[0] = out[0] & 0xF0;
			leftpart[0] = leftpart[0] >> 4;
			rightpart[0] = out[0] & 0x0F;

			//cutting the first and last four bits of the second character
			leftpart[1] = out[1] & 0xF0;
			leftpart[1] = leftpart[1] >> 4;
			rightpart[1] = out[1] & 0x0F;

			//cutting the first and last four bits of the third character
			leftpart[2] = out[2] & 0xF0;
			leftpart[2] = leftpart[2] >> 4;
			rightpart[2] = out[2] & 0x0F;

			//cutting the first and last four bits of the fourth character
			leftpart[3] = out[3] & 0xF0;
			leftpart[3] = leftpart[3] >> 4;
			rightpart[3] = out[3] & 0x0F;

			for (i = 0; i < 4; i++)
			{
				//permutating the left parts
				if (leftpart[i] == 0x00)
				{
					leftpart[i] = 0x06;
				}
				else if (leftpart[i] == 0x01)
				{
					leftpart[i] = 0x04;
				}
				else if (leftpart[i] == 0x02)
				{
					leftpart[i] = 0x0C;
				}
				else if (leftpart[i] == 0x03)
				{
					leftpart[i] = 0x05;
				}
				else if (leftpart[i] == 0x04)
				{
					leftpart[i] = 0x00;
				}
				else if (leftpart[i] == 0x05)
				{
					leftpart[i] = 0x07;
				}
				else if (leftpart[i] == 0x06)
				{
					leftpart[i] = 0x02;
				}
				else if (leftpart[i] == 0x07)
				{
					leftpart[i] = 0x0E;
				}
				else if (leftpart[i] == 0x08)
				{
					leftpart[i] = 0x01;
				}
				else if (leftpart[i] == 0x09)
				{
					leftpart[i] = 0x0F;
				}
				else if (leftpart[i] == 0x0A)
				{
					leftpart[i] = 0x03;
				}
				else if (leftpart[i] == 0x0B)
				{
					leftpart[i] = 0x0D;
				}
				else if (leftpart[i] == 0x0C)
				{
					leftpart[i] = 0x08;
				}
				else if (leftpart[i] == 0x0D)
				{
					leftpart[i] = 0x0A;
				}
				else if (leftpart[i] == 0x0E)
				{
					leftpart[i] = 0x09;
				}
				else if (leftpart[i] == 0x0F)
				{
					leftpart[i] = 0x0B;
				}

				//permutating the right parts
				if (rightpart[i] == 0x00)
				{
					rightpart[i] = 0x06;
				}
				else if (rightpart[i] == 0x01)
				{
					rightpart[i] = 0x04;
				}
				else if (rightpart[i] == 0x02)
				{
					rightpart[i] = 0x0C;
				}
				else if (rightpart[i] == 0x03)
				{
					rightpart[i] = 0x05;
				}
				else if (rightpart[i] == 0x04)
				{
					rightpart[i] = 0x00;
				}
				else if (rightpart[i] == 0x05)
				{
					rightpart[i] = 0x07;
				}
				else if (rightpart[i] == 0x06)
				{
					rightpart[i] = 0x02;
				}
				else if (rightpart[i] == 0x07)
				{
					rightpart[i] = 0x0E;
				}
				else if (rightpart[i] == 0x08)
				{
					rightpart[i] = 0x01;
				}
				else if (rightpart[i] == 0x09)
				{
					rightpart[i] = 0x0F;
				}
				else if (rightpart[i] == 0x0A)
				{
					rightpart[i] = 0x03;
				}
				else if (rightpart[i] == 0x0B)
				{
					rightpart[i] = 0x0D;
				}
				else if (rightpart[i] == 0x0C)
				{
					rightpart[i] = 0x08;
				}
				else if (rightpart[i] == 0x0D)
				{
					rightpart[i] = 0x0A;
				}
				else if (rightpart[i] == 0x0E)
				{
					rightpart[i] = 0x09;
				}
				else if (rightpart[i] == 0x0F)
				{
					rightpart[i] = 0x0B;
				}

			}

			//we take the bits of each part
			for (i = 0; i < 4; i++)
			{
				//we take the first (leftmost) bit
				leftpartbits[i][0] = (leftpart[i] & 0x08) >> 3;
				rightpartbits[i][0] = (rightpart[i] & 0x08) >> 3;

				//we take the second bit
				leftpartbits[i][1] = (leftpart[i] & 0x04) >> 2;
				rightpartbits[i][1] = (rightpart[i] & 0x04) >> 2;

				//we take the third bit
				leftpartbits[i][2] = (leftpart[i] & 0x02) >> 1;
				rightpartbits[i][2] = (rightpart[i] & 0x02) >> 1;

				//we take the fourth (rightmost) bit
				leftpartbits[i][3] = (leftpart[i] & 0x01);
				rightpartbits[i][3] = (rightpart[i] & 0x01);
			}


			unsigned char t[12];

			//we do the relocation between the bits of the two letters (first and second)
			t[0] = leftpartbits[0][1];
			leftpartbits[0][1] = rightpartbits[0][0];
			t[1] = leftpartbits[0][2];
			leftpartbits[0][2] = leftpartbits[1][0];
			t[2] = leftpartbits[0][3];
			leftpartbits[0][3] = rightpartbits[1][0];
			rightpartbits[0][0] = t[0];
			t[3] = rightpartbits[0][2];
			rightpartbits[0][2] = leftpartbits[1][1];
			t[4] = rightpartbits[0][3];
			rightpartbits[0][3] = rightpartbits[1][1];

			leftpartbits[1][0] = t[1];
			leftpartbits[1][1] = t[3];
			t[5] = leftpartbits[1][3];
			leftpartbits[1][3] = rightpartbits[1][2];
			rightpartbits[1][0] = t[2];
			rightpartbits[1][1] = t[4];
			rightpartbits[1][2] = t[5];


			//we do the relocation between the bits of the two letters (third and fourth)
			t[6] = leftpartbits[2][1];
			leftpartbits[2][1] = rightpartbits[2][0];
			t[7] = leftpartbits[2][2];
			leftpartbits[2][2] = leftpartbits[3][0];
			t[8] = leftpartbits[2][3];
			leftpartbits[2][3] = rightpartbits[3][0];
			rightpartbits[2][0] = t[6];
			t[9] = rightpartbits[2][2];
			rightpartbits[2][2] = leftpartbits[3][1];
			t[10] = rightpartbits[2][3];
			rightpartbits[2][3] = rightpartbits[3][1];

			leftpartbits[3][0] = t[7];
			leftpartbits[3][1] = t[9];
			t[11] = leftpartbits[3][3];
			leftpartbits[3][3] = rightpartbits[3][2];
			rightpartbits[3][0] = t[8];
			rightpartbits[3][1] = t[10];
			rightpartbits[3][2] = t[11];

			

			//we unite the bits of each part
			for (j = 0; j < 4; j++)
			{
				//we take the first left and right parts' bits
				leftpart[j] = (leftpartbits[j][0] << 3) | (leftpartbits[j][1] << 2) | (leftpartbits[j][2] << 1) | (leftpartbits[j][3]);
				rightpart[j] = (rightpartbits[j][0] << 3) | (rightpartbits[j][1] << 2) | (rightpartbits[j][2] << 1) | (rightpartbits[j][3]);

				//we do the XOR with the key
				out[j] = ((leftpart[j] << 4) | rightpart[j]) ^ key[k + 1][j];

			}

		}


		//cutting the first and last four bits of the first character
		leftpart[0] = out[0] & 0xF0;
		leftpart[0] = leftpart[0] >> 4;
		rightpart[0] = out[0] & 0x0F;

		//cutting the first and last four bits of the second character
		leftpart[1] = out[1] & 0xF0;
		leftpart[1] = leftpart[1] >> 4;
		rightpart[1] = out[1] & 0x0F;

		//cutting the first and last four bits of the third character
		leftpart[2] = out[2] & 0xF0;
		leftpart[2] = leftpart[2] >> 4;
		rightpart[2] = out[2] & 0x0F;

		//cutting the first and last four bits of the fourth character
		leftpart[3] = out[3] & 0xF0;
		leftpart[3] = leftpart[3] >> 4;
		rightpart[3] = out[3] & 0x0F;

		for (i = 0; i < 4; i++)
		{
			//permutating the left parts
			if (leftpart[i] == 0x00)
			{
				leftpart[i] = 0x06;
			}
			else if (leftpart[i] == 0x01)
			{
				leftpart[i] = 0x04;
			}
			else if (leftpart[i] == 0x02)
			{
				leftpart[i] = 0x0C;
			}
			else if (leftpart[i] == 0x03)
			{
				leftpart[i] = 0x05;
			}
			else if (leftpart[i] == 0x04)
			{
				leftpart[i] = 0x00;
			}
			else if (leftpart[i] == 0x05)
			{
				leftpart[i] = 0x07;
			}
			else if (leftpart[i] == 0x06)
			{
				leftpart[i] = 0x02;
			}
			else if (leftpart[i] == 0x07)
			{
				leftpart[i] = 0x0E;
			}
			else if (leftpart[i] == 0x08)
			{
				leftpart[i] = 0x01;
			}
			else if (leftpart[i] == 0x09)
			{
				leftpart[i] = 0x0F;
			}
			else if (leftpart[i] == 0x0A)
			{
				leftpart[i] = 0x03;
			}
			else if (leftpart[i] == 0x0B)
			{
				leftpart[i] = 0x0D;
			}
			else if (leftpart[i] == 0x0C)
			{
				leftpart[i] = 0x08;
			}
			else if (leftpart[i] == 0x0D)
			{
				leftpart[i] = 0x0A;
			}
			else if (leftpart[i] == 0x0E)
			{
				leftpart[i] = 0x09;
			}
			else if (leftpart[i] == 0x0F)
			{
				leftpart[i] = 0x0B;
			}

			//permutating the right parts
			if (rightpart[i] == 0x00)
			{
				rightpart[i] = 0x06;
			}
			else if (rightpart[i] == 0x01)
			{
				rightpart[i] = 0x04;
			}
			else if (rightpart[i] == 0x02)
			{
				rightpart[i] = 0x0C;
			}
			else if (rightpart[i] == 0x03)
			{
				rightpart[i] = 0x05;
			}
			else if (rightpart[i] == 0x04)
			{
				rightpart[i] = 0x00;
			}
			else if (rightpart[i] == 0x05)
			{
				rightpart[i] = 0x07;
			}
			else if (rightpart[i] == 0x06)
			{
				rightpart[i] = 0x02;
			}
			else if (rightpart[i] == 0x07)
			{
				rightpart[i] = 0x0E;
			}
			else if (rightpart[i] == 0x08)
			{
				rightpart[i] = 0x01;
			}
			else if (rightpart[i] == 0x09)
			{
				rightpart[i] = 0x0F;
			}
			else if (rightpart[i] == 0x0A)
			{
				rightpart[i] = 0x03;
			}
			else if (rightpart[i] == 0x0B)
			{
				rightpart[i] = 0x0D;
			}
			else if (rightpart[i] == 0x0C)
			{
				rightpart[i] = 0x08;
			}
			else if (rightpart[i] == 0x0D)
			{
				rightpart[i] = 0x0A;
			}
			else if (rightpart[i] == 0x0E)
			{
				rightpart[i] = 0x09;
			}
			else if (rightpart[i] == 0x0F)
			{
				rightpart[i] = 0x0B;
			}
		}

		for (j = 0; j < 4; j++)
		{
			out[j] = ((leftpart[j] << 4) | rightpart[j]) ^ key[4][j];

		}
		

		/*
		//We print the encryption output/decryption input
		printf("Encryption output/Decryption input message: ");
		for (i = 0; i < 4; i++)
		{
			printf("%c", out[i]);
		}
		printf("\n");
		*/

		
		
		
		
		//Decrypting
		
		//We do the XOR
		in[0] = out[0] ^ key[4][0];
		in[1] = out[1] ^ key[4][1];
		in[2] = out[2] ^ key[4][2];
		in[3] = out[3] ^ key[4][3];

		//cutting the first and last four bits of the first character
		leftpart[0] = in[0] & 0xF0;
		leftpart[0] = leftpart[0] >> 4;
		rightpart[0] = in[0] & 0x0F;

		//cutting the first and last four bits of the second character
		leftpart[1] = in[1] & 0xF0;
		leftpart[1] = leftpart[1] >> 4;
		rightpart[1] = in[1] & 0x0F;

		//cutting the first and last four bits of the third character
		leftpart[2] = in[2] & 0xF0;
		leftpart[2] = leftpart[2] >> 4;
		rightpart[2] = in[2] & 0x0F;

		//cutting the first and last four bits of the fourth character
		leftpart[3] = in[3] & 0xF0;
		leftpart[3] = leftpart[3] >> 4;
		rightpart[3] = in[3] & 0x0F;

		for (i = 0; i < 4; i++)
		{
			//permutating the left parts
			if (leftpart[i] == 0x06)
			{
				leftpart[i] = 0x00;
			}
			else if (leftpart[i] == 0x04)
			{
				leftpart[i] = 0x01;
			}
			else if (leftpart[i] == 0x0C)
			{
				leftpart[i] = 0x02;
			}
			else if (leftpart[i] == 0x05)
			{
				leftpart[i] = 0x03;
			}
			else if (leftpart[i] == 0x00)
			{
				leftpart[i] = 0x04;
			}
			else if (leftpart[i] == 0x07)
			{
				leftpart[i] = 0x05;
			}
			else if (leftpart[i] == 0x02)
			{
				leftpart[i] = 0x06;
			}
			else if (leftpart[i] == 0x0E)
			{
				leftpart[i] = 0x07;
			}
			else if (leftpart[i] == 0x01)
			{
				leftpart[i] = 0x08;
			}
			else if (leftpart[i] == 0x0F)
			{
				leftpart[i] = 0x09;
			}
			else if (leftpart[i] == 0x03)
			{
				leftpart[i] = 0x0A;
			}
			else if (leftpart[i] == 0x0D)
			{
				leftpart[i] = 0x0B;
			}
			else if (leftpart[i] == 0x08)
			{
				leftpart[i] = 0x0C;
			}
			else if (leftpart[i] == 0x0A)
			{
				leftpart[i] = 0x0D;
			}
			else if (leftpart[i] == 0x09)
			{
				leftpart[i] = 0x0E;
			}
			else if (leftpart[i] == 0x0B)
			{
				leftpart[i] = 0x0F;
			}

			//permutating the right parts
			if (rightpart[i] == 0x06)
			{
				rightpart[i] = 0x00;
			}
			else if (rightpart[i] == 0x04)
			{
				rightpart[i] = 0x01;
			}
			else if (rightpart[i] == 0x0C)
			{
				rightpart[i] = 0x02;
			}
			else if (rightpart[i] == 0x05)
			{
				rightpart[i] = 0x03;
			}
			else if (rightpart[i] == 0x00)
			{
				rightpart[i] = 0x04;
			}
			else if (rightpart[i] == 0x07)
			{
				rightpart[i] = 0x05;
			}
			else if (rightpart[i] == 0x02)
			{
				rightpart[i] = 0x06;
			}
			else if (rightpart[i] == 0x0E)
			{
				rightpart[i] = 0x07;
			}
			else if (rightpart[i] == 0x01)
			{
				rightpart[i] = 0x08;
			}
			else if (rightpart[i] == 0x0F)
			{
				rightpart[i] = 0x09;
			}
			else if (rightpart[i] == 0x03)
			{
				rightpart[i] = 0x0A;
			}
			else if (rightpart[i] == 0x0D)
			{
				rightpart[i] = 0x0B;
			}
			else if (rightpart[i] == 0x08)
			{
				rightpart[i] = 0x0C;
			}
			else if (rightpart[i] == 0x0A)
			{
				rightpart[i] = 0x0D;
			}
			else if (rightpart[i] == 0x09)
			{
				rightpart[i] = 0x0E;
			}
			else if (rightpart[i] == 0x0B)
			{
				rightpart[i] = 0x0F;
			}
		}

		//We do the XOR with the Key
		for (j = 0; j < 4; j++)
		{
			in[j] = ((leftpart[j] << 4) | rightpart[j]) ^ key[3][j];
		}


		for (k = 2; k >= 0; k--)
		{

			//cutting the first and last four bits of the first character
			leftpart[0] = in[0] & 0xF0;
			leftpart[0] = leftpart[0] >> 4;
			rightpart[0] = in[0] & 0x0F;

			//cutting the first and last four bits of the second character
			leftpart[1] = in[1] & 0xF0;
			leftpart[1] = leftpart[1] >> 4;
			rightpart[1] = in[1] & 0x0F;

			//cutting the first and last four bits of the third character
			leftpart[2] = in[2] & 0xF0;
			leftpart[2] = leftpart[2] >> 4;
			rightpart[2] = in[2] & 0x0F;

			//cutting the first and last four bits of the fourth character
			leftpart[3] = in[3] & 0xF0;
			leftpart[3] = leftpart[3] >> 4;
			rightpart[3] = in[3] & 0x0F;

			//we take the bits of each part
			for (i = 0; i < 4; i++)
			{
				//we take the first (leftmost) bit
				leftpartbits[i][0] = (leftpart[i] & 0x08) >> 3;
				rightpartbits[i][0] = (rightpart[i] & 0x08) >> 3;

				//we take the second bit
				leftpartbits[i][1] = (leftpart[i] & 0x04) >> 2;
				rightpartbits[i][1] = (rightpart[i] & 0x04) >> 2;

				//we take the third bit
				leftpartbits[i][2] = (leftpart[i] & 0x02) >> 1;
				rightpartbits[i][2] = (rightpart[i] & 0x02) >> 1;

				//we take the fourth (rightmost) bit
				leftpartbits[i][3] = (leftpart[i] & 0x01);
				rightpartbits[i][3] = (rightpart[i] & 0x01);
			}


			unsigned char t[12];


			//we do the relocation between the bits of the two letters (first and second)
			t[0] = leftpartbits[0][1];
			leftpartbits[0][1] = rightpartbits[0][0];
			t[1] = leftpartbits[0][2];
			leftpartbits[0][2] = leftpartbits[1][0];
			t[2] = leftpartbits[0][3];
			leftpartbits[0][3] = rightpartbits[1][0];
			rightpartbits[0][0] = t[0];
			t[3] = rightpartbits[0][2];
			rightpartbits[0][2] = leftpartbits[1][1];
			t[4] = rightpartbits[0][3];
			rightpartbits[0][3] = rightpartbits[1][1];

			leftpartbits[1][0] = t[1];
			leftpartbits[1][1] = t[3];
			t[5] = leftpartbits[1][3];
			leftpartbits[1][3] = rightpartbits[1][2];
			rightpartbits[1][0] = t[2];
			rightpartbits[1][1] = t[4];
			rightpartbits[1][2] = t[5];

			//we do the relocation between the bits of the two letters (third and fourth)
			t[6] = leftpartbits[2][1];
			leftpartbits[2][1] = rightpartbits[2][0];
			t[7] = leftpartbits[2][2];
			leftpartbits[2][2] = leftpartbits[3][0];
			t[8] = leftpartbits[2][3];
			leftpartbits[2][3] = rightpartbits[3][0];
			rightpartbits[2][0] = t[6];
			t[9] = rightpartbits[2][2];
			rightpartbits[2][2] = leftpartbits[3][1];
			t[10] = rightpartbits[2][3];
			rightpartbits[2][3] = rightpartbits[3][1];

			leftpartbits[3][0] = t[7];
			leftpartbits[3][1] = t[9];
			t[11] = leftpartbits[3][3];
			leftpartbits[3][3] = rightpartbits[3][2];
			rightpartbits[3][0] = t[8];
			rightpartbits[3][1] = t[10];
			rightpartbits[3][2] = t[11];

			//we unite the bits of each part
			for (j = 0; j < 4; j++)
			{
				//we take the first left and right parts' bits
				leftpart[j] = (leftpartbits[j][0] << 3) | (leftpartbits[j][1] << 2) | (leftpartbits[j][2] << 1) | (leftpartbits[j][3]);
				rightpart[j] = (rightpartbits[j][0] << 3) | (rightpartbits[j][1] << 2) | (rightpartbits[j][2] << 1) | (rightpartbits[j][3]);
			}

			for (i = 0; i < 4; i++)
			{
				//permutating the left parts
				if (leftpart[i] == 0x06)
				{
					leftpart[i] = 0x00;
				}
				else if (leftpart[i] == 0x04)
				{
					leftpart[i] = 0x01;
				}
				else if (leftpart[i] == 0x0C)
				{
					leftpart[i] = 0x02;
				}
				else if (leftpart[i] == 0x05)
				{
					leftpart[i] = 0x03;
				}
				else if (leftpart[i] == 0x00)
				{
					leftpart[i] = 0x04;
				}
				else if (leftpart[i] == 0x07)
				{
					leftpart[i] = 0x05;
				}
				else if (leftpart[i] == 0x02)
				{
					leftpart[i] = 0x06;
				}
				else if (leftpart[i] == 0x0E)
				{
					leftpart[i] = 0x07;
				}
				else if (leftpart[i] == 0x01)
				{
					leftpart[i] = 0x08;
				}
				else if (leftpart[i] == 0x0F)
				{
					leftpart[i] = 0x09;
				}
				else if (leftpart[i] == 0x03)
				{
					leftpart[i] = 0x0A;
				}
				else if (leftpart[i] == 0x0D)
				{
					leftpart[i] = 0x0B;
				}
				else if (leftpart[i] == 0x08)
				{
					leftpart[i] = 0x0C;
				}
				else if (leftpart[i] == 0x0A)
				{
					leftpart[i] = 0x0D;
				}
				else if (leftpart[i] == 0x09)
				{
					leftpart[i] = 0x0E;
				}
				else if (leftpart[i] == 0x0B)
				{
					leftpart[i] = 0x0F;
				}

				//permutating the right parts
				if (rightpart[i] == 0x06)
				{
					rightpart[i] = 0x00;
				}
				else if (rightpart[i] == 0x04)
				{
					rightpart[i] = 0x01;
				}
				else if (rightpart[i] == 0x0C)
				{
					rightpart[i] = 0x02;
				}
				else if (rightpart[i] == 0x05)
				{
					rightpart[i] = 0x03;
				}
				else if (rightpart[i] == 0x00)
				{
					rightpart[i] = 0x04;
				}
				else if (rightpart[i] == 0x07)
				{
					rightpart[i] = 0x05;
				}
				else if (rightpart[i] == 0x02)
				{
					rightpart[i] = 0x06;
				}
				else if (rightpart[i] == 0x0E)
				{
					rightpart[i] = 0x07;
				}
				else if (rightpart[i] == 0x01)
				{
					rightpart[i] = 0x08;
				}
				else if (rightpart[i] == 0x0F)
				{
					rightpart[i] = 0x09;
				}
				else if (rightpart[i] == 0x03)
				{
					rightpart[i] = 0x0A;
				}
				else if (rightpart[i] == 0x0D)
				{
					rightpart[i] = 0x0B;
				}
				else if (rightpart[i] == 0x08)
				{
					rightpart[i] = 0x0C;
				}
				else if (rightpart[i] == 0x0A)
				{
					rightpart[i] = 0x0D;
				}
				else if (rightpart[i] == 0x09)
				{
					rightpart[i] = 0x0E;
				}
				else if (rightpart[i] == 0x0B)
				{
					rightpart[i] = 0x0F;
				}
			}


			for (j = 0; j < 4; j++)
			{
				in[j] = ((leftpart[j] << 4) | rightpart[j]) ^ key[k][j];
			}

		}
		

		/*
		//We print the decryption output
		printf("Decryption output message: ");
		for (i = 0; i < 4; i++)
		{
			printf("%c", in[i]);
		}
		printf("\n");
		*/
	}



	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;


	printf("Process completed.\n");

	printf("The elapsed time is %lf seconds.\n", time_spent);
	

	return 0;

}
