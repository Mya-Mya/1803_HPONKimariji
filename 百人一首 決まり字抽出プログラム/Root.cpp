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

/*決まり字抽出。Upperには上の句全文の配列を、Averableにはその札を走査対象にするかどうかの配列を入れること。*/
sIdentification Identifyer(string Upper[]){//,bool Averable[LyricsAmount]) {
	sIdentification identification;
	string buf;
	int NowLetter;
	bool TryAgain = true;
	while (TryAgain) {
		TryAgain = false;
		for (int i = 0; i < LyricsAmount; i++) {
			buf = identification.put[i];//自分の札を手に取って、
			for (int j = 0; j < LyricsAmount; j++) {//他の札を覗いてみる。
				if (j == i)continue;//自分と自分を比べてもしょうがない
				if (buf == identification.put[j]) {//自分と他の札の内容が同じだ。まだ決まり字として足りぬ。
					NowLetter = identification.put[j].length();//この文字数じゃ足りぬ。
					identification.put[i] = Upper[i].substr(0, NowLetter + 2);//自分の札の決まり字を増強
					identification.put[j] = Upper[j].substr(0, NowLetter + 2);//その札の決まり字も増強
					TryAgain = true;//もう一回出直せ。
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
	/*読み出し*/
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

	/*決まり字抽出*/
	sIdentification idt = Identifyer(OguraHPONUpper);

	/*決まり字表示*/
	for (int i = 0; i < LyricsAmount; i++)cout << idt.put[i] << endl;
	return 0;
}