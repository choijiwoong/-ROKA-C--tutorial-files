/* [C����� malloc & free] 
#include <stdio.h>
#include <stdlib.h>
int main()
{
int studentNum, totalScore=0;
int* studentScore;
int i;
printf("�л� ���� �Է��ϼ���: ");
scanf("%d", &studentNum);
studentScore = (int *)malloc(sizeof(int) * studentNum);//******
for(i=0; i<studentNum; i++) {
printf("%d�� �л��� ����: ", i + 1);
scanf("%d", &studentScore[i]);
totalScore += studentScore[i];
}
printf("��� �л��� ���: %d\n", totalScore / studentNum);
free(studentScore);//*****
return 0;
}
*/

//[C++�� new & delete]

#include <iostream>

using namespace std;//������ std::cout, std::cin ����ؾߴ� 
int main()
{
int studentNum, totalScore=0;
int* studentScore;
int i;
cout << "�л� ���� �Է��ϼ���: ";
cin >> studentNum;
studentScore = new int[studentNum];//�ڷ���, ���� 

int* ptr1=new int(3);//�Ұ�ȣ�� new int�� �Ҵ��ϰ� 3���� ���� �ʱ�ȭ 
 
for(i=0; i < studentNum; i++) {
	cout << i + 1 << "�� �л��� ����: ";
	cin >> studentScore[i];
	totalScore += studentScore[i];
}
cout << "��� �л��� ���: " << totalScore / studentNum << endl;
delete []studentScore;
return 0;
}

/*
new/delete�� malloc/free�� �޸� �������̴�.
���Ҵ� �Ұ���. 
*/
