// Test case 1: Divisor is larger than dividend
std::vector<std::pair<power, coeff>> p1{{0, 1}};
std::vector<std::pair<power, coeff>> p2{{1, 1}};
polynomial p11(p1.begin(), p1.end());
polynomial p12(p2.begin(), p2.end());
polynomial result = p11 % p12;
assert(result.canonical_form() == p1);

// Test case 2: Divisor is smaller than dividend
std::vector<std::pair<power, coeff>> p3({{2, 1}, {1, 2}, {0, 1}});
std::vector<std::pair<power, coeff>> p4({{1, 1}, {0, 1}});
std::vector<std::pair<power, coeff>> expected({{0, 1}});
result = p3 % p4;
assert(result == expected);

// Test case 3: Divisor is equal to dividend
std::vector<std::pair<power, coeff>> p5({{2, 1}, {1, 2}, {0, 1}});
std::vector<std::pair<power, coeff>> p6({{2, 1}, {1, 2}, {0, 1}});
expected = polynomial();
result = p5 % p6;
assert(result == expected);

// Test case 4: Dividend is zero polynomial
std::vector<std::pair<power, coeff>> p7;
std::vector<std::pair<power, coeff>> p8({{1, 1}});
expected = polynomial();
result = p7 % p8;
assert(result == expected);

// Test case 5: Divisor is zero polynomial
std::vector<std::pair<power, coeff>> p9({{1, 1}});
std::vector<std::pair<power, coeff>> p10;
try {
    result = p9 % p10;
} catch (const std::invalid_argument& e) {
    assert(std::string(e.what()) == "Division by zero polynomial");
}

// Test case 6: Dividend and divisor have same degree, but different coefficients
std::vector<std::pair<power, coeff>> p11({{2, 1}, {1, 2}, {0, 1}});
std::vector<std::pair<power, coeff>> p12({{2, 2}, {1, 1}, {0, 2}});
expected = {{1, 1}};
polynomial p111(p11.begin(), p11.end());
polynomial p121(p12.begin(), p12.end());
result = p111 % p121;
assert(result == expected);

// Test case 7: Dividend has higher degree than divisor
std::vector<std::pair<power, coeff>> p13({{3, 1}, {2, 2}, {1, 1}, {0, 1}});
std::vector<std::pair<power, coeff>> p14({{1, 1}, {0, 1}});
expected = {{2, 2}, {0, 1}};
polynomial p131(p13.begin(), p13.end());
polynomial p141(p14.begin(), p14.end());
result = p131 % p141;
assert(result == expected);

// Test case 8: Dividend has lower degree than divisor
std::vector<std::pair<power, coeff>> p15({{1, 1}, {0, 1}});
std::vector<std::pair<power, coeff>> p16({{2, 1}, {1, 2}, {0, 1}});
expected = {{1, 1}, {0, 1}};
polynomial p151(p15.begin(), p15.end());
polynomial p161(p16.begin(), p16.end());
result = p151 % p161;
assert(result == expected);

// Test case 9: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p17({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p18({{2, 1}, {1, 2}, {0, 1}});
expected = {{0, 1}};
polynomial p171(p17.begin(), p17.end());
polynomial p181(p18.begin(), p18.end());
result = p171 % p181;
assert(result == expected);

// Test case 10: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p19({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p20({{1, 2}, {2, 1}, {0, 1}});
expected = {{0, 1}};
polynomial p191(p19.begin(), p19.end());
polynomial p201(p20.begin(), p20.end());
result = p191 % p201;
assert(result == expected);

// Test case 11: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p21({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p22({{0, 1}, {2, 1}, {1, 2}});
expected = {{0, 1}};
polynomial p211(p21.begin(), p21.end());
polynomial p221(p22.begin(), p22.end());
result = p211 % p221;
assert(result == expected);

// Test case 12: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p23({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p24({{0, 1}, {1, 2}, {2, 1}});
expected = {{0, 1}};
polynomial p231(p23.begin(), p23.end());
polynomial p241(p24.begin(), p24.end());
result = p231 % p241;
assert(result == expected);

// Test case 13: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p25({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p26({{1, 2}, {0, 1}, {2, 1}});
expected = {{0, 1}};
polynomial p251(p25.begin(), p25.end());
polynomial p261(p26.begin(), p26.end());
result = p251 % p261;
assert(result == expected);

// Test case 14: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p27({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p28({{2, 1}, {0, 1}, {1, 2}});
expected = polynomial();
polynomial p271(p27.begin(), p27.end());
polynomial p281(p28.begin(), p28.end());
result = p271 % p281;
assert(result == expected);

// Test case 15: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p29({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p30({{1, 2}, {2, 1}, {0, 1}});
expected = polynomial();
polynomial p291(p29.begin(), p29.end());
polynomial p301(p30.begin(), p30.end());
result = p291 % p301;
assert(result == expected);

