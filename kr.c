#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>


typedef struct Sentence{
    char* sent;
    int len_s;
    int count_word3;
    int rep;
} Sentence;

typedef struct Text{
    Sentence* txt;
    int len_t;
} Text;



Text read_input()
{
    int buff_size1, buff_size2 = 20;
    int sent_last_index, text_last_index = -1;
    int count_word_len, count_w3 = 0;
    char current_char, separator = '\0';

    char* s;
    Text text;
    Sentence* input_text = (Sentence*) malloc(buff_size2 * sizeof(Sentence));


    while(separator != '\n'){

        current_char = '\0';
        sent_last_index = -1;
	count_w3 = 0;
	count_word_len = 0;
        buff_size1 = 20;
        Sentence sentence;

        s = (char*) malloc(buff_size1);
        while(current_char != '.') {
            current_char = getchar();

            sent_last_index++;
            if(sent_last_index >= buff_size1 - 1){
                buff_size1 += 20;
                s = (char*) realloc(s, buff_size1);
            }
            
            if(current_char != ' ' && current_char != ',' && current_char != '.'){
				count_word_len++;
			}
			else{
				if(count_word_len == 3){
					count_w3++;
				}
				count_word_len = 0;
			}

            s[sent_last_index] = current_char;
        }

        sent_last_index++;
        s[sent_last_index] = '\0';

        s = (char*) realloc(s, sent_last_index + 1);

        sentence.sent = s;
        sentence.len_s = sent_last_index;
        sentence.count_word3 = count_w3;
	sentence.rep = 0;

        text_last_index++;
        if(text_last_index >= buff_size2){
            buff_size2 += 20;
            input_text = (Sentence*) realloc(input_text, buff_size2 * sizeof(Sentence));

        }

        input_text[text_last_index] = sentence;

        separator = getchar();
	
	if(separator != ' ' && separator != '\n' && separator != '\0'){
		printf("\nWarning: Sentences must be separated by ' '. Answer can be incorrect.\n");
	}

    }

    input_text = (Sentence*) realloc(input_text, (text_last_index + 1) * sizeof(Sentence));

    text.txt = input_text;
    text.len_t = text_last_index + 1;

    return text;
}



Text remove_same_sent(Text text, int old_len){
	
	int flag_ne = 0;
	int new_len = text.len_t;

	for(int i = 0; i < text.len_t; i++){
		for(int j = 0; j < text.len_t; j++){
			if(i != j && text.txt[i].len_s == text.txt[j].len_s && text.txt[j].rep != 1 && text.txt[i].rep != 1){
				flag_ne = 0;
				for(int k = 0; k <= text.txt[i].len_s; k++){
					if(text.txt[i].sent[k] != text.txt[j].sent[k]){
						flag_ne = 1;
					}

				}
				if(flag_ne == 0){
					text.txt[j].rep = 1;
					new_len--;
				}
				
			}
		}

	}
	
	int i = 0;
	int s = 0;

	if(new_len < old_len){

		while(i < text.len_t){
			if(text.txt[i].rep == 1){
				s++;
			}

			else{
				text.txt[i - s] = text.txt[i];
			}

			i++;
		}

		text.len_t = new_len;

		text.txt = (Sentence*) realloc(text.txt, text.len_t * sizeof(Sentence));
	}

	return text;	
	

}



int comparator(const void* s1, const void* s2){

	Sentence sent1 = *(Sentence*)s1;
	Sentence sent2 = *(Sentence*)s2;

	int cw3_1 = sent1.count_word3;
	int cw3_2 = sent2.count_word3;

	if(cw3_1 > cw3_2){
		return -1;
	}

	if(cw3_2 > cw3_1){
		return 1;
	}

	return 0;

}



