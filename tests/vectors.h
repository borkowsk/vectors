/// @file vectors.h
/// @details
///     Created by borkowsk on 10.12.22.
///     Names changed from `create` into `xD` 11.12.23
/// @date 2023-12-11 (last modification)
#ifndef WB_SIMULATIONS_VECTORS_H
#define WB_SIMULATIONS_VECTORS_H

#include <string_view>

/// @brief ....
constexpr bool strings_equal(char const * a, char const * b) {
    return std::string_view(a)==b;
}

namespace wb_vec {

    /// @brief Basic floating point type used for all physical values.
    typedef double float_base;

/// @brief ....
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
        constexpr Quantity(const long double& iniVal):value{(float_base)iniVal}       {/** @todo RANGE CHECK ASSERT? */}
        constexpr Quantity(const unsigned long long& iniVal):value{(float_base)iniVal}{/** @todo RANGE CHECK ASSERT? */}
        constexpr Quantity operator + () { return *this;}
        constexpr Quantity operator - () const { return Quantity(-this->value);}
        constexpr Quantity operator + (const Quantity& a) const { return Quantity{value + a.value};}
        constexpr Quantity operator - (const Quantity& a) const { return Quantity{value - a.value};}
        constexpr Quantity operator * (const double& m) const { return Quantity{value * m };}
        constexpr Quantity operator / (const double& d) const { return Quantity{value / d };}
    };

