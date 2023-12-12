/// @file vectors.h
/// @details
///     Created by borkowsk on 10.12.22.
///     Names changed from `create` into `xD` 11.12.23
/// @date 2023-12-11 (last modification)
#ifndef WB_SIMULATIONS_VECTORS_H
#define WB_SIMULATIONS_VECTORS_H

#include <string_view>
constexpr bool strings_equal(char const * a, char const * b) {
    return std::string_view(a)==b;
}

namespace wb_vec {

    /// @brief Basic floating point type used for all physical values.
    typedef double float_base;

#define WB_VEC_CLASS_SPECIFIC    static inline constexpr

    // BASIC AND EXAMPLE COORDINATE SYSTEMS:
    //*/////////////////////////////////////

    /// @brief Any class describing any coordinate system should inherit from this template.
    /// \tparam DERIVED - derived class (see `flat_simulation` below)
    template<class DERIVED>
    struct coordinate_system { WB_VEC_CLASS_SPECIFIC const char* name() { return "????"; }
                               //WB_VEC_CLASS_SPECIFIC bool isCoordinateSystem() {return true;}
    };

    /// @brief Typical simulation, where gravity acts along the `Z` axis
    struct Flat_simulation: public coordinate_system<Flat_simulation> { WB_VEC_CLASS_SPECIFIC const char* name(){
                                                                                              return "flat-Earth"; }};
    /// @brief Geographical system, where gravity acts toward center of the earth, and 0 on Z axis is a "sea level"
    struct Geographical:    public coordinate_system<Geographical>    { WB_VEC_CLASS_SPECIFIC const char* name(){
                                                                                              return "geographical"; }};
    /// @brief A space system with the Earth as the center of the coordinate system and
    ///        the equatorial plane as the XY plane.
    struct Earth_centered:  public coordinate_system<Earth_centered>  { WB_VEC_CLASS_SPECIFIC const char* name(){
                                                                                              return "geo-centered"; }};
    /// @brief A space system A space system with the zero point at the center of mass of the Solar System and
    ///        the ecliptic plane as the X,Y plane
    struct Solar:           public coordinate_system<Solar>           { WB_VEC_CLASS_SPECIFIC const char* name(){
                                                                                              return "solar-system"; }};

    // AXIS FOR BASIC FLAT SYSTEM:
    //*///////////////////////////

    /// @brief Any type of axis should derive from axis template
    /// \tparam DERIVED -  derived class (see `time` below)
    /// \tparam SYSTEM - should be type derived from `coordinate_system` template.
    template<class DERIVED,class SYSTEM=Flat_simulation>
    struct axis                                          {  WB_VEC_CLASS_SPECIFIC const char* name(){ return "?"; }};

    /// @brief https://en.wikipedia.org/wiki/Time_in_physics
    /// @note The smallest time step considered theoretically observable is called the Planck time,
    ///       which is approximately 5.391×10−44 seconds
    struct Time:        public axis<Time>                { WB_VEC_CLASS_SPECIFIC const char* name(){ return "t"; }
                                                                                                } static on_time;
    /// @brief https://en.wikipedia.org/wiki/Mass
    struct Mass:        public axis<Mass>                { WB_VEC_CLASS_SPECIFIC const char* name(){ return "m"; }
                                                                                                } static on_mass;
    /// @brief https://en.wikipedia.org/wiki/Thermodynamic_temperature
    struct Temperature: public axis<Temperature>      { WB_VEC_CLASS_SPECIFIC const char* name(){ return "T"; }
                                                                                                } static on_temperature;
    /// @brief Latitude -> https://en.wikipedia.org/wiki/Length
    struct Along:       public axis<Along>               { WB_VEC_CLASS_SPECIFIC const char* name(){ return "X"; }
                                                                                                } static is_along;
    /// @brief Longitude -> https://en.wikipedia.org/wiki/Length
    struct Across:      public axis<Across>              { WB_VEC_CLASS_SPECIFIC const char* name(){ return "Y"; }
                                                                                                } static is_across;
    /// @brief Altitude -> https://en.wikipedia.org/wiki/Length
    struct Upward:     public axis<Upward>             { WB_VEC_CLASS_SPECIFIC const char* name(){ return "Z"; }
                                                                                                } static is_upward;
    // TEMPLATE FOR ANY PHYSICAL UNITS:
    //*////////////////////////////////