Text sort_word(Text text){
    
	Text new_text;

	char* new_sent;

	Sentence* new_txt = (Sentence*) malloc(text.len_t * sizeof(Sentence));

	Sentence new_sentence;


	for(int i = 0; i < text.len_t; i++){
		new_sent = malloc(text.txt[i].len_s + 1);
		strcpy(new_sent, text.txt[i].sent);

		new_sentence.sent = new_sent;
		new_sentence.len_s = text.txt[i].len_s;
		new_sentence.count_word3 = text.txt[i].count_word3;

		new_txt[i] = new_sentence;
		
	}

	new_text.txt = new_txt;
	new_text.len_t = text.len_t;

	
	qsort(new_text.txt, new_text.len_t, sizeof(Sentence), comparator);
	
	return new_text;
}



Text reverse_i(Text text, int index)
{
    char current_char, tmp = '\0';
    Sentence cur_sentence;
    char* let;
    int* sep_ind;
    int k, m = 0;
    char* new_sentence;
    Text new_text;
    Sentence* new_txt = (Sentence*) malloc(text.len_t * sizeof(Sentence));

    new_text.len_t = text.len_t;


    for (int i = 0; i < new_text.len_t; i++) {

        cur_sentence = text.txt[i];
        new_sentence = (char*) malloc(cur_sentence.len_s + 1);

        if(i != index){
            new_sentence = cur_sentence.sent;

        }

        else{

            let = (char*) malloc(cur_sentence.len_s + 1);

            sep_ind = (int*) malloc((cur_sentence.len_s + 1) * sizeof(int));

            k = 0;
            m = 0;

            for (int j = 0; j <= cur_sentence.len_s; j++) {
                current_char = cur_sentence.sent[j];

                if(current_char != ' ' && current_char != ',' && current_char != '.'){
                    let[k] = current_char;
                    k++;
                }

                else{
                    sep_ind[m] = j;
                    m++;
                }

            }


            let = (char*) realloc(let, k);
            sep_ind = (int*) realloc(sep_ind, m * sizeof(int));


            for (int p = 0; p < (k - 1)/2; p++) {
                tmp = let[p];
                let[p] = let[k - p - 2];
                let[k - p - 2] = tmp;
            }

            m = 0;

            for (int j = 0; j <= cur_sentence.len_s; j++) {

                if(j != sep_ind[m]){
                    new_sentence[j] = let[j - m];
                }

                else{
                    new_sentence[j] = cur_sentence.sent[j];
                    m++;
                }

            }

        }

        new_txt[i].sent = new_sentence;

    }

    new_text.txt = new_txt;

    free(let);
    free(sep_ind);

    return new_text;

}



Text remove_physics(Text text)
{
    int flag_ph = 0;
    int j = 0;

    char l_chr;
    char r_chr;
    char physics[] = "physics";
    char* sbstr_a;
    char* cur_sentence;
    char* c_sent_low;

    Sentence* new_txt = (Sentence*) malloc(text.len_t * sizeof(Sentence));
    Text new_text;


    for (int i = 0; i < text.len_t; i++) {

        cur_sentence = text.txt[i].sent;

	c_sent_low = (char*) malloc(text.txt[i].len_s + 1);

	for(int k = 0; k <= text.txt[i].len_s; k++){
		c_sent_low[k] = tolower(cur_sentence[k]);
	}


        flag_ph = 0;
        sbstr_a = strstr(c_sent_low, physics);

        if(sbstr_a != NULL){

            r_chr = *(sbstr_a + 7);

            if(sbstr_a == c_sent_low){

                if(r_chr == ' ' || r_chr ==  ',' || r_chr ==  '.'){
                    flag_ph = 1;
                }
            }
            else{

                l_chr = *(sbstr_a - 1);

                if(l_chr == ' ' || l_chr ==  ',' && (r_chr == ' ' || r_chr ==  ',' || r_chr ==  '.')){
                    flag_ph = 1;
                }
            }

        }

        new_txt[j].sent = cur_sentence;

        if(flag_ph == 0){
            j++;
        }


    }

    new_txt = (Sentence*) realloc(new_txt, j * sizeof(Sentence));

    new_text.txt = new_txt;
    new_text.len_t = j;

    free(c_sent_low);

    return new_text;


}


