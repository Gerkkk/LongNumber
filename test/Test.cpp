#include <gtest/gtest.h>

#include "../Headers/library.h"

using namespace Lnum;

TEST(Compare, comp1) {
LongNumber a = LongNumber(10123123.64850_ln);
LongNumber b = LongNumber("10123123.64850");
auto ans = (a <=> b);
std::strong_ordering ans_int = std::strong_ordering::equal;
EXPECT_EQ(ans, ans_int);
}

TEST(Compare, comp2) {
LongNumber a = LongNumber();
LongNumber b = LongNumber(0.0_ln);
auto ans = (a <=> b);
std::strong_ordering ans_int = std::strong_ordering::equal;
EXPECT_EQ(ans, ans_int);
}

TEST(Compare, comp3) {
LongNumber a = LongNumber("0.000000000000000000000000000002");
LongNumber b = LongNumber("0.0000000000000000000000000000011");
auto ans = (a <=> b);
std::strong_ordering ans_int = std::strong_ordering::greater;
EXPECT_EQ(ans, ans_int);
}

TEST(Compare, comp4) {
LongNumber a = LongNumber("0.000000000000000000000000000001");
LongNumber b = LongNumber("0.0000000000000000000000000000011");
auto ans = (a <=> b);
std::strong_ordering ans_int = std::strong_ordering::less;
EXPECT_EQ(ans, ans_int);
}

TEST(Compare, comp5) {
LongNumber a = LongNumber("0.000000000000000000000000000001");
LongNumber b = LongNumber("0.0000000000000000000000000000011");
auto ans = (a <=> b);
std::strong_ordering ans_int = std::strong_ordering::less;
EXPECT_EQ(ans, ans_int);
}

TEST(Compare, comp6) {
LongNumber a = LongNumber("0.000000000000000000000000000001");
LongNumber b = LongNumber("0.0000000000000000000000000000011");
auto ans = (a > b);
bool ans_int = false;
EXPECT_EQ(ans, ans_int);
}

TEST(Compare, comp7) {
LongNumber a = LongNumber("0.000000000000000000000000000001");
LongNumber b = LongNumber("0.0000000000000000000000000000011");
auto ans = (a < b);
bool ans_int = true;
EXPECT_EQ(ans, ans_int);
}

TEST(Compare, comp8) {
LongNumber a = LongNumber("200.000000000000000000000000000001");
LongNumber b = LongNumber("200.000000000000000000000000000001");
auto ans = (a == b);
bool ans_int = true;
EXPECT_EQ(ans, ans_int);
}

TEST(Compare, comp9) {
LongNumber a = LongNumber("-200.1");
LongNumber b = LongNumber("200.1");
bool ans = (a == b);
bool ans_int = false;
EXPECT_EQ(ans, ans_int);
}


TEST(Compare, comp10) {
LongNumber a = LongNumber("-0.0");
LongNumber b = LongNumber("0.0");
bool ans = (a == b);
bool ans_int = true;
EXPECT_EQ(ans, ans_int);
}

TEST(Compare, comp11) {
LongNumber a = LongNumber("-200.1");
LongNumber b = LongNumber("200.1");
bool ans = (a != b);
bool ans_int = true;
EXPECT_EQ(ans, ans_int);
}

TEST(Compare, comp12) {
LongNumber a = LongNumber("200.1");
LongNumber b = LongNumber("200.1");
bool ans = (a != b);
bool ans_int = false;
EXPECT_EQ(ans, ans_int);
}

TEST(Abs, abs1) {
LongNumber a = LongNumber("10.10922");
auto ans = a.abs();
EXPECT_EQ(ans, a);
}

TEST(Abs, abs2) {
LongNumber a = LongNumber("-10.10922");
auto ans = a.abs();
auto ans_int = LongNumber("10.10922");
EXPECT_EQ(ans, ans_int);
}

TEST(Neg, neg1) {
LongNumber a = LongNumber("-10.10922");
auto ans = -a;
auto ans_int = LongNumber("10.10922");
EXPECT_EQ(ans, ans_int);
}

TEST(Neg, neg2) {
LongNumber a = LongNumber("10.10922");
auto ans = -a;
auto ans_int = LongNumber("-10.10922");
EXPECT_EQ(ans, ans_int);
}

TEST(Add, add1) {
LongNumber a = LongNumber("10.102");
LongNumber b = LongNumber("11.901");
auto ans = (a + b);
auto ans_int = LongNumber("22.003");
EXPECT_EQ(ans, ans_int);
}

TEST(Add, add2) {
LongNumber a = LongNumber("10.102");
LongNumber b = LongNumber("-10.102");
auto ans = (a + b);
auto ans_int = LongNumber("0");
EXPECT_EQ(ans, ans_int);
}

TEST(Add, add3) {
LongNumber a = LongNumber("10.102");
LongNumber b = LongNumber("-10.101");
auto ans = (a + b);
auto ans_int = LongNumber("0.001");
EXPECT_EQ(ans, ans_int);
}

TEST(Add, add4) {
LongNumber a = LongNumber("-10.102");
LongNumber b = LongNumber("10.101");
auto ans = (a + b);
auto ans_int = LongNumber("-0.001");
EXPECT_EQ(ans, ans_int);
}

TEST(Add, add5) {
LongNumber a = LongNumber("-10.101");
LongNumber b = LongNumber("10.102");
auto ans = (a + b);
auto ans_int = LongNumber("0.001");
EXPECT_EQ(ans, ans_int);
}

