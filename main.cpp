#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>

bool readFile(std::string fileName, std::string *&sRows, int &nCount)
{//���������� ����� ����� � ������
	std::ifstream ifs;
	std::string str;
	ifs.open(fileName);
	if (ifs.fail()) return false;
	nCount = 0;
	while (std::getline(ifs, str))
		sRows[nCount++] = str;
	ifs.close();
	return true;
}

//��������� ������ str � ������ �������
char* toLowerCase(char *str)
{
	int i = 0;
	char sz = ' ';
	int len = strlen(str);
	char *s = new char[len];
	
	for (i = 0; i < len; i++){
		//����� ������� �������
		sz = str[i];
		sz = tolower(sz);
		s[i] = sz;
	}
	s[i] = '\0';
	//������� ������ � ������ ��������
	return s;
}

void sortTextArray(std::string *&words, int &count)
{//���������� ��������� �������
	if (count == 0) return;
	int flag = 1;
	//������ ��� ����������
	char *str1 = new char[256];
	char *str2 = new char[256];
	std::string temp;

	//����������
	while (flag != 0)
	{
		flag = 0;
		for (int i = 0; i < count - 1; i++){

			strcpy(str1, words[i].c_str());
			strcpy(str2, words[i + 1].c_str());
			//���� ���� ������������� � ���������� �������� ��������
			if (strcmp(toLowerCase(str1), toLowerCase(str2)) > 0)
			{
				temp = words[i];
				words[i] = words[i + 1];
				words[i + 1] = temp;
				flag++;
			}
		}
	}
	//������������ ������������ ������
	delete[]str1;
	delete[]str2;
}

void searchCountSames(std::string *a, int &N, std::string fileName)
{//����� ���������� ��������� ������� ����� � �������� �������
	struct SAMES {
		int n = 0;
		std::string name;
	};
	SAMES *sames = new SAMES[N];
	int inx, count = 0;
	for (int i = 0; i < N; i++) {
		inx = -1;
		for (int j = 0; j < count; j++) {
			if (a[i] == sames[j].name) {
				inx = j;
				break;
			}
		}//for j

		if (inx == -1) {
			sames[count].name = a[i];
			sames[count++].n++;
		}
		else sames[inx].n++;
	}//for i



	//������ ������ �� ������� � ���� 
	std::ofstream ofs;//���������� ��� ������ ������ � ����
	ofs.open(fileName);//�������� ����� ��� ������
	//������ � ���� � ����� ���������� �� �����
	for (int i = 0; i < count; i++){
		ofs << sames[i].n << " " << sames[i].name << std::endl;
		std::cout << sames[i].n << " " << sames[i].name << std::endl;
	}
	ofs.close();//�������� �����
}

int main()
{
	std::string *sWords = new std::string[1000];//������������ ������ ����
	int size = 0;
	readFile("file.txt", sWords, size);
	//����� ����������� ����� �� �����
	for (int i = 0; i < size; i++){
		std::cout << sWords[i] << std::endl;
	}
	//���������� �������
	sortTextArray(sWords, size);
	//������� ���������� ���������� � ����� ����������� �� �����
	std::cout << "\n\nAfter sorting...\n";
	searchCountSames(sWords, size, "file_result.txt");

	delete[]sWords;//������������ ������ ������
	std::cout << std::endl;
	system("pause");
}