int num_frq[10];

int* numbers(Text text)
{
    char* sentence;

    for (int i = 0; i < 10; i++) {
        *(num_frq + i) = 0;
    }

    for (int i = 0; i < text.len_t; i++){
        sentence = text.txt[i].sent;
        for (int j = 0; j < text.txt[i].len_s; j++) {
            char c[] = {sentence[j]};
            if(isdigit(c[0])){
                num_frq[atoi(c)]++;
            }
        }
    }


    return num_frq;

}



void print_text(Text text)
{
    for (int i = 0; i < text.len_t; i++) {
        printf("%s", text.txt[i].sent);
        if(i != text.len_t - 1){
            printf(" ");
        }
    }
}



int main()
{
    printf("Enter text:\n");

    Text input = read_input();

    int user_input = 0;

    int* result_num;
    int num_flag;
    Text result_ph;
    Text result_rv;
    Text result_same;
    Text result_sort;
    int user_index;
    int test_input;
    int old_t_len;
    
    old_t_len = input.len_t;

    input = remove_same_sent(input, old_t_len);
    
    if(input.len_t < old_t_len){

    	printf("\nAll same sentences removed. Now text is:\n");
    	print_text(input);

    	printf("\n");
    }

    while(user_input != -1){
        //sleep(1);
        printf("\nChoose option:\n0 - Numbers and their frequency;\n1 - Delete all sentences with word \"physics\";\n2 - Invert chosen sentence;\n3 - Sort sentences;\n-1 - Exit.\nEnter your number: ");
        test_input = scanf("%d", &user_input);
	
	if(test_input == 0){
		puts("\nError: Enter NUMBER! Terminated.");
		return 0;
	}

        printf("\nResult: ");

        switch(user_input){
            case(0):

                num_flag = 0;

                result_num = numbers(input);

                for (int i = 0; i < 10; i++) {
                    if(result_num[i] != 0){
                        num_flag = 1;
                    }
                }


                if(num_flag == 0){
                    printf("There aren't any numbers in text.");
                }

                else{
                    for (int i = 0; i < 10; i++) {
                        if(result_num[i] != 0){
                            printf("'%d' - %d", i, result_num[i]);
                            if(i != 9){
                                printf("; ");
                            }
                        }
                    }

                }

                break;

            case(1):

                result_ph = remove_physics(input);
                print_text(result_ph);

                for(int i = 0; i < result_ph.len_t; i++){
			free(result_ph.txt[i].sent);
		}

		free(result_ph.txt);

                break;



            case(2):

                printf("\nEnter index of sentence you want to invert (use numbers form 0 to %d): ", input.len_t - 1);
                test_input = scanf("%d", &user_index);

		if(test_input == 0){
			printf("\nError: Enter NUMBER! Terminated.");
			return 0;
		}

                if(user_index < 0 || user_index > input.len_t - 1){
                    printf("\nIndex is wrong! Index can be only from 0 to %d.", input.len_t - 1);
                }
                else{
                    result_rv = reverse_i(input, user_index);
                    print_text(result_rv);
                }
                
		for(int i = 0; i < result_rv.len_t; i++){
			free(result_rv.txt[i].sent);
		}

		free(result_rv.txt);

                break;

		
	    case(3):
	        result_sort = sort_word(input);
		print_text(result_sort);
		for(int i = 0; i < result_sort.len_t; i++){
			free(result_sort.txt[i].sent);
		}

		free(result_sort.txt);

		break;


            default:
                printf("Wrong number!");
                break;

            case(-1):
                printf("Goodbye.");
                for(int i = 0; i < input.len_t; i++){
			free(input.txt[i].sent);
		}

		free(input.txt);

        }

        printf("\n");



    }
    return 0;
}