// Test case 16: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p31({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p32({{0, 1}, {2, 1}, {1, 2}});
expected = polynomial();
polynomial p311(p31.begin(), p31.end());
polynomial p321(p32.begin(), p32.end());
result = p311 % p321;
assert(result == expected);

// Test case 17: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p33({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p34({{0, 1}, {1, 2}, {2, 1}});
expected = polynomial();
polynomial p331(p33.begin(), p33.end());
polynomial p341(p34.begin(), p34.end());
result = p331 % p341;
assert(result == expected);

// Test case 18: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p35({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p36({{1, 2}, {0, 1}, {2, 1}});
expected = polynomial();
polynomial p351(p35.begin(), p35.end());
polynomial p361(p36.begin(), p36.end());
result = p351 % p361;
assert(result == expected);

// Test case 19: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p37({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p38({{2, 1}, {0, 1}, {1, 2}});
expected = polynomial();
polynomial p371(p37.begin(), p37.end());
polynomial p381(p38.begin(), p38.end());
result = p371 % p381;
assert(result == expected);

// Test case 20: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p39({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p40({{1, 2}, {2, 1}, {0, 1}});
expected = polynomial();
polynomial p391(p39.begin(), p39.end());
polynomial p401(p40.begin(), p40.end());
result = p391 % p401;
assert(result == expected);

// Test case 21: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p41({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p42({{0, 1}, {2, 1}, {1, 2}});
expected = polynomial();
polynomial p411(p41.begin(), p41.end());
polynomial p421(p42.begin(), p42.end());
result = p411 % p421;
assert(result == expected);

// Test case 22: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p43({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p44({{0, 1}, {1, 2}, {2, 1}});
expected = polynomial();
polynomial p431(p43.begin(), p43.end());
polynomial p441(p44.begin(), p44.end());
result = p431 % p441;
assert(result == expected);

// Test case 23: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p45({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p46({{1, 2}, {0, 1}, {2, 1}});
expected = polynomial();
polynomial p451(p45.begin(), p45.end());
polynomial p461(p46.begin(), p46.end());
result = p451 % p461;
assert(result == expected);

// Test case 24: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p47({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p48({{2, 1}, {0, 1}, {1, 2}});
expected = polynomial();
polynomial p471(p47.begin(), p47.end());
polynomial p481(p48.begin(), p48.end());
result = p471 % p481;
assert(result == expected);

// Test case 25: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p49({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p50({{1, 2}, {2, 1}, {0, 1}});
expected = polynomial();
polynomial p491(p49.begin(), p49.end());
polynomial p501(p50.begin(), p50.end());
result = p491 % p501;
assert(result == expected);

// Test case 26: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p51({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p52({{0, 1}, {2, 1}, {1, 2}});
expected = polynomial();
polynomial p511(p51.begin(), p51.end());
polynomial p521(p52.begin(), p52.end());
result = p511 % p521;
assert(result == expected);

// Test case 27: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p53({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p54({{0, 1}, {1, 2}, {2, 1}});
expected = polynomial();
polynomial p531(p53.begin(), p53.end());
polynomial p541(p54.begin(), p54.end());
result = p531 % p541;
assert(result == expected);

// Test case 28: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p55({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p56({{1, 2}, {0, 1}, {2, 1}});
expected = polynomial();
polynomial p551(p55.begin(), p55.end());
polynomial p561(p56.begin(), p56.end());
result = p551 % p561;
assert(result == expected);

// Test case 29: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p57({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p58({{2, 1}, {0, 1}, {1, 2}});
expected = polynomial();
polynomial p571(p57.begin(), p57.end());
polynomial p581(p58.begin(), p58.end());
result = p571 % p581;
assert(result == expected);

// Test case 30: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p59({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p60({{1, 2}, {2, 1}, {0, 1}});
expected = polynomial();
polynomial p591(p59.begin(), p59.end());
polynomial p601(p60.begin(), p60.end());
result = p591 % p601;
assert(result == expected);

// Test case 31: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p61({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p62({{0, 1}, {2, 1}, {1, 2}});
expected = polynomial();
polynomial p611(p61.begin(), p61.end());
polynomial p621(p62.begin(), p62.end());
result = p611 % p621;
assert(result == expected);

// Test case 32: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p63({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p64({{0, 1}, {1, 2}, {2, 1}});
expected = polynomial();
polynomial p631(p63.begin(), p63.end());
polynomial p641(p64.begin(), p64.end());
result = p631 % p641;
assert(result == expected);

// Test case 33: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p65({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p66({{1, 2}, {0, 1}, {2, 1}});
expected = polynomial();
polynomial p651(p65.begin(), p65.end());
polynomial p661(p66.begin(), p66.end());
result = p651 % p661;
assert(result == expected);

