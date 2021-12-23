#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"project.h"
#define START_ID 20100000

void regist(void);
void query1(void);
void query2(void);
void update1(void);
void update2(void);

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
	printf("**** 교직원용 프로그램 ****\n\n");
	while(1) {
		printf("========  MENU  ========\n\n");
		printf("1. 학생등록\n");
		printf("2. 학생 검색\n");
		printf("3. 학과별 학생검색\n");
		printf("4. 재학여부 확인 및 수정\n");
		printf("5. 정보수정\n");
		printf("6. 프로그램 종료\n\n");
		printf("========================\n");
		printf("선택: ");
		scanf("%d", &input);

		switch(input) {
			case 1: regist();
				break;
			case 2: query1();
				break;
			case 3: query2();
				break;
			case 4: update1();
				break;
			case 5: update2();
				break;
			case 6: printf("프로그램 종료\n");
				return 0;
			default: printf("잘못된 입력\n");
				 break;
		}
	}
}

void regist()
{
	do {
		printf("학번(8자리), 이름, 전화번호, 이메일, 주소, 소속학과, 학년, 장학금 총액, 다전공 내용, 졸업여부(0.졸업/1.재학), 등록여부(0.등록취소/1.등록), 휴학여부(0.휴학/1.재학) / *12항목*\n");
		while(scanf("%d %s %s %s %s %s %d %d %s %d %d %d", &rec.id, rec.name, rec.phone, rec.mail, rec.address, rec.major, &rec.grade, &rec.scholarship, rec.etcmajor, &rec.graduate, &rec.registration, &rec.taketime) == 12) {
			fseek(fp, (rec.id - START_ID)* sizeof(rec), SEEK_SET);
			if(fread(&rec.id, sizeof(rec), 1,fp) == 0) {
				if((rec.id >= 20100000) && (rec.id <= 99999999)) {
					if(((rec.graduate == 0) || (rec.graduate == 1)) && ((rec.registration == 0) || (rec.registration == 1)) && ((rec.taketime == 0) || (rec.taketime == 1))) {
						fseek(fp, (rec.id -START_ID)* sizeof(rec), SEEK_SET);
						fwrite(&rec, sizeof(rec), 1, fp);
						fflush(fp);
					}
					else {
						printf("졸업여부,등록여부,휴학여부는 0또는 1로 입력하세요\n");
					}
				}
				else {
					printf("학번 8자리를 입력하세요\n");
				}
			}
			else {
				printf("이미 등록된 학번입니다. 다른 학번을 이용하세요.\n");
			}
		}
		printf("계속하시겠습니까?(Y/N): ");
		scanf(" %c", &c);
	}
	while(c == 'Y');
}
void query1(void)
{
	int select;
	int count;
	int id;
	char name[20];
	char phone[20];
	char mail[20];
	char c;

	do {
		printf("검색방법\n");
		printf("1.학번, 2.이름, 3.전화번호, 4.이메일: ");
		scanf("%d", &select);

		if(select == 1) {
			printf("검색할 학번 입력: ");
			scanf("%d", &id);
			printf("==========  정보  ==========\n");
			if((id >= 20100000) && (id < 100000000)) {
				fseek(fp, (id - START_ID)* sizeof(rec), SEEK_SET);
				if((fread(&rec, sizeof(rec), 1, fp) > 0) && (rec.id != 0)) printf("학번:%d, 이름:%s, 전화번호:%s, 이메일:%s, 주소:%s, 소속학과:%s, 학년:%d, 장학금 총액:%d, 다전공 내용:%s\n", rec.id, rec.name, rec.phone, rec.mail, rec.address, rec.major, rec.grade, rec.scholarship, rec.etcmajor);
				else {
					printf("학번없음: %d\n", id);
					c = 'Y';
				}
			}
			else {
				printf("입력오류. 학번 8자리를 입력하세요\n");
				c = 'Y';
			}
		}
		else if(select == 2) {
			count = 0;
			printf("검색할 이름 입력: ");
			scanf(" %s", name);
			printf("==========  정보  ==========\n");
			fseek(fp, 0, SEEK_SET);
			while(fread(&rec, sizeof(rec), 1, fp) > 0) {
				if((strcmp(rec.name, name)) == 0) {
					printf("학번:%d, 이름:%s, 전화번호:%s, 이메일:%s, 주소:%s, 소속학과:%s, 학년:%d, 장학금 총액:%d, 다전공 내용:%s\n", rec.id, rec.name, rec.phone, rec.mail, rec.address, rec.major, rec.grade, rec.scholarship, rec.etcmajor);
					count += 1;
				}
			}
			if(count == 0) {
				printf("이름: %s 없음\n", name);
				c = 'Y';
			}

		}
		else if(select == 3) {
			count = 0;
			printf("검색할 전화번호 입력: ");
			scanf(" %s", phone);
			printf("==========  정보  ==========\n");
			fseek(fp, 0, SEEK_SET);
			while(fread(&rec, sizeof(rec), 1, fp) > 0) {
				if((strcmp(rec.phone, phone)) == 0) {
					printf("학번:%d, 이름:%s, 전화번호:%s, 이메일:%s, 주소:%s, 소속학과:%s, 학년:%d, 장학금 총액:%d, 다전공 내용:%s\n", rec.id, rec.name, rec.phone, rec.mail, rec.address, rec.major, rec.grade, rec.scholarship, rec.etcmajor);
					count += 1;
				}
			}
			if(count == 0) {
				printf("전화번호: %s 없음\n", phone);
				c = 'Y';
			}

		}
		else if(select == 4) {
			count = 0;
			printf("검색할 이메일 입력: ");
			scanf(" %s", mail);
			printf("==========  정보  ==========\n");
			fseek(fp, 0, SEEK_SET);
			while(fread(&rec, sizeof(rec), 1, fp) > 0) {
				if((strcmp(rec.mail, mail)) == 0) {
					printf("학번:%d, 이름:%s, 전화번호:%s, 이메일:%s, 주소:%s, 소속학과:%s, 학년:%d, 장학금 총액:%d, 다전공 내용:%s\n", rec.id, rec.name, rec.phone, rec.mail, rec.address, rec.major, rec.grade, rec.scholarship, rec.etcmajor);
					count += 1;
				}
			}
			if(count == 0) {
				printf("이메일: %s 없음\n", mail);
				c = 'Y';
			}

		}
		else {
			printf("잘못된 입력\n");
		}
		printf("계속하시겠습니까?(Y/N): ");
		scanf(" %c", &c);
	}
	while(c == 'Y');
}