    /// @brief ...
    /// \tparam DERIVED
    template<class DERIVED>
    struct physical_unit { WB_VEC_CLASS_SPECIFIC const char* abbreviation() { return "[?]"; }};

    // PHYSICAL SI UNITS:
    //*//////////////////

    /// @brief Base SI unit of time
    struct SI_time_unit:public physical_unit<SI_time_unit> { WB_VEC_CLASS_SPECIFIC const char* abbreviation() { return "[s]"; }};
    /// @brief Base SI unit of mass
    struct SI_mass_unit:public physical_unit<SI_mass_unit> { WB_VEC_CLASS_SPECIFIC const char* abbreviation() { return "[kg]"; }};
    /// @brief Base SI unit of temperature
    struct SI_temperature_unit:public physical_unit<SI_temperature_unit> { WB_VEC_CLASS_SPECIFIC const char* abbreviation() { return "[K]"; }};

    /// @brief Base SI unit of length
    struct SI_length_unit:public physical_unit<SI_length_unit> { WB_VEC_CLASS_SPECIFIC const char* abbreviation() { return "[m]"; }};
    /// @brief A unit derived from the SI system, e.g. speed
    struct SI_velocity_unit:public physical_unit<SI_velocity_unit> { WB_VEC_CLASS_SPECIFIC const char* abbreviation() { return "[m/s]"; }};
    /// @brief A unit derived from the SI system, e.g. acceleration
    struct SI_acceleration_unit:public physical_unit<SI_acceleration_unit> { WB_VEC_CLASS_SPECIFIC const char* abbreviation() { return "[m/s^2]"; }};

    // TEMPLATE FOR PHYSICAL QUANTITIES MEASURED IN ANY UNITS:
    //*///////////////////////////////////////////////////////

    /// @brief ....
    /// \tparam DERIVED
    /// \tparam UNIT
    template<class DERIVED,class UNIT>
    struct Quantity {
        WB_VEC_CLASS_SPECIFIC  char* abbreviation() { return UNIT::abbreviation(); }
        float_base value;
        constexpr Quantity(const Quantity&) = default;
        constexpr Quantity(const float_base& iniVal):value{iniVal}{}
        constexpr Quantity(const long double& iniVal):value{(float_base)iniVal}{ /** @todo RANGE CHECK ASSERT? */}
        constexpr Quantity(const unsigned long long& iniVal):value{(float_base)iniVal}{/** @todo RANGE CHECK ASSERT? */}
        constexpr auto operator - () { return Quantity(-this->value);}
    };

#define WB_VEC_QUANTITY_BODY(THISCLASS) using Quantity::Quantity;constexpr auto operator - () { return THISCLASS(-this->value);}

    // PHYSICAL QUANTITIES MEASURED IN SI UNITS:
    //*/////////////////////////////////////////

    /// @brief It is a quantity of length measured in SI units
    struct DistSI:     public Quantity<DistSI,SI_length_unit>       {WB_VEC_QUANTITY_BODY(DistSI)};
    /// @brief It is a quantity of time measured in SI units
    struct TimeSI:     public Quantity<TimeSI,SI_time_unit>         {WB_VEC_QUANTITY_BODY(TimeSI)};
    /// @brief It is a quantity of mass measured in SI units
    struct MassSI:     public Quantity<MassSI,SI_mass_unit>         {WB_VEC_QUANTITY_BODY(MassSI)};
    /// @brief It is a quantity of temperature measured in SI units
    struct TempSI:     public Quantity<TempSI,SI_temperature_unit>  {WB_VEC_QUANTITY_BODY(TempSI)};
    /// @brief It is a quantity of speed measured in SI units
    struct VelocitySI: public Quantity<VelocitySI,SI_velocity_unit> {WB_VEC_QUANTITY_BODY(VelocitySI)};
    /// @brief It is a quantity of acceleration measured in SI units
    struct AccelerationSI: public Quantity<AccelerationSI,SI_acceleration_unit> {WB_VEC_QUANTITY_BODY(AccelerationSI)};