// Test case 34: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p67({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p68({{2, 1}, {0, 1}, {1, 2}});
expected = polynomial();
polynomial p671(p67.begin(), p67.end());
polynomial p681(p68.begin(), p68.end());
result = p671 % p681;
assert(result == expected);

// Test case 35: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p69({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p70({{1, 2}, {2, 1}, {0, 1}});
expected = polynomial();
polynomial p691(p69.begin(), p69.end());
polynomial p701(p70.begin(), p70.end());
result = p691 % p701;
assert(result == expected);

// Test case 36: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p71({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p72({{0, 1}, {2, 1}, {1, 2}});
expected = polynomial();
polynomial p711(p71.begin(), p71.end());
polynomial p721(p72.begin(), p72.end());
result = p711 % p721;
assert(result == expected);

// Test case 37: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p73({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p74({{0, 1}, {1, 2}, {2, 1}});
expected = polynomial();
polynomial p731(p73.begin(), p73.end());
polynomial p741(p74.begin(), p74.end());
result = p731 % p741;
assert(result == expected);

// Test case 38: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p75({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p76({{1, 2}, {0, 1}, {2, 1}});
expected = polynomial();
polynomial p751(p75.begin(), p75.end());
polynomial p761(p76.begin(), p76.end());
result = p751 % p761;
assert(result == expected);

// Test case 39: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p77({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p78({{2, 1}, {0, 1}, {1, 2}});
expected = polynomial();
polynomial p771(p77.begin(), p77.end());
polynomial p781(p78.begin(), p78.end());
result = p771 % p781;
assert(result == expected);

// Test case 40: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p79({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p80({{1, 2}, {2, 1}, {0, 1}});
expected = polynomial();
polynomial p791(p79.begin(), p79.end());
polynomial p801(p80.begin(), p80.end());
result = p791 % p801;
assert(result == expected);

// Test case 41: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p81({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p82({{0, 1}, {2, 1}, {1, 2}});
expected = polynomial();
polynomial p811(p81.begin(), p81.end());
polynomial p821(p82.begin(), p82.end());
result = p811 % p821;
assert(result == expected);

// Test case 42: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p83({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p84({{0, 1}, {1, 2}, {2, 1}});
expected = polynomial();
polynomial p831(p83.begin(), p83.end());
polynomial p841(p84.begin(), p84.end());
result = p831 % p841;
assert(result == expected);

// Test case 43: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p85({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p86({{1, 2}, {0, 1}, {2, 1}});
expected = polynomial();
polynomial p851(p85.begin(), p85.end());
polynomial p861(p86.begin(), p86.end());
result = p851 % p861;
assert(result == expected);

// Test case 44: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p87({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p88({{2, 1}, {0, 1}, {1, 2}});
expected = polynomial();
polynomial p871(p87.begin(), p87.end());
polynomial p881(p88.begin(), p88.end());
result = p871 % p881;
assert(result == expected);

// Test case 45: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p89({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p90({{1, 2}, {2, 1}, {0, 1}});
expected = polynomial();
polynomial p891(p89.begin(), p89.end());
polynomial p901(p90.begin(), p90.end());
result = p891 % p901;
assert(result == expected);

// Test case 46: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p91({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p92({{0, 1}, {2, 1}, {1, 2}});
expected = polynomial();
polynomial p911(p91.begin(), p91.end());
polynomial p921(p92.begin(), p92.end());
result = p911 % p921;
assert(result == expected);

// Test case 47: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p93({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p94({{0, 1}, {1, 2}, {2, 1}});
expected = polynomial();
polynomial p931(p93.begin(), p93.end());
polynomial p941(p94.begin(), p94.end());
result = p931 % p941;
assert(result == expected);

// Test case 48: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p95({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p96({{1, 2}, {0, 1}, {2, 1}});
expected = polynomial();
polynomial p951(p95.begin(), p95.end());
polynomial p961(p96.begin(), p96.end());
result = p951 % p961;
assert(result == expected);

// Test case 49: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p97({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p98({{2, 1}, {0, 1}, {1, 2}});
expected = polynomial();
polynomial p971(p97.begin(), p97.end());
polynomial p981(p98.begin(), p98.end());
result = p971 % p981;
assert(result == expected);

// Test case 50: Dividend and divisor have same degree and coefficients, but different order
std::vector<std::pair<power, coeff>> p99({{2, 1}, {0, 1}, {1, 2}});
std::vector<std::pair<power, coeff>> p100({{1, 2}, {2, 1}, {0, 1}});
expected = polynomial();
polynomial p991(p99.begin(), p99.end());
polynomial p1001(p100.begin(), p100.end());
result = p991 % p1001;
assert(result == expected);