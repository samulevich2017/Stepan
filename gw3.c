#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
	char* s = malloc(10000);
	char c = '\0';
	char c2 = '\0';
	int sl = -1;
	int wlc = 0;
	int sw3 = 0;

	while(c != '.'){
		sl++;
		c = getchar();
		s[sl] = c;
	}

	sl++;
	s[sl] = '\0';

	for(int i = 0; i < sl; i++){
		if(s[i] != ' ' && s[i] != ',' && s[i] != '.'){
			wlc++;	
		}

		else{
			wlc = 0;
		}
		if(wlc == 3){
			sw3++;
		}

	}

	printf("%d", sw3);
	
	return 0;

}
