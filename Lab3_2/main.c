#include <stdio.h>
#include <stdlib.h>

void quicksort (int r, int *mass)
{
    int left = 0, right = r - 1, middle = mass[(left + right) / 2], temp;

    do {
        while (mass[left] < middle) {
            left++;
        }
        while (mass[right] > middle) {
            right--;
        }
        if (left <= right) {
            temp = mass[left];
            mass[left] = mass[right];
            mass[right] = temp;
            left++;
            right--;
        }
    } while (left <= right);

    if (left < r) {
        quicksort(r - left, &mass[left]);
    }
    if (right > 0) {
        quicksort(right + 1, mass);
    }
}

int getSochet(int n, int k) {
    int chisl = 1;
    int znam = 1;
    for (int i = 1; i <= n; ++i) {
        if (i <= k) {
            znam *= i;
        }
        if (i <= n-k) {
            znam *= i;
        }
        chisl *= i;
    }
    return chisl/znam;
}

void rF1(int currVal, int currIt, int k, int currC, int l, int *index, int **mass) {
    if (currIt > k) {
        return;
    }
    else {
        if (currC == l) {
            (*mass)[*index] = currVal;
            (*index)++;
        }
        if (k - currIt > l - currC) {
            rF1(currVal << 1, currIt + 1, k, currC, l, index, mass);
        }
        if (currC < l) {
            rF1((currVal << 1) + 1, currIt + 1, k, currC + 1, l, index, mass);
        }
    }
}

void rF2(int currVal, int currIt, int k, int l, int *index, int **mass) {
    if (k - l - currIt >= 0) {
        rF2(currVal << 1, currIt+1, k, l, index, mass);
        for (int i = 0; i < l - 1; ++i) {
            currVal += 1 << (currIt + i + 1);
        }
        (*mass)[*index] = currVal;
    }
}

void func1(int **mass, int *length) {
    int k, l, index = 0;
    scanf("%d %d", &k, &l);
    if (l == 0) {
        *length = 1;
        *mass = malloc(sizeof(int));
        (*mass)[0] = 0;
    } else {
        *length = getSochet(k, l);
        (*mass) = malloc(sizeof(int) * (*length));
        rF1(1, 1, k, 1, l, &index, mass);
    }
    //TODO: доделать быструю сортировку

    quicksort(*length - 1, *mass);
}

void func2(int **mass, int *length) {
    int k, l, index = 0;
    scanf("%d %d", &k, &l);
    if (l == 0) {
        *length = 0;
        *mass = malloc(sizeof(int));
        (*mass)[0] = 0;
    } else {
        *length = k - l + 1;
        *mass = malloc(sizeof(int)*(*length));
        rF2(1,0, k, l, &index, mass);
    }
    quicksort(*length - 1, *mass);
}

int main() {
    int *mass, length;
    func1(&mass, &length);
    printf("length is %d\n", length);
    for (int i = 0; i < length; ++i) {
        printf("%d\n", mass[i]);
    }
    return 0;
}
