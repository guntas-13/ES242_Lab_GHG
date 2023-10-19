#include "test.h"

#include <stdio.h>
#include <string.h>

/// THIS QUESTION IS DONE BY HITESH KUMAR - 22110098
/*
 * See Exercise 2 (a), page 94 in Jeff Erickson's textbook.
 * The exercise only asks you to count the possible splits.
 * In this assignment, you have to generate all possible splits into buf[]
 * and call process_split() to process them.
 * The dictionary parameter is an array of words, sorted in dictionary order.
 * nwords is the number of words in this dictionary.
 */
int isWord(char *b, const char *dictionary[], int nwords)
{
    for (int i = 0; i < nwords; i++)
    {
        if (strcmp(dictionary[i], b) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int temp_index = 0;
void split_it(char *b, char *temp, int a_len, const char *dictionary[], int nwords, char buf[], void *data, void(*process_split(char buf[], void *data)))
{
    if (a_len <= 0)
    {
        int i = 0;
        for (; temp[i] != '\0'; i++)
        {
            buf[i] = temp[i];
        }
        buf[i - 1] = '\0';
        process_split(buf, data);
        buf[0] = '\0';
        return;
    }
    // int end_idx = s;
    // printf("b = %s\n",b);
    char a[256];
    int j = 0;
    int temp_a_len = a_len;
    // printf("a_len = %d\n",a_len);
    while (b[0] != '\0' && temp_a_len > 0)
    {
        a[j] = b[j];
        a[j + 1] = '\0';
        int tmp_idx = temp_index;
        if (isWord(a, dictionary, nwords))
        {
            // printf("a is word = %s\n",a);
            for (int i = 0; a[i] != '\0'; i++)
            {
                temp[temp_index] = a[i];
                temp_index++;
            }
            temp[temp_index] = ' ';
            temp_index++;
            temp[temp_index] = '\0';

            // printf("******temp = '%s'\n",temp);
            int k = 0;
            char str_left[256];
            for (; b[k] != '\0'; k++)
            {
                str_left[k] = b[j + k + 1];
            }
            str_left[k] = '\0';
            // printf("str_left = '%s', j = %d\n",rest,j);

            split_it(str_left, temp, a_len - j - 1, dictionary, nwords, buf, data, process_split);
            temp_index = tmp_idx;
        }
        j++;
        temp_a_len--;
    }
}

void generate_splits(const char *source, const char *dictionary[], int nwords, char buf[], void *data, void(*process_split(char buf[], void *data)))
{
    int i = 0;
    while (source[i] != '\0')
    {
        i++;
    }
    char temp[256];
    split_it((char *)source, temp, i, dictionary, nwords, buf, data, process_split);
}


/// THIS QUESTION IS DONE BY GAURAV BUDHWANI - 22110085
/*
 * Transform a[] so that it becomes the previous permutation of the elements in it.
 * If a[] is the first permutation, leave it unchanged.
 */

void previous_permutation(int a[], int n)
{
    int first = n - 2, second = n - 1, temp, m, k = 0, i;
    while (a[first] < a[first + 1])
        first--;
    if (first < 0)
        return;
    while (a[first] < a[second])
        second--;
    temp = a[first];
    a[first] = a[second];
    a[second] = temp;
    m = (n - first - 1) / 2;
    for (i = first + 1; i < first + 1 + m; i++)
    {
        temp = a[i];
        a[i] = a[n - 1 - k];
        a[n - 1 - k] = temp;
        k++;
    }
}


/// THIS QUESTION IS DONE BY GUNTAS SINGH SARAN - 22110089
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
    int first;
} state_t;

static void test_selections_2165(int b[], int k, void *data)
{
    state_t *s = (state_t *)data;
    if (s->first) {
        s->err = 0;
        s->first = 0;
    }
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

void count_selections(int b[], int k, void *data)
{
    int *d = (int*)data;
    ++*d;
}

typedef struct {
    int b[100];
} selection_t;

void last_selection(int b[], int k, void *data)
{
    selection_t *s = (selection_t*)data;
    for (int i = 0; i < k; ++i) {
        s->b[i] = b[i];
    }
}

BEGIN_TEST(generate_selections) {
    int a[] = { 2, 1, 6, 5 };
    int b[10];
    state_t s2165 = { .index = 0, .err = 1, .first = 1 };
    generate_selections(a, 4, 2, b, &s2165, test_selections_2165);
    ASSERT(!s2165.err, "Failed on 2 1 6 5.");
    int c = 0;
    int aa[] = { 1, 5, 3, 0, 1, 12, 4, 3, 6, 6 };
    generate_selections(aa, 10, 5, b, &c, count_selections);
    ASSERT_EQ(c, 252, "Failed on 10C5.");

    selection_t s;
    generate_selections(aa, 10, 5, b, &s, last_selection);
    ASSERT_ARRAY_VALUES_EQ(s.b, 5, "Failed on last of 10C5.", 12, 4, 3, 6, 6);
} END_TEST

void test_splits_art(char buf[], void *data)
{
    state_t *s = (state_t*)data;
    if (s->first) {
        s->err = 0;
        s->first = 0;
    }
    switch (s->index) {
    case 0:
        if (strcmp(buf, "art is toil")) {
            s->err = 1;
        }
        break;
    case 1:
        if (strcmp(buf, "artist oil")) {
            s->err = 1;
        }
        break;
    default:
        s->err = 1;
    }
    ++(s->index);
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
    state_t s = { .index = 0, .err = 1, .first = 1 };
    char buf[256];
    generate_splits(a, dict, nwords, buf, &s, test_splits_art);
    ASSERT(!s.err, "Failed on 'artistoil'.");
} END_TEST

BEGIN_TEST(previous_permutation) {
    int a[] = { 1, 5, 6, 2, 3, 4 };
    previous_permutation(a, 6);
    ASSERT_ARRAY_VALUES_EQ(a, 6, "Failed on 1 5 6 2 3 4.", 1, 5, 4, 6, 3, 2);
    int aa[] = { 1, 2, 3, 5, 4, 6 };
    previous_permutation(aa, 3); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(aa, 3, "Failed on 1 2 3.", 1, 2, 3);
} END_TEST

int main()
{

    run_tests((test_t[]){
        TEST(generate_selections),
        TEST(previous_permutation),
        TEST(generate_splits),
        0});
    return 0;
}