    WB_VEC_CLASS_SPECIFIC auto operator "" _m    (long double val) { return DistSI{val}; }
    WB_VEC_CLASS_SPECIFIC auto operator "" _s    (long double val) { return TimeSI{val}; }
    WB_VEC_CLASS_SPECIFIC auto operator "" _kg   (long double val) { return MassSI{val}; }
    WB_VEC_CLASS_SPECIFIC auto operator "" _K    (long double val) { return TempSI{val}; }
    WB_VEC_CLASS_SPECIFIC auto operator "" _m_s  (long double val) { return VelocitySI{val}; }
    WB_VEC_CLASS_SPECIFIC auto operator "" _m_s2 (long double val) { return AccelerationSI{val}; }

    WB_VEC_CLASS_SPECIFIC auto operator "" _m    (unsigned long long val) { return DistSI{val}; }
    WB_VEC_CLASS_SPECIFIC auto operator "" _s    (unsigned long long val) { return TimeSI{val}; }
    WB_VEC_CLASS_SPECIFIC auto operator "" _kg   (unsigned long long val) { return MassSI{val}; }
    WB_VEC_CLASS_SPECIFIC auto operator "" _K    (unsigned long long val) { return TempSI{val}; }
    WB_VEC_CLASS_SPECIFIC auto operator "" _m_s  (unsigned long long val) { return VelocitySI{val}; }
    WB_VEC_CLASS_SPECIFIC auto operator "" _m_s2 (unsigned long long val) { return AccelerationSI{val}; }

    // PHYSICAL SCALARS TEMPLATE:
    //*//////////////////////////

    /// ....
    /// \tparam AXIS
    /// \tparam QUANTITY
    template<class AXIS,class QUANTITY>
    struct Scalar {
        WB_VEC_CLASS_SPECIFIC  char* unit_abr() { return QUANTITY::abbreviation(); }
        WB_VEC_CLASS_SPECIFIC  char* axis_abr() { return AXIS::name(); }
        QUANTITY val;
        constexpr Scalar(const Scalar&) = default;
        constexpr Scalar(const QUANTITY& initVal):val(initVal){}
    };

    //template<class AXIS,class QUANTITY>
    //std::enable_if_t<std::is_base_of_v<axis<AXIS>,AXIS>,bool>
    //inline auto xD(const QUANTITY& initVal,const AXIS& /*axis*/) {
    //    static_assert(AXIS::name() != nullptr);
    //  return Scalar<AXIS,QUANTITY>{initVal};
    //}

#define WB_VEC_SCALAR_BODY(THISCLASS,AXIS,UNIT)     using Scalar::Scalar; \
                                                    constexpr THISCLASS(const Scalar<AXIS,UNIT>& sc):Scalar{sc}{}

    // PHYSICAL SCALARS FOR FLAT COORDINATE SYSTEM MEASURED IN SI UNITS:
    //*/////////////////////////////////////////////////////////////////

    struct TimeSpan:public Scalar<Time,TimeSI> {WB_VEC_SCALAR_BODY(TimeSpan,Time,TimeSI)};
    constexpr inline TimeSpan xD(const TimeSI& t) { return TimeSpan{t}; }
    constexpr inline TimeSpan xD(const TimeSI& t,const Time&) { return TimeSpan{t}; }

    struct MassQuan:public Scalar<Mass,MassSI> {WB_VEC_SCALAR_BODY(MassQuan,Mass,MassSI)};
    constexpr inline MassQuan xD(const MassSI& m) { return MassQuan{m}; }
    constexpr inline MassQuan xD(const MassSI& m,const Mass&) { return MassQuan{m}; }

    struct TempQuan:public Scalar<Temperature,TempSI> {WB_VEC_SCALAR_BODY(TempQuan,Temperature,TempSI)};
    constexpr inline TempQuan xD(const TempSI& tt) { return TempQuan{tt}; }
    constexpr inline TempQuan xD(const TempSI& tt,const Temperature&) { return TempQuan{tt}; }

    struct Longitude:public Scalar<Along,DistSI> {WB_VEC_SCALAR_BODY(Longitude,Along,DistSI)};
    constexpr inline Longitude xD(const DistSI& d,const Along&) { return Longitude{d}; }

    struct Latitude:public Scalar<Across,DistSI> {WB_VEC_SCALAR_BODY(Latitude,Across,DistSI)};
    constexpr inline Latitude xD(const DistSI& d,const Across&) { return Latitude{d}; }

    struct Altitude:public Scalar<Upward,DistSI> {WB_VEC_SCALAR_BODY(Altitude,Upward,DistSI)};
    constexpr inline Altitude xD(const DistSI& d,const Upward&) { return Altitude{d}; }

