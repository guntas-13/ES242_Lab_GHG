#include "test.h"

#include <stdio.h>
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
void previous_permutation(int a[], int n)
{}

/* Write your tests here. Use the previous assignment for reference. */

// BEGIN_TEST(generate_selections) {
//     int a[] = {1, 2, 3, 4, 5};
//     int n = 5;
//     int k = 3;
//     int b[k];
//     generate_selections(a, n, k, b, NULL, );
//     ASSERT_ARRAY_VALUES_EQ(b, 3, "Failed on <1,2,3>.", 1, 2, 3);
//     ASSERT_ARRAY_VALUES_EQ(b, 3, "Failed on <1,2,3>.", 1, 2, 4);
//     ASSERT_ARRAY_VALUES_EQ(b, 3, "Failed on <1,2,3>.", 1, 2, 5);
//     ASSERT_ARRAY_VALUES_EQ(b, 3, "Failed on <1,2,3>.", 1, 3, 4);
//     ASSERT_ARRAY_VALUES_EQ(b, 3, "Failed on <1,2,3>.", 1, 3, 5);
//     ASSERT_ARRAY_VALUES_EQ(b, 3, "Failed on <1,2,3>.", 1, 4, 5);
//     ASSERT_ARRAY_VALUES_EQ(b, 3, "Failed on <1,2,3>.", 2, 3, 4);
//     ASSERT_ARRAY_VALUES_EQ(b, 3, "Failed on <1,2,3>.", 2, 3, 5);
//     ASSERT_ARRAY_VALUES_EQ(b, 3, "Failed on <1,2,3>.", 2, 4, 5);
//     ASSERT_ARRAY_VALUES_EQ(b, 3, "Failed on <1,2,3>.", 3, 4, 5);
// } END_TEST


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
    selections(a, b, 0, n - 1, 0, k, data, process_selection);
}

int main()
{
    // run_tests ((test_t []){
    //     TEST(generate_selections),
    //     0
    // });
    int a[] = {1, 2, 3, 4, 5};
    int n = 5;
    int k = 2;
    int b[k];
    generate_selections(a, n, k, b, NULL, print_array_b);
    return 0;
}