/// @brief ....
#define WB_VEC_QUANTITY_BODY(THISCLASS,UNIT)                                                 using  Quantity::Quantity; \
                                                                                             using  Quantity::operator+;\
                                                                                             using  Quantity::operator-;\
                                                                                             using  Quantity::operator*;\
                                                                                             using  Quantity::operator/;\
                                                         constexpr auto operator - () { return THISCLASS(-this->value);}\
                                                         constexpr THISCLASS(const Quantity<THISCLASS,UNIT> & sc):      \
                                                                                                          Quantity{sc}{}\
                                                         constexpr friend inline THISCLASS xD(                          \
                                                                            const Quantity<THISCLASS,UNIT> & sc){       \
                                                                            return THISCLASS(sc.value);                 \
                                                                            }                                           \
                                                         constexpr friend inline THISCLASS xD(                          \
                                                                            const Quantity<THISCLASS,UNIT> & sc1,       \
                                                                            const Quantity<THISCLASS,UNIT> & sc2 ){     \
                                                                            return THISCLASS(sc1.value+sc2.value);      \
                                                                            }                                           \

    // PHYSICAL QUANTITIES MEASURED IN SI UNITS:
    //*/////////////////////////////////////////

    /// @brief It is a quantity of time measured in SI units
    struct TimeSI:     public Quantity<TimeSI,SI_time_unit>         {WB_VEC_QUANTITY_BODY(TimeSI,SI_time_unit)};
    /// @brief It is a quantity of mass measured in SI units
    struct MassSI:     public Quantity<MassSI,SI_mass_unit>         {WB_VEC_QUANTITY_BODY(MassSI,SI_mass_unit)};
    /// @brief It is a quantity of temperature measured in SI units
    struct TempSI:     public Quantity<TempSI,SI_temperature_unit>  {WB_VEC_QUANTITY_BODY(TempSI,SI_temperature_unit)};
    /// @brief It is a quantity of length measured in SI units
    struct DistSI:     public Quantity<DistSI,SI_length_unit>       {WB_VEC_QUANTITY_BODY(DistSI,SI_length_unit)};
    /// @brief It is a quantity of speed measured in SI units
    struct VelocitySI: public Quantity<VelocitySI,SI_velocity_unit> {WB_VEC_QUANTITY_BODY(VelocitySI,SI_velocity_unit)};
    /// @brief It is a quantity of acceleration measured in SI units
    struct AccelerationSI: public Quantity<AccelerationSI,SI_acceleration_unit> {WB_VEC_QUANTITY_BODY(AccelerationSI,SI_acceleration_unit)};

    /// @brief ....
    WB_VEC_CLASS_SPECIFIC auto operator "" _m    (long double val) { return DistSI{val}; }
    /// @brief ....
    WB_VEC_CLASS_SPECIFIC auto operator "" _s    (long double val) { return TimeSI{val}; }
    /// @brief ....
    WB_VEC_CLASS_SPECIFIC auto operator "" _kg   (long double val) { return MassSI{val}; }
    /// @brief ....
    WB_VEC_CLASS_SPECIFIC auto operator "" _K    (long double val) { return TempSI{val}; }
    /// @brief ....
    WB_VEC_CLASS_SPECIFIC auto operator "" _m_s  (long double val) { return VelocitySI{val}; }
    /// @brief ....
    WB_VEC_CLASS_SPECIFIC auto operator "" _m_s2 (long double val) { return AccelerationSI{val}; }
    /// @brief ....
    WB_VEC_CLASS_SPECIFIC auto operator "" _m    (unsigned long long val) { return DistSI{val}; }
    /// @brief ....
    WB_VEC_CLASS_SPECIFIC auto operator "" _s    (unsigned long long val) { return TimeSI{val}; }
    /// @brief ....
    WB_VEC_CLASS_SPECIFIC auto operator "" _kg   (unsigned long long val) { return MassSI{val}; }
    /// @brief ....
    WB_VEC_CLASS_SPECIFIC auto operator "" _K    (unsigned long long val) { return TempSI{val}; }
    /// @brief ....
    WB_VEC_CLASS_SPECIFIC auto operator "" _m_s  (unsigned long long val) { return VelocitySI{val}; }
    /// @brief ....
    WB_VEC_CLASS_SPECIFIC auto operator "" _m_s2 (unsigned long long val) { return AccelerationSI{val}; }

    // PHYSICAL SCALARS TEMPLATE:
    //*//////////////////////////

    /// @brief ....
    /// \tparam AXIS
    /// \tparam QUANTITY
    template<class AXIS,class QUANTITY>
    struct Scalar {
        WB_VEC_CLASS_SPECIFIC  char* unit_abr() { return QUANTITY::abbreviation(); }
        WB_VEC_CLASS_SPECIFIC  char* axis_abr() { return AXIS::name(); }
        QUANTITY val;
        constexpr Scalar(const Scalar&) = default;
        constexpr Scalar(const QUANTITY& initVal):val(initVal){}
        constexpr Scalar operator + () { return *this;}
        constexpr Scalar operator - () const { return Scalar(-this->val);}
        constexpr Scalar operator + (const Scalar& a) const { return Scalar{val.value + a.val.value};}
        constexpr Scalar operator * (const double& m) const { return Scalar{val * m };}
        constexpr Scalar operator / (const double& d) const { return Scalar{val / d };}
    };

    //template<class AXIS,class QUANTITY>
    //std::enable_if_t<std::is_base_of_v<axis<AXIS>,AXIS>,bool>
    //constexpr inline auto xD(const QUANTITY& initVal,const AXIS& /*axis*/) {
    //    static_assert(AXIS::name() != nullptr);
    //  return Scalar<AXIS,QUANTITY>{initVal};
    //}

