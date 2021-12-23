#include<stdio.h>
#include<stdlib.h>
#include"project.h"
#define START_ID 20100000

void query(void);
void update(void);

FILE *fp;
char c;
struct project rec;

int main(int argc, char *argv[])
{
	int input;

	if(argc != 2) {
		fprintf(stderr, "사용법: %s 파일이름\n", argv[0]);
		exit(1);
	}
	
	if((fp = fopen(argv[1], "rb+")) == NULL) {
		if((fp = fopen(argv[1], "wb+")) == NULL) {
			fprintf(stderr, "파일열기 오류\n");
			exit(1);
		}
	}
	printf("학생용 프로그램\n");
	while(1) {
		printf("========  MENU  ========\n\n");
		printf("1. 정보확인\n");
		printf("2. 정보수정\n");
		printf("3. 프로그램 종료\n\n");
		printf("========================\n\n");
		printf("선택: ");
		scanf("%d", &input);

		switch(input) {
			case 1: query();
				break;
			case 2: update();
				break;
			case 3: printf("프로그램 종료\n");
				return 0;
			default: printf("잘못된 입력\n");
				 break;
		}
	}
}

void query(void)
{
	int id;

	do {
		if(c == 'Y') printf("계속입력\n");
		printf("검색할 학번 입력: ");
		if(scanf("%d", &id) == 1) {
			if((id >= 10000000) && (id < 100000000)) {
				fseek(fp, (id - START_ID)* sizeof(rec), SEEK_SET);
				if((fread(&rec, sizeof(rec), 1, fp) > 0)&& (rec.id != 0)) {
					printf("==========  정보  ==========\n");
					if((rec.graduate == 0) && (rec.registration == 0) && (rec.taketime == 0)) {
						printf("학번: %d, 이름:%s , 전화번호: %s, 이메일: %s, 주소: %s, 소속학과: %s, 학년: %d, 장학금 총액: %d, 다전공 내용: %s, 졸업여부:졸업, 등록여부:등록취소, 휴학확인:휴학\n", rec.id, rec.name, rec.phone, rec.mail, rec.address, rec.major, rec.grade, rec.scholarship, rec.etcmajor);
					}
					else if((rec.graduate == 0) && (rec.registration == 0) && (rec.taketime == 1)) {
						printf("학번: %d, 이름:%s , 전화번호: %s, 이메일: %s, 주소: %s, 소속학과: %s, 학년: %d, 장학금 총액: %d, 다전공 내용: %s, 졸업여부:졸업, 등록여부:등록취소, 휴학확인:재학\n", rec.id, rec.name, rec.phone, rec.mail, rec.address, rec.major, rec.grade, rec.scholarship, rec.etcmajor);
					}
					else if((rec.graduate == 0) && (rec.registration == 1) && (rec.taketime == 1)) {
						printf("학번: %d, 이름:%s , 전화번호: %s, 이메일: %s, 주소: %s, 소속학과: %s, 학년: %d, 장학금 총액: %d, 다전공 내용: %s, 졸업여부:졸업, 등록여부:등록, 휴학확인:재학\n", rec.id, rec.name, rec.phone, rec.mail, rec.address, rec.major, rec.grade, rec.scholarship, rec.etcmajor);
					}
					else if((rec.graduate == 1) && (rec.registration == 1) && (rec.taketime == 1)) {
						printf("학번: %d, 이름:%s , 전화번호: %s, 이메일: %s, 주소: %s, 소속학과: %s, 학년: %d, 장학금 총액: %d, 다전공 내용: %s, 졸업여부:재학, 등록여부:등록, 휴학확인:재학\n", rec.id, rec.name, rec.phone, rec.mail, rec.address, rec.major, rec.grade, rec.scholarship, rec.etcmajor);
					}
					else if((rec.graduate == 0) && (rec.registration == 1) && (rec.taketime == 0)) {
						printf("학번: %d, 이름:%s , 전화번호: %s, 이메일: %s, 주소: %s, 소속학과: %s, 학년: %d, 장학금 총액: %d, 다전공 내용: %s, 졸업여부:졸업, 등록여부:등록, 휴학확인:휴학\n", rec.id, rec.name, rec.phone, rec.mail, rec.address, rec.major, rec.grade, rec.scholarship, rec.etcmajor);
					}
					else if((rec.graduate == 1) && (rec.registration == 0) && (rec.taketime == 0)) {
						printf("학번: %d, 이름:%s , 전화번호: %s, 이메일: %s, 주소: %s, 소속학과: %s, 학년: %d, 장학금 총액: %d, 다전공 내용: %s, 졸업여부:재학, 등록여부:등록취소, 휴학확인:휴학\n", rec.id, rec.name, rec.phone, rec.mail, rec.address, rec.major, rec.grade, rec.scholarship, rec.etcmajor);
					}
					else if((rec.graduate == 1) && (rec.registration == 1) && (rec.taketime == 0)) {
						printf("학번: %d, 이름:%s , 전화번호: %s, 이메일: %s, 주소: %s, 소속학과: %s, 학년: %d, 장학금 총액: %d, 다전공 내용: %s, 졸업여부:재학, 등록여부:등록, 휴학확인:휴학\n", rec.id, rec.name, rec.phone, rec.mail, rec.address, rec.major, rec.grade, rec.scholarship, rec.etcmajor);
					}
					else printf("학번: %d, 이름:%s , 전화번호: %s, 이메일: %s, 주소: %s, 소속학과: %s, 학년: %d, 장학금 총액: %d, 다전공 내용: %s, 졸업여부:재학, 등록여부:등록취소, 휴학확인:재학\n", rec.id, rec.name, rec.phone, rec.mail, rec.address, rec.major, rec.grade, rec.scholarship, rec.etcmajor);
					}
				else {
					printf("학번 %d 없음. 다시 입력하세요\n", id);
					c = 'Y';
				}
			}
			else {
				printf("학번 8자리를 입력하세요\n");
				c = 'Y';
			}
		}
		else {
			printf("입력오류. 다시 입력하세요\n");
			c = 'Y';
		}
		printf("계속하시겠습니까?(Y/N): ");
		scanf(" %c", &c);
	}
	while(c == 'Y');
}

