#include <gmp.h>
#include <stdio.h>

#define LEN 856

int main() {
    int lengths[4] = {1, 2, 12, 40};
    int l = 4;

    mpz_t dp[LEN + 1];
    for (int i = 0; i <= LEN; i++) {
        mpz_init(dp[i]);
    }

    for (int i = 0; i < l; i++) {
        mpz_add_ui(dp[lengths[i]], dp[lengths[i]], 1);
    }

    for (int i = 1; i < LEN; i++) {
        if (dp[i] > 0) {
            for (int j = 0; j < l; j++) {
                if (i + lengths[j] <= LEN) {
                    mpz_add(dp[i + lengths[j]], dp[i + lengths[j]], dp[i]);
                }
            }
        }
    }

    mpz_out_str(stdout, 10, dp[LEN]);
    printf("\n");

    return 0;
}