#define WB_VEC_SCALAR_BODY(THISCLASS,AXIS,UNIT)                               using Scalar<AXIS,UNIT>::Scalar;          \
                                                                              using Scalar<AXIS,UNIT>::operator+;       \
                                                                              using Scalar<AXIS,UNIT>::operator-;       \
                                                                              using Scalar<AXIS,UNIT>::operator*;       \
                                                                              using Scalar<AXIS,UNIT>::operator/;       \
                                                    constexpr THISCLASS(const Scalar<AXIS,UNIT>& sc):Scalar{sc}{}       \
                                                    constexpr friend inline THISCLASS xD(                               \
                                                                            const Scalar<AXIS,UNIT> & sc) {             \
                                                                            return THISCLASS(sc.val);                   \
                                                                            }                                           \
                                                    constexpr friend inline THISCLASS xD(                               \
                                                                            const Scalar<AXIS,UNIT> & sc1,              \
                                                                            const Scalar<AXIS,UNIT> & sc2 ){            \
                                                                            return THISCLASS(sc1.val+sc2.val);          \
                                                                            }                                           \

    // PHYSICAL SCALARS FOR FLAT COORDINATE SYSTEM MEASURED IN SI UNITS:
    //*/////////////////////////////////////////////////////////////////

    /**
     * @brief ....
     */
    struct TimeSpan:public Scalar<Time,TimeSI> {WB_VEC_SCALAR_BODY(TimeSpan,Time,TimeSI)};
    /// @brief ....
    constexpr inline TimeSpan xD(const TimeSI& t) { return TimeSpan{t}; }
    /// @brief ....
    constexpr inline TimeSpan xD(const TimeSI& t,const Time&) { return TimeSpan{t}; }

    /**
     * @brief ....
     */
    struct MassQuan:public Scalar<Mass,MassSI> {WB_VEC_SCALAR_BODY(MassQuan,Mass,MassSI)};
    /// @brief ....
    constexpr inline MassQuan xD(const MassSI& m) { return MassQuan{m}; }
    /// @brief ....
    constexpr inline MassQuan xD(const MassSI& m,const Mass&) { return MassQuan{m}; }

    /**
     * @brief ....
     */
    struct TempQuan:public Scalar<Temperature,TempSI> {WB_VEC_SCALAR_BODY(TempQuan,Temperature,TempSI)};
    /// @brief ....
    constexpr inline TempQuan xD(const TempSI& tt) { return TempQuan{tt}; }
    /// @brief ....
    constexpr inline TempQuan xD(const TempSI& tt,const Temperature&) { return TempQuan{tt}; }

    /**
     * @brief ....
     */
    struct Longitude:public Scalar<Along,DistSI> {WB_VEC_SCALAR_BODY(Longitude,Along,DistSI)};
    /// @brief ....
    constexpr inline Longitude xD(const DistSI& d,const Along&) { return Longitude{d}; }

    /**
     * @brief ....
     */
    struct Latitude:public Scalar<Across,DistSI> {WB_VEC_SCALAR_BODY(Latitude,Across,DistSI)};
    /// @brief ....
    constexpr inline Latitude xD(const DistSI& d,const Across&) { return Latitude{d}; }

    /**
     * @brief ....
     */
    struct Altitude:public Scalar<Upward,DistSI> {WB_VEC_SCALAR_BODY(Altitude,Upward,DistSI)};
    /// @brief ....
    constexpr inline Altitude xD(const DistSI& d,const Upward&) { return Altitude{d}; }

    /**
     * @brief ....
     */
    struct VelAlong:public Scalar<Along,VelocitySI> {WB_VEC_SCALAR_BODY(VelAlong,Along,VelocitySI)};
    /// @brief ....
    constexpr inline VelAlong xD(const VelocitySI& v,const Along&) { return VelAlong{v}; }

    /**
     * @brief ....
     */
    struct VelAcross:public Scalar<Across,VelocitySI> {WB_VEC_SCALAR_BODY(VelAcross,Across,VelocitySI)};
    /// @brief ....
    constexpr inline VelAcross xD(const VelocitySI& v,const Across&) { return VelAcross{v}; }

    /**
     * @brief ....
     */
    struct VelUpward:public Scalar<Upward,VelocitySI> {WB_VEC_SCALAR_BODY(VelUpward,Upward,VelocitySI)};
    /// @brief ....
    constexpr inline VelUpward xD(const VelocitySI& v,const Upward&) { return VelUpward{v}; }

    /**
     * @brief ....
     */
    struct AccAlong:public Scalar<Along,AccelerationSI> {WB_VEC_SCALAR_BODY(AccAlong,Along,AccelerationSI)};
    /// @brief ....
    constexpr inline AccAlong xD(const AccelerationSI& a,const Along&) { return AccAlong{a}; }

    /**
     * @brief ....
     */
    struct AccAcross:public Scalar<Across,AccelerationSI> {WB_VEC_SCALAR_BODY(AccAcross,Across,AccelerationSI)};
    /// @brief ....
    constexpr inline AccAcross xD(const AccelerationSI& a,const Across&) { return AccAcross{a}; }

    /**
     * @brief ....
     */
    struct AccUpward:public Scalar<Upward,AccelerationSI> {WB_VEC_SCALAR_BODY(AccUpward,Upward,AccelerationSI)};
    /// @brief ....
    constexpr inline AccUpward xD(const AccelerationSI& a,const Upward&) { return AccUpward{a}; }

    ///https://www.youtube.com/watch?v=-PXAOZwvv04 - taki to kraj...

    // PHYSICAL VECTORS 2D TEMPLATE:
    //*/////////////////////////////

    /**
     * @brief ....
     * @tparam AXIS1
     * @tparam AXIS2
     * @tparam QUANTITY
     */
    template<class AXIS1,class AXIS2,class QUANTITY>
    struct Vec2D {
        WB_VEC_CLASS_SPECIFIC  char* unit_abr() { return QUANTITY::abbreviation(); }
        WB_VEC_CLASS_SPECIFIC  char* axisX_abr() { return AXIS1::name(); }
        WB_VEC_CLASS_SPECIFIC  char* axisY_abr() { return AXIS2::name(); }
        Scalar<AXIS1,QUANTITY> x;
        Scalar<AXIS2,QUANTITY> y;
        constexpr Vec2D(const Vec2D&) = default;
        constexpr Vec2D(const Scalar<AXIS1,QUANTITY>& iniX,const Scalar<AXIS2,QUANTITY>& iniY):x(iniX),y(iniY){}
        constexpr Vec2D operator + () { return *this;}
        constexpr Vec2D operator - () const { return Vec2D(-x,-y);}
    };

    /// @brief ....
    /// \tparam AXIS1
    /// \tparam AXIS2
    /// \tparam QUANTITY
    /// \param iniX
    /// \param iniY
    /// \return auto Vec2D<>
    template<class AXIS1,class AXIS2,class QUANTITY>
    constexpr inline auto xD(const Scalar<AXIS1,QUANTITY>& iniX,const Scalar<AXIS2,QUANTITY>& iniY){
        static_assert( AXIS1::name() != nullptr );
        static_assert( AXIS2::name() != nullptr );
        static_assert( !strings_equal(AXIS1::name(),AXIS2::name()) ); //Axes need to be different!

        return Vec2D<AXIS1,AXIS2,QUANTITY>(iniX,iniY);
    }

