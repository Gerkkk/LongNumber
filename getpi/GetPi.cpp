#include "../Headers/library.h"
#include <vector>
#include <cmath>

using namespace Lnum;

std::vector<LongNumber> binary_split(int aa, int bb, int mod){
    LongNumber Pab, Qab, Rab;
    LongNumber a = LongNumber(aa);
    LongNumber b = LongNumber(bb);
    if (b >= a + LongNumber(1) && b <= a + LongNumber(1)){
        LongNumber part1 = (LongNumber(6).mult_mod(a, mod) - LongNumber(5)).mult_mod((LongNumber(2).mult_mod(a, mod) - LongNumber(1)), mod);
        LongNumber part2 = part1.mult_mod((LongNumber(6).mult_mod(a, mod) - LongNumber(1)), mod);
        Pab = -part2;

        Qab = ((LongNumber(10939058860032000.0_ln).mult_mod(a, mod)).mult_mod(a, mod)).mult_mod(a, mod);
        Rab = Pab.mult_mod((LongNumber(545140134).mult_mod(a, mod) + LongNumber(13591409)), mod);
//        std::cout << Pab << " " << Qab << " " << Rab << std::endl;
    }else{
        int m = (aa + bb) / 2;
        std::vector<LongNumber> ans1 = binary_split(aa, m, mod);
        LongNumber Pam = ans1[0];
        LongNumber Qam = ans1[1];
        LongNumber Ram = ans1[2];
        std::vector<LongNumber> ans2 = binary_split(m, bb, mod);
        LongNumber Pmb = ans2[0];
        LongNumber Qmb = ans2[1];
        LongNumber Rmb = ans2[2];

        Pab = Pam.mult_mod(Pmb, mod);
        Qab = Qam.mult_mod(Qmb, mod);
        Rab = Qmb.mult_mod(Ram, mod) + Pam.mult_mod(Rmb, mod);
    }
    std::vector<LongNumber> ret;
    ret.push_back(Pab);
    ret.push_back(Qab);
    ret.push_back(Rab);
    return ret;
}

LongNumber chudnovsky(int n, int mod){
    std::vector<LongNumber> ans1 = binary_split(1, n, mod);
    LongNumber P1n = ans1[0];
    LongNumber Q1n = ans1[1];
    LongNumber R1n = ans1[2];

    LongNumber beg = LongNumber(100.0249968757810059447_ln);
    LongNumber next;
    int log = 1, y = 1;
    while (log < mod) {
        log *= 2;
        y++;
    }
    int n_mod = mod + 2;
    for (int i = 0; i < y + 3; i++) {
        LongNumber part1 = LongNumber(10005.0_ln).div_mod(beg, n_mod);
        LongNumber part2 = beg + part1;
        LongNumber part3 = LongNumber(0.5_ln).mult_mod(part2, n_mod);
        beg = part3;
    }

//    LongNumber sq = LongNumber("100.02499687578100594479218787635777800159502436869631465713551156965096785386430429231118794849997329775519388936956618111013103490739019910311301108176200210847732094847137555223009640258148773625979965387785206908441385174423308598593513683564559598792007420548033708884425917282914639271799746544495693553323515636239343714444612733534261105518140498470916019690155544383828305309917879815366285404221251555917895519003895679694787504372334672274648925046009358612063933982806162074319636809613156");
    LongNumber sq = beg;
    LongNumber part1 = LongNumber(426880).mult_mod(sq, mod).mult_mod(Q1n, mod);
    LongNumber part2 = (LongNumber(13591409).mult_mod(Q1n, mod) + R1n);
    return part1.div_mod(part2, mod);
}

int main() {
    int mod;
    std::cout << "Enter number of digits after point (up to 499)" << std::endl;
    std::cin >> mod;
    clock_t t1 = clock();
    std::string cand = chudnovsky(std::max(2, mod / 8), mod + 1).to_string();
    while (cand.size() > mod + 2) {
        cand.pop_back();
    }
    std::cout << cand << std::endl;
    clock_t t2 = clock();
    double dur = 1000.0 * (t2 - t1) / CLOCKS_PER_SEC;
    printf("CPU time used (per clock()): %.2f ms\n", dur);
}