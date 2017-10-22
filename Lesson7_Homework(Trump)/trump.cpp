
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

Card *init(Card card[MAX]);				//�迭�� ���������� ī�带 ���� �Ѵ�.  ->  ��Ʈ1, ��Ʈ2, ... , Ŭ�ι�J, Ŭ�ι�Q, Ŭ�ι�K
Card *shuffleCard(Card card[MAX]);		//init ���� �ʱ�ȭ �� ī�� �迭�� ���´�.
void printALLCard(Card card[MAX]);		//�� �������� Ȯ���ϱ� ���� ī�带 ��� ����ϴ� �Լ��̴�. ���� ������ �����ϸ� ��������� �ʴ´�.
Card SelectCard(Card card[MAX]);		//ī�带 ������� �����´�.
bool battingOK(int battig, int curYourMon,  int minBatMon);		//������ �� ���ñݾ��� ��ȿ����(�ֺ� ���ñݾ׺��� ũ�ų� ������, �׸��� ���� ���� �ִ� �ݾ׺��� �۰ų� ������ ) �˻��ϴ� �Լ��̴�
bool isItBetween2Card(Card card1, Card card2, Card pCard);		//����°�� ������ ī���� ���ڰ� �ռ� ������ ������ ī�� ���� ������ ������ Ȯ���ϴ� �Լ��̴�
void printCard(Card card);				// ������ ī�带 ����ϴ� �Լ���, ���ڰ� "1�� �� A, 11�� �� J, 12�� �� Q, 13�� �� K, �������� ����"�� ����ϰ� �Ѵ�.

