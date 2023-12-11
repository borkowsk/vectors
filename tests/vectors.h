/// @file vectors.h
/// @details
///     Created by borkowsk on 10.12.22.
///     Names changed from `create` into `xD` 11.12.23
/// @date 2023-12-11 (last modification)
#ifndef WB_SIMULATIONS_VECTORS_H
#define WB_SIMULATIONS_VECTORS_H

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
    struct Upwards:     public axis<Upwards>             { WB_VEC_CLASS_SPECIFIC const char* name(){ return "Z"; }
                                                                                                } static is_upwards;
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
        constexpr Quantity(const float_base& iniVal):value{iniVal}{}
        constexpr Quantity(const long double& iniVal):value{(float_base)iniVal}{ /** @todo RANGE CHECK ASSERT? */}
        constexpr Quantity(const unsigned long long& iniVal):value{(float_base)iniVal}{/** @todo RANGE CHECK ASSERT? */}
    };

#define WB_VEC_QUANTITY_BODY using Quantity::Quantity;

    // PHYSICAL QUANTITIES MEASURED IN SI UNITS:
    //*/////////////////////////////////////////

    /// @brief It is a quantity of length measured in SI units
    struct DistSI:     public Quantity<DistSI,SI_length_unit>       {WB_VEC_QUANTITY_BODY};
    /// @brief It is a quantity of time measured in SI units
    struct TimeSI:     public Quantity<TimeSI,SI_time_unit>         {WB_VEC_QUANTITY_BODY};
    /// @brief It is a quantity of mass measured in SI units
    struct MassSI:     public Quantity<MassSI,SI_mass_unit>         {WB_VEC_QUANTITY_BODY};
    /// @brief It is a quantity of temperature measured in SI units
    struct TempSI:     public Quantity<TempSI,SI_temperature_unit>  {WB_VEC_QUANTITY_BODY};
    /// @brief It is a quantity of speed measured in SI units
    struct VelocitySI: public Quantity<VelocitySI,SI_velocity_unit> {WB_VEC_QUANTITY_BODY};
    /// @brief It is a quantity of acceleration measured in SI units
    struct AccelerationSI: public Quantity<AccelerationSI,SI_acceleration_unit> {WB_VEC_QUANTITY_BODY};

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
        constexpr Scalar(const QUANTITY& initVal):val(initVal){}
    };

    template<class AXIS,class QUANTITY>
    inline auto xD(const QUANTITY& initVal,const AXIS& /*axis*/) {
        static_assert(AXIS::name() != nullptr);
        return Scalar<AXIS,QUANTITY>(initVal);
    }

#define WB_VEC_SCALAR_BODY(THISCLASS,AXIS,UNIT)          using Scalar::Scalar; \
                                                    constexpr THISCLASS(const Scalar<AXIS,UNIT>& sc):Scalar{sc}{}

    // PHYSICAL SCALARS FOR FLAT COORDINATE SYSTEM MEASURED IN SI UNITS:
    //*/////////////////////////////////////////////////////////////////

    struct TimeSpan:public Scalar<Time,TimeSI> {WB_VEC_SCALAR_BODY(TimeSpan,Time,TimeSI)};
    constexpr inline TimeSpan xD(const TimeSI& t) { return TimeSpan{t}; }

    struct MassQuan:public Scalar<Mass,MassSI> {WB_VEC_SCALAR_BODY(MassQuan,Mass,MassSI)};
    constexpr inline MassQuan xD(const MassSI& m) { return MassQuan{m}; }

    struct TempQuan:public Scalar<Temperature,TempSI> {WB_VEC_SCALAR_BODY(TempQuan,Temperature,TempSI)};
    constexpr inline TempQuan xD(const TempSI& tt) { return TempQuan{tt}; }

    struct Longitude:public Scalar<Along,DistSI> {WB_VEC_SCALAR_BODY(Longitude,Along,DistSI)};
    constexpr inline Longitude xD(const DistSI& d,const Along&) { return Longitude{d}; }

    struct Latitude:public Scalar<Across,DistSI> {WB_VEC_SCALAR_BODY(Latitude,Across,DistSI)};
    constexpr inline Latitude xD(const DistSI& d,const Across&) { return Latitude{d}; }

    struct Altitude:public Scalar<Upwards,DistSI> {WB_VEC_SCALAR_BODY(Altitude,Upwards,DistSI)};
    constexpr inline Altitude xD(const DistSI& d,const Upwards&) { return Altitude{d}; }

    struct VelAlong:public Scalar<Along,VelocitySI> {WB_VEC_SCALAR_BODY(VelAlong,Along,VelocitySI)};
    constexpr inline VelAlong xD(const VelocitySI& v,const Along&) { return VelAlong{v}; }

    struct VelAcross:public Scalar<Across,VelocitySI> {WB_VEC_SCALAR_BODY(VelAcross,Across,VelocitySI)};
    constexpr inline VelAcross xD(const VelocitySI& v,const Across&) { return VelAcross{v}; }

    struct VelUpwards:public Scalar<Upwards,VelocitySI> {WB_VEC_SCALAR_BODY(VelUpwards,Upwards,VelocitySI)};
    constexpr inline VelUpwards xD(const VelocitySI& v,const Upwards&) { return VelUpwards{v}; }

    struct AccAlong:public Scalar<Along,AccelerationSI> {WB_VEC_SCALAR_BODY(AccAlong,Along,AccelerationSI)};
    constexpr inline AccAlong xD(const AccelerationSI& a,const Along&) { return AccAlong{a}; }

    struct AccAcross:public Scalar<Across,AccelerationSI> {WB_VEC_SCALAR_BODY(AccAcross,Across,AccelerationSI)};
    constexpr inline AccAcross xD(const AccelerationSI& a,const Across&) { return AccAcross{a}; }

    struct AccUpwards:public Scalar<Upwards,AccelerationSI> {WB_VEC_SCALAR_BODY(AccUpwards,Upwards,AccelerationSI)};
    constexpr inline AccUpwards xD(const AccelerationSI& a,const Upwards&) { return AccUpwards{a}; }

}


#endif //WB_SIMULATIONS_VECTORS_H
