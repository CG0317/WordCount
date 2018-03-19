#include "stdafx.h"
#include "string"
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
				return 1;
			}
			if (i < argc - 1)
				outputFile = argv[i + 1];
			else
			{
				cout << "error :output file is empty." << endl;//没有输入指定输出文件报错
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
		return 3;// `-o`不是最后一个参数
	}


	if (fileName == NULL)
	{
		cout << "error :input file is empty." << endl;
		return 0;
	}

	file = fopen(fileName, "r");//读取输入文件
	if (file == NULL)
	{
		cout << "error :file is empty." << endl;
		return 4;
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
    }
	OutputFile.close();//关闭文件
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


