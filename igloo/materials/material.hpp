#pragma once

#include <igloo/geometry/differential_geometry.hpp>
#include <igloo/scattering/scattering_distribution_function.hpp>
#include <igloo/utility/any.hpp>
#include <igloo/utility/demangle.hpp>
#include <string>
#include <memory>
#include <map>
#include <functional>
#include <typeinfo>


namespace igloo
{


class material
{
  public:
    /*! \return true if this material is emissive; false, otherwise.
     */
    virtual bool is_emitter() const;

    /*! \return true if this material is a sensor; false, otherwise.
     */
    virtual bool is_sensor() const;

    virtual scattering_distribution_function evaluate_scattering(const differential_geometry& dg) const;

    virtual scattering_distribution_function evaluate_emission(const differential_geometry& dg) const;
}; // end material


namespace detail
{


class material_factories
{
  public:
    using factory_type = std::function<std::unique_ptr<material>(const std::map<std::string,any>&)>;

    bool register_material(const std::string& name, factory_type factory);

    std::unique_ptr<material> make(const std::string& name, const std::map<std::string,any>& parameters) const;

    inline bool unregistered(const std::string& name) const
    {
      return factories_.find(name) == factories_.end();
    }

  private:
    std::map<std::string, factory_type> factories_;
};


material_factories& get_material_factories();


} // end detail


template<class DerivedMaterial>
struct registered_material : public material
{
  private:
    static bool registered;

    struct factory
    {
      std::unique_ptr<DerivedMaterial> operator()(const std::map<std::string,any>& parameters) const
      {
        return std::make_unique<DerivedMaterial>(parameters);
      }
    };

  protected:
    ~registered_material()
    {
      // these side effects seem to be enough to prevent
      // the compiler from optimizing the registered member
      // away which causes the register_material() call below
      // not to be called

      std::string foo = typeid(DerivedMaterial).name();
      if(registered)
      {
        foo.clear();
      }

      if(foo == "please don't optimize that static variable away")
      {
        assert(0);
      }
    }
};


// here we statically initialize the registered static variable
// the reason we do this is to cause side effects through the call register_material()
template<class DerivedMaterial>
bool registered_material<DerivedMaterial>::registered = detail::get_material_factories().register_material(
  type_name(typeid(DerivedMaterial)),
  registered_material<DerivedMaterial>::factory{}
);


std::unique_ptr<material> make_material(const std::string& name, const std::map<std::string,any>& parameters);


} // end igloo

