
#include <iostream>
#include <time.h>
#define MAX 52
#define SHAPENUM 4
#define NUMBER 13

using namespace std;
struct Card {
	char *shp;
	int num;
};
char *cardShape[SHAPENUM] = { "��","��","��","��" };
int cardNum[NUMBER] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
int cnt = 0;

Card *init(Card card[MAX]);
Card *shuffleCard(Card card[MAX]);
void printALLCard(Card card[MAX]);
Card SelectCard(Card card[MAX]);
bool battingOK(int battig, int curYourMon,  int minBatMon);
bool isItBetween2Card(Card card1, Card card2, Card pCard);
void printCard(Card card);

int main() {
	srand(time(NULL));
	Card *allCard = new Card[MAX];
	int isPlay;
	int currentMon=4000, goalMon =20000; // 20000
	int minBatMon = 500;
	int batting;
	int remainCardNum = 52;
	Card selectCard1, selectCard2, selectPCard;
	int doYouWantKeepGoing;
	int oneMore;
	allCard = init(allCard);
	allCard = shuffleCard(allCard);

	cout << "���̸��� Ʈ����. (������ �׺� �ƴ� ����. �θ���� Ʈ������ ũ�� �����϶�� �ǹ̷δٰ� �����ֽ� �̸���)";
	cout << endl << "�츮 ���ȿ��� ���ڲ��� �ǰ� �帣�� �ִ�." << endl;
	cout << "ī���븦 �����峪��� �ϱ⸦ ��� 1�� 3���� 18�� °." << endl << "�翬�����Ե� ���Դ� ���� �ִ�. 2��... T^T" << endl;
	cout << "���� ������ ���ڿ� ��� ���� �ɾ���!" << endl << "������ ���� ���� 4õ���� �� �̤�" << endl;
	cout << "�� 4õ������ 2������ �ҷ����ھ�!" << endl << "�����̾߸��� ��������� �غ��� ���ڴ�!" << endl << endl;
	cout << "==================================================================" << endl;
	cout << "\t\t#�̼� : 4õ������ 2������ �Ҹ���" << endl;
	cout << "==================================================================" << endl;
	cout << "ī���뿡 �����Ͻðڽ��ϱ�?" << endl;
	cout << "1. ���� ���� \t 0. ���� �Ḹ. ���� ������ �غ� ����;;" << endl;
	cin >> isPlay;
	while (isPlay<0 || isPlay>1) {
		cout << "0, 1 �߿� ���   ";
		cin >> isPlay;
	}
	while (isPlay) {
		system("cls");
		cout << "============================================ TRUMP ============================================" << endl;
		cout << "\t\t���� �ݾ��� ���� ����. �ּ� ���ñݾ���" << minBatMon << "����" << endl;
		if (currentMon > 9999) {	//������ ���
			cout << "\t\t�� ���� �� : " << currentMon/10000 << "�� "<< currentMon%10000 <<"����" << "\t\t\t\t" << "�����ִ� ī����� : " << remainCardNum << " ��" << endl;
		}
		else {						//������ ���
			cout << "\t\t�� ���� �� : " << currentMon << "����" << "\t\t\t\t" << "�����ִ� ī����� : " << remainCardNum << " ��" << endl;
		}
		cout << "===============================================================================================" << endl;
		cout << "������ ������ ī���?? �ε�" << endl;
		selectCard1 = SelectCard(allCard);
		remainCardNum--;
		selectCard2 = SelectCard(allCard);
		remainCardNum--;
		
		printCard(selectCard1);
		printCard(selectCard2);
		cout << "�󸶸� �����ұ�??(��������)\t"; 
		cin >> batting;
		
		while (!battingOK(batting, currentMon, minBatMon)) {
			cout << "�� ���ñݾ��� �߸� ���߳�;; �ٽ�!(��������)\t";
			cin >> batting;
		}
		currentMon -= batting;
		
		cout << "�� ī���...?? �ε�!\t" ;
		selectPCard = SelectCard(allCard);
		remainCardNum--;
		printCard(selectPCard);
		
		if (isItBetween2Card(selectCard1, selectCard2, selectPCard)) {
			currentMon += batting * 2;
			cout << "�ƽ�! �� �ι� ����! ����~!" << endl << batting * 2 << " ���� ���� ���� " << currentMon << " ���� ����"<<endl;
		}
		else {
			cout << "!!!! ��... �ȵ� T^T ����" << endl << batting << "���� �Ҿ ���� " << currentMon << "���� ����" << endl;
		}
		
		if (currentMon <=0) {
			cout << "�����ƾƾƤþƾ�� T^T �Ļ��̶��! �Ļ��̶��������!" << endl;
			system("pause");
			return 0;
		}
		if (currentMon < minBatMon) {
			cout << "......�ּұݾ��� " << minBatMon << " ������ ���� �̤� " << minBatMon - currentMon << " ���� �� ������ �̤�" << endl;
			system("pause");
			return 0;
		}
		else if (currentMon >= goalMon) {
			cout << "�� ���!!! "<<currentMon/10000 <<"�� " << currentMon%10000<<" ���� ����! ������! ���Ҿ� ���� ���� ������ ����!" << endl;
			system("pause");
			return 0;
		}
		if (remainCardNum <= 1) {
			cout << "��?? ���� ī�尡 ����?" << endl << "�� �� ���ұ�? 1. ���� �ѹ������� 0. ���� �ƴϾ�... �׸��ҷ� ";
			cin >> oneMore;
			while (oneMore <0 || oneMore >1) {
				cout << "0,1 �߿� ���"; 
				cin >> oneMore;
			}
			if (oneMore == 1) {
				allCard = shuffleCard(allCard);
				cnt = 0;
				remainCardNum = 52;
				continue;
			}
			else if (oneMore==0) {
				system("pause");
				return 0;
			}
		}
		
		cout << "����ұ�?\n	 1. ���� �̹����߸��� ��¥ ���� ����! �帧 �Ծ�!  0. ���� ������ ���� �ƴѵ� (��������)" << endl;
		cin >> doYouWantKeepGoing;

		while (doYouWantKeepGoing<0 ||doYouWantKeepGoing >1) {
			cout << "0,1 �߿� ���  "; 
			cin >> doYouWantKeepGoing;
		}
		if (!doYouWantKeepGoing) {
			system("pause");
			return 0;
		}
	}
	//system("pause");
	return 0;
}

