#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>

#include "optimization.h"
#include "stack.h"

#define PI 3.14159265359
#define e 2.7182818284590452354
double number1, number2;
char result[100];
float h;
/*
	sin -> 1;
	cos -> 2;
	tan -> 3;
	cot -> 4;
	sqrt -> 5;
	log -> 6;
	ln -> 7;
	abs -> 8;

*/
double otherOperator( double number, char ex)
{
	switch(ex)
	{
		case '1':
			return sin(number * PI / 180);
			break;
		case '2':
			return cos(number * PI / 180);
			break;
		case '3':
			return tan(number * PI / 180);
			break;
		case '4':
			return 1 / tan(number * PI / 180);
			break;
		case '5':
			return sqrt(number);
			break;
		case '6':
			return log10(number);
			break;
		case '7':
			return log(number);
			break;
		case '8':
			return fabs(number);
			break;
	}
}
int checkSign(char *s, int i)
{
    if((s[i] == '+' || s[i] == '-') &&
       (s[i - 1] == '(' || s[i - 1] == '*' || s[i - 1] == '/' || s[i - 1] == '^') &&
       (s[i + 1] >= '0' && s[i + 1] <= '9'))
        return 1;// unary;
    else
		return 0; // binary;
}

double factorial(double number)
{
    double fac = 1;
    for(int i = 2; i <= number; i++)
    {
    	fac *= i;
	}
	return fac;
}
int subGCD(double number1, double number2)
{
	if (number2 == 0)
		return number1;
	return subGCD(number2, (int)number1 % (int)number2);
}
int subLCM(double number1, double number2)
{
	return number1 * number2 / subGCD(number1, number2);
}
int checkInt(double number)
{
	if((int)number == number)
		return 1;
	else return 0;
}
void GCD()
{
	double number1, number2;
	FILE *fi = fopen("INPUT.txt", "r");
	FILE *fo = fopen("OUTPUT.txt", "w");
	fscanf(fi, "%lf", &number1);
	fscanf(fi, "%lf", &number2);
	if(checkInt(number1) == 1 && checkInt(number2) == 1 &&
		number1 >= 0 && number2 >= 0)
	{
		fprintf(fo, "%d", subGCD(number1, number2));
	}
	else
		strcpy(result, "MATH_ERROR!!!");
	fclose(fi);
	fclose(fo);
}
void LCM()
{
	double number1, number2;
	FILE *fi = fopen("INPUT.txt", "r");
	FILE *fo = fopen("OUTPUT.txt", "w");
	fscanf(fi, "%lf", &number1);
	fscanf(fi, "%lf", &number2);
	if(checkInt(number1) == 1 && checkInt(number2) == 1 &&
		number1 >= 0 && number2 >= 0)
	{
		fprintf(fo, "%d", subLCM(number1, number2));
	}
	else
		strcpy(result, "MATH_ERROR!!!");
	fclose(fi);
	fclose(fo);
}
int order(char ex)
{
	if(ex >= '1' && ex <= '8')
		return 4;

	if(ex == '^')
		return 3;

    if(ex == '*' || ex == '/' || ex == '%')
        return 2;

    if(ex == '+' || ex == '-')
    	return 1;

    return 0;
}
double calculator(double a, double b, char ex)
{
    switch(ex)
    {
        case '+':
            a += b;
            break;
        case '*':
            a *= b;
            break;
        case '/':
            a /= b;
            break;
        case '^':
        	a = pow(a, b);
        	break;
        case '-':
        	a -= b;
        	break;
        default:
            break;
    }

    return a;
}

