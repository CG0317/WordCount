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

bool isLine(char a)//判断行数
{
	if (a == '\n')
		return true;
	return false;
}

bool isSpace(char a)//判断空格
{
	if (a == ' ')
		return true;
	return false;
}


bool isTab(char a)//判断制表符
{
	if (a == '\t')
		return true;
	return false;
}

bool isLetter(char a)//判断字母
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return true;
	return false;
}

bool isDigit(char a)//判断数字
{
	if (a >= '0' && a <= '9')
		return true;
	return false;
}

bool isComma(char a)//判断逗号
{
	if (a == ',')
		return true;
	return false;
}

bool isDiv(char a)//判断斜杠
{
	if (a == '/')
		return true;
	return false;
}

bool isSeparator(char a)//判断分隔符
{
	if ( a == '\n' ||a == ',' || a == ' ' || a == '\t' || a == '\r')
		return true;
	return false;
}

void wc()//统计单词，字符，行的数量
{
	chars = 0;
	words = 0;
	lines = 0;
	while ((c = fgetc(file)) != EOF)
	{
		chars++;//字符+1
		if (!isSeparator(c))
		{
			words++;//不是分隔符则单词+1
			while ((c = fgetc(file)) != EOF)
			{
				chars++;
				if (!isSeparator(c))
				{
				}//不是分隔符依然算一个单词，若是则继续判定
				else if (isLine(c))//若是新行，行数+1
				{
					lines++;
					break;
				}
				else if (isSpace(c) || isComma(c) || isTab(c))//单词判定结束
				{
					break;
				}
			}
		}
		else if (isLine(c))
			lines++;
	}
	if (chars !=0)//有字符的最后一行无换行符依然令行数+1
		lines++;
}

int count(int argc, char *argv[])
{
	char *resultFile = "result.txt", *fileName = NULL,*outputFile = NULL;
	int isc=0, isw=0, isl=0,iso = 0;//是否有字符、单词、行数计数和指定文件输出结果的需求
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-o") == 0)//若有-o，则接着输入指定输出文件名
		{
			if (iso == 0)
				iso = i;
			else
			{
				cout << "error :input format is wrong." << endl;//参数输入重复
				return 2;
			}
			if (i < argc - 1)
				outputFile = argv[i + 1];
			else
			{
				cout << "error :output file is empty." << endl;//没有输入指定输出文件报错
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
		return 4;// `-o`不是最后一个参数
	}


	if (fileName == NULL)
	{
		cout << "error :input file is empty." << endl;
		return 1;
	}

	file = fopen(fileName, "r");//读取输入文件
	if (file == NULL)
	{
		cout << "error :file is empty." << endl;
		return 5;
	}
	wc();
	fclose(file);

 if (iso !=0 && (iso > isc || iso > isw || iso > isl))//将结果输入到指定输出文件
 {
     fstream OutputFile;
	OutputFile.open(outputFile, ios_base::out);
	for (int i = 0; i < argc; i++)
	{
            if (strcmp(argv[i], "-c") == 0)
            {
                cout << "字符数:" << chars << endl;
                if (OutputFile.is_open())
                {
				OutputFile << fileName << ", 字符数：" << chars << endl;
                }
            }
            else if (strcmp(argv[i], "-w") == 0)
            {
                cout << "单词数:" << words << endl;
                if (OutputFile.is_open())
                {
                    OutputFile << fileName << ", 单词数：" << words << endl;
                }
            }
            else if (strcmp(argv[i], "-l") == 0)
            {
                cout << "行数:" << lines << endl;
                if (OutputFile.is_open())
                {
                    OutputFile << fileName << ", 行数：" << lines << endl;
                }
            }
            else if (argv[i][0] == '-' && strcmp(argv[i], "-c") != 0 && strcmp(argv[i], "-w") != 0 && strcmp(argv[i], "-l") != 0 && strcmp(argv[i], "-o") != 0)
		{
			cout << "error 4:parameter error." << endl;
			return 6;//参数错误
		}
    }
	OutputFile.close();//关闭文件
	return 0;
 }
 if(iso == 0)//将结果输入到默认文件
 {
     fstream resFile;
	resFile.open(resultFile, ios_base::out);
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-c") == 0)
		{
			cout << "字符数:" << chars << endl;
			if (resFile.is_open())
			{
				resFile << fileName << ", 字符数：" << chars << endl;
			}
		}
		else if (strcmp(argv[i], "-w") == 0)
		{
			cout << "单词数:" << words << endl;
			if (resFile.is_open())
			{
				resFile << fileName << ", 单词数：" << words << endl;
			}
		}
		else if (strcmp(argv[i], "-l") == 0)
		{
			cout << "行数:" << lines << endl;
			if (resFile.is_open())
                {
                    resFile << fileName << ", 行数：" << lines << endl;
                }
            }
             else if (argv[i][0] == '-' && strcmp(argv[i], "-c") != 0 && strcmp(argv[i], "-w") != 0 && strcmp(argv[i], "-l") != 0 && strcmp(argv[i], "-o") != 0)
		{
			cout << "error 4:parameter error." << endl;
			return 6;//参数错误
		}
        }
            resFile.close();
    }

	return 0;
}

