#include <iostream>
#include "vectors.h"

using namespace wb_vec;

int main() {
    std::cout << "Hello, World!" << std::endl;

    auto time1=-1_s;
    auto timePeriod1=TimeSpan(time1);
    auto time2=10.0_s;
    TimeSpan timePeriod2=time2;
    TimeSpan timePeriod3=333_s;
    TimeSpan timePeriod4=xD(33.5_s,on_time);
    auto timePeriod5=xD(33.5_s);

    auto tsi=TimeSI{1_s}+TimeSI{2_s};

    auto mass1=5.5_kg;
    auto mass1d=xD(mass1/3.);
    MassQuan mass1q= mass1;
    auto mass2=3_kg;
    auto mass2q=MassQuan{3_kg};
    MassQuan mass3q=33.5_kg;
    auto mass4q=xD(100_kg);
    MassQuan mass5q=xD(99.9_kg,on_mass);
    MassQuan mass6=mass5q/3.0;

    auto temp=280_K;
    auto tempQ=xD(temp);
    TempQuan tempr=xD(100_K,on_temperature);

    auto dist1=1_m;
    auto dist1X=Longitude(dist1);
    auto dist2=-100.5_m;
    auto dist2X=xD(dist2,is_along);
    auto dist3X=xD(5_m,is_along);

    auto vel1=10_m_s;
    auto vel1X=VelAlong{vel1};
    auto vel2=99.99_m_s;
    auto vel2X=xD(vel2,is_along);

    auto acc1=1_m_s2;
    auto acc1X=xD(acc1,is_along);

    PlanePosition point0{dist1X,Latitude{1_m}};
    auto point1=xD(dist2X,Latitude{7.7_m});
    auto test1=xD(Latitude{2_m},Altitude{3_m}); // The non-standard plane is accepted but has not predefined type.
    //auto test2=xD(Altitude{2_m},Altitude{3_m}); //fail on static_assert( !strings_equal(AXIS1::name(),AXIS2::name()) ); //Axes need to be different!

    PlaneVelocity velP0{vel2X,vel2};
    auto velP1=xD(VelAlong{10_m_s},VelAcross{1.59_m_s});

    PlaneAcceleration accP0{acc1X,AccAcross{2_m_s2}};
    //auto accP1=xD(AccAlong{2.33_m_s2},acc1);

    VolumeVelocity vel3D{VelAlong{5_m_s},VelAcross{1.22_m_s},VelUpward{0.33_m_s}};
    auto vol3D2=xD(vel1X,vel2,VelUpward{-0.55_m_s});
    auto vol3D3=xD(velP1,1_m_s);
    //auto vol3D3=xD(accP1,1_m_s); //type mismatch

    auto res0=point1-point0;
    auto res1=velP0+velP1;
    auto res2=vol3D2+vol3D3;
    auto res3=vol3D2-vol3D3;
    auto res4=Longitude{1_m}+Latitude{1_m};
    auto res5=Latitude{1_m}+Longitude{1_m}; //Should be reverse order allowed?
    auto res10=velP0+VelUpward(1_m_s);
    auto res11=res10-res3;
    //auto res4=velP1+Altitude{1_m}/TimeSpan{1_s};

    std::cout << "SUCCESS!" << std::endl;
    return 0;
}
