/* [C언어의 malloc & free] 
#include <stdio.h>
#include <stdlib.h>
int main()
{
int studentNum, totalScore=0;
int* studentScore;
int i;
printf("학생 수를 입력하세요: ");
scanf("%d", &studentNum);
studentScore = (int *)malloc(sizeof(int) * studentNum);//******
for(i=0; i<studentNum; i++) {
printf("%d번 학생의 점수: ", i + 1);
scanf("%d", &studentScore[i]);
totalScore += studentScore[i];
}
printf("모든 학생의 평균: %d\n", totalScore / studentNum);
free(studentScore);//*****
return 0;
}
*/

//[C++의 new & delete]

#include <iostream>

using namespace std;//없으면 std::cout, std::cin 사용해야댐 
int main()
{
int studentNum, totalScore=0;
int* studentScore;
int i;
cout << "학생 수를 입력하세요: ";
cin >> studentNum;
studentScore = new int[studentNum];//자료형, 길이 

int* ptr1=new int(3);//소괄호는 new int로 할당하고 3으로 값을 초기화 
 
for(i=0; i < studentNum; i++) {
	cout << i + 1 << "번 학생의 점수: ";
	cin >> studentScore[i];
	totalScore += studentScore[i];
}
cout << "모든 학생의 평균: " << totalScore / studentNum << endl;
delete []studentScore;
return 0;
}

/*
new/delete는 malloc/free와 달리 연산자이다.
재할당 불가능. 
*/
