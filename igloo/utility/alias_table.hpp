#pragma once

#include <vector>
#include <map>

namespace igloo
{


template<class Iterator>
class alias_table
{
  public:
    template<class Function>
    alias_table(Iterator values_begin, Iterator values_end, Function weight_function)
    {
      float sum_of_weights = 0;
      float mean_weight = 0;

      size_t n = 0;
      for(auto i = values_begin; i != values_end; ++i)
      {
        float weight = weight_function(*i);

        table_entry new_entry{i, i, weight, weight, weight};
        table_.emplace_back(new_entry);

        sum_of_weights += weight;
        ++n;
      }

      mean_weight = sum_of_weights / n;

      // mark all entries greater than the mean
      std::vector<std::reference_wrapper<table_entry>> rich;
      for(auto& entry : table_)
      {
        if(entry.divide > mean_weight)
        {
          rich.push_back(entry);
        }
      }

      // steal from the rich
      for(auto& entry : table_)
      {
        float difference = mean_weight - entry.divide;
        if(difference > 0)
        {
          if(rich.size() > 0)
          {
            // steal from the first rich entry
            table_entry& victim = rich.back();

            // set the alias to point to the victim
            entry.alias = victim.value;
            entry.alias_probability = victim.value_probability;

            // steal from the victim
            victim.divide -= difference;

            // did the victim become poor?
            if(victim.divide <= mean_weight)
            {
              rich.pop_back();
            }
          }
          else
          {
            // this case may occur due to floating point error
            // when difference ~ 0
            // fear not, it will still work
          }
        } // end if
      } // end for each entry

      float inv_mean_weight = 1.f / mean_weight;
      float inv_sum_of_weights = 1.f / sum_of_weights;

      // normalize and create inverse map
      inverse_map_.clear();
      for(auto& entry : table_)
      {
        entry.divide *= inv_mean_weight;
        entry.value_probability *= inv_sum_of_weights;
        entry.alias_probability *= inv_sum_of_weights;

        inverse_map_[entry.value] = entry.value_probability;
      }
    }

    template<class Range, class Function>
    alias_table(Range&& values, Function weight_function)
      : alias_table(std::forward<Range>(values).begin(), std::forward<Range>(values).end(), weight_function)
    {}

    // samples this alias_table's distribution
    // \param u A uniform random variable in [0,1).
    // \return The randomly selected element and the probability of selecting that element.
    std::pair<Iterator,float> operator()(float u) const
    {
      float q = float(table_.size()) * u;
      size_t index_of_selected_entry = static_cast<size_t>(q);
      float u1 = q - index_of_selected_entry;
      const auto& selected_entry = table_[index_of_selected_entry];

      if(u1 < selected_entry.divide)
      {
        return std::make_pair(selected_entry.value, selected_entry.value_probability);
      }

      return std::make_pair(selected_entry.alias, selected_entry.alias_probability);
    }

    /// \return The probability of selecting value.
    float probability_of(Iterator value) const
    {
      float result = 0;

      auto iter = inverse_map_.find(value);
      if(iter != inverse_map_.end())
      {
        result = iter->second;
      }

      return result;
    }

  private:
    struct table_entry
    {
      Iterator value;
      Iterator alias;
      float divide;
      float value_probability;
      float alias_probability;
    };

    //struct indirect_compare
    //{
    //  bool operator()(std::reference_wrapper<const T> lhs, std::reference_wrapper<const T> rhs) const
    //  {
    //    return lhs.get() < rhs.get();
    //  }
    //};

    std::vector<table_entry> table_;
    std::map<Iterator,float> inverse_map_;
};


} // end igloo

