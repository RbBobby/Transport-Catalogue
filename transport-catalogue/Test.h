#pragma once
#include "stat_reader.h"
#include "input_reader.h"
#include "transport_catalogue.h"

#include <iostream>
#include <sstream>
#include <cassert>

using namespace transport_catalogue;
using namespace transport_catalogue::input;
using namespace transport_catalogue::stat;
void TestTaskData() {

    TransportCatalogue transport_catalogue;
    std::istringstream input{
        "10\n"
"Stop Tolstopaltsevo : 55.611087, 37.208290\n"
"Stop Marushkino : 55.595884, 37.209755\n"
"Bus 256 : Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\n"
"Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka\n"
"Stop Rasskazovka : 55.632761, 37.333324\n"
"Stop Biryulyovo Zapadnoye : 55.574371, 37.651700\n"
"Stop Biryusinka : 55.581065, 37.648390\n"
"Stop Universam : 55.587655, 37.645687\n"
"Stop Biryulyovo Tovarnaya : 55.592028, 37.653656\n"
"Stop Biryulyovo Passazhirskaya : 55.580999, 37.659164\n"
    };

    InputReader Input(input, transport_catalogue);
    std::istringstream output{
    "3\n"
        "Bus 256\n"
        "Bus 750\n"
        "Bus 751\n"
    };

    std::ostringstream out_stream;

    StatReader Stat(output, out_stream, transport_catalogue);

    std::string str = out_stream.str();

    assert(str == "Bus 256: 6 stops on route, 5 unique stops, 4371.02 route length\nBus 750: 5 stops on route, 3 unique stops, 20939.5 route length\nBus 751: not found\n");

    std::cerr << "TEST defolt task OK\n";
}


