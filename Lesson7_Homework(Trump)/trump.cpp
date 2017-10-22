
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

Card *init(Card card[MAX]);				//배열에 순차적으로 카드를 세팅 한다.  ->  하트1, 하트2, ... , 클로버J, 클로버Q, 클로버K
Card *shuffleCard(Card card[MAX]);		//init 에서 초기화 한 카드 배열을 섞는다.
void printALLCard(Card card[MAX]);		//잘 섞였는지 확인하기 위해 카드를 모두 출력하는 함수이다. 실제 게임을 실행하면 출력하지는 않는다.
Card SelectCard(Card card[MAX]);		//카드를 순서대로 뒤집는다.
bool battingOK(int battig, int curYourMon,  int minBatMon);		//유저가 건 배팅금액이 유효한지(최보 배팅금액보다 크거나 같은지, 그리고 현재 갖고 있는 금액보다 작거나 같은지 ) 검사하는 함수이다
bool isItBetween2Card(Card card1, Card card2, Card pCard);		//세번째로 뒤집은 카드의 숫자가 앞서 뒤집은 두장의 카드 숫자 사이의 값인지 확인하는 함수이다
void printCard(Card card);				// 뒤집은 카드를 출력하는 함수로, 숫자가 "1일 때 A, 11일 때 J, 12일 때 Q, 13일 때 K, 나머지는 숫자"를 출력하게 한다.

