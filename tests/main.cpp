#include <iostream>
#include "vectors.h"

using namespace wb_vec;

int main() {
    std::cout << "Hello, World!" << std::endl;

    auto time1=1_s;
    auto timePeriod1=TimeSpan(time1);
    auto time2=10.0_s;
    TimeSpan timePeriod2=time2;
    TimeSpan timePeriod3=333_s;
    TimeSpan timePeriod4=xD(33.5_s,on_time);
    auto timePeriod5=xD(33.5_s);

    auto mass1=5.5_kg;
    MassQuan mass1q= mass1;
    auto mass2=3_kg;
    auto mass2q=MassQuan{3_kg};
    MassQuan mass3q=33.5_kg;
    auto mass4q=xD(100_kg);
    MassQuan mass5q=xD(99.9_kg,on_mass);

    auto temp=280_K;
    auto tempq=xD(temp);
    TempQuan tempr=xD(100_K,on_temperature);

    auto dist1=1_m;
    auto dist1X=Longitude(dist1);
    auto dist2=100.5_m;
    auto dist2X=xD(dist2,is_along);
    auto dist3X=xD(5_m,is_along);

    auto vel1=10_m_s;
    auto vel1X=VelAlong{vel1};
    auto vel2=99.99_m_s;
    auto vel2X=xD(vel2,is_along);

    auto acc1=1_m_s2;
    auto acc1X=xD(acc1,is_along);


    return 0;
}
