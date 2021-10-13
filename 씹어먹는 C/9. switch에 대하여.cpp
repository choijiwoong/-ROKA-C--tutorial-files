#include <stdio.h>

/*
1.	if문 보다 switch가 권장되는 이유는 switch는 jump table에 실행할 명령어의 주소를 입력해두기 때문에 if처럼 CMP연산이 늘어나는 것이 아니라 
	jump table의 크기만 커지기 때문이다.
	 고로 case의 값이 크지 않고, 정렬되어있고 그 값들의 차이가 크지 않다면 효율성을 극대화시킬 수 있다. 
	case값에 정수가 와야 하는 이유는 jump table에서 정수의 인덱스만큼을 건너뛰기 때문이다. 
*/
