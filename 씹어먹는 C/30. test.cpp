#include <stdio.h>
#include "30. book_function.h"

int main() {
  int user_choice;        /* ������ ������ �޴� */
  int num_total_book = 0; /* ���� å�� �� */

  /* ���� å, ����, ���ǻ縦 ������ �迭 ����. å�� �ִ� ������ 100 ��*/
  char book_name[100][30], auth_name[100][30], publ_name[100][30];
  /* ���ȴ��� ���¸� ǥ�� */
  int borrowed[100];

  while (1) {
    printf("���� ���� ���α׷� \n");
    printf("�޴��� �����ϼ��� \n");
    printf("1. å�� ���� �߰��ϱ� \n");
    printf("2. å�� �˻��ϱ� \n");
    printf("3. å�� ������ \n");
    printf("4. å�� �ݳ��ϱ� \n");
    printf("5. ���α׷� ���� \n");

    printf("����� ������ : ");
    scanf("%d", &user_choice);

    if (user_choice == 1) {
      /* å�� ���� �߰��ϴ� �Լ� ȣ�� */
      add_book(book_name, auth_name, publ_name, borrowed, &num_total_book);
    } else if (user_choice == 2) {
      /* å�� �˻��ϴ� �Լ� ȣ�� */
      search_book(book_name, auth_name, publ_name, num_total_book);
    } else if (user_choice == 3) {
      /* å�� ������ �Լ� ȣ�� */
      borrow_book(borrowed);
    } else if (user_choice == 4) {
      /* å�� �ݳ��ϴ� �Լ� ȣ�� */
      return_book(borrowed);
    } else if (user_choice == 5) {
      /* ���α׷��� �����Ѵ�. */
      break;
    }
  }

  return 0;
}
