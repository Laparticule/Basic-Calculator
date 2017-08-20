#include <stdlib.h>
#include <stdio.h>

int mystrlen(char *str)
{
	int i = 0;
	while (str[i] != 0)
		i = i+1;
	return i;
}

char getsign(int nb1_len, int nb2_len, char *str1, char *str2)
{
	char sign = '+';
	int i = 0;
	if (nb1_len < nb2_len)
		sign ='-';
	if (nb1_len == nb2_len)
	{
		while (i < nb1_len && str1[i] == str2[i])
			i = i+1 ;
		if (str1[i] < str2[i])
			sign = '-';
	}
	return sign;
}

int main(int argc, char *argv[])
{
	int operation;
	char nb1_str[81] = {0};
	char nb2_str[81] = {0};
	int nb1[80] = {0};
	int nb2[80] = {0};
	int nb[81] = {0};
	int i;
	int nb1_len;
	int nb2_len;
	int carry = 0;
	int nb_max;
	char sign = '+';

	printf("Enter two integers (80 digits at most) to compute a new operation.\n");
	scanf("%s", (char*)&nb1_str);
  scanf("%s", (char*)&nb2_str);

	nb1_len = mystrlen((char*)&nb1_str);
	nb2_len = mystrlen((char*)&nb2_str);
	nb_max = (nb1_len > nb2_len)? nb1_len : nb2_len;

	for (i = 0; i < nb1_len ; i = i+1)
  {
		nb1[nb1_len -1 - i] = nb1_str[i] - 48;
  }

	for (i = 0; i < nb2_len ; i = i+1)
	{
		nb2[nb2_len -1 -i] = nb2_str[i] - 48;
	}

	printf("Which operation do you want to compute : Addition (1) or Substraction (2) ?  ");
	scanf("%d", &operation);

	if (operation == 1) // ADDITION
	{
		for(i =  0; i < nb_max ; i = i+1)
		{
			nb[i] = (nb1[i] + nb2[i] + carry)%10;
			carry =  (nb1[i] + nb2[i] + carry < 10)? 0 : 1;
		}
		if (carry == 1);
			nb[nb_max] = 1;
	}
	else // SUBSTRACTION
	{
		sign = getsign(nb1_len, nb2_len, (char*)&nb1_str, (char*)&nb2_str);

		if (sign == '+')
		{
			for (i = 0 ; i < nb_max ; i = i+1)
			{
				if (nb2[i] + carry > nb1[i])
				{
					nb[i] = nb1[i] - nb2[i] + 10 - carry;
					carry = 1;
				}
				else
				{
					nb[i] = nb1[i] - nb2[i] - carry;
					carry = 0;
				}
			}
		}
		else
		{
			for (i = 0; i < nb_max; i = i+1)
			{
				if (nb2[i] >= nb1[i] + carry)
				{
					nb[i] = nb2[i] - nb1[i] - carry;
					carry = 0;
				}
				else
				{
					nb[i] = nb2[i] - nb1[i] + 10 - carry;
					carry = 1;
				}
			}
		}
	}

	printf("Here is your result : ");
	printf("%c ", sign); // Print sign
	if (carry == 1) // Print nb in reverse
		printf("%d", nb[nb_max]);
	for (i = nb_max-1 ; i>= 0; i = i-1)
	{
		printf("%d", nb[i]);
		if (!(i%3))
			printf(" ");
	}
	printf("\n");
}
