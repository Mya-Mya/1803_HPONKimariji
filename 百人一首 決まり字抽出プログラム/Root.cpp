#include<stdio.h>
#include<iostream>
#include<fstream>
#include<malloc.h>
#include<sstream>
#include<vector>
using namespace std;
#define Letters 16
#define LyricsAmount 100

vector<string> split(string &input, char delimiter) {
	istringstream stream(input);
	string field;
	vector<string>result;
	while (getline(stream, field, delimiter)) {
		result.push_back(field);
	}
	return result;
}

typedef struct {
	 string put [LyricsAmount];
}sIdentification;

/*���܂莚���o�BUpper�ɂ͏�̋�S���̔z����AAverable�ɂ͂��̎D�𑖍��Ώۂɂ��邩�ǂ����̔z������邱�ƁB*/
sIdentification Identifyer(string Upper[]){//,bool Averable[LyricsAmount]) {
	sIdentification identification;
	string buf;
	int NowLetter;
	bool TryAgain = true;
	while (TryAgain) {
		TryAgain = false;
		for (int i = 0; i < LyricsAmount; i++) {
			buf = identification.put[i];//�����̎D����Ɏ���āA
			for (int j = 0; j < LyricsAmount; j++) {//���̎D��`���Ă݂�B
				if (j == i)continue;//�����Ǝ������ׂĂ����傤���Ȃ�
				if (buf == identification.put[j]) {//�����Ƒ��̎D�̓��e���������B�܂����܂莚�Ƃ��đ���ʁB
					NowLetter = identification.put[j].length();//���̕��������ᑫ��ʁB
					identification.put[i] = Upper[i].substr(0, NowLetter + 2);//�����̎D�̌��܂莚�𑝋�
					identification.put[j] = Upper[j].substr(0, NowLetter + 2);//���̎D�̌��܂莚������
					TryAgain = true;//�������o�����B
				}
			}
		}
	}
	return (sIdentification)identification;
}
int *getDatePointer() {
	int *date=(int *)malloc(sizeof(int)*3);
	date[0] = 2016;
	date[1] = 2;
	date[2] = 29;
	return date;
}

int main() {
	string OguraHPON[LyricsAmount][5];
	string OguraHPONUpper[LyricsAmount];
	/*�ǂݏo��*/
	ifstream ifs("OguraHPON.csv");
	string line;
	int CardNo = 0;
	while (getline(ifs, line)) {
		vector<string> strvec = split(line,',');
		for (int i = 0; i < 5; i++) { 
			OguraHPON[CardNo][i] = strvec[i];
			if(0<=i&&i<=2)OguraHPONUpper[CardNo] = OguraHPONUpper[CardNo] + strvec[i];
		}
		CardNo++;
	}

	/*���܂莚���o*/
	sIdentification idt = Identifyer(OguraHPONUpper);

	/*���܂莚�\��*/
	for (int i = 0; i < LyricsAmount; i++)cout << idt.put[i] << endl;
	return 0;
}