double countNumber(char *s, int *i)
{
	if(s[*i] == 'x')
		return 0;
	if(s[*i] == 'e')
		return e;
    double so = 0., decimal = 0.;
    int dem = 1;
    while(s[(*i)] >= '0' && s[(*i)] <= '9')
    {
        so = so*10 + (s[(*i)] - '0');
        (*i)++;
    }
    if(s[(*i)] == '.')
    {
    	if(s[*i + 1] <= '0' && s[*i + 1] >= '9')
    		return so;
    	else ++(*i);

	}
    while(s[(*i)] == '.' || (s[*i] >= '0' && s[*i] <= '9'))
    {
        decimal = decimal*10 + (s[(*i)++] - '0');
        dem *= 10;
    }
    (*i)--;
    return so + (decimal/dem);
}
double countNumberFunction(char *s, int *i, double argument)
{
	if(s[*i] == 'x')
		return argument;
	if(s[*i] == 'e')
		return e;
    double so = 0., decimal = 0.;
    int dem = 1;
    while(s[(*i)] >= '0' && s[(*i)] <= '9')
    {
        so = so*10 + (s[(*i)] - '0');
        (*i)++;
    }
    if(s[(*i)] == '.')
    {
    	if(s[*i + 1] <= '0' && s[*i + 1] >= '9')
    		return so;
    	else ++(*i);

	}
    while(s[(*i)] == '.' || (s[*i] >= '0' && s[*i] <= '9'))
    {
        decimal = decimal*10 + (s[(*i)++] - '0');
        dem *= 10;
    }
    (*i)--;
    return so + (decimal/dem);
}
void Process(char *s)
{
    int i = -1;
    while (1)
    {
        int dau = 1;
        switch (s[++i])
        {
        case '(':
            pushExpression(s[i]);
            break;

        case '\0':
        case ')':

            while (!isEmptyExpression() && getExpression() != '(')
            {
            	if((getNode() < 0 && getExpression() == '5') ||
				(getNode() == 0 && getExpression() == '/') ||
				(getNode() <= 0 && (getExpression() == '6' || getExpression() == '7')))
	            {
	            	strcpy(result, "MATH_ERROR!!!");
	            	return;
				}
				if (order(getExpression()) == 4)
            	{
            		pushNode(otherOperator(popNode(), popExpression()));
				}

				else
                {
                	char a = popExpression();
                	double b = popNode();
                	pushNode(calculator(popNode(), b, a));
				}
            }

            if (!isEmptyExpression() && getExpression() == '(')
                popExpression();
            else
                return;
            break;


        case '+':
        case '-':
        case '*':
        case '/':
        case '^':

            if (checkSign(s, i) == 1)
                break;
            while (!isEmptyExpression() && order(s[i]) <= order(getExpression()))
            {
            	if((getNode() < 0 && getExpression() == '5') ||
				(getNode() == 0 && getExpression() == '/') ||
				(getNode() <= 0 && (getExpression() == '6' || getExpression() == '7')))
	            {
	            	strcpy(result, "MATH_ERROR!!!");
	            	return;
				}
				if (order(getExpression()) == 4)
            	{
            		pushNode(otherOperator(popNode(), popExpression()));
				}

				else
                {
                	char a = popExpression();
                	double b = popNode();
                	pushNode(calculator(popNode(), b, a));
				}

            }
            pushExpression(s[i]);
            break;
        case '%':
        	pushNode(popNode() / 100);
            break;
        case '!':
        	pushNode(factorial(popNode()));
        	break;
        case 's':
            if (s[i + 1] == 'i')
            {
                pushExpression('1');
                i += 2;
                break;
            }
            else
            {
                pushExpression('5');
                i += 3;
                break;
            }
        case 't':
           	pushExpression('3');
           	i += 2;
           	break;
        case 'c':
            if (s[i + 2] == 's')
            {
                pushExpression('2');
                i += 2;
                break;
            }
            else
            {
                pushExpression('4');
                i += 2;
                break;
            }
        case 'l':
        	if (s[i + 2] == 'g')
        	{
        		pushExpression('6');
        		i += 2;
        		break;
			}
			else
			{
				pushExpression('7');
        		i += 1;
        		break;
			}
		case 'a':
			pushExpression('8');
			i += 2;
			break;
		case 'G':
			i += 4;
			number1 = countNumber(s, &i);
			i += 2;
			number2 = countNumber(s, &i);
			if(checkInt(number1) == 1 && checkInt(number2) == 1 && number1 >= 0 && number2 >= 0)
			{
				pushNode(subGCD(number1, number2));
				i++;
				break;
			}
			else
			{
				strcpy(result, "MATH_ERROR!!!");
				return;
				break;
			}
			
		case 'L':
			i += 4;
			number1 = countNumber(s, &i);
			i += 2;
			number2 = countNumber(s, &i);
			if(checkInt(number1) == 1 && checkInt(number2) == 1 &&
			number1 >= 0 && number2 >= 0)
			{
				pushNode(subLCM(number1, number2));
				i++;
				break;
			}
			else
			{
				strcpy(result, "MATH_ERROR!!!");
				return;
				break;
			}
		case ',':
			strcpy(result, "MATH_ERROR!!!");
			return;
			break;
			
        default:
            if (i > 0 && checkSign(s, i - 1) == 1)
                dau = (s[i - 1] == '+') ? 1 : -1;
            pushNode(dau * countNumber(s, &i));
            break;
        }
    }
}

