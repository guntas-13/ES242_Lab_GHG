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
void generate_splits(const char *source, const char *dictionary[], int nwords, char buf[], void *data, void (*process_split(char buf[], void *data)))
{}

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

void print_array_b(int *b, int k, void *data)
{
    for (int i = 0; i < k; i++){
        printf("%d ", b[i]);
    }
    printf("\n");
}

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

void test_splits_art(char buf[], void *data)
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


//// RUNNING TEST ON ALL THREE!!!

int main()
{
    
    run_tests((test_t[]) {
            TEST(generate_selections),
            TEST(previous_permutation),
            0
        });
    // int a[] = {2, 1, 6, 5};
    // int n = 4;
    // int k = 2;
    // int b[k];
    // generate_selections(a, n, k, b, NULL, print_array_b);
    return 0;
}