    struct VelAlong:public Scalar<Along,VelocitySI> {WB_VEC_SCALAR_BODY(VelAlong,Along,VelocitySI)};
    constexpr inline VelAlong xD(const VelocitySI& v,const Along&) { return VelAlong{v}; }

    struct VelAcross:public Scalar<Across,VelocitySI> {WB_VEC_SCALAR_BODY(VelAcross,Across,VelocitySI)};
    constexpr inline VelAcross xD(const VelocitySI& v,const Across&) { return VelAcross{v}; }

    struct VelUpward:public Scalar<Upward,VelocitySI> {WB_VEC_SCALAR_BODY(VelUpward,Upward,VelocitySI)};
    constexpr inline VelUpward xD(const VelocitySI& v,const Upward&) { return VelUpward{v}; }

    struct AccAlong:public Scalar<Along,AccelerationSI> {WB_VEC_SCALAR_BODY(AccAlong,Along,AccelerationSI)};
    constexpr inline AccAlong xD(const AccelerationSI& a,const Along&) { return AccAlong{a}; }

    struct AccAcross:public Scalar<Across,AccelerationSI> {WB_VEC_SCALAR_BODY(AccAcross,Across,AccelerationSI)};
    constexpr inline AccAcross xD(const AccelerationSI& a,const Across&) { return AccAcross{a}; }

    struct AccUpward:public Scalar<Upward,AccelerationSI> {WB_VEC_SCALAR_BODY(AccUpward,Upward,AccelerationSI)};
    constexpr inline AccUpward xD(const AccelerationSI& a,const Upward&) { return AccUpward{a}; }

    ///https://www.youtube.com/watch?v=-PXAOZwvv04 - taki to kraj...

    // PHYSICAL VECTORS 2D TEMPLATE:
    //*/////////////////////////////

    template<class AXIS1,class AXIS2,class QUANTITY>
    struct Vec2D {
        WB_VEC_CLASS_SPECIFIC  char* unit_abr() { return QUANTITY::abbreviation(); }
        WB_VEC_CLASS_SPECIFIC  char* axisX_abr() { return AXIS1::name(); }
        WB_VEC_CLASS_SPECIFIC  char* axisY_abr() { return AXIS2::name(); }
        Scalar<AXIS1,QUANTITY> x;
        Scalar<AXIS2,QUANTITY> y;
        constexpr Vec2D(const Vec2D&) = default;
        constexpr Vec2D(const Scalar<AXIS1,QUANTITY>& iniX,const Scalar<AXIS2,QUANTITY>& iniY):x(iniX),y(iniY){}
    };

    template<class AXIS1,class AXIS2,class QUANTITY>
    inline auto xD(const Scalar<AXIS1,QUANTITY>& iniX,const Scalar<AXIS2,QUANTITY>& iniY){
        static_assert( AXIS1::name() != nullptr );
        static_assert( AXIS2::name() != nullptr );
        static_assert( !strings_equal(AXIS1::name(),AXIS2::name()) ); //Axes need to be different!

        return Vec2D<AXIS1,AXIS2,QUANTITY>(iniX,iniY);
    }

#define WB_VEC_VEC2D_BODY(THISCLASS,AXIS1,AXIS2,UNIT)     using Vec2D::Vec2D; \
                                                          constexpr THISCLASS(const Vec2D<AXIS1,AXIS2,UNIT>& sc):Vec2D{sc}{}

    // PHYSICAL VECTORS 2D FOR FLAT COORDINATE SYSTEM MEASURED IN SI UNITS:
    //*////////////////////////////////////////////////////////////////////

    struct PlanePosition:public Vec2D<Along,Across,DistSI> {WB_VEC_VEC2D_BODY(PlanePosition,Along,Across,DistSI)};
    constexpr inline PlanePosition xD(const Scalar<Along,DistSI> iniX,const Scalar<Across,DistSI> iniY) { return {iniX,iniY}; }

    struct PlaneVelocity:public Vec2D<Along,Across,VelocitySI> {WB_VEC_VEC2D_BODY(PlaneVelocity,Along,Across,VelocitySI)};
    constexpr inline PlaneVelocity xD(const Scalar<Along,VelocitySI> iniX,const Scalar<Across,VelocitySI> iniY) { return {iniX,iniY}; }