int main() {
	srand(time(NULL));
	Card *allCard = new Card[MAX];
	int isPlay;
	int currentMon=4000, goalMon =20000;// 현재 유저가 보유한 금액과 목표금액
	int minBatMon = 500;				// 최소 배팅 가능 금액
	int batting;						// 유저가 배팅할 금액
	int remainCardNum = 52;				// 남은 카드 개수
	Card selectCard1, selectCard2, selectPCard;		//뒤집은 카드를 저장할 변수 (한 턴에 총 세 장) 
	int doYouWantKeepGoing;				// 한 턴이 끝나고 나면 계속할지 물어본다.
	int oneMore;						//51장의 카드를 모두 뒤집엇을 때 한번 더 할건지 물어본다
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
	while (isPlay<0 || isPlay>1) {	//0,1 말고 다른 걸 입력하면 다시 입력받기
		cout << "0, 1 중에 골라   ";
		cin >> isPlay;
	}
	while (isPlay) {		//isPlay가 true(게임 진행 ㄱㄱ)인 동안 이 영역을 실행
		system("cls");
		cout << "============================================ TRUMP ============================================" << endl;
		cout << "\t\t배팅 금액은 만원 단위. 최소 배팅금액은" << minBatMon << "만원" << endl;
		if (currentMon > 9999) {	//억 단위 출력
			cout << "\t\t님 남은 돈 : " << currentMon/10000 << "억 "<< currentMon%10000 <<"만원" << "\t\t\t\t" << "남아있는 카드장수 : " << remainCardNum << " 장" << endl;
		}
		else {						//만 단위 출력
			cout << "\t\t님 남은 돈 : " << currentMon << "만원" << "\t\t\t\t" << "남아있는 카드장수 : " << remainCardNum << " 장" << endl;
		}
		cout << "===============================================================================================" << endl;
		cout << "뒤집은 두장의 카드는?? 두둔" << endl;
		selectCard1 = SelectCard(allCard);		//첫번째 카드 뒤집음
		remainCardNum--;						//남은 카드 개수 감소
		selectCard2 = SelectCard(allCard);		//두번째 카드 뒤집음
		remainCardNum--;						//남은 카드 개수 감소
		
		printCard(selectCard1);					//뒤집은 카드를 이뿌게 출력
		printCard(selectCard2);					//뒤집은 카드를 이뿌게 출력
		cout << "얼마를 배팅할까??(만원단위)\t"; 
		cin >> batting;
		
		while (!battingOK(batting, currentMon, minBatMon)) {		//배팅금액이 유효하지 않은 동안에는 배팅금액을 다시 입력 받음
			cout << "아 배팅금액을 잘못 정했네;; 다시!(만원단위)\t";		
			cin >> batting;
		}
		currentMon -= batting;					//현재 갖고 있는 금액에서 배팅 금액 빼기
		
		cout << "내 카드는...?? 두둔!\t" ;
		selectPCard = SelectCard(allCard);		//세번째 카드를 뒤집음
		remainCardNum--;						//남은 카드 개수 감소
		printCard(selectPCard);					//뒤집은 카드를 이뿌게 출력
		
		if (isItBetween2Card(selectCard1, selectCard2, selectPCard)) {		//세번째 카드의 숫자가 앞의 두장의 카드의 숫자 사이에 값인지 확인하고, 만약 사이값이라면 배팅금액의 2배를 현재 보유한 금액에 더한다.
			currentMon += batting * 2;
			cout << "아싸! 돈 두배 땄다! 유후~!" << endl << batting * 2 << " 만원 따서 현재 " << currentMon << " 만원 있음"<<endl;
		}
		else {
			cout << "!!!! 아... 안돼 T^T 내돈" << endl << batting << "만원 잃어서 현재 " << currentMon << "만원 있음" << endl;
		}
		
		if (currentMon <=0) {		//만약 유저가 파산했다면 게임종료
			cout << "으ㅇ아아아ㅓ아어ㅏ어 T^T 파산이라닛! 파산이라니이이잇!" << endl;
			system("pause");
			return 0;
		}
		if (currentMon < minBatMon) {	//파산은 아니지만 유저가 보유한 금액이 최소금액보다 적으면 게임 종료
			cout << "......최소금액인 " << minBatMon << " 만원이 없어 ㅜㅠ " << minBatMon - currentMon << " 만원 이 부족해 ㅜㅠ" << endl;
			system("pause");
			return 0;
		}
		else if (currentMon >= goalMon) {	//유저가 보유한 금액이 목표금액 이상을 달성하면 게임 종료!
			cout << "헐 대박!!! "<<currentMon/10000 <<"억 " << currentMon%10000<<" 만원 땄어! 으어어엉! 좋았어 이제 빚을 갚으러 가자!" << endl;
			system("pause");
			return 0;
		}
		if (remainCardNum <= 1) {		//만약 모든 카드를 다 뒤집어서 더이상 게임을 진행할 수 없을 때, 유저에게 카드 섞고 한번 더 할지 물어본다.
			cout << "어?? 남은 카드가 없네?" << endl << "한 판 더할까? 1. ㅇㅇ 한번더하자 0. ㄴㄴ 아니야... 그만할래 ";
			cin >> oneMore;
			while (oneMore <0 || oneMore >1) {
				cout << "0,1 중에 골라"; 
				cin >> oneMore;
			}
			if (oneMore == 1) {		//만약 한 번 더 한다고 하면 카드를 한번더 섞고, 초기화 해야 하는 값들은 초기화한다
				allCard = shuffleCard(allCard);
				cnt = 0;
				remainCardNum = 52;
				continue;
			}
			else if (oneMore==0) {	//그만한다고 하면 게임을 종료한다.
				system("pause");
				return 0;
			}
		}
		//한 턴이 끝났으므로 다음 턴을 계속 할 지 물어본다.
		cout << "계속할까?\n	 1. ㅇㅇ 이번에야말로 진짜 느낌 좋아! 흐름 왔어!  0. ㄴㄴ 오늘은 날이 아닌듯 (절레절레)" << endl;
		cin >> doYouWantKeepGoing;

		while (doYouWantKeepGoing<0 ||doYouWantKeepGoing >1) {
			cout << "0,1 중에 골라  "; 
			cin >> doYouWantKeepGoing;
		}
		if (!doYouWantKeepGoing) {		//그만 한다고 하면 게임 종료
			system("pause");
			return 0;
		}
	}
	
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
