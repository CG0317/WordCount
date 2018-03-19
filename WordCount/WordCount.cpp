#include "stdafx.h"
#include "string"
#include "string.h"
#include "iostream"
#include "fstream"

using namespace std;

FILE *file;
int chars = 0, words = 0, lines = 0;
char c;


bool isLine(char a)//�ж�����
{
	if (a == '\n')
		return true;
	return false;
}

bool isSpace(char a)//�жϿո�
{
	if (a == ' ')
		return true;
	return false;
}


bool isTab(char a)//�ж��Ʊ��
{
	if (a == '\t')
		return true;
	return false;
}

bool isLetter(char a)//�ж���ĸ
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return true;
	return false;
}

bool isDigit(char a)//�ж�����
{
	if (a >= '0' && a <= '9')
		return true;
	return false;
}

bool isComma(char a)//�ж϶���
{
	if (a == ',')
		return true;
	return false;
}

bool isDiv(char a)//�ж�б��
{
	if (a == '/')
		return true;
	return false;
}

bool isSeparator(char a)//�жϷָ���
{
	if ( a == '\n' ||a == ',' || a == ' ' || a == '\t' || a == '\r')
		return true;
	return false;
}

void wc()//ͳ�Ƶ��ʣ��ַ����е�����
{
	chars = 0;
	words = 0;
	lines = 0;
	while ((c = fgetc(file)) != EOF)
	{
		chars++;//�ַ�+1
		if (!isSeparator(c))
		{
			words++;//���Ƿָ����򵥴�+1
			while ((c = fgetc(file)) != EOF)
			{
				chars++;
				if (!isSeparator(c))
				{
				}//���Ƿָ�����Ȼ��һ�����ʣ�����������ж�
				else if (isLine(c))//�������У�����+1
				{
					lines++;
					break;
				}
				else if (isSpace(c) || isComma(c) || isTab(c))//�����ж�����
				{
					break;
				}
			}
		}
		else if (isLine(c))
			lines++;
	}
	if (chars !=0)//���ַ������һ���޻��з���Ȼ������+1
		lines++;
}


int count(int argc, char *argv[])
{
	char *resultFile = "result.txt", *fileName = NULL,*outputFile = NULL;
	int isc=0, isw=0, isl=0,iso = 0;//�Ƿ����ַ������ʡ�����������ָ���ļ�������������
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-o") == 0)//����-o�����������ָ������ļ���
		{
			if (iso == 0)
				iso = i;
			else
			{
				cout << "error :input format is wrong." << endl;//���������ظ�
				return 1;
			}
			if (i < argc - 1)
				outputFile = argv[i + 1];
			else
			{
				cout << "error :output file is empty." << endl;//û������ָ������ļ�����
				return 2;
			}
		}
		else if (strcmp(argv[i], "-c") == 0)
		{
			if (isc == 0)
				isc = i;
			else
			{
				cout << "error :input format is wrong." << endl;
				return 1;
			}
		}
		else if (strcmp(argv[i], "-w") == 0)
		{
			if (isw == 0)
				isw = i;
			else
			{
				cout << "error :input format is wrong." << endl;
				return 1;
			}

		}
		else if (strcmp(argv[i], "-l") == 0)
		{
			if (isl == 0)
				isl = i;
			else
			{
				cout << "error :input format is wrong." << endl;
				return 1;
			}

		}
		else if (i!=0 && i < 5 && fileName == NULL && argv[i][0] != '-')
		{
			fileName = argv[i];
		}

	}
	if (iso !=0 && (iso < isc || iso < isw || iso < isl))
	{
		cout << "error :input format is wrong." << endl;
		return 3;// `-o`�������һ������
	}


	if (fileName == NULL)
	{
		cout << "error :input file is empty." << endl;
		return 0;
	}

	file = fopen(fileName, "r");//��ȡ�����ļ�
	if (file == NULL)
	{
		cout << "error :file is empty." << endl;
		return 4;
	}
	wc();
	fclose(file);

 if (iso !=0 && (iso > isc || iso > isw || iso > isl))//��������뵽ָ������ļ�
 {
     fstream OutputFile;
	OutputFile.open(outputFile, ios_base::out);
	for (int i = 0; i < argc; i++)
	{
            if (strcmp(argv[i], "-c") == 0)
            {
                cout << "�ַ���:" << chars << endl;
                if (OutputFile.is_open())
                {
				OutputFile << fileName << ", �ַ�����" << chars << endl;
                }
            }
            else if (strcmp(argv[i], "-w") == 0)
            {
                cout << "������:" << words << endl;
                if (OutputFile.is_open())
                {
                    OutputFile << fileName << ", ��������" << words << endl;
                }
            }
            else if (strcmp(argv[i], "-l") == 0)
            {
                cout << "����:" << lines << endl;
                if (OutputFile.is_open())
                {
                    OutputFile << fileName << ", ������" << lines << endl;
                }
            }
    }
	OutputFile.close();//�ر��ļ�
 }
 if(iso == 0)//��������뵽Ĭ���ļ�
 {
     fstream resFile;
	resFile.open(resultFile, ios_base::out);
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-c") == 0)
		{
			cout << "�ַ���:" << chars << endl;
			if (resFile.is_open())
			{
				resFile << fileName << ", �ַ�����" << chars << endl;
			}
		}
		else if (strcmp(argv[i], "-w") == 0)
		{
			cout << "������:" << words << endl;
			if (resFile.is_open())
			{
				resFile << fileName << ", ��������" << words << endl;
			}
		}
		else if (strcmp(argv[i], "-l") == 0)
		{
			cout << "����:" << lines << endl;
			if (resFile.is_open())
                {
                    resFile << fileName << ", ������" << lines << endl;
                }
            }
        }
        resFile.close();
    }
	return 0;
}

int main(int argc, char *argv[])
{
	count(argc, argv);
	return 0;
}


