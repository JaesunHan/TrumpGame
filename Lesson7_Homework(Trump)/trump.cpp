
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
char *cardShape[SHAPENUM] = { "♡","◇","♠","♣" };
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

	cout << "내이름은 트럼프. (도날드 그분 아님 주의. 부모님이 트럼프로 크게 한탕하라는 의미로다가 지어주신 이름임)";
	cout << endl << "우리 집안에는 도박꾼의 피가 흐르고 있다." << endl;
	cout << "카지노를 제집드나들듯 하기를 어언 1년 3개월 18일 째." << endl << "당연스럽게도 내게는 빚이 있다. 2억... T^T" << endl;
	cout << "나는 오늘의 도박에 모든 것을 걸었다!" << endl << "오늘을 위해 빚을 4천만원 냄 ㅜㅠ" << endl;
	cout << "이 4천만원을 2억으로 불려가겠어!" << endl << "오늘이야말로 한탕제대로 해보고 가겠다!" << endl << endl;
	cout << "==================================================================" << endl;
	cout << "\t\t#미션 : 4천만원을 2억으로 불리기" << endl;
	cout << "==================================================================" << endl;
	cout << "카지노에 입장하시겠습니까?" << endl;
	cout << "1. ㅇㅇ ㄱㄱ \t 0. ㄴㄴ 잠만. 아직 마음의 준비가 덜됨;;" << endl;
	cin >> isPlay;
	while (isPlay<0 || isPlay>1) {
		cout << "0, 1 중에 골라   ";
		cin >> isPlay;
	}
	while (isPlay) {
		system("cls");
		cout << "============================================ TRUMP ============================================" << endl;
		cout << "\t\t배팅 금액은 만원 단위. 최소 배팅금액은" << minBatMon << "만원" << endl;
		if (currentMon > 9999) {	//역단위 출력
			cout << "\t\t님 남은 돈 : " << currentMon/10000 << "억 "<< currentMon%10000 <<"만원" << "\t\t\t\t" << "남아있는 카드장수 : " << remainCardNum << " 장" << endl;
		}
		else {						//만단위 출력
			cout << "\t\t님 남은 돈 : " << currentMon << "만원" << "\t\t\t\t" << "남아있는 카드장수 : " << remainCardNum << " 장" << endl;
		}
		cout << "===============================================================================================" << endl;
		cout << "뒤집은 두장의 카드는?? 두둔" << endl;
		selectCard1 = SelectCard(allCard);
		remainCardNum--;
		selectCard2 = SelectCard(allCard);
		remainCardNum--;
		
		printCard(selectCard1);
		printCard(selectCard2);
		cout << "얼마를 배팅할까??(만원단위)\t"; 
		cin >> batting;
		
		while (!battingOK(batting, currentMon, minBatMon)) {
			cout << "아 배팅금액을 잘못 정했네;; 다시!(만원단위)\t";
			cin >> batting;
		}
		currentMon -= batting;
		
		cout << "내 카드는...?? 두둔!\t" ;
		selectPCard = SelectCard(allCard);
		remainCardNum--;
		printCard(selectPCard);
		
		if (isItBetween2Card(selectCard1, selectCard2, selectPCard)) {
			currentMon += batting * 2;
			cout << "아싸! 돈 두배 땄다! 유후~!" << endl << batting * 2 << " 만원 따서 현재 " << currentMon << " 만원 있음"<<endl;
		}
		else {
			cout << "!!!! 아... 안돼 T^T 내돈" << endl << batting << "만원 잃어서 현재 " << currentMon << "만원 있음" << endl;
		}
		
		if (currentMon <=0) {
			cout << "으ㅇ아아아ㅓ아어ㅏ어 T^T 파산이라닛! 파산이라니이이잇!" << endl;
			system("pause");
			return 0;
		}
		if (currentMon < minBatMon) {
			cout << "......최소금액인 " << minBatMon << " 만원이 없어 ㅜㅠ " << minBatMon - currentMon << " 만원 이 부족해 ㅜㅠ" << endl;
			system("pause");
			return 0;
		}
		else if (currentMon >= goalMon) {
			cout << "헐 대박!!! "<<currentMon/10000 <<"억 " << currentMon%10000<<" 만원 땄어! 으어어엉! 좋았어 이제 빚을 갚으러 가자!" << endl;
			system("pause");
			return 0;
		}
		if (remainCardNum <= 1) {
			cout << "어?? 남은 카드가 없네?" << endl << "한 판 더할까? 1. ㅇㅇ 한번더하자 0. ㄴㄴ 아니야... 그만할래 ";
			cin >> oneMore;
			while (oneMore <0 || oneMore >1) {
				cout << "0,1 중에 골라"; 
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
		
		cout << "계속할까?\n	 1. ㅇㅇ 이번에야말로 진짜 느낌 좋아! 흐름 왔어!  0. ㄴㄴ 오늘은 날이 아닌듯 (절레절레)" << endl;
		cin >> doYouWantKeepGoing;

		while (doYouWantKeepGoing<0 ||doYouWantKeepGoing >1) {
			cout << "0,1 중에 골라  "; 
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

Card* init(Card card[MAX]) {	//카드를 순차적으로 세팅한다.
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
		cout << "배팅금액이 너무 적은데?" << endl;
		itsok = false;
	}
	if (batting > curYourMon) {
		cout << "아... 돈이 모자르구나...;;" << endl;
		itsok = false;
	}
	
	return itsok;
}

bool isItBetween2Card(Card card1, Card card2, Card pCard) {
	bool yesItIs;
	//두 카드 숫자 사이의 숫자이당 ㅎㅎㅎ
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