    struct PlaneAcceleration:public Vec2D<Along,Across,AccelerationSI> {WB_VEC_VEC2D_BODY(PlaneAcceleration,Along,Across,AccelerationSI)};
    constexpr inline PlaneAcceleration xD(const Scalar<Along,AccelerationSI> iniX,const Scalar<Across,AccelerationSI> iniY) { return {iniX,iniY}; }

    // PHYSICAL VECTORS 3D TEMPLATE:
    //*/////////////////////////////

    template<class AXIS1,class AXIS2,class AXIS3,class QUANTITY>
    struct Vec3D {
        WB_VEC_CLASS_SPECIFIC  char* unit_abr() { return QUANTITY::abbreviation(); }
        WB_VEC_CLASS_SPECIFIC  char* axisX_abr() { return AXIS1::name(); }
        WB_VEC_CLASS_SPECIFIC  char* axisY_abr() { return AXIS2::name(); }
        WB_VEC_CLASS_SPECIFIC  char* axisZ_abr() { return AXIS3::name(); }
        Scalar<AXIS1,QUANTITY> x;
        Scalar<AXIS2,QUANTITY> y;
        Scalar<AXIS3,QUANTITY> z;
        constexpr Vec3D(const Vec3D&) = default;
        constexpr Vec3D(const Scalar<AXIS1,QUANTITY>& iniX,
                        const Scalar<AXIS2,QUANTITY>& iniY,
                        const Scalar<AXIS3,QUANTITY>& iniZ):x(iniX),y(iniY),z(iniZ){}
    };

    template<class AXIS1,class AXIS2,class AXIS3,class QUANTITY>
    inline auto xD(const Scalar<AXIS1,QUANTITY>& iniX,
                   const Scalar<AXIS2,QUANTITY>& iniY,
                   const Scalar<AXIS3,QUANTITY>& iniZ){
        static_assert( AXIS1::name() != nullptr );
        static_assert( AXIS2::name() != nullptr );
        static_assert( AXIS3::name() != nullptr );
        static_assert( !strings_equal(AXIS1::name(),AXIS2::name()) ); //Axes need to be different!
        static_assert( !strings_equal(AXIS2::name(),AXIS3::name()) ); //Axes need to be different!
        static_assert( !strings_equal(AXIS3::name(),AXIS1::name()) ); //Axes need to be different!

        return Vec3D<AXIS1,AXIS2,AXIS3,QUANTITY>(iniX,iniY,iniZ);
    }

#define WB_VEC_VEC3D_BODY(THISCLASS,AXIS1,AXIS2,AXIS3,UNIT)     using Vec3D::Vec3D; \
                                                          constexpr THISCLASS(const Vec3D<AXIS1,AXIS2,AXIS3,UNIT>& sc):Vec3D{sc}{}

    // PHYSICAL VECTORS 2D FOR FLAT COORDINATE SYSTEM MEASURED IN SI UNITS:
    //*////////////////////////////////////////////////////////////////////

    struct VolumePosition: public Vec3D<Along,Across,Upward,DistSI> {WB_VEC_VEC3D_BODY(VolumePosition, Along, Across, Upward, DistSI)};
    constexpr inline VolumePosition xD(const Scalar<Along,DistSI> iniX,
                                       const Scalar<Across,DistSI> iniY,
                                       const Scalar<Upward,DistSI> iniZ) { return {iniX,iniY,iniZ}; }

    struct VolumeVelocity: public Vec3D<Along,Across,Upward,VelocitySI> {WB_VEC_VEC3D_BODY(VolumeVelocity, Along, Across, Upward, VelocitySI)};
    constexpr inline VolumeVelocity xD(const Scalar<Along,VelocitySI> iniX,
                                       const Scalar<Across,VelocitySI> iniY,
                                       const Scalar<Upward,VelocitySI> iniZ) { return {iniX,iniY,iniZ}; }

    struct VolumeAcceleration: public Vec3D<Along,Across,Upward,AccelerationSI> {WB_VEC_VEC3D_BODY(VolumeAcceleration, Along, Across, Upward, AccelerationSI)};
    constexpr inline VolumeAcceleration xD(const Scalar<Along,AccelerationSI> iniX,
                                           const Scalar<Across,AccelerationSI> iniY,
                                           const Scalar<Upward,AccelerationSI> iniZ) { return {iniX,iniY,iniZ}; }
}


#endif //WB_SIMULATIONS_VECTORS_H
