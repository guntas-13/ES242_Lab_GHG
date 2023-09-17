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

/* Write your tests here. Use the previous assignment for reference. */
BEGIN_TEST(previous_permutation) {
    int a[] = { 2, 3 ,1 };
    previous_permutation(a, 3);
    ASSERT_ARRAY_VALUES_EQ(a, 3, "Failed on <2,3,1>.", 2, 1, 3);

    int b[] = { 1, 3, 2 };
    previous_permutation(b, 3);
    ASSERT_ARRAY_VALUES_EQ(b, 3, "Failed on <1,3,2>.", 1, 2, 3);

    int c[] = { 2, 1, 3, 4 };
    previous_permutation(c, 4);
    ASSERT_ARRAY_VALUES_EQ(c, 4, "Failed on <2,1,3,4>.", 1, 4, 3, 2);

    int d[] = { [0]=2, [1]=1, [2]=3, [3]=4, [4] = 5};
    previous_permutation(d, 5);
    ASSERT_ARRAY_VALUES_EQ(d, 5, "Failed on <2,1,3,4,5>.", 1, 5, 4, 3, 2); /* lexiographic permutation in this case is 2,1,3,4,5 ggs*/

}END_TEST



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
    
    // testing previous permutations
    run_tests ((test_t []){
        TEST(previous_permutation),
        0
    });
    return 0;
}