void update(void)
{
	int id;
	int select;

	do {
		printf("수정할 학생 학번 입력: ");
		if(scanf("%d", &id) == 1) {
			if((id >= 10000000) && (id < 100000000)) {
				fseek(fp, (id - START_ID)* sizeof(rec), SEEK_SET);
				if((fread(&rec, sizeof(rec), 1, fp) > 0) && (rec.id != 0)) {
					printf("1.전화번호, 2.이메일, 3.주소 : ");
					scanf("%d", &select);
					if(select == 1) {
						printf("새로운 전화번호 입력: ");
						scanf(" %s", rec.phone);
						fseek(fp, -sizeof(rec), SEEK_CUR);
						fwrite(&rec, sizeof(rec), 1, fp);
						fflush(fp);
						printf("수정완료\n");
					}
					else if(select == 2) {
						printf("새로운 이메일 입력: ");
						scanf(" %s", rec.mail);
						fseek(fp, -sizeof(rec), SEEK_CUR);
						fwrite(&rec, sizeof(rec), 1, fp);
						fflush(fp);
						printf("수정완료\n");
					}
					else if(select == 3) {
						printf("새로운 주소 입력: ");
						scanf(" %s", rec.address);
						fseek(fp, -sizeof(rec), SEEK_CUR);
						fwrite(&rec, sizeof(rec), 1, fp);
						fflush(fp);
						printf("수정완료\n");
					}
					else {
						printf("잘못된 입력\n");
					}
				}
				else {
					printf("입력오류\n");
				}
			}
			else {
				printf("학번 8자리를 입력하세요\n");
			}
		}
		else {
			printf("학번 %d 없음\n", id);
		}
		printf("계속하시겠습니까?(Y/N): ");
		scanf(" %c", &c);
	}
	while(c == 'Y');
}