void TestFileData() {

    TransportCatalogue transport_catalogue;
    std::istringstream input{
        "300\n"
"Stop 97ChPsiaFJ xk : 38.590881, 34.724362\n"
"Stop nhfM4 : 38.653078, 34.910424\n"
"Bus pUFj82Cqn3 : QdPEP6 - w7V0IyAT4IqNKF7fFFyBq4B - h1OTf - aaDrzCkRa - G3o0bW - EJWKVw2R8gv6Od3J9NRC0UYq - JWt2HAu - lBP - TiqAnSNScH1 - fgO6d5U - L5pcYa50O j4etgtHGQt - A9OtxLHuKLO - G3o0bW - 4xyPd - HUb6xd4aaSJ01lo0ABt - 3 - A9OtxLHuKLO - FG - mOA - 4J jy2z - TiqAnSNScH1 - h - E - aaDrzCkRa - 01Z6NQhKl2UUkghq - 4xyPd - xn58ceA wXl0wo6fw1 - AiaFM3aIkyqmjhx\n"
"Bus wSX9kMv5NmodztTukEuRAkf8P : MRWeEEANMtzBJ8z - mbn1HhDBYL1 - Yd 6DHbRbROdw - Rz - Jkc - qaqYVmrgqP76mxDYebu08xF8E - v8yUoEHDcAR5K - CahFZzk - bATIYunTC9Z5XN0bk0FBq7 - lYPJidFhhh8qIjg0chE - fPX2y - eX02k7tW0j L2d7akVudao - w7V0IyAT4IqNKF7fFFyBq4B - SfV395Nnm1OrpX - 9uyCGpPMbWiXVAwsXG - mq35 - w7V0IyAT4IqNKF7fFFyBq4B\n"
"Bus EsjlC2AZFowRZ : ISlrnEIaKIEkpE4XC - 9n4lv - oM6 - iClhA6PCp1zjYNxCSdlF7Mzs - mOA - ur4VppUI3StmJP - QexzWmRfZ7VpKt0h - mTQElWNWMb99mLHtKSAt - 9kHYrxYT6UCUGcLH - CahFZzk - WGlidYF - esRv7H4ulnA9xmUm7cHCI8Q - SxvGUp9OhePe4pW FQfn - PCKCn - UA - 5UQ4TtSaNNs5SKSEHuTUKdh - xn58ceA wXl0wo6fw1 - zqIUaW3xbhG - 6ik0QUeq6YE2ZPf8fem - una0tkDG67WY2DKJlyGq - mT - dNWXYAy9UgTq - Rz - 4J jy2z - Jkc - KZ8 - CahFZzk - SxvGUp9OhePe4pW FQfn - eNJHau6B8 - v8yUoEHDcAR5K - KZ8 - bdIWPK1kWMN7wvJ7zl8Cgt7m - rOdgQuDph - t3R2RdoIYE0G4Z - G3o0bW - jwQ5 VVfrFgl0mL8hINmugEf - oVtcsLqV72 - esRv7H4ulnA9xmUm7cHCI8Q - QOW7FWL5v5kdJBk3RDCZg - wumWKUk63DWuiNF6nqpiiDSSf - 4J jy2z - L5pcYa50O j4etgtHGQt - jDThdjhjh2n7Wc - wEToSr8wPMLRaGmEorqMHF1e - QOW7FWL5v5kdJBk3RDCZg\n"
"Bus 2MxT: 9W6KH8pazOTFPc3zss7E3 - N0WC - J3GnXuZAAGf3oaa - xn58ceA wXl0wo6fw1 - 9kHYrxYT6UCUGcLH - esRv7H4ulnA9xmUm7cHCI8Q - YAMY0OvPvxZF2BlAzg - sHYiT9RK4sqe2\n"
"Bus sA50azC97OMPt3BPX : tPniDCwlR > UsaQup0GVKc2oPtsPdvk > L5pcYa50O j4etgtHGQt > XiIL1rrRfmLsCvs4t1 C4AzoT > 47SX 1ZvTKPGQJfaRaBJNN > HL > sHYiT9RK4sqe2 > OyB2TTwVRcMgD > tPniDCwlR > EJWKVw2R8gv6Od3J9NRC0UYq > BWMGV > Mzx > 7qpKAGotrE6vi5OEmh8Txf > imrGYjUSoKaMoOeEV > CahFZzk > TBP4AGPZg3GOQj5 zjGx j > 2fRakl6iS0cVl > tQVD77CEYItf6vMk279fDk > OJOci4wu2 > 2fRakl6iS0cVl > 01Z6NQhKl2UUkghq > dNWXYAy9UgTq > rOdgQuDph > WRo4l > ImEcfBE3Czdoa3 > TBP4AGPZg3GOQj5 zjGx j > 7iWYyQimeYwd56Ynj57 > 13ThLjYG > Mzx > QdPEP6 > oVtcsLqV72 > aBZFsZCWEVhVMbSMvuI7b > xn58ceA wXl0wo6fw1 > 7hSQl1n2m > MRWeEEANMtzBJ8z > JWt2HAu > P > kbU > 4xyPd > YN4J5hLU4vuP3UgrRt0soPVP > aaDrzCkRa > Y > KrSJ2LfG1Qo8EEttx > m > TBP4AGPZg3GOQj5 zjGx j > m > YN4J5hLU4vuP3UgrRt0soPVP > t3R2RdoIYE0G4Z > 1GzQO9dYIm0me > juAdbG4 > v8yUoEHDcAR5K > 7qpKAGotrE6vi5OEmh8Txf > VzkY8gVB > aAqPX > A3fg4VGWEfhi7pgZnWWtYs0wH > 2IuMsuRbGaGlT > eRlE31fLpeOfK5vSHL > PWIHxixUS8ROFlMqFTPXA > W93vQSGbE2mnskhufqwc > hq0ln 4A7RoGuAxeTUZaBTaNp > XB5NAUcKh yDNGkD7EtQ8 > QdPEP6 > wumWKUk63DWuiNF6nqpiiDSSf > PWIHxixUS8ROFlMqFTPXA > lBP > h230yZ > ImEcfBE3Czdoa3 > tPniDCwlR\n"
"Stop Mzx : 38.569868, 34.79233\n"
"Stop jmRffEd : 38.674352, 34.889454\n"
"Bus ukHDNN4j 1aj5vB7TJsGhg: jmRffEd - 47SX 1ZvTKPGQJfaRaBJNN - kpt - Sfskshp83VkmueW7t - ISlrnEIaKIEkpE4XC - RCMbeebIuxiDV - KoAi8XSxyu x - QdPEP6 - c0p1aqDEdlepF - E - umomAjuO - eNJHau6B8 - mq35 - Jkc - lBP - m - 4pa5EXOMn4kJeA - x6uAyDnts4HKRzp1XNol5 - aXYObzMStKKrHU4O - FG - jwQ5 VVfrFgl0mL8hINmugEf - TiqAnSNScH1 - aiAnA4AhBRojwfcFz - lYPJidFhhh8qIjg0chE - v8yUoEHDcAR5K - Yd 6DHbRbROdw - imrGYjUSoKaMoOeEV - h1OTf - dNWXYAy9UgTq - kbU - b5jXJLSbbBnQZsJ4OVJ87Nzf - BWMGV - lBP - Yki5weXl - CahFZzk - eX02k7tW0j L2d7akVudao - ztVWFuioD - pKIPR92hm - 8 - 0y4ho9GnEYu21UmoV42HZB0Mv - M2EClC - Q1yE - XmnTYd9cySp - 5UQ4TtSaNNs5SKSEHuTUKdh - hhmpyF gEZCyMurPa\n"
"Stop QexzWmRfZ7VpKt0h : 38.654274, 34.691305\n"
"Bus n : umomAjuO - UsaQup0GVKc2oPtsPdvk - f4mV - FNJOLqRq5Ad3N2qj - id aFBFmo9u7 - ImEcfBE3Czdoa3 - NKoCAqHa55 - lBP - sHYiT9RK4sqe2 - z - 97ChPsiaFJ xk - jg6oInTF0IOQjanfDYimaM - OyB2TTwVRcMgD - jwQ5 VVfrFgl0mL8hINmugEf - esRv7H4ulnA9xmUm7cHCI8Q - MRWeEEANMtzBJ8z - WUobJ5iHPZ974O - uwp6XK - WUobJ5iHPZ974O\n"
"Stop l3A : 38.460784, 34.937663\n"
"Stop kv8A5AKGj iN : 38.716203, 34.779089\n"
"Stop RCMbeebIuxiDV : 38.700196, 34.821645\n"
"Stop vA : 38.708395, 34.867487\n"
"Stop gdhjubQAp3ZEgHbYdb : 38.417503, 34.965038\n"
"Bus 2NLdbAzIUGKD: Q1yE - 9n4lv - HL - m - QdPEP6 - 8 - jDThdjhjh2n7Wc - G3o0bW - f6mSgT ud5 - 4pa5EXOMn4kJeA - oM6 - HL - MRWeEEANMtzBJ8z - Lp4MEdrq6otSB - eX02k7tW0j L2d7akVudao - z - 0y4ho9GnEYu21UmoV42HZB0Mv - jmRffEd - PWIHxixUS8ROFlMqFTPXA - RopMyKExUGlJSvuPjDjAWD - jmRffEd - z - AiaFM3aIkyqmjhx - 2fRakl6iS0cVl - mT - b5jXJLSbbBnQZsJ4OVJ87Nzf - z - KZ8 - fPX2y - WUobJ5iHPZ974O - QdPEP6 - g0xPM - h230yZ - 4xyPd - t3R2RdoIYE0G4Z - imrGYjUSoKaMoOeEV - yH6T6hYNXvjylXoM0uqb - A9OtxLHuKLO - mkmqHwVr8gzfTQfL294 - K - w7V0IyAT4IqNKF7fFFyBq4B - AiaFM3aIkyqmjhx - 0y4ho9GnEYu21UmoV42HZB0Mv\n"
"Stop VUtPzvEGpkYiJ8B7D2HmYkrci : 38.520254, 34.649199\n"
"Bus 876c40RmluF: J3GnXuZAAGf3oaa > aiAnA4AhBRojwfcFz > aXYObzMStKKrHU4O > 7hSQl1n2m > P > fPX2y > JWt2HAu > 47SX 1ZvTKPGQJfaRaBJNN > tQVD77CEYItf6vMk279fDk > RopMyKExUGlJSvuPjDjAWD > 9n4lv > llbORb4gdec4Y29 > fPX2y > mTQElWNWMb99mLHtKSAt > tPniDCwlR > v8yUoEHDcAR5K > lYPJidFhhh8qIjg0chE > c0p1aqDEdlepF > f4mV > AiaFM3aIkyqmjhx > h230yZ > x6uAyDnts4HKRzp1XNol5 > Z6WXRBiOsQBSywzKrhupa > KYszEJBfpaUkVjw5q6j > XiIL1rrRfmLsCvs4t1 C4AzoT > Lp4MEdrq6otSB > 5UQ4TtSaNNs5SKSEHuTUKdh > WGlidYF > RCMbeebIuxiDV > h > U49MIbaw4gamvekq > AC9t > aBZFsZCWEVhVMbSMvuI7b > ISlrnEIaKIEkpE4XC > gtm9BlpE8bAkxfHCPiz67Xs > wCZucJLumbtAX > mbn1HhDBYL1 > VUtPzvEGpkYiJ8B7D2HmYkrci > qC > A9OtxLHuKLO > mT > M2EClC > VzkY8gVB > QbvTBD > VUZ5 > YAMY0OvPvxZF2BlAzg > rOdgQuDph > c7vc3yBR > wCZucJLumbtAX > A9OtxLHuKLO > Lp4MEdrq6otSB > CahFZzk > E > 6erXqFth8x18P5BxH50SAu7 > 9uyCGpPMbWiXVAwsXG > WRo4l > C YdccGQZU6gbJL0mXX6IToE > HL > jDThdjhjh2n7Wc > 6x9ftRRGWjuUTQQ > qaqYVmrgqP76mxDYebu08xF8E > WGlidYF > 1GzQO9dYIm0me > aiAnA4AhBRojwfcFz > PWIHxixUS8ROFlMqFTPXA > jwQ5 VVfrFgl0mL8hINmugEf > una0tkDG67WY2DKJlyGq > 6x9ftRRGWjuUTQQ > w0PgbVmxAHFGF > 7qpKAGotrE6vi5OEmh8Txf > o > id aFBFmo9u7 > FiWYnMOOgvGlRS51l 2iP1ltP > h230yZ > M2EClC > Y7UB UGH5 > RjQCxV2X2hcA > gtm9BlpE8bAkxfHCPiz67Xs > 7hSQl1n2m > nhfM4 > fgO6d5U > w0PgbVmxAHFGF > gtm9BlpE8bAkxfHCPiz67Xs > Lp4MEdrq6otSB > A3fg4VGWEfhi7pgZnWWtYs0wH > Rz > J3GnXuZAAGf3oaa\n"
"Stop o : 38.523939, 34.886784\n"
"Stop t3R2RdoIYE0G4Z : 38.702836, 34.936086\n"
"Stop CahFZzk : 38.612466, 34.715042\n"
"Stop lYPJidFhhh8qIjg0chE : 38.453293, 34.826418\n"
"Bus iBAbvykyUAujN : 7qpKAGotrE6vi5OEmh8Txf > T893Gm > 0y4ho9GnEYu21UmoV42HZB0Mv > w7V0IyAT4IqNKF7fFFyBq4B > Lp4MEdrq6otSB > g0xPM > RCMbeebIuxiDV > A9OtxLHuKLO > YN4J5hLU4vuP3UgrRt0soPVP > qC > wCZucJLumbtAX > Y > 97ChPsiaFJ xk > BWMGV > 9uyCGpPMbWiXVAwsXG > hhmpyF gEZCyMurPa > una0tkDG67WY2DKJlyGq > U49MIbaw4gamvekq > K > KZ8 > TiqAnSNScH1 > bdIWPK1kWMN7wvJ7zl8Cgt7m > J3GnXuZAAGf3oaa > 6x9ftRRGWjuUTQQ > l3A > 9uyCGpPMbWiXVAwsXG > JWt2HAu > l3A > w7V0IyAT4IqNKF7fFFyBq4B > iClhA6PCp1zjYNxCSdlF7Mzs > EJWKVw2R8gv6Od3J9NRC0UYq > umomAjuO > FNJOLqRq5Ad3N2qj > QexzWmRfZ7VpKt0h > XEQUDl69zPpE9 > KZ8 > 6BXJi1odEOF3gnQkcH > eX02k7tW0j L2d7akVudao > aBZFsZCWEVhVMbSMvuI7b > tPniDCwlR > U3KBygTDyqkvCtB6o8 > VzkY8gVB > eX02k7tW0j L2d7akVudao > kbU > YAMY0OvPvxZF2BlAzg > TiqAnSNScH1 > zqIUaW3xbhG > T893Gm > rOdgQuDph > juAdbG4 > U3KBygTDyqkvCtB6o8 > bdIWPK1kWMN7wvJ7zl8Cgt7m > T893Gm > 6ik0QUeq6YE2ZPf8fem > h230yZ > kpt > oM6 > RopMyKExUGlJSvuPjDjAWD > FG > 2fRakl6iS0cVl > eRlE31fLpeOfK5vSHL > W93vQSGbE2mnskhufqwc > SxvGUp9OhePe4pW FQfn > pCumWQzxe 4xL4eWNY > C YdccGQZU6gbJL0mXX6IToE > zqIUaW3xbhG > SfV395Nnm1OrpX > wEToSr8wPMLRaGmEorqMHF1e > W93vQSGbE2mnskhufqwc > U49MIbaw4gamvekq > Sfskshp83VkmueW7t > RCMbeebIuxiDV > M2EClC > mTQElWNWMb99mLHtKSAt > MRWeEEANMtzBJ8z > juAdbG4 > pCumWQzxe 4xL4eWNY > eRlE31fLpeOfK5vSHL > z > jmRffEd > KoAi8XSxyu x > mTQElWNWMb99mLHtKSAt > uwp6XK > bATIYunTC9Z5XN0bk0FBq7 > 97ChPsiaFJ xk > 7qpKAGotrE6vi5OEmh8Txf\n"
"Stop f4mV : 38.492512, 34.665361\n"
"Stop m : 38.559248, 34.908154\n"
"Stop HL : 38.568337, 34.759169\n"
"Stop 4pa5EXOMn4kJeA: 38.55838, 34.814016\n"
"Stop 9n4lv: 38.683261, 34.986239\n"
"Stop QdPEP6 : 38.675193, 34.930785\n"
"Stop jDThdjhjh2n7Wc : 38.714647, 34.950007\n"
"Stop JWt2HAu : 38.556566, 34.763657\n"
"Stop qaqYVmrgqP76mxDYebu08xF8E : 38.658591, 34.921405\n"
"Bus C : 97ChPsiaFJ xk - hq0ln 4A7RoGuAxeTUZaBTaNp - c0p1aqDEdlepF - nhfM4 - CahFZzk - 1GzQO9dYIm0me - eRlE31fLpeOfK5vSHL - VzkY8gVB - Rz - XmnTYd9cySp - Mzx - HoZGABAZFoCFmJDO7U - 6x9ftRRGWjuUTQQ - 5UQ4TtSaNNs5SKSEHuTUKdh - yH6T6hYNXvjylXoM0uqb - E - N0WC - XiIL1rrRfmLsCvs4t1 C4AzoT - eX02k7tW0j L2d7akVudao\n"
"Bus ZGcqi3Xf8e : tQVD77CEYItf6vMk279fDk - u1lesMakDVZdJUyBO96wnYX4 - 97ChPsiaFJ xk - g0xPM - 4J jy2z - 4pa5EXOMn4kJeA - f4mV - 13ThLjYG - 2IuMsuRbGaGlT - v8yUoEHDcAR5K - xn58ceA wXl0wo6fw1 - 9uyCGpPMbWiXVAwsXG - lBP - 9kHYrxYT6UCUGcLH - fPX2y - 6BXJi1odEOF3gnQkcH - Rmxlj6yf5V6Hr1 6JPY9 - zqIUaW3xbhG - RCMbeebIuxiDV - mbn1HhDBYL1 - luOV urWGCs - PCKCn - mT - WUobJ5iHPZ974O - 6DlTRiDlBADHd5wxuGwM - eRlE31fLpeOfK5vSHL - w0PgbVmxAHFGF - xn58ceA wXl0wo6fw1 - U3KBygTDyqkvCtB6o8 - una0tkDG67WY2DKJlyGq - JoLcJeV8gQAS - TiqAnSNScH1 - jDThdjhjh2n7Wc - imrGYjUSoKaMoOeEV - x6uAyDnts4HKRzp1XNol5 - b5jXJLSbbBnQZsJ4OVJ87Nzf - fPX2y - JWt2HAu - aXYObzMStKKrHU4O - aiAnA4AhBRojwfcFz - A9OtxLHuKLO - Yki5weXl - 6ik0QUeq6YE2ZPf8fem - imrGYjUSoKaMoOeEV - hXCtNJ55eAcJyF - aBZFsZCWEVhVMbSMvuI7b - hXCtNJ55eAcJyF - QbvTBD - ztVWFuioD - tQVD77CEYItf6vMk279fDk\n"
"Stop VUZ5 : 38.661751, 34.897393\n"
"Stop 6DlTRiDlBADHd5wxuGwM: 38.441063, 34.952196\n"
"Bus CA4KwLqpD0Bdy8y : J0X8xdE3epu2 > SfV395Nnm1OrpX > QdPEP6 > E > P > U49MIbaw4gamvekq > hXCtNJ55eAcJyF > 7hSQl1n2m > 5RMNaOqZQp8CBhdok > f4mV > mbn1HhDBYL1 > OJOci4wu2 > kv8A5AKGj iN > BWMGV > A2cG0537NQS > WRo4l > FG > id aFBFmo9u7 > oVtcsLqV72 > oM6 > HL > UsaQup0GVKc2oPtsPdvk > fPX2y > mTQElWNWMb99mLHtKSAt > PWIHxixUS8ROFlMqFTPXA > A3fg4VGWEfhi7pgZnWWtYs0wH > AiaFM3aIkyqmjhx > tQVD77CEYItf6vMk279fDk > mq35 > U3KBygTDyqkvCtB6o8 > hXCtNJ55eAcJyF > w7V0IyAT4IqNKF7fFFyBq4B > jDThdjhjh2n7Wc > 5RMNaOqZQp8CBhdok > tPniDCwlR > qaqYVmrgqP76mxDYebu08xF8E > mkmqHwVr8gzfTQfL294 > ISlrnEIaKIEkpE4XC > YN4J5hLU4vuP3UgrRt0soPVP > wumWKUk63DWuiNF6nqpiiDSSf > aBZFsZCWEVhVMbSMvuI7b > dSzlIy80Uq nSpdPYp > UsaQup0GVKc2oPtsPdvk > jg6oInTF0IOQjanfDYimaM > OJOci4wu2 > fPX2y > fgO6d5U > A2cG0537NQS > 2IuMsuRbGaGlT > c0p1aqDEdlepF > PWIHxixUS8ROFlMqFTPXA > 6x9ftRRGWjuUTQQ > OJOci4wu2 > imrGYjUSoKaMoOeEV > hq0ln 4A7RoGuAxeTUZaBTaNp > AC9t > QdPEP6 > u1lesMakDVZdJUyBO96wnYX4 > XmnTYd9cySp > 7pyxD HFSz1P > RjQCxV2X2hcA > o > WUobJ5iHPZ974O > KIITYxZQM > EyivPqCySBygp4AaXYcEw > OyB2TTwVRcMgD > SfV395Nnm1OrpX > c0p1aqDEdlepF > aaDrzCkRa > l3A > XrjmSdG6CmrQwxfWN8ehJ > bdIWPK1kWMN7wvJ7zl8Cgt7m > kbU > 0y4ho9GnEYu21UmoV42HZB0Mv > mTQElWNWMb99mLHtKSAt > aBZFsZCWEVhVMbSMvuI7b > RCMbeebIuxiDV > 4xyPd > ImEcfBE3Czdoa3 > RjQCxV2X2hcA > 7hSQl1n2m > oVtcsLqV72 > jDThdjhjh2n7Wc > WUobJ5iHPZ974O > 01Z6NQhKl2UUkghq > A9OtxLHuKLO > mq35 > HoZGABAZFoCFmJDO7U > tQVD77CEYItf6vMk279fDk > AC9t > eX02k7tW0j L2d7akVudao > PWIHxixUS8ROFlMqFTPXA > J0X8xdE3epu2\n"
"Stop FNJOLqRq5Ad3N2qj : 38.440301, 34.668904\n"
"Stop id aFBFmo9u7 : 38.612529, 34.841709\n"
"Stop 01Z6NQhKl2UUkghq: 38.400504, 34.945975\n"
"Stop 9W6KH8pazOTFPc3zss7E3: 38.481306, 34.783387\n"
"Stop SfV395Nnm1OrpX : 38.607839, 34.720273\n"
"Bus Wf1W7QJtoSL : iClhA6PCp1zjYNxCSdlF7Mzs > 6ik0QUeq6YE2ZPf8fem > QdPEP6 > ztVWFuioD > WRo4l > VUZ5 > g0xPM > 2fRakl6iS0cVl > luOV urWGCs > w7V0IyAT4IqNKF7fFFyBq4B > Lp4MEdrq6otSB > XrjmSdG6CmrQwxfWN8ehJ > yH6T6hYNXvjylXoM0uqb > aBZFsZCWEVhVMbSMvuI7b > W93vQSGbE2mnskhufqwc > imrGYjUSoKaMoOeEV > RopMyKExUGlJSvuPjDjAWD > XrjmSdG6CmrQwxfWN8ehJ > VUtPzvEGpkYiJ8B7D2HmYkrci > Sfskshp83VkmueW7t > qC > WRo4l > KrSJ2LfG1Qo8EEttx > Rz > eRlE31fLpeOfK5vSHL > iClhA6PCp1zjYNxCSdlF7Mzs\n"
"Stop hXCtNJ55eAcJyF : 38.574429, 34.836525\n"
"Stop fPX2y : 38.500528, 34.657029\n"
"Stop NKoCAqHa55 : 38.61489, 34.962469\n"
"Stop z : 38.576576, 34.968404\n"
"Bus t5scblYTnfH6syDjvpdMOxY : Mzx - xn58ceA wXl0wo6fw1 - aiAnA4AhBRojwfcFz - 1GzQO9dYIm0me - ztVWFuioD - wEToSr8wPMLRaGmEorqMHF1e - kv8A5AKGj iN - Mzx - P - b5jXJLSbbBnQZsJ4OVJ87Nzf - U49MIbaw4gamvekq - 6erXqFth8x18P5BxH50SAu7 - FiWYnMOOgvGlRS51l 2iP1ltP - h1OTf - mbn1HhDBYL1 - wumWKUk63DWuiNF6nqpiiDSSf - h1OTf - RZIBvXF6op2sX5cURx - Z6WXRBiOsQBSywzKrhupa - 6x9ftRRGWjuUTQQ - aXYObzMStKKrHU4O\n"
"Stop LXt9PS4RSuqsisxyQkDZGH0 : 38.418104, 34.665777\n"
"Stop mTQElWNWMb99mLHtKSAt : 38.699459, 34.827361\n"
"Stop hq0ln 4A7RoGuAxeTUZaBTaNp: 38.496787, 34.749266\n"
"Stop bdIWPK1kWMN7wvJ7zl8Cgt7m : 38.398262, 34.729076\n"
"Stop QbW : 38.439847, 34.875072\n"
"Stop TiqAnSNScH1 : 38.483971, 34.759343\n"
"Stop U49MIbaw4gamvekq : 38.50034, 34.728898\n"
"Stop juAdbG4 : 38.482122, 34.679479\n"
"Stop 7qjQYTatbsF928i 4: 38.457814, 34.805291\n"
"Bus 0d6: h230yZ - EyivPqCySBygp4AaXYcEw - 1GzQO9dYIm0me - XmnTYd9cySp - SfV395Nnm1OrpX - t3R2RdoIYE0G4Z - XiIL1rrRfmLsCvs4t1 C4AzoT - QexzWmRfZ7VpKt0h - FNJOLqRq5Ad3N2qj - QOW7FWL5v5kdJBk3RDCZg - HUb6xd4aaSJ01lo0ABt - 47SX 1ZvTKPGQJfaRaBJNN - EJWKVw2R8gv6Od3J9NRC0UYq - gdhjubQAp3ZEgHbYdb - sHYiT9RK4sqe2 - tQVD77CEYItf6vMk279fDk - qaqYVmrgqP76mxDYebu08xF8E - 01Z6NQhKl2UUkghq - U3KBygTDyqkvCtB6o8 - mT - oM6 - W93vQSGbE2mnskhufqwc - mOA - sHYiT9RK4sqe2\n"
"Bus yiKTH6e6u50I kgvlXG : t3R2RdoIYE0G4Z - C YdccGQZU6gbJL0mXX6IToE - luOV urWGCs - P - UA - jwQ5 VVfrFgl0mL8hINmugEf - CahFZzk - kpt - KYszEJBfpaUkVjw5q6j - bATIYunTC9Z5XN0bk0FBq7 - ImEcfBE3Czdoa3 - Jkc\n"
"Stop jwQ5 VVfrFgl0mL8hINmugEf : 38.410292, 34.783164\n"
"Stop BWMGV : 38.673999, 34.944972\n"
"Stop YAMY0OvPvxZF2BlAzg : 38.392826, 34.761138\n"
"Bus CfAk6rjAF5Ucu26cCHpA : J3GnXuZAAGf3oaa - 4pa5EXOMn4kJeA - Yd 6DHbRbROdw - 47SX 1ZvTKPGQJfaRaBJNN - MeOzi4ywCT1W7xFOA5h - 6BXJi1odEOF3gnQkcH - VUtPzvEGpkYiJ8B7D2HmYkrci - 5UQ4TtSaNNs5SKSEHuTUKdh - mkmqHwVr8gzfTQfL294 - OyB2TTwVRcMgD - XmnTYd9cySp - tPniDCwlR - WRo4l - QbvTBD - 4J jy2z - c0p1aqDEdlepF - aBZFsZCWEVhVMbSMvuI7b - Y7UB UGH5 - 2IuMsuRbGaGlT - una0tkDG67WY2DKJlyGq - 6BXJi1odEOF3gnQkcH - PWIHxixUS8ROFlMqFTPXA - ImEcfBE3Czdoa3 - KZ8 - gtm9BlpE8bAkxfHCPiz67Xs - YN4J5hLU4vuP3UgrRt0soPVP - gtm9BlpE8bAkxfHCPiz67Xs - 9W6KH8pazOTFPc3zss7E3 - QbW - mbn1HhDBYL1 - 13ThLjYG - 7qjQYTatbsF928i 4 - BWMGV - llbORb4gdec4Y29\n"
"Bus ixbiNlw : sHYiT9RK4sqe2 - w7V0IyAT4IqNKF7fFFyBq4B - JoLcJeV8gQAS - kbU - aBZFsZCWEVhVMbSMvuI7b - JWt2HAu - ImEcfBE3Czdoa3 - 6ik0QUeq6YE2ZPf8fem - 3\n"
"Stop c7vc3yBR : 38.477151, 34.684103\n"
"Stop umomAjuO : 38.621338, 34.648199\n"
"Bus HuX8Yabr : FNJOLqRq5Ad3N2qj > wCZucJLumbtAX > P > WUobJ5iHPZ974O > mT > XB5NAUcKh yDNGkD7EtQ8 > oM6 > PCKCn > FG > 6erXqFth8x18P5BxH50SAu7 > juAdbG4 > N0WC > 4J jy2z > kpt > Jkc > id aFBFmo9u7 > TiqAnSNScH1 > MeOzi4ywCT1W7xFOA5h > wumWKUk63DWuiNF6nqpiiDSSf > RopMyKExUGlJSvuPjDjAWD > G3o0bW > W93vQSGbE2mnskhufqwc > jmRffEd > 4xyPd > 2IuMsuRbGaGlT > QOW7FWL5v5kdJBk3RDCZg > Yki5weXl > g0xPM > U3KBygTDyqkvCtB6o8 > PWIHxixUS8ROFlMqFTPXA > 7iWYyQimeYwd56Ynj57 > b5jXJLSbbBnQZsJ4OVJ87Nzf > oM6 > kpt > KYszEJBfpaUkVjw5q6j > VUtPzvEGpkYiJ8B7D2HmYkrci > U49MIbaw4gamvekq > C YdccGQZU6gbJL0mXX6IToE > wCZucJLumbtAX > jwQ5 VVfrFgl0mL8hINmugEf > J3GnXuZAAGf3oaa > lYPJidFhhh8qIjg0chE > 5UQ4TtSaNNs5SKSEHuTUKdh > 7pyxD HFSz1P > tQVD77CEYItf6vMk279fDk > mTQElWNWMb99mLHtKSAt > o > eRlE31fLpeOfK5vSHL > 9uyCGpPMbWiXVAwsXG > tPniDCwlR > 6DlTRiDlBADHd5wxuGwM > dSzlIy80Uq nSpdPYp > 4pa5EXOMn4kJeA > J3GnXuZAAGf3oaa > FNJOLqRq5Ad3N2qj\n"
"Stop P : 38.393996, 34.665324\n"
"Stop HoZGABAZFoCFmJDO7U : 38.695124, 34.731489\n"
"Stop 6ik0QUeq6YE2ZPf8fem: 38.63358, 34.769693\n"
"Stop 6x9ftRRGWjuUTQQ: 38.525544, 34.915775\n"
"Stop 3: 38.40753, 34.833804\n"
"Stop f6mSgT ud5 : 38.699814, 34.757873\n"
"Stop Z6WXRBiOsQBSywzKrhupa : 38.626264, 34.89862\n"
"Stop C YdccGQZU6gbJL0mXX6IToE : 38.544924, 34.789975\n"
"Bus m6mj5Cj9pzJ5hvNTYnFyIyMH8 : ImEcfBE3Czdoa3 > PWIHxixUS8ROFlMqFTPXA > 7hSQl1n2m > Mzx > ur4VppUI3StmJP > QexzWmRfZ7VpKt0h > J0X8xdE3epu2 > UsaQup0GVKc2oPtsPdvk > m > yH6T6hYNXvjylXoM0uqb > AC9t > HL > 2fRakl6iS0cVl > MRWeEEANMtzBJ8z > oVtcsLqV72 > 7pyxD HFSz1P > T893Gm > CahFZzk > tQVD77CEYItf6vMk279fDk > HoZGABAZFoCFmJDO7U > SfV395Nnm1OrpX > 7qjQYTatbsF928i 4 > BWMGV > aAqPX > QexzWmRfZ7VpKt0h > bATIYunTC9Z5XN0bk0FBq7 > hhmpyF gEZCyMurPa > Mzx > pKIPR92hm > llbORb4gdec4Y29 > Y > mT > luOV urWGCs > 6DlTRiDlBADHd5wxuGwM > jg6oInTF0IOQjanfDYimaM > A9OtxLHuKLO > qC > h230yZ > h1OTf > 7hSQl1n2m > 6erXqFth8x18P5BxH50SAu7 > QbvTBD > SxvGUp9OhePe4pW FQfn > juAdbG4 > EJWKVw2R8gv6Od3J9NRC0UYq > c0p1aqDEdlepF > aXYObzMStKKrHU4O > ISlrnEIaKIEkpE4XC > 4pa5EXOMn4kJeA > aiAnA4AhBRojwfcFz > J0X8xdE3epu2 > VzkY8gVB > UsaQup0GVKc2oPtsPdvk > hXCtNJ55eAcJyF > gtm9BlpE8bAkxfHCPiz67Xs > hhmpyF gEZCyMurPa > 13ThLjYG > N0WC > 9uyCGpPMbWiXVAwsXG > Z6WXRBiOsQBSywzKrhupa > lBP > 8 > QexzWmRfZ7VpKt0h > jmRffEd > rOdgQuDph > mOA > t3R2RdoIYE0G4Z > hq0ln 4A7RoGuAxeTUZaBTaNp > eNJHau6B8 > 6x9ftRRGWjuUTQQ > pKIPR92hm > KZ8 > mT > 6ik0QUeq6YE2ZPf8fem > A3fg4VGWEfhi7pgZnWWtYs0wH > x6uAyDnts4HKRzp1XNol5 > Lp4MEdrq6otSB > id aFBFmo9u7 > pCumWQzxe 4xL4eWNY > lBP > ImEcfBE3Czdoa3\n"
"Bus iFl6j8fP : 47SX 1ZvTKPGQJfaRaBJNN - 7hSQl1n2m - aaDrzCkRa - b5jXJLSbbBnQZsJ4OVJ87Nzf - HnD0ZD0LB - aBZFsZCWEVhVMbSMvuI7b - fgO6d5U - iClhA6PCp1zjYNxCSdlF7Mzs - 9kHYrxYT6UCUGcLH - Y - m - WRo4l - 9kHYrxYT6UCUGcLH - Rmxlj6yf5V6Hr1 6JPY9 - hXCtNJ55eAcJyF - mbn1HhDBYL1 - PWIHxixUS8ROFlMqFTPXA - 8 - QbvTBD\n"
"Stop mq35 : 38.662342, 34.642555\n"
"Bus ACMMek : g0xPM - LXt9PS4RSuqsisxyQkDZGH0 - wCZucJLumbtAX - Yki5weXl - BWMGV - XrjmSdG6CmrQwxfWN8ehJ - HUb6xd4aaSJ01lo0ABt\n"
"Bus pIXFth9Y16Em : QbvTBD - OJOci4wu2\n"
"Bus 5UefmiSd1fEd32w0b89: yH6T6hYNXvjylXoM0uqb - eRlE31fLpeOfK5vSHL - FNJOLqRq5Ad3N2qj - aBZFsZCWEVhVMbSMvuI7b - vA - RZIBvXF6op2sX5cURx - FG - RopMyKExUGlJSvuPjDjAWD - YN4J5hLU4vuP3UgrRt0soPVP - Jkc - OyB2TTwVRcMgD - 7qjQYTatbsF928i 4 - KZ8 - VzkY8gVB - FiWYnMOOgvGlRS51l 2iP1ltP - u1lesMakDVZdJUyBO96wnYX4 - dNWXYAy9UgTq - J3GnXuZAAGf3oaa - HUb6xd4aaSJ01lo0ABt - KYszEJBfpaUkVjw5q6j - A9OtxLHuKLO - Lp4MEdrq6otSB - lYPJidFhhh8qIjg0chE - m - BWMGV - nhfM4 - T893Gm - SfV395Nnm1OrpX\n"
"Stop 2fRakl6iS0cVl: 38.618721, 34.764102\n"
"Stop N0WC : 38.69108, 34.812436\n"
"Stop Y7UB UGH5 : 38.646783, 34.932888\n"
"Bus J7E7wh KHC : TiqAnSNScH1 > A9OtxLHuKLO > 6x9ftRRGWjuUTQQ > NKoCAqHa55 > mq35 > QbvTBD > lBP > MeOzi4ywCT1W7xFOA5h > yH6T6hYNXvjylXoM0uqb > JWt2HAu > g0xPM > HUb6xd4aaSJ01lo0ABt > uwp6XK > Lp4MEdrq6otSB > Rz > U49MIbaw4gamvekq > TiqAnSNScH1 > m > KIITYxZQM > pKIPR92hm > oM6 > MeOzi4ywCT1W7xFOA5h > A3fg4VGWEfhi7pgZnWWtYs0wH > b5jXJLSbbBnQZsJ4OVJ87Nzf > aXYObzMStKKrHU4O > HnD0ZD0LB > JWt2HAu > 1GzQO9dYIm0me > 7hSQl1n2m > RopMyKExUGlJSvuPjDjAWD > N0WC > ISlrnEIaKIEkpE4XC > wCZucJLumbtAX > tPniDCwlR > TBP4AGPZg3GOQj5 zjGx j > EyivPqCySBygp4AaXYcEw > FG > m > tQVD77CEYItf6vMk279fDk > P > SfV395Nnm1OrpX > mkmqHwVr8gzfTQfL294 > jDThdjhjh2n7Wc > OJOci4wu2 > umomAjuO > fPX2y > jg6oInTF0IOQjanfDYimaM > h230yZ > uwp6XK > UA > xn58ceA wXl0wo6fw1 > c0p1aqDEdlepF > ztVWFuioD > h230yZ > o > mkmqHwVr8gzfTQfL294 > h > eX02k7tW0j L2d7akVudao > 47SX 1ZvTKPGQJfaRaBJNN > aXYObzMStKKrHU4O > 2IuMsuRbGaGlT > TiqAnSNScH1\n"
"Stop U3KBygTDyqkvCtB6o8 : 38.587069, 34.821098\n"
"Bus ZVmNhh9is90LP1YKtO : ztVWFuioD > mkmqHwVr8gzfTQfL294 > EyivPqCySBygp4AaXYcEw > b5jXJLSbbBnQZsJ4OVJ87Nzf > oVtcsLqV72 > YN4J5hLU4vuP3UgrRt0soPVP > f4mV > pKIPR92hm > SfV395Nnm1OrpX > kpt > rOdgQuDph > 6BXJi1odEOF3gnQkcH > sHYiT9RK4sqe2 > RZIBvXF6op2sX5cURx > z > imrGYjUSoKaMoOeEV > AiaFM3aIkyqmjhx > ur4VppUI3StmJP > gdhjubQAp3ZEgHbYdb > TiqAnSNScH1 > c0p1aqDEdlepF > 6erXqFth8x18P5BxH50SAu7 > RCMbeebIuxiDV > ztVWFuioD\n"
"Stop luOV urWGCs : 38.565592, 34.893894\n"
"Stop oM6 : 38.602409, 34.736384\n"
"Bus vrPjRFJy1Q4Aq QGU : ur4VppUI3StmJP - 6BXJi1odEOF3gnQkcH - W93vQSGbE2mnskhufqwc - RjQCxV2X2hcA - xn58ceA wXl0wo6fw1 - eNJHau6B8 - C YdccGQZU6gbJL0mXX6IToE - tQVD77CEYItf6vMk279fDk - MeOzi4ywCT1W7xFOA5h - bdIWPK1kWMN7wvJ7zl8Cgt7m - x6uAyDnts4HKRzp1XNol5 - lYPJidFhhh8qIjg0chE - 6ik0QUeq6YE2ZPf8fem - rOdgQuDph - pKIPR92hm - YAMY0OvPvxZF2BlAzg - pCumWQzxe 4xL4eWNY - 4pa5EXOMn4kJeA - J3GnXuZAAGf3oaa - nhfM4 - 3 - 4xyPd - o - HL - wumWKUk63DWuiNF6nqpiiDSSf - c0p1aqDEdlepF - VUtPzvEGpkYiJ8B7D2HmYkrci - KoAi8XSxyu x\n"
"Stop qC : 38.61435, 34.684533\n"
"Bus lU : h - P - Z6WXRBiOsQBSywzKrhupa - esRv7H4ulnA9xmUm7cHCI8Q - PWIHxixUS8ROFlMqFTPXA - QexzWmRfZ7VpKt0h - AiaFM3aIkyqmjhx - 47SX 1ZvTKPGQJfaRaBJNN - Rz - SfV395Nnm1OrpX - 7pyxD HFSz1P - SxvGUp9OhePe4pW FQfn - 3 - id aFBFmo9u7 - mkmqHwVr8gzfTQfL294 - qaqYVmrgqP76mxDYebu08xF8E\n"
"Stop WRo4l : 38.489944, 34.806247\n"
"Stop jg6oInTF0IOQjanfDYimaM : 38.598213, 34.92938\n"
"Bus 3R7Q1I9ACzzX: Sfskshp83VkmueW7t - eRlE31fLpeOfK5vSHL - ImEcfBE3Czdoa3 - VUZ5 - kv8A5AKGj iN\n"
"Stop UsaQup0GVKc2oPtsPdvk : 38.589767, 34.774485\n"
"Stop aiAnA4AhBRojwfcFz : 38.628859, 34.683762\n"
"Bus wliQ9DLIHn : mq35 > QbW > una0tkDG67WY2DKJlyGq > J3GnXuZAAGf3oaa > c7vc3yBR > UA > iClhA6PCp1zjYNxCSdlF7Mzs > FiWYnMOOgvGlRS51l 2iP1ltP > x6uAyDnts4HKRzp1XNol5 > 4pa5EXOMn4kJeA > J3GnXuZAAGf3oaa > h1OTf > lBP > b5jXJLSbbBnQZsJ4OVJ87Nzf > XEQUDl69zPpE9 > Rmxlj6yf5V6Hr1 6JPY9 > o > f4mV > luOV urWGCs > oVtcsLqV72 > jmRffEd > Y7UB UGH5 > AiaFM3aIkyqmjhx > aAqPX > kpt > HoZGABAZFoCFmJDO7U > 6erXqFth8x18P5BxH50SAu7 > jg6oInTF0IOQjanfDYimaM > SKWNv9tePz > HoZGABAZFoCFmJDO7U > ImEcfBE3Czdoa3 > x6uAyDnts4HKRzp1XNol5 > WGlidYF > mq35\n"
"Stop OJOci4wu2 : 38.681552, 34.757034\n"
"Stop aBZFsZCWEVhVMbSMvuI7b : 38.471189, 34.918961\n"
"Stop Y : 38.648336, 34.90867\n"
"Stop QOW7FWL5v5kdJBk3RDCZg : 38.403761, 34.935408\n"
"Stop wumWKUk63DWuiNF6nqpiiDSSf : 38.424905, 34.843597\n"
"Stop M2EClC : 38.62538, 34.65567\n"
"Stop yH6T6hYNXvjylXoM0uqb : 38.394975, 34.900746\n"
"Bus F7MHFi7g098LQ : EJWKVw2R8gv6Od3J9NRC0UYq - mTQElWNWMb99mLHtKSAt - Y - mT - QbvTBD - ISlrnEIaKIEkpE4XC - aAqPX - C YdccGQZU6gbJL0mXX6IToE - HL - XmnTYd9cySp - yH6T6hYNXvjylXoM0uqb - o - 9kHYrxYT6UCUGcLH - ur4VppUI3StmJP - U49MIbaw4gamvekq - HoZGABAZFoCFmJDO7U\n"
"Bus Q0sdH18QvsP : E > h > E\n"
"Stop XEQUDl69zPpE9 : 38.519556, 34.90077\n"
"Stop eRlE31fLpeOfK5vSHL : 38.519931, 34.914667\n"
"Stop ztVWFuioD : 38.427014, 34.886383\n"
"Bus ai : K > C YdccGQZU6gbJL0mXX6IToE > 6x9ftRRGWjuUTQQ > 6DlTRiDlBADHd5wxuGwM > NKoCAqHa55 > A2cG0537NQS > eX02k7tW0j L2d7akVudao > 1GzQO9dYIm0me > lYPJidFhhh8qIjg0chE > AC9t > 6ik0QUeq6YE2ZPf8fem > rOdgQuDph > QbW > hXCtNJ55eAcJyF > b5jXJLSbbBnQZsJ4OVJ87Nzf > WRo4l > XmnTYd9cySp > XEQUDl69zPpE9 > K > aBZFsZCWEVhVMbSMvuI7b > BWMGV > Lp4MEdrq6otSB > CahFZzk > RZIBvXF6op2sX5cURx > mkmqHwVr8gzfTQfL294 > Lp4MEdrq6otSB > BWMGV > z > kpt > KrSJ2LfG1Qo8EEttx > zqIUaW3xbhG > KYszEJBfpaUkVjw5q6j > umomAjuO > f6mSgT ud5 > A2cG0537NQS > wEToSr8wPMLRaGmEorqMHF1e > aaDrzCkRa > luOV urWGCs > TBP4AGPZg3GOQj5 zjGx j > 9uyCGpPMbWiXVAwsXG > h > 3 > dSzlIy80Uq nSpdPYp > 4J jy2z > eNJHau6B8 > oVtcsLqV72 > eRlE31fLpeOfK5vSHL > nhfM4 > aiAnA4AhBRojwfcFz > zqIUaW3xbhG > juAdbG4 > YN4J5hLU4vuP3UgrRt0soPVP > h > hhmpyF gEZCyMurPa > pCumWQzxe 4xL4eWNY > lBP > L5pcYa50O j4etgtHGQt > qC > TBP4AGPZg3GOQj5 zjGx j > KZ8 > kbU > lYPJidFhhh8qIjg0chE > nhfM4 > 8 > ur4VppUI3StmJP > jDThdjhjh2n7Wc > kv8A5AKGj iN > zqIUaW3xbhG > WUobJ5iHPZ974O > WGlidYF > 7pyxD HFSz1P > kbU > mOA > QdPEP6 > A3fg4VGWEfhi7pgZnWWtYs0wH > vA > 6ik0QUeq6YE2ZPf8fem > SxvGUp9OhePe4pW FQfn > b5jXJLSbbBnQZsJ4OVJ87Nzf > 7iWYyQimeYwd56Ynj57 > oVtcsLqV72 > MRWeEEANMtzBJ8z > 97ChPsiaFJ xk > K > TiqAnSNScH1 > QOW7FWL5v5kdJBk3RDCZg > J3GnXuZAAGf3oaa > K\n"
"Stop Yd 6DHbRbROdw: 38.628014, 34.880393\n"
"Stop Rmxlj6yf5V6Hr1 6JPY9: 38.614005, 34.99644\n"
"Stop WUobJ5iHPZ974O : 38.642641, 34.826029\n"
"Bus Q : h1OTf - FNJOLqRq5Ad3N2qj - RopMyKExUGlJSvuPjDjAWD - YN4J5hLU4vuP3UgrRt0soPVP - UsaQup0GVKc2oPtsPdvk - Yd 6DHbRbROdw - EyivPqCySBygp4AaXYcEw - w0PgbVmxAHFGF - OJOci4wu2 - Q1yE - WGlidYF - 0y4ho9GnEYu21UmoV42HZB0Mv - 9uyCGpPMbWiXVAwsXG - pCumWQzxe 4xL4eWNY - A3fg4VGWEfhi7pgZnWWtYs0wH - pKIPR92hm - AC9t - QexzWmRfZ7VpKt0h - SKWNv9tePz - aAqPX - dNWXYAy9UgTq - EyivPqCySBygp4AaXYcEw - RZIBvXF6op2sX5cURx - NKoCAqHa55 - Rmxlj6yf5V6Hr1 6JPY9 - fgO6d5U - t3R2RdoIYE0G4Z - mbn1HhDBYL1 - 0y4ho9GnEYu21UmoV42HZB0Mv - 6x9ftRRGWjuUTQQ - x6uAyDnts4HKRzp1XNol5 - SfV395Nnm1OrpX - 9n4lv - 4pa5EXOMn4kJeA - imrGYjUSoKaMoOeEV - QdPEP6 - lBP - NKoCAqHa55 - h1OTf\n"
"Stop OyB2TTwVRcMgD : 38.493922, 34.743554\n"
"Bus hl7xRZX : f6mSgT ud5 - zqIUaW3xbhG - A9OtxLHuKLO - HoZGABAZFoCFmJDO7U - 9n4lv - U49MIbaw4gamvekq - 4pa5EXOMn4kJeA - eRlE31fLpeOfK5vSHL - h - 7iWYyQimeYwd56Ynj57 - XrjmSdG6CmrQwxfWN8ehJ - eX02k7tW0j L2d7akVudao - WGlidYF - 0y4ho9GnEYu21UmoV42HZB0Mv - ImEcfBE3Czdoa3 - h1OTf - SKWNv9tePz - aXYObzMStKKrHU4O - BWMGV - PCKCn - YAMY0OvPvxZF2BlAzg - FNJOLqRq5Ad3N2qj - OyB2TTwVRcMgD - mq35 - XiIL1rrRfmLsCvs4t1 C4AzoT - A9OtxLHuKLO - gtm9BlpE8bAkxfHCPiz67Xs - w7V0IyAT4IqNKF7fFFyBq4B - h230yZ - QdPEP6 - 13ThLjYG - SxvGUp9OhePe4pW FQfn - KZ8 - hq0ln 4A7RoGuAxeTUZaBTaNp - h1OTf - 7qjQYTatbsF928i 4\n"
"Bus oGk4GA2TBWQw8TkiPvY : f4mV - FG - YAMY0OvPvxZF2BlAzg - KoAi8XSxyu x - PCKCn - RjQCxV2X2hcA - XmnTYd9cySp - eX02k7tW0j L2d7akVudao - gdhjubQAp3ZEgHbYdb - 6BXJi1odEOF3gnQkcH - c7vc3yBR - VzkY8gVB - kv8A5AKGj iN - VUZ5 - oM6 - nhfM4 - 6x9ftRRGWjuUTQQ - m - TiqAnSNScH1 - 2IuMsuRbGaGlT - 3 - id aFBFmo9u7 - f4mV - UsaQup0GVKc2oPtsPdvk - b5jXJLSbbBnQZsJ4OVJ87Nzf - xn58ceA wXl0wo6fw1 - jDThdjhjh2n7Wc - Jkc - aBZFsZCWEVhVMbSMvuI7b - wEToSr8wPMLRaGmEorqMHF1e - h\n"
"Stop fgO6d5U : 38.653643, 34.641641\n"
"Stop c0p1aqDEdlepF : 38.403283, 34.910648\n"
"Bus Vuh84BYoDH : RjQCxV2X2hcA > P > QexzWmRfZ7VpKt0h > KZ8 > 9W6KH8pazOTFPc3zss7E3 > bdIWPK1kWMN7wvJ7zl8Cgt7m > oVtcsLqV72 > AiaFM3aIkyqmjhx > zqIUaW3xbhG > pCumWQzxe 4xL4eWNY > mOA > iClhA6PCp1zjYNxCSdlF7Mzs > eNJHau6B8 > aXYObzMStKKrHU4O > CahFZzk > 8 > RjQCxV2X2hcA\n"
"Stop QbvTBD : 38.41408, 34.948027\n"
"Stop dSzlIy80Uq nSpdPYp : 38.711401, 34.895453\n"
"Stop XiIL1rrRfmLsCvs4t1 C4AzoT : 38.650945, 34.939687\n"
"Stop dNWXYAy9UgTq : 38.508558, 34.955285\n"
"Bus ns3Ae RV152 : fPX2y - 9uyCGpPMbWiXVAwsXG - FiWYnMOOgvGlRS51l 2iP1ltP - L5pcYa50O j4etgtHGQt - 2IuMsuRbGaGlT - SxvGUp9OhePe4pW FQfn - gdhjubQAp3ZEgHbYdb - A2cG0537NQS - SfV395Nnm1OrpX - PWIHxixUS8ROFlMqFTPXA - J0X8xdE3epu2\n"
"Bus bQ4vsTvWhXlQEi : umomAjuO > PCKCn > KrSJ2LfG1Qo8EEttx > XEQUDl69zPpE9 > 47SX 1ZvTKPGQJfaRaBJNN > wumWKUk63DWuiNF6nqpiiDSSf > qaqYVmrgqP76mxDYebu08xF8E > x6uAyDnts4HKRzp1XNol5 > Sfskshp83VkmueW7t > YN4J5hLU4vuP3UgrRt0soPVP > 4J jy2z > tPniDCwlR > FG > yH6T6hYNXvjylXoM0uqb > XB5NAUcKh yDNGkD7EtQ8 > TBP4AGPZg3GOQj5 zjGx j > w7V0IyAT4IqNKF7fFFyBq4B > mq35 > U49MIbaw4gamvekq > ztVWFuioD > lYPJidFhhh8qIjg0chE > W93vQSGbE2mnskhufqwc > w7V0IyAT4IqNKF7fFFyBq4B > h > mkmqHwVr8gzfTQfL294 > E > VUZ5 > 9uyCGpPMbWiXVAwsXG > P > eRlE31fLpeOfK5vSHL > eNJHau6B8 > aAqPX > Rz > 6BXJi1odEOF3gnQkcH > 6x9ftRRGWjuUTQQ > aAqPX > KrSJ2LfG1Qo8EEttx > G3o0bW > u1lesMakDVZdJUyBO96wnYX4 > aaDrzCkRa > 5RMNaOqZQp8CBhdok > mOA > c7vc3yBR > Jkc > 9n4lv > JoLcJeV8gQAS > Yd 6DHbRbROdw > KIITYxZQM > tPniDCwlR > 9kHYrxYT6UCUGcLH > RCMbeebIuxiDV > Z6WXRBiOsQBSywzKrhupa > KoAi8XSxyu x > P > OJOci4wu2 > 5UQ4TtSaNNs5SKSEHuTUKdh > UA > 7iWYyQimeYwd56Ynj57 > Mzx > kpt > kv8A5AKGj iN > G3o0bW > RCMbeebIuxiDV > 2IuMsuRbGaGlT > WUobJ5iHPZ974O > HnD0ZD0LB > QbW > tPniDCwlR > kv8A5AKGj iN > Rz > f6mSgT ud5 > h1OTf > uwp6XK > XEQUDl69zPpE9 > Mzx > lYPJidFhhh8qIjg0chE > x6uAyDnts4HKRzp1XNol5 > BWMGV > m > SfV395Nnm1OrpX > Sfskshp83VkmueW7t > umomAjuO\n"
"Stop L5pcYa50O j4etgtHGQt : 38.489809, 34.791158\n"
"Bus UCmn6j3DA2CkQTDROXaOSG : bATIYunTC9Z5XN0bk0FBq7 - sHYiT9RK4sqe2 - 4xyPd - J3GnXuZAAGf3oaa - c0p1aqDEdlepF - 5UQ4TtSaNNs5SKSEHuTUKdh - VzkY8gVB - ztVWFuioD - ImEcfBE3Czdoa3 - AiaFM3aIkyqmjhx - FNJOLqRq5Ad3N2qj - WUobJ5iHPZ974O - U49MIbaw4gamvekq - llbORb4gdec4Y29 - XmnTYd9cySp - zqIUaW3xbhG - dNWXYAy9UgTq - MRWeEEANMtzBJ8z - m - XmnTYd9cySp - T893Gm - A9OtxLHuKLO - XrjmSdG6CmrQwxfWN8ehJ - 2fRakl6iS0cVl - 01Z6NQhKl2UUkghq - P - 7pyxD HFSz1P - CahFZzk - HnD0ZD0LB - OyB2TTwVRcMgD - FiWYnMOOgvGlRS51l 2iP1ltP - nhfM4 - RopMyKExUGlJSvuPjDjAWD\n"
"Bus A : fPX2y > KZ8 > ImEcfBE3Czdoa3 > lBP > jwQ5 VVfrFgl0mL8hINmugEf > dSzlIy80Uq nSpdPYp > A2cG0537NQS > ur4VppUI3StmJP > ImEcfBE3Czdoa3 > J0X8xdE3epu2 > ur4VppUI3StmJP > gdhjubQAp3ZEgHbYdb > U3KBygTDyqkvCtB6o8 > VUZ5 > 01Z6NQhKl2UUkghq > RopMyKExUGlJSvuPjDjAWD > HUb6xd4aaSJ01lo0ABt > Yd 6DHbRbROdw > CahFZzk > ImEcfBE3Czdoa3 > 6erXqFth8x18P5BxH50SAu7 > 6x9ftRRGWjuUTQQ > hq0ln 4A7RoGuAxeTUZaBTaNp > f6mSgT ud5 > wumWKUk63DWuiNF6nqpiiDSSf > 2fRakl6iS0cVl > ur4VppUI3StmJP > 0y4ho9GnEYu21UmoV42HZB0Mv > vA > Rz > f4mV > T893Gm > KoAi8XSxyu x > 7pyxD HFSz1P > sHYiT9RK4sqe2 > Mzx > 2IuMsuRbGaGlT > luOV urWGCs > w0PgbVmxAHFGF > w7V0IyAT4IqNKF7fFFyBq4B > N0WC > gdhjubQAp3ZEgHbYdb > 6x9ftRRGWjuUTQQ > RCMbeebIuxiDV > c0p1aqDEdlepF > Q1yE > jwQ5 VVfrFgl0mL8hINmugEf > TBP4AGPZg3GOQj5 zjGx j > QdPEP6 > P > aBZFsZCWEVhVMbSMvuI7b > lYPJidFhhh8qIjg0chE > YAMY0OvPvxZF2BlAzg > mT > ImEcfBE3Czdoa3 > ztVWFuioD > WUobJ5iHPZ974O > U3KBygTDyqkvCtB6o8 > Rz > x6uAyDnts4HKRzp1XNol5 > Y > J3GnXuZAAGf3oaa > b5jXJLSbbBnQZsJ4OVJ87Nzf > KrSJ2LfG1Qo8EEttx > VUZ5 > iClhA6PCp1zjYNxCSdlF7Mzs > aXYObzMStKKrHU4O > tPniDCwlR > oVtcsLqV72 > u1lesMakDVZdJUyBO96wnYX4 > uwp6XK > esRv7H4ulnA9xmUm7cHCI8Q > C YdccGQZU6gbJL0mXX6IToE > 6x9ftRRGWjuUTQQ > Q1yE > mTQElWNWMb99mLHtKSAt > XB5NAUcKh yDNGkD7EtQ8 > 13ThLjYG > VUtPzvEGpkYiJ8B7D2HmYkrci > t3R2RdoIYE0G4Z > aAqPX > EJWKVw2R8gv6Od3J9NRC0UYq > jmRffEd > XiIL1rrRfmLsCvs4t1 C4AzoT > v8yUoEHDcAR5K > umomAjuO > FG > llbORb4gdec4Y29 > wCZucJLumbtAX > SKWNv9tePz > oVtcsLqV72 > QdPEP6 > umomAjuO > o > FG > J0X8xdE3epu2 > sHYiT9RK4sqe2 > SxvGUp9OhePe4pW FQfn > 47SX 1ZvTKPGQJfaRaBJNN > fPX2y\n"
"Stop zqIUaW3xbhG : 38.58796, 34.854745\n"
"Stop 2IuMsuRbGaGlT: 38.38744, 34.661927\n"
"Bus njbuySC7 : UsaQup0GVKc2oPtsPdvk > 6ik0QUeq6YE2ZPf8fem > luOV urWGCs > umomAjuO > HnD0ZD0LB > RCMbeebIuxiDV > UsaQup0GVKc2oPtsPdvk\n"
"Stop mkmqHwVr8gzfTQfL294 : 38.445631, 34.894232\n"
"Bus k : EyivPqCySBygp4AaXYcEw - z - 6BXJi1odEOF3gnQkcH - LXt9PS4RSuqsisxyQkDZGH0 - 9kHYrxYT6UCUGcLH - hXCtNJ55eAcJyF - lYPJidFhhh8qIjg0chE - h - Y7UB UGH5 - luOV urWGCs - fPX2y - aBZFsZCWEVhVMbSMvuI7b - iClhA6PCp1zjYNxCSdlF7Mzs - hXCtNJ55eAcJyF - QbvTBD - AiaFM3aIkyqmjhx - esRv7H4ulnA9xmUm7cHCI8Q - U3KBygTDyqkvCtB6o8 - mq35 - J0X8xdE3epu2 - 4pa5EXOMn4kJeA - eX02k7tW0j L2d7akVudao - AiaFM3aIkyqmjhx - QexzWmRfZ7VpKt0h - 4J jy2z - 2IuMsuRbGaGlT - Jkc - 9uyCGpPMbWiXVAwsXG - WUobJ5iHPZ974O - kpt - mOA - QOW7FWL5v5kdJBk3RDCZg - VUZ5 - Q1yE - XiIL1rrRfmLsCvs4t1 C4AzoT - Y7UB UGH5 - dSzlIy80Uq nSpdPYp - M2EClC - E\n"
"Stop v8yUoEHDcAR5K : 38.533657, 34.73887\n"
"Bus HK46 : luOV urWGCs > LXt9PS4RSuqsisxyQkDZGH0 > aAqPX > kbU > FG > 5RMNaOqZQp8CBhdok > 6BXJi1odEOF3gnQkcH > J0X8xdE3epu2 > oVtcsLqV72 > Sfskshp83VkmueW7t > z > A9OtxLHuKLO > h1OTf > XmnTYd9cySp > Rmxlj6yf5V6Hr1 6JPY9 > A3fg4VGWEfhi7pgZnWWtYs0wH > hXCtNJ55eAcJyF > T893Gm > KIITYxZQM > XrjmSdG6CmrQwxfWN8ehJ > 6erXqFth8x18P5BxH50SAu7 > QbW > iClhA6PCp1zjYNxCSdlF7Mzs > mTQElWNWMb99mLHtKSAt > CahFZzk > qC > bATIYunTC9Z5XN0bk0FBq7 > ztVWFuioD > iClhA6PCp1zjYNxCSdlF7Mzs > pKIPR92hm > 2fRakl6iS0cVl > c7vc3yBR > pKIPR92hm > QbW > f6mSgT ud5 > 6DlTRiDlBADHd5wxuGwM > pCumWQzxe 4xL4eWNY > XrjmSdG6CmrQwxfWN8ehJ > dSzlIy80Uq nSpdPYp > 7qpKAGotrE6vi5OEmh8Txf > RjQCxV2X2hcA > VUZ5 > J3GnXuZAAGf3oaa > gtm9BlpE8bAkxfHCPiz67Xs > h230yZ > KIITYxZQM > QdPEP6 > h230yZ > KYszEJBfpaUkVjw5q6j > 6x9ftRRGWjuUTQQ > luOV urWGCs\n"
"Stop E : 38.570479, 34.667832\n"
"Stop 9kHYrxYT6UCUGcLH: 38.385422, 34.914074\n"
"Stop MRWeEEANMtzBJ8z : 38.540302, 34.932718\n"
"Bus DPEKv6xITDR22aygS18OpSDpb : hXCtNJ55eAcJyF - Z6WXRBiOsQBSywzKrhupa - HnD0ZD0LB - hhmpyF gEZCyMurPa - b5jXJLSbbBnQZsJ4OVJ87Nzf - jmRffEd - aaDrzCkRa - RopMyKExUGlJSvuPjDjAWD - m - 4pa5EXOMn4kJeA - oVtcsLqV72 - jmRffEd - UA - NKoCAqHa55 - 9n4lv - wCZucJLumbtAX - vA - FiWYnMOOgvGlRS51l 2iP1ltP - oVtcsLqV72 - xn58ceA wXl0wo6fw1 - AC9t - HoZGABAZFoCFmJDO7U - ImEcfBE3Czdoa3 - wumWKUk63DWuiNF6nqpiiDSSf - 0y4ho9GnEYu21UmoV42HZB0Mv - jwQ5 VVfrFgl0mL8hINmugEf - XmnTYd9cySp - 4pa5EXOMn4kJeA - c7vc3yBR\n"
"Bus N5 : mTQElWNWMb99mLHtKSAt - BWMGV - JWt2HAu - U3KBygTDyqkvCtB6o8\n"
"Bus dy68oy5FxyD6etpsp : wEToSr8wPMLRaGmEorqMHF1e > YAMY0OvPvxZF2BlAzg > C YdccGQZU6gbJL0mXX6IToE > Q1yE > tPniDCwlR > Mzx > bdIWPK1kWMN7wvJ7zl8Cgt7m > xn58ceA wXl0wo6fw1 > kbU > YAMY0OvPvxZF2BlAzg > Y7UB UGH5 > h230yZ > RCMbeebIuxiDV > c7vc3yBR > z > MRWeEEANMtzBJ8z > luOV urWGCs > HnD0ZD0LB > UA > mTQElWNWMb99mLHtKSAt > 4xyPd > 2fRakl6iS0cVl > KYszEJBfpaUkVjw5q6j > BWMGV > KZ8 > K > XmnTYd9cySp > tQVD77CEYItf6vMk279fDk > jDThdjhjh2n7Wc > AC9t > Jkc > 13ThLjYG > pCumWQzxe 4xL4eWNY > VUtPzvEGpkYiJ8B7D2HmYkrci > f4mV > h > tQVD77CEYItf6vMk279fDk > Sfskshp83VkmueW7t > 4pa5EXOMn4kJeA > UsaQup0GVKc2oPtsPdvk > una0tkDG67WY2DKJlyGq > qC > wEToSr8wPMLRaGmEorqMHF1e\n"
"Bus CtJOIgFpt9ptZteXtmVcf0nZI : u1lesMakDVZdJUyBO96wnYX4 - zqIUaW3xbhG - 13ThLjYG - eRlE31fLpeOfK5vSHL - 8 - eX02k7tW0j L2d7akVudao - sHYiT9RK4sqe2 - nhfM4 - A9OtxLHuKLO - YN4J5hLU4vuP3UgrRt0soPVP - w0PgbVmxAHFGF - fPX2y - mOA - QOW7FWL5v5kdJBk3RDCZg - RZIBvXF6op2sX5cURx - c7vc3yBR - rOdgQuDph - l3A - oVtcsLqV72 - 7qpKAGotrE6vi5OEmh8Txf - tPniDCwlR - h - KYszEJBfpaUkVjw5q6j - oVtcsLqV72 - wEToSr8wPMLRaGmEorqMHF1e - oVtcsLqV72 - RopMyKExUGlJSvuPjDjAWD - KYszEJBfpaUkVjw5q6j - ImEcfBE3Czdoa3 - Sfskshp83VkmueW7t - hq0ln 4A7RoGuAxeTUZaBTaNp - QdPEP6 - Y7UB UGH5 - x6uAyDnts4HKRzp1XNol5 - RjQCxV2X2hcA - sHYiT9RK4sqe2 - AiaFM3aIkyqmjhx\n"
"Stop aaDrzCkRa : 38.50603, 34.781322\n"
"Stop KYszEJBfpaUkVjw5q6j : 38.633658, 34.906958\n"
"Bus nRWzl3IWxFu : HL - hq0ln 4A7RoGuAxeTUZaBTaNp - v8yUoEHDcAR5K - E - jg6oInTF0IOQjanfDYimaM - JoLcJeV8gQAS - aXYObzMStKKrHU4O - AC9t - w7V0IyAT4IqNKF7fFFyBq4B - gtm9BlpE8bAkxfHCPiz67Xs - SKWNv9tePz - aXYObzMStKKrHU4O - SKWNv9tePz - ur4VppUI3StmJP - A2cG0537NQS - jDThdjhjh2n7Wc - hq0ln 4A7RoGuAxeTUZaBTaNp - 3 - C YdccGQZU6gbJL0mXX6IToE - dNWXYAy9UgTq - XiIL1rrRfmLsCvs4t1 C4AzoT - 4J jy2z - aAqPX - E - 13ThLjYG - mOA - KrSJ2LfG1Qo8EEttx - luOV urWGCs - h - tPniDCwlR - lYPJidFhhh8qIjg0chE - Jkc - L5pcYa50O j4etgtHGQt\n"
"Stop KrSJ2LfG1Qo8EEttx : 38.6489, 34.827063\n"
"Bus 8IMIhyC H : wEToSr8wPMLRaGmEorqMHF1e > c0p1aqDEdlepF > id aFBFmo9u7 > 4J jy2z > 9kHYrxYT6UCUGcLH > A2cG0537NQS > FiWYnMOOgvGlRS51l 2iP1ltP > 6x9ftRRGWjuUTQQ > mOA > 9uyCGpPMbWiXVAwsXG > C YdccGQZU6gbJL0mXX6IToE > x6uAyDnts4HKRzp1XNol5 > 01Z6NQhKl2UUkghq > wumWKUk63DWuiNF6nqpiiDSSf > Rmxlj6yf5V6Hr1 6JPY9 > 6erXqFth8x18P5BxH50SAu7 > z > 5UQ4TtSaNNs5SKSEHuTUKdh > K > 1GzQO9dYIm0me > PWIHxixUS8ROFlMqFTPXA > KrSJ2LfG1Qo8EEttx > c7vc3yBR > h > 1GzQO9dYIm0me > aiAnA4AhBRojwfcFz > AC9t > esRv7H4ulnA9xmUm7cHCI8Q > 0y4ho9GnEYu21UmoV42HZB0Mv > YAMY0OvPvxZF2BlAzg > TiqAnSNScH1 > c7vc3yBR > eX02k7tW0j L2d7akVudao > 7qjQYTatbsF928i 4 > Yki5weXl > XB5NAUcKh yDNGkD7EtQ8 > qaqYVmrgqP76mxDYebu08xF8E > K > A9OtxLHuKLO > TBP4AGPZg3GOQj5 zjGx j > Yd 6DHbRbROdw > TiqAnSNScH1 > wEToSr8wPMLRaGmEorqMHF1e > aAqPX > MRWeEEANMtzBJ8z > PWIHxixUS8ROFlMqFTPXA > MeOzi4ywCT1W7xFOA5h > h230yZ > QexzWmRfZ7VpKt0h > kpt > v8yUoEHDcAR5K > Lp4MEdrq6otSB > 6ik0QUeq6YE2ZPf8fem > aXYObzMStKKrHU4O > nhfM4 > wumWKUk63DWuiNF6nqpiiDSSf > 6x9ftRRGWjuUTQQ > 01Z6NQhKl2UUkghq > EJWKVw2R8gv6Od3J9NRC0UYq > bdIWPK1kWMN7wvJ7zl8Cgt7m > LXt9PS4RSuqsisxyQkDZGH0 > A3fg4VGWEfhi7pgZnWWtYs0wH > wEToSr8wPMLRaGmEorqMHF1e\n"
"Stop 7hSQl1n2m: 38.467211, 34.940556\n"
"Stop 0y4ho9GnEYu21UmoV42HZB0Mv: 38.595615, 34.75236\n"
"Stop x6uAyDnts4HKRzp1XNol5 : 38.667287, 34.727021\n"
"Bus T : NKoCAqHa55 > JWt2HAu > Jkc > 6ik0QUeq6YE2ZPf8fem > 0y4ho9GnEYu21UmoV42HZB0Mv > RCMbeebIuxiDV > 9n4lv > fgO6d5U > aaDrzCkRa > U49MIbaw4gamvekq > VUZ5 > QOW7FWL5v5kdJBk3RDCZg > 4J jy2z > 6ik0QUeq6YE2ZPf8fem > HnD0ZD0LB > QOW7FWL5v5kdJBk3RDCZg > Rmxlj6yf5V6Hr1 6JPY9 > zqIUaW3xbhG > gtm9BlpE8bAkxfHCPiz67Xs > 9kHYrxYT6UCUGcLH > A9OtxLHuKLO > tPniDCwlR > z > L5pcYa50O j4etgtHGQt > wEToSr8wPMLRaGmEorqMHF1e > b5jXJLSbbBnQZsJ4OVJ87Nzf > FG > c7vc3yBR > 7hSQl1n2m > u1lesMakDVZdJUyBO96wnYX4 > CahFZzk > h > rOdgQuDph > Yd 6DHbRbROdw > l3A > YAMY0OvPvxZF2BlAzg > 7qpKAGotrE6vi5OEmh8Txf > 01Z6NQhKl2UUkghq > xn58ceA wXl0wo6fw1 > fPX2y > jwQ5 VVfrFgl0mL8hINmugEf > A9OtxLHuKLO > bATIYunTC9Z5XN0bk0FBq7 > 1GzQO9dYIm0me > eNJHau6B8 > Sfskshp83VkmueW7t > 4pa5EXOMn4kJeA > Rz > eX02k7tW0j L2d7akVudao > tQVD77CEYItf6vMk279fDk > WRo4l > b5jXJLSbbBnQZsJ4OVJ87Nzf > o > JWt2HAu > KZ8 > dSzlIy80Uq nSpdPYp > qaqYVmrgqP76mxDYebu08xF8E > hXCtNJ55eAcJyF > yH6T6hYNXvjylXoM0uqb > 97ChPsiaFJ xk > M2EClC > llbORb4gdec4Y29 > Y7UB UGH5 > l3A > tQVD77CEYItf6vMk279fDk > 9uyCGpPMbWiXVAwsXG > w7V0IyAT4IqNKF7fFFyBq4B > 4J jy2z > 3 > Rz > RjQCxV2X2hcA > P > g0xPM > dNWXYAy9UgTq > NKoCAqHa55\n"
"Stop mbn1HhDBYL1 : 38.392834, 34.705707\n"
"Stop RopMyKExUGlJSvuPjDjAWD : 38.665234, 34.774243\n"
"Stop u1lesMakDVZdJUyBO96wnYX4 : 38.549154, 34.685643\n"
"Bus IvfFmKUcoScGJoa : o > 01Z6NQhKl2UUkghq > fgO6d5U > HnD0ZD0LB > 2IuMsuRbGaGlT > UsaQup0GVKc2oPtsPdvk > A2cG0537NQS > QOW7FWL5v5kdJBk3RDCZg > wumWKUk63DWuiNF6nqpiiDSSf > mTQElWNWMb99mLHtKSAt > g0xPM > 01Z6NQhKl2UUkghq > kpt > QOW7FWL5v5kdJBk3RDCZg > QbW > G3o0bW > eRlE31fLpeOfK5vSHL > kbU > KZ8 > luOV urWGCs > YAMY0OvPvxZF2BlAzg > 1GzQO9dYIm0me > 6DlTRiDlBADHd5wxuGwM > ztVWFuioD > rOdgQuDph > Lp4MEdrq6otSB > 47SX 1ZvTKPGQJfaRaBJNN > rOdgQuDph > 13ThLjYG > Lp4MEdrq6otSB > LXt9PS4RSuqsisxyQkDZGH0 > 9uyCGpPMbWiXVAwsXG > HnD0ZD0LB > rOdgQuDph > qaqYVmrgqP76mxDYebu08xF8E > hXCtNJ55eAcJyF > fPX2y > XmnTYd9cySp > K > hXCtNJ55eAcJyF > aaDrzCkRa > K > UsaQup0GVKc2oPtsPdvk > aBZFsZCWEVhVMbSMvuI7b > g0xPM > mOA > kv8A5AKGj iN > FNJOLqRq5Ad3N2qj > 9n4lv > QOW7FWL5v5kdJBk3RDCZg > kpt > VUtPzvEGpkYiJ8B7D2HmYkrci > wumWKUk63DWuiNF6nqpiiDSSf > VUZ5 > mT > pCumWQzxe 4xL4eWNY > XmnTYd9cySp > dSzlIy80Uq nSpdPYp > ISlrnEIaKIEkpE4XC > b5jXJLSbbBnQZsJ4OVJ87Nzf > WRo4l > wumWKUk63DWuiNF6nqpiiDSSf > mOA > WGlidYF > E > FiWYnMOOgvGlRS51l 2iP1ltP > KIITYxZQM > o > UA > 01Z6NQhKl2UUkghq > U49MIbaw4gamvekq > dNWXYAy9UgTq > YAMY0OvPvxZF2BlAzg > b5jXJLSbbBnQZsJ4OVJ87Nzf > A3fg4VGWEfhi7pgZnWWtYs0wH > 47SX 1ZvTKPGQJfaRaBJNN > U49MIbaw4gamvekq > N0WC > VzkY8gVB > mT > TiqAnSNScH1 > VUtPzvEGpkYiJ8B7D2HmYkrci > qC > gtm9BlpE8bAkxfHCPiz67Xs > XEQUDl69zPpE9 > U3KBygTDyqkvCtB6o8 > RopMyKExUGlJSvuPjDjAWD > llbORb4gdec4Y29 > SKWNv9tePz > nhfM4 > mbn1HhDBYL1 > jg6oInTF0IOQjanfDYimaM > TiqAnSNScH1 > rOdgQuDph > W93vQSGbE2mnskhufqwc > iClhA6PCp1zjYNxCSdlF7Mzs > 6BXJi1odEOF3gnQkcH > BWMGV > wumWKUk63DWuiNF6nqpiiDSSf > o\n"
"Bus Ho7KF8bipjJly8TvvQ : 4pa5EXOMn4kJeA > Jkc > ISlrnEIaKIEkpE4XC > Y7UB UGH5 > OyB2TTwVRcMgD > Jkc > WGlidYF > oM6 > aXYObzMStKKrHU4O > SxvGUp9OhePe4pW FQfn > 2fRakl6iS0cVl > wEToSr8wPMLRaGmEorqMHF1e > juAdbG4 > 4xyPd > mOA > 5UQ4TtSaNNs5SKSEHuTUKdh > id aFBFmo9u7 > EJWKVw2R8gv6Od3J9NRC0UYq > AiaFM3aIkyqmjhx > FiWYnMOOgvGlRS51l 2iP1ltP > HL > A9OtxLHuKLO > m > kbU > ImEcfBE3Czdoa3 > fPX2y > 2IuMsuRbGaGlT > h1OTf > aaDrzCkRa > 0y4ho9GnEYu21UmoV42HZB0Mv > b5jXJLSbbBnQZsJ4OVJ87Nzf > hq0ln 4A7RoGuAxeTUZaBTaNp > HnD0ZD0LB > Lp4MEdrq6otSB > JWt2HAu > FiWYnMOOgvGlRS51l 2iP1ltP > mTQElWNWMb99mLHtKSAt > lYPJidFhhh8qIjg0chE > UA > llbORb4gdec4Y29 > lBP > E > KIITYxZQM > W93vQSGbE2mnskhufqwc > UsaQup0GVKc2oPtsPdvk > fPX2y > dNWXYAy9UgTq > 5RMNaOqZQp8CBhdok > E > 47SX 1ZvTKPGQJfaRaBJNN > c7vc3yBR > f6mSgT ud5 > mOA > l3A > L5pcYa50O j4etgtHGQt > RCMbeebIuxiDV > L5pcYa50O j4etgtHGQt > PWIHxixUS8ROFlMqFTPXA > 9W6KH8pazOTFPc3zss7E3 > WGlidYF > N0WC > P > c7vc3yBR > JWt2HAu > jmRffEd > TiqAnSNScH1 > mkmqHwVr8gzfTQfL294 > HnD0ZD0LB > wEToSr8wPMLRaGmEorqMHF1e > ISlrnEIaKIEkpE4XC > JWt2HAu > E > XrjmSdG6CmrQwxfWN8ehJ > wCZucJLumbtAX > ISlrnEIaKIEkpE4XC > KYszEJBfpaUkVjw5q6j > HnD0ZD0LB > 13ThLjYG > sHYiT9RK4sqe2 > x6uAyDnts4HKRzp1XNol5 > fPX2y > N0WC > XrjmSdG6CmrQwxfWN8ehJ > 5UQ4TtSaNNs5SKSEHuTUKdh > c0p1aqDEdlepF > llbORb4gdec4Y29 > zqIUaW3xbhG > uwp6XK > Mzx > FNJOLqRq5Ad3N2qj > 7qpKAGotrE6vi5OEmh8Txf > RZIBvXF6op2sX5cURx > SfV395Nnm1OrpX > kv8A5AKGj iN > 7qjQYTatbsF928i 4 > 8 > OJOci4wu2 > 4pa5EXOMn4kJeA\n"
"Bus 50T3FDpDQnb25eWd2Kh21Mwk: aiAnA4AhBRojwfcFz - A9OtxLHuKLO - 97ChPsiaFJ xk - id aFBFmo9u7 - E - l3A - VzkY8gVB - UA\n"
"Bus 8ENjuk3tmmmNGP: RZIBvXF6op2sX5cURx - mT - f4mV\n"
"Stop Rz : 38.711843, 34.749269\n"
"Stop 5RMNaOqZQp8CBhdok: 38.514332, 34.95846\n"
"Bus jHtiZ0pjl : FiWYnMOOgvGlRS51l 2iP1ltP - 47SX 1ZvTKPGQJfaRaBJNN - 7pyxD HFSz1P - Y7UB UGH5\n"
"Bus kP4ts7zVw2Ffbb : gdhjubQAp3ZEgHbYdb - kv8A5AKGj iN - ztVWFuioD - KIITYxZQM\n"
"Stop 6BXJi1odEOF3gnQkcH: 38.392201, 34.915235\n"
"Stop rOdgQuDph : 38.584089, 34.828873\n"
"Stop KIITYxZQM : 38.59057, 34.667133\n"
"Stop mOA : 38.552177, 34.881677\n"
"Bus nPFuS0guFw2 8Awf: U3KBygTDyqkvCtB6o8 - A9OtxLHuKLO - TBP4AGPZg3GOQj5 zjGx j - QdPEP6 - YAMY0OvPvxZF2BlAzg - JoLcJeV8gQAS - Q1yE - oM6 - kpt - HoZGABAZFoCFmJDO7U - ImEcfBE3Czdoa3 - jg6oInTF0IOQjanfDYimaM - mkmqHwVr8gzfTQfL294 - XB5NAUcKh yDNGkD7EtQ8 - imrGYjUSoKaMoOeEV - mkmqHwVr8gzfTQfL294 - wumWKUk63DWuiNF6nqpiiDSSf - jwQ5 VVfrFgl0mL8hINmugEf - Y - esRv7H4ulnA9xmUm7cHCI8Q - C YdccGQZU6gbJL0mXX6IToE - pCumWQzxe 4xL4eWNY - wumWKUk63DWuiNF6nqpiiDSSf - kv8A5AKGj iN - WRo4l - K\n"
"Bus gBjmm65BVfcWBKmwi5 : QexzWmRfZ7VpKt0h - Mzx - pKIPR92hm - aBZFsZCWEVhVMbSMvuI7b - SxvGUp9OhePe4pW FQfn - LXt9PS4RSuqsisxyQkDZGH0 - jDThdjhjh2n7Wc - C YdccGQZU6gbJL0mXX6IToE - zqIUaW3xbhG - QdPEP6 - RjQCxV2X2hcA - vA - A9OtxLHuKLO - 7qpKAGotrE6vi5OEmh8Txf - SxvGUp9OhePe4pW FQfn - oVtcsLqV72 - OJOci4wu2 - JoLcJeV8gQAS - u1lesMakDVZdJUyBO96wnYX4 - zqIUaW3xbhG - wumWKUk63DWuiNF6nqpiiDSSf - L5pcYa50O j4etgtHGQt - HoZGABAZFoCFmJDO7U - g0xPM - z - N0WC - tPniDCwlR - JWt2HAu - MeOzi4ywCT1W7xFOA5h - KZ8\n"
"Stop SxvGUp9OhePe4pW FQfn : 38.497731, 34.851347\n"
"Stop w0PgbVmxAHFGF : 38.61117, 34.71049\n"
"Bus ImWTJwA2psmogMYVbKQXiHk : QdPEP6 - 6x9ftRRGWjuUTQQ - 4J jy2z - FNJOLqRq5Ad3N2qj - SxvGUp9OhePe4pW FQfn - XB5NAUcKh yDNGkD7EtQ8 - gdhjubQAp3ZEgHbYdb - HnD0ZD0LB - 6ik0QUeq6YE2ZPf8fem - 9W6KH8pazOTFPc3zss7E3 - 97ChPsiaFJ xk - f4mV - 6ik0QUeq6YE2ZPf8fem - l3A - XrjmSdG6CmrQwxfWN8ehJ - VUZ5 - E - U49MIbaw4gamvekq - aXYObzMStKKrHU4O - rOdgQuDph - J3GnXuZAAGf3oaa - juAdbG4 - Sfskshp83VkmueW7t - T893Gm - VUZ5 - ImEcfBE3Czdoa3 - u1lesMakDVZdJUyBO96wnYX4 - WGlidYF - id aFBFmo9u7 - A3fg4VGWEfhi7pgZnWWtYs0wH - tPniDCwlR - hhmpyF gEZCyMurPa - RZIBvXF6op2sX5cURx - VUtPzvEGpkYiJ8B7D2HmYkrci - L5pcYa50O j4etgtHGQt - 0y4ho9GnEYu21UmoV42HZB0Mv - t3R2RdoIYE0G4Z - A2cG0537NQS - kbU - 7qpKAGotrE6vi5OEmh8Txf - RopMyKExUGlJSvuPjDjAWD - z - FiWYnMOOgvGlRS51l 2iP1ltP - AC9t - qC - mbn1HhDBYL1\n"
"Stop aAqPX : 38.569372, 34.845907\n"
"Stop h230yZ : 38.661994, 34.923167\n"
"Bus V7fnb : TiqAnSNScH1 - h - Q1yE - aAqPX - v8yUoEHDcAR5K - Rz - jg6oInTF0IOQjanfDYimaM - l3A - g0xPM - FNJOLqRq5Ad3N2qj - J0X8xdE3epu2 - Rz - M2EClC - gtm9BlpE8bAkxfHCPiz67Xs - o - MRWeEEANMtzBJ8z - 4J jy2z - mkmqHwVr8gzfTQfL294 - FG - uwp6XK - YAMY0OvPvxZF2BlAzg - XB5NAUcKh yDNGkD7EtQ8 - Y7UB UGH5 - bATIYunTC9Z5XN0bk0FBq7\n"
"Stop UA : 38.587543, 34.834096\n"
"Stop 4xyPd: 38.60844, 34.960959\n"
"Stop aXYObzMStKKrHU4O : 38.714774, 34.658192\n"
"Stop eNJHau6B8 : 38.548812, 34.719189\n"
"Stop ISlrnEIaKIEkpE4XC : 38.578752, 34.737781\n"
"Stop TBP4AGPZg3GOQj5 zjGx j : 38.683365, 34.9837\n"
"Stop EJWKVw2R8gv6Od3J9NRC0UYq : 38.666481, 34.890034\n"
"Stop Jkc : 38.406816, 34.704924\n"
"Stop uwp6XK : 38.473176, 34.667976\n"
"Bus 2TjwvfZFHjEkpGkiLld: A3fg4VGWEfhi7pgZnWWtYs0wH - h230yZ - eX02k7tW0j L2d7akVudao - ztVWFuioD - v8yUoEHDcAR5K - PWIHxixUS8ROFlMqFTPXA - QbvTBD - f6mSgT ud5 - ztVWFuioD - vA - llbORb4gdec4Y29 - XrjmSdG6CmrQwxfWN8ehJ - 9W6KH8pazOTFPc3zss7E3 - E - gtm9BlpE8bAkxfHCPiz67Xs - UsaQup0GVKc2oPtsPdvk - mq35 - 13ThLjYG - T893Gm - WUobJ5iHPZ974O - nhfM4 - MRWeEEANMtzBJ8z - SKWNv9tePz - JWt2HAu - u1lesMakDVZdJUyBO96wnYX4 - aBZFsZCWEVhVMbSMvuI7b - aXYObzMStKKrHU4O - 5UQ4TtSaNNs5SKSEHuTUKdh - C YdccGQZU6gbJL0mXX6IToE - gtm9BlpE8bAkxfHCPiz67Xs - HUb6xd4aaSJ01lo0ABt - una0tkDG67WY2DKJlyGq - 7pyxD HFSz1P - c7vc3yBR - eNJHau6B8 - QbvTBD - 7qjQYTatbsF928i 4 - vA - 9kHYrxYT6UCUGcLH - Mzx - Y - XmnTYd9cySp - KrSJ2LfG1Qo8EEttx\n"
"Stop hhmpyF gEZCyMurPa : 38.559382, 34.87821\n"
"Bus 0n7d5xCe1S: vA > wEToSr8wPMLRaGmEorqMHF1e > una0tkDG67WY2DKJlyGq > h > 47SX 1ZvTKPGQJfaRaBJNN > QdPEP6 > EJWKVw2R8gv6Od3J9NRC0UYq > 3 > sHYiT9RK4sqe2 > AC9t > VUtPzvEGpkYiJ8B7D2HmYkrci > JoLcJeV8gQAS > aAqPX > G3o0bW > c7vc3yBR > WGlidYF > f6mSgT ud5 > XB5NAUcKh yDNGkD7EtQ8 > U3KBygTDyqkvCtB6o8 > pKIPR92hm > L5pcYa50O j4etgtHGQt > fPX2y > U49MIbaw4gamvekq > ztVWFuioD > mq35 > KIITYxZQM > nhfM4 > RCMbeebIuxiDV > QbvTBD > fgO6d5U > W93vQSGbE2mnskhufqwc > KZ8 > OJOci4wu2 > Yd 6DHbRbROdw > imrGYjUSoKaMoOeEV > KrSJ2LfG1Qo8EEttx > g0xPM > E > f6mSgT ud5 > ur4VppUI3StmJP > 4J jy2z > 5UQ4TtSaNNs5SKSEHuTUKdh > eNJHau6B8 > 6BXJi1odEOF3gnQkcH > eX02k7tW0j L2d7akVudao > ztVWFuioD > HL > h230yZ > VzkY8gVB > 4xyPd > aaDrzCkRa > vA\n"
"Stop W93vQSGbE2mnskhufqwc : 38.398461, 34.836729\n"
"Stop tPniDCwlR : 38.612259, 34.958378\n"
"Stop ur4VppUI3StmJP : 38.40346, 34.760831\n"
"Stop 13ThLjYG: 38.614086, 34.662852\n"
"Stop KZ8 : 38.462894, 34.984356\n"
"Bus I1wMnrwRq8weJZ : mTQElWNWMb99mLHtKSAt - 9kHYrxYT6UCUGcLH - L5pcYa50O j4etgtHGQt - jwQ5 VVfrFgl0mL8hINmugEf - g0xPM - ur4VppUI3StmJP - Rz\n"
"Bus ZZYK2jFJr7eqd10Eqt : JWt2HAu - G3o0bW - t3R2RdoIYE0G4Z - h1OTf - tPniDCwlR - u1lesMakDVZdJUyBO96wnYX4 - 7qpKAGotrE6vi5OEmh8Txf - h - LXt9PS4RSuqsisxyQkDZGH0 - 7pyxD HFSz1P - id aFBFmo9u7 - UA - x6uAyDnts4HKRzp1XNol5 - J3GnXuZAAGf3oaa - mTQElWNWMb99mLHtKSAt - u1lesMakDVZdJUyBO96wnYX4 - Yd 6DHbRbROdw - xn58ceA wXl0wo6fw1 - G3o0bW - nhfM4 - z - PCKCn - Rmxlj6yf5V6Hr1 6JPY9 - 6ik0QUeq6YE2ZPf8fem - P - eNJHau6B8 - RCMbeebIuxiDV - TiqAnSNScH1 - qC - pKIPR92hm - JoLcJeV8gQAS - eNJHau6B8 - kv8A5AKGj iN - WGlidYF - aiAnA4AhBRojwfcFz - A9OtxLHuKLO - SfV395Nnm1OrpX - esRv7H4ulnA9xmUm7cHCI8Q - w0PgbVmxAHFGF - 01Z6NQhKl2UUkghq - bATIYunTC9Z5XN0bk0FBq7 - wEToSr8wPMLRaGmEorqMHF1e - Rmxlj6yf5V6Hr1 6JPY9 - Z6WXRBiOsQBSywzKrhupa\n"
"Bus XU : P - jwQ5 VVfrFgl0mL8hINmugEf - 9kHYrxYT6UCUGcLH - 5RMNaOqZQp8CBhdok - Lp4MEdrq6otSB - N0WC - mTQElWNWMb99mLHtKSAt - luOV urWGCs - SKWNv9tePz - tPniDCwlR - tQVD77CEYItf6vMk279fDk - 7qjQYTatbsF928i 4 - P - iClhA6PCp1zjYNxCSdlF7Mzs - FG - G3o0bW - nhfM4 - 8 - f4mV - C YdccGQZU6gbJL0mXX6IToE - Jkc - mbn1HhDBYL1 - c0p1aqDEdlepF - m - AC9t - NKoCAqHa55 - h230yZ - jg6oInTF0IOQjanfDYimaM - eNJHau6B8 - A9OtxLHuKLO - QOW7FWL5v5kdJBk3RDCZg - Jkc - 4pa5EXOMn4kJeA - yH6T6hYNXvjylXoM0uqb - QOW7FWL5v5kdJBk3RDCZg - mTQElWNWMb99mLHtKSAt - RZIBvXF6op2sX5cURx - 6x9ftRRGWjuUTQQ\n"
"Stop XrjmSdG6CmrQwxfWN8ehJ : 38.412269, 34.847663\n"
"Stop K : 38.729226, 34.975025\n"
"Stop A9OtxLHuKLO : 38.424553, 34.69612\n"
"Stop eX02k7tW0j L2d7akVudao : 38.443042, 34.673845\n"
"Stop g0xPM : 38.393141, 34.743577\n"
"Stop 9uyCGpPMbWiXVAwsXG: 38.496987, 34.885215\n"
"Bus 0NTTuU1: NKoCAqHa55 - SxvGUp9OhePe4pW FQfn - VUZ5 - 0y4ho9GnEYu21UmoV42HZB0Mv - C YdccGQZU6gbJL0mXX6IToE - 9uyCGpPMbWiXVAwsXG - luOV urWGCs - Q1yE - XiIL1rrRfmLsCvs4t1 C4AzoT\n"
"Stop wCZucJLumbtAX : 38.478467, 34.858368\n"
"Stop 4J jy2z : 38.623016, 34.928688\n"
"Stop 7iWYyQimeYwd56Ynj57: 38.668945, 34.816707\n"
"Stop 8: 38.550717, 34.864803\n"
"Stop pKIPR92hm : 38.669876, 34.857476\n"
"Bus FlvRtih : QOW7FWL5v5kdJBk3RDCZg > AC9t > dNWXYAy9UgTq > JWt2HAu > tQVD77CEYItf6vMk279fDk > g0xPM > ztVWFuioD > b5jXJLSbbBnQZsJ4OVJ87Nzf > kbU > J3GnXuZAAGf3oaa > FNJOLqRq5Ad3N2qj > WRo4l > OJOci4wu2 > aBZFsZCWEVhVMbSMvuI7b > 5RMNaOqZQp8CBhdok > HUb6xd4aaSJ01lo0ABt > mT > xn58ceA wXl0wo6fw1 > UA > PCKCn > mT > h1OTf > 1GzQO9dYIm0me > aaDrzCkRa > id aFBFmo9u7 > T893Gm > U49MIbaw4gamvekq > eNJHau6B8 > Lp4MEdrq6otSB > l3A > A2cG0537NQS > tPniDCwlR > rOdgQuDph > Rmxlj6yf5V6Hr1 6JPY9 > bdIWPK1kWMN7wvJ7zl8Cgt7m > l3A > QOW7FWL5v5kdJBk3RDCZg\n"
"Bus HTNhkr : juAdbG4 > uwp6XK > U3KBygTDyqkvCtB6o8 > NKoCAqHa55 > mq35 > T893Gm > TBP4AGPZg3GOQj5 zjGx j > Yki5weXl > 97ChPsiaFJ xk > eNJHau6B8 > 9W6KH8pazOTFPc3zss7E3 > G3o0bW > Y > vA > QbW > MRWeEEANMtzBJ8z > Lp4MEdrq6otSB > w0PgbVmxAHFGF > WUobJ5iHPZ974O > mTQElWNWMb99mLHtKSAt > YAMY0OvPvxZF2BlAzg > RopMyKExUGlJSvuPjDjAWD > bATIYunTC9Z5XN0bk0FBq7 > f6mSgT ud5 > QOW7FWL5v5kdJBk3RDCZg > aAqPX > Yki5weXl > Y7UB UGH5 > m > 6ik0QUeq6YE2ZPf8fem > fPX2y > c7vc3yBR > 7hSQl1n2m > JoLcJeV8gQAS > XiIL1rrRfmLsCvs4t1 C4AzoT > qC > XB5NAUcKh yDNGkD7EtQ8 > nhfM4 > KoAi8XSxyu x > OJOci4wu2 > RCMbeebIuxiDV > Rz > A3fg4VGWEfhi7pgZnWWtYs0wH > oM6 > 9uyCGpPMbWiXVAwsXG > mq35 > w7V0IyAT4IqNKF7fFFyBq4B > juAdbG4\n"
"Stop llbORb4gdec4Y29 : 38.565545, 34.823755\n"
"Stop 7pyxD HFSz1P : 38.454657, 34.806218\n"
"Stop w7V0IyAT4IqNKF7fFFyBq4B : 38.626672, 34.714694\n"
"Stop 47SX 1ZvTKPGQJfaRaBJNN: 38.639683, 34.941685\n"
"Stop pCumWQzxe 4xL4eWNY: 38.528561, 34.701268\n"
"Stop tQVD77CEYItf6vMk279fDk : 38.491689, 34.960576\n"
"Bus 6iqtx: 01Z6NQhKl2UUkghq > W93vQSGbE2mnskhufqwc > oM6 > jwQ5 VVfrFgl0mL8hINmugEf > 9W6KH8pazOTFPc3zss7E3 > BWMGV > aaDrzCkRa > sHYiT9RK4sqe2 > XmnTYd9cySp > z > luOV urWGCs > h230yZ > f4mV > NKoCAqHa55 > 7qpKAGotrE6vi5OEmh8Txf > jDThdjhjh2n7Wc > QbW > c7vc3yBR > dNWXYAy9UgTq > z > QdPEP6 > h > jDThdjhjh2n7Wc > aBZFsZCWEVhVMbSMvuI7b > 4xyPd > llbORb4gdec4Y29 > f4mV > hq0ln 4A7RoGuAxeTUZaBTaNp > ISlrnEIaKIEkpE4XC > Mzx > z > WRo4l > hq0ln 4A7RoGuAxeTUZaBTaNp > pKIPR92hm > FG > 4J jy2z > pKIPR92hm > 3 > jg6oInTF0IOQjanfDYimaM > c0p1aqDEdlepF > z > 2IuMsuRbGaGlT > 1GzQO9dYIm0me > VUtPzvEGpkYiJ8B7D2HmYkrci > Lp4MEdrq6otSB > f4mV > 01Z6NQhKl2UUkghq\n"
"Bus qpkmFDw2Y7db2fx5be : Y > Yki5weXl > id aFBFmo9u7 > C YdccGQZU6gbJL0mXX6IToE > Q1yE > Lp4MEdrq6otSB > JoLcJeV8gQAS > 7hSQl1n2m > 9kHYrxYT6UCUGcLH > VzkY8gVB > MRWeEEANMtzBJ8z > XEQUDl69zPpE9 > WUobJ5iHPZ974O > A2cG0537NQS > FiWYnMOOgvGlRS51l 2iP1ltP > KYszEJBfpaUkVjw5q6j > VzkY8gVB > 9n4lv > rOdgQuDph > uwp6XK > 6erXqFth8x18P5BxH50SAu7 > tQVD77CEYItf6vMk279fDk > Y7UB UGH5 > l3A > OJOci4wu2 > TBP4AGPZg3GOQj5 zjGx j > wCZucJLumbtAX > w0PgbVmxAHFGF > tPniDCwlR > pKIPR92hm > 7qpKAGotrE6vi5OEmh8Txf > lBP > m > 9uyCGpPMbWiXVAwsXG > b5jXJLSbbBnQZsJ4OVJ87Nzf > 6DlTRiDlBADHd5wxuGwM > U49MIbaw4gamvekq > Rz > 8 > AC9t > Z6WXRBiOsQBSywzKrhupa > RZIBvXF6op2sX5cURx > Y7UB UGH5 > HnD0ZD0LB > A2cG0537NQS > 97ChPsiaFJ xk > sHYiT9RK4sqe2 > luOV urWGCs > U49MIbaw4gamvekq > JoLcJeV8gQAS > A3fg4VGWEfhi7pgZnWWtYs0wH > SfV395Nnm1OrpX > Sfskshp83VkmueW7t > g0xPM > 01Z6NQhKl2UUkghq > w0PgbVmxAHFGF > hXCtNJ55eAcJyF > JWt2HAu > aBZFsZCWEVhVMbSMvuI7b > W93vQSGbE2mnskhufqwc > 6BXJi1odEOF3gnQkcH > XiIL1rrRfmLsCvs4t1 C4AzoT > G3o0bW > UsaQup0GVKc2oPtsPdvk > 9n4lv > VUtPzvEGpkYiJ8B7D2HmYkrci > 5RMNaOqZQp8CBhdok > XrjmSdG6CmrQwxfWN8ehJ > Rmxlj6yf5V6Hr1 6JPY9 > luOV urWGCs > Jkc > G3o0bW > v8yUoEHDcAR5K > T893Gm > 6DlTRiDlBADHd5wxuGwM > nhfM4 > aAqPX > kbU > ImEcfBE3Czdoa3 > XmnTYd9cySp > P > 9W6KH8pazOTFPc3zss7E3 > l3A > HUb6xd4aaSJ01lo0ABt > M2EClC > jmRffEd > L5pcYa50O j4etgtHGQt > aiAnA4AhBRojwfcFz > Rz > Rmxlj6yf5V6Hr1 6JPY9 > KZ8 > N0WC > KoAi8XSxyu x > 7pyxD HFSz1P > A3fg4VGWEfhi7pgZnWWtYs0wH > FiWYnMOOgvGlRS51l 2iP1ltP > SKWNv9tePz > oM6 > Y\n"
"Stop una0tkDG67WY2DKJlyGq : 38.648197, 34.778782\n"
"Stop Q1yE : 38.399696, 34.855165\n"
"Bus ccXiI8whRdUwuoN8aGzvJs : w0PgbVmxAHFGF > 7iWYyQimeYwd56Ynj57 > PWIHxixUS8ROFlMqFTPXA > HUb6xd4aaSJ01lo0ABt > C YdccGQZU6gbJL0mXX6IToE > fPX2y > qC > gdhjubQAp3ZEgHbYdb > t3R2RdoIYE0G4Z > Yki5weXl > bATIYunTC9Z5XN0bk0FBq7 > fgO6d5U > 9uyCGpPMbWiXVAwsXG > oVtcsLqV72 > KrSJ2LfG1Qo8EEttx > w0PgbVmxAHFGF\n"
"Stop RjQCxV2X2hcA : 38.506611, 34.762744\n"
"Bus hfmcApyZc By : c7vc3yBR - YAMY0OvPvxZF2BlAzg - RCMbeebIuxiDV - luOV urWGCs - G3o0bW - 6ik0QUeq6YE2ZPf8fem - fPX2y - 9uyCGpPMbWiXVAwsXG - yH6T6hYNXvjylXoM0uqb - 4J jy2z - 1GzQO9dYIm0me - 6DlTRiDlBADHd5wxuGwM - 6ik0QUeq6YE2ZPf8fem - uwp6XK - mT - Lp4MEdrq6otSB - 9n4lv - wEToSr8wPMLRaGmEorqMHF1e - MeOzi4ywCT1W7xFOA5h - E - esRv7H4ulnA9xmUm7cHCI8Q - mTQElWNWMb99mLHtKSAt - K - ztVWFuioD - E - sHYiT9RK4sqe2 - PWIHxixUS8ROFlMqFTPXA - iClhA6PCp1zjYNxCSdlF7Mzs - 4xyPd - HL - 6ik0QUeq6YE2ZPf8fem - PCKCn - bATIYunTC9Z5XN0bk0FBq7 - Rz - 5UQ4TtSaNNs5SKSEHuTUKdh - 3 - v8yUoEHDcAR5K - u1lesMakDVZdJUyBO96wnYX4 - t3R2RdoIYE0G4Z - UA - ztVWFuioD\n"
"Bus 25vBFZ1cF9yETC9mlHu6i: KYszEJBfpaUkVjw5q6j - A3fg4VGWEfhi7pgZnWWtYs0wH - aAqPX - KoAi8XSxyu x - h - eRlE31fLpeOfK5vSHL - eNJHau6B8 - 9uyCGpPMbWiXVAwsXG - c7vc3yBR - 4pa5EXOMn4kJeA - llbORb4gdec4Y29 - P - 6ik0QUeq6YE2ZPf8fem - hq0ln 4A7RoGuAxeTUZaBTaNp - QbvTBD - kpt - 6erXqFth8x18P5BxH50SAu7 - 2IuMsuRbGaGlT - tQVD77CEYItf6vMk279fDk - w0PgbVmxAHFGF - YAMY0OvPvxZF2BlAzg - U3KBygTDyqkvCtB6o8 - SKWNv9tePz - L5pcYa50O j4etgtHGQt - N0WC - v8yUoEHDcAR5K\n"
"Stop PWIHxixUS8ROFlMqFTPXA : 38.530023, 34.891777\n"
"Stop 5UQ4TtSaNNs5SKSEHuTUKdh: 38.641647, 34.87721\n"
"Stop 7qpKAGotrE6vi5OEmh8Txf: 38.511641, 34.757136\n"
"Bus 3SYuWR: 4pa5EXOMn4kJeA > 4xyPd > 9W6KH8pazOTFPc3zss7E3 > QOW7FWL5v5kdJBk3RDCZg > A2cG0537NQS > WGlidYF > PWIHxixUS8ROFlMqFTPXA > K > vA > c7vc3yBR > UA > J3GnXuZAAGf3oaa > L5pcYa50O j4etgtHGQt > Sfskshp83VkmueW7t > FiWYnMOOgvGlRS51l 2iP1ltP > luOV urWGCs > EJWKVw2R8gv6Od3J9NRC0UYq > XrjmSdG6CmrQwxfWN8ehJ > XEQUDl69zPpE9 > 4pa5EXOMn4kJeA > pKIPR92hm > 9n4lv > XB5NAUcKh yDNGkD7EtQ8 > 6erXqFth8x18P5BxH50SAu7 > 2fRakl6iS0cVl > NKoCAqHa55 > hq0ln 4A7RoGuAxeTUZaBTaNp > QbvTBD > kv8A5AKGj iN > 4pa5EXOMn4kJeA > ImEcfBE3Czdoa3 > id aFBFmo9u7 > Yki5weXl > f4mV > EJWKVw2R8gv6Od3J9NRC0UYq > h1OTf > xn58ceA wXl0wo6fw1 > 5RMNaOqZQp8CBhdok > 5UQ4TtSaNNs5SKSEHuTUKdh > eRlE31fLpeOfK5vSHL > 5UQ4TtSaNNs5SKSEHuTUKdh > KrSJ2LfG1Qo8EEttx > Z6WXRBiOsQBSywzKrhupa > P > f6mSgT ud5 > RCMbeebIuxiDV > juAdbG4 > b5jXJLSbbBnQZsJ4OVJ87Nzf > MeOzi4ywCT1W7xFOA5h > gtm9BlpE8bAkxfHCPiz67Xs > Y > HL > XEQUDl69zPpE9 > JoLcJeV8gQAS > kv8A5AKGj iN > N0WC > G3o0bW > ur4VppUI3StmJP > L5pcYa50O j4etgtHGQt > qC > jDThdjhjh2n7Wc > ur4VppUI3StmJP > PCKCn > XEQUDl69zPpE9 > h230yZ > U3KBygTDyqkvCtB6o8 > umomAjuO > lYPJidFhhh8qIjg0chE > K > TBP4AGPZg3GOQj5 zjGx j > t3R2RdoIYE0G4Z > mTQElWNWMb99mLHtKSAt > VzkY8gVB > A2cG0537NQS > Sfskshp83VkmueW7t > mkmqHwVr8gzfTQfL294 > w7V0IyAT4IqNKF7fFFyBq4B > HUb6xd4aaSJ01lo0ABt > UsaQup0GVKc2oPtsPdvk > f4mV > 4xyPd > l3A > Lp4MEdrq6otSB > A2cG0537NQS > 01Z6NQhKl2UUkghq > o > WRo4l > kpt > nhfM4 > aaDrzCkRa > hXCtNJ55eAcJyF > esRv7H4ulnA9xmUm7cHCI8Q > WUobJ5iHPZ974O > A2cG0537NQS > XiIL1rrRfmLsCvs4t1 C4AzoT > KIITYxZQM > bATIYunTC9Z5XN0bk0FBq7 > FG > 4pa5EXOMn4kJeA\n"
"Stop J3GnXuZAAGf3oaa : 38.656247, 34.681918\n"
"Stop EyivPqCySBygp4AaXYcEw : 38.389339, 34.746071\n"
"Stop h : 38.446272, 34.886604\n"
"Stop wEToSr8wPMLRaGmEorqMHF1e : 38.494845, 34.893165\n"
"Stop AiaFM3aIkyqmjhx : 38.515447, 34.810467\n"
"Stop VzkY8gVB : 38.591239, 34.815659\n"
"Bus Szr1eY3O4 : gtm9BlpE8bAkxfHCPiz67Xs > YN4J5hLU4vuP3UgrRt0soPVP > QexzWmRfZ7VpKt0h > Sfskshp83VkmueW7t > t3R2RdoIYE0G4Z > 6BXJi1odEOF3gnQkcH > 01Z6NQhKl2UUkghq > WUobJ5iHPZ974O > BWMGV > RCMbeebIuxiDV > aXYObzMStKKrHU4O > RCMbeebIuxiDV > z > FNJOLqRq5Ad3N2qj > aAqPX > W93vQSGbE2mnskhufqwc > mT > J3GnXuZAAGf3oaa > vA > MRWeEEANMtzBJ8z > rOdgQuDph > Yki5weXl > kbU > KZ8 > gtm9BlpE8bAkxfHCPiz67Xs\n"
"Stop PCKCn : 38.656967, 34.890373\n"
"Bus RzJIG : EyivPqCySBygp4AaXYcEw > rOdgQuDph > 9W6KH8pazOTFPc3zss7E3 > 7pyxD HFSz1P > J0X8xdE3epu2 > VUZ5 > 1GzQO9dYIm0me > 9kHYrxYT6UCUGcLH > gtm9BlpE8bAkxfHCPiz67Xs > sHYiT9RK4sqe2 > A2cG0537NQS > EJWKVw2R8gv6Od3J9NRC0UYq > pKIPR92hm > J0X8xdE3epu2 > Sfskshp83VkmueW7t > HL > ISlrnEIaKIEkpE4XC > FiWYnMOOgvGlRS51l 2iP1ltP > kbU > U3KBygTDyqkvCtB6o8 > llbORb4gdec4Y29 > 9n4lv > z > 01Z6NQhKl2UUkghq > zqIUaW3xbhG > 1GzQO9dYIm0me > UsaQup0GVKc2oPtsPdvk > KYszEJBfpaUkVjw5q6j > W93vQSGbE2mnskhufqwc > wCZucJLumbtAX > A3fg4VGWEfhi7pgZnWWtYs0wH > 7qpKAGotrE6vi5OEmh8Txf > aiAnA4AhBRojwfcFz > o > XrjmSdG6CmrQwxfWN8ehJ > esRv7H4ulnA9xmUm7cHCI8Q > wEToSr8wPMLRaGmEorqMHF1e > esRv7H4ulnA9xmUm7cHCI8Q > bdIWPK1kWMN7wvJ7zl8Cgt7m > KYszEJBfpaUkVjw5q6j > JoLcJeV8gQAS > jg6oInTF0IOQjanfDYimaM > Sfskshp83VkmueW7t > 6x9ftRRGWjuUTQQ > W93vQSGbE2mnskhufqwc > pCumWQzxe 4xL4eWNY > vA > EyivPqCySBygp4AaXYcEw\n"
"Stop A3fg4VGWEfhi7pgZnWWtYs0wH : 38.668918, 34.932016\n"
"Stop esRv7H4ulnA9xmUm7cHCI8Q : 38.521192, 34.744221\n"
"Stop A2cG0537NQS : 38.607327, 34.956791\n"
"Stop YN4J5hLU4vuP3UgrRt0soPVP : 38.390816, 34.790646\n"
"Stop 6erXqFth8x18P5BxH50SAu7: 38.661688, 34.944865\n"
"Stop kpt : 38.574003, 34.853572\n"
"Bus R1D85mS iWkyr1 : 7qjQYTatbsF928i 4 - mkmqHwVr8gzfTQfL294 - aAqPX - N0WC - oVtcsLqV72 - f4mV - EJWKVw2R8gv6Od3J9NRC0UYq - c0p1aqDEdlepF - QOW7FWL5v5kdJBk3RDCZg - 2fRakl6iS0cVl - 1GzQO9dYIm0me - WGlidYF - aBZFsZCWEVhVMbSMvuI7b - L5pcYa50O j4etgtHGQt - c7vc3yBR - J3GnXuZAAGf3oaa - Rz - id aFBFmo9u7 - h1OTf - N0WC - m - c7vc3yBR - hXCtNJ55eAcJyF - mkmqHwVr8gzfTQfL294 - pCumWQzxe 4xL4eWNY - 7qpKAGotrE6vi5OEmh8Txf - HoZGABAZFoCFmJDO7U - UsaQup0GVKc2oPtsPdvk - v8yUoEHDcAR5K - HL - TiqAnSNScH1 - LXt9PS4RSuqsisxyQkDZGH0 - T893Gm - aAqPX - OJOci4wu2 - fgO6d5U - 01Z6NQhKl2UUkghq - m - W93vQSGbE2mnskhufqwc - v8yUoEHDcAR5K - Yki5weXl - HoZGABAZFoCFmJDO7U - QbW - WGlidYF - mTQElWNWMb99mLHtKSAt - Mzx - TiqAnSNScH1 - eRlE31fLpeOfK5vSHL - VzkY8gVB - Yd 6DHbRbROdw\n"
"Bus WqUXOGl : N0WC > XEQUDl69zPpE9 > QOW7FWL5v5kdJBk3RDCZg > QbW > FNJOLqRq5Ad3N2qj > Y7UB UGH5 > t3R2RdoIYE0G4Z > KYszEJBfpaUkVjw5q6j > HL > aXYObzMStKKrHU4O > kbU > NKoCAqHa55 > J0X8xdE3epu2 > kpt > oVtcsLqV72 > QOW7FWL5v5kdJBk3RDCZg > lYPJidFhhh8qIjg0chE > 9n4lv > aAqPX > aXYObzMStKKrHU4O > pKIPR92hm > 7hSQl1n2m > f4mV > YAMY0OvPvxZF2BlAzg > 4J jy2z > KoAi8XSxyu x > FNJOLqRq5Ad3N2qj > vA > TiqAnSNScH1 > pCumWQzxe 4xL4eWNY > qC > 7qjQYTatbsF928i 4 > 9W6KH8pazOTFPc3zss7E3 > RCMbeebIuxiDV > oM6 > FG > ImEcfBE3Czdoa3 > 7iWYyQimeYwd56Ynj57 > fPX2y > wumWKUk63DWuiNF6nqpiiDSSf > KoAi8XSxyu x > w7V0IyAT4IqNKF7fFFyBq4B > lBP > mq35 > RCMbeebIuxiDV > A2cG0537NQS > hhmpyF gEZCyMurPa > b5jXJLSbbBnQZsJ4OVJ87Nzf > 2IuMsuRbGaGlT > 0y4ho9GnEYu21UmoV42HZB0Mv > YAMY0OvPvxZF2BlAzg > mT > KZ8 > 6DlTRiDlBADHd5wxuGwM > una0tkDG67WY2DKJlyGq > 3 > 13ThLjYG > KIITYxZQM > ztVWFuioD > WUobJ5iHPZ974O > 3 > SxvGUp9OhePe4pW FQfn > pKIPR92hm > aXYObzMStKKrHU4O > ztVWFuioD > uwp6XK > 3 > aAqPX > PWIHxixUS8ROFlMqFTPXA > f6mSgT ud5 > K > zqIUaW3xbhG > llbORb4gdec4Y29 > J3GnXuZAAGf3oaa > xn58ceA wXl0wo6fw1 > WRo4l > OyB2TTwVRcMgD > mOA > Lp4MEdrq6otSB > jmRffEd > NKoCAqHa55 > RZIBvXF6op2sX5cURx > XiIL1rrRfmLsCvs4t1 C4AzoT > qaqYVmrgqP76mxDYebu08xF8E > 3 > ur4VppUI3StmJP > gdhjubQAp3ZEgHbYdb > rOdgQuDph > TiqAnSNScH1 > ztVWFuioD > TBP4AGPZg3GOQj5 zjGx j > mT > HUb6xd4aaSJ01lo0ABt > h1OTf > JWt2HAu > W93vQSGbE2mnskhufqwc > mT > Rz > QOW7FWL5v5kdJBk3RDCZg > N0WC\n"
"Stop MeOzi4ywCT1W7xFOA5h : 38.654873, 34.65053\n"
"Stop ImEcfBE3Czdoa3 : 38.486468, 34.957548\n"
"Bus QuuzKJ2 : lYPJidFhhh8qIjg0chE > FNJOLqRq5Ad3N2qj > J0X8xdE3epu2 > hq0ln 4A7RoGuAxeTUZaBTaNp > wCZucJLumbtAX > kpt > 4J jy2z > TBP4AGPZg3GOQj5 zjGx j > jmRffEd > Rz > 6erXqFth8x18P5BxH50SAu7 > Sfskshp83VkmueW7t > 7iWYyQimeYwd56Ynj57 > M2EClC > w0PgbVmxAHFGF > wumWKUk63DWuiNF6nqpiiDSSf > juAdbG4 > vA > YAMY0OvPvxZF2BlAzg > AiaFM3aIkyqmjhx > jwQ5 VVfrFgl0mL8hINmugEf > JoLcJeV8gQAS > HL > oVtcsLqV72 > ur4VppUI3StmJP > wumWKUk63DWuiNF6nqpiiDSSf > RCMbeebIuxiDV > WRo4l > kpt > XiIL1rrRfmLsCvs4t1 C4AzoT > 4J jy2z > T893Gm > JoLcJeV8gQAS > CahFZzk > VUtPzvEGpkYiJ8B7D2HmYkrci > 8 > mT > OJOci4wu2 > c7vc3yBR > VUtPzvEGpkYiJ8B7D2HmYkrci > bATIYunTC9Z5XN0bk0FBq7 > Z6WXRBiOsQBSywzKrhupa > KZ8 > lBP > P > vA > XEQUDl69zPpE9 > bdIWPK1kWMN7wvJ7zl8Cgt7m > umomAjuO > HUb6xd4aaSJ01lo0ABt > KrSJ2LfG1Qo8EEttx > ur4VppUI3StmJP > 13ThLjYG > XmnTYd9cySp > MeOzi4ywCT1W7xFOA5h > rOdgQuDph > ISlrnEIaKIEkpE4XC > hXCtNJ55eAcJyF > h > 4xyPd > KZ8 > Rz > AiaFM3aIkyqmjhx > hq0ln 4A7RoGuAxeTUZaBTaNp > pKIPR92hm > llbORb4gdec4Y29 > CahFZzk > hhmpyF gEZCyMurPa > 2IuMsuRbGaGlT > eNJHau6B8 > kpt > esRv7H4ulnA9xmUm7cHCI8Q > h230yZ > QbW > hq0ln 4A7RoGuAxeTUZaBTaNp > Yd 6DHbRbROdw > W93vQSGbE2mnskhufqwc > Rmxlj6yf5V6Hr1 6JPY9 > YAMY0OvPvxZF2BlAzg > l3A > Y7UB UGH5 > U3KBygTDyqkvCtB6o8 > lYPJidFhhh8qIjg0chE\n"
"Bus SwkJxKKZdSrUmTddXCO49O884 : oVtcsLqV72 - 9n4lv - z - yH6T6hYNXvjylXoM0uqb - A9OtxLHuKLO - qaqYVmrgqP76mxDYebu08xF8E - 6erXqFth8x18P5BxH50SAu7 - KoAi8XSxyu x - OyB2TTwVRcMgD - una0tkDG67WY2DKJlyGq - KrSJ2LfG1Qo8EEttx\n"
"Stop XB5NAUcKh yDNGkD7EtQ8 : 38.648906, 34.782513\n"
"Bus rxg : SxvGUp9OhePe4pW FQfn - A2cG0537NQS - 6x9ftRRGWjuUTQQ - 6DlTRiDlBADHd5wxuGwM - C YdccGQZU6gbJL0mXX6IToE - FNJOLqRq5Ad3N2qj - KZ8 - SfV395Nnm1OrpX - KIITYxZQM - jwQ5 VVfrFgl0mL8hINmugEf - t3R2RdoIYE0G4Z - oVtcsLqV72 - 97ChPsiaFJ xk - 47SX 1ZvTKPGQJfaRaBJNN - hhmpyF gEZCyMurPa - QOW7FWL5v5kdJBk3RDCZg - MeOzi4ywCT1W7xFOA5h - K - KrSJ2LfG1Qo8EEttx - A3fg4VGWEfhi7pgZnWWtYs0wH - esRv7H4ulnA9xmUm7cHCI8Q\n"
"Stop G3o0bW : 38.505659, 34.959126\n"
"Stop iClhA6PCp1zjYNxCSdlF7Mzs : 38.678454, 35.004847\n"
"Stop mT : 38.525998, 34.953568\n"
"Stop Lp4MEdrq6otSB : 38.680274, 34.673298\n"
"Stop T893Gm : 38.726347, 34.992735\n"
"Bus Gc : Lp4MEdrq6otSB > 5UQ4TtSaNNs5SKSEHuTUKdh > yH6T6hYNXvjylXoM0uqb > HL > Lp4MEdrq6otSB\n"
"Bus 1I: umomAjuO - PCKCn - 7iWYyQimeYwd56Ynj57 - XiIL1rrRfmLsCvs4t1 C4AzoT - vA - gdhjubQAp3ZEgHbYdb - m - nhfM4 - QdPEP6 - 6erXqFth8x18P5BxH50SAu7\n"
"Bus Mtlvd6TQDHcm : N0WC - oM6 - iClhA6PCp1zjYNxCSdlF7Mzs - uwp6XK - RopMyKExUGlJSvuPjDjAWD - C YdccGQZU6gbJL0mXX6IToE - U3KBygTDyqkvCtB6o8 - fgO6d5U - U3KBygTDyqkvCtB6o8 - hXCtNJ55eAcJyF - J3GnXuZAAGf3oaa - UA - fgO6d5U - 6BXJi1odEOF3gnQkcH - 4xyPd - EyivPqCySBygp4AaXYcEw - gdhjubQAp3ZEgHbYdb - KZ8 - SKWNv9tePz - wCZucJLumbtAX - QdPEP6 - qaqYVmrgqP76mxDYebu08xF8E - 0y4ho9GnEYu21UmoV42HZB0Mv - eX02k7tW0j L2d7akVudao - 97ChPsiaFJ xk - 7hSQl1n2m - tQVD77CEYItf6vMk279fDk - xn58ceA wXl0wo6fw1 - 6BXJi1odEOF3gnQkcH - RopMyKExUGlJSvuPjDjAWD - M2EClC - imrGYjUSoKaMoOeEV - XmnTYd9cySp - 5UQ4TtSaNNs5SKSEHuTUKdh - WUobJ5iHPZ974O - JWt2HAu\n"
"Stop gtm9BlpE8bAkxfHCPiz67Xs : 38.510622, 34.836274\n"
"Stop lBP : 38.665967, 34.701089\n"
"Stop JoLcJeV8gQAS : 38.561557, 35.001735\n"
"Stop xn58ceA wXl0wo6fw1 : 38.403334, 34.997722\n"
"Stop KoAi8XSxyu x : 38.539616, 34.934399\n"
"Bus jsh : RZIBvXF6op2sX5cURx > imrGYjUSoKaMoOeEV > eX02k7tW0j L2d7akVudao > tPniDCwlR > aiAnA4AhBRojwfcFz > G3o0bW > 5UQ4TtSaNNs5SKSEHuTUKdh > QexzWmRfZ7VpKt0h > b5jXJLSbbBnQZsJ4OVJ87Nzf > SKWNv9tePz > m > E > iClhA6PCp1zjYNxCSdlF7Mzs > mTQElWNWMb99mLHtKSAt > jwQ5 VVfrFgl0mL8hINmugEf > LXt9PS4RSuqsisxyQkDZGH0 > XEQUDl69zPpE9 > KrSJ2LfG1Qo8EEttx > 7qjQYTatbsF928i 4 > YAMY0OvPvxZF2BlAzg > Yd 6DHbRbROdw > 8 > tQVD77CEYItf6vMk279fDk > RjQCxV2X2hcA > juAdbG4 > P > iClhA6PCp1zjYNxCSdlF7Mzs > hq0ln 4A7RoGuAxeTUZaBTaNp > J3GnXuZAAGf3oaa > 7hSQl1n2m > 13ThLjYG > 9W6KH8pazOTFPc3zss7E3 > 7qjQYTatbsF928i 4 > dSzlIy80Uq nSpdPYp > XrjmSdG6CmrQwxfWN8ehJ > jmRffEd > tQVD77CEYItf6vMk279fDk > hq0ln 4A7RoGuAxeTUZaBTaNp > TiqAnSNScH1 > h > A9OtxLHuKLO > AC9t > KoAi8XSxyu x > QbW > E > mTQElWNWMb99mLHtKSAt > qaqYVmrgqP76mxDYebu08xF8E > mkmqHwVr8gzfTQfL294 > 01Z6NQhKl2UUkghq > 6erXqFth8x18P5BxH50SAu7 > KIITYxZQM > jg6oInTF0IOQjanfDYimaM > UsaQup0GVKc2oPtsPdvk > ztVWFuioD > xn58ceA wXl0wo6fw1 > esRv7H4ulnA9xmUm7cHCI8Q > EyivPqCySBygp4AaXYcEw > mkmqHwVr8gzfTQfL294 > U3KBygTDyqkvCtB6o8 > 0y4ho9GnEYu21UmoV42HZB0Mv > JoLcJeV8gQAS > RopMyKExUGlJSvuPjDjAWD > J0X8xdE3epu2 > sHYiT9RK4sqe2 > xn58ceA wXl0wo6fw1 > 1GzQO9dYIm0me > MeOzi4ywCT1W7xFOA5h > A2cG0537NQS > MeOzi4ywCT1W7xFOA5h > L5pcYa50O j4etgtHGQt > MRWeEEANMtzBJ8z > QdPEP6 > QbW > WGlidYF > RZIBvXF6op2sX5cURx\n"
"Stop kbU : 38.45448, 34.822492\n"
"Bus BVB : QdPEP6 - una0tkDG67WY2DKJlyGq - QbW - SfV395Nnm1OrpX - VUZ5 - QbW - kv8A5AKGj iN - W93vQSGbE2mnskhufqwc - mq35 - v8yUoEHDcAR5K - MRWeEEANMtzBJ8z - eRlE31fLpeOfK5vSHL - dSzlIy80Uq nSpdPYp - OyB2TTwVRcMgD - Yd 6DHbRbROdw - f4mV - E\n"
"Stop SKWNv9tePz : 38.574027, 34.984959\n"
"Bus 3sxdcqW0TlrW: esRv7H4ulnA9xmUm7cHCI8Q - 2fRakl6iS0cVl - jwQ5 VVfrFgl0mL8hINmugEf - w0PgbVmxAHFGF - QbW - x6uAyDnts4HKRzp1XNol5 - MeOzi4ywCT1W7xFOA5h - N0WC - Yki5weXl - W93vQSGbE2mnskhufqwc - mTQElWNWMb99mLHtKSAt\n"
"Stop Yki5weXl : 38.705177, 34.987733\n"
"Bus E 1OVSsLHihqtd63i2lCn: Rmxlj6yf5V6Hr1 6JPY9 > o > fgO6d5U > 1GzQO9dYIm0me > juAdbG4 > QOW7FWL5v5kdJBk3RDCZg > PCKCn > w7V0IyAT4IqNKF7fFFyBq4B > umomAjuO > tPniDCwlR > PCKCn > WRo4l > 4pa5EXOMn4kJeA > aBZFsZCWEVhVMbSMvuI7b > EyivPqCySBygp4AaXYcEw > A9OtxLHuKLO > SKWNv9tePz > VUtPzvEGpkYiJ8B7D2HmYkrci > CahFZzk > VUZ5 > h230yZ > eRlE31fLpeOfK5vSHL > PWIHxixUS8ROFlMqFTPXA > qC > kpt > 7qpKAGotrE6vi5OEmh8Txf > hq0ln 4A7RoGuAxeTUZaBTaNp > Yki5weXl > qaqYVmrgqP76mxDYebu08xF8E > CahFZzk > x6uAyDnts4HKRzp1XNol5 > L5pcYa50O j4etgtHGQt > wumWKUk63DWuiNF6nqpiiDSSf > L5pcYa50O j4etgtHGQt > SKWNv9tePz > OJOci4wu2 > rOdgQuDph > 9W6KH8pazOTFPc3zss7E3 > 0y4ho9GnEYu21UmoV42HZB0Mv > RjQCxV2X2hcA > 9n4lv > SfV395Nnm1OrpX > VUtPzvEGpkYiJ8B7D2HmYkrci > T893Gm > umomAjuO > WUobJ5iHPZ974O > N0WC > 2IuMsuRbGaGlT > umomAjuO > ImEcfBE3Czdoa3 > tQVD77CEYItf6vMk279fDk > mT > XrjmSdG6CmrQwxfWN8ehJ > jDThdjhjh2n7Wc > bATIYunTC9Z5XN0bk0FBq7 > K > U49MIbaw4gamvekq > mTQElWNWMb99mLHtKSAt > QbvTBD > g0xPM > VUZ5 > HnD0ZD0LB > aXYObzMStKKrHU4O > umomAjuO > 7hSQl1n2m > A9OtxLHuKLO > Rmxlj6yf5V6Hr1 6JPY9\n"
"Stop sHYiT9RK4sqe2 : 38.525394, 34.98831\n"
"Bus fePEeTYg8fcRO1 TPuGrJgeLR : dSzlIy80Uq nSpdPYp > Mzx > f6mSgT ud5 > HUb6xd4aaSJ01lo0ABt > hhmpyF gEZCyMurPa > RjQCxV2X2hcA > b5jXJLSbbBnQZsJ4OVJ87Nzf > v8yUoEHDcAR5K > MRWeEEANMtzBJ8z > L5pcYa50O j4etgtHGQt > 3 > FG > 9W6KH8pazOTFPc3zss7E3 > uwp6XK > 97ChPsiaFJ xk > XEQUDl69zPpE9 > A3fg4VGWEfhi7pgZnWWtYs0wH > 47SX 1ZvTKPGQJfaRaBJNN > pKIPR92hm > eRlE31fLpeOfK5vSHL > AC9t > juAdbG4 > MRWeEEANMtzBJ8z > b5jXJLSbbBnQZsJ4OVJ87Nzf > E > LXt9PS4RSuqsisxyQkDZGH0 > mkmqHwVr8gzfTQfL294 > UA > v8yUoEHDcAR5K > ImEcfBE3Czdoa3 > Z6WXRBiOsQBSywzKrhupa > QexzWmRfZ7VpKt0h > 6erXqFth8x18P5BxH50SAu7 > 5RMNaOqZQp8CBhdok > aAqPX > l3A > QbW > Rz > 6BXJi1odEOF3gnQkcH > 4J jy2z > lBP > TiqAnSNScH1 > h230yZ > K > mOA > aiAnA4AhBRojwfcFz > o > JoLcJeV8gQAS > h1OTf > 6DlTRiDlBADHd5wxuGwM > TBP4AGPZg3GOQj5 zjGx j > lYPJidFhhh8qIjg0chE > jg6oInTF0IOQjanfDYimaM > HoZGABAZFoCFmJDO7U > ur4VppUI3StmJP > c0p1aqDEdlepF > U3KBygTDyqkvCtB6o8 > zqIUaW3xbhG > LXt9PS4RSuqsisxyQkDZGH0 > WGlidYF > W93vQSGbE2mnskhufqwc > YN4J5hLU4vuP3UgrRt0soPVP > aXYObzMStKKrHU4O > vA > HL > L5pcYa50O j4etgtHGQt > qaqYVmrgqP76mxDYebu08xF8E > MeOzi4ywCT1W7xFOA5h > NKoCAqHa55 > qaqYVmrgqP76mxDYebu08xF8E > WUobJ5iHPZ974O > tPniDCwlR > kbU > TiqAnSNScH1 > SKWNv9tePz > YN4J5hLU4vuP3UgrRt0soPVP > HUb6xd4aaSJ01lo0ABt > wEToSr8wPMLRaGmEorqMHF1e > RopMyKExUGlJSvuPjDjAWD > vA > BWMGV > U49MIbaw4gamvekq > JWt2HAu > h1OTf > 9uyCGpPMbWiXVAwsXG > L5pcYa50O j4etgtHGQt > KIITYxZQM > 6ik0QUeq6YE2ZPf8fem > dSzlIy80Uq nSpdPYp\n"
"Bus 1zGhjjAhlDbcO CDy : f6mSgT ud5 > G3o0bW > 6DlTRiDlBADHd5wxuGwM > AiaFM3aIkyqmjhx > aXYObzMStKKrHU4O > Mzx > XEQUDl69zPpE9 > J0X8xdE3epu2 > 7pyxD HFSz1P > WRo4l > kbU > SxvGUp9OhePe4pW FQfn > 7pyxD HFSz1P > f6mSgT ud5 > iClhA6PCp1zjYNxCSdlF7Mzs > eX02k7tW0j L2d7akVudao > 2IuMsuRbGaGlT > g0xPM > XmnTYd9cySp > WUobJ5iHPZ974O > llbORb4gdec4Y29 > UA > hq0ln 4A7RoGuAxeTUZaBTaNp > 0y4ho9GnEYu21UmoV42HZB0Mv > 47SX 1ZvTKPGQJfaRaBJNN > uwp6XK > m > l3A > g0xPM > jmRffEd > JoLcJeV8gQAS > U3KBygTDyqkvCtB6o8 > KoAi8XSxyu x > gdhjubQAp3ZEgHbYdb > ImEcfBE3Czdoa3 > aaDrzCkRa > xn58ceA wXl0wo6fw1 > hhmpyF gEZCyMurPa > FiWYnMOOgvGlRS51l 2iP1ltP > FG > luOV urWGCs > x6uAyDnts4HKRzp1XNol5 > tPniDCwlR > imrGYjUSoKaMoOeEV > h1OTf > z > mbn1HhDBYL1 > aAqPX > RopMyKExUGlJSvuPjDjAWD > RjQCxV2X2hcA > WRo4l > v8yUoEHDcAR5K > c0p1aqDEdlepF > XB5NAUcKh yDNGkD7EtQ8 > KoAi8XSxyu x > z > 4J jy2z > N0WC > iClhA6PCp1zjYNxCSdlF7Mzs > aiAnA4AhBRojwfcFz > h > oVtcsLqV72 > pKIPR92hm > dNWXYAy9UgTq > Q1yE > m > QexzWmRfZ7VpKt0h > sHYiT9RK4sqe2 > b5jXJLSbbBnQZsJ4OVJ87Nzf > qC > 9uyCGpPMbWiXVAwsXG > t3R2RdoIYE0G4Z > C YdccGQZU6gbJL0mXX6IToE > qaqYVmrgqP76mxDYebu08xF8E > nhfM4 > QbvTBD > HoZGABAZFoCFmJDO7U > WRo4l > llbORb4gdec4Y29 > T893Gm > AC9t > x6uAyDnts4HKRzp1XNol5 > 9kHYrxYT6UCUGcLH > E > nhfM4 > pCumWQzxe 4xL4eWNY > HUb6xd4aaSJ01lo0ABt > 9W6KH8pazOTFPc3zss7E3 > ztVWFuioD > u1lesMakDVZdJUyBO96wnYX4 > oM6 > 7hSQl1n2m > mq35 > pKIPR92hm > EJWKVw2R8gv6Od3J9NRC0UYq > aBZFsZCWEVhVMbSMvuI7b > f6mSgT ud5\n"
"Bus woNoTDr : C YdccGQZU6gbJL0mXX6IToE > QbvTBD > mkmqHwVr8gzfTQfL294 > MRWeEEANMtzBJ8z > VzkY8gVB > tQVD77CEYItf6vMk279fDk > llbORb4gdec4Y29 > YN4J5hLU4vuP3UgrRt0soPVP > UA > 2IuMsuRbGaGlT > kpt > qC > mkmqHwVr8gzfTQfL294 > YAMY0OvPvxZF2BlAzg > WUobJ5iHPZ974O > Mzx > hhmpyF gEZCyMurPa > oM6 > JWt2HAu > Y7UB UGH5 > Rz > YN4J5hLU4vuP3UgrRt0soPVP > Lp4MEdrq6otSB > 01Z6NQhKl2UUkghq > mbn1HhDBYL1 > 7qpKAGotrE6vi5OEmh8Txf > JoLcJeV8gQAS > 6DlTRiDlBADHd5wxuGwM > 4J jy2z > XiIL1rrRfmLsCvs4t1 C4AzoT > U49MIbaw4gamvekq > 7qpKAGotrE6vi5OEmh8Txf > juAdbG4 > RjQCxV2X2hcA > M2EClC > NKoCAqHa55 > v8yUoEHDcAR5K > P > VUtPzvEGpkYiJ8B7D2HmYkrci > JoLcJeV8gQAS > QexzWmRfZ7VpKt0h > h230yZ > HL > YN4J5hLU4vuP3UgrRt0soPVP > mTQElWNWMb99mLHtKSAt > tQVD77CEYItf6vMk279fDk > Yd 6DHbRbROdw > esRv7H4ulnA9xmUm7cHCI8Q > SfV395Nnm1OrpX > eX02k7tW0j L2d7akVudao > 9kHYrxYT6UCUGcLH > ISlrnEIaKIEkpE4XC > KrSJ2LfG1Qo8EEttx > wCZucJLumbtAX > W93vQSGbE2mnskhufqwc > A3fg4VGWEfhi7pgZnWWtYs0wH > UsaQup0GVKc2oPtsPdvk > dNWXYAy9UgTq > mTQElWNWMb99mLHtKSAt > 5RMNaOqZQp8CBhdok > P > HUb6xd4aaSJ01lo0ABt > K > Mzx > 6BXJi1odEOF3gnQkcH > jg6oInTF0IOQjanfDYimaM > aaDrzCkRa > LXt9PS4RSuqsisxyQkDZGH0 > 7iWYyQimeYwd56Ynj57 > A2cG0537NQS > RCMbeebIuxiDV > RjQCxV2X2hcA > 7qpKAGotrE6vi5OEmh8Txf > umomAjuO > zqIUaW3xbhG > mkmqHwVr8gzfTQfL294 > jDThdjhjh2n7Wc > llbORb4gdec4Y29 > C YdccGQZU6gbJL0mXX6IToE\n"
"Stop RZIBvXF6op2sX5cURx : 38.468075, 34.769799\n"
"Stop FG : 38.714989, 34.982362\n"
"Stop HUb6xd4aaSJ01lo0ABt : 38.709242, 34.85923\n"
"Bus h4dpxtRSvC3Pous : wCZucJLumbtAX - l3A - VUtPzvEGpkYiJ8B7D2HmYkrci - llbORb4gdec4Y29 - 5RMNaOqZQp8CBhdok - 7pyxD HFSz1P - TiqAnSNScH1 - h - wumWKUk63DWuiNF6nqpiiDSSf - pKIPR92hm - id aFBFmo9u7 - hq0ln 4A7RoGuAxeTUZaBTaNp - M2EClC - SxvGUp9OhePe4pW FQfn - oVtcsLqV72 - wEToSr8wPMLRaGmEorqMHF1e - aBZFsZCWEVhVMbSMvuI7b - FG - KoAi8XSxyu x - EyivPqCySBygp4AaXYcEw - 47SX 1ZvTKPGQJfaRaBJNN - C YdccGQZU6gbJL0mXX6IToE - wCZucJLumbtAX - aiAnA4AhBRojwfcFz - RZIBvXF6op2sX5cURx - XEQUDl69zPpE9 - KZ8 - bdIWPK1kWMN7wvJ7zl8Cgt7m - VzkY8gVB - tQVD77CEYItf6vMk279fDk - fPX2y - TiqAnSNScH1 - o - RopMyKExUGlJSvuPjDjAWD - TiqAnSNScH1 - jg6oInTF0IOQjanfDYimaM\n"
"Bus e8XqEyqRsJSYUgIpvNBTH : pKIPR92hm - 9W6KH8pazOTFPc3zss7E3 - f4mV - FNJOLqRq5Ad3N2qj - XiIL1rrRfmLsCvs4t1 C4AzoT - 2fRakl6iS0cVl - mOA - luOV urWGCs - v8yUoEHDcAR5K - NKoCAqHa55 - W93vQSGbE2mnskhufqwc - 3 - w0PgbVmxAHFGF - SfV395Nnm1OrpX - rOdgQuDph - 6DlTRiDlBADHd5wxuGwM - 01Z6NQhKl2UUkghq - J0X8xdE3epu2 - VUZ5 - QbW - WRo4l - Mzx - o - gdhjubQAp3ZEgHbYdb - dSzlIy80Uq nSpdPYp - ISlrnEIaKIEkpE4XC - WUobJ5iHPZ974O - eX02k7tW0j L2d7akVudao - 6erXqFth8x18P5BxH50SAu7 - SKWNv9tePz - w0PgbVmxAHFGF - EyivPqCySBygp4AaXYcEw - kv8A5AKGj iN - Y7UB UGH5 - w7V0IyAT4IqNKF7fFFyBq4B - x6uAyDnts4HKRzp1XNol5\n"
"Stop oVtcsLqV72 : 38.69921, 34.746364\n"
"Stop bATIYunTC9Z5XN0bk0FBq7 : 38.48253, 34.720593\n"
"Stop J0X8xdE3epu2 : 38.551476, 34.736944\n"
"Stop h1OTf : 38.566795, 34.995027\n"
"Bus jo7ZoTNM1dMooS 2uAA7tvo2: KYszEJBfpaUkVjw5q6j > 1GzQO9dYIm0me > x6uAyDnts4HKRzp1XNol5 > m > tQVD77CEYItf6vMk279fDk > eRlE31fLpeOfK5vSHL > SfV395Nnm1OrpX > aXYObzMStKKrHU4O > f4mV > 1GzQO9dYIm0me > SfV395Nnm1OrpX > kpt > HoZGABAZFoCFmJDO7U > PWIHxixUS8ROFlMqFTPXA > KYszEJBfpaUkVjw5q6j\n"
"Stop WGlidYF : 38.472672, 34.765131\n"
"Bus JZ : RZIBvXF6op2sX5cURx > c7vc3yBR > 7hSQl1n2m > 01Z6NQhKl2UUkghq > w7V0IyAT4IqNKF7fFFyBq4B > AiaFM3aIkyqmjhx > h230yZ > XEQUDl69zPpE9 > ImEcfBE3Czdoa3 > RZIBvXF6op2sX5cURx > aaDrzCkRa > C YdccGQZU6gbJL0mXX6IToE > w0PgbVmxAHFGF > wumWKUk63DWuiNF6nqpiiDSSf > z > SfV395Nnm1OrpX > iClhA6PCp1zjYNxCSdlF7Mzs > RjQCxV2X2hcA > aaDrzCkRa > HUb6xd4aaSJ01lo0ABt > kbU > qC > 6DlTRiDlBADHd5wxuGwM > 4xyPd > 3 > 97ChPsiaFJ xk > 6BXJi1odEOF3gnQkcH > fgO6d5U > g0xPM > kv8A5AKGj iN > RjQCxV2X2hcA > J0X8xdE3epu2 > Yd 6DHbRbROdw > 6x9ftRRGWjuUTQQ > luOV urWGCs > SKWNv9tePz > c0p1aqDEdlepF > KZ8 > 4J jy2z > 6x9ftRRGWjuUTQQ > c0p1aqDEdlepF > yH6T6hYNXvjylXoM0uqb > A2cG0537NQS > QbW > FG > fgO6d5U > imrGYjUSoKaMoOeEV > h > RopMyKExUGlJSvuPjDjAWD > f4mV > v8yUoEHDcAR5K > aXYObzMStKKrHU4O > JWt2HAu > 7qpKAGotrE6vi5OEmh8Txf > XrjmSdG6CmrQwxfWN8ehJ > 6x9ftRRGWjuUTQQ > K > f6mSgT ud5 > P > bATIYunTC9Z5XN0bk0FBq7 > VzkY8gVB > WGlidYF > QdPEP6 > vA > hhmpyF gEZCyMurPa > NKoCAqHa55 > SfV395Nnm1OrpX > oM6 > HnD0ZD0LB > h1OTf > CahFZzk > t3R2RdoIYE0G4Z > mbn1HhDBYL1 > Z6WXRBiOsQBSywzKrhupa > g0xPM > l3A > HL > llbORb4gdec4Y29 > XmnTYd9cySp > RZIBvXF6op2sX5cURx\n"
"Stop Sfskshp83VkmueW7t : 38.528983, 34.866007\n"
"Bus s4 : Lp4MEdrq6otSB - 6ik0QUeq6YE2ZPf8fem - SxvGUp9OhePe4pW FQfn - dSzlIy80Uq nSpdPYp - tPniDCwlR - AiaFM3aIkyqmjhx - 4J jy2z - tPniDCwlR - ImEcfBE3Czdoa3 - 6erXqFth8x18P5BxH50SAu7 - WGlidYF - KZ8 - HnD0ZD0LB - 6BXJi1odEOF3gnQkcH - g0xPM - nhfM4 - aaDrzCkRa - FNJOLqRq5Ad3N2qj - Y7UB UGH5 - QexzWmRfZ7VpKt0h - hXCtNJ55eAcJyF - mkmqHwVr8gzfTQfL294 - tQVD77CEYItf6vMk279fDk - dSzlIy80Uq nSpdPYp - 6x9ftRRGWjuUTQQ - JWt2HAu - 7qpKAGotrE6vi5OEmh8Txf - RCMbeebIuxiDV - z - x6uAyDnts4HKRzp1XNol5 - UsaQup0GVKc2oPtsPdvk - QOW7FWL5v5kdJBk3RDCZg - MeOzi4ywCT1W7xFOA5h - JWt2HAu - jmRffEd - Q1yE - sHYiT9RK4sqe2 - Yki5weXl - MRWeEEANMtzBJ8z - 13ThLjYG - HoZGABAZFoCFmJDO7U - WGlidYF - x6uAyDnts4HKRzp1XNol5 - HnD0ZD0LB - N0WC - KYszEJBfpaUkVjw5q6j - J3GnXuZAAGf3oaa\n"
"Stop XmnTYd9cySp : 38.691137, 34.944883\n"
"Bus QqYkn8IywhPaaiq : lYPJidFhhh8qIjg0chE > eRlE31fLpeOfK5vSHL > C YdccGQZU6gbJL0mXX6IToE > QexzWmRfZ7VpKt0h > fPX2y > hXCtNJ55eAcJyF > wumWKUk63DWuiNF6nqpiiDSSf > fPX2y > EyivPqCySBygp4AaXYcEw > VUtPzvEGpkYiJ8B7D2HmYkrci > llbORb4gdec4Y29 > HL > mq35 > bATIYunTC9Z5XN0bk0FBq7 > gtm9BlpE8bAkxfHCPiz67Xs > 6BXJi1odEOF3gnQkcH > w0PgbVmxAHFGF > 01Z6NQhKl2UUkghq > QexzWmRfZ7VpKt0h > umomAjuO > 3 > 5UQ4TtSaNNs5SKSEHuTUKdh > eRlE31fLpeOfK5vSHL > eX02k7tW0j L2d7akVudao > ur4VppUI3StmJP > QbvTBD > rOdgQuDph > CahFZzk > NKoCAqHa55 > h230yZ > zqIUaW3xbhG > dSzlIy80Uq nSpdPYp > aBZFsZCWEVhVMbSMvuI7b > 97ChPsiaFJ xk > kpt > KIITYxZQM > 6BXJi1odEOF3gnQkcH > w0PgbVmxAHFGF > HnD0ZD0LB > HL > RopMyKExUGlJSvuPjDjAWD > luOV urWGCs > KIITYxZQM > 01Z6NQhKl2UUkghq > WRo4l > A9OtxLHuKLO > YAMY0OvPvxZF2BlAzg > 1GzQO9dYIm0me > HnD0ZD0LB > bATIYunTC9Z5XN0bk0FBq7 > id aFBFmo9u7 > ISlrnEIaKIEkpE4XC > XrjmSdG6CmrQwxfWN8ehJ > jmRffEd > Z6WXRBiOsQBSywzKrhupa > lYPJidFhhh8qIjg0chE\n"
"Stop 1GzQO9dYIm0me: 38.722844, 34.91119\n"
"Stop imrGYjUSoKaMoOeEV : 38.543323, 34.734868\n"
"Stop HnD0ZD0LB : 38.455819, 34.90135\n"
"Stop AC9t : 38.526642, 34.774462\n"
"Stop b5jXJLSbbBnQZsJ4OVJ87Nzf : 38.684222, 34.750811\n"
"Bus ZMlOhBpB2HXfz2DtN1GValBb : 7hSQl1n2m > c0p1aqDEdlepF > tQVD77CEYItf6vMk279fDk > gdhjubQAp3ZEgHbYdb > esRv7H4ulnA9xmUm7cHCI8Q > CahFZzk > pCumWQzxe 4xL4eWNY > oM6 > 2IuMsuRbGaGlT > VUZ5 > XEQUDl69zPpE9 > OJOci4wu2 > eRlE31fLpeOfK5vSHL > 9W6KH8pazOTFPc3zss7E3 > qC > LXt9PS4RSuqsisxyQkDZGH0 > imrGYjUSoKaMoOeEV > RCMbeebIuxiDV > UsaQup0GVKc2oPtsPdvk > mTQElWNWMb99mLHtKSAt > QbvTBD > aaDrzCkRa > U3KBygTDyqkvCtB6o8 > PCKCn > Rmxlj6yf5V6Hr1 6JPY9 > wCZucJLumbtAX > gdhjubQAp3ZEgHbYdb > iClhA6PCp1zjYNxCSdlF7Mzs > WRo4l > o > Q1yE > mOA > 01Z6NQhKl2UUkghq > 6BXJi1odEOF3gnQkcH > KIITYxZQM > wEToSr8wPMLRaGmEorqMHF1e > QbW > LXt9PS4RSuqsisxyQkDZGH0 > 5UQ4TtSaNNs5SKSEHuTUKdh > XiIL1rrRfmLsCvs4t1 C4AzoT > SxvGUp9OhePe4pW FQfn > RjQCxV2X2hcA > kpt > pKIPR92hm > W93vQSGbE2mnskhufqwc > 7hSQl1n2m\n"
"Stop FiWYnMOOgvGlRS51l 2iP1ltP: 38.493436, 34.78381\n"

};

    InputReader Input(input, transport_catalogue);
    std::istringstream output{
    "100\n"
"Bus sA50azC97OMPt3BPX\n"
"Bus jUA8eoWV9KkVE\n"
"Bus nPFuS0guFw2 8Awf\n"
"Bus WqUXOGl\n"
"Bus gBjmm65BVfcWBKmwi5\n"
"Bus 5yOg2sWTpk1XXUaPXXgnhLINI\n"
"Bus hfmcApyZc By\n"
"Bus ZMlOhBpB2HXfz2DtN1GValBb\n"
"Bus RzJIG\n"
"Bus R1D85mS iWkyr1\n"
"Bus ixbiNlw\n"
"Bus fePEeTYg8fcRO1 TPuGrJgeLR\n"
"Bus J jy ybF0CGIORQhqp\n"
"Bus XU\n"
"Bus CtJOIgFpt9ptZteXtmVcf0nZI\n"
"Bus Q\n"
"Bus fePEeTYg8fcRO1 TPuGrJgeLR\n"
"Bus Mtlvd6TQDHcm\n"
"Bus pIXFth9Y16Em\n"
"Bus iBAbvykyUAujN\n"
"Bus wliQ9DLIHn\n"
"Bus wSX9kMv5NmodztTukEuRAkf8P\n"
"Bus 0n7d5xCe1S\n"
"Bus 0NTTuU1\n"
"Bus CtJOIgFpt9ptZteXtmVcf0nZI\n"
"Bus h4dpxtRSvC3Pous\n"
"Bus CfAk6rjAF5Ucu26cCHpA\n"
"Bus knlX6Q88\n"
"Bus V7fnb\n"
"Bus m6mj5Cj9pzJ5hvNTYnFyIyMH8\n"
"Bus f8uj\n"
"Bus uCqmNz\n"
"Bus 0n7d5xCe1S\n"
"Bus BVB\n"
"Bus 7ncmLwXQHul zQf\n"
"Bus nRWzl3IWxFu\n"
"Bus jHtiZ0pjl\n"
"Bus R1D85mS iWkyr1\n"
"Bus 876c40RmluF\n"
"Bus G25AgVPhayb3ckP2f1\n"
"Bus wSX9kMv5NmodztTukEuRAkf8P\n"
"Bus HuX8Yabr\n"
"Bus 1I\n"
"Bus ukHDNN4j 1aj5vB7TJsGhg\n"
"Bus ukHDNN4j 1aj5vB7TJsGhg\n"
"Bus 5UefmiSd1fEd32w0b89\n"
"Bus bQ4vsTvWhXlQEi\n"
"Bus e8XqEyqRsJSYUgIpvNBTH\n"
"Bus E 1OVSsLHihqtd63i2lCn\n"
"Bus 25vBFZ1cF9yETC9mlHu6i\n"
"Bus m6mj5Cj9pzJ5hvNTYnFyIyMH8\n"
"Bus BVB\n"
"Bus e8XqEyqRsJSYUgIpvNBTH\n"
"Bus RzJIG\n"
"Bus 0d6\n"
"Bus ACMMek\n"
"Bus m6mj5Cj9pzJ5hvNTYnFyIyMH8\n"
"Bus lU\n"
"Bus yiKTH6e6u50I kgvlXG\n"
"Bus 0d6\n"
"Bus Ho7KF8bipjJly8TvvQ\n"
"Bus ZVmNhh9is90LP1YKtO\n"
"Bus JZ\n"
"Bus 16GhGA SD QBeC2m\n"
"Bus 2MxT\n"
"Bus vrPjRFJy1Q4Aq QGU\n"
"Bus ACMMek\n"
"Bus NIp x5\n"
"Bus 25vBFZ1cF9yETC9mlHu6i\n"
"Bus WqUXOGl\n"
"Bus s4\n"
"Bus nRWzl3IWxFu\n"
"Bus CfAk6rjAF5Ucu26cCHpA\n"
"Bus ai\n"
"Bus 5UefmiSd1fEd32w0b89\n"
"Bus 2MxT\n"
"Bus e8XqEyqRsJSYUgIpvNBTH\n"
"Bus 876c40RmluF\n"
"Bus HTNhkr\n"
"Bus hl7xRZX\n"
"Bus ccXiI8whRdUwuoN8aGzvJs\n"
"Bus h4dpxtRSvC3Pous\n"
"Bus C\n"
"Bus 1zGhjjAhlDbcO CDy\n"
"Bus 2MxT\n"
"Bus 8lBQ\n"
"Bus 3R7Q1I9ACzzX\n"
"Bus Ho7KF8bipjJly8TvvQ\n"
"Bus 1I\n"
"Bus sA50azC97OMPt3BPX\n"
"Bus FlvRtih\n"
"Bus ZVmNhh9is90LP1YKtO\n"
"Bus F7MHFi7g098LQ\n"
"Bus jsh\n"
"Bus njbuySC7\n"
"Bus 7x8ivGxqv3ajV2syTNo9NpTy\n"
"Bus h4dpxtRSvC3Pous\n"
"Bus HH\n"
"Bus Szr1eY3O4\n"
"Bus HK46\n"
    };

    std::ostringstream out_stream;

    StatReader Stat(output, out_stream, transport_catalogue);

    std::string str = out_stream.str();

    //assert(str == ("Bus sA50azC97OMPt3BPX: 68 stops on route, 56 unique stops, 1.07457e+06 route length\nBus jUA8eoWV9KkVE: not found\nBus nPFuS0guFw2 8Awf: 51 stops on route, 24 unique stops, 987441 route length\nBus WqUXOGl: 100 stops on route, 80 unique stops, 1.88517e+06 route length\nBus gBjmm65BVfcWBKmwi5: 59 stops on route, 28 unique stops, 1.13626e+06 route length\nBus 5yOg2sWTpk1XXUaPXXgnhLINI: not found\nBus hfmcApyZc By: 81 stops on route, 37 unique stops, 1.54904e+06 route length\nBus ZMlOhBpB2HXfz2DtN1GValBb: 46 stops on route, 43 unique stops, 743217 route length\nBus RzJIG: 48 stops on route, 41 unique stops, 702377 route length\nBus R1D85mS iWkyr1: 99 stops on route, 41 unique stops, 1.66299e+06 route length\nBus ixbiNlw: 17 stops on route, 9 unique stops, 328951 route length\nBus fePEeTYg8fcRO1 TPuGrJgeLR: 89 stops on route, 76 unique stops, 1.5174e+06 route length\nBus J jy ybF0CGIORQhqp: not found\nBus XU: 75 stops on route, 34 unique stops, 1.1446e+06 route length\nBus CtJOIgFpt9ptZteXtmVcf0nZI: 73 stops on route, 33 unique stops, 1.27211e+06 route length\nBus Q: 77 stops on route, 35 unique stops, 1.47438e+06 route length\nBus fePEeTYg8fcRO1 TPuGrJgeLR: 89 stops on route, 76 unique stops, 1.5174e+06 route length\nBus Mtlvd6TQDHcm: 71 stops on route, 32 unique stops, 1.14215e+06 route length\nBus pIXFth9Y16Em: 3 stops on route, 2 unique stops, 68130.3 route length\nBus iBAbvykyUAujN: 86 stops on route, 66 unique stops, 1.46238e+06 route length\nBus wliQ9DLIHn: 34 stops on route, 30 unique stops, 593049 route length\nBus wSX9kMv5NmodztTukEuRAkf8P: 33 stops on route, 16 unique stops, 584456 route length\nBus 0n7d5xCe1S: 52 stops on route, 49 unique stops, 952482 route length\nBus 0NTTuU1: 17 stops on route, 9 unique stops, 242311 route length\nBus CtJOIgFpt9ptZteXtmVcf0nZI: 73 stops on route, 33 unique stops, 1.27211e+06 route length\nBus h4dpxtRSvC3Pous: 71 stops on route, 33 unique stops, 1.20537e+06 route length\nBus CfAk6rjAF5Ucu26cCHpA: 67 stops on route, 32 unique stops, 1.22627e+06 route length\nBus knlX6Q88: not found\nBus V7fnb: 47 stops on route, 23 unique stops, 760530 route length\nBus m6mj5Cj9pzJ5hvNTYnFyIyMH8: 81 stops on route, 70 unique stops, 1.32404e+06 route length\nBus f8uj: not found\nBus uCqmNz: not found\nBus 0n7d5xCe1S: 52 stops on route, 49 unique stops, 952482 route length\nBus BVB: 33 stops on route, 16 unique stops, 681438 route length\nBus 7ncmLwXQHul zQf: not found\nBus nRWzl3IWxFu: 65 stops on route, 29 unique stops, 1.05165e+06 route length\nBus jHtiZ0pjl: 7 stops on route, 4 unique stops, 138049 route length\nBus R1D85mS iWkyr1: 99 stops on route, 41 unique stops, 1.66299e+06 route length\nBus 876c40RmluF: 87 stops on route, 72 unique stops, 1.4974e+06 route length\nBus G25AgVPhayb3ckP2f1: not found\nBus wSX9kMv5NmodztTukEuRAkf8P: 33 stops on route, 16 unique stops, 584456 route length\nBus HuX8Yabr: 55 stops on route, 50 unique stops, 1.00655e+06 route length\nBus 1I: 19 stops on route, 10 unique stops, 226220 route length\nBus ukHDNN4j 1aj5vB7TJsGhg: 89 stops on route, 44 unique stops, 1.56009e+06 route length\nBus ukHDNN4j 1aj5vB7TJsGhg: 89 stops on route, 44 unique stops, 1.56009e+06 route length\nBus 5UefmiSd1fEd32w0b89: 55 stops on route, 28 unique stops, 1.0257e+06 route length\nBus bQ4vsTvWhXlQEi: 82 stops on route, 66 unique stops, 1.47311e+06 route length\nBus e8XqEyqRsJSYUgIpvNBTH: 71 stops on route, 35 unique stops, 1.18177e+06 route length\nBus E 1OVSsLHihqtd63i2lCn: 67 stops on route, 56 unique stops, 1.28545e+06 route length\nBus 25vBFZ1cF9yETC9mlHu6i: 51 stops on route, 26 unique stops, 891144 route length\nBus m6mj5Cj9pzJ5hvNTYnFyIyMH8: 81 stops on route, 70 unique stops, 1.32404e+06 route length\nBus BVB: 33 stops on route, 16 unique stops, 681438 route length\nBus e8XqEyqRsJSYUgIpvNBTH: 71 stops on route, 35 unique stops, 1.18177e+06 route length\nBus RzJIG: 48 stops on route, 41 unique stops, 702377 route length\nBus 0d6: 47 stops on route, 23 unique stops, 897140 route length\nBus ACMMek: 13 stops on route, 7 unique stops, 242835 route length\nBus m6mj5Cj9pzJ5hvNTYnFyIyMH8: 81 stops on route, 70 unique stops, 1.32404e+06 route length\nBus lU: 31 stops on route, 16 unique stops, 546834 route length\nBus yiKTH6e6u50I kgvlXG: 23 stops on route, 12 unique stops, 433251 route length\nBus 0d6: 47 stops on route, 23 unique stops, 897140 route length\nBus Ho7KF8bipjJly8TvvQ: 98 stops on route, 76 unique stops, 1.63251e+06 route length\nBus ZVmNhh9is90LP1YKtO: 24 stops on route, 23 unique stops, 400907 route length\nBus JZ: 80 stops on route, 70 unique stops, 1.46545e+06 route length\nBus 16GhGA SD QBeC2m: not found\nBus 2MxT: 15 stops on route, 8 unique stops, 284919 route length\nBus vrPjRFJy1Q4Aq QGU: 55 stops on route, 28 unique stops, 1.01875e+06 route length\nBus ACMMek: 13 stops on route, 7 unique stops, 242835 route length\nBus NIp x5: not found\nBus 25vBFZ1cF9yETC9mlHu6i: 51 stops on route, 26 unique stops, 891144 route length\nBus WqUXOGl: 100 stops on route, 80 unique stops, 1.88517e+06 route length\nBus s4: 93 stops on route, 41 unique stops, 1.7003e+06 route length\nBus nRWzl3IWxFu: 65 stops on route, 29 unique stops, 1.05165e+06 route length\nBus CfAk6rjAF5Ucu26cCHpA: 67 stops on route, 32 unique stops, 1.22627e+06 route length\nBus ai: 88 stops on route, 72 unique stops, 1.46726e+06 route length\nBus 5UefmiSd1fEd32w0b89: 55 stops on route, 28 unique stops, 1.0257e+06 route length\nBus 2MxT: 15 stops on route, 8 unique stops, 284919 route length\nBus e8XqEyqRsJSYUgIpvNBTH: 71 stops on route, 35 unique stops, 1.18177e+06 route length\nBus 876c40RmluF: 87 stops on route, 72 unique stops, 1.4974e+06 route length\nBus HTNhkr: 48 stops on route, 45 unique stops, 753619 route length\nBus hl7xRZX: 71 stops on route, 34 unique stops, 1.27732e+06 route length\nBus ccXiI8whRdUwuoN8aGzvJs: 16 stops on route, 15 unique stops, 288960 route length\nBus h4dpxtRSvC3Pous: 71 stops on route, 33 unique stops, 1.20537e+06 route length\nBus C: 37 stops on route, 19 unique stops, 701997 route length\nBus 1zGhjjAhlDbcO CDy: 97 stops on route, 83 unique stops, 1.76154e+06 route length\nBus 2MxT: 15 stops on route, 8 unique stops, 284919 route length\nBus 8lBQ: not found\nBus 3R7Q1I9ACzzX: 9 stops on route, 5 unique stops, 83441.7 route length\nBus Ho7KF8bipjJly8TvvQ: 98 stops on route, 76 unique stops, 1.63251e+06 route length\nBus 1I: 19 stops on route, 10 unique stops, 226220 route length\nBus sA50azC97OMPt3BPX: 68 stops on route, 56 unique stops, 1.07457e+06 route length\nBus FlvRtih: 37 stops on route, 34 unique stops, 663730 route length\nBus ZVmNhh9is90LP1YKtO: 24 stops on route, 23 unique stops, 400907 route length\nBus F7MHFi7g098LQ: 31 stops on route, 16 unique stops, 434873 route length\nBus jsh: 75 stops on route, 64 unique stops, 1.38824e+06 route length\nBus njbuySC7: 7 stops on route, 6 unique stops, 109986 route length\nBus 7x8ivGxqv3ajV2syTNo9NpTy: not found\nBus h4dpxtRSvC3Pous: 71 stops on route, 33 unique stops, 1.20537e+06 route length\nBus HH: not found\nBus Szr1eY3O4: 25 stops on route, 23 unique stops, 461887 route length\nBus HK46: 51 stops on route, 44 unique stops, 969089 route length\n")
    //);

    std::cerr << "TEST tsA_case1_input OK\n";
}