/// @brief ....
#define WB_VEC_VEC2D_BODY(THISCLASS,AXIS1,AXIS2,UNIT)                         using Vec2D<AXIS1,AXIS2,UNIT>::Vec2D;     \
                                                                              using Vec2D<AXIS1,AXIS2,UNIT>::operator+; \
                                                                              using Vec2D<AXIS1,AXIS2,UNIT>::operator-; \
                                                          constexpr THISCLASS(const Vec2D<AXIS1,AXIS2,UNIT>& sc):Vec2D{sc}{} \
                                                          constexpr friend inline THISCLASS xD(                         \
                                                                            const Vec2D<AXIS1,AXIS2,UNIT>& sc) {        \
                                                                            return THISCLASS{sc.x,sc.y};                \
                                                                            }                                           \
                                                          constexpr friend inline THISCLASS xD(                         \
                                                                            const Vec2D<AXIS1,AXIS2,UNIT>& sc1,         \
                                                                            const Vec2D<AXIS1,AXIS2,UNIT>& sc2 ) {      \
                                                                            return THISCLASS{sc1.x+sc2.x,sc1.y+sc2.y};  \
                                                                            }                                           \

    // PHYSICAL VECTORS 2D FOR FLAT COORDINATE SYSTEM MEASURED IN SI UNITS:
    //*////////////////////////////////////////////////////////////////////

    /**
     * @brief ....
     */
    struct PlanePosition:public Vec2D<Along,Across,DistSI> {WB_VEC_VEC2D_BODY(PlanePosition,Along,Across,DistSI)};
    /// @brief ....
    constexpr inline PlanePosition xD(const Scalar<Along,DistSI>& iniX,const Scalar<Across,DistSI>& iniY) { return {iniX,iniY}; }
    /// @brief Should be reverse order allowed? ;-)
    //constexpr inline PlanePosition xD(const Scalar<Across,DistSI>& iniY,const Scalar<Along,DistSI>& iniX) { return {iniX,iniY}; }

    /**
     * @brief ....
     */
    struct PlaneVelocity:public Vec2D<Along,Across,VelocitySI> {WB_VEC_VEC2D_BODY(PlaneVelocity,Along,Across,VelocitySI)};
    /// @brief ....
    constexpr inline PlaneVelocity xD(const Scalar<Along,VelocitySI>& iniX,const Scalar<Across,VelocitySI>& iniY) { return {iniX,iniY}; }

    /**
     * @brief ....
     */
    struct PlaneAcceleration:public Vec2D<Along,Across,AccelerationSI> {WB_VEC_VEC2D_BODY(PlaneAcceleration,Along,Across,AccelerationSI)};
    /// @brief ....
    constexpr inline PlaneAcceleration xD(const Scalar<Along,AccelerationSI>& iniX,const Scalar<Across,AccelerationSI>& iniY) { return {iniX,iniY}; }

    // PHYSICAL VECTORS 3D TEMPLATE:
    //*/////////////////////////////
    /**
     * @brief ....
     * @tparam AXIS1
     * @tparam AXIS2
     * @tparam AXIS3
     * @tparam QUANTITY
     */
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
        constexpr Vec3D operator + () { return *this;}
        constexpr Vec3D operator - () const { return Vec3D(-x,-y,-z);}
    };

    /// @brief .....
    /// \tparam AXIS1
    /// \tparam AXIS2
    /// \tparam AXIS3
    /// \tparam QUANTITY
    /// \param iniX
    /// \param iniY
    /// \param iniZ
    /// \return auto Vec3D<>
    template<class AXIS1,class AXIS2,class AXIS3,class QUANTITY>
    constexpr inline auto xD(const Scalar<AXIS1,QUANTITY>& iniX,
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

/// @brief ....
#define WB_VEC_VEC3D_BODY(THISCLASS,AXIS1,AXIS2,AXIS3,UNIT)              using Vec3D<AXIS1,AXIS2,AXIS3,UNIT>::Vec3D;\
                                                                         using Vec3D<AXIS1,AXIS2,AXIS3,UNIT>::operator+;\
                                                                         using Vec3D<AXIS1,AXIS2,AXIS3,UNIT>::operator-;\
                                                constexpr THISCLASS(const Vec3D<AXIS1,AXIS2,AXIS3,UNIT>& sc):Vec3D{sc}{}\
                                                constexpr friend inline THISCLASS xD(                                   \
                                                                            const Vec3D<AXIS1,AXIS2,AXIS3,UNIT>& sc)  { \
                                                                            return{sc.x,sc.y,sc.z};                     \
                                                                        }                                               \
                                                constexpr friend inline THISCLASS xD(                                   \
                                                                            const Vec3D<AXIS1,AXIS2,AXIS3,UNIT>& sc1,   \
                                                                            const Vec3D<AXIS1,AXIS2,AXIS3,UNIT>& sc2)  {\
                                                                            return{sc1.x+sc2.x,sc1.y+sc2.y,sc1.z+sc2.z};\
                                                                        }                                               \

    // PHYSICAL VECTORS 2D FOR FLAT COORDINATE SYSTEM MEASURED IN SI UNITS:
    //*////////////////////////////////////////////////////////////////////

    /**
     * @brief ....
     */
    struct VolumePosition: public Vec3D<Along,Across,Upward,DistSI> {WB_VEC_VEC3D_BODY(VolumePosition, Along, Across, Upward, DistSI)};
    /// @brief ....
    constexpr inline VolumePosition xD(const Scalar<Along,DistSI>& iniX,
                                       const Scalar<Across,DistSI>& iniY,
                                       const Scalar<Upward,DistSI>& iniZ) { return {iniX,iniY,iniZ}; }
    /// @brief ....
    constexpr inline VolumePosition xD(const Vec2D<Along,Across,DistSI>& iniPV,
                                       const Scalar<Upward,DistSI>& iniZ) { return {iniPV.x,iniPV.y,iniZ}; }

    /// @brief ....
    //constexpr inline VolumePosition xD(const PlanePosition& iniPV,
    //                                   const Scalar<Upward,DistSI>& iniZ) { return {iniPV.x,iniPV.y,iniZ}; }

    /**
     * @brief ....
     */
    struct VolumeVelocity: public Vec3D<Along,Across,Upward,VelocitySI> {WB_VEC_VEC3D_BODY(VolumeVelocity, Along, Across, Upward, VelocitySI)};
    /// @brief ....
    constexpr inline VolumeVelocity xD(const Scalar<Along,VelocitySI>& iniX,
                                       const Scalar<Across,VelocitySI>& iniY,
                                       const Scalar<Upward,VelocitySI>& iniZ) { return {iniX,iniY,iniZ}; }
    /// @brief ....
    constexpr inline VolumeVelocity xD(const Vec2D<Along,Across,VelocitySI>& iniPV,
                                       const Scalar<Upward,VelocitySI>& iniZ) { return {iniPV.x,iniPV.y,iniZ}; }

    /**
     * @brief ....
     */
    struct VolumeAcceleration: public Vec3D<Along,Across,Upward,AccelerationSI> {WB_VEC_VEC3D_BODY(VolumeAcceleration, Along, Across, Upward, AccelerationSI)};
    /// @brief ....
    constexpr inline VolumeAcceleration xD(const Scalar<Along,AccelerationSI>& iniX,
                                           const Scalar<Across,AccelerationSI>& iniY,
                                           const Scalar<Upward,AccelerationSI>& iniZ) { return {iniX,iniY,iniZ}; }
    /// @brief ....
    constexpr inline VolumeAcceleration xD(const Vec2D<Along,Across,AccelerationSI>& iniPV,
                                           const Scalar<Upward,AccelerationSI>& iniZ) { return {iniPV.x,iniPV.y,iniZ}; }

    //template<class ADDEND> // NON-EXPECTED RECURRENCE HERE!!!
    //constexpr inline auto operator + ( const ADDEND& a1,const ADDEND& a2){ return xD(a1+a2); }

    /// @brief ....
    /// \tparam ADDEND1
    /// \tparam ADDEND2
    /// \param a1
    /// \param a2
    /// \return
    template<class ADDEND1,class ADDEND2>
    constexpr inline auto operator + ( const ADDEND1& a1,const ADDEND2& a2){ return xD(a1,a2); }

    /// @brief ....
    /// \tparam ADDEND1
    /// \tparam ADDEND2
    /// \param a1
    /// \param a2
    /// \return
    template<class ADDEND1,class ADDEND2>
    constexpr inline auto operator - ( const ADDEND1& a1,const ADDEND2& a2){ return xD(a1,-a2); }
}


#endif //WB_SIMULATIONS_VECTORS_H