void ProcessFunction(char *s, double argument)
{
    int i = -1;
    while (1)
    {
        int dau = 1;
        switch (s[++i])
        {
        case '(':
            pushExpression(s[i]);
            break;

        case '\0':
        case ')':

            while (!isEmptyExpression() && getExpression() != '(')
            {
            	if((getNode() < 0 && getExpression() == '5') ||
					(getNode() == 0 && getExpression() == '/') ||
					(getNode() <= 0 && (getExpression() == '6' || getExpression() == '7')))
	            {
	            	strcpy(result, "MATH_ERROR!!!");
	            	return;
				}
				if (order(getExpression()) == 4)
            	{
            		pushNode(otherOperator(popNode(), popExpression()));
				}
				else
                {
                	char a = popExpression();
                	double b = popNode();
                	pushNode(calculator(popNode(), b, a));
				}
            }

            if (!isEmptyExpression() && getExpression() == '(')
                popExpression();
            else
                return;
            break;


        case '+':
        case '-':
        case '*':
        case '/':
        case '^':

            if (checkSign(s, i) == 1)
                break;
            while (!isEmptyExpression() && order(s[i]) <= order(getExpression()))
            {
            	if((getNode() < 0 && getExpression() == '5') ||
					(getNode() == 0 && getExpression() == '/') ||
					(getNode() <= 0 && (getExpression() == '6' || getExpression() == '7')))
	            {
	            	strcpy(result, "MATH_ERROR!!!");
	            	return;
				}
				if (order(getExpression()) == 4)
            	{
            		pushNode(otherOperator(popNode(), popExpression()));
				}

				else
                {
                	char a = popExpression();
                	double b = popNode();
                	pushNode(calculator(popNode(), b, a));
				}

            }
            pushExpression(s[i]);
            break;
        case '%':
        	pushNode(popNode() / 100);
            break;
        case '!':
        	pushNode(factorial(popNode()));
        	break;
        case 's':
            if (s[i + 1] == 'i')
            {
                pushExpression('1');
                i += 2;
                break;
            }
            else
            {
                pushExpression('5');
                i += 3;
                break;
            }
        case 't':
           	pushExpression('3');
           	i += 2;
           	break;
        case 'c':
            if (s[i + 2] == 's')
            {
                pushExpression('2');
                i += 2;
                break;
            }
            else
            {
                pushExpression('4');
                i += 2;
                break;
            }
        case 'l':
        	if (s[i + 2] == 'g')
        	{
        		pushExpression('6');
        		i += 2;
        		break;
			}
			else
			{
				pushExpression('7');
        		i += 1;
        		break;
			}
		case 'a':
			pushExpression('8');
			i += 2;
			break;
        default:
            if (i > 0 && checkSign(s, i - 1) == 1)
                dau = (s[i - 1] == '+') ? 1 : -1;
            pushNode(dau * countNumberFunction(s, &i, argument));
            break;
        }
    }
}