Card* init(Card card[MAX]) {	//ī�带 ���������� �����Ѵ�.
	int cardIDX = 0;
	for (int i = 0; i < SHAPENUM; i++) {
		for (int j = 0; j < NUMBER; j++) {
			card[cardIDX].shp = cardShape[i];
			card[cardIDX].num = cardNum[j];
			cardIDX++;
		}
		cout << endl;
	}
	return card;
}

Card* shuffleCard(Card card[MAX]) {
	srand(time(NULL));
	Card tmp;
	int idx1 = 0, idx2 = 0;
	for (int i = 0; i < 1234; i++) {
		idx1 = rand() % 52;
		idx2 = rand() % 52;
		tmp = card[idx1];
		card[idx1] = card[idx2];
		card[idx2] = tmp;
	}
	return card;
}
void printALLCard(Card card[MAX]) {
	for (int i = 0; i < MAX; i++) {
		cout << card[i].shp << card[i].num << "\t";
		if (i % 13 == 12) { cout << endl; }
	}
	cout << endl << endl;
}
Card SelectCard(Card card[MAX]) {
	Card selectCard;
	selectCard = card[cnt++];

	return selectCard;
}

bool battingOK(int batting, int curYourMon, int minBatMon) {
	bool itsok=true;
	if (batting < minBatMon){
		cout << "���ñݾ��� �ʹ� ������?" << endl;
		itsok = false;
	}
	if (batting > curYourMon) {
		cout << "��... ���� ���ڸ�����...;;" << endl;
		itsok = false;
	}
	
	return itsok;
}

bool isItBetween2Card(Card card1, Card card2, Card pCard) {
	bool yesItIs;
	//�� ī�� ���� ������ �����̴� ������
	if ((pCard.num >card1.num && pCard.num < card2.num) || (pCard.num >card2.num && pCard.num < card1.num)) {
		yesItIs = true;
	}
	else {	
		yesItIs = false;
	}
	 
	return yesItIs;
}

void printCard(Card card) {
	cout << card.shp;
	if (card.num == 1) {
		cout << "A" << endl;
	}
	else if (card.num == 11) {
		cout << "J" << endl;
	}
	else if (card.num == 12) {
		cout << "Q" << endl;
	}
	else if (card.num == 13) {
		cout << "K" << endl;
	}
	else {
		cout << card.num << endl;
	}
}
