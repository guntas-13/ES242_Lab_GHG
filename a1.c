#include "test.h"

#include <stdio.h>
#include <string.h>

// This is Hitesh here.
/*
 * See Exercise 2 (a), page 94 in Jeff Erickson's textbook.
 * The exercise only asks you to count the possible splits.
 * In this assignment, you have to generate all possible splits into buf[]
 * and call process_split() to process them.
 * The dictionary parameter is an array of words, sorted in dictionary order.
 * nwords is the number of words in this dictionary.
 */
int isWord(char *b, const char *dictionary[], int nwords){
    for (int i = 0; i < nwords; i++){
        if (strcmp(dictionary[i], b) == 0){
            return 1;
        }
    }return 0;
}
void printc(char *b){
    for (int i = 0; b[i] != '\0'; i++){
        printf("%c", b[i]);
    }printf("\n");
}

int gj = 0;
void split_it(char* b,char* temp, int s, int a_len, const char* dictionary[], int nwords, char buf[], void* data, void(*process_split(char buf[], void *data)))
{
    if(a_len <= 0){
        int i = 0;
        for (; temp[i]!='\0'; i++){
            buf[i] = temp[i];
        }buf[i-1] = '\0';
        process_split(buf,data);
        buf[0] = '\0';
        return;
    }
    // int end_idx = s;
    // printf("b = %s\n",b);
    char a[256];
    int j = 0;
    int temp_alen = a_len;
    // printf("a_len = %d\n",a_len);
    while(b[0] != '\0' && temp_alen > 0)
    {
        a[j] = b[j];
        a[j+1] = '\0';
        int z = gj;
        // printf("gj = %d\n",gj);
        // printf("j = %d\n",j);
        // printf("a in loop = %s\n",a);
        // printf("temp in loop = %s\n",temp);
        if(isWord(a,dictionary,nwords)){
            // printf("a is word = %s\n",a);
            for (int i = 0; a[i] != '\0'; i++)
            {
                temp[gj] = a[i];gj++;
            }temp[gj] = ' ';gj++;
            temp[gj] = '\0';
            
            // printf("******temp = '%s'\n",temp);
            int k = 0;
            char* rest = (char*)malloc((a_len)*sizeof(char));
            for (; b[k] != '\0'; k++)
            {
                rest[k] = b[j+k+1];
            }rest[k] = '\0';
            // printf("rest = '%s', j = %d\n",rest,j);
            
            split_it(rest,temp,0,a_len-j-1,dictionary,nwords,buf,data,process_split);
            gj = z;
        }
        j++;temp_alen--;
    }    
}

void generate_splits(const char *source, const char *dictionary[], int nwords, char buf[], void *data, void(*process_split(char buf[], void *data)))
{
    int i = 0; 
    while(source[i] != '\0'){i++;}
    char temp[256];
    split_it((char*)source,temp,0,i,dictionary,nwords,buf,data,process_split);
}


/*
 * Transform a[] so that it becomes the previous permutation of the elements in it.
 * If a[] is the first permutation, leave it unchanged.
 */

// This is Gaurav Budhwani - 22110085 :)
void previous_permutation(int a[], int n)
{
    int first = n - 2, second = n - 1, temp, m, k = 0, i;
    while (a[first] < a[first + 1])
        first--;
        if (first < 0)
            return;
        while(a[first] < a[second])
            second--;
            temp = a[first];
            a[first] = a[second];
            a[second] = temp;
            m = (n - first - 1)/2;
            for(i = first+1; i<first+1+m; i++)
            {
                temp = a[i];
                a[i] = a[n-1-k];
                a[n-1-k] = temp;
                k++;
            }
}

// This is Guntas Singh Saran - 22110089 !
/*
 * Generate k-selections of a[0..n-1] in lexicographic order and call process_selection to process them.
 *
 * The array b[] will have enough space to hold k elements.
 * For a selection i1, ..., ik, you should set b[0] = a[i1], ..., b[k-1] = a[ik].
 * Selections should be generated in lexicographic order.
 * a[0..k-1] is the smallest selection and a[n-k..n-1] is the largest.
 */

void selections(int a[], int b[], int start, int end, int index, int k, void *data, void (*process_selection)(int *b, int k, void *data))
{
    if (index == k)
    {
        process_selection(b, k, data);
        return;
    }
    for (int i = start; i < end && end - i + 1 >= k - index; ++i)
    {
        b[index] = a[i];
        selections(a, b, i + 1, end, index + 1, k, data, process_selection);
    }
}

void generate_selections(int a[], int n, int k, int b[], void *data, void (*process_selection)(int *b, int k, void *data))
{
    selections(a, b, 0, n, 0, k, data, process_selection);
}

// TESTS BEGIN FROM HERE!!!!!

typedef struct {
    int index;
    int err;
} state_t;

static void test_selections_2165(int b[], int k, void *data)
{
    state_t *s = (state_t *)data;
    s->err = 0;
    switch (s->index) {
    case 0:
        if ((b[0] != 2) || (b[1] != 1)) {
            s->err = 1;
        }
        break;
    case 1:
        if ((b[0] != 2) || (b[1] != 6)) {
            s->err = 1;
        }
        break;
    case 2:
        if ((b[0] != 2) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    case 3:
        if ((b[0] != 1) || (b[1] != 6)) {
            s->err = 1;
        }
        break;
    case 4:
        if ((b[0] != 1) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    case 5:
        if ((b[0] != 6) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    default:
        s->err = 1;
    }
    ++(s->index);
}


BEGIN_TEST(previous_permutation) {
    int a[] = { 1, 5, 6, 2, 3, 4 };
    previous_permutation(a, 6);
    ASSERT_ARRAY_VALUES_EQ(a, 6, "Failed on 1 5 6 2 3 4.", 1, 5, 4, 6, 3, 2);
} END_TEST

BEGIN_TEST(generate_selections) {
    int a[] = { 2, 1, 6, 5 };
    int b[2];
    state_t s2165 = { .index = 0, .err = 1 };
    generate_selections(a, 4, 2, b, &s2165, test_selections_2165);
    ASSERT(!s2165.err, "Failed on 2 1 6 5.");
} END_TEST

void *test_splits_art(char buf[], void *data)
{
    state_t *s = (state_t*)data;
    s->err = 0;
    switch (s->index) {
    case 0:
        if (!strcmp(buf, "art is toil")) {
            s->err = 1;
        }
        break;
    case 1:
        if (!strcmp(buf, "artist oil")) {
            s->err = 1;
        }
        break;
    default:
        s->err = 1;
    }
}

BEGIN_TEST(generate_splits) {
    const char *a = "artistoil";
    const char *dict[] = {
        "art",
        "artist",
        "is",
        "oil",
        "toil"
    };
    int nwords = 5;
    state_t s = { .index = 0, .err = 1 };
    char buf[256];
    generate_splits(a, dict, nwords, buf, &s, test_splits_art);
    ASSERT(!s.err, "Failed on 'artistoil'.");
} END_TEST
// RUNNING TEST ON ALL THREE!!!


int main()
{
    
    run_tests((test_t[]) {
            TEST(generate_selections),
            TEST(previous_permutation),
            TEST(generate_splits),
            0
        });

    // const char* dictionary[] = {"BOTH","THE","HEAR","HEART","HEARTH","AND","SATURN","TURN","SPIN","PIN","URN","ART","HAND","SAT","BOT","HE"};
    // const char* source = "BOTHEARHEARTHANDSATURNSPIN";
    // int nwords = 16;
    // char buf[256];
    // generate_splits(source,dictionary,nwords,buf,NULL,NULL);
    return 0;
}
