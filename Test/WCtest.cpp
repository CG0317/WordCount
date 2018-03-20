#include <stdio.h>
#include <tchar.h>
#include "assert.h"
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
				return 2;
			}
			if (i < argc - 1)
				outputFile = argv[i + 1];
			else
			{
				cout << "error :output file is empty." << endl;//û������ָ������ļ�����
				return 3;
			}
		}
		else if (strcmp(argv[i], "-c") == 0)
		{
			if (isc == 0)
				isc = i;
			else
			{
				cout << "error :input format is wrong." << endl;
				return 2;
			}
		}
		else if (strcmp(argv[i], "-w") == 0)
		{
			if (isw == 0)
				isw = i;
			else
			{
				cout << "error :input format is wrong." << endl;
				return 2;
			}

		}
		else if (strcmp(argv[i], "-l") == 0)
		{
			if (isl == 0)
				isl = i;
			else
			{
				cout << "error :input format is wrong." << endl;
				return 2;
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
		return 4;// `-o`�������һ������
	}


	if (fileName == NULL)
	{
		cout << "error :input file is empty." << endl;
		return 1;
	}

	file = fopen(fileName, "r");//��ȡ�����ļ�
	if (file == NULL)
	{
		cout << "error :file is empty." << endl;
		return 5;
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
            else if (argv[i][0] == '-' && strcmp(argv[i], "-c") != 0 && strcmp(argv[i], "-w") != 0 && strcmp(argv[i], "-l") != 0 && strcmp(argv[i], "-o") != 0)
		{
			cout << "error 4:parameter error." << endl;
			return 6;//��������
		}
    }
	OutputFile.close();//�ر��ļ�
	return 0;
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
             else if (argv[i][0] == '-' && strcmp(argv[i], "-c") != 0 && strcmp(argv[i], "-w") != 0 && strcmp(argv[i], "-l") != 0 && strcmp(argv[i], "-o") != 0)
		{
			cout << "error 4:parameter error." << endl;
			return 6;//��������
		}
        }
            resFile.close();
    }

	return 0;
}

void test1()//��ȷ����
{
	cout << "testcase1:" << endl;
	int argc = 5;
	char *argv[] = { "WordCountTest.exe", "-c", "-w", "-l", "file.c" };
	int result = count(argc, argv);
	assert(result == 0);
}

void test2()//ָ������ļ�
{
	cout << "testcase2:" << endl;
	int argc = 7;
	char *argv[] = { "WordCountTest.exe", "-c", "-w", "-l", "file.c" , "-o", "outputFile.txt"};
	int result = count(argc, argv);
	assert(result == 0);
}

void test3()//����������
{
	cout << "testcase3:" << endl;
	int argc = 7;
	char *argv[] = { "WordCountTest.exe", "-b", "-w", "-l", "file.c" , "-o", "outputFile.txt" };
	int result = count(argc, argv);
	assert(result == 6);
}

void test4()//�������ļ�
{
	cout << "testcase4:" << endl;
	int argc = 6;
	char *argv[] = { "WordCountTest.exe", "-c", "-w", "-l" , "-o", "outputFile.txt" };
	int result = count(argc, argv);
	assert(result == 1);
}

void test5()//��-o����ָ������ļ�
{
	cout << "testcase5:" << endl;
	int argc = 6;
	char *argv[] = { "WordCountTest.exe", "-c", "-w", "-l" , "file.c", "-o"};
	int result = count(argc, argv);
	assert(result == 3);
}

void test6()//�����ļ�������
{
	cout << "testcase6:" << endl;
	int argc = 7;
	char *argv[] = { "WordCountTest.exe", "-c", "-w", "-l" , "file4.c", "-o" , "outputFile.txt" };
	int result = count(argc, argv);
	assert(result == 5);
}

void test7()//�����������
{
	cout << "testcase7:" << endl;
	int argc = 4;
	char *argv[] = { "WordCountTest.exe", "-c", "-c", "file.c" };
	int result = count(argc, argv);
	assert(result == 2);
}

void test8()//�������˳�����
{
	cout << "testcase8:" << endl;
	int argc = 6;
	char *argv[] = { "WordCountTest.exe", "-c", "-o", "-l" , "file.c" , "outputFile.txt" };
	int result = count(argc, argv);
	assert(result == 4);
}

void test9()//�����ļ�ȺΪ�ո�
{
	cout << "testcase9:" << endl;
	int argc = 7;
	char *argv[] = { "WordCountTest.exe", "-c", "-w", "-l" , "file2.c", "-o" , "outputFile.txt" };
	int result = count(argc, argv);
	assert(result == 0);
}

void test10()//����\n,\t,\r���ļ�
{
	cout << "testcase10:" << endl;
	int argc = 7;
	char *argv[] = { "WordCountTest.exe", "-c", "-w", "-l" , "file3.c", "-o" , "outputFile.txt" };
	int result = count(argc, argv);
	assert(result == 0);
}

int main()
{
	test1();
	cout << endl;
	test2();
	cout << endl;
	test3();
	cout << endl;
	test4();
	cout << endl;
	test5();
	cout << endl;
	test6();
	cout << endl;
	test7();
	cout << endl;
	test8();
	cout << endl;
	test9();
	cout << endl;
	test10();
	cout << endl;
	getchar();
    return 0;
}