double f(double argument, char *str)
{
	ProcessFunction(str, argument);
	double result = popNode();
	return result;
}
double dy(double x, char *str)
{
	float b = (f(x + h, str) - f(x - h, str)) / (2 * h);
	return(b);
}
void derivative()
{
	double d[100];
	int j, k;
	double x,p;
	initStack();
	char *function;
	function = (char*)malloc(sizeof(char));
	FILE *fi = fopen("INPUT.txt", "r");
	FILE *fo = fopen("OUTPUT.txt", "w");
	fscanf(fi, "%[^\n]", function);
	optimizeCal(function);
	puts(function);
	fscanf(fi, "%lf", &x);
	if (checkError(function))
	{
		strcpy(result, "Syntax_ERROR!!!");
	}
	else
	{
		h=0.2;
		d[0] = dy(x, function);
		for (k = 2; k <= 10; k++)
		{
			h = h/2;
			d[k] = dy(x, function);
			p = 1.0;
			for (j=k-1;j>=1;j--)
			{
				p = 4*p;
				d[j] = (p * d[j+1] - d[j]) / (p-1);
			}
		}
		if(strcmp(result, "MATH_ERROR!!!") != 0 || strcmp(result, "Syntax_ERROR!!!") != 0)
	    {
	    	
	    	if((int)getNode() == getNode())
	    		snprintf(result, 1000, "%g", d[10]);
	    	else
	    		snprintf(result, 1000, "%.8lf", d[10]);
		}
	}
	fputs(result, fo);
	fclose(fi);
	fclose(fo);
	free(function);
	freeAll();
}
void integral()
{
	double upperPole, lowerPole, difference, integral;
	char *function;
	function = (char*)malloc(sizeof(char));
	FILE *fi = fopen("INPUT.txt", "r");
	FILE *fo = fopen("OUTPUT.txt", "w");
	fscanf(fi, "%lf", &lowerPole);
	fscanf(fi, "%lf", &upperPole);
	fscanf(fi, "%s", function);
	optimizeCal(function);
	printf("%lf %lf ", lowerPole, upperPole);
	puts(function);
	initStack();
	if (checkError(function))
	{
		strcpy(result, "Syntax_ERROR!!!");
	}
	else
	{
		double x = lowerPole;
		difference = (upperPole - lowerPole) / 10000;
	 	integral = (f(upperPole, function) + f(lowerPole, function)) / 2;
	 	for(int i = 1; i < 10000; i++)
	 	{
	 		x += difference;
	 		integral += f(x, function);
	 	}
	 	integral *= difference;
	 	if(strcmp(result, "MATH_ERROR!!!") != 0)
	    {
	    	if((int)getNode() == getNode())
	    		snprintf(result, 1000, "%g", integral);
	    	else
	    		snprintf(result, 1000, "%.8lf", integral);
		}
	}
	fputs(result, fo);

 	fclose(fi);
 	fclose(fo);
 	free(function);
	freeAll();
}
void calculate()
{
	FILE *fi = fopen("INPUT.txt", "r");
	FILE *fo = fopen("OUTPUT.txt", "w");
	char *s;
	s = (char*)malloc(sizeof(char));
	fscanf(fi, "%s", s);
	optimizeCal(s);
	initStack();
	if(checkError(s))
	{
		strcpy(result, "Syntax_ERROR!!!");
	}
	else
	{

	    Process(s);
	    if(strcmp(result, "MATH_ERROR!!!") != 0)
	    {
	    	if(getNode() >= 999999999999999999999999999999)
	    		strcpy(result, "ERROR!!!");
	    	else if(getNode() >= 1000000000)
	    		snprintf(result, 1000, "%.0lf", popNode());
	    	else 
	    		snprintf(result, 1000, "%.10g", popNode());
		}

	}
	fputs(result, fo);
	strcpy(result, " ");
	fclose(fi);
	fclose(fo);
	free(s);
	freeAll();
}