void query2(void)
{
	char pmajor[20];
	int count;

	do {
		count = 0;
		printf("학과별 검색\n");
		printf("검색할 학과를 입력하세요: ");
		scanf(" %s", pmajor);
		printf("==========  정보  ==========\n");
		
		fseek(fp, 0, SEEK_SET);
		while(fread(&rec, sizeof(rec), 1, fp) > 0) {
			if((strcmp(rec.major, pmajor)) == 0) {
				printf("학번:%d, 이름:%s, 전화번호:%s, 이메일:%s, 주소:%s, 소속학과:%s, 학년:%d, 장학금 총액:%d, 다전공 내용:%s\n", rec.id, rec.name, rec.phone, rec.mail, rec.address, rec.major, rec.grade, rec.scholarship, rec.etcmajor);
				count += 1;
			}
		}

		if(count == 0) {
			printf("학과: %s 없음\n", pmajor);
			c = 'Y';
		}
		printf("계속하시겠습니까?(Y/N): ");
		scanf(" %c", &c);
	}
	while(c == 'Y');
}

void update1(void)
{
	int id;
	int select;
	int choice;

	printf("1.재학확인, 2.재학수정 : ");
	scanf("%d", &select);
	if(select == 1) {
		do {
			printf("검색할 학생 학번입력: ");
			if(scanf(" %d", &id) == 1) {
				if((id >= 20100000) && (id <= 99999999)) {
					fseek(fp, (id - START_ID)* sizeof(rec), SEEK_SET);
					if((fread(&rec, sizeof(rec), 1, fp) > 0) && (rec.id != 0)) {
						if((rec.graduate == 0) && (rec.registration == 0) && (rec.taketime == 0)) printf("졸업여부:졸업 , 등록여부:등록취소, 휴학확인:휴학\n\n");
						else if((rec.graduate == 0) && (rec.registration == 0) && (rec.taketime == 1)) printf("졸업여부:졸업 , 등록여부:등록취소, 휴학확인:재학\n\n");
						else if((rec.graduate == 0) && (rec.registration == 1) && (rec.taketime == 1)) printf("졸업여부:졸업 , 등록여부:등록, 휴학확인:재학\n\n");
						else if((rec.graduate == 1) && (rec.registration == 1) && (rec.taketime == 1)) printf("졸업여부:재학 , 등록여부:등록, 휴학확인:재학\n\n");
						else if((rec.graduate == 0) && (rec.registration == 1) && (rec.taketime == 0)) printf("졸업여부:졸업 , 등록여부:등록, 휴학확인:휴학\n\n");
						else if((rec.graduate == 1) && (rec.registration == 0) && (rec.taketime == 0)) printf("졸업여부:재학 , 등록여부:등록취소, 휴학확인:휴학\n\n");
						else if((rec.graduate == 1) && (rec.registration == 1) && (rec.taketime == 0)) printf("졸업여부:재학 , 등록여부:등록, 휴학확인:휴학\n\n");
						else printf("졸업여부:재학 , 등록여부:등록취소, 휴학확인:재학\n\n");
					}
					else {
						printf("학번: %d 없음. 다시 입력하세요\n", id);
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
	else if(select == 2) {
		do {
			printf("수정할 학생 학번입력: ");
			if(scanf("%d", &id) == 1) {
				if((id >= 20100000) && (id <= 99999999)) {
					fseek(fp, (id - START_ID)* sizeof(rec), SEEK_SET);
					if((fread(&rec, sizeof(rec), 1, fp) > 0) && (rec.id != 0)) {
						printf("==========  정보  ==========\n");
						if((rec.graduate == 0) && (rec.registration == 0) && (rec.taketime == 0)) printf("졸업여부:졸업 , 등록여부:등록취소, 휴학확인:휴학\n\n");
						else if((rec.graduate == 0) && (rec.registration == 0) && (rec.taketime == 1)) printf("졸업여부:졸업 , 등록여부:등록취소, 휴학확인:재학\n\n");
						else if((rec.graduate == 0) && (rec.registration == 1) && (rec.taketime == 1)) printf("졸업여부:졸업 , 등록여부:등록, 휴학확인:재학\n\n");
						else if((rec.graduate == 1) && (rec.registration == 1) && (rec.taketime == 1)) printf("졸업여부:재학 , 등록여부:등록, 휴학확인:재학\n\n");
						else if((rec.graduate == 0) && (rec.registration == 1) && (rec.taketime == 0)) printf("졸업여부:졸업 , 등록여부:등록, 휴학확인:휴학\n\n");
						else if((rec.graduate == 1) && (rec.registration == 0) && (rec.taketime == 0)) printf("졸업여부:재학 , 등록여부:등록취소, 휴학확인:휴학\n\n");
						else if((rec.graduate == 1) && (rec.registration == 1) && (rec.taketime == 0)) printf("졸업여부:재학 , 등록여부:등록, 휴학확인:휴학\n\n");
						else printf("졸업여부:재학 , 등록여부:등록취소, 휴학확인:재학\n\n");
						
						printf("수정할 내용 선택\n");
						printf("1.졸업여부, 2.등록여부, 3.휴학여부 : ");
						scanf("%d", &choice);

						if(choice == 1) {
							printf("졸업여부 입력(0.졸업 / 1.재학) : ");
							scanf("%d", &rec.graduate);
							if((rec.graduate == 0) || (rec.graduate == 1)) {
								fseek(fp, -sizeof(rec), SEEK_CUR);
								fwrite(&rec, sizeof(rec), 1, fp);
								fflush(fp);
								printf("수정완료\n");
								printf("========== 수정 정보  ==========\n");
								fseek(fp, (id - START_ID)* sizeof(rec), SEEK_SET);
								fread(&rec, sizeof(rec), 1, fp);
								if((rec.graduate == 0) && (rec.registration == 0) && (rec.taketime == 0)) printf("졸업여부:졸업 , 등록여부:등록취소, 휴학확인:휴학\n\n");
								else if((rec.graduate == 0) && (rec.registration == 0) && (rec.taketime == 1)) printf("졸업여부:졸업 , 등록여부:등록취소, 휴학확인:재학\n\n");
								else if((rec.graduate == 0) && (rec.registration == 1) && (rec.taketime == 1)) printf("졸업여부:졸업 , 등록여부:등록, 휴학확인:재학\n\n");
								else if((rec.graduate == 1) && (rec.registration == 1) && (rec.taketime == 1)) printf("졸업여부:재학 , 등록여부:등록, 휴학확인:재학\n\n");
								else if((rec.graduate == 0) && (rec.registration == 1) && (rec.taketime == 0)) printf("졸업여부:졸업 , 등록여부:등록, 휴학확인:휴학\n\n");
								else if((rec.graduate == 1) && (rec.registration == 0) && (rec.taketime == 0)) printf("졸업여부:재학 , 등록여부:등록취소, 휴학확인:휴학\n\n");
								else if((rec.graduate == 1) && (rec.registration == 1) && (rec.taketime == 0)) printf("졸업여부:재학 , 등록여부:등록, 휴학확인:휴학\n\n");
								else printf("졸업여부:재학 , 등록여부:등록취소, 휴학확인:재학\n\n");
							}
							else {
								printf("0또는 1을 입력하세요\n");
								c = 'Y';
							}
						}
						else if(choice == 2) {
							printf("등록여부 입력(0.등록취소 / 1.등록) : ");
							scanf("%d", &rec.registration);
							if((rec.graduate == 0) || (rec.graduate == 1)) {
								fseek(fp, -sizeof(rec), SEEK_CUR);
								fwrite(&rec, sizeof(rec), 1, fp);
								fflush(fp);
								printf("수정완료\n");
								printf("========== 수정 정보  ==========\n");
								fseek(fp, (id - START_ID)* sizeof(rec), SEEK_SET);
								fread(&rec, sizeof(rec), 1, fp);
								if((rec.graduate == 0) && (rec.registration == 0) && (rec.taketime == 0)) printf("졸업여부:졸업 , 등록여부:등록취소, 휴학확인:휴학\n\n");
								else if((rec.graduate == 0) && (rec.registration == 0) && (rec.taketime == 1)) printf("졸업여부:졸업 , 등록여부:등록취소, 휴학확인:재학\n\n");
								else if((rec.graduate == 0) && (rec.registration == 1) && (rec.taketime == 1)) printf("졸업여부:졸업 , 등록여부:등록, 휴학확인:재학\n\n");
								else if((rec.graduate == 1) && (rec.registration == 1) && (rec.taketime == 1)) printf("졸업여부:재학 , 등록여부:등록, 휴학확인:재학\n\n");
								else if((rec.graduate == 0) && (rec.registration == 1) && (rec.taketime == 0)) printf("졸업여부:졸업 , 등록여부:등록, 휴학확인:휴학\n\n");
								else if((rec.graduate == 1) && (rec.registration == 0) && (rec.taketime == 0)) printf("졸업여부:재학 , 등록여부:등록취소, 휴학확인:휴학\n\n");
								else if((rec.graduate == 1) && (rec.registration == 1) && (rec.taketime == 0)) printf("졸업여부:재학 , 등록여부:등록, 휴학확인:휴학\n\n");
								else printf("졸업여부:재학 , 등록여부:등록취소, 휴학확인:재학\n\n");
							}
							else {
								printf("0또는 1을 입력하세요\n");
								c = 'Y';
							}
						}
						else if(choice == 3) {
							printf("휴학여부 입력(0.휴학 / 1.재학) : ");
							scanf("%d", &rec.taketime);
							if((rec.graduate == 0) || (rec.graduate == 1)) {
								fseek(fp, -sizeof(rec), SEEK_CUR);
								fwrite(&rec, sizeof(rec), 1, fp);
								fflush(fp);
								printf("수정완료\n");
								printf("==========  수정 정보  ==========\n");
								fseek(fp, (id - START_ID)* sizeof(rec), SEEK_SET);
								fread(&rec, sizeof(rec), 1, fp);
								if((rec.graduate == 0) && (rec.registration == 0) && (rec.taketime == 0)) printf("졸업여부:졸업 , 등록여부:등록취소, 휴학확인:휴학\n\n");
								else if((rec.graduate == 0) && (rec.registration == 0) && (rec.taketime == 1)) printf("졸업여부:졸업 , 등록여부:등록취소, 휴학확인:재학\n\n");
								else if((rec.graduate == 0) && (rec.registration == 1) && (rec.taketime == 1)) printf("졸업여부:졸업 , 등록여부:등록, 휴학확인:재학\n\n");
								else if((rec.graduate == 1) && (rec.registration == 1) && (rec.taketime == 1)) printf("졸업여부:재학 , 등록여부:등록, 휴학확인:재학\n\n");
								else if((rec.graduate == 0) && (rec.registration == 1) && (rec.taketime == 0)) printf("졸업여부:졸업 , 등록여부:등록, 휴학확인:휴학\n\n");
								else if((rec.graduate == 1) && (rec.registration == 0) && (rec.taketime == 0)) printf("졸업여부:재학 , 등록여부:등록취소, 휴학확인:휴학\n\n");
								else if((rec.graduate == 1) && (rec.registration == 1) && (rec.taketime == 0)) printf("졸업여부:재학 , 등록여부:등록, 휴학확인:휴학\n\n");
								else printf("졸업여부:재학 , 등록여부:등록취소, 휴학확인:재학\n");
							}
							else {
								printf("0또는 1을 입력하세요\n");
								c = 'Y';
							}
						}
						else {
							printf("1~3중에 선택하세요\n");
							c = 'Y';
						}
					}
					else {
						printf("학번: %d 없음\n", id);
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
}

void update2(void)
{
	int id;
	int select;
	char c;

	do {
		printf("수정할 학생 학번 입력: ");
		if(scanf("%d", &id) == 1) {
			fseek(fp, (id - START_ID)* sizeof(rec), SEEK_SET);
			if((fread(&rec, sizeof(rec), 1, fp) > 0) && (rec.id != 0)) {
				printf("1.전화번호, 2.이메일, 3.주소, 4.소속학과, 5.학년, 6.장학금, 7.다전공 : ");
				scanf("%d", &select);
				if(select == 1) {
					printf("새로운 전화번호 입력: ");
					scanf(" %s", rec.phone);
					fseek(fp, -sizeof(rec), SEEK_CUR);
					fwrite(&rec, sizeof(rec), 1, fp);
					fflush(fp);
					printf("수정완료\n\n");
				}
				else if(select == 2) {
					printf("새로운 이메일 입력: ");
					scanf(" %s", rec.mail);
					fseek(fp, -sizeof(rec), SEEK_CUR);
					fwrite(&rec, sizeof(rec), 1, fp);
					fflush(fp);
					printf("수정완료\n\n");
				}
				else if(select == 3) {
					printf("새로운 주소 입력: ");
					scanf(" %s", rec.address);
					fseek(fp, -sizeof(rec), SEEK_CUR);
					fwrite(&rec, sizeof(rec), 1, fp);
					fflush(fp);
					printf("수정완료\n\n");
				}
				else if(select == 4) {
					printf("새로운 소속학과 입력: ");
					scanf(" %s", rec.major);
					fseek(fp, -sizeof(rec), SEEK_CUR);
					fwrite(&rec, sizeof(rec), 1, fp);
					fflush(fp);
					printf("수정완료\n\n");
				}
				else if(select == 5) {
					printf("새로운 학년 입력: ");
					scanf("%d", &rec.grade);
					fseek(fp, -sizeof(rec), SEEK_CUR);
					fwrite(&rec, sizeof(rec), 1, fp);
					fflush(fp);
					printf("수정완료\n\n");
				}
				else if(select == 6) {
					printf("새로운 장학금 입력: ");
					scanf("%d", &rec.scholarship);
					fseek(fp, -sizeof(rec), SEEK_CUR);
					fwrite(&rec, sizeof(rec), 1, fp);
					fflush(fp);
					printf("수정완료\n\n");
				}
				else if(select == 7) {
					printf("새로운 다전공 입력: ");
					scanf(" %s", rec.etcmajor);
					fseek(fp, -sizeof(rec), SEEK_CUR);
					fwrite(&rec, sizeof(rec), 1, fp);
					fflush(fp);
					printf("수정완료\n\n");
				}
				else {
					printf("잘못된 입력\n");
				}
			}
			else {
				printf("학번: %d 없음\n", id);
			}
		}
		else {
			printf("입력오류\n");
		}
		printf("계속하시겠습니까?(Y/N): ");
		scanf(" %c", &c);
	}
	while(c == 'Y');
}
