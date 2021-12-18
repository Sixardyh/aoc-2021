// run with < input.txt in STDIN
// comment the irrelevant part

#include <stdio.h>

#define FILE_LINES 2000

int part1() {
        int nb_larger = 0;
        int m, n;  // assume input doesn't get negative cuz im lazy

        for (int i = 0 ; i < FILE_LINES ; i++) {
                scanf("%d", &m);
                if (!i) {
                        n = m;
                        continue;
                }
                if (m > n) nb_larger++;
                n = m;
        }

        return nb_larger;
}

int part2() {
        int nb_larger = 0;
        int a, b, m, n, o, t;

        for (int i = 0 ; i < FILE_LINES ; i++) {
                t = m;
                scanf("%d", &m);
                if (!i) {
                        o = m;
                        continue;
                } else if (i == 1) {
                        n = m;
                        continue;
                } else if (i == 2) {
                        b = m + n + o;
                        continue;
                }
                o = n;
                n = t;
                a = m + n + o;
                if (a > b) nb_larger++;
                b = a;
        }

        return nb_larger;
}

int main() {
//        printf("Number of single increases: %d\n", part1());
        printf("Nuber of three-measurement increases: %d\n", part2());

        return 0;
}