void test1()//正确输入
{
	cout << "testcase1:" << endl;
	int argc = 5;
	char *argv[] = { "WordCountTest.exe", "-c", "-w", "-l", "file.c" };
	int result = count(argc, argv);
	assert(result == 0);
}

void test2()//指定输出文件
{
	cout << "testcase2:" << endl;
	int argc = 7;
	char *argv[] = { "WordCountTest.exe", "-c", "-w", "-l", "file.c" , "-o", "outputFile.txt"};
	int result = count(argc, argv);
	assert(result == 0);
}

void test3()//输入错误参数
{
	cout << "testcase3:" << endl;
	int argc = 7;
	char *argv[] = { "WordCountTest.exe", "-b", "-w", "-l", "file.c" , "-o", "outputFile.txt" };
	int result = count(argc, argv);
	assert(result == 6);
}

void test4()//无输入文件
{
	cout << "testcase4:" << endl;
	int argc = 6;
	char *argv[] = { "WordCountTest.exe", "-c", "-w", "-l" , "-o", "outputFile.txt" };
	int result = count(argc, argv);
	assert(result == 1);
}

void test5()//“-o”后不指定输出文件
{
	cout << "testcase5:" << endl;
	int argc = 6;
	char *argv[] = { "WordCountTest.exe", "-c", "-w", "-l" , "file.c", "-o"};
	int result = count(argc, argv);
	assert(result == 3);
}

void test6()//输入文件名错误
{
	cout << "testcase6:" << endl;
	int argc = 7;
	char *argv[] = { "WordCountTest.exe", "-c", "-w", "-l" , "file4.c", "-o" , "outputFile.txt" };
	int result = count(argc, argv);
	assert(result == 5);
}

void test7()//参数输入错误
{
	cout << "testcase7:" << endl;
	int argc = 4;
	char *argv[] = { "WordCountTest.exe", "-c", "-c", "file.c" };
	int result = count(argc, argv);
	assert(result == 2);
}

void test8()//输入参数顺序错误
{
	cout << "testcase8:" << endl;
	int argc = 6;
	char *argv[] = { "WordCountTest.exe", "-c", "-o", "-l" , "file.c" , "outputFile.txt" };
	int result = count(argc, argv);
	assert(result == 4);
}

void test9()//输入文件群为空格
{
	cout << "testcase9:" << endl;
	int argc = 7;
	char *argv[] = { "WordCountTest.exe", "-c", "-w", "-l" , "file2.c", "-o" , "outputFile.txt" };
	int result = count(argc, argv);
	assert(result == 0);
}

void test10()//仅有\n,\t,\r的文件
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