void TestOneRoute() {

    
    TransportCatalogue transport_catalogue;
    std::istringstream input{
    "3\n"
    "Stop A : 55.611087, 37.20829\n"
    "Stop B : 55.595884, 37.209755\n"
    "Bus Bus Name : A - B\n"
        };



    InputReader Input(input, transport_catalogue);
    std::istringstream output{
    "1\n"
    "Bus Bus Name\n"
    };

    std::ostringstream out_stream;

    StatReader Stat(output, out_stream, transport_catalogue);
    
    std::string str = out_stream.str();

    assert(str == "Bus Bus Name: 3 stops on route, 2 unique stops, 3386 route length\n");

    std::cerr << "TEST One Route OK\n";
}

void TestEmptyStopAndRoute() {

    TransportCatalogue transport_catalogue;
    std::istringstream input{
        "0\n"
    };

    InputReader Input(input, transport_catalogue);
    std::istringstream output{
    "1\n"
    "Bus Bus Name\n"
        };

    std::ostringstream out_stream;

    StatReader Stat(output, out_stream, transport_catalogue);

    std::string str = out_stream.str();

    assert(str == "Bus Bus Name: not found\n");

    std::cerr << "TEST Empty stops and route OK\n";
}

void TestTaskBData(){
    TransportCatalogue transport_catalogue;
    std::istringstream input{
        "13\n"
"Stop Tolstopaltsevo : 55.611087, 37.208290\n"
"Stop Marushkino : 55.595884, 37.209755\n"
"Bus 256 : Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\n"
"Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka\n"
"Stop Rasskazovka : 55.632761, 37.333324\n"
"Stop Biryulyovo Zapadnoye : 55.574371, 37.651700\n"
"Stop Biryusinka : 55.581065, 37.648390\n"
"Stop Universam : 55.587655, 37.645687\n"
"Stop Biryulyovo Tovarnaya : 55.592028, 37.653656\n"
"Stop Biryulyovo Passazhirskaya : 55.580999, 37.659164\n"
"Bus 828: Biryulyovo Zapadnoye > Universam > Rossoshanskaya ulitsa > Biryulyovo Zapadnoye\n"
"Stop Rossoshanskaya ulitsa : 55.595579, 37.605757\n"
"Stop Prazhskaya : 55.611678, 37.603831\n"
    };

    InputReader Input(input, transport_catalogue);
    std::istringstream output{
   "6\n"
        "Bus 256\n"
        "Bus 750\n"
        "Bus 751\n"
        "Stop Samara\n"
        "Stop Prazhskaya\n"
        "Stop Biryulyovo Zapadnoye\n"
    };

    std::ostringstream out_stream;

    StatReader Stat(output, out_stream, transport_catalogue);

    std::string str = out_stream.str();

    assert(str == "Bus 256: 6 stops on route, 5 unique stops, 4371.02 route length\nBus 750: 5 stops on route, 3 unique stops, 20939.5 route length\nBus 751: not found\nStop Samara: not found\nStop Prazhskaya: no buses\nStop Biryulyovo Zapadnoye: buses 256 828\n");

    std::cerr << "TEST Bus to stops and stop to buses OK\n";
}