TEST(Diff, diff1) {
LongNumber a = LongNumber("10.102");
LongNumber b = LongNumber("10.101");
auto ans = (a - b);
auto ans_int = (a + (-b));
EXPECT_EQ(ans, ans_int);
}

TEST(Diff, diff2) {
LongNumber a = LongNumber("10.102");
LongNumber b = LongNumber("10.101");
auto ans = (a - b);
auto ans_int = LongNumber("0.001");
EXPECT_EQ(ans, ans_int);
}

TEST(Diff, diff3) {
LongNumber a = LongNumber("10.101");
LongNumber b = LongNumber("10.101");
auto ans = (a - b);
auto ans_int = LongNumber("0");
EXPECT_EQ(ans, ans_int);
}

TEST(Mult, mult1) {
LongNumber a = LongNumber("2");
LongNumber b = LongNumber("-2");
auto ans = (a * b);
auto ans_int = LongNumber(-4);
EXPECT_EQ(ans, ans_int);
}

TEST(Mult, mult2) {
LongNumber a = LongNumber("202323423.423");
LongNumber b = LongNumber("0");
auto ans = (a * b);
auto ans_int = LongNumber(0);
EXPECT_EQ(ans, ans_int);
}

TEST(Mult, mult3) {
LongNumber a = LongNumber("202323423.423");
LongNumber b = LongNumber("-123.45");
auto ans = (a * b);
auto ans_int = (b * a);
EXPECT_EQ(ans, ans_int);
}

TEST(Mult, mult4) {
LongNumber a = LongNumber("202323942902423.423");
LongNumber b = LongNumber("1");
auto ans = (a * b);
EXPECT_EQ(ans, a);
}

TEST(Mult, mult5) {
LongNumber a = LongNumber("202323942902423.423");
LongNumber b = LongNumber("0.00001");
auto ans = (a * b);
auto cor_ans = LongNumber("2023239429.02423423");
EXPECT_EQ(ans, cor_ans);
}

TEST(Mult, mult6) {
LongNumber a = LongNumber("0");
LongNumber b = LongNumber("0");
auto ans = (a * b);
auto cor_ans = LongNumber("0");
EXPECT_EQ(ans, cor_ans);
}

TEST(Div, div1) {
LongNumber a = LongNumber("1023.45");
LongNumber b = LongNumber("1");
auto ans = (a / b);
EXPECT_EQ(ans, a);
}

TEST(Div, div2) {
LongNumber a = LongNumber("10.234");
LongNumber b = LongNumber("10.234");
auto ans = (a / b);
auto cor_ans = LongNumber(1);
EXPECT_EQ(ans, cor_ans);
}

TEST(Div, div3) {
LongNumber a = LongNumber("10.55");
LongNumber b = LongNumber("12.6");
auto ans = (a / b);
auto cor_ans = LongNumber("0.837301587301587301587301587301587301587301587301586615");
EXPECT_EQ(ans, cor_ans);
}

TEST(Div, div4) {
LongNumber a = LongNumber("-10.55");
LongNumber b = LongNumber("12.6");
auto ans = (a / b);
auto cor_ans = LongNumber("-0.837301587301587301587301587301587301587301587301586615");
EXPECT_EQ(ans, cor_ans);
}

TEST(Div, div5) {
LongNumber a = LongNumber("10.55");
LongNumber b = LongNumber("0");
auto ans = (a / b);
auto cor_ans = LongNumber("0");
EXPECT_EQ(ans, cor_ans);
}

TEST(Div, div6) {
LongNumber a = LongNumber("10.55");
LongNumber b = LongNumber("0.001");
auto ans = (a / b);
auto cor_ans = LongNumber("10550");
EXPECT_EQ(ans, cor_ans);
}

TEST(Div, div7) {
LongNumber a = LongNumber("10.55");
LongNumber b = LongNumber("1000000");
auto ans = (a / b);
auto cor_ans = LongNumber("0.00001055");
EXPECT_EQ(ans, cor_ans);
}

TEST(DivMod, divmod1) {
LongNumber a = LongNumber("10.55");
LongNumber b = LongNumber("12.6");
int mod = 10;
auto ans = a.div_mod(b, mod);
auto cor_ans = LongNumber("0.8373015873");
EXPECT_EQ(ans, cor_ans);
}

TEST(MultMod, multmod1) {
LongNumber a = LongNumber("10.55");
LongNumber b = LongNumber("12.6");
int mod = 10;
auto ans = a.mult_mod(b, mod);
auto cor_ans = LongNumber("132.93");
EXPECT_EQ(ans, cor_ans);
}

TEST(MultMod, multmod2) {
LongNumber a = LongNumber("10.55");
LongNumber b = LongNumber("12.6");
int mod = 2;
auto ans = a.mult_mod(b, mod);
auto cor_ans = LongNumber("132.93");
EXPECT_EQ(ans, cor_ans);
}

TEST(ToString, tostring1) {
std::string s = "-10.55";
LongNumber a = LongNumber(s);
EXPECT_EQ(a.to_string(), s);
}

TEST(ToString, tostring2) {
std::string s = "0.021000";
LongNumber a = LongNumber(0.021_ln);
EXPECT_EQ(a, LongNumber(s));
EXPECT_EQ(a.to_string(), s);
}

TEST(ToString, tostring3) {
std::string s = "-0.021000";
LongNumber a = LongNumber(-0.021_ln);
EXPECT_EQ(a, LongNumber(s));
EXPECT_EQ(a.to_string(), s);
}