int main() {
	srand(time(NULL));
	Card *allCard = new Card[MAX];
	int isPlay;
	int currentMon=4000, goalMon =20000;// ���� ������ ������ �ݾװ� ��ǥ�ݾ�
	int minBatMon = 500;				// �ּ� ���� ���� �ݾ�
	int batting;						// ������ ������ �ݾ�
	int remainCardNum = 52;				// ���� ī�� ����
	Card selectCard1, selectCard2, selectPCard;		//������ ī�带 ������ ���� (�� �Ͽ� �� �� ��) 
	int doYouWantKeepGoing;				// �� ���� ������ ���� ������� �����.
	int oneMore;						//51���� ī�带 ��� �������� �� �ѹ� �� �Ұ��� �����
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
	while (isPlay<0 || isPlay>1) {	//0,1 ���� �ٸ� �� �Է��ϸ� �ٽ� �Է¹ޱ�
		cout << "0, 1 �߿� ���   ";
		cin >> isPlay;
	}
	while (isPlay) {		//isPlay�� true(���� ���� ����)�� ���� �� ������ ����
		system("cls");
		cout << "============================================ TRUMP ============================================" << endl;
		cout << "\t\t���� �ݾ��� ���� ����. �ּ� ���ñݾ���" << minBatMon << "����" << endl;
		if (currentMon > 9999) {	//�� ���� ���
			cout << "\t\t�� ���� �� : " << currentMon/10000 << "�� "<< currentMon%10000 <<"����" << "\t\t\t\t" << "�����ִ� ī����� : " << remainCardNum << " ��" << endl;
		}
		else {						//�� ���� ���
			cout << "\t\t�� ���� �� : " << currentMon << "����" << "\t\t\t\t" << "�����ִ� ī����� : " << remainCardNum << " ��" << endl;
		}
		cout << "===============================================================================================" << endl;
		cout << "������ ������ ī���?? �ε�" << endl;
		selectCard1 = SelectCard(allCard);		//ù��° ī�� ������
		remainCardNum--;						//���� ī�� ���� ����
		selectCard2 = SelectCard(allCard);		//�ι�° ī�� ������
		remainCardNum--;						//���� ī�� ���� ����
		
		printCard(selectCard1);					//������ ī�带 �̻Ѱ� ���
		printCard(selectCard2);					//������ ī�带 �̻Ѱ� ���
		cout << "�󸶸� �����ұ�??(��������)\t"; 
		cin >> batting;
		
		while (!battingOK(batting, currentMon, minBatMon)) {		//���ñݾ��� ��ȿ���� ���� ���ȿ��� ���ñݾ��� �ٽ� �Է� ����
			cout << "�� ���ñݾ��� �߸� ���߳�;; �ٽ�!(��������)\t";		
			cin >> batting;
		}
		currentMon -= batting;					//���� ���� �ִ� �ݾ׿��� ���� �ݾ� ����
		
		cout << "�� ī���...?? �ε�!\t" ;
		selectPCard = SelectCard(allCard);		//����° ī�带 ������
		remainCardNum--;						//���� ī�� ���� ����
		printCard(selectPCard);					//������ ī�带 �̻Ѱ� ���
		
		if (isItBetween2Card(selectCard1, selectCard2, selectPCard)) {		//����° ī���� ���ڰ� ���� ������ ī���� ���� ���̿� ������ Ȯ���ϰ�, ���� ���̰��̶�� ���ñݾ��� 2�踦 ���� ������ �ݾ׿� ���Ѵ�.
			currentMon += batting * 2;
			cout << "�ƽ�! �� �ι� ����! ����~!" << endl << batting * 2 << " ���� ���� ���� " << currentMon << " ���� ����"<<endl;
		}
		else {
			cout << "!!!! ��... �ȵ� T^T ����" << endl << batting << "���� �Ҿ ���� " << currentMon << "���� ����" << endl;
		}
		
		if (currentMon <=0) {		//���� ������ �Ļ��ߴٸ� ��������
			cout << "�����ƾƾƤþƾ�� T^T �Ļ��̶��! �Ļ��̶��������!" << endl;
			system("pause");
			return 0;
		}
		if (currentMon < minBatMon) {	//�Ļ��� �ƴ����� ������ ������ �ݾ��� �ּұݾ׺��� ������ ���� ����
			cout << "......�ּұݾ��� " << minBatMon << " ������ ���� �̤� " << minBatMon - currentMon << " ���� �� ������ �̤�" << endl;
			system("pause");
			return 0;
		}
		else if (currentMon >= goalMon) {	//������ ������ �ݾ��� ��ǥ�ݾ� �̻��� �޼��ϸ� ���� ����!
			cout << "�� ���!!! "<<currentMon/10000 <<"�� " << currentMon%10000<<" ���� ����! ������! ���Ҿ� ���� ���� ������ ����!" << endl;
			system("pause");
			return 0;
		}
		if (remainCardNum <= 1) {		//���� ��� ī�带 �� ����� ���̻� ������ ������ �� ���� ��, �������� ī�� ���� �ѹ� �� ���� �����.
			cout << "��?? ���� ī�尡 ����?" << endl << "�� �� ���ұ�? 1. ���� �ѹ������� 0. ���� �ƴϾ�... �׸��ҷ� ";
			cin >> oneMore;
			while (oneMore <0 || oneMore >1) {
				cout << "0,1 �߿� ���"; 
				cin >> oneMore;
			}
			if (oneMore == 1) {		//���� �� �� �� �Ѵٰ� �ϸ� ī�带 �ѹ��� ����, �ʱ�ȭ �ؾ� �ϴ� ������ �ʱ�ȭ�Ѵ�
				allCard = shuffleCard(allCard);
				cnt = 0;
				remainCardNum = 52;
				continue;
			}
			else if (oneMore==0) {	//�׸��Ѵٰ� �ϸ� ������ �����Ѵ�.
				system("pause");
				return 0;
			}
		}
		//�� ���� �������Ƿ� ���� ���� ��� �� �� �����.
		cout << "����ұ�?\n	 1. ���� �̹����߸��� ��¥ ���� ����! �帧 �Ծ�!  0. ���� ������ ���� �ƴѵ� (��������)" << endl;
		cin >> doYouWantKeepGoing;

		while (doYouWantKeepGoing<0 ||doYouWantKeepGoing >1) {
			cout << "0,1 �߿� ���  "; 
			cin >> doYouWantKeepGoing;
		}
		if (!doYouWantKeepGoing) {		//�׸� �Ѵٰ� �ϸ� ���� ����
			system("pause");
			return 0;
		}
	}
	
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