void TestNearbyStopsLengthData() {
    TransportCatalogue transport_catalogue;
    std::istringstream input{
        "13\n"
"Stop Tolstopaltsevo : 55.611087, 37.20829, 3900m to Marushkino\n"
"Stop Marushkino : 55.595884, 37.209755, 9900m to Rasskazovka, 100m to Marushkino\n"
"Bus 256 : Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\n"
"Bus 750: Tolstopaltsevo - Marushkino - Marushkino - Rasskazovka\n"
"Stop Rasskazovka : 55.632761, 37.333324, 9500m to Marushkino\n"
"Stop Biryulyovo Zapadnoye : 55.574371, 37.6517, 7500m to Rossoshanskaya ulitsa, 1800m to Biryusinka, 2400m to Universam\n"
"Stop Biryusinka : 55.581065, 37.64839, 750m to Universam\n"
"Stop Universam : 55.587655, 37.645687, 5600m to Rossoshanskaya ulitsa, 900m to Biryulyovo Tovarnaya\n"
"Stop Biryulyovo Tovarnaya : 55.592028, 37.653656, 1300m to Biryulyovo Passazhirskaya\n"
"Stop Biryulyovo Passazhirskaya : 55.580999, 37.659164, 1200m to Biryulyovo Zapadnoye\n"
"Bus 828 : Biryulyovo Zapadnoye > Universam > Rossoshanskaya ulitsa > Biryulyovo Zapadnoye\n"
"Stop Rossoshanskaya ulitsa : 55.595579, 37.605757\n"
"Stop Prazhskaya : 55.611678, 37.603831\n"
    };

    InputReader Input(input, transport_catalogue);
    std::istringstream output{
   "6\n"
        "Bus 256\n"
        "Bus 750\n"
        "Bus 751\n"
        "Stop Samara\n"
        "Stop Prazhskaya\n"
        "Stop Biryulyovo Zapadnoye\n"
    };

    std::ostringstream out_stream;

    StatReader Stat(output, out_stream, transport_catalogue);



    std::string str = out_stream.str();

    assert(str == "Bus 256: 6 stops on route, 5 unique stops, 5950 route length, 1.36124 curvature\nBus 750: 7 stops on route, 3 unique stops, 27400 route length, 1.30853 curvature\nBus 751: not found\nStop Samara: not found\nStop Prazhskaya: no buses\nStop Biryulyovo Zapadnoye: buses 256 828\n");

    std::cerr << "TEST nearby stops length OK\n";
}